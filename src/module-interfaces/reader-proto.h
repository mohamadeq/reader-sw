/**
 * @file       src/module-interfaces/id-reader.h
 * @brief      Description of messaging interface for module implementing a
 *             Reader <-> Controller communication protocol
 *
 * Message structures used in this interface are guarenteed to be compatible with data structures
 * in Reader <-> Controller protocol v1.
 *
 * @note       Documentation generated from this file looks disorganized. TODO!
 */

#ifndef ID_READER_H
#define ID_READER_H

#include "src/module-interfaces.h"
#include "src/message.h"

/**
 * @name MSG_READER_PROTO_LINK_CHANGE
 * @{
 */

/**
 * @brief Inform the core that the link state has changed
 *
 * Direction: module -> core
 *
 * `message_type_minor`: MSG_READER_PROTO_LINK_CHANGE_DOWN, MSG_READER_PROTO_LINK_CHANGE_UP.
 *
 * Structure: header only.
 *
 * @note       The core may send messages for transmission only after reception of
 *             MSG_READER_PROTO_LINK_CHANGE_UP.
 *
 */
#define MSG_READER_PROTO_LINK_CHANGE 1

/**
 * @brief      The link went down.
 *
 * When the link goes down it means that the module has encountered an unrecoverable communication
 * error and several link resets did not help, the link is simply unusable.
 * All messages to be sent to the Controller were discarded as a result and any new messages
 * will be silently discarded as well.
 */
#define MSG_READER_PROTO_LINK_CHANGE_DOWN  1

/**
 * @brief      The link went up.
 */
#define MSG_READER_PROTO_LINK_CHANGE_UP  2

/** @} ------------------------------------------------------------------------------------------ */

/**
 * @name MSG_READER_PROTO_SEND_ID
 * @{
 */

/**
 * @brief IDs were obtained from the user, send them to the Controller
 *
 * Direction: core -> module
 *
 * `message_type_minor`: number of IDs obtained from the user
 *
 * Structure: msg_id_reader_result_t (from id-reader interface)
 *
 */
#define MSG_READER_PROTO_SEND_ID 2

/** @} ------------------------------------------------------------------------------------------ */

/**
 * @name MSG_READER_PROTO_READER_FAILURE
 * @{
 */

/**
 * @brief Report failure of the Reader to the Controller
 *
 * Direction: core -> module
 *
 * `message_type_minor`: unused
 *
 * Structure: msg_reader_proto_report_failure_t
 *
 */
#define MSG_READER_PROTO_REPORT_FAILURE 3

typedef struct {
    message_header_t header;
    char error_string[];    /**< null-terminated string describing the error.                     */
} msg_reader_proto_report_failure_t;

/** @} ------------------------------------------------------------------------------------------ */

/**
 * @name MSG_READER_PROTO_UI_UPDATE
 * @{
 */

/**
 * @brief Controller wants us to update the UI.
 *
 * Direction: module -> core
 *
 * `message_type_minor`: new UI state
 *
 * Structure: header only.
 *
 */
#define MSG_READER_PROTO_UI_UPDATE 4

#define MSG_READER_PROTO_UI_UPDATE_LOCKED                   0
#define MSG_READER_PROTO_UI_UPDATE_ID_ACCEPTED_UNLOCKED     1
#define MSG_READER_PROTO_UI_UPDATE_ID_REJECTED              2
#define MSG_READER_PROTO_UI_UPDATE_PERMANENTLY_UNLOCKED     3
#define MSG_READER_PROTO_UI_UPDATE_PERMANENTLY_LOCKED       4
#define MSG_READER_PROTO_UI_UPDATE_SYSTEM_FAILURE           5
#define MSG_READER_PROTO_UI_UPDATE_DOOR_OPEN_TOO_LONG       6
#define MSG_READER_PROTO_UI_UPDATE_VADER                    47

/** @} ------------------------------------------------------------------------------------------ */

#endif
