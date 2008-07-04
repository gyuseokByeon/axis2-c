/*
 *Copyright 2004,2005 The Apache Software Foundation.
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
 
#include <rampart_handler_util.h>
#include <axis2_handler_desc.h>
#include <axis2_qname.h>
#include <axis2_svc.h>
#include <axiom_soap_header.h>
#include <axiom_soap_body.h>
#include <axiom_soap_header_block.h>
#include <axis2_endpoint_ref.h>
#include <axis2_property.h>
#include <rampart_constants.h>
#include <axis2_dll_desc.h>
#include <axis2_class_loader.h>
#include <axis2_conf_ctx.h>

axis2_char_t* AXIS2_CALL
rampart_get_property_from_ctx( const axis2_env_t *env,
    axis2_ctx_t *ctx,
    const axis2_char_t *key);

AXIS2_EXTERN axis2_param_t* AXIS2_CALL
rampart_get_security_param( const axis2_env_t *env,
                          axis2_msg_ctx_t *msg_ctx,
                          axis2_char_t *parameter);
                         
AXIS2_EXTERN axis2_array_list_t* AXIS2_CALL
rampart_get_actions( const axis2_env_t *env,
                                          axis2_ctx_t *ctx,
                                          axis2_param_t *param_x_flow_security);
                                            
AXIS2_EXTERN axis2_char_t* AXIS2_CALL
rampart_get_action_params( const axis2_env_t *env,
                   axis2_param_t *param_action,
                   const axis2_char_t *key);
                        
 AXIS2_EXTERN axiom_node_t *AXIS2_CALL
rampart_get_security_token(const axis2_env_t *env,
                                axis2_msg_ctx_t *msg_ctx,
                                axiom_soap_header_t *soap_header);


AXIS2_EXTERN void AXIS2_CALL
rampart_create_fault_envelope(const axis2_env_t *env,
        const axis2_char_t *header_name,
        const axis2_char_t *description,
        axis2_array_list_t *sub_codes,
        axis2_msg_ctx_t *msg_ctx);

/**********************end of header functions ****************************/

axis2_char_t* AXIS2_CALL
rampart_get_property_from_ctx( const axis2_env_t *env,
    axis2_ctx_t *ctx,
    const axis2_char_t *key)
{
   axis2_property_t* property = NULL;
   axis2_char_t* str_property = NULL;

    /*Get value from the dynamic settings*/

    property = AXIS2_CTX_GET_PROPERTY (ctx, env, key, AXIS2_FALSE);
    if(property)
    {
        str_property = AXIS2_PROPERTY_GET_VALUE(property,env);
        property = NULL;
    }

    if(str_property)
    {
       return str_property;
    }else{
       /* printf(" Cannot find dynamic settings for %s ", key);*/
    }

    return str_property;
}


axis2_param_t* AXIS2_CALL
rampart_get_security_param( const axis2_env_t *env,
                          axis2_msg_ctx_t *msg_ctx,
                          axis2_char_t *parameter)
{
  
  
        axis2_conf_ctx_t *conf_ctx = NULL;
        axis2_conf_t *conf = NULL;
        axis2_param_t *param= NULL;

         conf_ctx = AXIS2_MSG_CTX_GET_CONF_CTX(msg_ctx, env);
         if(NULL == conf_ctx)
          {
              return NULL;
          }
         conf = AXIS2_CONF_CTX_GET_CONF(conf_ctx, env);
         if(NULL == conf)
         {
           return NULL;
         }
         param= AXIS2_CONF_GET_PARAM(conf, env, parameter); 

         return param;
}


axis2_array_list_t *AXIS2_CALL
rampart_get_actions( const axis2_env_t *env,
        axis2_ctx_t *ctx,
        axis2_param_t *param_x_flow_security)
{
    axis2_array_list_t *action_list = NULL;
    int param_type;
    if(!param_x_flow_security)
    {
        AXIS2_LOG_INFO(env->log,"param_in_flow_security is NULL");
        return action_list;
    }
    
    /*ERROR HERE param returns TEXT even for DOM*/
    param_type = AXIS2_PARAM_GET_PARAM_TYPE(param_x_flow_security, env);

    action_list = AXIS2_PARAM_GET_VALUE_LIST(param_x_flow_security, env);
    if(!action_list)
    {
            AXIS2_LOG_INFO(env->log," action_list is NULL ... ERROR ");
    }
    return action_list;
}


axis2_char_t* AXIS2_CALL
rampart_get_action_params( const axis2_env_t *env,
                   axis2_param_t *param_action,
                   const axis2_char_t *key)
{
    axis2_char_t *value= NULL, *tmp_key = NULL;
    axis2_array_list_t *param_list = NULL;
    axis2_param_t *param = NULL;
    int param_type;
    axis2_char_t * param_name = NULL;
    int i, size = 0;
    if(!param_action)
    {
        printf("param_action is NULL");
    }
    
    param_type = AXIS2_PARAM_GET_PARAM_TYPE(param_action, env);
    param_name = AXIS2_PARAM_GET_NAME(param_action, env);
    
    param_list = AXIS2_PARAM_GET_VALUE_LIST(param_action, env);
    if(!param_list)
    {
        printf("param list is null");
    }
    
    size = AXIS2_ARRAY_LIST_SIZE(param_list, env);    
    for (i = 0; i < size; i = i + 1)
    {
        param = (axis2_param_t*) AXIS2_ARRAY_LIST_GET(param_list, env, i);
        if(param)
        {
           tmp_key = AXIS2_PARAM_GET_NAME(param, env);

           if(0 == AXIS2_STRCMP(tmp_key , key) ) 
            {
                value = AXIS2_PARAM_GET_VALUE(param, env);
                return value;
            }
        }
    }

    return value;
}

axiom_node_t *AXIS2_CALL
rampart_get_security_token(const axis2_env_t *env,
                                axis2_msg_ctx_t *msg_ctx,
                                axiom_soap_header_t *soap_header
                                )
{
    axis2_array_list_t *sec_headers = NULL;
    axis2_char_t *sec_ns_str = NULL;
    axis2_hash_index_t *hash_index =  NULL;
    axis2_hash_t *header_block_ht = NULL;
    axiom_element_t *header_block_ele = NULL;
    axiom_node_t *header_block_node = NULL;

    sec_headers = AXIOM_SOAP_HEADER_GET_HEADER_BLOCKS_WITH_NAMESPACE_URI(soap_header, env, RAMPART_WSSE_XMLNS);     
    if(sec_headers)
    {
        sec_ns_str = AXIS2_STRDUP(RAMPART_WSSE_XMLNS, env);

        header_block_ht = AXIOM_SOAP_HEADER_GET_ALL_HEADER_BLOCKS(soap_header, env);
        if(!header_block_ht)
          return AXIS2_FAILURE;    

        for(hash_index = axis2_hash_first(header_block_ht, env); hash_index;
            hash_index = axis2_hash_next(env, hash_index))
        {   

            void *hb = NULL;
            axiom_soap_header_block_t *header_block =    NULL;
            axis2_char_t *ele_localname = NULL;
            
            axis2_hash_this(hash_index, NULL, NULL, &hb);
            header_block = (axiom_soap_header_block_t *)hb;
            header_block_node = AXIOM_SOAP_HEADER_BLOCK_GET_BASE_NODE(header_block, env);
            header_block_ele  = (axiom_element_t*)AXIOM_NODE_GET_DATA_ELEMENT(header_block_node, env);
            ele_localname = AXIOM_ELEMENT_GET_LOCALNAME(header_block_ele, env);
    
            if(AXIS2_STRCMP(ele_localname, RAMPART_SECURITY) == 0)
            {
                return header_block_node;
            }
        
        }/*End of for*/
   }

    return header_block_node;

}



AXIS2_EXTERN void AXIS2_CALL
rampart_create_fault_envelope(const axis2_env_t *env,
        const axis2_char_t *header_name,
        const axis2_char_t *description,
        axis2_array_list_t *sub_codes,
        axis2_msg_ctx_t *msg_ctx)
{
    axiom_soap_envelope_t *envelope = NULL;
    int soap_version = AXIOM_SOAP12;
    axiom_node_t* text_om_node = NULL;
    axiom_element_t * text_om_ele = NULL;
    axiom_namespace_t *ns1 = NULL;

    ns1 = axiom_namespace_create (env, RAMPART_WSSE_XMLNS, RAMPART_WSSE);
    text_om_ele = axiom_element_create(env, NULL, "ProblemSecurityHeader", ns1, &text_om_node);
    AXIOM_ELEMENT_SET_TEXT(text_om_ele, env, header_name, text_om_node);

    envelope = axiom_soap_envelope_create_default_soap_fault_envelope(env,
            "soapenv:Sender",
            description,
            soap_version, sub_codes, text_om_node);
    
    AXIS2_MSG_CTX_SET_FAULT_SOAP_ENVELOPE(msg_ctx, env, envelope);
    return;
}


