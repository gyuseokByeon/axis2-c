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


#ifndef AXIS2_PLATFORM_AUTOSENSE_H
#define AXIS2_PLATFORM_AUTOSENSE_H

/**
  * @file axis2_platform_auto_sense.h
  * @brief axis2 platform auto sense
  */

#ifdef __cplusplus
extern "C"
{
#endif

/** @defgroup axis2_platform_auto_sense 
 * @ingroup axis2_platforms
 * @{
 */

#if defined( WIN32 )
	#include <windows/axis2_windows.h>
	#include <windows/axis2_dir_windows.h>
	#include <windows/axis2_uuid_gen_windows.h>
	#include <windows/axis2_getopt_windows.h>
#elif defined ( __OS400__  )
  #include <os400/axis2_os400.h>
#elif defined ( AIX )
  #include <aix/aix.h>
#elif defined ( HPUX )
  #include <hp-ux/axis2_ht-ux.h>
#else
  #include <platforms/unix/axis2_unix.h>
#endif

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* AXIS2_PLATFORM_AUTOSENSE_H */