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

#include <guththila_error.h>
#include <guththila_defines.h>
#include <stdlib.h>

guththila_char_t *GUTHTHILA_CALL
guththila_error_ops_get_message ()
{
    return "This is the default error code";
}

int GUTHTHILA_CALL
guththila_error_free(guththila_error_t *error)
{
    if(!error) return 0;
    if(error->ops)
        free(error->ops);
    free(error);
    return 1;
}


GUTHTHILA_DECLARE (guththila_error_t *)
guththila_error_create (guththila_allocator_t * allocator)
{
    guththila_error_t *error;
    if (!allocator)
        return NULL;

    error =
        (guththila_error_t *) GUTHTHILA_MALLOC (allocator,
                                sizeof (guththila_error_t));

    if (!error)
        return NULL;

    error->ops =
        (guththila_error_ops_t *) GUTHTHILA_MALLOC (allocator,
                                sizeof(guththila_error_ops_t));

    if (!error->ops)
    {
        GUTHTHILA_FREE (allocator, error);
        return NULL;
    }

    error->ops->get_message = guththila_error_ops_get_message;
    error->ops->free = guththila_error_free;
    
    return error;
}
