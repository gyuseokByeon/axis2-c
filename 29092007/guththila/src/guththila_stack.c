
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
#include <guththila_stack.h>
    
    GUTHTHILA_CALL guththila_stack_create(const axutil_env_t * env) 
{
    
    
        (guththila_stack_t *) AXIS2_MALLOC(env->allocator,
                                           sizeof(guththila_stack_t));
    
        return NULL;
    
    
        (void **) AXIS2_MALLOC(env->allocator,
                               sizeof(void **) * GUTHTHILA_STACK_DEFAULT);
    
    {
        
        
    
    else
    {
        
        
        
    


guththila_stack_init(
    guththila_stack_t * stack,
    const axutil_env_t * env) 
{
    
    
        (void **) AXIS2_MALLOC(env->allocator,
                               sizeof(void **) * GUTHTHILA_STACK_DEFAULT);
    
    {
        
    
    else
    {
        
        
    


guththila_stack_free(
    guththila_stack_t * stack,
    const axutil_env_t * env) 
{
    
        AXIS2_FREE(env->allocator, stack->data);
    


guththila_stack_un_init(
    guththila_stack_t * stack,
    const axutil_env_t * env) 
{
    
        AXIS2_FREE(env->allocator, stack->data);


guththila_stack_pop(
    guththila_stack_t * stack,
    const axutil_env_t * env) 
{
    
    {
        
    
    


guththila_stack_push(
    guththila_stack_t * stack,
    void *data,
    const axutil_env_t * env) 
{
    
    
    
    {
        
            /*stack->data = (void **) realloc(stack->data, sizeof(void **) * (stack->max += GUTHTHILA_STACK_DEFAULT)); */ 
            temp =
            (void **) AXIS2_MALLOC(env->allocator,
                                   sizeof(void **) * (stack->max +=
                                                      GUTHTHILA_STACK_DEFAULT));
        
        {
            
        
        
        
        
            return GUTHTHILA_FAILURE;
    
    
    


guththila_stack_peek(
    guththila_stack_t * stack,
    const axutil_env_t * env) 
{
    
    {
        
    
    else
    {
        
    


guththila_stack_del_top(
    guththila_stack_t * stack,
    const axutil_env_t * env) 
{
    
    {
        
        
    
    


guththila_stack_is_empty(
    guththila_stack_t * stack,
    const axutil_env_t * env) 
{
    


guththila_stack_get_by_index(
    guththila_stack_t * stack,
    int index,
    const axutil_env_t * env) 
{
    


