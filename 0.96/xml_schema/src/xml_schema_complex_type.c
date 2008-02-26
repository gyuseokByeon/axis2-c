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

#include <xml_schema.h>
#include <xml_schema_constants.h>
#include <xml_schema_complex_type.h>
#include <xml_schema_data_type.h>
#include <xml_schema_derivation_method.h>
#include <axis2_qname.h>

typedef struct xml_schema_complex_type_impl
            xml_schema_complex_type_impl_t;

/**
 * @brief complex type struct impl
 *   Axis2 Other Extension
 */
struct xml_schema_complex_type_impl
{
    xml_schema_complex_type_t complex_type;

    /** parent type */
    xml_schema_type_t *schema_type;

    xml_schema_any_attribute_t *any_attr, *attr_wildcard;

    xml_schema_obj_collection_t *attributes;

    xml_schema_obj_table_t *attr_uses;

    xml_schema_derivation_method_t *block, *block_resolved;

    /** type stores the type of model stored in content_model */
    void *content_model;

    xml_schema_content_type_t *content_type;

    void *particle_type;
    void *particle;

    axis2_bool_t is_abstract, is_mixed;

    xml_schema_types_t obj_type;

    axis2_hash_t *ht_super;

};

#define AXIS2_INTF_TO_IMPL(complex_type) \
        ((xml_schema_complex_type_impl_t *) complex_type)

/************************** function prototypes ******************************/

axis2_status_t AXIS2_CALL
xml_schema_complex_type_free(
    void *complex_type,
    const axis2_env_t *env);


xml_schema_type_t* AXIS2_CALL
xml_schema_complex_type_get_base_impl(
    void *complex_type,
    const axis2_env_t *env);

xml_schema_types_t AXIS2_CALL
xml_schema_complex_type_get_type(
    void *complex_type,
    const axis2_env_t *env);

axis2_hash_t* AXIS2_CALL
xml_schema_complex_type_super_objs(
    void *complex_type,
    const axis2_env_t *env);

xml_schema_any_attribute_t* AXIS2_CALL
xml_schema_complex_type_get_any_attribute(
    void *cmp_type,
    const axis2_env_t *env);

axis2_status_t  AXIS2_CALL
xml_schema_complex_type_set_any_attribute(
    void *cmp_type,
    const axis2_env_t *env,
    xml_schema_any_attribute_t *any_attr);

xml_schema_obj_collection_t* AXIS2_CALL
xml_schema_complex_type_get_attributes(
    void *cmp_type,
    const axis2_env_t *env);

xml_schema_obj_table_t* AXIS2_CALL
xml_schema_complex_type_get_attribute_use(
    void *cmp_type,
    const axis2_env_t *env);

xml_schema_any_attribute_t* AXIS2_CALL
xml_schema_complex_type_get_attribute_wildcard(
    void *cmp_type,
    const axis2_env_t *env);

xml_schema_derivation_method_t* AXIS2_CALL
xml_schema_complex_type_get_block(
    void *cmp_type,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
xml_schema_complex_type_set_block(
    void *cmp_type,
    const axis2_env_t *env,
    xml_schema_derivation_method_t *block);

xml_schema_derivation_method_t* AXIS2_CALL
xml_schema_complex_type_get_block_resolved(
    void *cmp_type,
    const axis2_env_t *env);

void* AXIS2_CALL
xml_schema_complex_type_get_content_model(
    void *cmp_type,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
xml_schema_complex_type_set_content_model(
    void *cmp_type,
    const axis2_env_t *env,
    void *content_model);

xml_schema_content_type_t* AXIS2_CALL
xml_schema_complex_type_get_content_type(
    void *cmp_type,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
xml_schema_complex_type_set_content_type(
    void *cmp_type,
    const axis2_env_t *env,
    xml_schema_content_type_t *content_type);

xml_schema_particle_t * AXIS2_CALL
xml_schema_complex_type_get_content_type_particle(
    void *cmp_type,
    const axis2_env_t *env);

axis2_bool_t AXIS2_CALL
xml_schema_complex_type_is_abstract(
    void *cmp_type,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
xml_schema_complex_type_set_abstract(
    void *cmp_type,
    const axis2_env_t *env,
    axis2_bool_t b);

axis2_bool_t AXIS2_CALL
xml_schema_complex_type_is_mixed(
    void *cmp_type,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
xml_schema_complex_type_set_mixed(
    void *cmp_type,
    const axis2_env_t *env,
    axis2_bool_t b);

void* AXIS2_CALL
xml_schema_complex_type_get_particle(
    void *cmp_type,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
xml_schema_complex_type_set_particle(
    void *cmp_type,
    const axis2_env_t *env,
    void *particle);

axis2_char_t* AXIS2_CALL
xml_schema_complex_type_to_string(
    void *cmp_type,
    const axis2_env_t *env,
    axis2_char_t *prefix,
    int tab);


/************************** end ***********************************************/

AXIS2_EXTERN xml_schema_complex_type_t * AXIS2_CALL
xml_schema_complex_type_create(
    const axis2_env_t *env,
    xml_schema_t *schema)
{
    xml_schema_complex_type_impl_t *complex_type_impl = NULL;
    xml_schema_annotated_t *annotated = NULL;

    complex_type_impl = AXIS2_MALLOC(env->allocator,
            sizeof(xml_schema_complex_type_impl_t));
    if (!complex_type_impl)
    {
        AXIS2_ERROR_SET(env->error,
                AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    complex_type_impl->any_attr = NULL;
    complex_type_impl->attr_uses = NULL;
    complex_type_impl->attr_wildcard = NULL;
    complex_type_impl->attributes = NULL;
    complex_type_impl->block = NULL;
    complex_type_impl->block_resolved = NULL;
    complex_type_impl->complex_type.ops = NULL;
    complex_type_impl->complex_type.base.ops = NULL;
    complex_type_impl->content_model = NULL;
    complex_type_impl->content_type = NULL;
    complex_type_impl->attr_uses = NULL;
    complex_type_impl->is_mixed = AXIS2_FALSE;
    complex_type_impl->is_abstract = AXIS2_FALSE;
    complex_type_impl->ht_super = NULL;
    complex_type_impl->obj_type = XML_SCHEMA_COMPLEX_TYPE;

    complex_type_impl->complex_type.ops = AXIS2_MALLOC(env->allocator,
            sizeof(xml_schema_complex_type_ops_t));
    if (!complex_type_impl->complex_type.ops)
    {
        xml_schema_complex_type_free(&(complex_type_impl->complex_type), env);
        AXIS2_ERROR_SET(env->error,
                AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    complex_type_impl->schema_type = xml_schema_type_create(env, schema);
    if (!complex_type_impl->schema_type)
    {
        xml_schema_complex_type_free(&(complex_type_impl->complex_type), env);
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    complex_type_impl->attributes = xml_schema_obj_collection_create(env);

    if (!complex_type_impl->attributes)
    {
        xml_schema_complex_type_free(&(complex_type_impl->complex_type), env);
        return NULL;
    }

    complex_type_impl->block = xml_schema_derivation_method_create(env, "none");
    if (!complex_type_impl->block)
    {
        xml_schema_complex_type_free(&(complex_type_impl->complex_type), env);
        return NULL;
    }

    complex_type_impl->complex_type.ops->free =
        xml_schema_complex_type_free;
    complex_type_impl->complex_type.ops->get_type =
        xml_schema_complex_type_get_type;
    complex_type_impl->complex_type.ops->super_objs =
        xml_schema_complex_type_super_objs;
    complex_type_impl->complex_type.ops->get_base_impl =
        xml_schema_complex_type_get_base_impl;
    complex_type_impl->complex_type.ops->get_any_attribute =
        xml_schema_complex_type_get_any_attribute;
    complex_type_impl->complex_type.ops->set_any_attribute =
        xml_schema_complex_type_set_any_attribute;
    complex_type_impl->complex_type.ops->get_attributes =
        xml_schema_complex_type_get_attributes;
    complex_type_impl->complex_type.ops->get_attribute_use =
        xml_schema_complex_type_get_attribute_use;
    complex_type_impl->complex_type.ops->get_attribute_wildcard =
        xml_schema_complex_type_get_attribute_wildcard;
    complex_type_impl->complex_type.ops->get_block =
        xml_schema_complex_type_get_block;
    complex_type_impl->complex_type.ops->set_block =
        xml_schema_complex_type_set_block;
    complex_type_impl->complex_type.ops->get_block_resolved =
        xml_schema_complex_type_get_block_resolved;
    complex_type_impl->complex_type.ops->get_content_model =
        xml_schema_complex_type_get_content_model;
    complex_type_impl->complex_type.ops->set_content_model =
        xml_schema_complex_type_set_content_model;
    complex_type_impl->complex_type.ops->get_content_type =
        xml_schema_complex_type_get_content_type;
    complex_type_impl->complex_type.ops->set_content_type =
        xml_schema_complex_type_set_content_type;
    complex_type_impl->complex_type.ops->get_content_type_particle =
        xml_schema_complex_type_get_content_type_particle;
    complex_type_impl->complex_type.ops->is_abstract =
        xml_schema_complex_type_is_abstract;
    complex_type_impl->complex_type.ops->set_abstract =
        xml_schema_complex_type_set_abstract;
    complex_type_impl->complex_type.ops->is_mixed =
        xml_schema_complex_type_is_mixed;
    complex_type_impl->complex_type.ops->set_mixed =
        xml_schema_complex_type_set_mixed;
    complex_type_impl->complex_type.ops->get_particle =
        xml_schema_complex_type_get_particle;
    complex_type_impl->complex_type.ops->set_particle =
        xml_schema_complex_type_set_particle;
    complex_type_impl->complex_type.ops->to_string =
        xml_schema_complex_type_to_string;

    complex_type_impl->ht_super = axis2_hash_make(env);

    if (!complex_type_impl->ht_super)
    {
        xml_schema_complex_type_free(&(complex_type_impl->complex_type), env);
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    axis2_hash_set(complex_type_impl->ht_super, "XML_SCHEMA_COMPLEX_TYPE",
            AXIS2_HASH_KEY_STRING, &(complex_type_impl->complex_type));
    axis2_hash_set(complex_type_impl->ht_super, "XML_SCHEMA_TYPE",
            AXIS2_HASH_KEY_STRING, complex_type_impl->schema_type);

    annotated =
        XML_SCHEMA_TYPE_GET_BASE_IMPL(complex_type_impl->schema_type, env);
    if (annotated)
    {
        axis2_hash_set(complex_type_impl->ht_super, "XML_SCHEMA_ANNOTATED",
                AXIS2_HASH_KEY_STRING, annotated);
        axis2_hash_set(complex_type_impl->ht_super, "XML_SCHEMA_OBJ",
                AXIS2_HASH_KEY_STRING,
                XML_SCHEMA_ANNOTATED_GET_BASE_IMPL(annotated, env));
    }

    axis2_hash_set(complex_type_impl->ht_super, "XML_SCHEMA_COMPLEX_TYPE",
            AXIS2_HASH_KEY_STRING, &(complex_type_impl->complex_type));

    xml_schema_type_resolve_methods(&(complex_type_impl->complex_type.base), env,
            complex_type_impl->schema_type,
            xml_schema_complex_type_super_objs,
            xml_schema_complex_type_get_type,
            xml_schema_complex_type_free);

    return &(complex_type_impl->complex_type);
}

axis2_status_t AXIS2_CALL
xml_schema_complex_type_free(void *complex_type,
        const axis2_env_t *env)
{
    xml_schema_complex_type_impl_t *complex_type_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    complex_type_impl = AXIS2_INTF_TO_IMPL(complex_type);

    if (complex_type_impl->schema_type)
    {
        XML_SCHEMA_TYPE_FREE(complex_type_impl->schema_type, env);
        complex_type_impl->schema_type = NULL;
    }
    if (complex_type_impl->complex_type.base.ops)
    {
        AXIS2_FREE(env->allocator, complex_type_impl->complex_type.base.ops);
        complex_type_impl->complex_type.base.ops = NULL;
    }

    if (complex_type_impl->complex_type.ops)
    {
        AXIS2_FREE(env->allocator, complex_type_impl->complex_type.ops);
        complex_type_impl->complex_type.ops = NULL;
    }
    AXIS2_FREE(env->allocator, complex_type_impl);
    complex_type_impl = NULL;
    return AXIS2_SUCCESS;
}

xml_schema_type_t *AXIS2_CALL
xml_schema_complex_type_get_base_impl(
    void *complex_type,
    const axis2_env_t *env)
{
    xml_schema_complex_type_impl_t *complex_type_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    complex_type_impl = AXIS2_INTF_TO_IMPL(complex_type);
    return complex_type_impl->schema_type;

}

xml_schema_any_attribute_t* AXIS2_CALL
xml_schema_complex_type_get_any_attribute(
    void *cmp_type,
    const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(cmp_type)->any_attr;
}

axis2_status_t  AXIS2_CALL
xml_schema_complex_type_set_any_attribute(
    void *cmp_type,
    const axis2_env_t *env,
    xml_schema_any_attribute_t *any_attr)
{
    xml_schema_complex_type_impl_t *cmp_type_impl = NULL;

    cmp_type_impl = AXIS2_INTF_TO_IMPL(cmp_type);
    if (cmp_type_impl->any_attr)
    {
        /** TODO free attribute */
    }
    cmp_type_impl->any_attr = any_attr;
    return AXIS2_SUCCESS;
}

xml_schema_obj_collection_t* AXIS2_CALL
xml_schema_complex_type_get_attributes(
    void *cmp_type,
    const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(cmp_type)->attributes;
}

xml_schema_obj_table_t* AXIS2_CALL
xml_schema_complex_type_get_attribute_use(
    void *cmp_type,
    const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(cmp_type)->attr_uses;
}

xml_schema_any_attribute_t* AXIS2_CALL
xml_schema_complex_type_get_attribute_wildcard(
    void *cmp_type,
    const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(cmp_type)->attr_wildcard;
}

xml_schema_derivation_method_t* AXIS2_CALL
xml_schema_complex_type_get_block(
    void *cmp_type,
    const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(cmp_type)->block;
}

axis2_status_t AXIS2_CALL
xml_schema_complex_type_set_block(
    void *cmp_type,
    const axis2_env_t *env,
    xml_schema_derivation_method_t *block)
{
    xml_schema_complex_type_impl_t *cmp_type_impl = NULL;
    cmp_type_impl = AXIS2_INTF_TO_IMPL(cmp_type);
    if (cmp_type_impl->block)
    {
        /** TODO free block */
    }

    cmp_type_impl->block = block;
    return AXIS2_SUCCESS;
}

xml_schema_derivation_method_t* AXIS2_CALL
xml_schema_complex_type_get_block_resolved(
    void *cmp_type,
    const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(cmp_type)->block_resolved;

}

void* AXIS2_CALL
xml_schema_complex_type_get_content_model(
    void *cmp_type,
    const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(cmp_type)->content_model;

}

axis2_status_t AXIS2_CALL
xml_schema_complex_type_set_content_model(
    void *cmp_type,
    const axis2_env_t *env,
    void *content_model)
{
    xml_schema_complex_type_impl_t *cmp_type_impl = NULL;
    cmp_type_impl = AXIS2_INTF_TO_IMPL(cmp_type);

    if (cmp_type_impl->content_model)
    {
        /** TODO free content_model_type */
    }
    AXIS2_INTF_TO_IMPL(cmp_type)->content_model = content_model;
    return AXIS2_SUCCESS;
}

xml_schema_content_type_t* AXIS2_CALL
xml_schema_complex_type_get_content_type(
    void *cmp_type,
    const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(cmp_type)->content_type;
}

axis2_status_t AXIS2_CALL
xml_schema_complex_type_set_content_type(
    void *cmp_type,
    const axis2_env_t *env,
    xml_schema_content_type_t *content_type)
{
    xml_schema_complex_type_impl_t *cmp_type_impl = NULL;

    cmp_type_impl = AXIS2_INTF_TO_IMPL(cmp_type);
    if (cmp_type_impl->content_type)
    {
        /** TODO free */
    }
    cmp_type_impl->content_type = content_type;
    return AXIS2_SUCCESS;
}

xml_schema_particle_t * AXIS2_CALL
xml_schema_complex_type_get_content_type_particle(
    void *cmp_type,
    const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(cmp_type)->particle_type;
}

axis2_bool_t AXIS2_CALL
xml_schema_complex_type_is_abstract(
    void *cmp_type,
    const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(cmp_type)->is_abstract;
}

axis2_status_t AXIS2_CALL
xml_schema_complex_type_set_abstract(
    void *cmp_type,
    const axis2_env_t *env,
    axis2_bool_t b)
{
    AXIS2_INTF_TO_IMPL(cmp_type)->is_abstract = b;
    return AXIS2_SUCCESS;
}

axis2_bool_t AXIS2_CALL
xml_schema_complex_type_is_mixed(
    void *cmp_type,
    const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(cmp_type)->is_mixed;
}

axis2_status_t AXIS2_CALL
xml_schema_complex_type_set_mixed(
    void *cmp_type,
    const axis2_env_t *env,
    axis2_bool_t b)
{
    AXIS2_INTF_TO_IMPL(cmp_type)->is_mixed = b;
    return AXIS2_SUCCESS;
}

void* AXIS2_CALL
xml_schema_complex_type_get_particle(
    void *cmp_type,
    const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(cmp_type)->particle;
}

axis2_status_t AXIS2_CALL
xml_schema_complex_type_set_particle(
    void *cmp_type,
    const axis2_env_t *env,
    void *particle)
{
    xml_schema_complex_type_impl_t *cmp_type_impl = NULL;
    cmp_type_impl = AXIS2_INTF_TO_IMPL(cmp_type);
    if (cmp_type_impl->particle)
    {
        /** TODO free particle */
    }
    cmp_type_impl->particle = particle;
    return AXIS2_SUCCESS;
}



axis2_char_t* AXIS2_CALL
xml_schema_complex_type_to_string(
    void *complex_type,
    const axis2_env_t *env,
    axis2_char_t *prefix,
    int tab)
{
    xml_schema_complex_type_impl_t *complex_type_impl = NULL;
    AXIS2_ENV_CHECK(env, NULL);
    complex_type_impl = AXIS2_INTF_TO_IMPL(complex_type);
    /** TODO implement the method */
    return NULL;
}

xml_schema_types_t AXIS2_CALL
xml_schema_complex_type_get_type(
    void *complex_type,
    const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(complex_type)->obj_type;
}

axis2_hash_t* AXIS2_CALL
xml_schema_complex_type_super_objs(
    void *complex_type,
    const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(complex_type)->ht_super;
}