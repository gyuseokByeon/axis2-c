/*
 *   Copyright 2004,2005 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *   
 */

#ifndef GUTHTHILA_XML_PULL_PARSER_H
#define GUTHTHILA_XML_PULL_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "guththila_buffer.h"
#include "guththila_reader.h"
#include "guththila_xml_writer.h"
#include "guththila_token.h"
#include "guththila_namespace.h"
#include "guththila_depth.h"
#include "guththila_attribute.h"
/* #include "guththila_stack.h */
#include "guththila_unicode.h"
/* #include "guththila_environment.h" */
#include "guththila_defines.h"

#include <axis2_env.h>
#include <axis2_allocator.h>
#include <axis2_stack.h>
#include <axis2_string.h>

#define p_FILE __FILE__         /* file name */
#define LINE __LINE__           /* line number */

/*NOTE:
 *-----
 *The above defined p_FILE and LINE should provide as parameters when
 *   throwing Xml_PullParser_Exception
 */

enum guththila_status
  {
    S_0 = 0,
    S_1,
    S_2,
    S_3,
    S_4
  };

enum guththila_event_types
  {
    GUTHTHILA_START_DOCUMENT = 0,
    GUTHTHILA_START_ELEMENT,
    GUTHTHILA_END_ELEMENT,
    GUTHTHILA_SPACE,
    GUTHTHILA_EMPTY_ELEMENT,
    GUTHTHILA_CHARACTER,
    GUTHTHILA_ENTITY_REFERANCE,
    GUTHTHILA_COMMENT
  };




typedef struct guththila_xml_pull_parser_s
{
  guththila_buffer_t *buffer;
  guththila_reader_t *reader;
  guththila_xml_writer_t *xsw;
  guththila_token_t *prefix;
  guththila_token_t *name;
  guththila_token_t *value;
  axis2_stack_t *stack;
  axis2_stack_t *attrib;
  axis2_stack_t *namesp;
  axis2_stack_t *dep;
  int _next;
  int offset;
  int last;
  int unicode_state;
  enum guththila_status status;
  enum guththila_event_types guththila_event;
} guththila_xml_pull_parser_t;


int AXIS2_CALL
guththila_xml_pull_parser_read (axis2_env_t * environment,
				guththila_xml_pull_parser_t * p);
                                
int AXIS2_CALL
guththila_xml_pull_parser_next_char (axis2_env_t *environment,
				     guththila_xml_pull_parser_t * p,
				     int eof);

int AXIS2_CALL
guththila_xml_pull_parser_tokenize (axis2_env_t *environment,
				    guththila_xml_pull_parser_t * p);
                                        
                                        
AXIS2_EXTERN int AXIS2_CALL
guththila_xml_pull_parser_exception (guththila_char_t * s, int line, int error_code);

int AXIS2_CALL
guththila_xml_pull_parser_skip_spaces (axis2_env_t *environment,
				       guththila_xml_pull_parser_t *p,
				       int c);
                                           
int AXIS2_CALL
guththila_xml_pull_parser_process_xml_decl(axis2_env_t *environment,
					   guththila_xml_pull_parser_t * p);
                                            
int AXIS2_CALL
guththila_xml_pull_parser_process_version_info(axis2_env_t * environment,
                                               guththila_xml_pull_parser_t * p);
                                               
                                               
int AXIS2_CALL
guththila_xml_pull_parser_process_encoding_decl (axis2_env_t * environment,
                                                 guththila_xml_pull_parser_t * p);
                                                 
int AXIS2_CALL
guththila_xml_pull_parser_process_sd_decl (axis2_env_t *environment,
                                           guththila_xml_pull_parser_t *p);
                                           
void AXIS2_CALL
guththila_xml_pull_parser_open_token (axis2_env_t *environment,
                                      guththila_xml_pull_parser_t *p);
                                      
void AXIS2_CALL
guththila_xml_pull_parser_close_token (axis2_env_t *environment,
                                       guththila_xml_pull_parser_t *p,
                                       int t,
                                       int refer);
                                       
guththila_char_t * AXIS2_CALL
guththila_xml_pull_parser_last_char (axis2_env_t *environment,
                                     guththila_xml_pull_parser_t *p);
                                     
int AXIS2_CALL
guththila_xml_pull_parser_process_eq (axis2_env_t *environment,
                                      guththila_xml_pull_parser_t *p,
                                      int c);
                                      
void AXIS2_CALL
guththila_xml_pull_parser_add_attribute (axis2_env_t *environment,
                                         guththila_xml_pull_parser_t *p,
                                         guththila_token_t * name,
                                         guththila_token_t * value);
                                         
void AXIS2_CALL
guththila_xml_pull_parser_add_attribute_with_prefix (axis2_env_t *environment,
						     guththila_xml_pull_parser_t *p,
						     guththila_token_t * prefix,
						     guththila_token_t * name,
						     guththila_token_t * value);
                                         
int AXIS2_CALL
guththila_xml_pull_parser_process_char_data (axis2_env_t *environment,
                                             guththila_xml_pull_parser_t *p);
                                             
int AXIS2_CALL
guththila_xml_pull_parser_process_space_tag_or_empty_element (axis2_env_t * environment,
							      guththila_xml_pull_parser_t *p);
                                             
int AXIS2_CALL
guththila_xml_pull_parser_process_comment (axis2_env_t *environment,
                                           guththila_xml_pull_parser_t *p);
                                           
int AXIS2_CALL
guththila_xml_pull_parser_process_pi (axis2_env_t *environment,
                                      guththila_xml_pull_parser_t *p);
                                      
int AXIS2_CALL
guththila_xml_pull_parser_process_end_tag (axis2_env_t *environment,
					   guththila_xml_pull_parser_t *p);
                                             
void AXIS2_CALL
guththila_xml_pull_parser_reset (axis2_env_t *environment,
                                 guththila_xml_pull_parser_t * p);
                                 
int AXIS2_CALL
guththila_xml_pull_parser_process_name (axis2_env_t *environment,
                                        guththila_xml_pull_parser_t *p);
                                        
int AXIS2_CALL
guththila_xml_pull_parser_process_attribute (axis2_env_t  *environment,
                                             guththila_xml_pull_parser_t *p,
                                             int c);
                                             
int AXIS2_CALL
guththila_xml_pull_parser_process_attribute_value (axis2_env_t * environment,
						   guththila_xml_pull_parser_t * p,
						   int c);
                                              
                                              
int AXIS2_CALL
guththila_xml_pull_parser_is_space (axis2_env_t *environment, int c);


void AXIS2_CALL
guththila_xml_pull_parser_relocate_tokens (axis2_env_t *environment,
                                           guththila_xml_pull_parser_t *p,
                                           int offset);
                                           
void AXIS2_CALL
guththila_xml_pull_parser_shift (axis2_env_t *environment,
                                 guththila_xml_pull_parser_t * p);
                                 
void AXIS2_CALL
guththila_xml_pull_parser_add_namespace (axis2_env_t *environment,
                                         guththila_xml_pull_parser_t *p,
                                         guththila_token_t * name,
                                         guththila_token_t * uri);
                                         
void AXIS2_CALL
guththila_xml_pull_parser_open_element (axis2_env_t *environment,
                                        guththila_xml_pull_parser_t *p);
                                        
void AXIS2_CALL
guththila_xml_pull_parser_close_element (axis2_env_t *environment,
                                         guththila_xml_pull_parser_t *p);
                                         
int AXIS2_CALL
guththila_xml_pull_parser_from_utf16 (axis2_env_t *environment,
                                      guththila_xml_pull_parser_t *p,
                                      int eof);
                                      
int AXIS2_CALL
guththila_xml_pull_parser_is_valid_starting_char (axis2_env_t * environment,
						  guththila_xml_pull_parser_t * p,
						  int c);
                                         

AXIS2_EXTERN  int AXIS2_CALL
guththila_xml_pull_parser_next (axis2_env_t * environment,
				guththila_xml_pull_parser_t * p);
                                
AXIS2_EXTERN guththila_xml_pull_parser_t * AXIS2_CALL
guththila_xml_pull_parser_create (axis2_env_t * environment,
				  guththila_reader_t * r);
                                  
AXIS2_EXTERN void AXIS2_CALL
guththila_xml_pull_parser_free (axis2_env_t * environment,
				guththila_xml_pull_parser_t * parser);
                               
AXIS2_EXTERN int AXIS2_CALL
guththila_xml_pull_parser_get_attribute_count (axis2_env_t * environment,
					       guththila_xml_pull_parser_t *p);
                                 
                                 
AXIS2_EXTERN guththila_char_t * AXIS2_CALL
guththila_xml_pull_parser_get_attribute_name (axis2_env_t *environment,
					      guththila_xml_pull_parser_t * p,
					      guththila_attribute_t * att);
                                 
                                 
AXIS2_EXTERN guththila_char_t * AXIS2_CALL
guththila_xml_pull_parser_get_attribute_value (axis2_env_t *environment,
					       guththila_xml_pull_parser_t *p,
					       guththila_attribute_t * att);
                                 
                                 
AXIS2_EXTERN guththila_char_t * AXIS2_CALL
guththila_xml_pull_parser_get_attribute_prefix (axis2_env_t *environment,
						guththila_xml_pull_parser_t *p,
						guththila_attribute_t * att);
                                 
                                 
AXIS2_EXTERN guththila_attribute_t * AXIS2_CALL
guththila_xml_pull_parser_get_attribute (axis2_env_t *environment,
					 guththila_xml_pull_parser_t * p);
                                         
                                         
AXIS2_EXTERN guththila_char_t * AXIS2_CALL
guththila_xml_pull_parser_get_attribute_name_by_number (axis2_env_t * environment,
							guththila_xml_pull_parser_t * p,
							int i);
                                         
                                         
AXIS2_EXTERN guththila_char_t * AXIS2_CALL
guththila_xml_pull_parser_get_attribute_value_by_number (axis2_env_t * environment,
							 guththila_xml_pull_parser_t * p,
							 int i);
                                         
                                         
AXIS2_EXTERN guththila_char_t * AXIS2_CALL
guththila_xml_pull_parser_get_attribute_prefix_by_number (axis2_env_t * environment,
							  guththila_xml_pull_parser_t * p,
							  int i);
                                         
                                         
AXIS2_EXTERN guththila_char_t * AXIS2_CALL
guththila_xml_pull_parser_get_name (axis2_env_t * environment,
				    guththila_xml_pull_parser_t * p);
                                    
                                    
AXIS2_EXTERN guththila_char_t * AXIS2_CALL
guththila_xml_pull_parser_get_prefix (axis2_env_t * environment,
				      guththila_xml_pull_parser_t * p);
                                      
                                      
AXIS2_EXTERN guththila_char_t * AXIS2_CALL
guththila_xml_pull_parser_get_value (axis2_env_t * environment,
				     guththila_xml_pull_parser_t * p);
                                     
                                     
AXIS2_EXTERN guththila_namespace_t * AXIS2_CALL
guththila_xml_pull_parser_get_namespace (axis2_env_t *environment,
					 guththila_xml_pull_parser_t * p);
                                         
                                         
AXIS2_EXTERN int AXIS2_CALL
guththila_xml_pull_parser_get_namespace_count (axis2_env_t *environment,
					       guththila_xml_pull_parser_t *p);
                                         
                                         
AXIS2_EXTERN guththila_char_t * AXIS2_CALL
guththila_xml_pull_parser_get_namespace_uri (axis2_env_t *environment,
					     guththila_xml_pull_parser_t * p,
					     guththila_namespace_t * ns);
                                             
                                             
AXIS2_EXTERN guththila_char_t * AXIS2_CALL
guththila_xml_pull_parser_get_namespace_prefix (axis2_env_t *environment,
						guththila_xml_pull_parser_t *p,
						guththila_namespace_t * ns);
                                     

AXIS2_EXTERN guththila_char_t * AXIS2_CALL
guththila_xml_pull_parser_get_namespace_prefix_by_number (axis2_env_t * environment,
							  guththila_xml_pull_parser_t * p,
							  int i);
                                     
                                     
AXIS2_EXTERN guththila_char_t * AXIS2_CALL
guththila_xml_pull_parser_get_namespace_uri_by_number (axis2_env_t *environment,
						       guththila_xml_pull_parser_t * p,
						       int i);
                                       
                                       
AXIS2_EXTERN guththila_char_t * AXIS2_CALL
guththila_xml_pull_parser_get_attribute_namespace_by_number (axis2_env_t * environment,
							     guththila_xml_pull_parser_t * p,
							     int i);

AXIS2_EXTERN guththila_char_t * AXIS2_CALL
guththila_xml_pull_parser_get_encoding (axis2_env_t *environment,
					guththila_xml_pull_parser_t *p);

/* --------------writer api --------------------------*/

AXIS2_EXTERN void  AXIS2_CALL
guththila_xml_pull_parser_create_xml_stream_writer (axis2_env_t *environment, 
						    guththila_xml_pull_parser_t *p, 
						    char *fp);


AXIS2_EXTERN void AXIS2_CALL
guththila_xml_pull_parser_write_to_buffer (axis2_env_t *env, 
					   guththila_xml_pull_parser_t *p,
					   const char *buff);


AXIS2_EXTERN void AXIS2_CALL
guththila_xml_pull_parser_close_start_element (axis2_env_t *environment,
					       guththila_xml_pull_parser_t *p);


AXIS2_EXTERN void AXIS2_CALL
guththila_xml_pull_parser_close_depth_element (axis2_env_t *environment,
					       guththila_xml_pull_parser_t *p);


AXIS2_EXTERN void AXIS2_CALL
guththila_xml_pull_parser_check_name_validity (axis2_env_t *environment,
					       guththila_xml_pull_parser_t *p,
					       char *start_element);


AXIS2_EXTERN void AXIS2_CALL
guththila_xml_pull_parser_open_depth_element (axis2_env_t *environment,
					      guththila_xml_pull_parser_t *p);


AXIS2_EXTERN void AXIS2_CALL
guththila_xml_pull_parser_do_write_attribute (axis2_env_t *environment, 
					      guththila_xml_pull_parser_t *p, 
					      const char *local_name, 
					      const char *value);


AXIS2_EXTERN int AXIS2_CALL
guththila_xml_pull_parser_check_default_namespace (axis2_env_t *env, 
						   guththila_xml_pull_parser_t *p, 
						   char *ns_uri);


AXIS2_EXTERN void AXIS2_CALL
guththila_xml_pull_parser_do_write_default_namespace (axis2_env_t *env, 
						      guththila_xml_pull_parser_t *p, 
						      char *ns_uri);


AXIS2_EXTERN int  AXIS2_CALL
guththila_xml_pull_parser_check_prefix_validity (axis2_env_t *env, 
						 guththila_xml_pull_parser_t *p, 
						 char *prefix, 
						 char *uri);

AXIS2_EXTERN void  AXIS2_CALL
guththila_xml_pull_parser_write_namespace (axis2_env_t *env, 
					   guththila_xml_pull_parser_t *p, 
					   char *prefix, 
					   char *uri);


int  AXIS2_CALL
guththila_xml_pull_parser_check_xml_stream_writer (axis2_env_t *environment, 
						   guththila_xml_pull_parser_t *p);


void AXIS2_CALL
guththila_xml_pull_parser_do_write_namespace (axis2_env_t *env, 
					      guththila_xml_pull_parser_t *p, 
					      char *prefix, 
					      char *uri);

void AXIS2_CALL
guththila_xml_pull_parser_do_write_attribute_with_prefix_and_namespace (axis2_env_t *env, 
									guththila_xml_pull_parser_t *p,
									const char *prefix, 
									const char *namespace_uri,
									const char *local_name, 
									const char *value);


AXIS2_EXTERN int AXIS2_CALL
guththila_xml_pull_parser_is_exsisting_prefix (axis2_env_t *env, 
					       guththila_xml_pull_parser_t *p, 
					       const char *prefix);


AXIS2_EXTERN void   AXIS2_CALL
guththila_xml_pull_parser_write_start_document (axis2_env_t *environment, 
						guththila_xml_pull_parser_t *p);


void AXIS2_CALL
guththila_xml_pull_parser_do_write_attribute_with_prefix (axis2_env_t *env, 
							  guththila_xml_pull_parser_t *p, 
							  const char *prefix,
							  const char *local_name, 
							  const char *value);


AXIS2_EXTERN char * AXIS2_CALL
guththila_xml_pull_parser_get_prefix_for_namespace (axis2_env_t *env, 
						    guththila_xml_pull_parser_t *p, 
						    const char *namespace);



AXIS2_EXTERN void   AXIS2_CALL
guththila_xml_pull_parser_write_start_element (axis2_env_t *environment, 
						     guththila_xml_pull_parser_t *p, 
						     char *start_element);


AXIS2_EXTERN void   AXIS2_CALL
guththila_xml_pull_parser_write_end_element (axis2_env_t *environment, 
					     guththila_xml_pull_parser_t *p);


AXIS2_EXTERN void   AXIS2_CALL
guththila_xml_pull_parser_flush (axis2_env_t *environment, 
				 guththila_xml_pull_parser_t *p);


AXIS2_EXTERN void  AXIS2_CALL
guththila_xml_pull_parser_close (axis2_env_t *environment, 
				 guththila_xml_pull_parser_t *p);


AXIS2_EXTERN void   AXIS2_CALL
guththila_xml_pull_parser_write_characters (axis2_env_t *environment, 
					    guththila_xml_pull_parser_t *p,
					    const char  *buff);


AXIS2_EXTERN void   AXIS2_CALL
guththila_xml_pull_parser_write_comment (axis2_env_t *environment, 
					 guththila_xml_pull_parser_t *p, 
					 const char *buff);

AXIS2_EXTERN void   AXIS2_CALL
guththila_xml_pull_parser_write_escape_character (axis2_env_t *environment, 
						  guththila_xml_pull_parser_t *p, 
						  const char *buff);


AXIS2_EXTERN void   AXIS2_CALL
guththila_xml_pull_parser_write_empty_element (axis2_env_t *environment, 
					       guththila_xml_pull_parser_t *p, 
					       char *empty_element);


AXIS2_EXTERN void  AXIS2_CALL
guththila_xml_pull_parser_write_default_namespace (axis2_env_t *environment, 
						   guththila_xml_pull_parser_t *p, 
						   char *namespace_uri);


AXIS2_EXTERN void  AXIS2_CALL
guththila_xml_pull_parser_write_namespace (axis2_env_t *environment, 
					   guththila_xml_pull_parser_t *p, 
					   char *prefix, char *uri);


AXIS2_EXTERN void   AXIS2_CALL
guththila_xml_pull_parser_writeAttribute (axis2_env_t *environment, 
					  guththila_xml_pull_parser_t *p, 
					  const char *localname, 
					  const char *value);


AXIS2_EXTERN void   AXIS2_CALL
guththila_xml_pull_parser_write_attribute_with_prefix_and_namespace (axis2_env_t *environment, 
								     guththila_xml_pull_parser_t *p,
								     const char *prefix, 
								     const char *namespace_uri,
								     const char *localname, const char *value);


AXIS2_EXTERN void   AXIS2_CALL
guththila_xml_pull_parser_write_attribute_with_prefix (axis2_env_t *environment, 
						       guththila_xml_pull_parser_t *p,
						       const char *prefix,
						       const char *localname, const char *value);


AXIS2_EXTERN void   AXIS2_CALL
guththila_xml_pull_parser_write_attribute_with_namespace (axis2_env_t *environment, 
							  guththila_xml_pull_parser_t *p,
							  const char *namespace,
							  const char *localname, const char *value);


AXIS2_EXTERN void  AXIS2_CALL
guththila_xml_pull_parser_write_start_element_with_prefix_and_namespace (axis2_env_t *environment, 
									 guththila_xml_pull_parser_t *p, 
									 const char* prefix,
									 const char *namespace_uri, const char *local_name);


AXIS2_EXTERN void  AXIS2_CALL
guththila_xml_pull_parser_write_start_element_with_namespace (axis2_env_t *environment, 
							      guththila_xml_pull_parser_t *p, 
							      const char *namespace_uri, 
							      const char *local_name);


AXIS2_EXTERN void  AXIS2_CALL
guththila_xml_pull_parser_write_start_element_with_prefix (axis2_env_t *environment, 
							   guththila_xml_pull_parser_t *p, 
							   const char *prefix, 
							   const char *local_name);


AXIS2_EXTERN void  AXIS2_CALL
guththila_xml_pull_parser_write_empty_element_with_prefix_and_namespace (axis2_env_t *environment, 
									 guththila_xml_pull_parser_t *p, 
									 const char* prefix,
									 const char *namespace_uri, 
									 const char *local_name);


AXIS2_EXTERN void  AXIS2_CALL
guththila_xml_pull_parser_write_empty_element_with_namespace (axis2_env_t *environment, 
							      guththila_xml_pull_parser_t *p, 
							      const char *namespace_uri, 
							      const char *local_name);


AXIS2_EXTERN void  AXIS2_CALL
guththila_xml_pull_parser_write_empty_element_with_prefix (axis2_env_t *environment, 
							   guththila_xml_pull_parser_t *p, 
							   const char *prefix, 
							   const char *local_name);


AXIS2_EXTERN void  AXIS2_CALL
guththila_xml_pull_parser_write_end_document (axis2_env_t *environment, 
					      guththila_xml_pull_parser_t *p);


AXIS2_EXTERN void  AXIS2_CALL
guththila_xml_pull_parser_write_line (axis2_env_t *environment, 
				      guththila_xml_pull_parser_t *p, 
				      char *element_name, 
				      char *characters);

AXIS2_EXTERN void AXIS2_CALL
guththila_xml_pull_parser_xml_writer_free (axis2_env_t *environment,
					   guththila_xml_pull_parser_t *t);

#endif /* GUTHTHILA_XML_PULL_PARSER_H */