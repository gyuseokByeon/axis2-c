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

#ifndef WODEN_BOOL_ATTR_H
#define WODEN_BOOL_ATTR_H

/**
 * @file woden_bool_attr.h
 * @brief Axis2 Boolean Attribute Interface
 *          This class represents XML attribute information items of type 
 *          xs:boolean. If the attribute value is not "true" or "false" 
 *          the Boolean content will be initialized to "false" by default, 
 *          but the isValid() method will return "false".
 */

#include <woden_xml_attr.h>
#include <woden.h>

/** @defgroup woden_bool_attr Boolean Attribute
  * @ingroup woden
  * @{
  */

typedef struct woden_bool_attr woden_bool_attr_t;
typedef struct woden_bool_attr_ops woden_bool_attr_ops_t;
struct axiom_element;
struct axiom_node;

#ifdef __cplusplus
extern "C"
{
#endif

struct woden_bool_attr_ops
{
   /** 
     * Deallocate memory
     * @return status code
     */
    axis2_status_t (AXIS2_CALL *
    free) (
            void *bool_attr,
            const axis2_env_t *env);
    
    axis2_status_t (AXIS2_CALL *
    to_bool_attr_free) (
            void *bool_attr,
            const axis2_env_t *env);
    
    woden_obj_types_t (AXIS2_CALL *
    type) (
            void *bool_attr,
            const axis2_env_t *env);

    /**
     * @return the base implementation class
     */
    woden_xml_attr_t *(AXIS2_CALL *
    get_base_impl) (
            void *bool_attr,
            const axis2_env_t *env);

    /* ************************************************************
     *  BooleanAttr interface declared methods 
     * ************************************************************/

    axis2_bool_t (AXIS2_CALL *
    get_boolean) (
            void *bool_attr,
            const axis2_env_t *env);

    /* ************************************************************
     *  Non-API implementation methods 
     * ************************************************************/

    /**
     * Convert a string of type xs:boolean to a axis2_bool_t.
     * An empty string or a null argument will initialize the Boolean to false.
     * Any conversion error will be reported and will initialize the Boolean to false.
     * If the attrValue does not match the Boolean value the Attr is marked invalid.
     */
    void *(AXIS2_CALL *
    convert) (
            void *bool_attr,
            const axis2_env_t *env,
            struct axiom_element *owner_el,
            struct axiom_node *owner_node,
            axis2_char_t *attr_value);

  
};

struct woden_bool_attr
{
    woden_xml_attr_t base;
    woden_bool_attr_ops_t *ops;
};

/*
 * TODO This constructor is not used for extension attributes, but may be useful if
 * parsing of native WSDL attributes is changed to use the axis2_xml_attr interface.
 */
AXIS2_EXTERN woden_bool_attr_t * AXIS2_CALL
woden_bool_attr_create(
        const axis2_env_t *env,
        struct axiom_element *owner_el,
        struct axiom_node *owner_node,
        axis2_qname_t *attr_type,
        axis2_char_t *attr_value);


/************************Woden C Internal Methods******************************/
AXIS2_EXTERN axis2_status_t AXIS2_CALL
woden_bool_attr_resolve_methods(
        woden_bool_attr_t *bool_attr,
        const axis2_env_t *env,
        axis2_hash_t *methods);
/************************End of Woden C Internal Methods***********************/

#define WODEN_BOOL_ATTR_FREE(bool_attr, env) \
      (((woden_bool_attr_t *) bool_attr)->ops->free(bool_attr, env))

#define WODEN_BOOL_ATTR_TO_BOOL_ATTR_FREE(bool_attr, env) \
      (((woden_bool_attr_t *) bool_attr)->ops->\
         to_bool_attr_free(bool_attr, env))

#define WODEN_BOOL_ATTR_TYPE(bool_attr, env) \
      (((woden_bool_attr_t *) bool_attr)->ops->\
         type(bool_attr, env))

#define WODEN_BOOL_ATTR_GET_BASE_IMPL(bool_attr, env) \
      (((woden_bool_attr_t *) bool_attr)->ops->\
         get_base_impl(bool_attr, env))

#define WODEN_BOOL_ATTR_GET_BOOL(bool_attr, env) \
      (((woden_bool_attr_t *) bool_attr)->ops->\
         get_boolean(bool_attr, env))

#define WODEN_BOOL_ATTR_CONVERT(bool_attr, env) \
      (((woden_bool_attr_t *) bool_attr)->ops->\
         convert(bool_attr, env))

/** @} */
#ifdef __cplusplus
}
#endif
#endif /* WODEN_BOOL_ATTR_H */