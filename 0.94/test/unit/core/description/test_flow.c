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

#include "test_flow.h"
#include <axis2_op.h>
#include <axis2_flow.h>
#include <axis2_phase.h>
#include <axis2_handler_desc.h>
#include <axis2_handler.h>
#include <axis2_phase_rule.h>
#include <stdio.h>
#include <string.h>



axis2_handler_desc_t *
test_flow_create_handler(const axis2_env_t *env)
{
    axis2_handler_desc_t *handler_desc = NULL;
    axis2_handler_t *handler = NULL;
    axis2_qname_t *qname = NULL;
    axis2_phase_rule_t *rule = NULL;

    printf("******************************************\n");
    printf("testing axis2_flow_create_handler  method \n");
    printf("******************************************\n");

    rule = axis2_phase_rule_create(env, AXIS2_PHASE_POLICY_DETERMINATION);
    AXIS2_PHASE_RULE_SET_BEFORE(rule, env, "before");
    AXIS2_PHASE_RULE_SET_AFTER(rule, env, "after");
    qname = axis2_qname_create(env, "handler1", NULL, NULL);
    handler_desc = axis2_handler_desc_create_with_qname(env, qname);
    AXIS2_QNAME_FREE(qname, env);
    AXIS2_HANDLER_DESC_SET_RULES(handler_desc, env, rule);
    handler = axis2_handler_create(env);
    AXIS2_HANDLER_INIT(handler, env, handler_desc);
    AXIS2_HANDLER_DESC_SET_HANDLER(handler_desc, env, handler);

    return handler_desc;
}

void Testaxis2_flow_add_handler(CuTest *tc)
{
    axis2_status_t actual = AXIS2_FAILURE;
    axis2_status_t expected = AXIS2_TRUE;
    axis2_flow_t *flow = NULL;
    axis2_handler_desc_t *handler_desc = NULL;

    printf("***************************************\n");
    printf("testing axis2_flow_add_handler  method \n");
    printf("***************************************\n");

    axis2_allocator_t *allocator = axis2_allocator_init(NULL);
    const axis2_env_t *env = axis2_env_create(allocator);

    flow = axis2_flow_create(env);
    handler_desc = test_flow_create_handler(env);
    actual = AXIS2_FLOW_ADD_HANDLER(flow, env, handler_desc);
    CuAssertIntEquals(tc, expected, actual);
    AXIS2_FLOW_FREE(flow,  env);

}

void Testaxis2_flow_free(CuTest *tc)
{
    axis2_status_t actual = AXIS2_FAILURE;
    axis2_status_t expected = AXIS2_TRUE;
    axis2_flow_t *flow = NULL;

    printf("********************************\n");
    printf("testing axis2_flow_free  method \n");
    printf("********************************\n");

    axis2_allocator_t *allocator = axis2_allocator_init(NULL);
    const axis2_env_t *env = axis2_env_create(allocator);

    flow = axis2_flow_create(env);
    actual = AXIS2_FLOW_FREE(flow,  env);

    CuAssertIntEquals(tc, expected, actual);

}
