
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

/*
Compiling For Windows:
cl.exe /nologo /D "WIN32" /D "_WINDOWS" /D "_MBCS" /I %AXIS2C_HOME%\include /c *.c
link.exe /LIBPATH:%AXIS2C_HOME%\lib axutil.lib axiom.lib axis2_parser.lib axis2_engine.lib /OUT:test.exe *.obj
*/

#include <gtest/gtest.h>

#include <stdio.h>
#include <axiom.h>
#include <axis2_util.h>
#include <axiom_soap.h>
#include <axiom_xpath.h>

/* Function headers */
axiom_node_t *build_test_xml(const axutil_env_t *env);

void output_results(const axutil_env_t *env, axiom_xpath_result_t *xpath_result);

axiom_node_t *read_test_xml(const axutil_env_t *env, char *file_name);

void output_results(const axutil_env_t *env,
        axiom_xpath_result_t *xpath_result);

void evaluate(const axutil_env_t *env,
        axiom_xpath_context_t *context,
        axis2_char_t *expr_str);

void evaluate_expressions(const axutil_env_t *env,
        axiom_xpath_context_t *context,
        char *file_name);

void add_namespaces(const axutil_env_t *env,
        axiom_xpath_context_t *context,
        char *file_name);

int readline(FILE *fin, char *str);

FILE *fcor;
/*FILE *ftemp;*/


/* FIXME 
 * These tests exercise code, but don't actually check that the output is
 * correct.  They didn't when they were in the old test format, either.
 */

class TestXPath: public ::testing::Test
{

    protected:
        void SetUp()
        {
            m_env = axutil_env_create_all("xpath_test.log", AXIS2_LOG_LEVEL_TRACE);

        }

        void TearDown()
        {
            axutil_env_free(m_env);
        }

        axutil_env_t *m_env = NULL;

};


TEST_F(TestXPath, test_xpath) {

    axiom_node_t *test_tree = NULL;
    axis2_char_t *test_tree_str;
    char *xml_file = "test.xml";
    char *xpath_file = "test.xpath";
    char *ns_file = "test.ns";
    char *cor_file = "results.txt";
    axiom_xpath_context_t *context = NULL;

    /*Create the request */
    /* test_tree = build_test_xml(env); */
    test_tree = read_test_xml(m_env, (axis2_char_t *)xml_file);

    fcor = fopen(cor_file, "r");
    /*ftemp = fopen("temp.txt", "w");*/

    ASSERT_NE(fcor, nullptr);

    ASSERT_NE(test_tree, nullptr);

    test_tree_str = axiom_node_to_string(test_tree, m_env);
    printf("\nTesting XML\n-----------\n\"%s\"\n\n\n", test_tree_str);
    AXIS2_FREE(m_env->allocator, test_tree_str);

    /* Create XPath Context */
    context = axiom_xpath_context_create(m_env, test_tree);

    /* Namespaces */
    add_namespaces(m_env, context, ns_file);

    evaluate_expressions(m_env, context, xpath_file);

    test_tree_str = axiom_node_to_string(test_tree, m_env);
    printf("\n\nFinal XML\n-----------\n\"%s\"\n\n\n", test_tree_str);
    AXIS2_FREE(m_env->allocator, test_tree_str);

    /* Freeing memory */
    if (context)
    {
        axiom_xpath_free_context(m_env, context);
    }

    if (test_tree)
    {
        axiom_node_free_tree(test_tree, m_env);
    }

    if(fcor)
    {
        fclose(fcor);
    }

}

int readline(FILE *fin, char *str)
{
    int i;

    for (i = 0; 1; i++)
    {
        str[i] = (char)getc(fin);

        if (str[i] == '\n' || str[i] == '\r' || str[i] == EOF)
        {
            break;
        }
    }

    str[i] = '\0';

    return i;
}

void add_namespaces(const axutil_env_t *env,
        axiom_xpath_context_t *context,
        char *file_name)
{
    FILE *fin = NULL;
    char prefix[1024];
    char uri[1024];
    axiom_namespace_t *ns;

    fin = fopen(file_name, "r");

    ASSERT_NE(fin, nullptr);

    /* Compiling XPath expression */
    while (1)
    {
        if (readline(fin, prefix) == 0)
        {
            break;
        }

        if (readline(fin, uri) == 0)
        {
            break;
        }

        ns = axiom_namespace_create(
                    env, (axis2_char_t *)uri, (axis2_char_t *)prefix);

        if (ns)
        {
            axiom_xpath_register_namespace(context, ns);
        }
    }

    fclose(fin);
}

void evaluate_expressions(
    const axutil_env_t *env,
    axiom_xpath_context_t *context,
    char *file_name)
{
    FILE *fin = NULL;
    char str[1024];

    fin = fopen(file_name, "r");

    ASSERT_NE(fin, nullptr);

    /* Compiling XPath expression */
    while (1)
    {
        if (readline(fin, str) == 0)
        {
            break;
        }

        if (str[0] == '#')
        {
            printf("\n\n%s", str + 1);
            continue;
        }

        evaluate(env, context, (axis2_char_t *)str);
    }

    fclose(fin);
}

void evaluate(
    const axutil_env_t *env,
    axiom_xpath_context_t *context,
    axis2_char_t *expr_str)
{
    axiom_xpath_expression_t *expr = NULL;
    axiom_xpath_result_t *result = NULL;

    printf("\nCompiling XPath expression: \"%s\" ...\n", expr_str);
    expr = axiom_xpath_compile_expression(env, expr_str);

    if (!expr)
    {
        printf("Compilation error.");
        printf("Please check the systax of the XPath query.\n");

        return;
    }

    /* Evaluating XPath expression */
    printf("Evaluating...\n");
    result = axiom_xpath_evaluate(context, expr);

    if (!result)
    {
        printf("An error occured while evaluating the expression.\n");

        axiom_xpath_free_expression(env, expr);

        return;
    }

    if (result->flag == AXIOM_XPATH_ERROR_STREAMING_NOT_SUPPORTED)
    {
        printf("Streaming not supported.\n");

        axiom_xpath_free_expression(env, expr);

        return;
    }

    output_results(env, result);

    if (result)
    {
        axiom_xpath_free_result(env, result);
    }
}

int compare_result(axis2_char_t *rs)
{
    int i;
    char c;

    /*fprintf(ftemp, "%s#", rs);*/

    if(!fcor)
    {
        return 0;
    }

    for(i = 0; 1; i++)
    {
        while(rs[i] == ' ' || rs[i] == '\n' || rs[i] == '\r' || rs[i] == '\t')
        {
            i++;
        }

        do
        {
            c = (char)getc(fcor);
        }
        while(c == ' ' || c == '\n' || c == '\r' || c == '\t');

        if(c == '#' || c == EOF)
        {
            break;
        }

        if(c != rs[i])
        {
            while(c != '#' && c != EOF)
            {
                c = getc(fcor);
            }

            return 0;
        }
    }

    return rs[i] == '\0';
}

void output_results(const axutil_env_t *env,
        axiom_xpath_result_t *xpath_result)
{
    axiom_xpath_result_node_t *xpath_result_node;
    axiom_node_t *result_node=NULL;
    axis2_char_t *result_str=NULL;
    axis2_char_t result_set[100000];
    axis2_char_t temp_res[100000];

    axiom_element_t *ele;
    int i;

    result_set[0] = '\n';
    result_set[1] = '\0';

    for (i = 0; i < axutil_array_list_size(xpath_result->nodes, env); i++)
    {
        xpath_result_node = (axiom_xpath_result_node_t*)  axutil_array_list_get(xpath_result->nodes, env, i);

        if (xpath_result_node->type == AXIOM_XPATH_TYPE_NODE)
        {
            result_node = (axiom_node_t*) xpath_result_node->value;
            ele = (axiom_element_t *)axiom_node_get_data_element(
                        result_node, env);

            if (ele)
            {
                /*result_str = axiom_element_get_text(ele, env, result_node);*/
                result_str = axiom_node_to_string(result_node, env);

                sprintf(temp_res, "\"%s\"\n", result_str);
                strcat(result_set, temp_res);
                AXIS2_FREE(env->allocator, result_str);
            }
        }
        else if (xpath_result_node->type == AXIOM_XPATH_TYPE_ATTRIBUTE)
        {
            result_str =
                axiom_attribute_get_localname((axiom_attribute*)xpath_result_node->value, env);
            sprintf(temp_res, "%s = ", result_str);
            strcat(result_set, temp_res);
            result_str =
                axiom_attribute_get_value((axiom_attribute*)xpath_result_node->value, env);
            sprintf(temp_res, "\"%s\"\n", result_str);
            strcat(result_set, temp_res);
        }
        else if (xpath_result_node->type == AXIOM_XPATH_TYPE_NAMESPACE)
        {
            result_str =
                axiom_namespace_get_prefix((axiom_namespace*)xpath_result_node->value, env);
            sprintf(temp_res, "%s = ", result_str);
            strcat(result_set, temp_res);
            result_str =
                axiom_namespace_get_uri((axiom_namespace*)xpath_result_node->value, env);
            sprintf(temp_res, "\"%s\"\n", result_str);
            strcat(result_set, temp_res);
        }
        else if (xpath_result_node->type == AXIOM_XPATH_TYPE_BOOLEAN)
        {
            sprintf(temp_res, "\"%s\"\n",  
                    (*(axis2_bool_t *)xpath_result_node->value) ? "true" : "false");
            strcat(result_set, temp_res);
        }
        else if (xpath_result_node->type == AXIOM_XPATH_TYPE_TEXT)
        {
            sprintf(temp_res, "\"%s\"\n", 
                    (axis2_char_t *)xpath_result_node->value);
            strcat(result_set, temp_res);
        }
        else if (xpath_result_node->type == AXIOM_XPATH_TYPE_NUMBER)
        {
            sprintf(temp_res, "\"%lf\"\n", 
                    *(double *)xpath_result_node->value);
            strcat(result_set, temp_res);
        }
    }

    if(compare_result(result_set))
    {
        printf("Test case passed\n");
    }
    else
    {
        printf("Failed test case!\nOutput\n%s\n", result_set);
    }
}

axiom_node_t *read_test_xml(const axutil_env_t *env, axis2_char_t *file_name)
{
    axiom_xml_reader_t *reader = NULL;
    axiom_stax_builder_t *builder = NULL;
    axiom_document_t *document = NULL;
    axiom_node_t *root = NULL;


    /* Create parser */
    reader = axiom_xml_reader_create_for_file(env, file_name, NULL);

    if (!reader)
    {
        printf("Error creating pullparser");
        return NULL;
    }

    /* Create axiom_stax_builder */
    builder = axiom_stax_builder_create(env, reader);

    if (!builder)
    {
        printf("Error creating pull parser");
        return NULL;
    }

    /* Create an om document */
    document = axiom_stax_builder_get_document(builder, env);

    if (!document)
    {
        printf("Error creating document");
        return NULL;
    }

    /* Get root element */
    root = axiom_document_get_root_element(document, env);
    if (!root)
    {
        printf("Root element null ");
        axiom_stax_builder_free(builder, env);
        return NULL;
    }

    while (axiom_document_build_next(document, env));

    axiom_stax_builder_free_self(builder, env);

    return root;
}

axiom_node_t * build_test_xml(const axutil_env_t *env)
{
    axiom_node_t *main_node;
    axiom_node_t *order_node;
    axiom_node_t *values_node;
    axiom_node_t *value_node;
    axiom_node_t *grandchild;
    axis2_char_t value_str[255];
    axiom_element_t *order_ele;
    axiom_element_t *values_ele;
    axiom_element_t *value_ele;
    axiom_element_t *grandchild_ele;
    axiom_attribute_t *attribute;
    int i, N = 20;

    axiom_namespace_t *ns1 =
        axiom_namespace_create(env, "http://xpath/test", "ns1");

    axiom_element_create(env, NULL, "test", ns1, &main_node);

    order_ele =
        axiom_element_create(env, main_node, "node1", NULL, &order_node);
    axiom_element_set_text(order_ele, env, "10", order_node);
    attribute =
        axiom_attribute_create(env, "attr1", "attribute_value_1", NULL);
    axiom_element_add_attribute(order_ele, env, attribute, order_node);

    values_ele =
        axiom_element_create(env, main_node, "node2", NULL, &values_node);

    for (i = 0 ; i < N; i++)
    {
        sprintf(value_str, "%d", i + 1);

        value_ele =
            axiom_element_create(env, values_node, "child", NULL, &value_node);
        axiom_element_set_text(value_ele, env, value_str, value_node);

        grandchild_ele =
            axiom_element_create(env, value_node, "grandchild", NULL, &grandchild);
        axiom_element_set_text(grandchild_ele, env, value_str /*"3 rd level"*/, grandchild);
    }

    return main_node;
}
