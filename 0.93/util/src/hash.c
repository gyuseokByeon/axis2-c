/*
 * Copyright 2004,2005 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "axis2_hash.h"

#include <axis2_string.h>

/*
 * The internal form of a hash table.
 *
 * The table is an array indexed by the hash of the key; collisions
 * are resolved by hanging a linked list of hash entries off each
 * element of the array. Although this is a really simple design it
 * isn't too bad given that environments have a low allocation overhead.
 */

typedef struct axis2_hash_entry_t axis2_hash_entry_t;

struct axis2_hash_entry_t
{
    axis2_hash_entry_t *next;
    unsigned int hash;
    const void *key;
    axis2_ssize_t klen;
    const void *val;
};

/*
 * Data structure for iterating through a hash table.
 *
 * We keep a pointer to the next hash entry here to allow the current
 * hash entry to be freed or otherwise mangled between calls to
 * axis2_hash_next().
 */
struct axis2_hash_index_t
{
    axis2_hash_t *ht;
    axis2_hash_entry_t *this, *next;
    unsigned int index;
};

/*
 * The size of the array is always a power of two. We use the maximum
 * index rather than the size so that we can use bitwise-AND for
 * modular arithmetic.
 * The count of hash entries may be greater depending on the chosen
 * collision rate.
 */
struct axis2_hash_t
{
    const axis2_env_t *env;
    axis2_hash_entry_t **array;
    axis2_hash_index_t iterator;    /* For axis2_hash_first(NULL, ...) */
    unsigned int count, max;
    axis2_hashfunc_t hash_func;
    axis2_hash_entry_t *free;   /* List of recycled entries */
};

#define INITIAL_MAX 15          /* tunable == 2^n - 1 */


/*
 * Hash creation functions.
 */

static axis2_hash_entry_t **
alloc_array (axis2_hash_t *ht, unsigned int max)
{
    return memset (AXIS2_MALLOC (ht->env->allocator,  
                   sizeof (*ht->array) * (max + 1)), 0,
                   sizeof (*ht->array) * (max + 1));
}

AXIS2_EXTERN axis2_hash_t* AXIS2_CALL
axis2_hash_make (const axis2_env_t *env)
{
    axis2_hash_t *ht;
    AXIS2_ENV_CHECK(env, NULL);
    
    ht = AXIS2_MALLOC (env->allocator, sizeof (axis2_hash_t));
    ht->env = env;
    ht->free = NULL;
    ht->count = 0;
    ht->max = INITIAL_MAX;
    ht->array = alloc_array (ht, ht->max);
    ht->hash_func = axis2_hashfunc_default;
    return ht;
}

AXIS2_EXTERN axis2_hash_t* AXIS2_CALL
axis2_hash_make_custom (const axis2_env_t *env,
                        axis2_hashfunc_t hash_func)
{
    axis2_hash_t *ht;
    AXIS2_ENV_CHECK(env, NULL);
    ht = axis2_hash_make (env);
    ht->hash_func = hash_func;
    return ht;
}


/*
 * Hash iteration functions.
 */

AXIS2_EXTERN axis2_hash_index_t* AXIS2_CALL
axis2_hash_next (const axis2_env_t *env, axis2_hash_index_t *hi)
{
    hi->this = hi->next;
    while (!hi->this)
    {
        if (hi->index > hi->ht->max)
        {
            if (env)
                AXIS2_FREE (env->allocator, hi); 
            return NULL;
        }

        hi->this = hi->ht->array[hi->index++];
    }
    hi->next = hi->this->next;
    return hi;
}

AXIS2_EXTERN axis2_hash_index_t* AXIS2_CALL
axis2_hash_first (axis2_hash_t *ht, const axis2_env_t *env)
{
    axis2_hash_index_t *hi;
    if (env)
        hi = AXIS2_MALLOC (env->allocator, sizeof (*hi));
    else
        hi = &ht->iterator;

    hi->ht = ht;
    hi->index = 0;
    hi->this = NULL;
    hi->next = NULL;
    return axis2_hash_next (env, hi);
}

AXIS2_EXTERN void AXIS2_CALL
axis2_hash_this (axis2_hash_index_t *hi,
                 const void **key, axis2_ssize_t *klen, void **val)
{
    if (key)
        *key = hi->this->key;
    if (klen)
        *klen = hi->this->klen;
    if (val)
        *val = (void *) hi->this->val;
}


/*
 * Expanding a hash table
 */

static void
expand_array (axis2_hash_t * ht)
{
    axis2_hash_index_t *hi;
    
    axis2_hash_entry_t **new_array;
    unsigned int new_max;

    new_max = ht->max * 2 + 1;
    new_array = alloc_array (ht, new_max);
    for (hi = axis2_hash_first (ht, NULL); hi;
         hi = axis2_hash_next (NULL, hi))
    {
        unsigned int i = hi->this->hash & new_max;
        hi->this->next = new_array[i];
        new_array[i] = hi->this;
    }
    AXIS2_FREE (ht->env->allocator, ht->array);
    ht->array = new_array;
    ht->max = new_max;
}

unsigned int
axis2_hashfunc_default (const char *char_key, axis2_ssize_t * klen)
{
    unsigned int hash = 0;
    const unsigned char *key = (const unsigned char *) char_key;
    const unsigned char *p;
    axis2_ssize_t i;

    /*
     * This is the popular `times 33' hash algorithm which is used by
     * perl and also appears in Berkeley DB. This is one of the best
     * known hash functions for strings because it is both computed
     * very fast and distributes very well.
     *
     * The originator may be Dan Bernstein but the code in Berkeley DB
     * cites Chris Torek as the source. The best citation I have found
     * is "Chris Torek, Hash function for text in C, Usenet message
     * <27038@mimsy.umd.edu> in comp.lang.c , October, 1990." in Rich
     * Salz's USENIX 1992 paper about INN which can be found at
     * <http://citeseer.nj.nec.com/salz92internetnews.html>.
     *
     * The magic of number 33, i.e. why it works better than many other
     * constants, prime or not, has never been adequately explained by
     * anyone. So I try an explanation: if one experimentally tests all
     * multipliers between 1 and 256 (as I did while writing a low-level
     * data structure library some time ago) one detects that even
     * numbers are not useable at all. The remaining 128 odd numbers
     * (except for the number 1) work more or less all equally well.
     * They all distribute in an acceptable way and this way fill a hash
     * table with an average percent of approx. 86%.
     *
     * If one compares the chi^2 values of the variants (see
     * Bob Jenkins ``Hashing Frequently Asked Questions'' at
     * http://burtleburtle.net/bob/hash/hashfaq.html for a description
     * of chi^2), the number 33 not even has the best value. But the
     * number 33 and a few other equally good numbers like 17, 31, 63,
     * 127 and 129 have nevertheless a great advantage to the remaining
     * numbers in the large set of possible multipliers: their multiply
     * op can be replaced by a faster op based on just one
     * shift plus either a single addition or subtraction op. And
     * because a hash function has to both distribute good _and_ has to
     * be very fast to compute, those few numbers should be preferred.
     *
     *                  -- Ralf S. Engelschall <rse@engelschall.com>
     */

    if (*klen == AXIS2_HASH_KEY_STRING)
    {
        for (p = key; *p; p++)
        {
            hash = hash * 33 + *p;
        }
        *klen = p - key;
    }
    else
    {
        for (p = key, i = *klen; i; i--, p++)
        {
            hash = hash * 33 + *p;
        }
    }

    return hash;
}


/*
 * This is where we keep the details of the hash function and control
 * the maximum collision rate.
 *
 * If val is non-NULL it creates and initializes a new hash entry if
 * there isn't already one there; it returns an updatable pointer so
 * that hash entries can be removed.
 */

static axis2_hash_entry_t **
find_entry (axis2_hash_t * ht,
            const void *key, axis2_ssize_t klen, const void *val)
{
    axis2_hash_entry_t **hep, *he;
    unsigned int hash;

    hash = ht->hash_func (key, &klen);

    /* scan linked list */
    for (hep = &ht->array[hash & ht->max], he = *hep;
         he; hep = &he->next, he = *hep)
    {
        if (he->hash == hash
            && he->klen == klen && memcmp (he->key, key, klen) == 0)
            break;
    }
    
    if (he || !val)
        return hep;

    /* add a new entry for non-NULL values */
    if ((he = ht->free) != NULL)
        ht->free = he->next;
    else
        he = AXIS2_MALLOC (ht->env->allocator, sizeof (*he));
    he->next = NULL;
    he->hash = hash;
    he->key = key;
    he->klen = klen;
    he->val = val;
    *hep = he;
    ht->count++;
    return hep;
}

AXIS2_EXTERN axis2_hash_t* AXIS2_CALL
axis2_hash_copy (const axis2_hash_t *orig, const axis2_env_t *env)
{
    axis2_hash_t *ht;
    axis2_hash_entry_t *new_vals;
    unsigned int i, j;
    
    AXIS2_ENV_CHECK(env, NULL);

    ht = AXIS2_MALLOC (env->allocator, sizeof (axis2_hash_t) +
                       sizeof (*ht->array) * (orig->max + 1) +
                       sizeof (axis2_hash_entry_t) * orig->count);
    ht->env = env;
    ht->free = NULL;
    ht->count = orig->count;
    ht->max = orig->max;
    ht->hash_func = orig->hash_func;
    ht->array = (axis2_hash_entry_t **) ((char *) ht + sizeof (axis2_hash_t));

    new_vals = (axis2_hash_entry_t *) ((char *) (ht) + sizeof (axis2_hash_t) +
                                       sizeof (*ht->array) * (orig->max + 1));
    j = 0;
    for (i = 0; i <= ht->max; i++)
    {
        axis2_hash_entry_t **new_entry = &(ht->array[i]);
        axis2_hash_entry_t *orig_entry = orig->array[i];
        while (orig_entry)
        {
            *new_entry = &new_vals[j++];
            (*new_entry)->hash = orig_entry->hash;
            (*new_entry)->key = orig_entry->key;
            (*new_entry)->klen = orig_entry->klen;
            (*new_entry)->val = orig_entry->val;
            new_entry = &((*new_entry)->next);
            orig_entry = orig_entry->next;
        }
        *new_entry = NULL;
    }
    return ht;
}

AXIS2_EXTERN void* AXIS2_CALL
axis2_hash_get (axis2_hash_t *ht, const void *key, axis2_ssize_t klen)
{
    axis2_hash_entry_t *he;
    he = *find_entry (ht, key, klen, NULL);
    if (he)
        return (void *) he->val;
    else
        return NULL;
}

AXIS2_EXTERN void AXIS2_CALL
axis2_hash_set (axis2_hash_t *ht,
                const void *key, axis2_ssize_t klen, const void *val)
{
    axis2_hash_entry_t **hep;
    hep = find_entry (ht, key, klen, val);
    if (*hep)
    {
        if (!val)
        {
            /* delete entry */
            axis2_hash_entry_t *old = *hep;
            *hep = (*hep)->next;
            old->next = ht->free;
            ht->free = old;
            --ht->count;
        }
        else
        {
            /* replace entry */
            (*hep)->val = val;
            /* check that the collision rate isn't too high */
            if (ht->count > ht->max)
            {
                expand_array (ht);
            }
        }
    }
    /* else key not present and val==NULL */
}

AXIS2_EXTERN  unsigned int  AXIS2_CALL
axis2_hash_count (axis2_hash_t * ht)
{
    return ht->count;
}

AXIS2_EXTERN axis2_hash_t* AXIS2_CALL
axis2_hash_overlay (const axis2_hash_t *overlay, const axis2_env_t *env
      , const axis2_hash_t * base)
{
    AXIS2_ENV_CHECK(env, NULL);
    return axis2_hash_merge (overlay, env, base, NULL, NULL);
}

AXIS2_EXTERN axis2_hash_t* AXIS2_CALL
axis2_hash_merge (const axis2_hash_t *overlay, const axis2_env_t *env
         , const axis2_hash_t * base, void *(*merger) (const axis2_env_t * env
            , const void *key, axis2_ssize_t klen, const void *h1_val
            , const void *h2_val, const void *data), const void *data)
{
    axis2_hash_t *res;
    axis2_hash_entry_t *new_vals = NULL;
    axis2_hash_entry_t *iter;
    axis2_hash_entry_t *ent;
    unsigned int i, j, k;
    AXIS2_ENV_CHECK(env, NULL);
    
#if AXIS2_POOL_DEBUG
    /* we don't copy keys and values, so it's necessary that
     * overlay->a.env and base->a.env have a life span at least
     * as long as p
     */
    if (!axis2_env_is_ancestor (overlay->env, p))
    {
        fprintf (stderr,
                 "axis2_hash_merge: overlay's env is not an ancestor of p\n");
        abort ();
    }
    if (!axis2_env_is_ancestor (base->env, p))
    {
        fprintf (stderr,
                 "axis2_hash_merge: base's env is not an ancestor of p\n");
        abort ();
    }
#endif

    res = AXIS2_MALLOC (env->allocator, sizeof (axis2_hash_t));
    res->env = env;
    res->free = NULL;
    res->hash_func = base->hash_func;
    res->count = base->count;
    res->max = (overlay->max > base->max) ? overlay->max : base->max;
    if (base->count + overlay->count > res->max)
    {
        res->max = res->max * 2 + 1;
    }
    res->array = alloc_array (res, res->max);
    if (base->count + overlay->count)
    {
        new_vals =
            AXIS2_MALLOC (env->allocator,
                          sizeof (axis2_hash_entry_t) * (base->count +
                                                         overlay->count));
    }
    j = 0;
    for (k = 0; k <= base->max; k++)
    {
        for (iter = base->array[k]; iter; iter = iter->next)
        {
            i = iter->hash & res->max;
            new_vals[j].klen = iter->klen;
            new_vals[j].key = iter->key;
            new_vals[j].val = iter->val;
            new_vals[j].hash = iter->hash;
            new_vals[j].next = res->array[i];
            res->array[i] = &new_vals[j];
            j++;
        }
    }

    for (k = 0; k <= overlay->max; k++)
    {
        for (iter = overlay->array[k]; iter; iter = iter->next)
        {
            i = iter->hash & res->max;
            for (ent = res->array[i]; ent; ent = ent->next)
            {
                if ((ent->klen == iter->klen) &&
                    (memcmp (ent->key, iter->key, iter->klen) == 0))
                {
                    if (merger)
                    {
                        ent->val =
                            (*merger) (env, iter->key, iter->klen,
                                       iter->val, ent->val, data);
                    }
                    else
                    {
                        ent->val = iter->val;
                    }
                    break;
                }
            }
            if (!ent)
            {
                new_vals[j].klen = iter->klen;
                new_vals[j].key = iter->key;
                new_vals[j].val = iter->val;
                new_vals[j].hash = iter->hash;
                new_vals[j].next = res->array[i];
                res->array[i] = &new_vals[j];
                res->count++;
                j++;
            }
        }
    }
    return res;
}

AXIS2_EXTERN axis2_bool_t AXIS2_CALL
axis2_hash_contains_key (
        axis2_hash_t *ht, 
        const axis2_env_t *env,
        const axis2_char_t *key)
{
    axis2_hash_index_t *i = NULL;
    
    AXIS2_ENV_CHECK(env, AXIS2_FALSE);
    
    for (i = axis2_hash_first (ht, env); i; i = axis2_hash_next (env, i))
    {
        const void *v = NULL;
        const axis2_char_t *key_l = NULL;
        
        axis2_hash_this (i, &v, NULL, NULL);
        key_l = (const axis2_char_t *) v;
        if(0 == AXIS2_STRCMP(key, key_l))
            return AXIS2_TRUE;
    }

    return AXIS2_FALSE;
} 

static axis2_status_t
axis2_hash_entry_free (const axis2_env_t *env, axis2_hash_entry_t *hash_entry)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    if (!hash_entry)
        return AXIS2_FAILURE;
    if (hash_entry->next)
    {
        axis2_hash_entry_free (env, hash_entry->next);
    }
    AXIS2_FREE (env->allocator, hash_entry);
    return AXIS2_SUCCESS;
}

AXIS2_EXTERN axis2_status_t AXIS2_CALL
axis2_hash_free (axis2_hash_t *ht, const axis2_env_t* env)
{
    int i =0;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    if (ht)
    {
        for(i = 0;i <= ht->max; i++)
        {
            axis2_hash_entry_t *next = NULL;
            axis2_hash_entry_t *current = ht->array[i];
            while(current)
            {
                next = current->next;
                AXIS2_FREE(env->allocator, current);
                current = NULL;
                current = next;
            }
        }
        if (ht->free)
        {
            axis2_hash_entry_t *next = NULL;
            axis2_hash_entry_t *current = ht->free;
            while(current)
            {
                next = current->next;
                AXIS2_FREE(env->allocator, current);
                current = NULL;
                current = next;
            }
        }
        AXIS2_FREE(env->allocator, (ht->array));
        AXIS2_FREE (env->allocator, ht);
        return AXIS2_SUCCESS;
    }
    return AXIS2_FAILURE;
}

AXIS2_EXTERN axis2_status_t AXIS2_CALL
axis2_hash_free_void_arg (void *ht_void, const axis2_env_t* env)
{
    int i =0;
    axis2_hash_t *ht = (axis2_hash_t*)ht_void;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    if (ht)
    {
        for(i = 0;i <ht->max; i++)
        {
            axis2_hash_entry_t *next = NULL;
            axis2_hash_entry_t *current = ht->array[i];
            while(current)
            {
                next = current->next;
                AXIS2_FREE(env->allocator, current);
                current = next;
            }
        }
        AXIS2_FREE(env->allocator, (ht->array));
        AXIS2_FREE (env->allocator, ht);
        return AXIS2_SUCCESS;
    }
    return AXIS2_FAILURE;
}