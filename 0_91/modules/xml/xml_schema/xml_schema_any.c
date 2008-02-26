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

#include <xml_schema/axis2_xml_schema_any.h>

typedef struct axis2_xml_schema_any_impl 
                axis2_xml_schema_any_impl_t;

/** 
 * @brief Other Extension Struct Impl
 *	Axis2 Other Extension  
 */ 
struct axis2_xml_schema_any_impl
{
    axis2_xml_schema_any_t any;
    axis2_xml_schema_particle_t *particle;
    axis2_xml_schema_types_t obj_type;
    axis2_hash_t *super;
    axis2_hash_t *methods;
    
    axis2_xml_schema_content_processing_t *process_content;
    /**
     * Namespaces containing the elements that can be used.
     */
    axis2_char_t *ns;
};

#define AXIS2_INTF_TO_IMPL(any) ((axis2_xml_schema_any_impl_t *) any)

/******************* function prototypes **********************************/
axis2_status_t AXIS2_CALL 
axis2_xml_schema_any_free(
        void *any,
        axis2_env_t **env);

axis2_hash_t *AXIS2_CALL 
axis2_xml_schema_any_super_objs(
        void *any,
        axis2_env_t **env);

axis2_xml_schema_types_t AXIS2_CALL 
axis2_xml_schema_any_type(
        void *any,
        axis2_env_t **env);

axis2_xml_schema_particle_t *AXIS2_CALL
axis2_xml_schema_any_get_base_impl(void *any,
                                    axis2_env_t **env);

axis2_char_t *AXIS2_CALL
axis2_xml_schema_any_get_namespace(void *any,
                                    axis2_env_t **env);

axis2_status_t AXIS2_CALL
axis2_xml_schema_any_set_namespace(void *any,
                                            axis2_env_t **env,
                                            axis2_char_t *namespc);

axis2_xml_schema_content_processing_t *AXIS2_CALL
axis2_xml_schema_any_get_process_content(void *any,
                                            axis2_env_t **env);

axis2_status_t AXIS2_CALL
axis2_xml_schema_any_set_process_content(void *any,
                                            axis2_env_t **env,
                                            axis2_xml_schema_content_processing_t *
                                                process_content);
                                                
 /************************ end function prototypes ******************************/
 
AXIS2_DECLARE(axis2_xml_schema_any_t *)
axis2_xml_schema_any_create(axis2_env_t **env)
{
    axis2_xml_schema_any_impl_t *any_impl = NULL;
    axis2_status_t status = AXIS2_FAILURE;
    
    any_impl = AXIS2_MALLOC((*env)->allocator, 
                    sizeof(axis2_xml_schema_any_impl_t));
    if(!any_impl)
    {
        AXIS2_ERROR_SET((*env)->error , AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    any_impl->any.base.ops = NULL;
    any_impl->any.ops = NULL;
    any_impl->ns = NULL;
    any_impl->obj_type = AXIS2_XML_SCHEMA_ANY;
    any_impl->super = NULL;
    any_impl->particle = NULL;
    any_impl->process_content = NULL;
    any_impl->any.ops = AXIS2_MALLOC((*env)->allocator, 
                    sizeof(axis2_xml_schema_any_ops_t));

    if(!any_impl->any.ops)
    {
        axis2_xml_schema_any_free(&(any_impl->any), env);
        AXIS2_ERROR_SET((*env)->error , 
            AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    any_impl->process_content = axis2_xml_schema_content_processing_create(env, 
            "None");
    if(!any_impl->process_content)
    {
        axis2_xml_schema_any_free(&(any_impl->any), env);
        return NULL;
    }            
    any_impl->any.ops->free = 
        axis2_xml_schema_any_free;
    any_impl->any.ops->super_objs = 
        axis2_xml_schema_any_super_objs;
    any_impl->any.ops->type = 
        axis2_xml_schema_any_type;
    any_impl->any.ops->get_base_impl = 
        axis2_xml_schema_any_get_base_impl;
    any_impl->any.ops->get_namespace = 
        axis2_xml_schema_any_get_namespace;
    any_impl->any.ops->set_namespace = 
        axis2_xml_schema_any_set_namespace;
    any_impl->any.ops->get_process_content = 
        axis2_xml_schema_any_get_process_content;
    any_impl->any.ops->set_process_content = 
        axis2_xml_schema_any_set_process_content;

    any_impl->methods = axis2_hash_make(env);
    if(!any_impl->methods)
    {
        AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    axis2_hash_set(any_impl->methods, "free", AXIS2_HASH_KEY_STRING, 
            axis2_xml_schema_any_super_objs);
    axis2_hash_set(any_impl->methods, "super_objs", AXIS2_HASH_KEY_STRING, 
            axis2_xml_schema_any_free);
    axis2_hash_set(any_impl->methods, "type", AXIS2_HASH_KEY_STRING, 
            axis2_xml_schema_any_type);
    axis2_hash_set(any_impl->methods, "get_namespace", AXIS2_HASH_KEY_STRING, 
            axis2_xml_schema_any_get_namespace);
    axis2_hash_set(any_impl->methods, "set_namespace", AXIS2_HASH_KEY_STRING, 
            axis2_xml_schema_any_set_namespace);
    axis2_hash_set(any_impl->methods, "get_process_content", 
            AXIS2_HASH_KEY_STRING, axis2_xml_schema_any_get_process_content);
    axis2_hash_set(any_impl->methods, "set_process_content", 
            AXIS2_HASH_KEY_STRING, axis2_xml_schema_any_set_process_content);
    
    any_impl->particle = axis2_xml_schema_particle_create(env);
    if(!any_impl->particle)
    {
        axis2_xml_schema_any_free(&(any_impl->any), env);
        AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    any_impl->super = axis2_hash_make(env);
    if(!any_impl->super)
    {
        AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    axis2_hash_set(any_impl->super, "AXIS_XML_SCHEMA_ANY", AXIS2_HASH_KEY_STRING, 
            &(any_impl->any));
    axis2_hash_set(any_impl->super, "AXIS_XML_SCHEMA_PARTICLE", AXIS2_HASH_KEY_STRING, 
            any_impl->particle);

    status = axis2_xml_schema_particle_resolve_methods(
            &(any_impl->any.base), env, any_impl->particle, 
            any_impl->methods); 
    return &(any_impl->any);
}

axis2_status_t AXIS2_CALL
axis2_xml_schema_any_free(void *any,
                            axis2_env_t **env)
{
    axis2_xml_schema_any_impl_t *any_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    any_impl = AXIS2_INTF_TO_IMPL(any);

    if(NULL != any_impl->ns)
    {
        AXIS2_FREE((*env)->allocator, any_impl->ns);
        any_impl->ns = NULL;
    }
    
    if(NULL != any_impl->process_content)
    {
        AXIS2_XML_SCHEMA_CONTENT_PROCESSING_FREE(any_impl->process_content, env);
        any_impl->process_content = NULL;
    }
 
    if(NULL != any_impl->super)
    {
        axis2_hash_free(any_impl->super, env);
        any_impl->super = NULL;
    }
 
    if(NULL != any_impl->methods)
    {
        axis2_hash_free(any_impl->methods, env);
        any_impl->methods = NULL;
    }
   
    if(NULL != any_impl->particle)
    {
        AXIS2_XML_SCHEMA_PARTICLE_FREE(any_impl->particle, env);
        any_impl->particle = NULL;
    }
    
    if(NULL != any_impl->any.ops)
    {
        AXIS2_FREE((*env)->allocator, any_impl->any.ops);
        any_impl->any.ops = NULL;
    }
    if(NULL != any_impl->any.base.ops)
    {
        AXIS2_FREE((*env)->allocator, any_impl->any.base.ops);
        any_impl->any.base.ops = NULL;    
    }

    AXIS2_FREE((*env)->allocator, any_impl);
    any_impl = NULL;
    return AXIS2_SUCCESS;
}

axis2_xml_schema_types_t AXIS2_CALL
axis2_xml_schema_any_type(void *any,
                                axis2_env_t **env)
{
    axis2_xml_schema_any_impl_t *any_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    any_impl = AXIS2_INTF_TO_IMPL(any);
    return any_impl->obj_type;
}

axis2_hash_t *AXIS2_CALL
axis2_xml_schema_any_super_objs(
        void *any,
        axis2_env_t **env)
{
    axis2_xml_schema_any_impl_t *any_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    any_impl = AXIS2_INTF_TO_IMPL(any);
    return any_impl->super;
}

axis2_xml_schema_particle_t *AXIS2_CALL
axis2_xml_schema_any_get_base_impl(void *any,
                                axis2_env_t **env)
{
    axis2_xml_schema_any_impl_t *any_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    any_impl = AXIS2_INTF_TO_IMPL(any);
    return any_impl->particle;
}

AXIS2_DECLARE(axis2_status_t)
axis2_xml_schema_any_resolve_methods(
        axis2_xml_schema_any_t *any,
        axis2_env_t **env,
        axis2_xml_schema_any_t *any_impl,
        axis2_hash_t *methods)
{
    axis2_xml_schema_any_impl_t *any_impl_l = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, any_impl, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, methods, AXIS2_FAILURE);
    
    any_impl_l = (axis2_xml_schema_any_impl_t *) any_impl;
    
    any->ops = AXIS2_MALLOC((*env)->allocator, 
            sizeof(axis2_xml_schema_any_ops_t));
    any->ops->free = axis2_hash_get(methods, "free", 
            AXIS2_HASH_KEY_STRING);
    any->ops->super_objs = axis2_hash_get(methods, "super_objs", 
            AXIS2_HASH_KEY_STRING);
    any->ops->type = axis2_hash_get(methods, "type", 
            AXIS2_HASH_KEY_STRING);
    
    any->ops->get_namespace = axis2_hash_get(methods, 
            "get_namespace", AXIS2_HASH_KEY_STRING);
    if(!any->ops->get_namespace)
            any->ops->get_namespace = 
            any_impl_l->any.ops->get_namespace;
    
    any->ops->set_namespace = axis2_hash_get(methods, 
            "set_namespace", AXIS2_HASH_KEY_STRING);
    if(!any->ops->set_namespace)
    any->ops->set_namespace = 
            any_impl_l->any.ops->set_namespace;
    
    any->ops->get_process_content = axis2_hash_get(methods, 
            "get_process_content", AXIS2_HASH_KEY_STRING);
    if(!any->ops->get_process_content)
    any->ops->get_process_content = 
            any_impl_l->any.ops->get_process_content;
    
    any->ops->set_process_content = axis2_hash_get(methods, 
            "set_process_content", AXIS2_HASH_KEY_STRING);
    if(!any->ops->set_process_content)
    any->ops->set_process_content = 
            any_impl_l->any.ops->set_process_content;
    
    return axis2_xml_schema_particle_resolve_methods(&(any->base), 
            env, any_impl_l->particle, methods);
}

axis2_char_t *AXIS2_CALL
axis2_xml_schema_any_get_namespace(void *any,
                                    axis2_env_t **env)
{
    axis2_xml_schema_any_impl_t *any_impl = NULL;
    axis2_hash_t *super = NULL;
    
    super = AXIS2_XML_SCHEMA_ANY_SUPER_OBJS(any, env);
    any_impl = AXIS2_INTF_TO_IMPL(axis2_hash_get(super, 
                "AXIS2_XML_SCHEMA_ANY", AXIS2_HASH_KEY_STRING));

    return any_impl->ns;
}

axis2_status_t AXIS2_CALL
axis2_xml_schema_any_set_namespace(void *any,
                                            axis2_env_t **env,
                                            axis2_char_t *namespc)
{
    axis2_xml_schema_any_impl_t *any_impl = NULL;
    axis2_hash_t *super = NULL;
    
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    super = AXIS2_XML_SCHEMA_ANY_SUPER_OBJS(any, env);
    any_impl = AXIS2_INTF_TO_IMPL(axis2_hash_get(super, 
                "AXIS2_XML_SCHEMA_ANY", AXIS2_HASH_KEY_STRING));
    
    if(!any_impl->ns)
    {
        AXIS2_FREE((*env)->allocator, any_impl->ns);
        any_impl->ns = NULL;
    }
    any_impl->ns = AXIS2_STRDUP(any_impl->ns, env);
    return AXIS2_SUCCESS;
}

axis2_xml_schema_content_processing_t *AXIS2_CALL
axis2_xml_schema_any_get_process_content(void *any,
                                            axis2_env_t **env)
{
    axis2_xml_schema_any_impl_t *any_impl = NULL;
    axis2_hash_t *super = NULL;
    super = AXIS2_XML_SCHEMA_ANY_SUPER_OBJS(any, env);
    any_impl = AXIS2_INTF_TO_IMPL(axis2_hash_get(super, 
                "AXIS2_XML_SCHEMA_ANY", AXIS2_HASH_KEY_STRING));

    return any_impl->process_content;
}

axis2_status_t AXIS2_CALL
axis2_xml_schema_any_set_process_content(void *any,
                                        axis2_env_t **env,
                                        axis2_xml_schema_content_processing_t *
                                                process_content)
{
    axis2_xml_schema_any_impl_t *any_impl = NULL;
    axis2_hash_t *super = NULL;
    
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    super = AXIS2_XML_SCHEMA_ANY_SUPER_OBJS(any, env);
    any_impl = AXIS2_INTF_TO_IMPL(axis2_hash_get(super, 
                "AXIS2_XML_SCHEMA_ANY", AXIS2_HASH_KEY_STRING));
    
    if(!any_impl->process_content)
    {
        AXIS2_XML_SCHEMA_CONTENT_PROCESSING_FREE(any_impl->process_content, env);
        any_impl->process_content = NULL;
    }
    any_impl->process_content = process_content;
    return AXIS2_SUCCESS;
}
