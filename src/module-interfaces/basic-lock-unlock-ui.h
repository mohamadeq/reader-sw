/**
 * @file       src/module-interfaces/basic-lock-unlock-ui.h
 * @brief      Description of messaging interface for basic UI capable of displaying lock states.
 *
 * @note       Documentation generated from this file looks disorganized. TODO!
 */

#ifndef BASIC_LOCK_UNLOCK_UI_H
#define BASIC_LOCK_UNLOCK_UI_H

#include "src/module-interfaces.h"
#include "src/message.h"

/**
 * @name MSG_BASIC_LOCK_UNLOCK_UI_LOCKED
 * @{
 */

/**
 * @brief Inform the user that the door is locked
 *
 * Direction: core -> module
 *
 * `message_type_minor`: unused
 *
 * Structure: header only.
 *
 */
#define MSG_BASIC_LOCK_UNLOCK_UI_LOCKED  1

/** @} ------------------------------------------------------------------------------------------ */

/**
 * @name MSG_BASIC_LOCK_UNLOCK_UI_ACCEPTED_UNLOCKED
 * @{
 */

/**
 * @brief Inform the user that his ID was accepted and the door was unlocked
 *
 * Direction: core -> module
 *
 * `message_type_minor`: unused
 *
 * Structure: header only.
 *
 */
#define MSG_BASIC_LOCK_UNLOCK_UI_ACCEPTED_UNLOCKED  2

/** @} ------------------------------------------------------------------------------------------ */

/**
 * @name MSG_BASIC_LOCK_UNLOCK_UI_REJECTED
 * @{
 */

/**
 * @brief Inform the user that his ID was rejected
 *
 * Direction: core -> module
 *
 * `message_type_minor`: unused
 *
 * Structure: header only.
 *
 */
#define MSG_BASIC_LOCK_UNLOCK_UI_REJECTED  3

/** @} ------------------------------------------------------------------------------------------ */

/**
 * @name MSG_BASIC_LOCK_UNLOCK_UI_PERMANENTLY_UNLOCKED
 * @{
 */

/**
 * @brief Inform the user that the door is permanently unlocked
 *
 * Direction: core -> module
 *
 * `message_type_minor`: unused
 *
 * Structure: header only.
 *
 */
#define MSG_BASIC_LOCK_UNLOCK_UI_PERMANENTLY_UNLOCKED  4

/** @} ------------------------------------------------------------------------------------------ */

/**
 * @name MSG_BASIC_LOCK_UNLOCK_UI_PERMANENTLY_LOCKED
 * @{
 */

/**
 * @brief Inform the user that the door is permanently locked
 *
 * Direction: core -> module
 *
 * `message_type_minor`: unused
 *
 * Structure: header only.
 *
 */
#define MSG_BASIC_LOCK_UNLOCK_UI_PERMANENTLY_LOCKED  5

/** @} ------------------------------------------------------------------------------------------ */

/**
 * @name MSG_BASIC_LOCK_UNLOCK_UI_SYSTEM_FAILURE
 * @{
 */

/**
 * @brief Inform the user of a system failure
 *
 * Direction: core -> module
 *
 * `message_type_minor`: unused
 *
 * Structure: header only.
 *
 */
#define MSG_BASIC_LOCK_UNLOCK_UI_SYSTEM_FAILURE  6

/** @} ------------------------------------------------------------------------------------------ */

/**
 * @name MSG_BASIC_LOCK_UNLOCK_UI_DOOR_OPEN_TOO_LONG
 * @{
 */

/**
 * @brief Inform the user that the door is open for too long
 *
 * Direction: core -> module
 *
 * `message_type_minor`: unused
 *
 * Structure: header only.
 *
 */
#define MSG_BASIC_LOCK_UNLOCK_UI_DOOR_OPEN_TOO_LONG  7

/** @} ------------------------------------------------------------------------------------------ */

/**
 * @name MSG_BASIC_LOCK_UNLOCK_UI_INITIALIZING
 * @{
 */

/**
 * @brief Inform the user that the system is initializing
 *
 * Direction: core -> module
 *
 * `message_type_minor`: unused
 *
 * Structure: header only.
 *
 */
#define MSG_BASIC_LOCK_UNLOCK_UI_INITIALIZING 8

/** @} ------------------------------------------------------------------------------------------ */

/**
 * @name MSG_BASIC_LOCK_UNLOCK_UI_VADER
 * @{
 */

/**
 * @brief Vader.
 *
 * Direction: core -> module
 *
 * `message_type_minor`: unused
 *
 * Structure: header only.
 *
 */
#define MSG_BASIC_LOCK_UNLOCK_UI_VADER  47

/** @} ------------------------------------------------------------------------------------------ */

#endif
