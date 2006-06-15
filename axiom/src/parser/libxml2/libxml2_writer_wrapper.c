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
 */
 
#include <libxml/xmlwriter.h>
#include <axis2_utils.h>
#include <axis2_utils_defines.h>
#include <axis2_env.h>
#include <axiom_writer.h>
#include <axis2_string.h>
#include <string.h>
#include <axis2_stack.h>
#include <axis2_hash.h>
#include <axis2_array_list.h>

/*******************************************************************************/

#define ENCODING "ISO-8859-1"

#define AXIS2_XMLNS_NAMESPACE_URI "http://www.w3.org/XML/1998/namespace"
#define AXIS2_XMLNS_PREFIX "xml"

/************************ structures *****************************************/

typedef struct uri_prefix_element
{
    axis2_char_t *prefix;
    
    axis2_char_t *uri;
    
    axis2_char_t *real_prefix;
    
    axis2_char_t *key;
    
}uri_prefix_element_t;

typedef struct axis2_libxml2_writer_wrapper_impl
{
    axiom_writer_t writer;
    
    xmlTextWriterPtr xml_writer;
    
    xmlBufferPtr buffer;

   xmlDocPtr doc;
    
    int writer_type;
    
    axis2_char_t *encoding;
    
    int is_prefix_defaulting;
    
    int compression;

    axis2_stack_t *stack;
    
    axis2_bool_t in_empty_element;
    
    axis2_bool_t in_start_element;
    
    axis2_hash_t *uri_prefix_map;
    
    uri_prefix_element_t *default_lang_namespace;
    
}axis2_libxml2_writer_wrapper_impl_t;


/***************************** Macros ******************************************/

#define AXIS2_INTF_TO_IMPL(p) ((axis2_libxml2_writer_wrapper_impl_t*)p)


/*********************** function prototypes ***********************************/
axis2_status_t AXIS2_CALL 
axis2_libxml2_writer_wrapper_free(
        axiom_writer_t *writer,
        const axis2_env_t *env);
        
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_start_element(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *localname);
        
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_end_start_element(
        axiom_writer_t *writer,
        const axis2_env_t *env);

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_start_element_with_namespace(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *localname,
        axis2_char_t *namespace_uri);

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_start_element_with_namespace_prefix(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *localname,
        axis2_char_t *namespace_uri,
        axis2_char_t *prefix);       
    
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_empty_element(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *localname);

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_empty_element_with_namespace(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *localname,
        axis2_char_t *namespace_uri);

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_empty_element_with_namespace_prefix(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *localname,
        axis2_char_t *namespace_uri,
        axis2_char_t *prefix);

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_end_element(
        axiom_writer_t *writer,
        const axis2_env_t *env);

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_end_document(
        axiom_writer_t *writer,
        const axis2_env_t *env);

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_attribute(axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *localname,
        axis2_char_t *value);
            
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_attribute_with_namespace(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *localname,
        axis2_char_t *value,
        axis2_char_t *namespace_uri);
        
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_attribute_with_namespace_prefix(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *localname,
        axis2_char_t *value,
        axis2_char_t *namespace_uri,
        axis2_char_t *prefix);
        
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_namespace(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *prefix,
        axis2_char_t *namespace_uri);   


axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_default_namespace(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *namespace_uri);  

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_comment(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *value);
        
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_processing_instruction(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *target);
        
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_processing_instruction_data(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *target,
        axis2_char_t *data);
        
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_cdata(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *data);

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_dtd(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *dtd); 

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_entity_ref(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *name); 

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_start_document(
        axiom_writer_t *writer,
        const axis2_env_t *env);  

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_start_document_with_version(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *version);   

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_start_document_with_version_encoding(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *encoding,
        axis2_char_t *version);
        
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_characters(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *text);   

axis2_char_t* AXIS2_CALL
axis2_libxml2_writer_wrapper_get_prefix(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *uri);

axis2_status_t AXIS2_CALL 
axis2_libxml2_writer_wrapper_set_prefix( 
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *prefix,
        axis2_char_t *uri);
        
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_set_default_prefix(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *uri);                                                 

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_encoded(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *text,
        int in_attr);

void* AXIS2_CALL
axis2_libxml2_writer_wrapper_get_xml(
        axiom_writer_t *writer,
        const axis2_env_t *env);

int AXIS2_CALL
axis2_libxml2_writer_wrapper_get_type(
        axiom_writer_t *writer,
        const axis2_env_t *env);
        
/*********************** static functions ************************************/
static axis2_status_t
axis2_libxml2_writer_wrapper_pop_context(
        axiom_writer_t *writer,
        const axis2_env_t *env);
        
static axis2_status_t
axis2_libxml2_writer_wrapper_push(
        axiom_writer_t *writer, 
        const axis2_env_t *env,
        const axis2_char_t *uri,
        const axis2_char_t *prefix);
        
static axis2_bool_t
axis2_libxml2_writer_wrapper_is_namespace_declared(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *key);
        
static axis2_status_t
uri_prefix_element_free(
        uri_prefix_element_t *up_element,
        const axis2_env_t *env);
                                
static uri_prefix_element_t *
uri_prefix_element_create(
        const axis2_env_t *env,
        const axis2_char_t *uri,
        const axis2_char_t *prefix,
        const axis2_char_t *real_prefix,
        const axis2_char_t *key);    
        
static axis2_status_t
axis2_libxml2_writer_wrapper_push_context(
        axiom_writer_t *writer,
        const axis2_env_t *env);                  
        
static axis2_char_t *
create_key_from_uri_prefix(
        const axis2_env_t *env,
        const axis2_char_t *uri,
        const axis2_char_t *prefix);
  
  
static  axis2_status_t
axis2_libxml2_writer_wrapper_set_default_lang_namespace(
        axiom_writer_t *writer,
        const axis2_env_t *env);
                                                 
static axis2_char_t* 
axis2_libxml2_writer_wrapper_find_prefix(
        axiom_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *uri);                                                    

static uri_prefix_element_t* 
axis2_libxml2_writer_wrapper_find_prefix_in_context(
        axis2_array_list_t  *context,
        const axis2_env_t *env,
        axis2_char_t *uri); 
                            
static void
axis2_libxml2_writer_wrapper_init_ops(
        axiom_writer_t *writer);                             
  
/**************************** end function pointers ****************************/




AXIS2_EXTERN axiom_writer_t * AXIS2_CALL
axiom_writer_create(const axis2_env_t *env,
                        axis2_char_t *filename,
                        axis2_char_t *encoding,
                        int is_prefix_default,
                        int compression)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    AXIS2_ENV_CHECK(env, NULL);
    writer_impl = (axis2_libxml2_writer_wrapper_impl_t *)AXIS2_MALLOC(env->allocator,
                   sizeof(axis2_libxml2_writer_wrapper_impl_t));
    if(!writer_impl)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    writer_impl->xml_writer = xmlNewTextWriterFilename(filename, compression);
    
    if(!(writer_impl->xml_writer))
    {
        AXIS2_FREE(env->allocator, writer_impl);
        AXIS2_ERROR_SET(env->error,
                   AXIS2_ERROR_CREATING_XML_STREAM_WRITER, AXIS2_FAILURE);
        return NULL;
                
    }
    writer_impl->buffer = NULL;
    writer_impl->encoding = NULL;
    writer_impl->compression = 0;
    writer_impl->in_empty_element = AXIS2_FALSE;
    writer_impl->in_start_element = AXIS2_FALSE;
    writer_impl->stack = NULL;
    writer_impl->uri_prefix_map = NULL;
    writer_impl->default_lang_namespace = NULL;
    writer_impl->writer.ops = NULL;

    writer_impl->writer_type = AXIS2_XML_PARSER_TYPE_FILE;   
    writer_impl->compression = compression;
 
    if(NULL != encoding)
        writer_impl->encoding = AXIS2_STRDUP(encoding , env);
    else
        writer_impl->encoding = AXIS2_STRDUP(ENCODING, env);
     

    writer_impl->uri_prefix_map = axis2_hash_make(env);
    if(!(writer_impl->uri_prefix_map))
    {
        axis2_libxml2_writer_wrapper_free(&(writer_impl->writer), env);
        AXIS2_ERROR_SET(env->error, 
            AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        
        return NULL;
    }
    writer_impl->stack = axis2_stack_create(env);
    if(!(writer_impl->stack))
    {
        axis2_libxml2_writer_wrapper_free(&(writer_impl->writer), env);
        AXIS2_ERROR_SET(env->error, 
            AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        
        return NULL;
    }
    
    axis2_libxml2_writer_wrapper_set_default_lang_namespace(&(writer_impl->writer), env);
    
    writer_impl->writer.ops = (axiom_writer_ops_t*)AXIS2_MALLOC(env->allocator,
                                    sizeof(axiom_writer_ops_t));
    
    if(!(writer_impl->writer.ops))
    {
        AXIS2_FREE(env->allocator,writer_impl);
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    /* ops */
    axis2_libxml2_writer_wrapper_init_ops(&(writer_impl->writer));
    return &(writer_impl->writer);
}

/*********************** writer create func for file ***************************/

AXIS2_EXTERN axiom_writer_t * AXIS2_CALL
axiom_writer_create_for_memory(const axis2_env_t *env,
                                   axis2_char_t *encoding, 
                                   int is_prefix_default,
                                   int compression,
                           int type)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    AXIS2_ENV_CHECK(env, NULL);
    writer_impl = (axis2_libxml2_writer_wrapper_impl_t *)AXIS2_MALLOC(env->allocator,
                   sizeof(axis2_libxml2_writer_wrapper_impl_t));
    if(!writer_impl)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    
    writer_impl->writer.ops = NULL;
    writer_impl->encoding = NULL;
    writer_impl->buffer = NULL;
   writer_impl->doc = NULL;
    writer_impl->in_empty_element = AXIS2_FALSE;
    writer_impl->in_start_element = AXIS2_FALSE;
    writer_impl->stack = NULL;
    writer_impl->uri_prefix_map = NULL;
    writer_impl->default_lang_namespace = NULL;
    writer_impl->compression = compression;
   
   if (AXIS2_XML_PARSER_TYPE_BUFFER == type)
   {
      writer_impl->writer_type = AXIS2_XML_PARSER_TYPE_BUFFER;
       writer_impl->buffer = xmlBufferCreate();
       if(writer_impl->buffer == NULL)
       {
           axis2_libxml2_writer_wrapper_free(&(writer_impl->writer), env);
           AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
           return NULL;
       }
    
       writer_impl->xml_writer = xmlNewTextWriterMemory(writer_impl->buffer, 0);
   }
   else if (AXIS2_XML_PARSER_TYPE_DOC == type)   
   {
       writer_impl->writer_type = AXIS2_XML_PARSER_TYPE_DOC;
       writer_impl->xml_writer = xmlNewTextWriterDoc(&writer_impl->doc, 0);
   }
   else
   {
      axis2_libxml2_writer_wrapper_free(&(writer_impl->writer), env);
      AXIS2_ERROR_SET(env->error, AXIS2_ERROR_XML_PARSER_INVALID_MEM_TYPE, AXIS2_FAILURE);
      return NULL;
   }
      
    
    
    if(writer_impl->xml_writer == NULL)
    {
        axis2_libxml2_writer_wrapper_free(&(writer_impl->writer), env);
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_CREATING_XML_STREAM_WRITER , AXIS2_FAILURE);
        return NULL;
    }

     if(encoding)
        writer_impl->encoding = AXIS2_STRDUP(encoding , env);
    else
        writer_impl->encoding = AXIS2_STRDUP(ENCODING, env);
     
    
    writer_impl->uri_prefix_map = axis2_hash_make(env);
    if(!(writer_impl->uri_prefix_map))
    {
        axis2_libxml2_writer_wrapper_free(&(writer_impl->writer), env);
        AXIS2_ERROR_SET(env->error, 
            AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        
        return NULL;
    }
    writer_impl->stack = axis2_stack_create(env);
    if(!(writer_impl->stack))
    {
        axis2_libxml2_writer_wrapper_free(&(writer_impl->writer), env);
        AXIS2_ERROR_SET(env->error, 
            AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    
    axis2_libxml2_writer_wrapper_set_default_lang_namespace(&(writer_impl->writer), env);
    
    writer_impl->writer.ops = (axiom_writer_ops_t*)AXIS2_MALLOC(env->allocator,
                                    sizeof(axiom_writer_ops_t));
    if(!(writer_impl->writer.ops))
    {
        axis2_libxml2_writer_wrapper_free(&(writer_impl->writer), env);
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    
    /* ops */
    axis2_libxml2_writer_wrapper_init_ops(&(writer_impl->writer));

    return &(writer_impl->writer);
}


/*******************************************************************************/
static void
axis2_libxml2_writer_wrapper_init_ops(axiom_writer_t *writer)
{
    writer->ops->free = 
            axis2_libxml2_writer_wrapper_free;
    writer->ops->write_start_element = 
            axis2_libxml2_writer_wrapper_write_start_element;
    writer->ops->write_start_element_with_namespace =
            axis2_libxml2_writer_wrapper_write_start_element_with_namespace;
    writer->ops->write_start_element_with_namespace_prefix = 
            axis2_libxml2_writer_wrapper_write_start_element_with_namespace_prefix;
    writer->ops->write_empty_element =
            axis2_libxml2_writer_wrapper_write_empty_element;
    writer->ops->write_empty_element_with_namespace  =
            axis2_libxml2_writer_wrapper_write_empty_element_with_namespace;
    writer->ops->write_empty_element_with_namespace_prefix =
            axis2_libxml2_writer_wrapper_write_empty_element_with_namespace_prefix;
    writer->ops->write_end_element = 
            axis2_libxml2_writer_wrapper_write_end_element;
    writer->ops->write_end_document = 
            axis2_libxml2_writer_wrapper_write_end_document;
    writer->ops->write_attribute = 
            axis2_libxml2_writer_wrapper_write_attribute;
    writer->ops->write_attribute_with_namespace =
            axis2_libxml2_writer_wrapper_write_attribute_with_namespace;
    writer->ops->write_attribute_with_namespace_prefix =
            axis2_libxml2_writer_wrapper_write_attribute_with_namespace_prefix;
    writer->ops->write_namespace = 
            axis2_libxml2_writer_wrapper_write_namespace;
    writer->ops->write_default_namespace =
            axis2_libxml2_writer_wrapper_write_default_namespace;
    writer->ops->write_comment = 
            axis2_libxml2_writer_wrapper_write_comment;
    writer->ops->write_processing_instruction = 
            axis2_libxml2_writer_wrapper_write_processing_instruction;
    writer->ops->write_processing_instruction_data = 
            axis2_libxml2_writer_wrapper_write_processing_instruction_data;
    writer->ops->write_cdata = 
            axis2_libxml2_writer_wrapper_write_cdata;
    writer->ops->write_dtd = 
            axis2_libxml2_writer_wrapper_write_dtd;
    writer->ops->write_entity_ref = 
            axis2_libxml2_writer_wrapper_write_entity_ref;
    writer->ops->write_start_document = 
            axis2_libxml2_writer_wrapper_write_start_document;
    writer->ops->write_start_document_with_version = 
            axis2_libxml2_writer_wrapper_write_start_document_with_version;
    writer->ops->write_start_document_with_version_encoding = 
            axis2_libxml2_writer_wrapper_write_start_document_with_version_encoding;
    writer->ops->write_characters = 
            axis2_libxml2_writer_wrapper_write_characters;
    writer->ops->get_prefix =
            axis2_libxml2_writer_wrapper_get_prefix;
    writer->ops->set_prefix = 
            axis2_libxml2_writer_wrapper_set_prefix;
    writer->ops->set_default_prefix = 
            axis2_libxml2_writer_wrapper_set_default_prefix;
    writer->ops->write_encoded = 
            axis2_libxml2_writer_wrapper_write_encoded;
    writer->ops->get_xml =
            axis2_libxml2_writer_wrapper_get_xml;
    writer->ops->get_type =
            axis2_libxml2_writer_wrapper_get_type;
}


axis2_status_t AXIS2_CALL 
axis2_libxml2_writer_wrapper_free(axiom_writer_t *writer,
                                  const axis2_env_t *env)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    
    if(NULL != writer_impl->buffer)
    {
        xmlBufferFree(writer_impl->buffer);
       writer_impl->buffer = NULL;
    }       
    if(NULL != writer_impl->encoding)
    {
        AXIS2_FREE(env->allocator, writer_impl->encoding);
        writer_impl->encoding = NULL;
    }
    if(NULL != writer_impl->uri_prefix_map)
    {
        axis2_hash_free(writer_impl->uri_prefix_map, env);
        writer_impl->uri_prefix_map = NULL;
    }
    if(NULL != writer_impl->stack)
    {
        AXIS2_STACK_FREE(writer_impl->stack, env);
        writer_impl->stack = NULL;
    }
    if(NULL != writer_impl->default_lang_namespace)
    {
        uri_prefix_element_free(writer_impl->default_lang_namespace, env);
        writer_impl->default_lang_namespace = NULL;
    }
    if(NULL != writer->ops)
    {
        AXIS2_FREE(env->allocator, writer->ops);
        writer->ops = NULL;
    }
    
    
    
    AXIS2_FREE(env->allocator, writer_impl);
    writer_impl = NULL;
    return AXIS2_SUCCESS;
}
        
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_start_element(
                                    axiom_writer_t *writer,
                                    const axis2_env_t *env,
                                    axis2_char_t *localname)
{
    int status = 0;
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname, AXIS2_FAILURE);
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    
    axis2_libxml2_writer_wrapper_push_context(writer, env);
    writer_impl->in_start_element = AXIS2_TRUE;

    status =  xmlTextWriterStartElement(writer_impl->xml_writer,(xmlChar *)localname);
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_WRITING_START_ELEMENT, AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_end_start_element(axiom_writer_t *writer,
                                               const axis2_env_t *env)
{
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    /* nothing to do , 
       it is automatically taken care by the libxml2 writer */
    return AXIS2_SUCCESS;
}
        
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_start_element_with_namespace(
                                        axiom_writer_t *writer,
                                        const axis2_env_t *env,
                                        axis2_char_t *localname,
                                        axis2_char_t *namespace_uri)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    axis2_bool_t declared = AXIS2_FALSE;
    
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error,namespace_uri, AXIS2_FAILURE);
    
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    
    axis2_libxml2_writer_wrapper_push_context(writer, env);
    declared = axis2_libxml2_writer_wrapper_is_namespace_declared(writer, env, namespace_uri);
    
    if(declared == AXIS2_FALSE)
    {
        /** this should be the case all the time */
        axis2_libxml2_writer_wrapper_push(writer, env, namespace_uri, NULL);
        writer_impl->in_start_element = AXIS2_TRUE;
    }
    status = xmlTextWriterStartElementNS(writer_impl->xml_writer
                , NULL, BAD_CAST localname, BAD_CAST namespace_uri);

    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error,
            AXIS2_ERROR_WRITING_START_ELEMENT_WITH_NAMESPACE, AXIS2_FAILURE);
        return AXIS2_FAILURE;            
    }   
    return AXIS2_SUCCESS;    
}
        
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_start_element_with_namespace_prefix(
                                        axiom_writer_t *writer,
                                        const axis2_env_t *env,
                                        axis2_char_t *localname,
                                        axis2_char_t *namespace_uri,
                                        axis2_char_t *prefix)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    axis2_bool_t is_declared = AXIS2_FALSE;
    axis2_char_t *key = NULL;
    
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname,  AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, namespace_uri, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, prefix, AXIS2_FAILURE);
    
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
   
    axis2_libxml2_writer_wrapper_push_context(writer, env);
    writer_impl->in_start_element = AXIS2_TRUE;
    
    key = create_key_from_uri_prefix(env, namespace_uri, prefix);
    
    is_declared = axis2_libxml2_writer_wrapper_is_namespace_declared(writer, env, key);
    
    if(NULL != key)
    {
        AXIS2_FREE(env->allocator, key);
        key = NULL;
    }
    if(is_declared == AXIS2_TRUE)
    {
        status = xmlTextWriterStartElementNS(writer_impl->xml_writer,
                                        BAD_CAST prefix,
                                        BAD_CAST localname, 
                                        BAD_CAST NULL);
    } 
    else
    {
        axis2_libxml2_writer_wrapper_push(writer, env, namespace_uri, prefix);
        
        status = xmlTextWriterStartElementNS(writer_impl->xml_writer,
                                        BAD_CAST prefix,
                                        BAD_CAST localname, 
                                        BAD_CAST namespace_uri);
    
    
    }                                       
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error,
            AXIS2_ERROR_WRITING_START_ELEMENT_WITH_NAMESPACE_PREFIX, AXIS2_FAILURE);
        return AXIS2_FAILURE;            
    }                                        
    return AXIS2_SUCCESS;       
}
                                    
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_empty_element(
                                        axiom_writer_t *writer,
                                        const axis2_env_t *env,
                                        axis2_char_t *localname)
{
    int status = 0;
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname, AXIS2_FAILURE);
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
        
    status =  xmlTextWriterStartElement(writer_impl->xml_writer,(xmlChar *)localname);

    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_WRITING_EMPTY_ELEMENT, AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }
    status =  xmlTextWriterEndElement(writer_impl->xml_writer);
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_WRITING_EMPTY_ELEMENT, AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }
    return AXIS2_SUCCESS;
}
        
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_empty_element_with_namespace(
                                        axiom_writer_t *writer,
                                        const axis2_env_t *env,
                                        axis2_char_t *localname,
                                        axis2_char_t *namespace_uri)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error,namespace_uri, AXIS2_FAILURE);
    
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    
    status = xmlTextWriterStartElementNS(writer_impl->xml_writer
                , NULL, BAD_CAST localname, BAD_CAST namespace_uri);

    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error,
            AXIS2_ERROR_WRITING_EMPTY_ELEMENT_WITH_NAMESPACE, AXIS2_FAILURE);
        return AXIS2_FAILURE;            
    }
    status =  xmlTextWriterEndElement(writer_impl->xml_writer);
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error,
            AXIS2_ERROR_WRITING_EMPTY_ELEMENT_WITH_NAMESPACE, AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }
      
    return AXIS2_SUCCESS;    
}

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_empty_element_with_namespace_prefix(
                                        axiom_writer_t *writer,
                                        const axis2_env_t *env,
                                        axis2_char_t *localname,
                                        axis2_char_t *namespace_uri,
                                        axis2_char_t *prefix)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    axis2_bool_t is_declared = AXIS2_FALSE;
    axis2_char_t *key = NULL;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname,  AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, namespace_uri, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, prefix, AXIS2_FAILURE);
    
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    
    key = create_key_from_uri_prefix(env, namespace_uri, prefix);
    
    is_declared = axis2_libxml2_writer_wrapper_is_namespace_declared(writer, env, key);
    
    if(NULL != key)
    {
        AXIS2_FREE(env->allocator, key);
        key = NULL;
    }
    if(is_declared == AXIS2_TRUE)
    {
        status = xmlTextWriterStartElementNS(writer_impl->xml_writer,
                                        BAD_CAST prefix,
                                        BAD_CAST localname, 
                                        BAD_CAST NULL);
    }
    else
    {
        status = xmlTextWriterStartElementNS(writer_impl->xml_writer,
                                        BAD_CAST prefix,
                                        BAD_CAST localname, 
                                        BAD_CAST namespace_uri);
    }                                    
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error,
            AXIS2_ERROR_WRITING_START_ELEMENT_WITH_NAMESPACE_PREFIX, AXIS2_FAILURE);
        return AXIS2_FAILURE;            
    }                                        
    status =  xmlTextWriterEndElement(writer_impl->xml_writer);
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error,
            AXIS2_ERROR_WRITING_EMPTY_ELEMENT_WITH_NAMESPACE_PREFIX, AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_end_element(axiom_writer_t *writer,
                                               const axis2_env_t *env)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    
    axis2_libxml2_writer_wrapper_pop_context(writer, env);
    
    writer_impl->in_start_element = AXIS2_FALSE;
    
    status = xmlTextWriterFullEndElement(writer_impl->xml_writer);
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error,
                     AXIS2_ERROR_WRITING_END_ELEMENT,
                     AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }
    return AXIS2_SUCCESS;    
}

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_end_document(axiom_writer_t *writer,
                                               const axis2_env_t *env)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
  
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    status =  xmlTextWriterEndDocument(writer_impl->xml_writer);
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error,
                        AXIS2_ERROR_WRITING_END_DOCUMENT,
                        AXIS2_FAILURE);
                        
        return AXIS2_FAILURE;    
    }
    return AXIS2_SUCCESS;    
}

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_attribute(axiom_writer_t *writer,
                                           const axis2_env_t *env,
                                           axis2_char_t *localname,
                                           axis2_char_t *value)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, value, AXIS2_FAILURE);
    
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    status = xmlTextWriterWriteAttribute(writer_impl->xml_writer,
                      BAD_CAST localname, BAD_CAST value);
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error,
                        AXIS2_ERROR_WRITING_ATTRIBUTE,  AXIS2_FAILURE);
                        
        return AXIS2_FAILURE;    
    }
    return AXIS2_SUCCESS;                     
}
                                               
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_attribute_with_namespace(
                                          axiom_writer_t *writer,
                                          const axis2_env_t *env,
                                          axis2_char_t *localname,
                                          axis2_char_t *value,
                                          axis2_char_t *namespace_uri)
{   
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    axis2_bool_t exists = AXIS2_FALSE;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname,  AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, value, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, namespace_uri, AXIS2_FAILURE);
    
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    
    exists = axis2_libxml2_writer_wrapper_is_namespace_declared(writer, env, namespace_uri);

    if(exists == AXIS2_TRUE)
    {
        status = xmlTextWriterWriteAttributeNS(writer_impl->xml_writer,
                        NULL, BAD_CAST localname, BAD_CAST NULL,
                        BAD_CAST value);
    }
    else
    {
        axis2_libxml2_writer_wrapper_push(writer, env, namespace_uri, NULL);
                           
        status = xmlTextWriterWriteAttributeNS(writer_impl->xml_writer,
                        NULL, BAD_CAST localname, BAD_CAST namespace_uri,
                        BAD_CAST value);
    }                
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error,
             AXIS2_ERROR_WRITING_ATTRIBUTE_WITH_NAMESPACE,  AXIS2_FAILURE);
                        
        return AXIS2_FAILURE;    
    }
    return AXIS2_SUCCESS;                   
}
                                          
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_attribute_with_namespace_prefix(
                                          axiom_writer_t *writer,
                                          const axis2_env_t *env,
                                          axis2_char_t *localname,
                                          axis2_char_t *value,
                                          axis2_char_t *namespace_uri,
                                          axis2_char_t *prefix)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    axis2_bool_t is_declared = AXIS2_FALSE;
    axis2_char_t *key = NULL;
    
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname,  AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, value, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, namespace_uri, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, prefix, AXIS2_FAILURE);
        
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    
    key = create_key_from_uri_prefix(env, namespace_uri, prefix);
    
    is_declared = axis2_libxml2_writer_wrapper_is_namespace_declared(writer, env, key);
    if(NULL != key)
    {
        AXIS2_FREE(env->allocator, key);
        key = NULL;
    }
    
    if(is_declared == AXIS2_TRUE)
    {
         status = xmlTextWriterWriteAttributeNS(writer_impl->xml_writer,
                    BAD_CAST prefix , BAD_CAST localname, 
                        BAD_CAST NULL , BAD_CAST value);
    }
    else
    {
        axis2_libxml2_writer_wrapper_push(writer, env, namespace_uri, prefix);
                                
        status = xmlTextWriterWriteAttributeNS(writer_impl->xml_writer,
                    BAD_CAST prefix , BAD_CAST localname, 
                        BAD_CAST namespace_uri , BAD_CAST value);
     
    }              
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error,
             AXIS2_ERROR_WRITING_ATTRIBUTE_WITH_NAMESPACE_PREFIX,  AXIS2_FAILURE);
                        
        return AXIS2_FAILURE;    
    }
    return AXIS2_SUCCESS;                   
}

/** need to work on this */                                         
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_namespace(axiom_writer_t *writer,
                                             const axis2_env_t *env,
                                             axis2_char_t *prefix,
                                             axis2_char_t *namespace_uri)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    int is_declared = AXIS2_FALSE;
    axis2_char_t *key = NULL;
    char *xmlnsprefix = NULL;
    
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, namespace_uri, AXIS2_FAILURE);
    if(AXIS2_STRCMP(namespace_uri, "") == 0)
        return AXIS2_FAILURE;
    
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    
    key = create_key_from_uri_prefix(env, namespace_uri, prefix);
    
    
    is_declared = axis2_libxml2_writer_wrapper_is_namespace_declared(writer, env, key);

    if(NULL != key)
    {
        AXIS2_FREE(env->allocator, key);
        key = NULL;
    }

    if(is_declared == AXIS2_TRUE)
    {
        return AXIS2_SUCCESS;
    }
    else
    {
        axis2_libxml2_writer_wrapper_push(writer, env, namespace_uri, prefix);
        if(NULL != prefix && (AXIS2_STRCMP(prefix,"") != 0))
        {
             
            xmlnsprefix = (axis2_char_t*)AXIS2_MALLOC(env->allocator,
                        (sizeof(char)* (AXIS2_STRLEN(prefix) +7)));
            sprintf(xmlnsprefix,"xmlns:%s",prefix);
        }
        else
        {
            xmlnsprefix = AXIS2_STRDUP("xmlns", env);
        }
        
        status = xmlTextWriterWriteAttribute(writer_impl->xml_writer,
                    BAD_CAST xmlnsprefix, BAD_CAST namespace_uri);
        AXIS2_FREE(env->allocator, xmlnsprefix);
        xmlnsprefix = NULL;
                           
    }
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error,
             AXIS2_ERROR_WRITING_ATTRIBUTE_WITH_NAMESPACE_PREFIX,  AXIS2_FAILURE);
                        
        return AXIS2_FAILURE;    
    }
    
    AXIS2_FREE(env->allocator, xmlnsprefix);
    xmlnsprefix = NULL;
    return AXIS2_SUCCESS;   
}

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_default_namespace
                                            (axiom_writer_t *writer,
                                             const axis2_env_t *env,
                                             axis2_char_t *namespace_uri)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    axis2_bool_t is_declared = AXIS2_FALSE;
    axis2_char_t *xmlns = NULL;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, namespace_uri, AXIS2_FAILURE)
    
    is_declared = axis2_libxml2_writer_wrapper_is_namespace_declared(writer, env, namespace_uri);
 
    if(is_declared == AXIS2_TRUE)
    {
        /* namespace already declared , nothing to do */
        return AXIS2_SUCCESS;
    }
    axis2_libxml2_writer_wrapper_push(writer, env, namespace_uri, NULL);
      
    xmlns = AXIS2_MALLOC(env->allocator, 
            sizeof(axis2_char_t)*(strlen("xmlns")+1));
    sprintf(xmlns,"xmlns");
    
    status = xmlTextWriterWriteAttribute(writer_impl->xml_writer,
                   (const xmlChar *)xmlns , BAD_CAST namespace_uri);
    
    if(NULL != xmlns)
    {
        AXIS2_FREE(env->allocator, xmlns);
        xmlns = NULL;
    }                   
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_WRITING_DEFAULT_NAMESPACE, AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }                   
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_comment(axiom_writer_t *writer,
                                           const axis2_env_t *env,
                                           axis2_char_t *value)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, value, AXIS2_FAILURE);
    
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    status = xmlTextWriterWriteComment(writer_impl->xml_writer,BAD_CAST value);
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error,
             AXIS2_ERROR_WRITING_COMMENT,  AXIS2_FAILURE);
                        
        return AXIS2_FAILURE;    
    }
    return AXIS2_SUCCESS;    
}

                                           
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_processing_instruction(
                                           axiom_writer_t *writer,
                                           const axis2_env_t *env,
                                           axis2_char_t *target)
{   
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, target, AXIS2_FAILURE);
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    
    status = xmlTextWriterStartPI(writer_impl->xml_writer, BAD_CAST target);
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error,
            AXIS2_ERROR_WRITING_PROCESSING_INSTRUCTION, AXIS2_FAILURE);
        return AXIS2_FAILURE;            
    }
    return AXIS2_SUCCESS;    
}    
                                           
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_processing_instruction_data(
                                           axiom_writer_t *writer,
                                           const axis2_env_t *env,
                                           axis2_char_t *target,
                                           axis2_char_t *data)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, target, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, data, AXIS2_FAILURE);
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    
    status = xmlTextWriterWritePI(writer_impl->xml_writer,
                                  BAD_CAST target,
                                  BAD_CAST data);
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error,
            AXIS2_ERROR_WRITING_PROCESSING_INSTRUCTION, AXIS2_FAILURE);
        return AXIS2_FAILURE;            
    }
    return AXIS2_SUCCESS; 
}
                                           
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_cdata(axiom_writer_t *writer,
                                         const axis2_env_t *env,
                                         axis2_char_t *data)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, data, AXIS2_FAILURE);
    
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    
    status = xmlTextWriterWriteCDATA(writer_impl->xml_writer, BAD_CAST data);
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_WRITING_CDATA, AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }
    return AXIS2_SUCCESS;    
}    

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_dtd(axiom_writer_t *writer,
                                         const axis2_env_t *env,
                                         axis2_char_t *dtd)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, dtd, AXIS2_FAILURE);
    
    status = xmlTextWriterStartDTD(writer_impl->xml_writer,
                    BAD_CAST dtd, NULL, NULL);
    if(status < 0)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_WRITING_DTD, AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_entity_ref(
                                         axiom_writer_t *writer,
                                         const axis2_env_t *env,
                                         axis2_char_t *name)
{
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, name, AXIS2_FAILURE);
    printf("axis2_libxml2_writer_wrapper_write_entity_ref not implemented\n");
    return AXIS2_FAILURE;
}    

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_start_document(
                                         axiom_writer_t *writer,
                                         const axis2_env_t *env)
{
    axis2_libxml2_writer_wrapper_impl_t *wrapper_impl = NULL;
    int status = 0;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    
    wrapper_impl = AXIS2_INTF_TO_IMPL(writer);
    status = xmlTextWriterStartDocument(wrapper_impl->xml_writer,
                             NULL, NULL, NULL);
    if(status < 0)
    {   AXIS2_ERROR_SET(env->error,
            AXIS2_ERROR_WRITING_START_DOCUMENT,AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }
    return AXIS2_SUCCESS;        
}    

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_start_document_with_version(
                                         axiom_writer_t *writer,
                                         const axis2_env_t *env,
                                         axis2_char_t *version)
{   
    axis2_libxml2_writer_wrapper_impl_t *wrapper_impl = NULL;
    int status = 0;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, version, AXIS2_FAILURE);
    
    wrapper_impl = AXIS2_INTF_TO_IMPL(writer);
    status = xmlTextWriterStartDocument(wrapper_impl->xml_writer,
                             version , NULL, NULL);
    if(status < 0)
    {   AXIS2_ERROR_SET(env->error,
            AXIS2_ERROR_WRITING_START_DOCUMENT, AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }
    return AXIS2_SUCCESS;
}    

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_start_document_with_version_encoding(
                                         axiom_writer_t *writer,
                                         const axis2_env_t *env,
                                         axis2_char_t *version,
                                         axis2_char_t *encoding)
{
    axis2_libxml2_writer_wrapper_impl_t *wrapper_impl = NULL;
    int status = 0;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    
    wrapper_impl = AXIS2_INTF_TO_IMPL(writer);
    status = xmlTextWriterStartDocument(wrapper_impl->xml_writer,
                              version , encoding , NULL);
    if(status < 0)
    {   AXIS2_ERROR_SET(env->error,
            AXIS2_ERROR_WRITING_START_DOCUMENT, AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }
    return AXIS2_SUCCESS;
}

                                         
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_characters(
                                         axiom_writer_t *writer,
                                         const axis2_env_t *env,
                                         axis2_char_t *text)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int status = 0;
    
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, text, AXIS2_FAILURE); 
    
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    
    status = xmlTextWriterWriteString(writer_impl->xml_writer,
                                      BAD_CAST text);
    if(status < 0)
    {   AXIS2_ERROR_SET(env->error,
            AXIS2_ERROR_WRITING_START_DOCUMENT, AXIS2_FAILURE);
        return AXIS2_FAILURE;
    }
    return AXIS2_SUCCESS;
}    

axis2_char_t* AXIS2_CALL
axis2_libxml2_writer_wrapper_get_prefix(  axiom_writer_t *writer,
                                         const axis2_env_t *env,
                                         axis2_char_t *uri)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    AXIS2_ENV_CHECK( env, NULL);
    AXIS2_PARAM_CHECK(env->error, uri, NULL);
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    if(!uri || AXIS2_STRCMP(uri, "") == 0)
        return NULL;
    return axis2_libxml2_writer_wrapper_find_prefix(writer, env, uri);
}

axis2_status_t AXIS2_CALL 
axis2_libxml2_writer_wrapper_set_prefix( axiom_writer_t *writer,
                                         const axis2_env_t *env,
                                         axis2_char_t *prefix,
                                         axis2_char_t *uri)
{   
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    
    axis2_bool_t is_declared = AXIS2_FALSE;
    axis2_char_t *key = NULL;
    
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, prefix, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, uri, AXIS2_FAILURE);
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    if(AXIS2_STRCMP(uri, "") == 0)
        return AXIS2_FAILURE;
    
    key = create_key_from_uri_prefix(env, uri, prefix);
    
    is_declared = axis2_libxml2_writer_wrapper_is_namespace_declared(writer, env, key);
    if(NULL != key)
    {
        AXIS2_FREE(env->allocator, key);
        key = NULL;
    }
    if(!is_declared)
    {
        return axis2_libxml2_writer_wrapper_push(writer, env, uri, prefix);
    }
    return AXIS2_FAILURE;
}
axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_set_default_prefix(
                                         axiom_writer_t *writer,
                                         const axis2_env_t *env,
                                         axis2_char_t *uri)
{
    axis2_bool_t is_declared = AXIS2_FALSE;
    
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, uri, AXIS2_FAILURE);
    if(AXIS2_STRCMP(uri, "") == 0)
        return AXIS2_FAILURE;
    is_declared = axis2_libxml2_writer_wrapper_is_namespace_declared(writer, env, uri); 
    if(!is_declared)
    {
        return axis2_libxml2_writer_wrapper_push(writer, env, uri, NULL);
    }        
    return AXIS2_FAILURE;
}    

axis2_status_t AXIS2_CALL
axis2_libxml2_writer_wrapper_write_encoded(
                                         axiom_writer_t *writer,
                                         const axis2_env_t *env,
                                         axis2_char_t *text,
                                         int in_attr)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    AXIS2_ENV_CHECK( env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, text, AXIS2_FAILURE);
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    printf("axis2_libxml2_writer_wrapper_write_encoded not implemented\n");
    return AXIS2_FAILURE;    
}

void* AXIS2_CALL
axis2_libxml2_writer_wrapper_get_xml(axiom_writer_t *writer,
                                     const axis2_env_t *env)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    if(writer_impl->xml_writer)
    {
        xmlFreeTextWriter(writer_impl->xml_writer);
        writer_impl->xml_writer = NULL;
    }
    if(writer_impl->writer_type == AXIS2_XML_PARSER_TYPE_BUFFER)
    {
       axis2_char_t *output = NULL;
      
        if(writer_impl->buffer != NULL)
        {
           output = AXIS2_MALLOC(env->allocator,     
                    sizeof(axis2_char_t)*(
                        strlen((const axis2_char_t*)(writer_impl->buffer->content))+1));
            sprintf(output, 
                    ((const axis2_char_t*)(writer_impl->buffer->content)));
        }
      return (void*)output;
    }
   else if (writer_impl->writer_type == AXIS2_XML_PARSER_TYPE_DOC)
   {
      return (void*)writer_impl->doc;
   }
    else if(writer_impl->writer_type == AXIS2_XML_PARSER_TYPE_FILE)
    {
        printf("axis2_libxml2_writer_wrapper_get_xml does not support file writer\n");
    }

    return NULL;   
}

int AXIS2_CALL
axis2_libxml2_writer_wrapper_get_type(axiom_writer_t *writer,
                                     const axis2_env_t *env)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    writer_impl = AXIS2_INTF_TO_IMPL(writer);

   return writer_impl->writer_type;
}

static axis2_status_t
axis2_libxml2_writer_wrapper_pop_context(axiom_writer_t *writer,
                                         const axis2_env_t *env)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    axis2_array_list_t *ns_list = NULL;
    int size = 0;
    int i = 0;
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    
    ns_list = AXIS2_STACK_POP(writer_impl->stack, env);
    if(!ns_list)
        return AXIS2_FAILURE;
            
    size = AXIS2_ARRAY_LIST_SIZE(ns_list, env);
    for(i=0; i < size; i++)
    {
        uri_prefix_element_t *ele = NULL;
        void *value = NULL;
        value = AXIS2_ARRAY_LIST_GET(ns_list, env, i);
        if(NULL != value)
        {
           ele = (uri_prefix_element_t *)value;
           if(NULL != writer_impl->uri_prefix_map && NULL != ele->key)
           {
                void *val = NULL;
                val = axis2_hash_get(writer_impl->uri_prefix_map, ele->key, 
                        AXIS2_HASH_KEY_STRING);
                if(NULL != val)
                {
                    /** this namespace uri and prefix should be removed*/
                    axis2_hash_set(writer_impl->uri_prefix_map, ele->key, 
                        AXIS2_HASH_KEY_STRING, NULL);
                }
            uri_prefix_element_free(ele, env);           
           }
        }
    }
    AXIS2_ARRAY_LIST_FREE(ns_list, env);
    ns_list = NULL;
    return AXIS2_SUCCESS;
}                                         
                                         
static axis2_status_t
axis2_libxml2_writer_wrapper_push(axiom_writer_t *writer, 
                                  const axis2_env_t *env,
                                  const axis2_char_t *uri,
                                  const axis2_char_t *prefix)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    axis2_array_list_t *current_list = NULL;
    axis2_char_t *key = NULL;
    const axis2_char_t *temp_prefix = NULL;
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    if(!prefix || AXIS2_STRCMP(prefix, "") == 0)
    {
        temp_prefix = "default";
    }
    else
    {
        temp_prefix = prefix;
    }
    
    if(NULL != writer_impl->stack)
    {
        current_list = (axis2_array_list_t *)
                AXIS2_STACK_GET(writer_impl->stack, env);
        
        if(NULL != current_list)
        {
            uri_prefix_element_t *ele = NULL;
            key = create_key_from_uri_prefix(env, uri, prefix);
            
            ele = uri_prefix_element_create(env, uri , temp_prefix, prefix,  key);
            if(NULL != key)
            {
                AXIS2_FREE(env->allocator, key);
                key = NULL;
            }
            if(NULL != ele)
            {
                AXIS2_ARRAY_LIST_ADD(current_list, env, ele);
                axis2_hash_set(writer_impl->uri_prefix_map, ele->key, 
                    AXIS2_HASH_KEY_STRING, ele->prefix);
            }
        }
    }
    return AXIS2_SUCCESS;    
}                                  
                                  
static axis2_bool_t
axis2_libxml2_writer_wrapper_is_namespace_declared(axiom_writer_t *writer,
                                             const axis2_env_t *env,
                                             axis2_char_t *key)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FALSE);
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    if(NULL != writer_impl->uri_prefix_map && NULL != key)
    {
        void *ret = NULL;
        ret = axis2_hash_get(writer_impl->uri_prefix_map, key, 
                AXIS2_HASH_KEY_STRING);
        if(NULL != ret)
        {
           return AXIS2_TRUE;
        }
    }
    return AXIS2_FALSE;
} 

static axis2_status_t
uri_prefix_element_free(uri_prefix_element_t *up_element,
                        const axis2_env_t *env)
{
    if(NULL != up_element)
    {
        if(NULL != up_element->uri)
        {
            AXIS2_FREE(env->allocator, up_element->uri);
            up_element->uri = NULL;
        }
        if(NULL != up_element->prefix)
        {
            AXIS2_FREE(env->allocator, up_element->prefix);
            up_element->prefix = NULL;
        }
        if(NULL != up_element->key)
        {
            AXIS2_FREE(env->allocator, up_element->key);
            up_element->key = NULL;
        }
        if(NULL != up_element->real_prefix)
        {
            AXIS2_FREE(env->allocator, up_element->real_prefix);
            up_element->real_prefix = NULL;
        }
     AXIS2_FREE(env->allocator, up_element);
     up_element = NULL;
     return AXIS2_SUCCESS;   
    }
    return AXIS2_FAILURE;
}                        
                                             
static uri_prefix_element_t *
uri_prefix_element_create(const axis2_env_t *env,
                          const axis2_char_t *uri,
                          const axis2_char_t *prefix,
                          const axis2_char_t *real_prefix,
                          const axis2_char_t *key)
{
    uri_prefix_element_t *up_element = NULL;
    up_element = (uri_prefix_element_t *)AXIS2_MALLOC(env->allocator, 
                    sizeof(uri_prefix_element_t));
    
    if(!uri)
        return NULL;
                                
    if(!up_element)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    up_element->key = NULL;
    up_element->prefix = NULL;
    up_element->uri = NULL;
    up_element->real_prefix = NULL;
    
    up_element->uri = AXIS2_STRDUP(uri, env);
    if(!up_element->uri)
    {
        uri_prefix_element_free(up_element, env);
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    up_element->prefix = AXIS2_STRDUP(prefix, env);
    if(NULL != prefix && !up_element->prefix)
    {
        uri_prefix_element_free(up_element, env);
        AXIS2_ERROR_SET(env->error , AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;            
    }
    up_element->key = AXIS2_STRDUP(key, env);
    if(NULL != key  && !up_element->key)
    {
        uri_prefix_element_free(up_element, env);
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    up_element->real_prefix = AXIS2_STRDUP(real_prefix, env);
    
    return up_element;                    
} 

static axis2_status_t
axis2_libxml2_writer_wrapper_push_context(axiom_writer_t *writer,
                                          const axis2_env_t *env)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    if(NULL != writer_impl->stack)
    {
        axis2_array_list_t *array_list = NULL;
        array_list = axis2_array_list_create(env, 10);
        if(NULL != array_list)
        {
            AXIS2_STACK_PUSH(writer_impl->stack, env, array_list);
            return AXIS2_SUCCESS;
        }
    }
    return AXIS2_FAILURE;
}                                                                                                 
static axis2_char_t *
create_key_from_uri_prefix(const axis2_env_t *env,
                           const axis2_char_t *uri,
                           const axis2_char_t *prefix)
{
    axis2_char_t *key = NULL;
    axis2_char_t *temp_val = NULL;
    if(!prefix || AXIS2_STRCMP(prefix, "") == 0)
    {
        key = AXIS2_STRDUP(uri, env);
    }
    else
    {
        temp_val = AXIS2_STRACAT(uri, "|", env);
        key = AXIS2_STRACAT(temp_val, prefix, env);
        AXIS2_FREE(env->allocator, temp_val);
    }
    return key;
} 

static axis2_status_t
axis2_libxml2_writer_wrapper_set_default_lang_namespace(
                            axiom_writer_t *writer,
                            const axis2_env_t *env)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    axis2_char_t *key = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
    key = create_key_from_uri_prefix( env,
             AXIS2_XMLNS_NAMESPACE_URI, AXIS2_XMLNS_PREFIX);        
    
    writer_impl->default_lang_namespace = 
        uri_prefix_element_create(env, AXIS2_XMLNS_NAMESPACE_URI, 
                AXIS2_XMLNS_PREFIX, AXIS2_XMLNS_PREFIX, key);
    if(NULL != key)
    {
        AXIS2_FREE(env->allocator, key);
        key = NULL;
    }
        
    if(NULL != writer_impl->uri_prefix_map)
    {
        axis2_hash_set(writer_impl->uri_prefix_map, 
           writer_impl->default_lang_namespace->key , 
           AXIS2_HASH_KEY_STRING, AXIS2_XMLNS_PREFIX);
    }
    return AXIS2_SUCCESS;
}

static axis2_char_t* 
axis2_libxml2_writer_wrapper_find_prefix(
                            axiom_writer_t *writer,
                            const axis2_env_t *env,
                            axis2_char_t *uri)
{
    axis2_libxml2_writer_wrapper_impl_t *writer_impl = NULL;
    int size = 0;
    int i = 0;
    
    writer_impl = AXIS2_INTF_TO_IMPL(writer);
   
    if(!writer_impl->stack)
        return NULL;
    size = AXIS2_STACK_SIZE(writer_impl->stack, env);
    if(size <= 0)
        return NULL;
    
    for(i = size -1 ; i < 0; i --)
    {
        axis2_array_list_t *context = NULL;
        void *value = NULL;
        value = AXIS2_STACK_GET_AT(writer_impl->stack, env, i);
        if(NULL != value)
        {
            uri_prefix_element_t *up_ele = NULL;
            context = (axis2_array_list_t *)value;
            up_ele = 
            axis2_libxml2_writer_wrapper_find_prefix_in_context(
                    context, env, uri);
            if(NULL != up_ele)
            {
                return up_ele->real_prefix;
            }                    
        }
    }
    return NULL;
} 

static uri_prefix_element_t* 
axis2_libxml2_writer_wrapper_find_prefix_in_context(
                            axis2_array_list_t  *context,
                            const axis2_env_t *env,
                            axis2_char_t *uri)
{
    int size = 0;
    int i = 0;
    if(!context)
        return NULL;
    size = AXIS2_ARRAY_LIST_SIZE(context, env);
    for(i =0; i < size; i++)
    {
        uri_prefix_element_t *ele = NULL;
        void *value = NULL;
        value = AXIS2_ARRAY_LIST_GET(context, env, i);
        if(NULL != value)
        {
            ele = (uri_prefix_element_t*)value;
            if(NULL != ele->uri && AXIS2_STRCMP(uri, ele->uri))
            {
                return ele;
            }
        }
    }
    return NULL;
}                                                                                                                           
