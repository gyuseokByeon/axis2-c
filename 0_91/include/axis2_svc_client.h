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

#ifndef AXIS2_SVC_CLIENT_H
#define AXIS2_SVC_CLIENT_H


/**
  * @file axis2_svc_client.h
  * @brief axis2 Service Client interface
  */

#include <axis2_defines.h>
#include <axis2_env.h>
#include <axis2_svc.h>
#include <axis2_options.h>
#include <axis2_qname.h>
#include <axis2_om_element.h>
#include <axis2_callback.h>
#include <axis2_endpoint_ref.h>
#include <axis2_svc_ctx.h>
#include <axis2_conf_ctx.h>
#include <axis2_op_client.h>

#define AXIS2_ANON_SERVICE 				"__ANONYMOUS_SERVICE__"
#define AXIS2_ANON_OUT_ONLY_OP 			"__OPERATION_OUT_ONLY__"
#define AXIS2_ANON_ROBUST_OUT_ONLY_OP	"__OPERATION_ROBUST_OUT_ONLY__"
#define AXIS2_ANON_OUT_IN_OP			"__OPERATION_OUT_IN__"


#ifdef __cplusplus
extern "C"
{
#endif

/** @defgroup axis2_svc_client Service Client 
 * @ingroup axis2_core_clientapi
 * @{
 */
    
typedef struct axis2_svc_client_ops axis2_svc_client_ops_t;
typedef struct axis2_svc_client axis2_svc_client_t; 

    
/** 
 * @brief Service Client ops struct
 * Encapsulator struct for ops of axis2_svc_client
 */  
struct axis2_svc_client_ops
{
  /**
    * Returns the axis2_svc_t this is a client for. This is primarily useful
    * when the service is created anonymously or from WSDL.
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @return the axis service
    */
	axis2_svc_t* (AXIS2_CALL *
	get_svc)(
        struct axis2_svc_client *svc_client, 
        axis2_env_t **env);

  /**
    * Sets the options to be used by service client
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param options pointer to options struct to be set
    * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
    */
	axis2_status_t (AXIS2_CALL *
	set_options)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_options_t *options);	

  /**
    * Gets options used by service client
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @return a pointer to the options struct
    */
    axis2_options_t* (AXIS2_CALL *
	get_options)(
        struct axis2_svc_client *svc_client,
        axis2_env_t **env);

  /**
    * Sets the client options related to this service interaction to
    * override any options that the underlying operation client may have.
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param options pointer to options struct to be set
    * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
    */
	axis2_status_t (AXIS2_CALL *
	set_override_options)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_options_t *override_options);    

  /**
    * Gets the overriding options
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @return pointer to options struct 
    */
	axis2_options_t* (AXIS2_CALL *
	get_override_options)(
        struct axis2_svc_client *svc_client,
        axis2_env_t **env);    

  /**
    * Engages the named module
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param module_name name of the module to be engaged
    * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
    */
	axis2_status_t (AXIS2_CALL *
	engage_module)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_char_t *module_name);

  /**
    * Dis-engages the named module 
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param module_name name of the module to be dis-engaged
    * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
    */
	axis2_status_t (AXIS2_CALL *
	disengage_module)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_char_t *module_name);
	
  /**
    * Adds an XML element as a header to be sent to server side.
    * This allows users to go a bit beyond the simple XML in/out pattern, and 
    * send custom SOAP headers.
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param header om node representing the SOAP header in XML
    * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
    */
	axis2_status_t (AXIS2_CALL *
	add_header)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_om_node_t *header);

  /**
    * Removes all the headers added to service client
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
    */
	axis2_status_t (AXIS2_CALL *
	remove_headers)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env);

  /**
    * Adds a simple header consisting of some text to be sent with interactions.
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param header_name qname representing the header name
    * @param header_text text of the header
    * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
    */
	axis2_status_t (AXIS2_CALL *
	add_header_with_text)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_qname_t *header_name,
		axis2_char_t *header_text); 	

  /**
    * This is a simple client API to invoke a service operation who's MEP is
    * Robust In-Only. This API can be used to simply send a bit of XML.
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param payload pointer to OM node representing the XML payload to be sent
    * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
    */	
	axis2_status_t (AXIS2_CALL *
	send_robust)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_om_node_t *payload);

  /**
    * This is a simple client API to invoke a service operation who's MEP is
    * Robust In-Only. This API can be used to simply send a bit of XML.
    * The difference between this function and "send_robust" is that this
    * method has to be given the operation name as a qname, wehre as 
    * "send_robust" assumes the operation name to be 
    * "__OPERATION_ROBUST_OUT_ONLY__"
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param op_qname operation qname 
    * @param payload pointer to OM node representing the XML payload to be sent
    * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
    */	
    axis2_status_t (AXIS2_CALL *
	send_robust_with_op_qname)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_qname_t *op_qname,
		axis2_om_node_t *payload);
	
  /**
    * Sends a bit of XML and forget about it. This API is used to interact with
    * a service operation who's MEP is In-Only. That is, there is no
    * opportunity to get an error from the service via this API; one may still
    * get client-side errors, such as host unknown etc.
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param payload pointer to OM node representing the XML payload to be sent
    */
	void (AXIS2_CALL *
	fire_and_forget)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_om_node_t *payload);

  /**
    * Sends a bit of XML and forget about it. This API is used to interact with
    * a service operation who's MEP is In-Only. That is, there is no
    * opportunity to get an error from the service via this API; one may still
    * get client-side errors, such as host unknown etc.
    * The difference between this function and "fire_and_forget" is that this
    * method has to be given the operation name as a qname, wehre as 
    * "fire_and_forget" assumes the operation name to be 
    * "__OPERATION_OUT_ONLY__"
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param op_qname operation qname 
    * @param payload pointer to OM node representing the XML payload to be sent
    */
	void (AXIS2_CALL *
	fire_and_forget_with_op_qname)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_qname_t *op_qname,
		axis2_om_node_t *payload);

  /**
    * Sends XML request and receives XML response.
    * This API is used to interact with a service operation who's MEP is In-Out.
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param payload pointer to OM node representing the XML payload to be sent
    * @return pointer to OM node representing the XML response
    */
	axis2_om_node_t* (AXIS2_CALL *
	send_receive)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_om_node_t *payload);

  /**
    * Sends XML request and receives XML response.
    * This API is used to interact with a service operation who's MEP is In-Out.
    * The difference between this function and "send_receive" is that this
    * method has to be given the operation name as a qname, wehre as 
    * "send_receive" assumes the operation name to be 
    * "__OPERATION_OUT_IN__"
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param op_qname operation qname 
    * @param payload pointer to OM node representing the XML payload to be sent
    * @return pointer to OM node representing the XML response
    */
	axis2_om_node_t* (AXIS2_CALL *
	send_receive_with_op_qname)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_qname_t *op_qname,	
		axis2_om_node_t *payload);

  /**
    * Sends XML request and receives XML response, but do not block for response.
    * This API is used to interact with a service operation who's MEP is In-Out,
    * in a non blocking mode.
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param payload pointer to OM node representing the XML payload to be sent
    * @callback pointer to callback struct used to capture response 
    */
        
	void (AXIS2_CALL *
	send_receive_non_blocking)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_om_node_t *payload,
		axis2_callback_t *callback);

  /**
    * Sends XML request and receives XML response, but do not block for response.
    * This API is used to interact with a service operation who's MEP is In-Out,
    * in a non blocking mode.
    * The difference between this function and "send_receive_non_blocking" is that this
    * method has to be given the operation name as a qname, wehre as 
    * "send_receive_non_blocking" assumes the operation name to be 
    * "__OPERATION_OUT_IN__"
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param op_qname operation qname 
    * @param payload pointer to OM node representing the XML payload to be sent
    * @callback pointer to callback struct used to capture response 
    */
	void (AXIS2_CALL *
	send_receive_non_blocking_with_op_qname)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_qname_t *op_qname,
		axis2_om_node_t *payload,
		axis2_callback_t *callback);
	
  /**
    * Create an op_client for a specific operation. This is the way one can
    * create a full function MEP client which can be used to exchange messages
    * for this specific operation. 
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param op_qname axis2_qname_t of the operation
    * @return pointer to op_client configured to talk to the given operation
    */
	axis2_op_client_t* (AXIS2_CALL *
	create_op_client)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_qname_t *op_qname);

  /**
    * This will close the output stream and/or remove entry from waiting
    * queue of the transport Listener queue
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
    */
	axis2_status_t (AXIS2_CALL *
	finalize_invoke)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env);

  /**
    * Gets the from EPR 
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param transport name of the transport, e.g "http"
    * @return pointer to the epr struct
    */
    axis2_endpoint_ref_t* (AXIS2_CALL *
	get_my_epr)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_char_t *transport);				
		
  /**
    * Gets the target EPR 
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @return pointer to the epr struct
    */
	axis2_endpoint_ref_t* (AXIS2_CALL *
	get_target_epr)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env);

  /**
    * Sets the target EPR 
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @param target_epr pointer to the epr struct to be set as target
    * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
    */
	axis2_status_t (AXIS2_CALL *
	set_target_epr)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env,
		axis2_endpoint_ref_t *target_epr);		
        
  /**
    * Gets the service context
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @return pointer to service context struct
    */
	axis2_svc_ctx_t* (AXIS2_CALL *
	get_svc_ctx)(
        struct axis2_svc_client *svc_client,
	   	axis2_env_t **env);		

  /**
    * Frees the service client 
    * @param svc_client pointer to service client struct
    * @param env double pointer to environment struct. MUST NOT be NULL
    * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
    */

	axis2_status_t (AXIS2_CALL *
	free)(
        struct axis2_svc_client *svc_client,
		axis2_env_t **env);	
};

/** 
 * @brief Serivce Client struct
  *	Axis2 Service Client
 */
struct axis2_svc_client
{
    axis2_svc_client_ops_t *ops;    
};

AXIS2_DECLARE(axis2_svc_client_t*) 
axis2_svc_client_create(
    axis2_env_t **env, 
    axis2_char_t *client_home);

AXIS2_DECLARE(axis2_svc_client_t*) 
axis2_svc_client_create_with_conf_ctx_and_svc(
    axis2_env_t **env,
    axis2_conf_ctx_t *conf_ctx,
    axis2_svc_t *svc,
    axis2_char_t *client_home);
   
/************************** Start of function macros **************************/

#define AXIS2_SVC_CLIENT_GET_AXIS_SERVICE(svc_client) \
		((svc_client)->ops->get_svc(svc_client))

#define AXIS2_SVC_CLIENT_SET_OPTIONS(svc_client, env, options) \
		((svc_client)->ops->set_options(svc_client, env, options))

#define AXIS2_SVC_CLIENT_GET_OPTIONS(svc_client) \
		((svc_client)->ops->get_options(svc_client))

#define AXIS2_SVC_CLIENT_SET_OVERRIDE_OPTIONS(svc_client, env, override_options) \
		((svc_client)->ops->set_override_options(svc_client, env, override_options))

#define AXIS2_SVC_CLIENT_GET_OVERRIDE_OPTIONS(svc_client) \
	    ((svc_client)->ops->get_override_options(svc_client))

#define AXIS2_SVC_CLIENT_ENGAGE_MODULE(svc_client, env, module_name) \
		((svc_client)->ops->engage_module(svc_client, env, module_name))

#define AXIS2_SVC_CLIENT_DISENGAGE_MODULE(svc_client, env, module_name) \
		((svc_client)->ops->disengage_module(svc_client, env, module_name))

#define AXIS2_SVC_CLIENT_ADD_HEADER(svc_client, env, header) \
		((svc_client)->ops->add_header(svc_client, env, header))

#define AXIS2_SVC_CLIENT_REMOVE_HEADERS(svc_client, env) \
		((svc_client)->ops->remove_headers(svc_client, env))

#define AXIS2_SVC_CLIENT_ADD_HEADER_WITH_TEXT(svc_client, env, header_name, header_text) \
		((svc_client)->ops->add_header_with_text(svc_client, env, header_name, header_text))

#define AXIS2_SVC_CLIENT_SEND_ROBUST(svc_client, env, payload) \
		((svc_client)->ops->send_robust(svc_client, env, payload))

#define AXIS2_SVC_CLIENT_SEND_ROBUST_WITH_OP_QNAME(svc_client, env, op_qname, payload) \
		((svc_client)->ops->send_robust_with_op_qname(svc_client, env, op_qname, payload))

#define AXIS2_SVC_CLIENT_FIRE_AND_FORGET(svc_client, env, payload) \
		((svc_client)->ops->fire_and_forget(svc_client, env, payload))

#define AXIS2_SVC_CLIENT_FIRE_AND_FORGET_WITH_OP_QNAME(svc_client, env, op_qname, payload) \
		((svc_client)->ops->fire_and_forget_with_op_qname(svc_client, env, op_qname, payload))

#define AXIS2_SVC_CLIENT_SEND_RECEIVE(svc_client, env, payload) \
		((svc_client)->ops->send_receive(svc_client, env, payload))

#define AXIS2_SVC_CLIENT_SEND_RECEIVE_WITH_OP_QNAME(svc_client, env, op_qname, payload) \
		((svc_client)->ops->send_receive_with_op_qname(svc_client, env, op_qname, payload))

#define AXIS2_SVC_CLIENT_SEND_RECEIVE_NON_BLOCKING(svc_client, env, payload, callback) \
		((svc_client)->ops->send_receive_non_blocking(svc_client, env, payload, callback))

#define AXIS2_SVC_CLIENT_SEND_RECEIVE_NON_BLOCKING_WITH_OP_QNAME(svc_client, env, op_qname, payload, callback) \
		((svc_client)->ops->send_receive_non_blocking_with_op_qname(svc_client, env, op_qname, payload, callback))
	
#define AXIS2_SVC_CLIENT_CREATE_OP_CLIENT(svc_client, env, op_qname) \
		((svc_client)->ops->create_op_client(svc_client, env, op_qname))

#define AXIS2_SVC_CLIENT_FINALIZE_INVOKE(svc_client, env) \
		((svc_client)->ops->finalize_invoke(svc_client, env))

#define AXIS2_SVC_CLIENT_GET_MY_EPR(svc_client, env, transport) \
		((svc_client)->ops->get_my_epr(svc_client, env, transport))

#define AXIS2_SVC_CLIENT_GET_TARGET_EPR(svc_client, env) \
		((svc_client)->ops->get_target_epr(svc_client, env))

#define AXIS2_SVC_CLIENT_SET_TARGET_EPR(svc_client, env, target_epr) \
		((svc_client)->ops->set_target_epr(svc_client, env, target_epr))

#define AXIS2_SVC_CLIENT_GET_SERVICE_CONTEXT(svc_client, env) \
		((svc_client)->ops->get_svc_ctx(svc_client, env))


#define AXIS2_SVC_CLIENT_FREE(svc_client, env) \
		((svc_client)->ops->free(svc_client, env))

/************************** End of function macros ****************************/    

/** @} */
#ifdef __cplusplus
}
#endif

#endif                          /* AXIS2_SVC_CLIENT_H */