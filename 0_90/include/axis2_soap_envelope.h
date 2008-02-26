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
 
 #ifndef AXIS2_SOAP_ENVELOPE_H
 #define AXIS2_SOAP_ENVELOPE_H
 
/**
 * @file axis2_soap_envelope.h
 * @brief axis2_soap_envelope struct
 *        corresponds to root element of soap message
 */
#include <axis2_env.h>
#include <axis2_om_node.h>
#include <axis2_om_element.h>
#include <axis2_om_namespace.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct axis2_soap_envelope        axis2_soap_envelope_t;
    typedef struct axis2_soap_envelope_ops    axis2_soap_envelope_ops_t;
    
    struct axis2_soap_body;
    struct axis2_soap_header;
    struct axis2_soap_header_block;
    struct axis2_soap_builder;
    
/**
 * @defgroup axis2_soap_envelope
 * @ingroup axis2_soap
 * @{
 */

/**
 *   \brief soap_envelope operations struct
 *   ops Encapsulator struct of axis2_soap body
 */
 AXIS2_DECLARE_DATA   struct axis2_soap_envelope_ops
    {
        /**
         * gets the soap header of this soap envelope
         * @param envelope soap envelope
         * @param env environment must not be null
         * @return soap header null it no header is present
         */
        struct axis2_soap_header* (AXIS2_CALL *
		get_header)(axis2_soap_envelope_t *envelope,
                    axis2_env_t **env);
        /**
         * Returns the soap body associated with this soap envelope
         * @param envelope soap_envelope
         * @param env environment
         * @return soap_body
         */
        struct axis2_soap_body* (AXIS2_CALL *
		get_body)(axis2_soap_envelope_t *envelope,
                  axis2_env_t **env);
        /**
         * serialize function , serialize the soap envelope 
         * IF the soap version it set to soap11 the soap fault part is converted 
         * to soap11 fault even is the underlying soap fault is of soap12 type
         * @param envelope soap envelope
         * @param env environment must not be null
         * @param om_output 
         * @param cache whether caching is enabled or not
         * @return status code , AXIS2_SUCCESS if success ,
         *                 AXIS2_FAILURE otherwise
         */
        axis2_status_t (AXIS2_CALL *
		serialize)(axis2_soap_envelope_t *envelope,
                   axis2_env_t **env,
                   axis2_om_output_t *om_output, 
                   axis2_bool_t cache);
		
        /**
         * Free function, This function deallocate all the resources associated 
         * with the soap_envelope
         * IT frees it's soap body and soap headers as well as the underlying
         * om node tree by calling AXIS2_OM_NODE_FREE_TREE function
         * @param envelope soap_envelope
         * @param env environment
         * @return status code AXIS2_SUCCESS on success , AXIS2_FAILURE otherwise
         */         
        axis2_status_t (AXIS2_CALL *
		free)(axis2_soap_envelope_t *envelope,
              axis2_env_t **env);
			  
        /**
         * returns the om_node associated with this soap envelope
         * @param envelope soap_envelope
         * @param env environment
         * @return axis2_om_node_t pointer
         */
        axis2_om_node_t* (AXIS2_CALL *
		get_base_node)(axis2_soap_envelope_t *envelope,
                       axis2_env_t **env);

           
        /** returns the soap version of this soap envelope
         * @param envelope soap_envelope
         * @param env environment must not be null
         * @return soap_version AXIS2_SOAP12 or AXIS2_SOAP11
         */         
        int (AXIS2_CALL *
		get_soap_version)(axis2_soap_envelope_t *envelope,
                          axis2_env_t **env);
                   
        /**
         * set soap version, This is internal function do not use outside of soap
         */         
        axis2_status_t (AXIS2_CALL *
		set_soap_version)(axis2_soap_envelope_t *envelope,
                          axis2_env_t **env,
                          int soap_version);
     
        /** return the soap envelope namespace 
         * @param envelope 
         * @param env 
         * @return axis2_om_namespace_t 
         */                                                
        axis2_om_namespace_t* (AXIS2_CALL *
		get_namespace)(axis2_soap_envelope_t *envelope,
                       axis2_env_t **env);
     
    };

/**
 * \brief soap_envelope struct
 * represent a soap_envelope
 */
struct axis2_soap_envelope
{
  /** operation of axis2_soap_envelope struct */
  axis2_soap_envelope_ops_t *ops;
};

 /**
  * creates a soap envelope struct with empty values 
  * Indended to be uaed by soap_builder
  * @param env Environment. MUST NOT be NULL
  */
AXIS2_DECLARE(axis2_soap_envelope_t*)
axis2_soap_envelope_create(axis2_env_t **env, 
						   axis2_om_namespace_t *ns);

AXIS2_DECLARE(axis2_soap_envelope_t *)
axis2_soap_envelope_create_default_soap_envelope(axis2_env_t **env,
                                                 int soap_version);
 
AXIS2_DECLARE(axis2_soap_envelope_t *)
axis2_soap_envelope_create_default_soap_fault_envelope(axis2_env_t **env,
		    axis2_char_t *code_value, axis2_char_t *reason_text, int soap_version);

/******************** Macros **************************************************/

#define AXIS2_SOAP_ENVELOPE_GET_HEADER(envelope, env) \
        ((envelope)->ops->get_header(envelope, env))

#define AXIS2_SOAP_ENVELOPE_GET_BODY(envelope, env) \
        ((envelope)->ops->get_body(envelope, env))

#define AXIS2_SOAP_ENVELOPE_SERIALIZE(envelope, env, om_output, cache) \
        ((envelope)->ops->serialize(envelope, env, om_output, cache))
        
#define AXIS2_SOAP_ENVELOPE_FREE(envelope, env) \
        ((envelope)->ops->free(envelope, env))
        
#define AXIS2_SOAP_ENVELOPE_GET_BASE_NODE(envelope, env) \
        ((envelope)->ops->get_base_node(envelope, env))

#define AXIS2_SOAP_ENVELOPE_GET_SOAP_VERSION(envelope, env) \
        ((envelope)->ops->get_soap_version(envelope, env))

#define AXIS2_SOAP_ENVELOPE_SET_SOAP_VERSION(envelope, env, soap_version) \
        ((envelope)->ops->set_soap_version(envelope, env, soap_version))

#define AXIS2_SOAP_ENVELOPE_GET_NAMESPACE(envelope, env) \
        ((envelope)->ops->get_namespace(envelope, env))

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* AXIS2_SOAP_ENVELOPE_H */