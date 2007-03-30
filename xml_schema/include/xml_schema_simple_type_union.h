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

#ifndef XML_SCHEMA_SIMPLE_TYPE_UNION_H
#define XML_SCHEMA_SIMPLE_TYPE_UNION_H

/**
 * @file xml_schema_simple_type_union.h
 * @brief Axis2 Xml Schema Particle Interface
 *          Base class for all simple_type_union types.
 */


#include <xml_schema_simple_type.h>
#include <xml_schema_simple_type_content.h>
#include <xml_schema_obj_collection.h>
#include <axis2_hash.h>
#include <axutil_array_list.h>
/** @defgroup xml_schema_simple_type_union 
  * @ingroup xml_schema
  * @{
  */
#ifdef __cplusplus
extern "C"
{
#endif

typedef struct xml_schema_simple_type_union 
                    xml_schema_simple_type_union_t;
typedef struct xml_schema_simple_type_union_ops 
                    xml_schema_simple_type_union_ops_t;

struct xml_schema_simple_type_union_ops
{
    axis2_status_t (AXIS2_CALL *
    free)(void *sim_type_union, const axutil_env_t *env);

    xml_schema_simple_type_content_t *(AXIS2_CALL *
    get_base_impl)(
            void *sim_type_union,
            const axutil_env_t *env);
                    
    axis2_hash_t*(AXIS2_CALL *
    super_objs)(
            void *sim_type_union,
            const axutil_env_t *env);                    
    
    xml_schema_types_t (AXIS2_CALL *
    get_type)(
            void *sim_type_union,
            const axutil_env_t *env);

    xml_schema_obj_collection_t*(AXIS2_CALL *
    get_base_types)(
            void *sim_type_union,
            const axutil_env_t *env);
    
    axis2_status_t (AXIS2_CALL *
    set_member_types_source)(
            void *sim_type_union,
            const axutil_env_t *env,
            axis2_char_t *member_types_source);
    
    axis2_char_t* (AXIS2_CALL *
    get_member_types_source)(
            void *sim_type_union,
            const axutil_env_t *env);
                    
    axutil_array_list_t* (AXIS2_CALL *
    get_member_types_qnames)(
            void *sim_type_union,
            const axutil_env_t *env);
                
    axis2_status_t (AXIS2_CALL *
    set_member_types_qnames)(
            void *sim_type_union,
            const axutil_env_t *env,
            axutil_array_list_t *qns);                
                
};

struct xml_schema_simple_type_union
{
    xml_schema_simple_type_content_t base;
    xml_schema_simple_type_union_ops_t *ops;
};

/**
 * Creates new Xml Schema Particle
 * Particle types are usually interchangeable.
 * A local element declaration or reference to a global element
 * declaration (element), a compositor ( sequence, choice, or all),
 * a reference to a named content model group (group), or an element wildcard 
 * (any).
 */
AXIS2_EXTERN xml_schema_simple_type_union_t * AXIS2_CALL
xml_schema_simple_type_union_create(const axutil_env_t *env);

#define XML_SCHEMA_SIMPLE_TYPE_UNION_FREE(sim_type_union, env) \
      (((xml_schema_simple_type_union_t *) sim_type_union)->ops->\
            free(sim_type_union, env))

#define XML_SCHEMA_SIMPLE_TYPE_UNION_GET_BASE_IMPL(sim_type_union, env) \
      (((xml_schema_simple_type_union_t *) sim_type_union)->ops->\
            get_base_impl(sim_type_union, env))

#define XML_SCHEMA_SIMPLE_TYPE_UNION_SUPER_OBJS(sim_type_union, env) \
      (((xml_schema_simple_type_union_t *) sim_type_union)->ops->\
            super_objs(sim_type_union, env))

#define XML_SCHEMA_SIMPLE_TYPE_UNION_GET_TYPE(sim_type_union, env) \
      (((xml_schema_simple_type_union_t *) sim_type_union)->ops->\
            get_type(sim_type_union, env))

#define XML_SCHEMA_SIMPLE_TYPE_UNION_GET_BASE_TYPES(sim_type_union, env) \
      (((xml_schema_simple_type_union_t *) sim_type_union)->ops->\
            get_base_types(sim_type_union, env))

#define XML_SCHEMA_SIMPLE_TYPE_UNION_SET_MEMBER_TYPES_SOURCE(sim_type_union,\
         env, member_types_sources) \
      (((xml_schema_simple_type_union_t *) sim_type_union)->ops->\
            set_member_types_source(sim_type_union, env, member_types_sources))

#define XML_SCHEMA_SIMPLE_TYPE_UNION_GET_MEMBER_TYPES_SOURCE(sim_type_union, env) \
      (((xml_schema_simple_type_union_t *) sim_type_union)->ops->\
            get_member_types_source(sim_type_union, env))

#define XML_SCHEMA_SIMPLE_TYPE_UNION_SET_MEMBER_TYPES_QNAMES(sim_type_union, env, qns) \
      (((xml_schema_simple_type_union_t *) sim_type_union)->ops->\
            set_member_types_qnames(sim_type_union, env, qns))

/** @} */
#ifdef __cplusplus
}
#endif
#endif /* XML_SCHEMA_SIMPLE_TYPE_UNION_H */
