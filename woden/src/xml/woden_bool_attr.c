/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <woden_bool_attr.h>
#include <woden_xml_attr.h>
#include <axiom_element.h>
#include <axiom_node.h>

typedef struct woden_bool_attr_impl woden_bool_attr_impl_t;

/**
 * @brief Bool Attribute Struct Impl
 *   Axis2 Bool Attribute
 */
struct woden_bool_attr_impl
{
    woden_bool_attr_t bool_attr;
    woden_xml_attr_t *xml_attr;
    woden_obj_types_t obj_type;
    axis2_hash_t *methods;
};

#define INTF_TO_IMPL(bool_attr) \
    ((woden_bool_attr_impl_t *) bool_attr)

axis2_status_t AXIS2_CALL
woden_bool_attr_free(void *bool_attr,
        const axutil_env_t *env);

woden_obj_types_t AXIS2_CALL
woden_bool_attr_type(void *bool_attr,
        const axutil_env_t *env);

woden_xml_attr_t *AXIS2_CALL
woden_bool_attr_get_base_impl(void *bool_attr,
        const axutil_env_t *env);

axis2_bool_t AXIS2_CALL
woden_bool_attr_get_boolean(void *bool_attr,
        const axutil_env_t *env);

void *AXIS2_CALL
woden_bool_attr_convert(void *bool_attr,
        const axutil_env_t *env,
        axiom_element_t *owner_el,
        axiom_node_t *owner_node,
        axis2_char_t *attr_value);

static woden_bool_attr_t *
create(
    const axutil_env_t *env)
{
    woden_bool_attr_impl_t *bool_attr_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    bool_attr_impl = AXIS2_MALLOC(env->allocator,
            sizeof(woden_bool_attr_impl_t));

    bool_attr_impl->obj_type = WODEN_BOOL_ATTR;
    bool_attr_impl->xml_attr = NULL;
    bool_attr_impl->methods = NULL;
    bool_attr_impl->bool_attr.ops =
        AXIS2_MALLOC(env->allocator,
                sizeof(woden_bool_attr_ops_t));

    bool_attr_impl->bool_attr.ops->free =
        woden_bool_attr_free;
    bool_attr_impl->bool_attr.ops->type =
        woden_bool_attr_type;
    bool_attr_impl->bool_attr.ops->get_base_impl =
        woden_bool_attr_get_base_impl;
    bool_attr_impl->bool_attr.ops->get_boolean =
        woden_bool_attr_get_boolean;
    bool_attr_impl->bool_attr.ops->convert =
        woden_bool_attr_convert;


    bool_attr_impl->methods = axis2_hash_make(env);
    if (!bool_attr_impl->methods)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    axis2_hash_set(bool_attr_impl->methods, "free",
            AXIS2_HASH_KEY_STRING, woden_bool_attr_free);
    axis2_hash_set(bool_attr_impl->methods, "type",
            AXIS2_HASH_KEY_STRING, woden_bool_attr_type);
    axis2_hash_set(bool_attr_impl->methods, "get_boolean",
            AXIS2_HASH_KEY_STRING, woden_bool_attr_get_boolean);
    axis2_hash_set(bool_attr_impl->methods, "convert",
            AXIS2_HASH_KEY_STRING, woden_bool_attr_convert);

    return &(bool_attr_impl->bool_attr);
}
/*
 * TODO This constructor is not used for extension attributes, but may be useful if
 * parsing of native WSDL attributes is changed to use the XMLAttr interface.
 */
AXIS2_EXTERN woden_bool_attr_t * AXIS2_CALL
woden_bool_attr_create(
    const axutil_env_t *env,
    axiom_element_t *owner_el,
    axiom_node_t *owner_node,
    axis2_qname_t *attr_type,
    axis2_char_t *attr_value)
{
    woden_bool_attr_impl_t *bool_attr_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    bool_attr_impl = (woden_bool_attr_impl_t *) create(env);

    bool_attr_impl->xml_attr = woden_xml_attr_create(env, owner_el,
            owner_node, attr_type, attr_value);
    return &(bool_attr_impl->bool_attr);
}

woden_obj_types_t AXIS2_CALL
woden_bool_attr_type(
    void *bool_attr,
    const axutil_env_t *env)
{
    woden_bool_attr_impl_t *bool_attr_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    bool_attr_impl = INTF_TO_IMPL(bool_attr);

    return bool_attr_impl->obj_type;
}

axis2_status_t AXIS2_CALL
woden_bool_attr_free(void *bool_attr,
        const axutil_env_t *env)
{
    woden_bool_attr_impl_t *bool_attr_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    bool_attr_impl = INTF_TO_IMPL(bool_attr);

    if (bool_attr_impl->methods)
    {
        axis2_hash_free(bool_attr_impl->methods, env);
        bool_attr_impl->methods = NULL;
    }

    if (bool_attr_impl->xml_attr)
    {
        WODEN_XML_ATTR_FREE(bool_attr_impl->xml_attr, env);
        bool_attr_impl->xml_attr = NULL;
    }

    if ((&(bool_attr_impl->bool_attr))->ops)
    {
        AXIS2_FREE(env->allocator, (&(bool_attr_impl->bool_attr))->ops);
        (&(bool_attr_impl->bool_attr))->ops = NULL;
    }

    if (bool_attr_impl)
    {
        AXIS2_FREE(env->allocator, bool_attr_impl);
        bool_attr_impl = NULL;
    }
    return AXIS2_SUCCESS;
}

woden_xml_attr_t *AXIS2_CALL
woden_bool_attr_get_base_impl(void *bool_attr,
        const axutil_env_t *env)
{
    woden_bool_attr_impl_t *bool_attr_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    bool_attr_impl = INTF_TO_IMPL(bool_attr);

    return bool_attr_impl->xml_attr;
}

axis2_status_t AXIS2_CALL
woden_bool_attr_resolve_methods(
    woden_bool_attr_t *bool_attr,
    const axutil_env_t *env,
    axis2_hash_t *methods)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, methods, AXIS2_FAILURE);

    bool_attr->ops->free =
        axis2_hash_get(methods, "free", AXIS2_HASH_KEY_STRING);
    bool_attr->ops->to_bool_attr_free = axis2_hash_get(methods,
            "to_bool_attr_free", AXIS2_HASH_KEY_STRING);
    bool_attr->ops->type =
        axis2_hash_get(methods, "type", AXIS2_HASH_KEY_STRING);
    bool_attr->ops->get_boolean = axis2_hash_get(methods, "get_boolean",
            AXIS2_HASH_KEY_STRING);
    bool_attr->ops->convert = axis2_hash_get(methods, "convert",
            AXIS2_HASH_KEY_STRING);

    return AXIS2_SUCCESS;
}

axis2_bool_t AXIS2_CALL
woden_bool_attr_get_boolean(void *bool_attr,
        const axutil_env_t *env)
{
    woden_bool_attr_impl_t *bool_attr_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    bool_attr_impl = INTF_TO_IMPL(bool_attr);
    /* TODO return WODEN_XML_ATTR_GET_CONTENT(
            bool_attr_impl->xml_attr, env);
     */
    return AXIS2_FALSE;
}

void *AXIS2_CALL
woden_bool_attr_convert(void *bool_attr,
        const axutil_env_t *env,
        axiom_element_t *owner_el,
        axiom_node_t *owner_node,
        axis2_char_t *attr_value)
{
    woden_bool_attr_impl_t *bool_attr_impl = NULL;
    axis2_qname_t *qn = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    bool_attr_impl = INTF_TO_IMPL(bool_attr);

    if (attr_value)
    {
        /* TODO */
    }

    if (!qn)
    {
        WODEN_XML_ATTR_SET_VALID(bool_attr_impl->xml_attr, env, AXIS2_FALSE);
        /* TODO handler error */
    }

    return qn;
}

