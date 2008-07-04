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
#include "add.h"
#include <stdio.h>
#include <axis2_svc_grp_ctx.h>

axiom_node_t *
axis2_add_add(const axis2_env_t *env, axiom_node_t *node, axis2_msg_ctx_t *msg_ctx)
{
    axiom_node_t *param1_node = NULL;
    axiom_node_t *param1_text_node = NULL;
    axis2_char_t *param1_str = NULL;
    long int param1 = 0;
    axiom_node_t *param2_node = NULL;
    axiom_node_t *param2_text_node = NULL;
    axis2_char_t *param2_str = NULL;
    long int param2 = 0;

    if (!node)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_SVC_SKEL_INPUT_OM_NODE_NULL, AXIS2_FAILURE);
        printf("Math client request ERROR: input parameter NULL\n");
        return NULL;
    }

    param1_node = AXIOM_NODE_GET_FIRST_CHILD(node, env);
    if (!param1_node)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_SVC_SKEL_INVALID_XML_FORMAT_IN_REQUEST, AXIS2_FAILURE);
        printf("Math service  ERROR: invalid XML in request\n");
        return NULL;
    }

    param1_text_node = AXIOM_NODE_GET_FIRST_CHILD(param1_node, env);
    if (!param1_text_node)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_SVC_SKEL_INVALID_XML_FORMAT_IN_REQUEST, AXIS2_FAILURE);
        printf("Math service ERROR: invalid XML in request\n");
        return NULL;
    }

    if (AXIOM_NODE_GET_NODE_TYPE(param1_text_node, env) == AXIOM_TEXT)
    {
        axiom_text_t *text = (axiom_text_t *)AXIOM_NODE_GET_DATA_ELEMENT(param1_text_node, env);
        if (text && AXIOM_TEXT_GET_VALUE(text , env))
        {
            param1_str = AXIOM_TEXT_GET_VALUE(text, env);
        }
    }
    else
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_SVC_SKEL_INVALID_XML_FORMAT_IN_REQUEST, AXIS2_FAILURE);
        printf("Math service ERROR: invalid XML in request\n");
        return NULL;
    }

    param2_node = AXIOM_NODE_GET_NEXT_SIBLING(param1_node, env);
    if (!param2_node)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_SVC_SKEL_INVALID_XML_FORMAT_IN_REQUEST, AXIS2_FAILURE);
        printf("Math service  ERROR: invalid XML in request\n");
        return NULL;
    }

    param2_text_node = AXIOM_NODE_GET_FIRST_CHILD(param2_node, env);
    if (!param2_text_node)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_SVC_SKEL_INVALID_XML_FORMAT_IN_REQUEST, AXIS2_FAILURE);
        printf("Math service ERROR: invalid XML in request\n");
        return NULL;
    }

    if (AXIOM_NODE_GET_NODE_TYPE(param2_text_node, env) == AXIOM_TEXT)
    {
        axiom_text_t *text = (axiom_text_t *)AXIOM_NODE_GET_DATA_ELEMENT(param2_text_node, env);
        if (text && AXIOM_TEXT_GET_VALUE(text , env))
        {
            param2_str = AXIOM_TEXT_GET_VALUE(text, env);
        }
    }
    else
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_SVC_SKEL_INVALID_XML_FORMAT_IN_REQUEST, AXIS2_FAILURE);
        printf("Math service ERROR: invalid XML in request\n");
        return NULL;
    }

    if (param1_str && param2_str)
    {
        long int result = 0;
        axis2_char_t result_str[255];

        axiom_element_t *ele1 = NULL;
        axiom_node_t *node1 = NULL, *node2 = NULL;
        axiom_namespace_t *ns1 = NULL;
        axiom_text_t *text1 = NULL;

        axis2_svc_grp_ctx_t *svc_grp_ctx = NULL;

        param1 = strtol(param1_str, NULL, 10);
        param2 = strtol(param2_str, NULL, 10);
        result = param1 + param2;
        sprintf(result_str, "%ld", result);



        ns1 = axiom_namespace_create(env,
                "http://axis2/test/namespace1",
                "ns1");
        ele1 = axiom_element_create(env, NULL, "result", ns1, &node1);
        text1 = axiom_text_create(env, node1, result_str, &node2);

        /* Put the result into service group context */
        svc_grp_ctx = AXIS2_MSG_CTX_GET_SVC_GRP_CTX(msg_ctx, env);
        if (svc_grp_ctx)
        {
            axis2_ctx_t* ctx = NULL;
            ctx = AXIS2_SVC_GRP_CTX_GET_BASE(svc_grp_ctx, env);
            if (ctx)
            {
                axis2_property_t* prop = NULL;
                /* get value */
                prop = AXIS2_CTX_GET_PROPERTY(ctx, env, "ADD_RESULT", AXIS2_FALSE);
                if (prop)
                {
                    axis2_char_t *val = (axis2_char_t*)AXIS2_PROPERTY_GET_VALUE(prop, env);
                    printf("Previous result = %s\n", val);
                }
                /* set value */
                prop = axis2_property_create(env);
                if (prop)
                {
                    AXIS2_PROPERTY_SET_VALUE(prop, env, AXIS2_STRDUP(result_str, env));
                    AXIS2_CTX_SET_PROPERTY(ctx, env, "ADD_RESULT", prop, AXIS2_FALSE);
                }
            }
        }


        return node1;
    }

    AXIS2_ERROR_SET(env->error, AXIS2_ERROR_SVC_SKEL_INVALID_OPERATION_PARAMETERS_IN_SOAP_REQUEST, AXIS2_FAILURE);
    printf("Math service ERROR: invalid parameters\n");
    return NULL;
}

