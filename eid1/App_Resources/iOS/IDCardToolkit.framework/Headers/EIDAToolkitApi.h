/****************************************************************************
* Copyright (C) 2017 by Identity & Citizenship Authority (ICA)             *
*                                                                          *
* This file is part of Emirates ID Card Toolkit.                           *
*                                                                          *
*   The Toolkit provides functionality to access Emirates ID Card and      *
*   corressponding online services of ICA Validation Gateway (VG).         *
*                                                                          *
****************************************************************************/

#ifndef EIDA_TOOLKIT_API_H_
#define EIDA_TOOLKIT_API_H_

#if __GNUC__ >= 4

#ifdef __cplusplus
#define ETAPI extern "C" __attribute__((visibility("default")))
#else
#define ETAPI __attribute__ ((visibility("default")))
#endif

#else

#ifdef __cplusplus
#define ETAPI extern "C"
#else
#define ETAPI
#endif

#endif

/**
* @brief Initialize the Emirates ID Card Toolkit
*
* @param[in] in_process_mode TRUE if toolkit is used as in-process module
* @param[in] config_params Application specific configuration parameters
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS Initialize(BOOL in_process_mode, char *config_params);

/**
* @brief Cleanup the Emirates ID Card Toolkit
*
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS Cleanup();

/**
* @brief Free a memory buffer allocated by this module
*
* @param[in] buffer Memory buffer to free
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS FreeMemory(void *buffer);

/**
* @brief Get the status message corressponding to an ETSTATUS value
*
* Almost all the Toolkit APIs return the status as an ETSTATUS value.
* This function helps developers to get the text message corressponding
* to the status code.
*
* @param[in] status Toolkit status value
* @return Return value (Pointer to the status message)
*/
ETAPI const char *GetStatusMessage(ETSTATUS status);

#if !defined(TOOLKIT_VERIFONE_SUPPORT)
/**
* @brief Gets the List of readers connected.
*
* @param[out] readers_list Return buffer of readers list.
* @param[out] list_length Readers name list length in bytes.
* @param[out] readers_count Number of reader names in the list.
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS ListReaders(char **readers_list, unsigned int *list_length,
    unsigned int *readers_count);

/**
* @brief Get first reader with Emirates ID Card inserted
*
* @param[in] reader_name Connected reader name
* @param[inout] reader_name_max Reader name length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS GetReaderWithEmiratesID(char *reader_name,
    int *reader_name_max);

/**
* @brief Connect Establish connection with the smartcard in the reader
*
* @param[in] reader_name Smartcard reader name
* @param[out] connection_handle Handle to smartcard connection
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS Connect(char *reader_name, unsigned int *connection_handle);

/**
* @brief Disconnect smartcard session
*
* @param[out] connection_handle Handle to smartcard connection
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS Disconnect(unsigned int connection_handle);

/**
* @brief Prepare service request
*
* @param[in] connection_handle Handle to an Emirates ID Card connection handle
* @param[in] request_id Application random number
* @param[out] request_handle 8-byte request handle encoded in base64 format
* @param[out] request_handle_len Length of the request handle
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS PrepareRequest(unsigned int connection_handle, char *request_id,
    char **request_handle, unsigned int *request_handle_len);

/**
* @brief Registers a device with Validation Gateway (VG) against the
* Service Provider (SP) license
*
* @param[in] user_id Authorised Service Provider (SP) user id ecncypted
* @param[in] password Ecncypted password of the user
* @param[in] device_reference_id Device registration reference number
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS RegisterDevice(char *user_id, char *password,
    char *device_reference_id, char **response, unsigned int *response_len);

/**
* @brief Toolkit API to read public data from the card
*
* This API can be called to retrieve the Emirates ID Card public data.
* Call this API with flags indicating which data is required to be read.
* Choosing to read only the data required can improve the performance compared
* to reading the complete public data every time.
*
* @param[in] connection_handle Emirates ID Card connection handle
* @param[in] request_id Application generated random request ID
* @param[in] non_modifiable_data Flag to read non modifiable data from the card.
* @param[in] modifiable_data Flag to read Modifiable Data from the card.
* @param[in] photography Flag to read photo data from the card.
* @param[in] signature_image Flag to read hand written signature image from the card.
* @param[in] address Flag to read Home and Office address from the card.
* @param[in] validate_signature Flag to perform signature validation.
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS ReadPublicData(unsigned int connection_handle, char *request_id,
    int non_modifiable_data, int modifiable_data, int photography,
    int signature_image, int address, char **response,
    unsigned int *response_len);

/**
* @brief Toolkit API to read family book data from the card
*
* @param[out] pin Emirates ID Card PIN ecnrypted
* @param[out] pin_len The encrypted PIN length
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS ReadFamilyBookData(char *pin, int pin_len, int *attempts_left,
    char **response, unsigned int *response_len);

/**
* @brief Toolkit API to export certificates
*
* @param[in] pin Emirates ID Card PIN ecnrypted
* @param[in] pin_len Length of the encrypted PIN
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (SUCCESS / ERROR codes).
*/
ETAPI ETSTATUS GetPKICertificates(char *pin, unsigned int pin_len,
    int *attempts_left, char **response, unsigned int *response_len);

/**
* @brief Verify certificate using crl
*
* @param[in] crl_path crl path
* @param[in] crl_filetype CRL file type (X509_FILETYPE_PEM = 1/
* X509_FILETYPE_ASN1 = 2)
* @param[in] cert_data Certificate data by which data is signed.
* @param[in] cert_data_len Certificate data length.
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS VerifyCertificateUsingCRL(unsigned char *crl_path,
    unsigned int crl_filetype, unsigned char *cert_data,
    unsigned int cert_data_len);

/**
* @brief This function checks the card status with the help of 
* Validation Gateway (VG)
*
* @param[in] connection_handle Emirates ID Card connection handle
* @param[in] request_id Application random number
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS CheckCardStatus(unsigned int connection_handle,
    char *request_id, char **response, unsigned int *response_len);

/**
* @brief Get stored finger indexes from the Emirates ID Card
*
* @param[in] connection_handle Emirates ID Card connection handle
* @param[in] first_finger_id First finger id
* @param[in] first_finger_index First finger index
* @param[in] second_finger_id Second finger id
* @param[in] second_finger_index Second finger index
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS GetFingerIndex(int connection_handle,
    unsigned char *first_finger_id, unsigned char *first_finger_index,
    unsigned char *second_finger_id, unsigned char *second_finger_index);

/**
* @brief Perform biometric authentication on server (Validation Gateway - VG)
*
* @param[in] connection_handle Emirates ID Card connection handle
* @param[in] request_id Application random number
* @param[in] finger_index Index of finger to be used for bio. authentication
* @param[in] sensor_timeout Fingerprint sensor capture timeout in seconds
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS AuthenticateBiometricOnServer(unsigned int connection_handle,
    char *request_id, unsigned int finger_index, int sensor_timeout,
    char **response, unsigned int *response_len);

/**
* @brief Reset PIN on Emirates ID Card
*
* @param[in] pin New PIN to set on the Emirates ID Card in ecnrypted format
* @param[in] pin_len Length of the encrypted PIN
* @param[in] finger_index Index of finger to be used for bio. authentication
* @param[in] finger_id Finger ID to be used for bio. authentication
* @param[in] sensor_timeout Fingerprint sensor capture timeout in seconds
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS ResetPIN(char *pin, unsigned int pin_len,
    unsigned int finger_index, unsigned int finger_id, int sensor_timeout,
    int *attempts_left);

/**
* @brief Reset PIN Ex on Emirates ID Card
*
* @param[in] pin New PIN to set on the Emirates ID Card in ecnrypted format
* @param[in] pin_len Length of the encrypted PIN
* @param[in] finger_index Index of finger to be used for bio. authentication
* @param[in] finger_id Finger ID to be used for bio. authentication
* @param[in] sensor_timeout Fingerprint sensor capture timeout in seconds
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS ResetPINEx(char *pin, unsigned int pin_len,
    unsigned int finger_index, unsigned int finger_id, int sensor_timeout,
    int *attempts_left, char **response, unsigned int *response_len);

/**
* @brief Toolkit API to unblock Emirates ID card PKI PIN
*
* @param[in] pin Emirates ID Card PIN encrypted
* @param[in] pin_len Length of the encrypted PIN
* @param[in] finger_index Index of finger to be used for bio. authentication
* @param[in] finger_id Finger identifier
* @param[in] sensor_timeout Fingerprint sensor capture timeout in seconds
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS UnblockPIN(char *pin, unsigned int pin_len,
    unsigned int finger_index, unsigned int finger_id, int sensor_timeout,
    int *attempts_left);

/**
* @brief Toolkit API to unblock Emirates ID card PKI PIN
*
* @param[in] pin Emirates ID Card PIN encrypted
* @param[in] pin_len Length of the encrypted PIN
* @param[in] finger_index Index of finger to be used for bio. authentication
* @param[in] finger_id Finger identifier
* @param[in] sensor_timeout Fingerprint sensor capture timeout in seconds
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS UnblockPINEx(char *pin, unsigned int pin_len,
    unsigned int finger_index, unsigned int finger_id, int sensor_timeout,
    int *attempts_left, char **response, unsigned int *response_len);

/**
* @brief Perform Emirates ID Card PKI authentication
*
* @param[in] pin Emirates ID Card PIN enrypted
* @param[in] pin_len Length of the encrypted PIN
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS AuthenticatePKI(char *pin, unsigned int pin_len,
    int *attempts_left, char **response, unsigned int *response_len);

/** @brief Digitally sign data or hash provided
*
* @param[in] data Plain data or hash to sign
* @param[in] data_length Length of plain data or hash provided
* @param[in] data_hash TRUE if hash/FALSE if plain data
* @param[in] pin Emirates ID Card PIN encrypted
* @param[in] pin_len Length of the encrypted PIN
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS SignData(unsigned char *data, unsigned int data_len,
    BOOL data_hash, char* pin, unsigned int pin_len, int *attempts_left,
    char **response, unsigned int *response_len);

/** @brief Digitally sign challenge or hash provided
*
* @param[in] challenge Plain data or hash to sign
* @param[in] challenge_len Length of the challenge
* @param[in] data_hash TRUE if hash/FALSE if plain data
* @param[in] pin Emirates ID Card PIN encrypted
* @param[in] pin_len Length of the encrypted PIN
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS SignChallenge(unsigned char *challenge,
    unsigned int challenge_len, BOOL data_hash, char* pin,
    unsigned int pin_len, int *attempts_left, char **response,
    unsigned int *response_len);

/**
* @brief Verify digital signature
*
* @param[in] data Plain data or hash for which signature is verified
* @param[in] data_len Plain data or hash length
* @param[in] signature Digital signature of the data
* @param[in] signature_len Digital signature length
* @param[in] certificate Certificate data by which data is signed.
* @param[in] certificate_len Certificate data length.
* @param[in] data_hash TRUE if hash/FALSE if plain data.
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS VerifySignature(unsigned char *data, unsigned int data_len,
    unsigned char *signature, unsigned int signature_len,
    unsigned char *certificate, unsigned int certificate_len, BOOL data_hash);

/**
* @brief Set NFC Authentication params for the Emirates ID Card
*
* @param[in] connection_handle Emirates ID card connection handle
* @param[in] card_number Card Number (CN)
* @param[in] date_of_birth Card holder Date of Birth (DoB)
* @param[in] expiry_date Emirates ID Card expiry date
* @param[in] mrz_data Data from the Machine Readable Zone (MRZ) of the card
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS SetNfcAuthenticationParams(int connection_handle,
    char *card_number, char *date_of_birth, char *expiry_date, char *mrz_data);

/** @brief Gets the Card Cerial Number (CSN)
*
* @param[in] connection_handle Emirates ID Card connection handle
* @param[out] csn Card serial number (CSN)
* @param[out] csn_len Card Serial Number (CSN) length
* @return Return value (SUCCESS / ERROR codes).
*/
ETAPI ETSTATUS GetCSN(int connection_handle, char **csn,
    unsigned int *csn_len);

/** @brief Retrieves the interface type from plugin context
*
* @param[in] connection_handle Emirates ID Card connection handle
* @param[out] interface_type Connection interface type.
* @return Return value (SUCCESS / ERROR codes).
*/
ETAPI ETSTATUS GetInterfaceType(int connection_handle, int *interface_type);

/**
* @brief Check if Emirates ID Card is Genuine.
* This function is used only with SAM
*
* @param[in] connection_handle Emirates ID Card connection handle
* @param[in] request_id Application random number
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS IsCardGenuine(unsigned int connection_handle, char *request_id,
    int *attempts_left, char **response, unsigned int *response_len);

/**
* @brief Toolkit API to Get card version
*
* This API can be called to retrieve the Emirates ID Card version number.
*
* @param[in] connection_handle Emirates ID Card connection handle
* @param[out] card_version Emirates ID Card version
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS GetCardVersion(int connection_handle,
    unsigned char *card_version);

/**
* @brief Toolkit API to read Card Production Life Cycle (CPLC)
* data from card
*
* @param[in] connection_handle Handle to an Emirates ID Card connection handle
* @param[out] cplc_info Card Production Life Cycle (CPLC) data
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS GetCPLCData(int connection_handle, CPLC_INFO *cplc_info);

/**
* @brief Get the Toolkit Version
*
* @param[out] major_version EIDAToolkit major version number
* @param[out] minor_version EIDAToolkit minor version number
* @param[out] patch_version EIDAToolkit patch version number
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS GetToolkitVersion(int *major_version, int *minor_version,
    int *patch_version);

#if defined(_WIN32) || defined(_WIN64) || defined(LINUX) || defined(__MACH__)

/**
* @brief Perform digital signing of PDF document following
* PDF Advanced Electronic Signature (PAdES) standard
*
* @param[in] signing_context Toolkit digital signature context
* @param[in] pdf_file_path Path of the input pdf document
* @param[in] signed_pdf_file_path Path of the signed pdf document
* @param[in] pades_params Additional PAdES specific parameters
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS PadesSign(SIGNING_CONTEXT *signing_context, char *pdf_file_path,
    char *signed_pdf_file_path, PADES_SIGN_PARAMS *pades_params,
    int *attempts_left);

/**
* @brief Perform digital signing of PDF document following
* PDF Advanced Electronic Signature (PAdES) standard
*
* @param[in] signing_context Toolkit digital signature context
* @param[in] pdf_file_path Path of the input pdf document
* @param[in] signed_pdf_file_path Path of the signed pdf document
* @param[in] pades_params Additional PAdES specific parameters
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS PadesSignEx(SIGNING_CONTEXT *signing_context,
    char *pdf_file_path, char *signed_pdf_file_path,
    PADES_SIGN_PARAMS *pades_params, int *attempts_left, char **response,
    unsigned int *response_len);

/**
* @brief Perform digital signature verification of PDF document following
* PDF Advanced Electronic Signature (PAdES) standard
*
* @param[in] verification_context Digital signature verification context
* @param[in] pdf_file_path Path of the input pdf document to verify
* @param[out] verification_report Verification report
* @param[out] report_len Verification report length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS PadesVerify(VERIFICATION_CONTEXT *verification_context,
    char *pdf_file_path, char **verification_report, unsigned int *report_len);

/**
* @brief Perform digital signing of XML document following 
* XML Advanced Electronic Signature (XAdES) standard
*
* @param[in] signing_context Toolkit digital signature context
* @param[in] xml_file_path Path of the input xml document
* @param[in] signed_xml_file_path Path of the signed xml document
* @param[out] signature signature data if packaging mode is Detached
* @param[out] signature_len signature data length
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS XadesSign(SIGNING_CONTEXT *signing_context, char *xml_file_path,
    char *signed_xml_file_path, unsigned char **signature,
    unsigned int *signature_len, int *attempts_left);

/**
* @brief Perform digital signing of XML document following
* XML Advanced Electronic Signature (XAdES) standard
*
* @param[in] signing_context Toolkit digital signature context
* @param[in] xml_file_path Path of the input xml document
* @param[in] signed_xml_file_path Path of the signed xml document
* @param[out] signature signature data if packaging mode is Detached
* @param[out] signature_len signature data length
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS XadesSignEx(SIGNING_CONTEXT *signing_context,
    char *xml_file_path, char *signed_xml_file_path, unsigned char **signature,
    unsigned int *signature_len, int *attempts_left, char **response,
    unsigned int *response_len);

/**
* @brief Perform digital signature verification of XML document following
* XML Advanced Electronic Signature (XAdES) standard
*
* @param[in] verification_context Digital signature verification context
* @param[in] xml_file_path Path of the input xml document to verify
* @param[in] signature signature data if packaging mode is Detached 
* @param[in] signature_len signature data length
* @param[out] verification_report Verification report
* @param[out] report_len Verification report length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS XadesVerify(VERIFICATION_CONTEXT *verification_context,
    char *xml_file_path, unsigned char *signature, unsigned int signature_len,
    char **verification_report, unsigned int *report_len);

/**
* @brief Perform digital signing of document following 
* CMS Advanced Electronic Signature (CAdES) standard
*
* @param[in] signature_context Toolkit digital signature context
* @param[in] input_document_path Path of the input document
* @param[out] signature signature data
* @param[out] signature_len signature data length
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS CadesSign(SIGNING_CONTEXT *signing_context,
    char *input_document_path, unsigned char **signature,
    unsigned int *signature_len, int *attempts_left);

/**
* @brief Perform digital signing of document following
* CMS Advanced Electronic Signature (CAdES) standard
*
* @param[in] signature_context Toolkit digital signature context
* @param[in] input_document_path Path of the input document
* @param[out] signature signature data
* @param[out] signature_len signature data length
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS CadesSignEx(SIGNING_CONTEXT *signing_context,
    char *input_document_path, unsigned char **signature,
    unsigned int *signature_len, int *attempts_left, char **response,
    unsigned int *response_len);

/**
* @brief Perform digital signature verification of document following
* CMS Advanced Electronic Signature (CAdES) standard
*
* @param[in] verification_context Digital signature verification context
* @param[in] input_document_path Path of the input document to verify
* @param[in] signature CAdES signature of the input document
* @param[in] signature_len Length of the signature bytes
* @param[out] verification_report Verification report
* @param[out] report_len Verification report length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS CadesVerify(VERIFICATION_CONTEXT *verification_context,
    char *input_document_path, unsigned char *signature,
    unsigned int signature_len, char **verification_report,
    unsigned int *report_len);
#endif

/**
* @brief Toolkit API to Get Device ID
*
* This API can be called to retrieve the Device ID.
*
* @param[out] device_id Unique Device ID string
* @param[out] device_id_len Device ID string length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS GetDeviceID(char **device_id, unsigned int *device_id_len);

/**
* @brief Perform biometric authentication on the card
*
* @param[in] connection_handle Emirates ID Card connection handle
* @param[in] request_id Application random number
* @param[in] finger_index Finger index to be used for biometric authentication
* @param[in] finger_id Finger ID to be used for biometric authentication
* @param[in] sensor_timeout Fingerprint sensor capture timeout in seconds
* @param[out] attempts_left Number of attempts left before the card is blocked.
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS AuthenticateBiometricOnCard(unsigned int connection_handle,
    char *request_id, unsigned int finger_index, unsigned int finger_id,
    int sensor_timeout, int *attempts_left, char **response,
    unsigned int *response_len);

/** @brief Retrieves the SecureMessaging mode
*
* @param[out] sm_mode Type of Secure Messaging mode
* @return Return value (SUCCESS / ERROR codes).
*/
ETAPI ETSTATUS GetSMMode(int *sm_mode);

/** @brief Get data protection key
*
* @param[out] data_protection_key Data protection public key
* @param[out] key_len Data protection public key length
* @param[out] modulus Data protection public key modulus
* @param[out] modulus_len Data protection public key modulus length
* @param[out] exponent Data protection public key public exponent
* @param[out] exponent_len Data protection public key public exponent length
* @return Return value (SUCCESS / ERROR codes).
*/
ETAPI ETSTATUS GetDataProtectionKey(unsigned char **data_protection_key,
    unsigned int *key_len, char **modulus, unsigned int *modulus_len,
    char **exponent, unsigned int *exponent_len);

/**
* @brief Verify certificate using OCSP
*
* @param[in] ocsp_url OCSP url
* @param[in] cert_data Certificate data for which status is checked.
* @param[in] cert_data_len Certificate data length.
* @param[in] issuer_cert_data Issuer Certificate data.
* @param[in] issuer_cert_len Issuer Certificate data length.
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS VerifyCertificateUsingOCSP(char *ocsp_url,
    unsigned char *cert_data, unsigned int cert_data_len,
    unsigned char *issuer_cert_data, unsigned int issuer_cert_len);

/**
* @brief EIDA Toolkit API to verify Toolkit response
*
* @param[in] in_process_mode TRUE if toolkit is used as in-process module
* @param[in] vg_response Validation Gateway (VG) response
* @param[in] cert_data Validation Gateway (VG) response signing certificate
* @param[in] cert_data_len Certificate data length
* @param[in] cert_chain Validation Gateway (VG) response signing
*            certificate chain
* @param[in] cert_chain_len Certificate chain length
* @param[in] chain_validation Flag (TRUE/FALSE) indicating chain validation
*            is required or not
* @param[out] status Signature validation status(-1 not set / 1 set)
* @param[out] error_message Error message
* @param[out] error_message_len Length of error message
* @param[out] response_data Parsed VG response attributes
* @return Return value (SUCCESS / ERROR codes).
*/
ETAPI ETSTATUS ValidateToolkitResponse(BOOL in_process_mode, char *vg_response,
    unsigned char *cert_data, unsigned int cert_data_len,
    unsigned char *cert_chain, unsigned int cert_chain_len,
    BOOL chain_validation, int *status, char **error_message,
    unsigned int *error_message_len, VGRESPONSE_DATA *response_data);

#if defined(_WIN32) || defined(_WIN64) || defined(LINUX) || defined(__MACH__) && !defined(ARM_WIN)
/**
* @brief Attach a Java environment to the Toolkit
*
* @param[in] jenv_obj Pointer to Java environment object
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS AttachJEnv(void *jenv_obj);
#endif

#if defined(ANDROID)
/**
* @brief Set device context
*
* @param[in] context Device context object
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETSTATUS SetContext(void *context);
#endif

/**
* @brief Parse MRZ data
*
* @param[in] mrz Data from the Machine Readable Zone (MRZ) of the card
* @param[out] mrz_data Parsed MRZ string attributes
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS ParseMRZData(char *mrz, MRZ_DATA *mrz_data);

/**
* @brief Perform check card status and biometric authentication on server
* (Validation Gateway - VG)
*
* @param[in] connection_handle Emirates ID Card connection handle
* @param[in] request_id Application random number
* @param[in] finger_index Index of finger to be used for bio. authentication
* @param[in] sensor_timeout Fingerprint sensor capture timeout in seconds
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS AuthenticateCardAndBiometric(unsigned int connection_handle,
    char *request_id, unsigned int finger_index, int sensor_timeout,
    char **response, unsigned int *response_len);

/**
* @brief Toolkit API to read public data EF from the Emirates ID Card
*
* This API can be called to retrieve the Emirates ID Card public data EF
* Call this API with enumeration indicating which data is required to be read.
*
* @param[in] connection_handle Emirates ID Card connection handle
* @param[in] public_data_ef_type Enumeration of public data EF type to read
* corresponding data from Emirates ID Card
* @param[in] validate_signature Flag to perform EF signature validation.
* @param[out] ef_data Pointer to receive EF data
* @param[out] ef_data_length EF data length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS ReadPublicDataEF(unsigned int connection_handle,
    PUBLIC_DATA_EF_TYPE public_data_ef_type, BOOL validate_signature,
    unsigned char **ef_data, unsigned int *ef_data_length);

/**
* @brief Get license expiry date
*
* @param[out] expiry_date Toolkit license expiry date
* @param[out] expiry_date_len Toolkit license expiry date length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS GetLicenseExpiryDate(char **expiry_date,
    unsigned int *expiry_date_len);

/**
* @brief Get config certificate expiry date
*
* @param[out] config_cert_expiry_date Struture to receive
* config certificate expiry date
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS GetConfigCertificateExpiryDate(
    CONFIG_CERT_EXPIRY_DATE *config_cert_expiry_date);

/**
* @brief Set NFC tag object
*
* @param[in] nfc_object Struture for passing NFC tag object
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS SetNFCTag(void *nfc_object);

/**
* @brief EIDA Toolkit API to Personalise new containers
* and for updating file data to card
*
* @param[in] connection_handle Emirates ID Card connection handle
* @param[in] file_type Type of file to update
* @param[in] request_id Application random number
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS UpdateData(unsigned int connection_handle, FILE_TYPE file_type,
    char *request_id, char **response, unsigned int *response_len);

/**
* @brief EIDA Toolkit API to read file data from card
*
* @param[in] connection_handle Emirates ID Card connection handle
* @param[in] file_type Type of file to read data from
* @param[in] request_id Application random number
* @param[out] response Pointer to receive the response
* @param[out] response_len Response length
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS ReadData(unsigned int connection_handle,
    FILE_TYPE file_type, char *request_id, char **response,
    unsigned int *response_len);

#endif

/**
* @brief Connect Establish connection with the smartcard in the reader
* for Verifone
*
* @param[in] reader_name Smartcard reader name
* @param[out] connection_handle Handle to smartcard connection
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS ConnectEx(char *reader_name, unsigned int *connection_handle);

/**
* @brief Disconnect smartcard session for Verifone
*
* @param[out] connection_handle Handle to smartcard connection
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS DisconnectEx(unsigned int connection_handle);

/**
* @brief Toolkit API to read public data from the card for Verifone
*
* This API can be called to retrieve the Emirates ID Card public data.
* Call this API with flags indicating which data is required to be read.
* Choosing to read only the data required can improve the performance compared
* to reading the complete public data every time.
*
* @param[in] connection_handle Emirates ID Card connection handle
* @param[out] PUBLIC_DATA_OBJ Structure to receive public data attributes
* @return Return value (ETSTATUS_SUCCESS on success else error code)
*/
ETAPI ETSTATUS ReadPublicDataEx(unsigned int connection_handle,
    PUBLIC_DATA_OBJ *public_data_obj);

#endif // EIDA_TOOLKIT_API_H_
