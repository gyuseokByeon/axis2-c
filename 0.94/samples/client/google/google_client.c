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

#include <stdio.h>
#include <axiom.h>
#include <axis2_util.h>
#include <axiom_soap.h>
#include <axis2_client.h>

axiom_node_t *
build_soap_body_content(const axis2_env_t *env,
        const axis2_char_t *operation,
        const axis2_char_t *google_key,
        const axis2_char_t *word_to_spell);

void print_invalid_om(const axis2_env_t *env, axiom_node_t *ret_node);

int main(int argc, char** argv)
{
    const axis2_env_t *env = NULL;
    const axis2_char_t *address = NULL;
    axis2_endpoint_ref_t* endpoint_ref = NULL;
    axis2_options_t *options = NULL;
    const axis2_char_t *client_home = NULL;
    axis2_svc_client_t* svc_client = NULL;
    axiom_node_t *payload = NULL;
    axiom_node_t *ret_node = NULL;

    const axis2_char_t *google_key = NULL;
    const axis2_char_t *word_to_spell = NULL;
    const axis2_char_t *operation = NULL;

    operation = "doSpellingSuggestion";
    google_key = "00000000000000000000000000000000";
    word_to_spell = "salvasion";

    /* Set up the environment */
    env = axis2_env_create_all("google_client.log", AXIS2_LOG_LEVEL_TRACE);

    /* Set end point reference of google service */
    address = "http://api.google.com/search/beta2";

    if ((argc > 1) && (AXIS2_STRCMP("-h", argv[1]) == 0))
    {
        printf("\nUsage : %s [google_key] [word_to_spell] \n", argv[0]);
        printf("\tgoogle_key Your Google license key. Default value won't work. You must use your key here.\n");
        printf("\tword_to_spell Word to be spelled by Google service. Default is %s\n", word_to_spell);
        printf("NOTE: command line arguments must appear in given order, with trailing ones being optional\n");
        printf("\tUse -h for help\n");
        return 0;
    }

    if (argc > 1)
        google_key = argv[1];
    if (argc > 2)
        word_to_spell = argv[2];

    printf("Using endpoint : %s\n", address);
    printf("\nInvoking operation %s with params %s and %s\n", operation, google_key, word_to_spell);

    /* Create EPR with given address */
    endpoint_ref = axis2_endpoint_ref_create(env, address);

    /* Setup options */
    options = axis2_options_create(env);
    AXIS2_OPTIONS_SET_TO(options, env, endpoint_ref);
    AXIS2_OPTIONS_SET_SOAP_VERSION(options, env, AXIOM_SOAP11);

    /* Set up deploy folder.*/
    client_home = AXIS2_GETENV("AXIS2C_HOME");
    if (!client_home)
        client_home = "../../deploy";

    /* Create service client */
    svc_client = axis2_svc_client_create(env, client_home);
    if (!svc_client)
    {
        printf("Error creating service client\n");
        AXIS2_LOG_ERROR(env->log, AXIS2_LOG_SI, "Stub invoke FAILED: Error code:"
                " %d :: %s", env->error->error_number,
                AXIS2_ERROR_GET_MESSAGE(env->error));
    }

    /* Set service client options */
    AXIS2_SVC_CLIENT_SET_OPTIONS(svc_client, env, options);

    /* Build the SOAP request message payload using OM API.*/
    payload = build_soap_body_content(env, operation, google_key, word_to_spell);

    /* Send request */
    ret_node = AXIS2_SVC_CLIENT_SEND_RECEIVE(svc_client, env, payload);

    if (ret_node)
    {
        if (AXIOM_NODE_GET_NODE_TYPE(ret_node, env) == AXIOM_ELEMENT)
        {
            axis2_char_t *result = NULL;
            axiom_element_t *result_ele = NULL;
            axiom_node_t *ret_node1 = NULL;

            result_ele = (axiom_element_t*)AXIOM_NODE_GET_DATA_ELEMENT(ret_node, env);
            if (AXIS2_STRCMP(AXIOM_ELEMENT_GET_LOCALNAME(result_ele, env), "doSpellingSuggestionResponse") != 0)
            {
                print_invalid_om(env, ret_node);
                return AXIS2_FAILURE;
            }

            ret_node1 = AXIOM_NODE_GET_FIRST_CHILD(ret_node, env); /*return*/
            if (!ret_node1)
            {
                print_invalid_om(env, ret_node);
                return AXIS2_FAILURE;
            }
            result_ele = (axiom_element_t*)AXIOM_NODE_GET_DATA_ELEMENT(ret_node1, env);
            result = AXIOM_ELEMENT_GET_TEXT(result_ele, env, ret_node1);
            printf("\nResult = %s\n", result);
        }
        else
        {
            print_invalid_om(env, ret_node);
            return AXIS2_FAILURE;
        }
    }
    else
    {
        AXIS2_LOG_ERROR(env->log, AXIS2_LOG_SI, "Stub invoke FAILED: Error code:"
                " %d :: %s", env->error->error_number,
                AXIS2_ERROR_GET_MESSAGE(env->error));
        printf("Google client invoke FAILED!\n");
    }

    if (svc_client)
    {
        AXIS2_SVC_CLIENT_FREE(svc_client, env);
        svc_client = NULL;
    }

    return 0;
}

axiom_node_t *
build_soap_body_content(const axis2_env_t *env,
        const axis2_char_t *operation,
        const axis2_char_t *google_key,
        const axis2_char_t *word_to_spell)
{
    axiom_node_t *google_om_node = NULL;
    axiom_element_t* google_om_ele = NULL;
    axiom_node_t* text_om_node = NULL;
    axiom_element_t * text_om_ele = NULL;
    axiom_namespace_t *ns0 = NULL, *ns1 = NULL, *ns2 = NULL, *ns3 = NULL;
    axiom_attribute_t* attri1 = NULL;
    axis2_char_t *buffer = NULL;

    ns0 = axiom_namespace_create(env, AXIOM_SOAP11_SOAP_ENVELOPE_NAMESPACE_URI, "soapenv");
    ns1 = axiom_namespace_create(env, "urn:GoogleSearch", "ns1");
    ns2 = axiom_namespace_create(env, "http://www.w3.org/1999/XMLSchema-instance", "xsi");
    ns3 = axiom_namespace_create(env, "http://www.w3.org/1999/XMLSchema", "xsd");

    attri1 = axiom_attribute_create(env, "encodingStyle",
            "http://schemas.xmlsoap.org/soap/encoding/", ns0);

    google_om_ele = axiom_element_create(env, NULL, operation, ns1, &google_om_node);
    AXIOM_ELEMENT_ADD_ATTRIBUTE(google_om_ele, env, attri1, google_om_node);
    AXIOM_ELEMENT_DECLARE_NAMESPACE(google_om_ele, env, google_om_node, ns2);
    AXIOM_ELEMENT_DECLARE_NAMESPACE(google_om_ele, env, google_om_node, ns3);

    text_om_ele = axiom_element_create(env, google_om_node, "key", NULL, &text_om_node);
    attri1 = axiom_attribute_create(env, "type", "xsd:string", ns2);
    AXIOM_ELEMENT_ADD_ATTRIBUTE(text_om_ele, env, attri1, text_om_node);
    AXIOM_ELEMENT_SET_TEXT(text_om_ele, env, google_key, text_om_node);

    text_om_ele = axiom_element_create(env, google_om_node, "phrase", NULL, &text_om_node);
    AXIOM_ELEMENT_ADD_ATTRIBUTE(text_om_ele, env, attri1, text_om_node);
    AXIOM_ELEMENT_SET_TEXT(text_om_ele, env, word_to_spell, text_om_node);

    buffer = AXIOM_NODE_TO_STRING(google_om_node, env);
    printf("%s\n", buffer);
    return google_om_node;
}

void print_invalid_om(const axis2_env_t *env, axiom_node_t *ret_node)
{
    axis2_char_t *buffer = NULL;
    buffer = AXIOM_NODE_TO_STRING(ret_node, env);
    printf("\nReceived OM as result : %s\n", buffer);
}