
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    
#include <guththila_xml_writer.h>
    
#define GUTHTHILA_WRITER_SD_DECLARATION  "<?xml version=\"1.0\" encoding=\"utf-8\" ?>"
    
#ifndef GUTHTHILA_XML_WRITER_TOKEN
#ifndef GUTHTHILA_WRITER_ELEM_FREE
#define GUTHTHILA_WRITER_ELEM_FREE(wr, elem, _env)		\
    if ((elem)->prefix)
    AXIS2_FREE(env->allocator, (elem)->prefix);
\
    AXIS2_FREE(env->allocator, (elem)->name);
\

#endif  /* 
#else   /* 
#ifndef GUTHTHILA_WRITER_ELEM_FREE
#define GUTHTHILA_WRITER_ELEM_FREE(wr, elem, _env)		\
    if ((elem)->prefix)
    guththila_tok_list_release_token(&wr->tok_list, (elem)->prefix, _env);
\
    guththila_tok_list_release_token(&wr->tok_list, (elem)->name, _env);
\

#endif  /* 
#endif  /* 
    
#ifndef GUTHTHILA_XML_WRITER_TOKEN
#ifndef GUTHTHILA_WRITER_CLEAR_NAMESP 
#define GUTHTHILA_WRITER_CLEAR_NAMESP(wr, stack_namesp, _no, counter, _namesp, j, _env)		\
    for (counter = GUTHTHILA_STACK_TOP_INDEX(*stack_namesp); counter >= _no;
         counter--)
{
    \
        (guththila_xml_writer_namesp_t *) guththila_stack_pop(stack_namesp,
                                                              _env);
    \
    {
        \
        {
            \
                AXIS2_FREE(env->allocator, _namesp->name[j]);
            \
                AXIS2_FREE(env->allocator, _namesp->uri[j]);
        \
        \
        \
        \
    \
    \
\


#endif  /* 
#else   /* 
#ifndef GUTHTHILA_WRITER_CLEAR_NAMESP 
#define GUTHTHILA_WRITER_CLEAR_NAMESP(wr, stack_namesp, _no, counter, _namesp, j, _env)		\
    for (counter = GUTHTHILA_STACK_TOP_INDEX(*stack_namesp); counter >= _no;
         counter--)
{
    \
        (guththila_xml_writer_namesp_t *) guththila_stack_pop(stack_namesp,
                                                              _env);
    \
    {
        \
        {
            \
                                               _env);
            \
                                               _env);
        \
        \
        \
        \
    \
    \
\


#endif  /* 
#endif  /* 
    
#ifndef GUTHTHILA_WRITER_INIT_ELEMENT
#define GUTHTHILA_WRITER_INIT_ELEMENT_WITH_PREFIX(wr, _elem, _name_start, _name_size, _pref_start, _pref_size) \
    _elem->name = guththila_tok_list_get_token(&wr->tok_list);
\
\
\
\
\

#endif  /* 
    
#ifndef GUTHTHILA_WRITER_INIT_ELEMENT
#define GUTHTHILA_WRITER_INIT_ELEMENT_WITHOUT_PREFIX(wr, _elem, _name_start, _name_size) \
    _elem->name = guththila_tok_list_get_token(&(wr)->tok_list);
\
\
\

#endif  /* 
    

/*
#ifndef guththila_write(_wr, _buff, _buff_size)
#define guththila_write(_wr, _buff, _buff_size)	\
	if (_wr->type == GUTHTHILA_WRITER_MEMORY){	\
		if (_wr->buffer.size > _wr->buffer.next + _buff_size) {\
			memcpy (_wr->buffer.buff + _wr->buffer.next, _buff, _buff_size);\
			_wr->buffer.next += (int)_buff_size;			\
		} else {\
		_wr->buffer.buff = realloc(_wr->buffer.buff, _wr->buffer.size * 2);\
		_wr->buffer.size = _wr->buffer.size * 2; \
		memcpy (_wr->buffer.buff + _wr->buffer.next, _buff, _buff_size);\
		_wr->buffer.next += (int)_buff_size;			\
		}\
	} 
#endif*/ 
    
guththila_create_xml_stream_writer(char *file_name,
                                   const axutil_env_t * env) 
{
    
        AXIS2_MALLOC(env->allocator, sizeof(guththila_xml_writer_t));
    
        return NULL;
    
    
    {
        
        
    
    
    {
        
        
        
    
    
    {
        
        
        
        
    
    
    
    
    



guththila_create_xml_stream_writer_for_memory(const axutil_env_t * env) 
{
    
        AXIS2_MALLOC(env->allocator, sizeof(guththila_xml_writer_t));
    
        return NULL;
    
    {
        
        
    
    
    {
        
        
        
    
    
    {
        
        
        
        
    
    
#ifdef GUTHTHILA_XML_WRITER_TOKEN
        if (!guththila_tok_list_init(&wr->tok_list, env))
    {
        
        
        
        
        
    
    
#endif  /* 
        wr->type = GUTHTHILA_WRITER_MEMORY;
    
    
    


guththila_xml_writer_free(
    guththila_xml_writer_t * wr,
    const axutil_env_t * env) 
{
    
    {
        
    
    else if (wr->type == GUTHTHILA_WRITER_FILE)
    {
        
    
    
#ifdef GUTHTHILA_XML_WRITER_TOKEN
        guththila_tok_list_free_data(&wr->tok_list, env);
    
#endif  /* 
        guththila_stack_un_init(&wr->element, env);
    


guththila_write(
    guththila_xml_writer_t * wr,
    char *buff,
    size_t buff_len,
    const axutil_env_t * env) 
{
    
    
    
    
    
    
    {
        
            wr->buffer.buffs_size[wr->buffer.cur_buff] -
            wr->buffer.data_size[wr->buffer.cur_buff];
        
        {
            
                    wr->buffer.data_size[wr->buffer.cur_buff], buff, buff_len);
            
            
            
        
        else
        {
            
            {
                
                        wr->buffer.data_size[wr->buffer.cur_buff], buff,
                        remain_len);
                
            
            
            {
                
                
                    (char **) AXIS2_MALLOC(env->allocator,
                                           sizeof(char *) *
                                           wr->buffer.no_buffers);
                
                    (size_t *) AXIS2_MALLOC(env->allocator,
                                            sizeof(size_t) *
                                            wr->buffer.no_buffers);
                
                    (size_t *) AXIS2_MALLOC(env->allocator,
                                            sizeof(size_t) *
                                            wr->buffer.no_buffers);
                
                {
                    
                    
                    
                
                
                
                
                
                
                
            
            
            
            
            {
                
            
            
                (char *) AXIS2_MALLOC(env->allocator, sizeof(char) * temp);
            
            
                    buff_len - remain_len);
            
            
                wr->buffer.data_size[wr->buffer.cur_buff - 1];
            
            
    
    else if (wr->type == GUTHTHILA_WRITER_FILE)
    {
        
    
    


guththila_write_token(
    guththila_xml_writer_t * wr,
    guththila_token_t * tok,
    const axutil_env_t * env) 
{
    
    
    
    
    
    {
        
            wr->buffer.buffs_size[wr->buffer.cur_buff] -
            wr->buffer.data_size[wr->buffer.cur_buff];
        
        {
            
                    wr->buffer.data_size[wr->buffer.cur_buff], tok->start,
                    tok->size);
            
            
            
        
        else
        {
            
            {
                
                        wr->buffer.data_size[wr->buffer.cur_buff], tok->start,
                        remain_len);
                
            
            
            {
                
                
                    (char **) AXIS2_MALLOC(env->allocator,
                                           sizeof(char *) *
                                           wr->buffer.no_buffers);
                
                    (size_t *) AXIS2_MALLOC(env->allocator,
                                            sizeof(size_t) *
                                            wr->buffer.no_buffers);
                
                    (size_t *) AXIS2_MALLOC(env->allocator,
                                            sizeof(size_t) *
                                            wr->buffer.no_buffers);
                
                {
                    
                    
                    
                
                
                
                
                
                
                
            
            
            
            
            {
                
            
            
                (char *) AXIS2_MALLOC(env->allocator, sizeof(char) * temp);
            
            
                    tok->start + remain_len, tok->size - remain_len);
            
            
                wr->buffer.data_size[wr->buffer.cur_buff - 1];
            
            
    
    else if (wr->type == GUTHTHILA_WRITER_FILE)
    {
        
    
    


guththila_write_xtoken(
    guththila_xml_writer_t * wr,
    char *buff,
    size_t buff_len,
    const axutil_env_t * env) 
{
    
    
    
    
    
    {
        
            wr->buffer.buffs_size[wr->buffer.cur_buff] -
            wr->buffer.data_size[wr->buffer.cur_buff];
        
        {
            
                    wr->buffer.data_size[wr->buffer.cur_buff], buff, buff_len);
            
            
            
        
        else
        {
            
            {
                
                
                    (char **) AXIS2_MALLOC(env->allocator,
                                           sizeof(char *) *
                                           wr->buffer.no_buffers);
                
                    (size_t *) AXIS2_MALLOC(env->allocator,
                                            sizeof(size_t) *
                                            wr->buffer.no_buffers);
                
                    (size_t *) AXIS2_MALLOC(env->allocator,
                                            sizeof(size_t) *
                                            wr->buffer.no_buffers);
                
                {
                    
                    
                    
                
                
                
                
                
                
                
            
            
            
            {
                
            
            
            
                (char *) AXIS2_MALLOC(env->allocator, sizeof(char) * temp);
            
            
            
            
                wr->buffer.data_size[wr->buffer.cur_buff - 1];
            
            
    
    else if (wr->type == GUTHTHILA_WRITER_FILE)
    {
        
    
    


guththila_write_start_document(
    guththila_xml_writer_t * wr,
    const axutil_env_t * env) 
{
    
                     strlen(GUTHTHILA_WRITER_SD_DECLARATION), env);
    


guththila_write_start_element(
    guththila_xml_writer_t * wr,
    char *start_element,
    const axutil_env_t * env) 
{
    
    
    
        (guththila_xml_writer_element_t *) AXIS2_MALLOC(env->allocator,
                                                        sizeof
                                                        (guththila_xml_writer_element_t));
    
    
    {
        
        
        
    
    else if (wr->status == START_EMPTY)
    {
        
        
        
    
    else if (BEGINING)
    {
        
        
        
    
    else
    {
        
    
    
    
#ifndef GUTHTHILA_XML_WRITER_TOKEN
        element->name = strdup(start_element);
    
    
#else   /* 
        element->name = guththila_tok_list_get_token(&wr->tok_list, env);
    
    
    
    
#endif  /* 
        element->name_sp_stack_no = -1;
    


guththila_write_end_element(
    guththila_xml_writer_t * wr,
    const axutil_env_t * env) 
{
    
    
    
        j = 0;
    
    {
        
        
            (guththila_xml_writer_element_t *) guththila_stack_pop(&wr->element,
                                                                   env);
        
        {
            
            {
                
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                    guththila_write(wr, elem->prefix, strlen(elem->prefix),
                                    env);
                
#else   /* 
                    guththila_write_token(wr, elem->prefix, env);
                
#endif  /* 
                    guththila_write(wr, ":", 1u, env);
            
            
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                guththila_write(wr, elem->name, strlen(elem->name), env);
            
#else   /* 
                guththila_write_token(wr, elem->name, env);
            
#endif  /* 
                guththila_write(wr, ">", 1u, env);
            
            
            {
                
                                               elem->name_sp_stack_no, i,
                                               namesp, j, env);
            
            
            
        
        else
        {
            
        
    
    else if (wr->status == START_EMPTY)
    {
        
        
        
    
    else if (wr->status == BEGINING)
    {
        
        
            (guththila_xml_writer_element_t *) guththila_stack_pop(&wr->element,
                                                                   env);
        
        {
            
            {
                
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                    guththila_write(wr, elem->prefix, strlen(elem->prefix),
                                    env);
                
#else   /* 
                    guththila_write_token(wr, elem->prefix, env);
                
#endif  /* 
                    guththila_write(wr, ":", 1u, env);
            
            
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                guththila_write(wr, elem->name, strlen(elem->name), env);
            
#else   /* 
                guththila_write_token(wr, elem->name, env);
            
#endif  /* 
                guththila_write(wr, ">", 1u, env);
            
            
            {
                
                                               elem->name_sp_stack_no, i,
                                               namesp, j, env);
            
            
            
        
        else
        {
            
        
    
    


guththila_close(
    guththila_xml_writer_t * wr,
    const axutil_env_t * env) 
{
    


guththila_write_characters(
    guththila_xml_writer_t * wr,
    char *buff,
    const axutil_env_t * env) 
{
    
    {
        
        
        
        
    
    else if (wr->status == START_EMPTY)
    {
        
        
        
        
    
    else if (wr->status == BEGINING)
    {
        
        
    
    


guththila_write_comment(
    guththila_xml_writer_t * wr,
    char *buff,
    const axutil_env_t * env) 
{
    
    {
        
        
        
        
        
    
    else if (wr->status == START_EMPTY)
    {
        
        
        
        
        
    
    else if (wr->status == BEGINING)
    {
        
        
        
        
    
    


guththila_write_escape_character(
    guththila_xml_writer_t * wr,
    char *buff,
    const axutil_env_t * env) 
{
    
        /*TODO element closing -- not sure */ 
        if (wr->status == START)
    {
        
        
    
    else if (wr->status == START_EMPTY)
    {
        
        
    
    
    {
        
        {
        
            
            
        
            
            
        
            
            
        
            
            
        
            
            
        
    
    


guththila_write_empty_element(
    guththila_xml_writer_t * wr,
    char *empty_element,
    const axutil_env_t * env) 
{
    
    
    
    
    {
        
        
        
    
    else if (wr->status == START_EMPTY)
    {
        
        
        
    
    else if (BEGINING)
    {
        
        
        
    
    else
    {
        
    
    
    


guththila_write_default_namespace(
    guththila_xml_writer_t * wr,
    char *namespace_uri,
    const axutil_env_t * env) 
{
    
    {
        
        
        
        
    
    


guththila_write_namespace(
    guththila_xml_writer_t * wr,
    char *prefix,
    char *uri,
    const axutil_env_t * env) 
{
    
        j = 0,
        temp = 0,
        nmsp_found = GUTHTHILA_FALSE,
        stack_size = 0;
    
    
    
        uri_start = 0;
    
    
    
    
    
    {
        
            (guththila_xml_writer_namesp_t *) guththila_stack_get_by_index(&wr->
                                                                           namesp,
                                                                           i,
                                                                           env);
        
        
        {
            
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                if (!strcmp(prefix, writer_namesp->name[j]))
            {
                
#else   /* 
                if (!guththila_tok_str_cmp
                    (writer_namesp->name[j], prefix, pref_len, env))
            {
                
#endif  /* 
                    nmsp_found = GUTHTHILA_TRUE;
            
        
    
    
    {
        
        
        
        
        
        
        
        
        
        {
            
                (guththila_xml_writer_namesp_t *) AXIS2_MALLOC(env->allocator,
                                                               sizeof
                                                               (guththila_xml_writer_namesp_t));
            
            {
                
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                    namesp->name =
                    (char **) AXIS2_MALLOC(env->allocator,
                                           sizeof(char *) *
                                           GUTHTHILA_XML_WRITER_NAMESP_DEF_SIZE);
                
                    (char **) AXIS2_MALLOC(env->allocator,
                                           sizeof(char *) *
                                           GUTHTHILA_XML_WRITER_NAMESP_DEF_SIZE);
                
                
                
#else   /* 
                    namesp->name =
                    (guththila_token_t **) AXIS2_MALLOC(env->allocator,
                                                        sizeof(guththila_token_t
                                                               *) *
                                                        GUTHTHILA_XML_WRITER_NAMESP_DEF_SIZE);
                
                    (guththila_token_t **) AXIS2_MALLOC(env->allocator,
                                                        sizeof(guththila_token_t
                                                               *) *
                                                        GUTHTHILA_XML_WRITER_NAMESP_DEF_SIZE);
                
                    guththila_tok_list_get_token(&wr->tok_list, env);
                
                    GUTHTHILA_BUF_POS(wr->buffer, pref_start);
                
                
                    guththila_tok_list_get_token(&wr->tok_list, env);
                
                    GUTHTHILA_BUF_POS(wr->buffer, uri_start);
                
                
#endif  /* 
                    namesp->no = 1;
                
                
                
            
            else
            {
                
            
        
        else if (elem)
        {
            
            
            {
                
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                    namesp->name[++(namesp->no) - 1] = strdup(prefix);
                
                
#else   /* 
                    namesp->name[++(namesp->no) - 1] =
                    guththila_tok_list_get_token(&wr->tok_list, env);
                
                    guththila_tok_list_get_token(&wr->tok_list, env);
                
                    GUTHTHILA_BUF_POS(wr->buffer, pref_start);
                
                
                    GUTHTHILA_BUF_POS(wr->buffer, uri_start);
                
                
#endif  /* 
            }
            else
            {
                
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                    namesp->name =
                    (char **) realloc(namesp->name,
                                      sizeof(char *) *
                                      (GUTHTHILA_XML_WRITER_NAMESP_DEF_SIZE +
                                       namesp->size));
                
                    (char **) realloc(namesp->name,
                                      sizeof(char *) *
                                      (GUTHTHILA_XML_WRITER_NAMESP_DEF_SIZE +
                                       namesp->size));
                
                    GUTHTHILA_XML_WRITER_NAMESP_DEF_SIZE + namesp->size;
                
                
                
#else   /* 
                    /*namesp->name = (guththila_token_t **)realloc(namesp->name, sizeof(guththila_token_t *) * (GUTHTHILA_XML_WRITER_NAMESP_DEF_SIZE + namesp->size));
                       namesp->uri = (guththila_token_t **)realloc(namesp->name, sizeof(guththila_token_t *) * (GUTHTHILA_XML_WRITER_NAMESP_DEF_SIZE + namesp->size)); */ 
                    tok_name =
                    (guththila_token_t **) AXIS2_MALLOC(env->allocator,
                                                        sizeof(guththila_token_t
                                                               *) *
                                                        (GUTHTHILA_XML_WRITER_NAMESP_DEF_SIZE
                                                         + namesp->size));
                
                    (guththila_token_t **) AXIS2_MALLOC(env->allocator,
                                                        sizeof(guththila_token_t
                                                               *) *
                                                        (GUTHTHILA_XML_WRITER_NAMESP_DEF_SIZE
                                                         + namesp->size));
                
                {
                    
                    
                
                
                
                
                
                
                    GUTHTHILA_XML_WRITER_NAMESP_DEF_SIZE + namesp->size;
                
                    GUTHTHILA_BUF_POS(wr->buffer, pref_start);
                
                
                    GUTHTHILA_BUF_POS(wr->buffer, uri_start);
                
                
#endif  /* 
            }
        
        
    
    
        
    


guththila_write_attribute(
    guththila_xml_writer_t * wr,
    char *localname,
    char *value,
    const axutil_env_t * env) 
{
    
    {
        
        
        
        
        
        
    
    


guththila_write_attribute_with_prefix_and_namespace(
    guththila_xml_writer_t * wr,
    char *prefix,
    
    char *localname,
    char *value,
    const axutil_env_t * env) 
{
    
        guththila_write_attribute_with_prefix(wr, prefix, localname, value,
                                              env);


guththila_write_attribute_with_prefix(
    guththila_xml_writer_t * wr,
    char *prefix,
    
    char *value,
    const axutil_env_t * env) 
{
    
        j = 0;
    
    
    
    
    
    {
        
        {
            
                (guththila_xml_writer_namesp_t *)
                guththila_stack_get_by_index(&wr->namesp, i, env);
            
            
            {
                
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                    if (!strcmp(prefix, writer_namesp->name[j]))
                {
                    
#else   /* 
                    if (!guththila_tok_str_cmp
                        (writer_namesp->name[j], prefix, pref_len, env))
                {
                    
#endif  /* 
                        guththila_write(wr, " ", 1u, env);
                    
                    
                    
                    
                    
                    
                    
                
            
        
    
    


guththila_write_attribute_with_namespace(
    guththila_xml_writer_t * wr,
    char *namesp,
    
    char *value,
    const axutil_env_t * env) 
{
    
        j = 0;
    
    
    
    
    {
        
        {
            
                (guththila_xml_writer_namesp_t *)
                guththila_stack_get_by_index(&wr->namesp, i, env);
            
            
            {
                
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                    if (!strcmp(namesp, writer_namesp->uri[j]))
                {
                    
                    
                                     strlen(writer_namesp->name[j]), env);
                    
#else   /* 
                    if (!guththila_tok_str_cmp
                        (writer_namesp->uri[j], namesp, strlen(namesp), env))
                {
                    
                    
                    
#endif  /* 
                        guththila_write(wr, ":", 1u, env);
                    
                    
                    
                    
                    
                
            
        
    
    


guththila_write_start_element_with_prefix_and_namespace(
    guththila_xml_writer_t * wr,
    char *prefix,
    
    char *local_name,
    const axutil_env_t * env) 
{
    
        j = 0,
        temp = 0,
        stack_size = 0,
        nmsp_found = GUTHTHILA_FALSE;
    
    
    
        pref_start = 0,
        elem_start = 0,
        elem_pref_start = 0;
    
    
    
    
    
        (guththila_xml_writer_namesp_t *) AXIS2_MALLOC(env->allocator,
                                                       sizeof
                                                       (guththila_xml_writer_namesp_t));
    
        (guththila_xml_writer_element_t *) AXIS2_MALLOC(env->allocator,
                                                        sizeof
                                                        (guththila_xml_writer_element_t));
    
    
    
    
    
    {
        
            (guththila_xml_writer_namesp_t *) guththila_stack_get_by_index(&wr->
                                                                           namesp,
                                                                           i,
                                                                           env);
        
        
        {
            
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                if (!strcmp(uri, writer_namesp->uri[j]))
            {
                
#else   /* 
                if (!guththila_tok_str_cmp
                    (writer_namesp->name[j], prefix, pref_len, env))
            {
                
#endif  /* 
                    nmsp_found = GUTHTHILA_TRUE;
            
        
    
    
    {
        
        {
            
            
            
            
            
            
            
            {
                
                
                
                
                
                
                
                
            
        
        else if (wr->status == START_EMPTY)
        {
            
            
            
            
            
            
            
            {
                
                
                
                
                
                
                
                
            
            
        
        else if (BEGINING)
        {
            
            
            
            
            
            
            
            {
                
                
                
                
                
                
                
                
            
            
        
        else
        {
            
        
        
        {
            
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                namesp->name =
                (char **) AXIS2_MALLOC(env->allocator,
                                       sizeof(char *) *
                                       GUTHTHILA_XML_WRITER_NAMESP_DEF_SIZE);
            
                (char **) AXIS2_MALLOC(env->allocator,
                                       sizeof(char *) *
                                       GUTHTHILA_XML_WRITER_NAMESP_DEF_SIZE);
            
            
            
#else   /* 
                namesp->name =
                (guththila_token_t **) AXIS2_MALLOC(env->allocator,
                                                    sizeof(guththila_token_t *)
                                                    *
                                                    GUTHTHILA_XML_WRITER_NAMESP_DEF_SIZE);
            
                (guththila_token_t **) AXIS2_MALLOC(env->allocator,
                                                    sizeof(guththila_token_t *)
                                                    *
                                                    GUTHTHILA_XML_WRITER_NAMESP_DEF_SIZE);
            
            
            
            
            
            
            
#endif  /* 
                namesp->no = 1;
            
            
        
        
#ifndef GUTHTHILA_XML_WRITER_TOKEN
            elem->name = strdup(local_name);
        
        
#else   /* 
            elem->name = guththila_tok_list_get_token(&wr->tok_list, env);
        
        
        
        
        
        
#endif  /* 
            elem->name_sp_stack_no = GUTHTHILA_STACK_TOP_INDEX(wr->namesp);
        
    
    else
    {
        
    
    


guththila_write_start_element_with_namespace(
    guththila_xml_writer_t * wr,
    char *namespace_uri,
    
    const axutil_env_t * env) 
{
    
        j = 0;
    
    
    
    
    
    
    
    {
        
            (guththila_xml_writer_namesp_t *) guththila_stack_get_by_index(&wr->
                                                                           namesp,
                                                                           i,
                                                                           env);
        
        
        {
            
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                if (!strcmp(namespace_uri, writer_namesp->uri[j]))
            {
                
#else   /* 
                if (!guththila_tok_str_cmp
                    (writer_namesp->uri[j], namespace_uri,
                     strlen(namespace_uri), env))
            {
                
#endif  /* 
                    guththila_xml_writer_element_t * element =
                    (guththila_xml_writer_element_t *) AXIS2_MALLOC(env->
                                                                    allocator,
                                                                    sizeof
                                                                    (guththila_xml_writer_element_t));
                
                {
                    
                    
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                        guththila_write(wr, writer_namesp->name[j],
                                        strlen(writer_namesp->name[j]));
                    
#else   /* 
                        guththila_write_token(wr, writer_namesp->name[j], env);
                    
#endif  /* 
                        guththila_write(wr, ":", 1u, env);
                    
                    
                
                else if (wr->status == START_EMPTY)
                {
                    
                    
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                        guththila_write(wr, writer_namesp->name[j],
                                        strlen(writer_namesp->name[j]), env);
                    
#else   /* 
                        guththila_write_token(wr, writer_namesp->name[j], env);
                    
#endif  /* 
                        guththila_write(wr, ":", 1u, env);
                    
                    
                
                else if (BEGINING)
                {
                    
                    
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                        guththila_write(wr, writer_namesp->name[j],
                                        strlen(writer_namesp->name[j]), env);
                    
#else   /* 
                        guththila_write_token(wr, writer_namesp->name[j], env);
                    
#endif  /* 
                        guththila_write(wr, ":", 1u, env);
                    
                    
                
                else
                {
                    
                
                
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                    element->name = strdup(local_name);
                
                
#else   /* 
                    element->name =
                    guththila_tok_list_get_token(&wr->tok_list, env);
                
                
                    GUTHTHILA_BUF_POS(wr->buffer, elem_start);
                
                    guththila_tok_list_get_token(&wr->tok_list, env);
                
                
                
#endif  /* 
                    element->name_sp_stack_no = -1;
                
                
            
        
    
    


guththila_write_start_element_with_prefix(
    guththila_xml_writer_t * wr,
    char *prefix,
    char *local_name,
    const axutil_env_t * env) 
{
    
        j = 0;
    
    
    
    
    
    
    
    
    {
        
            (guththila_xml_writer_namesp_t *) guththila_stack_get_by_index(&wr->
                                                                           namesp,
                                                                           i,
                                                                           env);
        
        
        {
            
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                if (!strcmp(prefix, writer_namesp->name[j]))
            {
                
#else   /* 
                if (!guththila_tok_str_cmp
                    (writer_namesp->name[j], prefix, pref_len, env))
            {
                
#endif  /* 
                    guththila_xml_writer_element_t * element =
                    (guththila_xml_writer_element_t *) AXIS2_MALLOC(env->
                                                                    allocator,
                                                                    sizeof
                                                                    (guththila_xml_writer_element_t));
                
                {
                    
                    
                    
                    
                    
                                            env);
                
                else if (wr->status == START_EMPTY)
                {
                    
                    
                    
                    
                    
                                            env);
                
                else if (BEGINING)
                {
                    
                    
                    
                    
                    
                                            env);
                
                else
                {
                    
                
                
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                    element->name = strdup(local_name);
                
                
#else   /* 
                    element->name =
                    guththila_tok_list_get_token(&wr->tok_list, env);
                
                
                    GUTHTHILA_BUF_POS(wr->buffer, elem_start);
                
                    guththila_tok_list_get_token(&wr->tok_list, env);
                
                
                
#endif  /* 
                    wr->status = START;
                
                
            
        
    
    


guththila_write_empty_element_with_prefix_and_namespace(
    guththila_xml_writer_t * wr,
    char *prefix,
    
    char *local_name,
    const axutil_env_t * env) 
{
    
    
    
        (guththila_xml_writer_namesp_t *) AXIS2_MALLOC(env->allocator,
                                                       sizeof
                                                       (guththila_xml_writer_namesp_t));
    
        (guththila_xml_writer_element_t *) AXIS2_MALLOC(env->allocator,
                                                        sizeof
                                                        (guththila_xml_writer_element_t));
    
    {
        
        {
            
            
            
            
            
            
            
            
            
            
            
            
        
        else if (wr->status == START_EMPTY)
        {
            
            
            
            
            
            
            
            
            
            
            
        
        else if (BEGINING)
        {
            
            
            
            
            
            
            
            
            
            
            
            
        
        else
        {
            
        
    
    else
    {
        
    
    


guththila_write_empty_element_with_namespace(
    guththila_xml_writer_t * wr,
    char *namespace_uri,
    char *local_name,
    const axutil_env_t * env) 
{
    
        j = 0;
    
    
    
    
    {
        
            (guththila_xml_writer_namesp_t *) guththila_stack_get_by_index(&wr->
                                                                           namesp,
                                                                           i,
                                                                           env);
        
        
        {
            
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                if (!strcmp(namespace_uri, writer_namesp->uri[j]))
            {
                
#else   /* 
                if (!guththila_tok_str_cmp
                    (writer_namesp->uri[j], namespace_uri,
                     strlen(namespace_uri), env))
            {
                
#endif  /* 
                    if (wr->status == START)
                {
                    
                    
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                        guththila_write(wr, writer_namesp->name[j],
                                        strlen(writer_namesp->name[j]), env);
                    
#else   /* 
                        guththila_write_token(wr, writer_namesp->name[j], env);
                    
#endif  /* 
                        guththila_write(wr, ":", 1u, env);
                    
                                            env);
                
                else if (wr->status == START_EMPTY)
                {
                    
                    
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                        guththila_write(wr, writer_namesp->name[j],
                                        strlen(writer_namesp->name[j]), env);
                    
#else   /* 
                        guththila_write_token(wr, writer_namesp->name[j], env);
                    
#endif  /* 
                        guththila_write(wr, ":", 1u, env);
                    
                                            env);
                
                else if (BEGINING)
                {
                    
                    
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                        guththila_write(wr, writer_namesp->name[j],
                                        strlen(writer_namesp->name[j]), env);
                    
#else   /* 
                        guththila_write_token(wr, writer_namesp->name[j], env);
                    
#endif  /* 
                        guththila_write(wr, ":", 1u, env);
                    
                                            env);
                
                else
                {
                    
                
                
                
            
        
    
    


guththila_write_empty_element_with_prefix(
    guththila_xml_writer_t * wr,
    char *prefix,
    char *local_name,
    const axutil_env_t * env) 
{
    
        j = 0;
    
    
    
    
    
    {
        
            (guththila_xml_writer_namesp_t *) guththila_stack_get_by_index(&wr->
                                                                           namesp,
                                                                           i,
                                                                           env);
        
        
        {
            
#ifndef GUTHTHILA_XML_WRITER_TOKEN
                if (!strcmp(prefix, writer_namesp->name[j]))
            {
                
#else   /* 
                if (!guththila_tok_str_cmp
                    (writer_namesp->name[j], prefix, pref_len, env))
            {
                
#endif  /* 
                    if (wr->status == START)
                {
                    
                    
                    
                    
                                            env);
                
                else if (wr->status == START_EMPTY)
                {
                    
                    
                    
                    
                                            env);
                
                else if (BEGINING)
                {
                    
                    
                    
                    
                                            env);
                
                else
                {
                    
                
                
                
            
        
    
    


guththila_write_end_document(
    guththila_xml_writer_t * wr,
    const axutil_env_t * env) 
{
    
    
    
        
    
    {
        
        {
            
        
    
    


guththila_write_line(
    guththila_xml_writer_t * wr,
    char *element_name,
    char *characters,
    const axutil_env_t * env) 
{
    
    
    
    
    


guththila_get_memory_buffer(
    guththila_xml_writer_t * wr,
    const axutil_env_t * env) 
{
    
    {
        
    
    


guththila_get_memory_buffer_size(
    guththila_xml_writer_t * wr,
    const axutil_env_t * env) 
{
    
    {
        
            wr->buffer.data_size[wr->buffer.cur_buff];
    
    


guththila_get_prefix_for_namespace(
    guththila_xml_writer_t * wr,
    
    const axutil_env_t * env) 
{
    
        j = 0;
    
    
    
    
    
    {
        
            (guththila_xml_writer_namesp_t *) guththila_stack_get_by_index(&wr->
                                                                           namesp,
                                                                           i,
                                                                           env);
        
        
        {
            
                 (writer_namesp->uri[j], nmsp, strlen(nmsp), env))
            {
                
                
            
        
    
    


guththila_write_to_buffer(
    guththila_xml_writer_t * wr,
    char *buff,
    int size,
    const axutil_env_t * env) 
{
    
    


