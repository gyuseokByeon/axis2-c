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

#include <axiom_doctype.h>
#include <axis2_string.h>
#include "axiom_node_internal.h"

axis2_status_t AXIS2_CALL
axiom_doctype_free(axiom_doctype_t *om_doctype,
        const axis2_env_t *env);

axis2_status_t AXIS2_CALL
axiom_doctype_set_value(axiom_doctype_t *om_doctype,
        const axis2_env_t *env,
        const axis2_char_t *value);

axis2_char_t* AXIS2_CALL
axiom_doctype_get_value(axiom_doctype_t *om_doctype,
        const axis2_env_t *env);

axis2_status_t AXIS2_CALL
axiom_doctype_serialize(axiom_doctype_t *om_doctype,
        const axis2_env_t *env,
        axiom_output_t *om_output);

/************************ axiom_doctype struct *********************/

typedef struct axiom_doctype_impl_t
{
    /* this should be first member for casting to work */
    axiom_doctype_t om_doctype;
    /** Doctype value */
    axis2_char_t *value;

}
axiom_doctype_impl_t;

/*************************** Macro ***********************************/

#define AXIS2_INTF_TO_IMPL(om_doctype) ((axiom_doctype_impl_t*)om_doctype)

/********************************************************************/

AXIS2_EXTERN axiom_doctype_t * AXIS2_CALL
axiom_doctype_create(const axis2_env_t *env,
        axiom_node_t * parent,
        const axis2_char_t * value,
        axiom_node_t ** node)
{
    axiom_doctype_impl_t *doctype = NULL;
    AXIS2_ENV_CHECK(env, NULL);
    AXIS2_PARAM_CHECK(env->error, node, NULL);

    *node = axiom_node_create(env);
    if (!*node)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    doctype = (axiom_doctype_impl_t *) AXIS2_MALLOC(env->allocator,
            sizeof(axiom_doctype_impl_t));

    if (!doctype)
    {
        AXIS2_FREE(env->allocator, (*node));
        AXIS2_ERROR_SET(env->error , AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    doctype->value = NULL;

    if (value)
    {
        doctype->value = (axis2_char_t*)AXIS2_STRDUP(value, env);
        if (!doctype->value)
        {
            AXIS2_FREE(env->allocator, doctype);
            AXIS2_FREE(env->allocator, (*node));
            AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
            return NULL;
        }
    }

    axiom_node_set_data_element((*node), env, doctype);
    axiom_node_set_node_type((*node), env, AXIOM_DOCTYPE);

    if (parent)
    {
        AXIOM_NODE_ADD_CHILD(parent, env, (*node));
    }

    /* ops */
    doctype->om_doctype.ops = NULL;
    doctype->om_doctype.ops = (axiom_doctype_ops_t *) AXIS2_MALLOC(
                env->allocator, sizeof(axiom_doctype_ops_t));

    if (!doctype->om_doctype.ops)
    {
        AXIS2_FREE(env->allocator, doctype);
        AXIS2_FREE(env->allocator, doctype->value);
        AXIS2_FREE(env->allocator, *node);
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    doctype->om_doctype.ops->free = axiom_doctype_free;

    return &(doctype->om_doctype);
}


axis2_status_t AXIS2_CALL
axiom_doctype_free(axiom_doctype_t *om_doctype,
        const axis2_env_t *env)
{
    if (om_doctype)
    {
        if (AXIS2_INTF_TO_IMPL(om_doctype)->value)
        {
            AXIS2_FREE(env->allocator, AXIS2_INTF_TO_IMPL(om_doctype)->value);
        }
        AXIS2_FREE(env->allocator, AXIS2_INTF_TO_IMPL(om_doctype));
        return AXIS2_SUCCESS;
    }
    return AXIS2_FAILURE;
}

axis2_status_t AXIS2_CALL
axiom_doctype_set_value(axiom_doctype_t *om_doctype,
        const axis2_env_t *env,
        const axis2_char_t *value)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, value, AXIS2_FAILURE);
    AXIS2_INTF_TO_IMPL(om_doctype)->value =
        (axis2_char_t*)AXIS2_STRDUP(value, env);
    return AXIS2_SUCCESS;
}

axis2_char_t* AXIS2_CALL
axiom_doctype_get_value(axiom_doctype_t *om_doctype,
        const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(om_doctype)->value;
}

axis2_status_t AXIS2_CALL
axiom_doctype_serialize(axiom_doctype_t *om_doctype,
        const axis2_env_t *env,
        axiom_output_t *om_output)
{
    axiom_doctype_impl_t *doctype_impl;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, om_output, AXIS2_FAILURE);

    doctype_impl = AXIS2_INTF_TO_IMPL(om_doctype);
    if (doctype_impl->value)
        return  axiom_output_write(om_output, env,
                AXIOM_DOCTYPE, 1, doctype_impl->value);

    return AXIS2_FAILURE;
}