/**
 * @file    module-interfaces.h
 * @brief   This file defines interface module numbers.
 */

#ifndef SRC_MODULE_INTERFACES_H
#define SRC_MODULE_INTERFACES_H

/**
 * `id_reader` interface.
 * @see src/module-interfaces/id-reader.h
 */
#define IFACE_ID_READER              1

/**
 * `basic_lock_unlock_ui` interface.
 * @see src/module-interfaces/basic-lock-unlock-ui.h
 */
#define IFACE_BASIC_LOCK_UNLOCK_UI   2

/**
 * `reader_proto` (Reader <-> Contorller communication) interface.
 * @see src/module-interfaces/reader-proto.h
 */
#define IFACE_READER_PROTO           3

#endif
