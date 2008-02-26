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

#include <woden_wsdl10_svc_element.h>

axis2_status_t AXIS2_CALL
woden_wsdl10_svc_element_resolve_methods(
        woden_wsdl10_svc_element_t *svc_element,
        const axis2_env_t *env,
        axis2_hash_t *methods)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, methods, AXIS2_FAILURE);
    
    svc_element->ops->free = axis2_hash_get(methods, "free", 
            AXIS2_HASH_KEY_STRING);
    svc_element->ops->type = axis2_hash_get(methods, "type", 
            AXIS2_HASH_KEY_STRING);
    svc_element->ops->set_qname = axis2_hash_get(methods,
            "set_qname", AXIS2_HASH_KEY_STRING);
    svc_element->ops->get_qname = axis2_hash_get(methods,
            "get_qname", AXIS2_HASH_KEY_STRING);
    svc_element->ops->set_interface_qname = axis2_hash_get(methods,
            "set_interface_qname", AXIS2_HASH_KEY_STRING);
    svc_element->ops->get_interface_qname = axis2_hash_get(methods,
            "get_interface_qname", AXIS2_HASH_KEY_STRING);
    svc_element->ops->get_interface_element = axis2_hash_get(methods,
            "get_interface_element", AXIS2_HASH_KEY_STRING);
    svc_element->ops->add_endpoint_element = axis2_hash_get(methods,
            "add_endpoint_element", AXIS2_HASH_KEY_STRING);
    svc_element->ops->get_endpoint_elements = axis2_hash_get(methods,
            "get_endpoint_elements", AXIS2_HASH_KEY_STRING);

    return AXIS2_SUCCESS;    
}
