/**
 * @file       src/module-interfaces/id-reader.h
 * @brief      Description of messaging interface for generic ID Reader
 *
 * @note       Documentation generated from this file looks disorganized. TODO!
 */

#ifndef ID_READER_H
#define ID_READER_H

#include "src/module-interfaces.h"
#include "src/message.h"

/**
 * @name MSG_ID_READER_START
 * @{
 */

/**
 * @brief Start polling for cards.
 *
 * Direction: core -> module
 *
 * `message_type_minor`: unused
 *
 * Structure: header only.
 *
 */
#define MSG_ID_READER_START             1

/** @} ------------------------------------------------------------------------------------------ */

/**
 * @name MSG_ID_READER_STOP
 * @{
 */

/**
 * @brief Stop polling for cards.
 *
 * Direction: core -> module
 *
 * Minor: unused
 *
 * Structure: header only.
 */
#define MSG_ID_READER_STOP              2

/** @} ------------------------------------------------------------------------------------------ */

/**
 * @name MSG_ID_READER_SELFTEST
 * @{
 */

/**
 * @brief Perform a self-test.
 *
 * Direction: core -> module
 *
 * Minor: unused
 *
 * Structure: header only.
 */
#define MSG_ID_READER_SELFTEST          3

/** @} ------------------------------------------------------------------------------------------ */

/**
 * @name MSG_ID_READER_SELFTEST_RESULT
 * @{
 */

/**
 * @brief Report a self-test result.
 *
 * Direction: module -> core
 *
 * Minor: #MSG_ID_READER_SELFTEST_RESULT_OK, #MSG_ID_READER_SELFTEST_RESULT_FAIL,
 *        #MSG_ID_READER_SELFTEST_RESULT_BAD_STATE, #MSG_ID_READER_SELFTEST_RESULT_UNSUPPORTED
 *
 * Struture: header only.
 */
#define MSG_ID_READER_SELFTEST_RESULT   4

/**
 * Self-test successful.
 */
#define MSG_ID_READER_SELFTEST_RESULT_OK            0

/**
 * Self-test failed. MSG_ID_READER_FAULT may follow.
 */
#define MSG_ID_READER_SELFTEST_RESULT_FAIL          1

/**
 * Self-test can't be run right now. Try stopping the reader.
 *
 * @note This does not indicate an error condition.
 */
#define MSG_ID_READER_SELFTEST_RESULT_BAD_STATE     2

/**
 * This module does not support self-testing.
 *
 * @note This does not necesarilly indicate an error condition.
 */
#define MSG_ID_READER_SELFTEST_RESULT_UNSUPPORTED   3

/** @} ------------------------------------------------------------------------------------------ */

/**
 * @name MSG_ID_READER_FAULT
 * @{
 */

/**
 * @brief Report a reader failure.
 *
 * Direction: module -> core
 *
 * Minor: MSG_ID_READER_FAULT_HARDWARE, MSG_ID_READER_FAULT_DRIVER
 *
 * Structure: msg_id_reader_fault_t
 */
#define MSG_ID_READER_FAULT             5

typedef struct {
    message_header_t header;
    char error_string[];    /**< null-terminated string describing the error. Core may log it.    */
} msg_id_reader_fault_t;

/** @} ------------------------------------------------------------------------------------------ */

/**
 * @name MSG_ID_READER_RESULT
 * @{
 */

/**
 * @brief Report found cards.
 *
 * Direction: module -> core
 *
 * Minor: number of found cards.
 *
 * Structure: msg_id_reader_result_t
 */
#define MSG_ID_READER_RESULT            6

// Warning: This structure is shared with
//   - reader-proto, message #MSG_READER_PROTO_SEND_ID
typedef struct {
    message_header_t header;

    struct id_t {
        uint8_t id_length;
        uint8_t id_data[10];
    } ids[];                /**< Array of id_t representing IDs of detected cards                 */
} msg_id_reader_result_t;

/** @} ------------------------------------------------------------------------------------------ */

#endif
