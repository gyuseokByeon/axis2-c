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

#include <axis2_om_stax_builder.h>
#include <axis2_om_document.h>
#include <axis2_om_node.h>
#include <axis2_om_element.h>
#include <axis2_om_text.h>
#include <axis2_stream.h>
#include <axis2_log_default.h>
#include <axis2_error_default.h>
#include <axis2_xml_reader.h>
#include <stdio.h>
#include <axis2_xml_writer.h>
#include <axis2_soap_builder.h>
#include <axis2_soap.h>
#include <axis2_soap_envelope.h>
#include <axis2_soap_body.h>
#include <axis2_soap_header.h>
#include <axis2_soap_message.h>
#include <axis2_soap_header_block.h>
#include <axis2_soap_fault.h>
#include <axis2_soap_fault_code.h>
#include <axis2_soap_fault_role.h>
#include <axis2_om_node.h>
#include <axis2_msg_ctx.h>
#include <axis2_call.h>
#include <ctype.h>
#include <string.h>

axis2_om_node_t *build_soap_body_content (axis2_env_t ** env,
                                          axis2_char_t * echo_operation,
                                          axis2_char_t * echo_type,
                                          axis2_char_t * word_to_echo,
                                          axis2_om_node_t * body_node);

void print_invalid_om (axis2_env_t ** env, axis2_om_node_t * ret_node);

int
main (int argc, char **argv)
{
    axis2_om_node_t *node = NULL;
    axis2_status_t status = AXIS2_FAILURE;
    axis2_env_t *env = NULL;
    axis2_error_t *error = NULL;
    axis2_log_t *log = NULL;
    axis2_allocator_t *allocator = NULL;
    axis2_char_t *address = NULL;
    axis2_char_t *client_home = NULL;
    axis2_om_node_t *ret_node = NULL;
    axis2_svc_t *svc = NULL;
    axis2_op_t *op = NULL;
    axis2_call_t *call = NULL;
    axis2_msg_ctx_t *msg_ctx = NULL;
    axis2_mep_client_t *mep_client = NULL;
    axis2_endpoint_ref_t *endpoint_ref = NULL;
    axis2_conf_t *conf = NULL;
    axis2_msg_ctx_t *response_ctx = NULL;
    axis2_soap_envelope_t *soap_envelope = NULL;
    axis2_soap_body_t *soap_body = NULL;
    axis2_om_namespace_t *env_ns = NULL;
    axis2_om_node_t *body_node = NULL;
    axis2_char_t *echo_operation = NULL;
    axis2_char_t *word_to_echo = NULL;
    axis2_char_t *echo_type = NULL;
    axis2_char_t operation[32];
    allocator = axis2_allocator_init (NULL);

    echo_operation = "String";
    word_to_echo = "helloworld";
    echo_type = "string";

    allocator = axis2_allocator_init (NULL);
    error = axis2_error_create (allocator);
    log = axis2_log_create (allocator, NULL, "test_client.log");
    env = axis2_env_create_with_error_log (allocator, error, log);
    env->log->level = AXIS2_LOG_LEVEL_INFO;
    axis2_error_init ();

    client_home = getenv ("AXIS2C_HOME");
    if (!client_home)
        client_home = "../../deploy";

    address = "http://easysoap.sourceforge.net/cgi-bin/interopserver";

    if ((argc > 1) && (AXIS2_STRCMP ("-h", argv[1]) == 0))
    {
        printf ("\nUsage : %s [echo_operation] [echo_value] [XSD_type]\n",
                argv[0]);
        return 0;
    }

    if (argc > 1)
        echo_operation = argv[1];
    if (argc > 2)
        word_to_echo = argv[2];
    if (argc > 3)
        echo_type = argv[3];

    sprintf (operation, "echo%s", echo_operation);

    printf ("Using endpoint : %s\n", address);
    printf ("Invoking %s with param %s\n", operation, word_to_echo);


    /* create call without passing svc_ctx_t struct */
    call = axis2_call_create (&env, NULL, client_home);
    mep_client = AXIS2_CALL_GET_BASE (call, &env);
    /* prepare SOAP envelope */
    env_ns =
        axis2_om_namespace_create (&env,
                                   AXIS2_SOAP11_SOAP_ENVELOPE_NAMESPACE_URI,
                                   "soap");
    soap_envelope = axis2_soap_envelope_create (&env, env_ns);
    soap_body = axis2_soap_body_create_with_parent (&env, soap_envelope);
    body_node = AXIS2_SOAP_BODY_GET_BASE_NODE (soap_body, &env);
    build_soap_body_content (&env, echo_operation, echo_type, word_to_echo,
                             body_node);

    /*print_invalid_om(&env, body_node); */


    msg_ctx = AXIS2_MEP_CLIENT_PREPARE_SOAP_ENVELOPE (mep_client, &env, node);
    if (!msg_ctx)
    {
        printf("ERROR: Could not prepare message context. ");
        printf("May be you havent set the repository corretly.\n");
        return -1;
    }

    AXIS2_MSG_CTX_SET_SOAP_ENVELOPE (msg_ctx, &env, soap_envelope);
    endpoint_ref = axis2_endpoint_ref_create (&env, address);
    AXIS2_CALL_SET_TO (call, &env, endpoint_ref);
    conf =
        AXIS2_CONF_CTX_GET_CONF (AXIS2_SVC_CTX_GET_CONF_CTX
                                 (AXIS2_MEP_CLIENT_GET_SVC_CTX
                                  (mep_client, &env), &env), &env);
    svc = AXIS2_CONF_GET_SVC (conf, &env, "echo");
    /*if (svc)
       {
       op = AXIS2_SVC_GET_OP_WITH_NAME(svc, &env, "echoString");
       if (op)
       {
       AXIS2_OP_SET_MSG_EXCHANGE_PATTERN(op, &env, AXIS2_MEP_URI_OUT_IN);
       }
       }
       else */
    {
        axis2_qname_t *op_qname = NULL;
        axis2_qname_t *svc_qname =
            axis2_qname_create (&env, "echo", NULL, NULL);
        svc = axis2_svc_create_with_qname (&env, svc_qname);
        op_qname = axis2_qname_create (&env, operation, NULL, NULL);
        op = axis2_op_create_with_qname (&env, op_qname);
        AXIS2_OP_SET_MSG_EXCHANGE_PATTERN (op, &env, AXIS2_MEP_URI_OUT_IN);
        AXIS2_SVC_ADD_OP (svc, &env, op);
        AXIS2_CONF_ADD_SVC (conf, &env, svc);
    }

    if (!op)
    {
        printf ("ERROR: echo_operation not present in service\n");
        return -1;
    }
    response_ctx = AXIS2_CALL_INVOKE_BLOCKING (call, &env, op, msg_ctx);

    if (response_ctx)
    {
        axis2_soap_envelope_t *soap_envelope =
            AXIS2_MSG_CTX_GET_SOAP_ENVELOPE (response_ctx, &env);
        ret_node = AXIS2_SOAP_ENVELOPE_GET_BASE_NODE (soap_envelope, &env);
    }

    if (ret_node)
    {
        print_invalid_om (&env, ret_node);
        if (AXIS2_OM_NODE_GET_NODE_TYPE (ret_node, &env) == AXIS2_OM_ELEMENT)
        {
            axis2_char_t *result = NULL;
            axis2_om_element_t *result_ele = NULL;
            axis2_om_node_t *ret_node1 = NULL;
            ret_node1 = AXIS2_OM_NODE_GET_FIRST_CHILD (ret_node, &env); /*Body */
            if (!ret_node1)
            {
                print_invalid_om (&env, ret_node);
                return AXIS2_FAILURE;
            }
            ret_node = AXIS2_OM_NODE_GET_FIRST_CHILD (ret_node1, &env); /*GetTypeResponse */
            if (!ret_node)
            {
                print_invalid_om (&env, ret_node1);
                return AXIS2_FAILURE;
            }
            /*see if we have got a fault */
            axis2_char_t echo_response_buff[32];
            sprintf (echo_response_buff, "echo%sResponse", echo_operation);
            result_ele =
                (axis2_om_element_t *)
                AXIS2_OM_NODE_GET_DATA_ELEMENT (ret_node, &env);
            if (AXIS2_STRCMP
                (AXIS2_OM_ELEMENT_GET_LOCALNAME (result_ele, &env),
                 echo_response_buff) != 0)
            {
                print_invalid_om (&env, ret_node1);
                return AXIS2_FAILURE;
            }

            ret_node1 = AXIS2_OM_NODE_GET_FIRST_CHILD (ret_node, &env); /*return */
            if (!ret_node1)
            {
                print_invalid_om (&env, ret_node);
                return AXIS2_FAILURE;
            }
            result_ele =
                (axis2_om_element_t *)
                AXIS2_OM_NODE_GET_DATA_ELEMENT (ret_node1, &env);
            result = AXIS2_OM_ELEMENT_GET_TEXT (result_ele, &env, ret_node1);
            if (!strcmp (word_to_echo, result))
            {
                printf ("\nSUCCESS\n\n");
            }
            else
            {
                printf ("\nFAIL\n\n");
            }

        }
        else
        {
            printf ("\nFAIL\n\n");
            return AXIS2_FAILURE;
        }
    }
    else
    {
        AXIS2_LOG_ERROR (env->log, AXIS2_LOG_SI,
                         "Stub invoke FAILED: Error code:" " %d :: %s",
                         env->error->error_number,
                         AXIS2_ERROR_GET_MESSAGE (env->error));
        printf ("round1 stub invoke FAILED!\n");
    }

    /*if (node)
       {
       AXIS2_OM_NODE_FREE_TREE(node, &env);
       } */
    return status;
}

axis2_om_node_t *
build_soap_body_content (axis2_env_t ** env, axis2_char_t * echo_operation,
                         axis2_char_t * echo_type,
                         axis2_char_t * word_to_echo,
                         axis2_om_node_t * body_node)
{
    axis2_om_node_t *envelope_node = NULL;
    axis2_om_element_t *envelope_element = NULL;
    axis2_om_element_t *body_om_ele = NULL;

    axis2_om_node_t *echo_om_node = NULL;
    axis2_om_element_t *echo_om_ele = NULL;
    axis2_om_node_t *text_om_node = NULL;
    axis2_om_element_t *text_om_ele = NULL;
    axis2_om_namespace_t *ns0 = NULL, *ns1 = NULL, *ns2 = NULL, *ns3 = NULL,
        *ns4 = NULL, *ns5 = NULL, *ns6 = NULL;

    axis2_om_attribute_t *attri1 = NULL;

    axis2_xml_writer_t *xml_writer = NULL;
    axis2_xml_writer_t *writer = NULL;
    axis2_om_output_t *om_output = NULL;
    axis2_char_t *buffer = NULL;

    axis2_char_t echo_operation_buff[32];
    axis2_char_t input_type_buff[32];
    axis2_char_t xsd_type_buff[32];

    /*generating the requried parameters */



    sprintf (echo_operation_buff, "echo%s", echo_operation);
    sprintf (input_type_buff, "input%s", echo_operation);
    sprintf (xsd_type_buff, "xsd:%s", echo_type);


    ns1 =
        axis2_om_namespace_create (env,
                                   "http://www.w3.org/2001/XMLSchema-instance",
                                   "xsi");
    ns2 =
        axis2_om_namespace_create (env, "http://www.w3.org/2001/XMLSchema",
                                   "xsd");
    ns3 =
        axis2_om_namespace_create (env,
                                   "http://schemas.xmlsoap.org/soap/encoding/",
                                   "soapenc");
    ns4 = axis2_om_namespace_create (env, "http://soapinterop.org/", "tns");
    ns5 =
        axis2_om_namespace_create (env, "http://soapinterop.org/encodedTypes",
                                   "types");

    envelope_node = AXIS2_OM_NODE_GET_PARENT (body_node, env);
    envelope_element =
        (axis2_om_element_t *) AXIS2_OM_NODE_GET_DATA_ELEMENT (envelope_node,
                                                               env);
    AXIS2_OM_ELEMENT_DECLARE_NAMESPACE (envelope_element, env, envelope_node,
                                        ns1);
    AXIS2_OM_ELEMENT_DECLARE_NAMESPACE (envelope_element, env, envelope_node,
                                        ns2);
    AXIS2_OM_ELEMENT_DECLARE_NAMESPACE (envelope_element, env, envelope_node,
                                        ns3);
    AXIS2_OM_ELEMENT_DECLARE_NAMESPACE (envelope_element, env, envelope_node,
                                        ns4);
    AXIS2_OM_ELEMENT_DECLARE_NAMESPACE (envelope_element, env, envelope_node,
                                        ns5);
    AXIS2_OM_ELEMENT_DECLARE_NAMESPACE (envelope_element, env, envelope_node,
                                        ns6);
    ns0 = AXIS2_OM_ELEMENT_GET_NAMESPACE (envelope_element, env);
    attri1 =
        axis2_om_attribute_create (env, "encodingStyle",
                                   "http://schemas.xmlsoap.org/soap/encoding/",
                                   ns0);

    body_om_ele = AXIS2_OM_NODE_GET_DATA_ELEMENT (body_node, env);
    AXIS2_OM_ELEMENT_ADD_ATTRIBUTE (body_om_ele, env, attri1, body_node);

    echo_om_ele =
        axis2_om_element_create (env, body_node, echo_operation_buff, ns4,
                                 &echo_om_node);

    text_om_ele =
        axis2_om_element_create (env, echo_om_node, input_type_buff, NULL,
                                 &text_om_node);
    attri1 = axis2_om_attribute_create (env, "type", xsd_type_buff, ns1);
    AXIS2_OM_ELEMENT_ADD_ATTRIBUTE (text_om_ele, env, attri1, text_om_node);
    AXIS2_OM_ELEMENT_SET_TEXT (text_om_ele, env, word_to_echo, text_om_node);

    xml_writer =
        axis2_xml_writer_create_for_memory (env, NULL, AXIS2_FALSE,
                                            AXIS2_FALSE);
    om_output = axis2_om_output_create (env, xml_writer);

    AXIS2_OM_NODE_SERIALIZE (echo_om_node, env, om_output);
    buffer = AXIS2_XML_WRITER_GET_XML (xml_writer, env);
    AXIS2_LOG_DEBUG ((*env)->log, AXIS2_LOG_SI,
                     "\nSending OM node in XML : %s \n", buffer);

    writer = axis2_xml_writer_create_for_memory (env, NULL, AXIS2_TRUE, 0);
    om_output = axis2_om_output_create (env, writer);
    AXIS2_OM_NODE_SERIALIZE (envelope_node, env, om_output);
    buffer = AXIS2_XML_WRITER_GET_XML (writer, env);
    printf ("Sending :\n%s\n", buffer);
    return echo_om_node;
}

void
print_invalid_om (axis2_env_t ** env, axis2_om_node_t * ret_node)
{

    axis2_xml_writer_t *writer = NULL;
    axis2_om_output_t *om_output = NULL;
    axis2_char_t *buffer = NULL;
    writer = axis2_xml_writer_create_for_memory (env, NULL, AXIS2_TRUE, 0);
    om_output = axis2_om_output_create (env, writer);

    AXIS2_OM_NODE_SERIALIZE (ret_node, env, om_output);
    buffer = AXIS2_XML_WRITER_GET_XML (writer, env);
    printf ("Received : \n%s\n", buffer);
}