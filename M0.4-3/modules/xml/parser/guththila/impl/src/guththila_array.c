/* Copyright 2000-2005 The Apache Software Foundation or its licensors, as
 * applicable.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */  
    
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "guththila_array.h"
#include "guththila_string.h"
    
/*****************************************************************
 * This file contains guththila_array  functions.
 */ 
    
/*****************************************************************
 *
 * The 'array' functions...
 */ 
    
make_array_core (guththila_array_header_t * res,
                 guththila_environment_t * environment, 
                 int elt_size,
                 int clear) 
{
    
/*
* Assure sanity if someone asks for
* array of zero elts.
*/ 
    if (nelts < 1)
    {
        nelts = 1;
    }
    
    {
        res->elts = GUTHTHILA_MALLOC (environment->allocator, nelts * elt_size);
    }
    else
    {
        res->elts = GUTHTHILA_MALLOC (environment->allocator, nelts * elt_size);
    }
    
    res->elt_size = elt_size;
    res->nelts = 0;            /* No active elements yet... */
    res->nalloc = nelts;       /* ...but this many allocated */
}

guththila_is_empty_array (const guththila_array_header_t * a) 
{
    return ((a == NULL) || (a->nelts == 0));
}
guththila_array_make (guththila_environment_t * environment, 
                      int elt_size) 
{
    guththila_array_header_t * res;
    res = (guththila_array_header_t *) GUTHTHILA_MALLOC (environment->allocator,
                                                sizeof(guththila_array_header_t));
    
    return res;
}
guththila_array_pop (guththila_array_header_t *arr) 
{
    
    {
        return NULL;
    }
    return arr->elts + (arr->elt_size * (--arr->nelts));
}
guththila_array_push (guththila_array_header_t *arr) 
{
    
    {
        int new_size = (arr->nalloc <= 0) ? 1 : arr->nalloc * 2;
        guththila_char_t * new_data;
        new_data =  GUTHTHILA_MALLOC (arr->environment->allocator,
                                       arr->elt_size * new_size);
        
        memcpy (new_data, arr->elts, arr->nalloc * arr->elt_size);
        memset (new_data + arr->nalloc * arr->elt_size, 0,
        arr->elt_size * (new_size - arr->nalloc));
        arr->elts = new_data;
        arr->nalloc = new_size;
    }
    
    ++arr->nelts;
    return arr->elts + (arr->elt_size * (arr->nelts - 1));
}

/*
static void *guththila_array_push_noclear(guththila_array_header_t *arr)
{
    if (arr->nelts == arr->nalloc) {
        int new_size = (arr->nalloc <= 0) ? 1 : arr->nalloc * 2;
        guththila_char_t *new_data;

        new_data = GUTHTHILA_MALLOC(arr->environment->allocator, arr->elt_size * new_size);

        memcpy(new_data, arr->elts, arr->nalloc * arr->elt_size);
        arr->elts = new_data;
        arr->nalloc = new_size;
    }

    ++arr->nelts;
    return arr->elts + (arr->elt_size * (arr->nelts - 1));
}
*/ 

GUTHTHILA_DECLARE (void) 
guththila_array_cat (guththila_array_header_t *dst,
                     const guththila_array_header_t *src) 
{
    
    
    if (dst->nelts + src->nelts > dst->nalloc)
    {
        
        int new_size = (dst->nalloc <= 0) ? 1 : dst->nalloc * 2;
        guththila_char_t * new_data;
    
        {
            new_size *= 2;
        }
        
                                     elt_size * new_size);
        
        memcpy (new_data, dst->elts, dst->nalloc * elt_size);

        dst->nalloc = new_size;
    }
    memcpy (dst->elts + dst->nelts * elt_size, src->elts,
            elt_size * src->nelts);
    dst->nelts += src->nelts;
}
guththila_array_copy (guththila_environment_t * environment,
                      const guththila_array_header_t * arr) 
{
    guththila_array_header_t * res = (guththila_array_header_t *) GUTHTHILA_MALLOC(
                                         environment->allocator,
                                         sizeof(guththila_array_header_t));
    
    make_array_core (res, environment, arr->nalloc, arr->elt_size, 0);
    
    memcpy (res->elts, arr->elts, arr->elt_size * arr->nelts);
    
    res->nelts = arr->nelts;
    
             
    
}
/* This cute function copies the array header *only*, but arranges
 * for the data section to be copied on the first push or arraycat.
 * It's useful when the elements of the array being copied are
 * read only, but new stuff *might* get added on the end; we have the
 * overhead of the full copy only where it is really needed.
 */ 
    
copy_array_hdr_core (guththila_array_header_t * res,
                     const guththila_array_header_t * arr) 
{
    
        
        
        
}
guththila_array_copy_hdr (guththila_environment_t * environment,
                          const guththila_array_header_t * arr) 
{
    guththila_array_header_t * res;
    
                                            environment->allocator,
                                            sizeof(guththila_array_header_t));
    
    
    return res;
}

/* The above is used here to avoid consing multiple new array bodies... */ 
    
guththila_array_append (guththila_environment_t * environment,
                        const guththila_array_header_t * first,
                        const guththila_array_header_t * second) 
{
    
        
        guththila_array_cat (res, second);
        return res;
}

/* guththila_array_pstrcat generates a new string containing
 * the concatenated sequence of substrings referenced as elements within
 * the array.  The string will be empty if all substrings are empty or null,
 * or if there are no elements in the array.
 * If sep is non-NUL, it will be inserted between elements as a separator.
 */ 


GUTHTHILA_DECLARE (guththila_char_t *)
guththila_array_pstrcat (guththila_environment_t * environment,
                         const guththila_array_header_t * arr,
                         const guththila_char_t sep) 
{
    
        
        
        
    {                           /* Empty table? */
          return (guththila_char_t *) GUTHTHILA_MALLOC (
                            environment->allocator, 1);
    }    
        /* Pass one --- find length of required string */ 
        
    
    {
      if (strpp && *strpp != NULL)
      {
           len += GUTHTHILA_STRLEN ( *strpp);
      }
        
        {
            break;
        }
        
        {
            ++len;
        }
    }
        /* Allocate the required string */ 
        
                            environment->allocator, len + 1);
    cp = res;
    
        
    {
        if (strpp && *strpp != NULL)
        {
            len = GUTHTHILA_STRLEN (*strpp);
            memcpy (cp, *strpp, len);
            cp += len;
        }
        
        {
            break;
        }
        
        {
            *cp++ = sep;
        }
    
    
    
        
}


guththila_array_free (guththila_environment_t * environment,
                      guththila_array_header_t * header) 
{
    if (header != NULL)
    {
        
                GUTHTHILA_FREE (environment->allocator, header->elts);
        GUTHTHILA_FREE (environment->allocator, header);
        return GUTHTHILA_SUCCESS;
    }
    return GUTHTHILA_FAILURE;
}