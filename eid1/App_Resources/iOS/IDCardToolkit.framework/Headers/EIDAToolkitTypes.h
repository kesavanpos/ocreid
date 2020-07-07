/****************************************************************************
* Copyright (C) 2017 by Identity & Citizenship Authority (ICA)             *
*                                                                          *
* This file is part of Emirates ID Card Toolkit.                           *
*                                                                          *
*   The Toolkit provides functionality to access Emirates ID Card and      *
*   corressponding online services of ICA Validation Gateway (VG).         *
*                                                                          *
****************************************************************************/

#ifndef EIDA_TOOLKIT_DATA_TYPES_H_
#define EIDA_TOOLKIT_DATA_TYPES_H_

#if __GNUC__ >= 4
#pragma GCC visibility push(hidden)
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef BOOL
#ifdef ARM_WIN
typedef int BOOL;
#endif
#ifndef ARM_WIN
#define BOOL int
#endif
#endif

// Type of the EIDA Toolkit (ET) Status
typedef unsigned int ETSTATUS;

// Return the ETSTATUS individual parts
#define ETSTATUS_CODE(ets)          ((ets) & 0x1FFF)
#define ETSTATUS_SYSTEM_ERROR(ets)  ((((unsigned int)ets >> 13) & 0x1))
#define ETSTATUS_SOURCE_FILE(ets)   ((((unsigned int)ets >> 25) & 0x7F))
#define ETSTATUS_SOURCE_LINE(ets)   ((((unsigned int)ets >> 14) & 0x7FF))

// EIDA toolkit constants
#define MAX_SIZE        256
#define CODE_MAX        16
#define MAX_ATTR_SIZE   64

// This structure defines Card Production Life Cycle (CPLC) information
typedef struct _CPLC_INFO_ {
    unsigned char cplc_0101_data[MAX_SIZE];
    unsigned int cplc_0101_len;
    unsigned char cplc_9F7F_data[MAX_SIZE];
    unsigned int cplc_9F7F_len;
} CPLC_INFO, *PCPLC_INFO;

#if !defined(TOOLKIT_VERIFONE_SUPPORT)

// Enumeration of digital signature levels
typedef enum _SIGNATURE_LEVEL {
    BASELINE_B = 1,
    BASELINE_LT = 2,
    BASELINE_LTA = 3,
    BASELINE_T = 4
} SIGNATURE_LEVEL;

// Enumeration of digital signature packaging
typedef enum _PACKAGING_MODE {
    ENVELOPED = 1,
    ENVELOPING = 2,
    DEATACHED = 3
} PACKAGING_MODE;

// Enumeration of digital signature document type
typedef enum _DOCUMENT_TYPE {
    XADES = 1,
    PADES = 2,
    CADES = 3
} DOCUMENT_TYPE;

// Enumeration of digital signature report type
typedef enum _REPORT_TYPE {
    DETAILED = 1,
    DIAGNOSTIC = 2,
    SIMPLE = 3
} REPORT_TYPE;

// This structure defines signer location
typedef struct _SIGNER_LOCATION {
    char country_code[CODE_MAX];
    char state_or_province[MAX_SIZE];
    char postal_code[CODE_MAX];
    char locality[MAX_SIZE];
    char street[MAX_SIZE];
} SIGNER_LOCATION;

// This structure defines digital signature context
typedef struct _SIGNING_CONTEXT {
    SIGNATURE_LEVEL signature_level;
    PACKAGING_MODE packaging_mode;
    SIGNER_LOCATION location;
    char tsa_url[MAX_SIZE];
    char ocsp_url[MAX_SIZE];
    char cert_path[MAX_SIZE];
    char pin[512];
} SIGNING_CONTEXT;

// Enumeration of signer name position
typedef enum _SIGNER_NAME_POSITION {
    LEFT = 1,
    RIGHT = 2,
    TOP = 3,
    BOTTOM = 4
} SIGNER_NAME_POSITION;

// This structure defines PDF Advanced Electronic Signature (PAdES)
// signing parameters
typedef struct _PADES_SIGN_PARAMS {
    char sign_reason[MAX_SIZE];
    char signer_location[MAX_SIZE];
    char signer_contact_info[MAX_SIZE];
    int signature_xaxis;
    int signature_yaxis;
    char signature_image[MAX_SIZE];
    char font_name[MAX_SIZE];
    char background_color[CODE_MAX];
    char font_color[CODE_MAX];
    int font_size;
    char signature_text[MAX_SIZE];
    int sign_visible;
    SIGNER_NAME_POSITION name_position;
    int page_number;
} PADES_SIGN_PARAMS;

// This structure defines digital signature verification context
typedef struct _VERIFICATION_CONTEXT {
    char ocsp_url[MAX_SIZE];
    char cert_path[MAX_SIZE];
    REPORT_TYPE report_type;
    BOOL is_deattached;
} VERIFICATION_CONTEXT;

// This structure defines VG response attributes
typedef struct _VGRESPONSE_DATA {
    char service[MAX_SIZE];
    char action[MAX_SIZE];
    char request_id[MAX_SIZE];
    char nonce[MAX_SIZE];
    char correlation_id[MAX_SIZE];
    char csn[MAX_SIZE];
    char cardnumber[MAX_SIZE];
    char idnumber[MAX_SIZE];
    char time_stamp[MAX_SIZE];
    int validity_interval;
} VGRESPONSE_DATA;

// This structure defines MRZ fields
typedef struct _MRZ_DATA {
    char document_type[CODE_MAX];
    char issued_country[CODE_MAX];
    char cardnumber[CODE_MAX];
    char idnumber[CODE_MAX];
    char date_of_birth[CODE_MAX];
    char gender[CODE_MAX];
    char card_expiry_date[CODE_MAX];
    char nationality[CODE_MAX];
    char fullname[32];
} MRZ_DATA;

// Enumeration of public data EF's
typedef enum _PUBLIC_DATA_EF_TYPE {
    IDN_CN = 1,
    ROOT_CERTIFICATE = 2,
    NON_MODIFIABLE_DATA = 3,
    MODIFIABLE_DATA = 4,
    PHOTOGRAPHY = 5,
    SIGNATURE_IMAGE = 6,
    HOME_ADDRESS = 7,
    WORK_ADDRESS = 8
} PUBLIC_DATA_EF_TYPE;
#endif

// This structure represents public data information read
// from Emirates ID card.
typedef struct _PUBLIC_DATA_OBJ {
    char id_number[MAX_ATTR_SIZE];
    char card_number[MAX_ATTR_SIZE];
    char expiry_date[MAX_ATTR_SIZE];
    char fullname_arabic[MAX_ATTR_SIZE];
    char fullname_english[MAX_ATTR_SIZE];
    char date_of_birth[MAX_ATTR_SIZE];
    char mobile_phone_number[MAX_ATTR_SIZE];
    char email[MAX_ATTR_SIZE];
    char title_arabic[MAX_ATTR_SIZE];
    char title_english[MAX_ATTR_SIZE];
    char gender[MAX_ATTR_SIZE];
    char csn[MAX_ATTR_SIZE];
} PUBLIC_DATA_OBJ;

// Enumeration of data files to be updated
typedef enum _FILE_TYPE {
    HEALTH_INSURANCE = 0,
    HEALTH_INSURANCE_PROTECTED = 1,
    MOD_DATA = 2,
    HOMEADDRESS = 3,
    WORKADDRESS = 4,
    HEAD_OF_FAMILY = 5,
    WIFE1 = 6,
    WIFE2 = 7,
    WIFE3 = 8,
    WIFE4 = 9,
    CHILD1 = 10,
    CHILD2 = 11,
    CHILD3 = 12,
    CHILD4 = 13,
    CHILD5 = 14,
    CHILD6 = 15,
    CHILD7 = 16,
    CHILD8 = 17,
    CHILD9 = 18,
    CHILD10 = 19,
    CHILD11 = 20,
    CHILD12 = 21,
    CHILD13 = 22,
    CHILD14 = 23,
    CHILD15 = 24,
    CHILD16 = 25,
    CHILD17 = 26,
    CHILD18 = 27,
    CHILD19 = 28,
    CHILD20 = 29,
} FILE_TYPE;

// This structure stores the expiry dates of the service provider
// configuration certificates
typedef struct _CONFIG_CERT_EXPIRY_DATE {
    char config_vg_cert_expiry[MAX_ATTR_SIZE];
    char config_lv_cert_expiry[MAX_ATTR_SIZE];
    char server_tls_cert_expiry[MAX_ATTR_SIZE];
    char config_ag_cert_expiry[MAX_ATTR_SIZE];
    char license_expiry[MAX_ATTR_SIZE];
} CONFIG_CERT_EXPIRY_DATE;

// This structure stores NFC session details
typedef struct _NFC_OBJECT {
    void *session;
    void *tag;
} NFC_OBJECT;

#if __GNUC__ >= 4
#pragma GCC visibility pop
#endif

#endif // EIDA_TOOLKIT_DATA_TYPES_H_
