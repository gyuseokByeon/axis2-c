
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
    
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <httpfilt.h>
#include <httpext.h>
    

/* Axis headers */ 
#include <axutil_error_default.h>
#include <axutil_log_default.h>
#include <axutil_thread_pool.h>
#include <axiom_xml_reader.h>
#include <axutil_log.h>
    
#include "axis2_isapi_plugin.h"
    
#include "axis2_iis_worker.h"
#include "axis2_iis_constants.h"
    
#define	AXIS2_IIS_LOG_FILE_TAG		("log_file")
#define AXIS2_IIS_LOG_LEVEL_TAG		("log_level")
#define AXIS2_IIS_REPO_PATH_TAG		("axis2c_home")
#define AXIS2_IIS_EXTENSION_URI_TAG	("extension_uri")
#define AXIS2_IIS_REDIRECT_WORD_TAG	("redirect_uri")
    
#define AXIS2_IIS_LOG_TRACE_VERB	("trace")
#define AXIS2_IIS_LOG_ERROR_VERB	("error")
#define AXIS2_IIS_LOG_INFO_VERB		("info")
#define AXIS2_IIS_LOG_CRITICAL_VERB	("critical")
#define AXIS2_IIS_LOG_WARN_VERB		("warning")
#define AXIS2_IIS_LOG_DEBUG_VERB	("debug")
    
#define MAX_FILE_PATH				256
    
#define REGISTRY_LOCATION			("Software\\Apache Axis2c\\IIS ISAPI Redirector")
static int is_inited = FALSE;






    "/axis2/mod_axis2_IIS.dll\?";


/*
This is a utility functipn for reading configuration data from the registery.
*/ 
static axis2_status_t read_registery_init_data(
    );


/*
Utility function for reading 
*/ 
static axis2_status_t get_registry_config_parameter(
    HKEY hkey,
    
    char *b,
    DWORD sz);


/*
Parse the given string and return the corresponding log_level
*/ 
    axutil_log_levels_t axis2_iis_parse_log_level(char level[]);


/*
This is the entry point for the extention. The filter will redirect a 
given request to this extentiom. 
*/ 
    BOOL WINAPI GetExtensionVersion(HSE_VERSION_INFO * pVer) 
{
    
        // Create the extension version string, and copy string to HSE_VERSION_INFO structure. 
        pVer->dwExtensionVersion =
        MAKELONG(HSE_VERSION_MINOR, HSE_VERSION_MAJOR);
    
        // Copy description string into HSE_VERSION_INFO structure. 
        strcpy(pVer->lpszExtensionDesc, "Apache Axis2c ISAPI Redirector");
    




/*
This is the entri point for every request to the axis2c. The redirected response 
will come here. This method invoke the axis2 engine and build the response result 
and send it.
*/ 
    DWORD WINAPI HttpExtensionProc(LPEXTENSION_CONTROL_BLOCK lpECB) 
{
    
    
    
        
    
    else
        
    




/**
This method initializes the axis2 engine. All the required variables are set to 
their initial values in this method.
*/ 
    axis2_status_t init_axis2() 
{
    
        /*
           These are the varibles required to initialize axis.
         */ 
        axutil_error_t * error = NULL;
    
    
    
    
        // We need to init xml readers before we go into threaded env     
        if (!is_inited)
    {
        
        
        
        
        
        {
            
        
        
        
        {
            
        
        
    
    



{
    



{
    
//  axiom_xml_reader_cleanup();
        
//  AXIS2_IIS_WORKER_FREE(axis2_worker, axutil_env);
        
//  axutil_env_free(axutil_env);
        return TRUE;



{
    
    
        // Should contain "/axis2/"
        ret_url[0] = '\0';
    
        // The url should begin with "/axis2/"
        if (url[0] == '/' && (url[1] == 'a' || url[1] == 'A') 
            &&(url[2] == 'x' || url[2] == 'X') 
            &&(url[3] == 'i' || url[3] == 'I') 
            &&(url[4] == 's' || url[4] == 'S') 
            &&url[5] == '2' && url[6] == '/')
        
    {
        
            // Append the string to redirect the request
            strcpy(ret_url, redirect_word);
        
        
    
    
         &&(url[2] == 'x' || url[2] == 'X') 
         &&(url[3] == 'i' || url[3] == 'I') 
         &&(url[4] == 's' || url[4] == 'S') 
        
    {
        
        
    
    



{
    
    
    
    
    
        RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
                     KEY_READ, &hkey);
    
    {
        
    
    
          (hkey, 
    {
        
    
    
    else
    {
        
    
    
          (hkey, 
    {
        
    
    
    else
    {
        
    
    
          (hkey, 
    {
        
    
    
    



{
    
    {
        
    
    
    {
        
    
    
    {
        
    
    
    {
        
    
    
    {
        
    
    
    {
        
    
    



                                               char *b, DWORD sz) 
{
    
    
    
    
    {
        
    
    
    
