/*
 * Copyright 2004,2005 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain count copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AXIS2_STREAM_H
#define AXIS2_STREAM_H

#include <axis2_allocator.h>

#ifdef __cplusplus
extern "C"
{
#endif

    struct axis2_stream;
    struct axis2_stream_ops;

/**
 * @defgroup axis2_stream Stream
 * @ingroup axis2_util 
 * @{
 */

  /** 
    * \brief Axis2 stream operations struct
    *
    * Encapsulator struct for operations of axis2_stream
    */
  AXIS2_DECLARE_DATA  typedef struct axis2_stream_ops
    {

      /**
       * deletes the stream
       * @return axis2_status_t AXIS2_SUCCESS on success else AXIS2_FAILURE
       */

       axis2_status_t (AXIS2_CALL *free) (struct axis2_stream *stream);
       
      /**
        * reads from stream
        * @param buffer buffer into which the content is to be read
        * @param size size of the buffer
        * @return satus of the operation. AXIS2_SUCCESS on success else AXIS2_FAILURE
        */
        axis2_status_t (AXIS2_CALL *read) (void *buffer
			, size_t count);
		/**
        * writes into stream
        * @param buffer buffer to be written
        * @param size size of the buffer
        * @return satus of the operation. AXIS2_SUCCESS on success else AXIS2_FAILURE
        */
        axis2_status_t (AXIS2_CALL *write) 
			(const void *buffer, size_t count);
		
		/**
		 * open a file for read according to the file options given
		 * @param file_name file to be opened
		 * @param options file options given.
		 * @return status code
		 */ 
		void * (AXIS2_CALL  *file_open)
			(const char *file_name, const char *options);
		
		/**
		 * close a file
		 * @param file_ptr file pointer of the file need to be closed
		 * @return status code
		 */
		axis2_status_t (AXIS2_CALL *file_close) 
				(void *file_ptr);
		
		/** reads a once character from a file
		 * @param file_ptr pointer to the file to be read from
		 * @return char read
		 */
		axis2_char_t (AXIS2_CALL *file_get_char) 
				(void *file_ptr);
		
		/** write a previously read character back to the file stream
		 * @param chr charater to write back
		 * @param file_ptr file pointer from which chr is read previously
		 *        and need to be written back to
		 * @return status code
		 */
		axis2_status_t (AXIS2_CALL *file_unget_char) 
				(const char chr, void *file_ptr);
				
    } axis2_stream_ops_t;

  /** 
    * \brief Axis2 Stream struct
    *
    * Stream is the encapsulating struct for all stream related operations
    */
    typedef struct axis2_stream
    {
        /** Stream related operations */
        struct axis2_stream_ops *ops;
		int axis2_eof;
    } axis2_stream_t;

#define AXIS2_STREAM_FREE(stream) ((stream->ops)->free(stream))

#define AXIS2_STREAM_READ(stream, buffer, count) \
		((stream)->ops->read(buffer, count))
#define AXIS2_STREAM_WRITE(stream, buffer, count) \
		((stream->ops)->write(buffer, count))
#define AXIS2_STREAM_FILE_OPEN(stream, file_name, options) \
		((stream->ops)->file_open(file_name, options))
#define AXIS2_STREAM_FILE_CLOSE(stream, file_ptr) \
		((stream->ops)->file_close(file_ptr))
#define AXIS2_STREAM_FILE_GET_CHAR(stream, file_ptr) \
		((stream->ops)->file_get_char(file_ptr))
#define AXIS2_STREAM_FILE_UNGET_CHAR(stream, chr, file_ptr) \
		((stream->ops)->file_unget_char(chr, file_ptr))	

/** @} */
    
#ifdef __cplusplus
}
#endif

#endif                          /* AXIS2_STREAM_H */
