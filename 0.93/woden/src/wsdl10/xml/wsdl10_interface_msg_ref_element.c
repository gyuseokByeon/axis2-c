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

#include <woden_wsdl10_interface_msg_ref_element.h>

axis2_status_t AXIS2_CALL
woden_wsdl10_interface_msg_ref_element_resolve_methods(
        woden_wsdl10_interface_msg_ref_element_t *interface_msg_ref_element,
        const axis2_env_t *env,
        axis2_hash_t *methods)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, methods, AXIS2_FAILURE);
    
    interface_msg_ref_element->ops->free = axis2_hash_get(methods, "free", 
            AXIS2_HASH_KEY_STRING);
    interface_msg_ref_element->ops->type = axis2_hash_get(methods, "type", 
            AXIS2_HASH_KEY_STRING);

    interface_msg_ref_element->ops->set_qname = 
            axis2_hash_get(methods, "set_qname", 
            AXIS2_HASH_KEY_STRING);

    interface_msg_ref_element->ops->get_qname = 
            axis2_hash_get(methods, "get_qname", 
            AXIS2_HASH_KEY_STRING);

    interface_msg_ref_element->ops->set_msg = 
            axis2_hash_get(methods, "set_msg", 
            AXIS2_HASH_KEY_STRING);

    interface_msg_ref_element->ops->get_msg = 
            axis2_hash_get(methods, "get_msg", 
            AXIS2_HASH_KEY_STRING);

    interface_msg_ref_element->ops->set_msg_qname = 
            axis2_hash_get(methods, "set_msg_qname", 
            AXIS2_HASH_KEY_STRING);

    interface_msg_ref_element->ops->get_msg_qname = 
            axis2_hash_get(methods, "get_msg_qname", 
            AXIS2_HASH_KEY_STRING);

    interface_msg_ref_element->ops->set_direction = 
            axis2_hash_get(methods, "set_direction", 
            AXIS2_HASH_KEY_STRING);

    interface_msg_ref_element->ops->get_direction = 
            axis2_hash_get(methods, "get_direction", 
            AXIS2_HASH_KEY_STRING);

    return AXIS2_SUCCESS;    
}
