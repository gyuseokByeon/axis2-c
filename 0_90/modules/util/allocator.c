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

#include <axis2_allocator.h>
#include <axis2.h>
#include <stdlib.h>

AXIS2_DECLARE(axis2_allocator_t *)
axis2_allocator_init (axis2_allocator_t * allocator)
{
    if (allocator)
        return allocator;

    else
    {
        allocator = (axis2_allocator_t *) malloc (sizeof (axis2_allocator_t));
        if (allocator)
        {
            allocator->malloc = malloc;
            allocator->realloc = realloc;
            allocator->free = free;
            return allocator;
        }
    }
    return NULL;
}

AXIS2_DECLARE(axis2_status_t)
axis2_allocator_free(axis2_allocator_t *allocator)
{
    void (*free_func)(void *) = NULL;
    if(allocator)
    {
        free_func = allocator->free; 
        free_func(allocator);
    }
    return AXIS2_SUCCESS;
}