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

#ifndef AXIS2_OM_NAMESPACE_H
#define AXIS2_OM_NAMESPACE_H

/**
 * @file axis2_om_namespace.h
 * @brief defines axis2_om_namespace data structure,
 *        used for representing XML namespaces in OM
 */

#include <axis2_defines.h>
#include <axis2_env.h>
#include <axis2_om_output.h>

#ifdef __cplusplus
extern "C"
{
#endif

    struct axis2_om_namespace;
    struct axis2_om_namespace_ops;
    
/**
 * @defgroup axis2_om_namespace OM Namespace
 * @ingroup axis2_om 
 * @{
 */

  /** 
    * \brief OM Namespace operations struct
    * Encapsulator struct for operations of axis2_om_namespace
    */
 AXIS2_DECLARE_DATA   typedef struct axis2_om_namespace_ops
    {
      /**
        * Frees given OM namespcae
        * @param om_namespace namespace to be freed.
        * @param env Environment. MUST NOT be NULL.
        * @return satus of the operation. AXIS2_SUCCESS on success else AXIS2_FAILURE.
        */
        axis2_status_t (AXIS2_CALL *free) (struct axis2_om_namespace *om_namespace,
                                           axis2_env_t **env);

      /**
        * Compares two namepsaces
        * @param om_namespace first namespase to be compared
        * @param env Environment. MUST NOT be NULL.
        * @param om_namespace1 second namespace to be compared
        * @return AXIS2_TRUE if the two namespaces are equal,AXIS2_FALSE otherwise
        */
        axis2_bool_t (AXIS2_CALL *equals)(struct axis2_om_namespace *om_namespace,
                                          axis2_env_t **env,
                                          struct axis2_om_namespace *om_namespace1);

      /**
        * Serializes given namespace 
        * @param om_namespace namespace to be serialized.
        * @param env Environment. MUST NOT be NULL.
        * @param om_output OM output handler to be used in serializing
        * @return satus of the operation. AXIS2_SUCCESS on success else AXIS2_FAILURE.
        */
        axis2_status_t (AXIS2_CALL *serialize)(struct axis2_om_namespace *om_namespace,
                                               axis2_env_t **env,
                                               axis2_om_output_t * om_output);
       /**   
        *@param om_namespace pointer to om_namespace struct
        *@param env environment , MUST NOT be NULL.
        *@returns namespace uri , NULL on error
        */
        axis2_char_t* (AXIS2_CALL *get_uri)(struct axis2_om_namespace *om_namespace,
                                            axis2_env_t **env);
       /**   
        *@param om_namespace pointer to om namespace struct
        *@param env  environment, MUST NOT be NULL
        *@return prefix , NULL on error
        */
        axis2_char_t* (AXIS2_CALL *get_prefix)(struct axis2_om_namespace *om_namespace,
                                               axis2_env_t **env);
        /**   
        *@param om_namespace pointer to om namespace struct
        *@param env environment, MUST NOT be NULL.
        *@param uri namespace uri to be set 
        *@returns status of the operation AXIS2_SUCCESS on success, AXIS2_FAILURE on error.
        */
        axis2_status_t (AXIS2_CALL *set_uri)(struct axis2_om_namespace *om_namespace,
                                            axis2_env_t **env,
                                            const axis2_char_t *uri);
        /**   
        *@param om_namespace pointer to om_namespace struct
        *@param env environment struct
        *@param prefix prefix to be set
        *@returns status code of the operation AXIS2_SUCCESS on success,
        *                       AXIS2_FAILURE on error.
        */
        axis2_status_t (AXIS2_CALL *set_prefix)(struct axis2_om_namespace *om_namespace,
                                                axis2_env_t **env,
                                                const axis2_char_t *prefix);

    } axis2_om_namespace_ops_t;

  /** 
    * \brief OM namespace struct
    * Handles the XML namespace in OM
    */
    typedef struct axis2_om_namespace
    {
        /** OM namespace related operations */
        axis2_om_namespace_ops_t *ops;
        
    } axis2_om_namespace_t;

  /**
    * Creates a namespace struct
    * @param uri namespace URI
    * @param prefix namespace prefix
    * @return a pointer to newly created namespace struct
    */
    AXIS2_DECLARE(axis2_om_namespace_t *)
    axis2_om_namespace_create (axis2_env_t **env,
                               const axis2_char_t * uri,
                               const axis2_char_t *prefix);

/** frees given namespace */
#define AXIS2_OM_NAMESPACE_FREE(om_namespace,env) \
        ((om_namespace)->ops->free(om_namespace, env))
        
/** compares the given two namespaces for equality */
#define AXIS2_OM_NAMESPACE_EQUALS(om_namespace, env, om_namespace1) \
        ((om_namespace)->ops->equals(om_namespace, env, om_namespace1))
        
/** serializes given namespace */
#define AXIS2_OM_NAMESPACE_SERIALIZE(om_namespace,env, om_output) \
        ((om_namespace)->ops->serialize(om_namespace, env,om_output))
/** get prefix */        
#define AXIS2_OM_NAMESPACE_GET_PREFIX(om_namespace, env) \
        ((om_namespace)->ops->get_prefix(om_namespace, env))
/** get namespace uri */
#define AXIS2_OM_NAMESPACE_GET_URI(om_namespace, env) \
        ((om_namespace)->ops->get_uri(om_namespace, env))
/** set uri           */
#define AXIS2_OM_NAMESPACE_SET_URI(om_namespace, env, uri) \
        ((om_namespace)->ops->set_uri(om_namespace, env, uri))
/** set prefix        */
#define AXIS2_OM_NAMESPACE_SET_PREFIX(om_namespace, env, prefix) \
        ((om_namespace)->ops->set_prefix(om_namesapce, env, prefix))

/** @} */

#ifdef __cplusplus
}
#endif

#endif                          /* AXIS2_OM_NAMESPACE */
