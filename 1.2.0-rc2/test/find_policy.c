
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
    
#include <axiom_stax_builder.h>
#include <axiom_document.h>
#include <axiom_node.h>
#include <axiom_element.h>
#include <axiom_text.h>
#include <axiom_data_source.h>
#include <axutil_stream.h>
#include <axutil_log_default.h>
#include <axutil_error_default.h>
#include <axiom_xml_reader.h>
#include <stdio.h>
#include <axiom_xml_writer.h>
#include <axutil_env.h>
    
                                          const axutil_env_t * env,
                                          axis2_char_t * wsdl_name);


    axis2_char_t * element_name,
    const axutil_env_t * env,
    axutil_array_list_t * policy_node_list,
    axis2_char_t * wsdl_name);


/**
   Define the environment related variables globaly so that they are available
   for both functions
*/ 
    








/** a method that demonstrate creating a om model using an xml file */ 
    
read_input(
    char *buffer,
    int size,
    void *ctx) 
{
    
    
    
    
        
    
        
    {
        
        
    
    


main(
    int argc,
    char *argv[]) 
{
    
    
    
    
    
    
    
    
    
    
        "C:\\OMWsdl\\wsdltest\\debug\\PolicyAttachments.wsdl";
    
    
    
    
    
        axutil_env_create_with_error_log(allocator, error, axis_log);
    
    
        //get all the policy values of "Binding_2B"
        get_all_policy("Binding-2B", environment, policy_array, file_name);
    
        (axiom_node_t *) axutil_array_list_get(policy_array, environment, 2);
    
    
    
    
        axiom_xml_writer_create_for_memory(environment, NULL, AXIS2_TRUE, 0,
                                           
    
    
    
    
        
    {
        
            //printf(outfilename);
            o = fopen("C:\\OMWsdl\\wsdltest\\debug\\out.xml", "w");
        
            
        
        
        
    
    
    
    
    



                                       const axutil_env_t * env,
                                       axis2_char_t * wsdl_name) 
{
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        
    
        axiom_xml_reader_create_for_io(environment, read_input, NULL, NULL,
                                       NULL);
    
        
    {
        
        
    
    
    
        
    {
        
        
    
    
    
        
    
    
        
    {
        
        
        
    
    
    do
        
    {
        
        
            
        
            
        {
            
                (axiom_element_t *) axiom_node_get_data_element(node2,
                                                                environment);
            
            
                
            {
                
                
                
                      (axiom_attribute_get_value(attr, environment), name) == 0)
                    
                {
                    
                
            
        
    
    while (node2);
    



{
    
    
    
    
    
    
    
    
        (axiom_element_t *) axiom_node_get_data_element(node, env);
    
    
        
    {
        
        
            
        {
            
                (axiom_element_t *) axiom_node_get_data_element(child_node,
                                                                environment);
            
                  (axiom_element_get_localname(policy_element, environment),
                   "PolicyReference") == 0)
                
            {
                
                
                    axiom_element_get_attribute(policy_element, environment,
                                                qname);
                
                    
                {
                    
                    
                    
                
            
        
    
    


get_all_policy(
    axis2_char_t * element_name,
    const axutil_env_t * env,
    axutil_array_list_t * policy_node_list,
    axis2_char_t * wsdl_name) 
{
    
    
    
    
    
    
    
    
        
    
        return_policy_element(get_policy_ref(parent_node, env), env, wsdl_name);
    
    
        
    {
        
            (axiom_element_t *) axiom_node_get_data_element(parent_node, env);
        
        
            
        {
            
            
            do
                
            {
                
                    
                {
                    
                    
                    
                    
                        axutil_string_substring_starting_at(attribute_val, 1);
                    
                                    wsdl_name);
                    
                
            
            while (hi);
        
    
    
