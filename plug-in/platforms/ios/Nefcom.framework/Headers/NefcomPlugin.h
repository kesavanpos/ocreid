//
//  NefcomPlugin.h
//  Nefcom
//
//  Created by Federal Authority For Identity and Citizenship on 17/09/19.
//  Copyright © 2019 Federal Authority For Identity and Citizenship. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PluginUtils.h"

NS_ASSUME_NONNULL_BEGIN

// In this header, you should import all the public headers of your framework using statements like #import <grabba/PublicHeader.h>

/****************************************************************************
 * Copyright (C) 2017 by Identity & Citizenship Authority (ICA)             *
 *                                                                          *
 * This file is part of Emirates ID Card Toolkit.                           *
 *                                                                          *
 *   The Toolkit provides functionality to access Emirates ID Card and      *
 *   corressponding online services of ICA Validation Gateway (VG).         *
 *                                                                          *
 ****************************************************************************/

#if defined EIDASDK_EXPORTS
#define EIDASDK_API __declspec(dllexport)
#else
#define EIDASDK_API __declspec(dllexport)
#endif

#if defined __cplusplus
extern "C" {
#endif
    
#ifndef __EIDA_TOOLKIT_PCSC_PLUGIN_H__
#define __EIDA_TOOLKIT_PCSC_PLUGIN_H__
    
    // Plugin interface definitions
    
    /**
     * @brief Initialize the toolkit plugin.
     *
     * @param[in] context Java object containing the application context
     * @param[in] jenv_obj JNI environment of the application of type JNIEnv*
     * @return Return value (0 on success else error code)
     */
    int Plugin_Initialize(
                          void *context
#if defined(ANDROID)
                          , void *jenv_obj
#endif
    );
    
    /**
     * @brief Cleanup the plugin module.
     *
     * @param[in] jenv_obj JNI environment of the application of type JNIEnv*
     * @return Return value (0 on success else error code)
     */
    int Plugin_Cleanup(
#if defined(ANDROID)
                       void *jenv_obj
#endif
    );
    
    /**
     * @brief Gets the list of SmartCard readers connected.
     *
     * @param[out] reader_list List of smart card reader names separated by
     *                         NULL character
     * @param[out] num_bytes Length of the multistring returned in reader_list.
     * @return Return value (0 on success else error code)
     */
    int Plugin_ListReaders(
                           char **reader_list,
                           unsigned int *num_bytes
                           );
    
#if defined(ANDROID)
    /**
     * @brief Gets the list of SmartCard readers connected.
     *
     * @param[out] reader_list List of smart card reader names separated by
     *                         NULL character
     * @param[out] num_bytes Length of the multistring returned in reader_list.
     * @param[in] jenv_obj JNI environment of the application of type JNIEnv*
     * @return Return value (0 on success else error code)
     */
    int Plugin_ListReadersEx(
                             char **reader_list,
                             unsigned int *num_bytes,
                             void *jenv_obj
                             );
#endif
    
    /**
     * @brief Frees the memory buffers allocated by the plugin.
     *
     * @param[in] buffer Pointer to the buffer returned by a previous call to a
     *                   plugin method
     * @return Return value (0 on success else error code)
     */
    int Plugin_FreeMemory(
                          void *buffer
                          );
    
    // Smart Card plugin interface
    
#if defined(ANDROID)
    /**
     * @brief This function is to set the NFC tag received by an Android application
     upon the tapping of ID card on the NFC reader.
     *
     * @param[in] jnfc_tag Java object received by application upon tapping of
     ID card on the NFC reader
     * @param[in] jenv_obj JNI environment of the application of type JNIEnv*
     * @return Return value (0 on success else error code)
     */
    int Plugin_SetNfcTag(
                         void *jnfc_tag,
                         void *jenv_obj
                         );
#endif
    
    /**
     * @brief This function is to establish connection to the smartcard in
     * the specific reader identified by the reader name
     *
     * @param[in] reader Name of the smartcard reader to connect to
     * @param[out] plugin_context The context allocated by the plugin which is
     *                            be passed as the input parameter to the plugin
     *                            functions that require the connection state.
     * @param[in] jenv_obj JNI environment of the application of type JNIEnv*
     * @return Return value (0 on success else error code)
     */
    int Plugin_Connect(
                       char *reader,
                       void **plugin_context
#if defined(ANDROID)
                       , void* jenv_obj
#endif
    );
    
    /**
     * @brief This method is to disconnect an already established connection to
     * smartcard from a previous call to Plugin_Connect
     *
     * @param[in] plugin_context Pointer returned from a successful call to
     *                           Plugin_Connect.
     * @param[in] jenv_obj JNI environment of the application of type JNIEnv*
     * @return Return value (0 on success else error code)
     */
    int Plugin_Disconnect(
                          void *plugin_context
#if defined(ANDROID)
                          , void* jenv_obj
#endif
    );
    
    /**
     * @brief This method is to get the Answer to Reset (ATR) value of a smartcard
     *
     * @param[in] plugin_context Pointer returned from a successful call to
     *                           Plugin_Connect.
     * @param[out] atr_bytes Buffer containing the ATR bytes.
     * @param[out] atr_len Length of the ATR bytes.
     * @param[in] jenv_obj JNI environment of the application of type JNIEnv*
     * @return Return value (0 on success else error code)
     */
    int Plugin_GetATR(
                      void *plugin_context,
                      unsigned char **atr_bytes,
                      unsigned int *atr_len
#if defined(ANDROID)
                      , void* jenv_obj
#endif
    );
    
    /**
     * @brief This method is to execute APDU commands for accessing data from
     * smartcard.
     *
     * @param[in] plugin_context Pointer returned from a successful call to
     *                           Plugin_Connect.
     * @param[in] isocommand Smartcard command in ISO 7816 format
     * @param[in] command_length Length of the SmartCard command
     * @param[out] out_buf Buffer containing the SmartCard response
     * @param[out] out_length Length of the SmartCard response.
     * @param[in] interface_type Smart card connection interface type
     *                           (1 - contact interface / 2 - nfc interface).
     * @param[in] jenv_obj JNI environment of the application of type JNIEnv*
     * @return Return value (0 on success else error code)
     */
    int Plugin_ExecuteCommand(
                              void *plugin_context,
                              unsigned char *isocommand,
                              unsigned int command_length,
                              unsigned char *out_buf,
                              unsigned int *out_length,
                              int interface_type
#if defined(ANDROID)
                              , void* jenv_obj
#endif
    );
    
    // Fingerprint Scanner Plugin Interface
    
    /**
     * @brief This function is to establish connection with the fingerprint sensor
     * associated with the plugin.
     *
     * @param[in] jenv_obj JNI environment of the application of type JNIEnv*
     * @return Return value (0 on success else error code)
     */
    int FP_Plugin_Connect(
#if defined(ANDROID)
                          void* jenv_obj
#endif
    );
    
    /**
     * @brief This function is to disconnect an already established connection from
     * a previous call to FP_Plugin_Connect.
     *
     * @param[in] jenv_obj JNI environment of the application of type JNIEnv*
     * @return Return value (0 on success else error code)
     */
    int FP_Plugin_Disconnect(
#if defined(ANDROID)
                             void* jenv_obj
#endif
    );
    
    /**
     * @brief This function is to capture the fingerprint raw image from the sensor.
     *
     * @param[in] jenv_obj JNI environment of the application of type JNIEnv*
     * @param[in] time_out Fingerprint sensor capture timeout in seconds.
     * @param[out] image Pointer to receive fingerprint raw image data.
     * @return Return value (0 on success else error code)
     */
    int FP_Capture(
#if defined(ANDROID)
                   void* jenv_obj,
#endif
                   int time_out,
                   FTP_IMAGE *image
                   );
    
    /**
     * @brief This function is to apture and convert the fingerprint data as
     * ISO Compact Card template.
     *
     * @param[in] jenv_obj JNI environment of the application of type JNIEnv*
     * @param[in] time_out Fingerprint sensor capture timeout in seconds.
     * @param[out] ftp_template Pointer to receive fingerprint template data.
     * @return Return value (0 on success else error code)
     */
    int FP_CaptureAndConvert(
#if defined(ANDROID)
                             void* jenv_obj,
#endif
                             int time_out,
                             FTP_TEMPLATE *ftp_template
                             );
    
#endif // __EIDA_TOOLKIT_PCSC_PLUGIN_H__
    
    
#if defined __cplusplus
}
#endif

//#endif // EIDA_TOOLKIT_DEVICE_PLUGIN_H_


@interface NefcomPlugin : NSObject

@end

NS_ASSUME_NONNULL_END
