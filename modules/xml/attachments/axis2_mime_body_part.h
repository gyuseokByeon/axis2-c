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

#ifndef AXIS2_MIME_BODY_PART_H
#define AXIS2_MIME_BODY_PART_H

/**
 * @file axis2_mime_body_part.h
 * @brief axis2 mime_body_part interface
 */

#include <axis2.h>
#include <axis2_error.h>
#include <axis2_defines.h>
#include <axis2_env.h>
#include <axis2_allocator.h>
#include <axis2_string.h>
#include <axis2_array_list.h>
#include <axis2_handler_desc.h>
#include <axis2_data_handler.h>

#ifdef __cplusplus
extern "C"
{
#endif


/* This should be moved to header file later axis2_defines.h*/    
#define axis2_byte_t char
	
typedef struct axis2_mime_body_part_ops axis2_mime_body_part_ops_t;
typedef struct axis2_mime_body_part axis2_mime_body_part_t;	

/*
      private final DataSource ds;
      private final DataFlavor flavor;
      private CommandMap commandMap;
      private DataContentHandler dch;
*/

/** @defgroup axis2_mime_body_part Flow
  * @ingroup axis2_mime_body_part
  * @{
  */

/** 
 * @brief Flow ops struct
 * Encapsulator struct for ops of axis2_mime_body_part
 */
struct axis2_mime_body_part_ops
{
	axis2_status_t (AXIS2_CALL *add_header)(axis2_mime_body_part_t *mime_body_part, axis2_env_t **env, axis2_char_t *name, axis2_char_t *value); 
	
    axis2_status_t (AXIS2_CALL *set_data_handler)(axis2_mime_body_part_t *mime_body_part, axis2_env_t **env, axis2_data_handler_t *data_handler); 

    axis2_status_t (AXIS2_CALL *write_to)(axis2_mime_body_part_t *mime_body_part, axis2_env_t **env,axis2_byte_t **output_stream, int *output_stream_size, axis2_char_t *ignore_list); 

	/** Deallocate memory
     * @return status code
     */
    axis2_status_t (AXIS2_CALL *free) (axis2_mime_body_part_t *mime_body_part, axis2_env_t **env);
};

/** 
 * @brief Flow struct
 *	Flow  
 */ 
struct axis2_mime_body_part
{
	axis2_mime_body_part_ops_t *ops;
	
};

/**
 * Creates mime_body_part struct
 * @return pointer to newly created mime_body_part
 */
AXIS2_DECLARE(axis2_mime_body_part_t *) 
axis2_mime_body_part_create (axis2_env_t **env);

/*************************** Function macros **********************************/

#define AXIS2_MIME_BODY_PART_FREE(mime_body_part, env) ((mime_body_part)->ops->free (mime_body_part, env))

#define AXIS2_MIME_BODY_PART_ADD_HEADER(mime_body_part, env, name, value) ((mime_body_part)->ops->add_header (mime_body_part, env, name, value))

#define AXIS2_MIME_BODY_PART_SET_DATA_HANDLER(mime_body_part, env, data_handler) ((mime_body_part)->ops->set_data_handler (mime_body_part, env, data_handler))

#define AXIS2_MIME_BODY_WRITE_TO(mime_body_part, env, output_stream, output_stream_size, ignore_list)


/*************************** End of function macros ***************************/

/** @} */

#ifdef __cplusplus
}
#endif
#endif  /* AXIS2_MIME_BODY_PART_H */
