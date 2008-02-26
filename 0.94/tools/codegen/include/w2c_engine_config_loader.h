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
  
#ifndef W2C_ENGINE_CONFIG_LOADER_H
#define W2C_ENGINE_CONFIG_LOADER_H

/**
 * @file w2c_engine_config_loader.h
 * @brief handles Axis2/C w2c config loading
 */

#include <axis2_utils.h>
#include <axis2_hash.h>
#include <w2c_engine_configuration.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup w2c_engine_config_loader handles loading configurations
 * @ingroup w2c_utils
 * @{
 */    

/**
 * set configurations according to the user options.
 * @param env         pointer to environment struct. MUST NOT be NULL
 * @param conf        engine configurations -> derived from options.
 * @param options_map user options
 * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
 */
AXIS2_EXTERN axis2_status_t AXIS2_CALL
w2c_engine_config_loader_load_config( 
    const axis2_env_t *env,
    w2c_engine_configuration_t *conf,
    axis2_hash_t *option_map );


/** @} */

#ifdef __cplusplus
}
#endif

#endif /* W2C_ENGINE_CONFIG_LOADER_H */