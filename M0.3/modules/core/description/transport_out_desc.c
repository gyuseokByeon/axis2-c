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
 
#include <axis2_transport_out_desc.h>
    
/** 
 * @brief Description transport out struct impl
 * Transport out
 * Represents a incoming transport deployed in AXis2
 */ 
typedef struct axis2_transport_out_desc_impl
{
	axis2_transport_out_desc_t transport_out;
    
    /** 
     * Field flowInclude 
     * This will have a shallow copy and will not be freed by the descructor
     */
    struct axis2_flow *outflow;
    
    /** 
     * Field flowInclude 
     * This will have a shallow copy and will not be freed by the descructor
     */
    struct axis2_flow *faultflow;
        
    /** 
     * Field name
     * This will have a shallow copy and will not be freed by the descructor
     */
    axis2_qname_t *qname;
    
    /**
     * This will have a shallow copy and will not be freed by the descructor
     */
    struct axis2_transport_sender *sender;
    
    /** to store handler in inFlow */
    struct axis2_phase *out_phase;
        
    /** to store handler Fault in inFlow */
    struct axis2_phase *faultphase;
    
    
} axis2_transport_out_desc_impl_t;

#define AXIS2_INTF_TO_IMPL(transport_out) ((axis2_transport_out_desc_impl_t *)transport_out)

/************************* Function prototypes ********************************/

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_free (
                axis2_transport_out_desc_t *transport_out,
				axis2_env_t **env);

axis2_qname_t *AXIS2_CALL
axis2_transport_out_desc_get_qname(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env);

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_qname(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env,
                                        axis2_qname_t *qname);

struct axis2_flow *AXIS2_CALL
axis2_transport_out_desc_get_outflow(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env);

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_outflow(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env,
                                        struct axis2_flow *outflow);

struct axis2_flow *AXIS2_CALL
axis2_transport_out_desc_get_faultflow(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env);

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_faultflow(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env,
                                        struct axis2_flow *faultflow);

struct axis2_transport_sender * AXIS2_CALL
axis2_transport_out_desc_get_sender(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env);

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_sender(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env,
                                        struct axis2_transport_sender *sender);

struct axis2_phase * AXIS2_CALL
axis2_transport_out_desc_get_out_phase(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env);

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_out_phase(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env,
                                        struct axis2_phase *out_phase);
                                            
struct axis2_phase *AXIS2_CALL
axis2_transport_out_desc_get_faultphase(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env);

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_faultphase(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env,
                                        struct axis2_phase *faultphase);


/************************** End of function prototypes ************************/

axis2_transport_out_desc_t * AXIS2_CALL 
axis2_transport_out_desc_create_with_qname (axis2_env_t **env, axis2_qname_t *qname)
{
    axis2_transport_out_desc_impl_t *transport_out_impl = NULL;
     
	AXIS2_ENV_CHECK(env, NULL);
    AXIS2_PARAM_CHECK((*env)->error, qname, NULL);
	
	transport_out_impl = (axis2_transport_out_desc_impl_t *) AXIS2_MALLOC((*env)->
        allocator, sizeof(axis2_transport_out_desc_impl_t));
	
	if(NULL == transport_out_impl)
    {
        AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE); 
        return NULL;
    }
    
    transport_out_impl->qname = NULL;
    transport_out_impl->out_phase = NULL;
    transport_out_impl->faultphase = NULL;
    transport_out_impl->outflow = NULL;
    transport_out_impl->faultflow = NULL;
    transport_out_impl->sender = NULL;
    transport_out_impl->transport_out.ops = NULL;
    transport_out_impl->transport_out.param_container = NULL;
    
    transport_out_impl->transport_out.param_container = axis2_param_container_create(env);
    if(NULL == transport_out_impl->transport_out.param_container)
    {
        axis2_transport_out_desc_free(&(transport_out_impl->transport_out), env);
        AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    
    transport_out_impl->qname = qname;
    
	transport_out_impl->transport_out.ops = 
		AXIS2_MALLOC ((*env)->allocator, sizeof(axis2_transport_out_desc_ops_t));
	if(NULL == transport_out_impl->transport_out.ops)
    {
        axis2_transport_out_desc_free(&(transport_out_impl->transport_out), env);
		AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    
    transport_out_impl->transport_out.ops->free = axis2_transport_out_desc_free;
    
	transport_out_impl->transport_out.ops->get_qname =  
        axis2_transport_out_desc_get_qname;
	transport_out_impl->transport_out.ops->set_qname =  
        axis2_transport_out_desc_set_qname;
	transport_out_impl->transport_out.ops->get_outflow =  
        axis2_transport_out_desc_get_outflow;
	transport_out_impl->transport_out.ops->set_outflow = 
        axis2_transport_out_desc_set_outflow;
    transport_out_impl->transport_out.ops->get_faultflow = 
        axis2_transport_out_desc_get_faultflow;
    transport_out_impl->transport_out.ops->set_faultflow = 
        axis2_transport_out_desc_set_faultflow;
    transport_out_impl->transport_out.ops->get_sender = 
        axis2_transport_out_desc_get_sender;
    transport_out_impl->transport_out.ops->set_sender = 
        axis2_transport_out_desc_set_sender;
    transport_out_impl->transport_out.ops->get_out_phase = 
        axis2_transport_out_desc_get_out_phase;
    transport_out_impl->transport_out.ops->set_out_phase = 
        axis2_transport_out_desc_set_out_phase;
    transport_out_impl->transport_out.ops->get_faultphase = 
        axis2_transport_out_desc_get_faultphase;
    transport_out_impl->transport_out.ops->set_faultphase = 
        axis2_transport_out_desc_set_faultphase;
    
	return &(transport_out_impl->transport_out);
}

/***************************Function implementation****************************/

axis2_status_t AXIS2_CALL 
axis2_transport_out_desc_free (axis2_transport_out_desc_t *transport_out, 
                            axis2_env_t **env)
{
    axis2_transport_out_desc_impl_t *transport_out_impl = NULL;
    
    AXIS2_FUNC_PARAM_CHECK(transport_out, env, AXIS2_FAILURE);
    
    transport_out_impl = AXIS2_INTF_TO_IMPL(transport_out);
    
	if(NULL != transport_out->ops)
    {
        AXIS2_FREE((*env)->allocator, transport_out->ops);
        transport_out->ops = NULL;
    }
    
    if(NULL != transport_out_impl->transport_out.param_container)
    {
        AXIS2_PARAM_CONTAINER_FREE(transport_out_impl->transport_out.param_container, env);
        transport_out_impl->transport_out.param_container = NULL;
    }
    
    if(NULL != transport_out_impl->qname)
    {
        AXIS2_QNAME_FREE(transport_out_impl->qname, env);
        transport_out_impl->qname = NULL;
    }
    
    if(transport_out_impl->outflow)
    {   
        AXIS2_FLOW_FREE(transport_out_impl->outflow, env);        
        transport_out_impl->outflow = NULL;
    }
    
    if(transport_out_impl->faultflow)
    {   
        AXIS2_FLOW_FREE(transport_out_impl->faultflow, env);        
        transport_out_impl->faultflow = NULL;
    }
    
    if(transport_out_impl->out_phase)
    {   
        AXIS2_FLOW_FREE(transport_out_impl->out_phase, env);        
        transport_out_impl->out_phase = NULL;
    }
    
    if(transport_out_impl->faultphase)
    {   
        AXIS2_FLOW_FREE(transport_out_impl->faultphase, env);        
        transport_out_impl->faultphase = NULL;
    }
    
    transport_out_impl->sender = NULL;
    
    AXIS2_FREE((*env)->allocator, transport_out_impl);
    
	return AXIS2_SUCCESS;
}

axis2_qname_t *AXIS2_CALL
axis2_transport_out_desc_get_qname(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env) 
{
    AXIS2_FUNC_PARAM_CHECK(transport_out, env, NULL);
    return AXIS2_INTF_TO_IMPL(transport_out)->qname;
}

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_qname(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env,
                                        axis2_qname_t *qname) 
{
    axis2_transport_out_desc_impl_t *transport_out_impl = AXIS2_INTF_TO_IMPL(transport_out);
    AXIS2_FUNC_PARAM_CHECK(transport_out, env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, qname, AXIS2_FAILURE);
    
    if(transport_out_impl->qname)
    {
        AXIS2_PHASE_FREE(transport_out_impl->qname, env);
        transport_out_impl->qname = NULL;
    }
    transport_out_impl->qname = qname;
    return AXIS2_SUCCESS;
}

struct axis2_flow *AXIS2_CALL
axis2_transport_out_desc_get_outflow(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env) 
{
    AXIS2_FUNC_PARAM_CHECK(transport_out, env, NULL);
    return AXIS2_INTF_TO_IMPL(transport_out)->outflow;
}

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_outflow(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env,
                                        struct axis2_flow *outflow) 
{
    axis2_transport_out_desc_impl_t *transport_out_impl = NULL;
    AXIS2_FUNC_PARAM_CHECK(transport_out, env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, outflow, AXIS2_FAILURE);
    
    transport_out_impl = AXIS2_INTF_TO_IMPL(transport_out);
    if(transport_out_impl->outflow)
    {
        AXIS2_FLOW_FREE(transport_out_impl->outflow, env);
        transport_out_impl->outflow = NULL;
    }
    transport_out_impl->outflow = outflow;
    return AXIS2_SUCCESS;
}

struct axis2_flow *AXIS2_CALL
axis2_transport_out_desc_get_faultflow(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env) 
{
    return AXIS2_INTF_TO_IMPL(transport_out)->faultflow;
}

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_faultflow(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env,
                                        struct axis2_flow *faultflow) 
{
    axis2_transport_out_desc_impl_t *transport_out_impl = NULL;
    AXIS2_FUNC_PARAM_CHECK(transport_out, env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, faultflow, AXIS2_FAILURE);
    
    transport_out_impl = AXIS2_INTF_TO_IMPL(transport_out);
    if(transport_out_impl->faultflow)
    {
        AXIS2_FLOW_FREE(transport_out_impl->faultflow, env);
        transport_out_impl->faultflow = NULL;
    }
    transport_out_impl->faultflow = faultflow;
    return AXIS2_SUCCESS;
}

struct axis2_transport_sender * AXIS2_CALL
axis2_transport_out_desc_get_sender(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env) 
{
    AXIS2_FUNC_PARAM_CHECK(transport_out, env, NULL);
    return AXIS2_INTF_TO_IMPL(transport_out)->sender;
}

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_sender(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env,
                                        struct axis2_transport_sender *sender) 
{
    axis2_transport_out_desc_impl_t *transport_out_impl = NULL;
    AXIS2_FUNC_PARAM_CHECK(transport_out, env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, sender, AXIS2_FAILURE);
    
    transport_out_impl = AXIS2_INTF_TO_IMPL(transport_out);

    transport_out_impl->sender = sender;
    return AXIS2_SUCCESS;
}

struct axis2_phase * AXIS2_CALL
axis2_transport_out_desc_get_out_phase(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env) 
{
    AXIS2_FUNC_PARAM_CHECK(transport_out, env, NULL);
    
    return AXIS2_INTF_TO_IMPL(transport_out)->out_phase;
}

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_out_phase(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env,
                                        struct axis2_phase *out_phase) 
{
    axis2_transport_out_desc_impl_t *transport_out_impl = NULL;
    
    AXIS2_FUNC_PARAM_CHECK(transport_out, env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, out_phase, AXIS2_FAILURE);
    
    transport_out_impl = AXIS2_INTF_TO_IMPL(transport_out);
    if(transport_out_impl->out_phase)
    {
        AXIS2_FLOW_FREE(transport_out_impl->out_phase, env);
        transport_out_impl->out_phase = NULL;
    }
    transport_out_impl->out_phase = out_phase;
    return AXIS2_SUCCESS;
}

struct axis2_phase *AXIS2_CALL
axis2_transport_out_desc_get_faultphase(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env) 
{
    AXIS2_FUNC_PARAM_CHECK(transport_out, env, NULL);
    
    return AXIS2_INTF_TO_IMPL(transport_out)->faultphase;
}

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_faultphase(struct axis2_transport_out_desc *transport_out,
                                        axis2_env_t **env,
                                        struct axis2_phase *faultphase) 
{
    axis2_transport_out_desc_impl_t *transport_out_impl = NULL;
    
    AXIS2_FUNC_PARAM_CHECK(transport_out, env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, faultphase, AXIS2_FAILURE);
    
    transport_out_impl = AXIS2_INTF_TO_IMPL(transport_out);
    if(transport_out_impl->faultphase)
    {
        AXIS2_FLOW_FREE(transport_out_impl->faultphase, env);
        transport_out_impl->faultphase = NULL;
    }
    transport_out_impl->faultphase = faultphase;
    return AXIS2_SUCCESS;
    
}