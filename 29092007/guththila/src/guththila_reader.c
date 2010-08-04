
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
#include <stdlib.h>
#include <string.h>
#include <guththila_reader.h>
    
guththila_reader_create_for_file(char *file_name, const axutil_env_t * env) 
{
    
    
    
        
    
        (guththila_reader_t *) AXIS2_MALLOC(env->allocator,
                                            sizeof(guththila_reader_t));
    
        
    
    
    {
        
        
    
    
    
    



guththila_reader_create_for_memory(void *buffer, int size,
                                   const axutil_env_t * env) 
{
    
        (guththila_reader_t *) AXIS2_MALLOC(env->allocator,
                                            sizeof(guththila_reader_t));
    
    {
        
        
        
        
        
    
    



guththila_reader_create_for_io(GUTHTHILA_READ_INPUT_CALLBACK
                               input_read_callback, void *ctx,
                               const axutil_env_t * env) 
{
    
        (guththila_reader_t *) AXIS2_MALLOC(env->allocator,
                                            sizeof(guththila_reader_t));
    
    {
        
        
        
        
    
    


guththila_reader_free(
    guththila_reader_t * r,
    const axutil_env_t * env) 
{
    
    {
        
    
    


guththila_reader_read(
    guththila_reader_t * r,
    guththila_char * buffer,
    int offset,
    int length,
    const axutil_env_t * env) 
{
    
    
    {
    
        
    
        
    
        
    
    


