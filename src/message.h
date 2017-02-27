/**
 * @file       message.h
 * @brief      This file defines common header for messages exchanged between the core and modules.
 */

#ifndef SRC_MESSAGE_H
#define SRC_MESSAGE_H

#include "stdint.h"

typedef struct {
    uint8_t  interface_number;
    uint16_t message_type_major;
    uint8_t  message_type_minor;
} message_header_t;

#endif
