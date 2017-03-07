/**
 * @file       src/common-services/logging.h
 * @brief      This file defines logging interface of Deadlock Common Services.
 */

#ifndef COMMON_SERVICES_LOGGING_H
#define COMMON_SERVICES_LOGGING_H

typedef enum {
    DCS_LOG_DEBUG   = 0,
    DCS_LOG_INFO    = 1,
    DCS_LOG_WARNING = 2,
    DCS_LOG_ERROR   = 3
} dcs_log_severity_t;

/**
 * @brief      Initialize the logging subsystem.
 *
 * This initializes the logging subsystem. The flavour may choose one of the following logging
 * techniques:
 *
 *   - NULL logger: goes nowhere.
 *   - ITM logger: uses ARM Instrumentation Trace Macrocell for logging.
 *   - Semihosting logger: uses Semihosting for logging.
 *   - USART logger: uses dedicated serial port for logging.
 *
 * @param[in]  log_level Minimum level of the message that gets logged.
 */
void dcsLogInit(dcs_log_severity_t log_level);

/**
 * @brief      Log a message
 *
 * @param[in]  severity  Severity of the message
 * @param[in]  source    Source of the message (such as a part of DCS, core or some module)
 * @param[in]  message   The message to log
 */
void dcsLog(dcs_log_severity_t severity, const char *source, char *message);

#endif
