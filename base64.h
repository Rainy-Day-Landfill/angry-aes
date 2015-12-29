/*********************************************************************
* Filename:   base64.h
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Defines the API for the corresponding Base64 implementation.
*********************************************************************/

#ifndef BASE64_H
#define BASE64_H

/*************************** HEADER FILES ***************************/
#include <stddef.h>

/**************************** DATA TYPES ****************************/
typedef unsigned char BYTE;             // 8-bit byte

/*********************** FUNCTION DECLARATIONS **********************/
// Returns the size of the output. If called with out = NULL, will just return
// the size of what the output would have been (without a terminating NULL).
size_t base64_encode(BYTE out[], const BYTE in[]);

// Returns the size of the output. If called with out = NULL, will just return
// the size of what the output would have been (without a terminating NULL).
size_t base64_decode(BYTE out[], const BYTE in[]);

#endif   // BASE64_H
