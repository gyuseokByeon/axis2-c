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
 
 #ifndef AXIOM_SOAP_FAULT_REASON_H
 #define AXIOM_SOAP_FAULT_REASON_H
 
     /**
    * @file axiom_soap_fault_reason.h
    * @brief axiom_soap_fault_reason 
    */
#include <axis2_env.h>
#include <axiom_soap_fault.h>
#include <axis2_array_list.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct axiom_soap_fault_reason_ops axiom_soap_fault_reason_ops_t;
typedef struct axiom_soap_fault_reason axiom_soap_fault_reason_t;
struct axiom_soap_fault_text;
struct axiom_soap_builder;
/**
 * @defgroup axiom_soap_fault_reason soap fault reason
 * @ingroup axiom_soap
 * @{
 */

/**
 *   \brief soap_fault_reason operations struct
 *   ops Encapsulator struct of axiom_soap_fault_reason
 */
    struct axiom_soap_fault_reason_ops
    {
      /**
        * Free an axiom_soap_fault_reason
        * @param  fault_reason pointer to soap_fault_reason struct
        * @param  env Environment. MUST NOT be NULL
        * @return satus of the op. AXIS2_SUCCESS on success 
        *         else AXIS2_FAILURE
        */

        axis2_status_t (AXIS2_CALL *
      free_fn)(axiom_soap_fault_reason_t *fault_reason,
                 const axis2_env_t *env);

        struct axiom_soap_fault_text* (AXIS2_CALL *
      get_soap_fault_text)(axiom_soap_fault_reason_t *fault_reason,
                             const axis2_env_t *env,
                             axis2_char_t *lang);
                             
        axis2_array_list_t* (AXIS2_CALL *
        get_all_soap_fault_texts)(axiom_soap_fault_reason_t *fault_reason,
                                  const axis2_env_t *env);
                                  
        struct axiom_soap_fault_text* (AXIS2_CALL *
        get_first_soap_fault_text)(axiom_soap_fault_reason_t *fault_reason,
                                   const axis2_env_t *env);
                             
        axis2_status_t (AXIS2_CALL *
        add_soap_fault_text)(axiom_soap_fault_reason_t *fault_reason,
                             const axis2_env_t *env,
                             struct axiom_soap_fault_text *fault_text);
                                           
        axiom_node_t* (AXIS2_CALL *
      get_base_node)(axiom_soap_fault_reason_t *fault_reason,
                       const axis2_env_t *env);
                                 
    };      

  /**
    * \brief soap_fault_reason struct
    * represent a soap_fault_reason
    */
    struct axiom_soap_fault_reason
    {
        /** operation of axiom_soap_fault_reason struct */
        axiom_soap_fault_reason_ops_t *ops;
       
    };

  /**
    * creates a soap struct 
    * @param env Environment. MUST NOT be NULL
    */
    
    
AXIS2_EXTERN axiom_soap_fault_reason_t * AXIS2_CALL
axiom_soap_fault_reason_create_with_parent(const axis2_env_t *env,
                            axiom_soap_fault_t *fault);

/******************** Macros **************************************************/
    
/** free soap_fault_reason */
#define AXIOM_SOAP_FAULT_REASON_FREE(fault_reason , env) \
        ((fault_reason)->ops->free_fn(fault_reason, env))

        
#define AXIOM_SOAP_FAULT_REASON_GET_SOAP_FAULT_TEXT(fault_reason , env, lang) \
        ((fault_reason)->ops->get_soap_fault_text(fault_reason, env, lang)) 
        
#define AXIOM_SOAP_FAULT_REASON_GET_BASE_NODE(fault_reason, env) \
        ((fault_reason)->ops->get_base_node(fault_reason, env))    
        
#define AXIOM_SOAP_FAULT_REASON_ADD_SOAP_FAULT_TEXT(fault_reason, env, fault_text) \
        ((fault_reason)->ops->add_soap_fault_text(fault_reason, env, fault_text))             
        
#define AXIOM_SOAP_FAULT_REASON_GET_ALL_SOAP_FAULT_TEXTS(fault_reason, env) \
        ((fault_reason)->ops->get_all_soap_fault_texts(fault_reason, env))
        
#define AXIOM_SOAP_FAULT_REASON_GET_FIRST_SOAP_FAULT_TEXT(fault_reason, env) \
        ((fault_reason)->ops->get_first_soap_fault_text(fault_reason, env))
        
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* AXIOM_SOAP_FAULT_REASON_H */
