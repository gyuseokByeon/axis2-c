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

#include <woden_soap_binding_fault_ref_exts.h>
#include <woden_component_exts.h>
#include <woden_wsdl_element.h>
#include <woden_string_attr.h>
#include <woden_qname_or_token_any_attr.h>
#include <woden_qname_list_or_token_any_attr.h>
#include "woden_soap_constants.h"

typedef struct woden_soap_binding_fault_ref_exts_impl woden_soap_binding_fault_ref_exts_impl_t;

/**
 * @brief Soap Binding Fault Reference Extensions Struct Impl
 *   Axis2 Soap Binding Fault Reference Extensions
 */
struct woden_soap_binding_fault_ref_exts_impl
{
    woden_soap_binding_fault_ref_exts_t binding_fault_ref_exts;
    woden_component_exts_t *component_exts;
    axis2_hash_t *methods;
    axis2_hash_t *super;
    woden_obj_types_t obj_type;

    axis2_qname_t *qname;
};

#define INTF_TO_IMPL(binding_fault_ref_exts) ((woden_soap_binding_fault_ref_exts_impl_t *) binding_fault_ref_exts)

axis2_status_t AXIS2_CALL
woden_soap_binding_fault_ref_exts_free(
    void *binding_fault_ref_exts,
    const axis2_env_t *env);

axis2_hash_t *AXIS2_CALL
woden_soap_binding_fault_ref_exts_super_objs(
    void *binding_fault_ref_exts,
    const axis2_env_t *env);

woden_obj_types_t AXIS2_CALL
woden_soap_binding_fault_ref_exts_type(
    void *binding_fault_ref_exts,
    const axis2_env_t *env);

woden_component_exts_t *AXIS2_CALL
woden_soap_binding_fault_ref_exts_get_base_impl(
    void *binding_fault_ref_exts,
    const axis2_env_t *env);

axis2_array_list_t *AXIS2_CALL
woden_soap_binding_fault_ref_exts_get_soap_modules(
    void *binding_fault_ref_exts,
    const axis2_env_t *env);

static woden_soap_binding_fault_ref_exts_t *
create(
    const axis2_env_t *env);

static axis2_status_t
woden_soap_binding_fault_ref_exts_free_ops(
    void *binding_fault_ref_exts,
    const axis2_env_t *env);

/************************Woden C Internal Methods******************************/
AXIS2_EXTERN woden_soap_binding_fault_ref_exts_t * AXIS2_CALL
woden_soap_binding_fault_ref_exts_to_component_exts(
    void *binding_fault_ref_exts,
    const axis2_env_t *env)
{
    woden_soap_binding_fault_ref_exts_impl_t *binding_fault_ref_exts_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    if (!binding_fault_ref_exts)
    {
        binding_fault_ref_exts_impl = (woden_soap_binding_fault_ref_exts_impl_t *) create(env);
    }
    else
        binding_fault_ref_exts_impl = (woden_soap_binding_fault_ref_exts_impl_t *) binding_fault_ref_exts;
    woden_soap_binding_fault_ref_exts_free_ops(binding_fault_ref_exts, env);

    binding_fault_ref_exts_impl->binding_fault_ref_exts.component_exts.ops =
        AXIS2_MALLOC(env->allocator,
                sizeof(woden_component_exts_ops_t));
    woden_component_exts_resolve_methods(&(binding_fault_ref_exts_impl->binding_fault_ref_exts.
            component_exts), env, binding_fault_ref_exts_impl->methods);
    return binding_fault_ref_exts;
}

/************************End of Woden C Internal Methods***********************/
static woden_soap_binding_fault_ref_exts_t *
create(const axis2_env_t *env)
{
    woden_soap_binding_fault_ref_exts_impl_t *binding_fault_ref_exts_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    binding_fault_ref_exts_impl = AXIS2_MALLOC(env->allocator,
            sizeof(woden_soap_binding_fault_ref_exts_impl_t));

    binding_fault_ref_exts_impl->obj_type = WODEN_SOAP_BINDING_FAULT_REF_EXTS;
    binding_fault_ref_exts_impl->super = NULL;
    binding_fault_ref_exts_impl->methods = NULL;

    binding_fault_ref_exts_impl->component_exts = NULL;
    binding_fault_ref_exts_impl->qname = NULL;

    binding_fault_ref_exts_impl->binding_fault_ref_exts.component_exts.ops = NULL;

    binding_fault_ref_exts_impl->binding_fault_ref_exts.ops = AXIS2_MALLOC(env->allocator,
            sizeof(woden_soap_binding_fault_ref_exts_ops_t));

    binding_fault_ref_exts_impl->binding_fault_ref_exts.ops->free = woden_soap_binding_fault_ref_exts_free;
    binding_fault_ref_exts_impl->binding_fault_ref_exts.ops->super_objs =
        woden_soap_binding_fault_ref_exts_super_objs;
    binding_fault_ref_exts_impl->binding_fault_ref_exts.ops->type =
        woden_soap_binding_fault_ref_exts_type;
    binding_fault_ref_exts_impl->binding_fault_ref_exts.ops->get_base_impl =
        woden_soap_binding_fault_ref_exts_get_base_impl;

    binding_fault_ref_exts_impl->binding_fault_ref_exts.ops->get_soap_modules =
        woden_soap_binding_fault_ref_exts_get_soap_modules;

    binding_fault_ref_exts_impl->methods = axis2_hash_make(env);
    if (!binding_fault_ref_exts_impl->methods)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    axis2_hash_set(binding_fault_ref_exts_impl->methods, "free", AXIS2_HASH_KEY_STRING,
            woden_soap_binding_fault_ref_exts_free);
    axis2_hash_set(binding_fault_ref_exts_impl->methods, "super_objs",
            AXIS2_HASH_KEY_STRING, woden_soap_binding_fault_ref_exts_super_objs);
    axis2_hash_set(binding_fault_ref_exts_impl->methods, "type",
            AXIS2_HASH_KEY_STRING, woden_soap_binding_fault_ref_exts_type);

    axis2_hash_set(binding_fault_ref_exts_impl->methods, "get_modules",
            AXIS2_HASH_KEY_STRING,
            woden_soap_binding_fault_ref_exts_get_soap_modules);

    return &(binding_fault_ref_exts_impl->binding_fault_ref_exts);
}

AXIS2_EXTERN woden_soap_binding_fault_ref_exts_t * AXIS2_CALL
woden_soap_binding_fault_ref_exts_create(const axis2_env_t *env)
{
    woden_soap_binding_fault_ref_exts_impl_t *binding_fault_ref_exts_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    binding_fault_ref_exts_impl = (woden_soap_binding_fault_ref_exts_impl_t *) create(env);

    binding_fault_ref_exts_impl->component_exts = woden_component_exts_create(env);

    binding_fault_ref_exts_impl->super = axis2_hash_make(env);
    if (!binding_fault_ref_exts_impl->super)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    axis2_hash_set(binding_fault_ref_exts_impl->super, "WODEN_SOAP_BINDING_FAULT_REF_EXTS", AXIS2_HASH_KEY_STRING,
            &(binding_fault_ref_exts_impl->binding_fault_ref_exts));
    axis2_hash_set(binding_fault_ref_exts_impl->super, "WODEN_COMPONENT_EXTS", AXIS2_HASH_KEY_STRING,
            binding_fault_ref_exts_impl->component_exts);

    return &(binding_fault_ref_exts_impl->binding_fault_ref_exts);
}

static axis2_status_t
woden_soap_binding_fault_ref_exts_free_ops(
    void *binding_fault_ref_exts,
    const axis2_env_t *env)
{
    woden_soap_binding_fault_ref_exts_impl_t *binding_fault_ref_exts_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    binding_fault_ref_exts_impl = INTF_TO_IMPL(binding_fault_ref_exts);

    if (binding_fault_ref_exts_impl->binding_fault_ref_exts.component_exts.ops)
    {
        AXIS2_FREE(env->allocator, binding_fault_ref_exts_impl->binding_fault_ref_exts.
                component_exts.ops);
        binding_fault_ref_exts_impl->binding_fault_ref_exts.component_exts.ops = NULL;
    }

    return AXIS2_SUCCESS;
}


axis2_status_t AXIS2_CALL
woden_soap_binding_fault_ref_exts_free(void *binding_fault_ref_exts,
        const axis2_env_t *env)
{
    woden_soap_binding_fault_ref_exts_impl_t *binding_fault_ref_exts_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    binding_fault_ref_exts_impl = INTF_TO_IMPL(binding_fault_ref_exts);

    if (binding_fault_ref_exts_impl->super)
    {
        axis2_hash_free(binding_fault_ref_exts_impl->super, env);
        binding_fault_ref_exts_impl->super = NULL;
    }

    if (binding_fault_ref_exts_impl->methods)
    {
        axis2_hash_free(binding_fault_ref_exts_impl->methods, env);
        binding_fault_ref_exts_impl->methods = NULL;
    }

    if (binding_fault_ref_exts_impl->component_exts)
    {
        WODEN_COMPONENT_EXTS_FREE(binding_fault_ref_exts_impl->component_exts, env);
        binding_fault_ref_exts_impl->component_exts = NULL;
    }

    if (binding_fault_ref_exts_impl->qname)
    {
        AXIS2_QNAME_FREE(binding_fault_ref_exts_impl->qname, env);
        binding_fault_ref_exts_impl->qname = NULL;
    }
    woden_soap_binding_fault_ref_exts_free_ops(binding_fault_ref_exts, env);

    if ((&(binding_fault_ref_exts_impl->binding_fault_ref_exts))->ops)
    {
        AXIS2_FREE(env->allocator, (&(binding_fault_ref_exts_impl->binding_fault_ref_exts))->ops);
        (&(binding_fault_ref_exts_impl->binding_fault_ref_exts))->ops = NULL;
    }

    if (binding_fault_ref_exts_impl)
    {
        AXIS2_FREE(env->allocator, binding_fault_ref_exts_impl);
        binding_fault_ref_exts_impl = NULL;
    }
    return AXIS2_SUCCESS;
}

axis2_hash_t *AXIS2_CALL
woden_soap_binding_fault_ref_exts_super_objs(
    void *binding_fault_ref_exts,
    const axis2_env_t *env)
{
    woden_soap_binding_fault_ref_exts_impl_t *binding_fault_ref_exts_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    binding_fault_ref_exts_impl = INTF_TO_IMPL(binding_fault_ref_exts);

    return binding_fault_ref_exts_impl->super;
}

woden_obj_types_t AXIS2_CALL
woden_soap_binding_fault_ref_exts_type(
    void *binding_fault_ref_exts,
    const axis2_env_t *env)
{
    woden_soap_binding_fault_ref_exts_impl_t *binding_fault_ref_exts_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    binding_fault_ref_exts_impl = INTF_TO_IMPL(binding_fault_ref_exts);

    return binding_fault_ref_exts_impl->obj_type;
}

woden_component_exts_t *AXIS2_CALL
woden_soap_binding_fault_ref_exts_get_base_impl(
    void *binding_fault_ref_exts,
    const axis2_env_t *env)
{
    woden_soap_binding_fault_ref_exts_impl_t *binding_fault_ref_exts_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    binding_fault_ref_exts_impl = INTF_TO_IMPL(binding_fault_ref_exts);

    return binding_fault_ref_exts_impl->component_exts;
}

axis2_status_t AXIS2_CALL
woden_soap_binding_fault_ref_exts_resolve_methods(
    woden_soap_binding_fault_ref_exts_t *binding_fault_ref_exts,
    const axis2_env_t *env,
    woden_soap_binding_fault_ref_exts_t *binding_fault_ref_exts_impl,
    axis2_hash_t *methods)
{
    woden_soap_binding_fault_ref_exts_impl_t *binding_fault_ref_exts_impl_l = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, methods, AXIS2_FAILURE);
    binding_fault_ref_exts_impl_l = INTF_TO_IMPL(binding_fault_ref_exts_impl);

    binding_fault_ref_exts->ops->free = axis2_hash_get(methods, "free",
            AXIS2_HASH_KEY_STRING);
    binding_fault_ref_exts->ops->super_objs = axis2_hash_get(methods, "super_objs",
            AXIS2_HASH_KEY_STRING);
    binding_fault_ref_exts->ops->type = axis2_hash_get(methods, "type",
            AXIS2_HASH_KEY_STRING);

    binding_fault_ref_exts->ops->get_soap_modules = axis2_hash_get(methods,
            "get_soap_modules", AXIS2_HASH_KEY_STRING);
    if (!binding_fault_ref_exts->ops->get_soap_modules && binding_fault_ref_exts_impl_l)
        binding_fault_ref_exts->ops->get_soap_modules =
            binding_fault_ref_exts_impl_l->binding_fault_ref_exts.ops->get_soap_modules;

    return AXIS2_SUCCESS;
}

axis2_array_list_t *AXIS2_CALL
woden_soap_binding_fault_ref_exts_get_soap_modules(
    void *binding_fault_ref_exts,
    const axis2_env_t *env)
{
    woden_soap_binding_fault_ref_exts_impl_t *binding_fault_ref_exts_impl = NULL;
    axis2_array_list_t *soap_mods = NULL;
    void *parent_element = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    binding_fault_ref_exts_impl = INTF_TO_IMPL(binding_fault_ref_exts);

    parent_element = WODEN_COMPONENT_EXTS_GET_PARENT_ELEMENT(
                binding_fault_ref_exts_impl->component_exts, env);
    parent_element = woden_wsdl_element_to_element_extensible(parent_element,
            env);
    binding_fault_ref_exts_impl->qname = axis2_qname_create_from_string(env,
            WODEN_Q_ELEM_SOAP_MODULE);
    soap_mods = WODEN_ELEMENT_EXTENSIBLE_GET_EXT_ELEMENTS_OF_TYPE(
                parent_element, env, binding_fault_ref_exts_impl->qname);

    return soap_mods;
}
