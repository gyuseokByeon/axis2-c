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

#ifndef AXIS2_MSG_RECV_H
#define AXIS2_MSG_RECV_H


/**
  * @file axis2_msg_recv.h
  * @brief axis Message Receiver interface
  */

#include <axis2_core.h>
#include <axis2_param.h>
#include <axis2_msg_ctx.h>
#include <axis2_op_ctx.h>
#include <axis2.h>
#include <axis2_svc_skeleton.h>

#ifdef __cplusplus
extern "C"
{
#endif
    
/** @defgroup axis2_msg_recv Message Receiver
  * @ingroup axis2_core_engine
  * @{
  */
    
struct axis2_msg_ctx;
typedef struct axis2_msg_recv axis2_msg_recv_t;
typedef struct axis2_msg_recv_ops axis2_msg_recv_ops_t;

/** 
 * @brief Message Receiver ops struct
 * Encapsulator struct for ops of axis2_msg_recv
 */     
struct axis2_msg_recv_ops
{
    /** 
     * Deallocate memory
     * @return status code
     */
    axis2_status_t (AXIS2_CALL *free) (axis2_msg_recv_t *msg_recv,
                                        axis2_env_t **env);

    axis2_status_t (AXIS2_CALL *receive) (axis2_msg_recv_t *msg_recv,
                                            axis2_env_t **env,
                                            struct axis2_msg_ctx *msg_ctx);
    axis2_status_t (AXIS2_CALL *invoke_in_business_logic) (axis2_msg_recv_t *msg_recv,
                                            axis2_env_t **env,
                                            struct axis2_msg_ctx *in_msg_ctx);
    axis2_status_t (AXIS2_CALL *invoke_in_out_business_logic) (axis2_msg_recv_t *msg_recv,
                                            axis2_env_t **env,
                                            struct axis2_msg_ctx *in_msg_ctx,
                                            struct axis2_msg_ctx *out_msg_ctx);
    axis2_status_t (AXIS2_CALL *set_in_only)(axis2_msg_recv_t *msg_recv,
                                                axis2_env_t **env,
                                                axis2_bool_t in_only);
                                            
    /**
     * Method makeNewServiceObject
     *
     * @param msgContext
     * @return
     */
    axis2_svc_skeleton_t * (AXIS2_CALL *
    make_new_svc_obj) (void *msg_recv,
                        axis2_env_t **env,
                        struct axis2_msg_ctx *msg_ctx);
    
    /**
     * Method getTheImplementationObject
     *
     * @param msgContext
     * @return
     */
    axis2_svc_skeleton_t * (AXIS2_CALL *
    get_impl_obj) (void *msg_recv,
                    axis2_env_t **env,
                    struct axis2_msg_ctx *msg_ctx); 

    axis2_status_t (AXIS2_CALL *
    set_scope) (axis2_msg_recv_t *msg_recv,
                                axis2_env_t **env,
                                axis2_char_t *scope);
    
    axis2_char_t * (AXIS2_CALL *
    get_scope) (axis2_msg_recv_t *msg_recv,
                                axis2_env_t **env);                                      
};

/** 
 * @brief Message Receiver struct
  *	Axis2 Message Receiver
 */
struct axis2_msg_recv
{
    axis2_msg_recv_ops_t *ops;    
};

AXIS2_DECLARE(axis2_msg_recv_t *)
axis2_msg_recv_create (axis2_env_t **env);

/************************** Start of function macros **************************/

#define AXIS2_MSG_RECV_FREE(msg_recv, env) ((msg_recv)->ops->free (msg_recv, env))

#define AXIS2_MSG_RECV_RECEIVE(msg_recv, env, msg_ctx) \
		((msg_recv)->ops->receive (msg_recv, env, msg_ctx))

#define AXIS2_MSG_RECV_SET_IN_ONLY(msg_recv, env, in_only) \
		((msg_recv)->ops->set_in_only(msg_recv, env, in_only))

#define AXIS2_MSG_RECV_INVOKE_IN_BUSINESS_LOGIC(msg_recv, env, in_msg_ctx) \
		((msg_recv)->ops->invoke_in_business_logic(msg_recv, env, in_msg_ctx))

#define AXIS2_MSG_RECV_INVOKE_IN_OUT_BUSINESS_LOGIC(msg_recv, env, in_msg_ctx, \
        out_msg_ctx) ((msg_recv)->ops->invoke_in_out_business_logic(msg_recv, \
            env, in_msg_ctx, out_msg_ctx))

#define AXIS2_MSG_RECV_MAKE_NEW_SVC_OBJ(msg_recv, env, msg_ctx) \
		((msg_recv)->ops->make_new_svc_obj(msg_recv, env, msg_ctx))

#define AXIS2_MSG_RECV_GET_IMPL_OBJ(msg_recv, env, msg_ctx) \
		((msg_recv)->ops->get_impl_obj(msg_recv, env, msg_ctx))
        
#define AXIS2_MSG_RECV_SET_SCOPE(msg_recv, env, scope) \
		((msg_recv)->ops->set_scope(msg_recv, env, scope))

#define AXIS2_MSG_RECV_GET_SCOPE(msg_recv, env) \
		((msg_recv)->ops->get_scope(msg_recv, env))


/************************** End of function macros ****************************/
    
/** @} */
#ifdef __cplusplus
}
#endif

#endif                          /* AXIS2_MSG_RECV_H */
