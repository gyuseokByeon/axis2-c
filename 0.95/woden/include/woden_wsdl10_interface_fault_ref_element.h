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

#ifndef WODEN_WSDL10_INTERFACE_FAULT_REF_ELEMENT_H
#define WODEN_WSDL10_INTERFACE_FAULT_REF_ELEMENT_H

/**
 * @file woden_wsdl10_interface_fault_ref_element.h
 * @brief Axis2 Interface Msg Reference Element Interface
 * This interface represents the &lt;input&gt; and &lt;output&gt; 
 * child elements of interface operation. 
 */

#include <axis2_allocator.h>
#include <axis2_env.h>
#include <axis2_error.h>
#include <axis2_string.h>
#include <axis2_utils.h>
#include <axis2_hash.h>
#include <axis2_qname.h>
#include <axis2_uri.h>
#include <axis2_array_list.h>
#include <woden.h>
#include <woden_documentable_element.h>
#include <woden_configurable_element.h>
#include <woden_nested_element.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct woden_wsdl10_interface_fault_ref_element woden_wsdl10_interface_fault_ref_element_t;
typedef struct woden_wsdl10_interface_fault_ref_element_ops woden_wsdl10_interface_fault_ref_element_ops_t;
typedef union woden_wsdl10_interface_fault_ref_element_base woden_wsdl10_interface_fault_ref_element_base_t;

/** @defgroup woden_wsdl10_interface_fault_ref_element Interface Msg Reference Element
  * @ingroup axis2_interface
  * @{
  */

struct woden_wsdl10_interface_fault_ref_element_ops
{
   /** 
     * Deallocate memory
     * @return status code
     */
    axis2_status_t (AXIS2_CALL *
    free) (
            void *interface_fault_ref_element,
            const axis2_env_t *env);
 
    woden_obj_types_t (AXIS2_CALL *
    type) (
            void *interface_fault_ref_element,
            const axis2_env_t *env);
    
    axis2_status_t (AXIS2_CALL *
    set_qname) (
            void *iface_fault_ele,
            const axis2_env_t *env,
            axis2_qname_t *qname);

    axis2_qname_t *(AXIS2_CALL *
    get_qname) (
            void *iface_fault_ele,
            const axis2_env_t *env);
    
    axis2_status_t (AXIS2_CALL *
    set_msg_qname) (
            void *iface_fault_ele,
            const axis2_env_t *env,
            axis2_qname_t *element);

    axis2_qname_t *(AXIS2_CALL *
    get_msg_qname) (
            void *iface_fault_ele,
            const axis2_env_t *env);
    
    axis2_status_t (AXIS2_CALL *
    set_direction) (
            void *iface_fault_ele,
            const axis2_env_t *env,
            void *dir);

    void *(AXIS2_CALL *
    get_direction) (
            void *iface_fault_ele,
            const axis2_env_t *env);
    

};

union woden_wsdl10_interface_fault_ref_element_base
{
    woden_documentable_element_t documentable_element;
    woden_configurable_element_t configurable_element;
    woden_nested_element_t nested_element;
};

struct woden_wsdl10_interface_fault_ref_element
{
    woden_wsdl10_interface_fault_ref_element_base_t base;
    woden_wsdl10_interface_fault_ref_element_ops_t *ops;
};

AXIS2_EXTERN woden_wsdl10_interface_fault_ref_element_t * AXIS2_CALL
woden_wsdl10_interface_fault_ref_element_create(
        const axis2_env_t *env);

/************************Woden C Internal Methods******************************/
AXIS2_EXTERN axis2_status_t AXIS2_CALL
woden_wsdl10_interface_fault_ref_element_resolve_methods(
        woden_wsdl10_interface_fault_ref_element_t *interface_fault_ref_element,
        const axis2_env_t *env,
        axis2_hash_t *methods);
/************************End of Woden C Internal Methods***********************/

#define WODEN_WSDL10_INTERFACE_FAULT_REF_ELEMENT_FREE(interface_fault_ref_element, env) \
      (((woden_wsdl10_interface_fault_ref_element_t *) interface_fault_ref_element)->ops->\
         free (interface_fault_ref_element, env))

#define WODEN_WSDL10_INTERFACE_FAULT_REF_ELEMENT_TYPE(interface_fault_ref_element, env) \
      (((woden_wsdl10_interface_fault_ref_element_t *) interface_fault_ref_element)->ops->\
         type (interface_fault_ref_element, env))

#define WODEN_WSDL10_INTERFACE_FAULT_REF_ELEMENT_SET_QNAME(interface_fault_ref_element, env, qname) \
      (((woden_wsdl10_interface_fault_ref_element_t *) interface_fault_ref_element)->ops->\
        set_qname  (interface_fault_ref_element, env, qname))

#define WODEN_WSDL10_INTERFACE_FAULT_REF_ELEMENT_GET_QNAME(interface_fault_ref_element, env) \
      (((woden_wsdl10_interface_fault_ref_element_t *) interface_fault_ref_element)->ops->\
        get_qname  (interface_fault_ref_element, env))

#define WODEN_WSDL10_INTERFACE_FAULT_REF_ELEMENT_SET_MSG_QNAME(interface_fault_ref_element, env, element) \
      (((woden_wsdl10_interface_fault_ref_element_t *) interface_fault_ref_element)->ops->\
        set_msg_qname  (interface_fault_ref_element, env, element))

#define WODEN_WSDL10_INTERFACE_FAULT_REF_ELEMENT_GET_MSG_QNAME(interface_fault_ref_element, env) \
      (((woden_wsdl10_interface_fault_ref_element_t *) interface_fault_ref_element)->ops->\
        get_msg_qname  (interface_fault_ref_element, env))

#define WODEN_WSDL10_INTERFACE_FAULT_REF_ELEMENT_SET_DIRECTION(interface_fault_ref_element, env, dir) \
      (((woden_wsdl10_interface_fault_ref_element_t *) interface_fault_ref_element)->ops->\
         set_direction (interface_fault_ref_element, env, dir))

#define WODEN_WSDL10_INTERFACE_FAULT_REF_ELEMENT_GET_DIRECTION(interface_fault_ref_element, env) \
      (((woden_wsdl10_interface_fault_ref_element_t *) interface_fault_ref_element)->ops->\
         get_direction (interface_fault_ref_element, env))




/** @} */
#ifdef __cplusplus
}
#endif
#endif /* WODEN_WSDL10_INTERFACE_FAULT_REF_ELEMENT_H */