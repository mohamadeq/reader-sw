/**
 * @file       src/msg-alloc.h
 * @brief      This is a Central Message Allocator
 *
 * This firmware has modular architecture (see documentation, section
 * 'Reader Firmware Architecture'). Core and Modules comunnicate by passing Messages.
 *
 * Each message has a life cycle:
 *
 *   - Sender allocates a message of appropriate size using this allocator
 *   - Sender populates the message with data
 *   - Message is sent to the receiver
 *     - One message can be sent to at most one receiver
 *   - Receiver obtains the message and processes its content
 *     - The receiver must treat the message as read only
 *   - Once the receiver is done it deallocates the message using this allocator
 *
 * Therefore the 'responsibility for the message' belongs to the sender up to the point of actually
 * sending the message. The moment the message is enqueued in the inbox receiver is responsible
 * for it.
 *
 * Since modules must be restartable in case of a failure, this allocator also provides a way of
 * tagging allocated messages and can mass-unallocate all messages with a certain tag.
 * This can prevent memory leaks due to lost references to messages when restarting a module.
 *
 * @note       Taggging and mass-unallocation is a planned feature, and is not implemented yet!
 *
 */

#ifndef SRC_MSG_ALLOC_H
#define SRC_MSG_ALLOC_H

#include "ch.h"

typedef msg_tag_t uint32_t;     /**< Type of the message tag                                      */

/**
 * Return codes of the Central Message Allocator functions
 */
typedef enum {
    DL_CMA_OK  = 0,             /**< The requested operation completed successfully               */
    DL_CMA_ERR = 1,             /**< An undefined error occured during this operation             */
    DL_CMA_OOM = 2              /**< Out-of-memory condition                                      */
} dl_cma_status;

/**
 * @brief      Initialize the Central Message Allocator using a pool of static memory.
 *
 * @param[in]  buf   Buffer of statically allocated memory
 * @param[in]  size  Size of the buffer
 *
 * @return     #DL_CMA_OK if CMA was initializes successfully.
 *             #DL_CMA_OOM if the buffer is too small.
 *             #DL_CMA_ERR if other error occured.
 *
 * @note       This function must be called before any other CMA-related function.
 */
dl_cma_status dlCmaInit(void *buf, size_t size);

/**
 * @brief      Allocates a message.
 *
 * @param[out] allocated_message  The allocated message
 * @param[in]  msg_size           The message size
 * @param[in]  tag                The message tag
 *
 * @return     #DL_CMA_OK if the message was allocated.
 *             #DL_CMA_OOM if there is not enough memory.
 *             #DL_CMA_ERR if other error occured.
 *
 * @note       This function is thread-safe.
 * @note       Message tagging is a TODO and @p tag is ignored for now.
 */
dl_cma_status dlCmaAlloc(void *allocated_message, size_t msg_size, msg_tag_t tag);

/**
 * @brief      Frees a message.
 *
 * @param[in]  msg   The message to free
 *
 * @return     #DL_CMA_OK if the message was freed.
 *             #DL_CMA_ERR if other error occured.
 *
 * @note       This function is thread-safe.
 */
dl_cma_status dlCmaFree(void* msg);

/**
 * @brief      Frees all messages tagged with @p tag
 *
 * @param[in]  tag   The tag
 *
 * @return     #DL_CMA_ERR, since this function is not yet implemented.
 *
 * @note       This function is thread-safe.
 * @note       This function is not yet implemented and is a no-op.
 * @note       But it is a thread-safe no-op.
 */
dl_cma_status dlCmaFreeAll(msg_tag_t tag);

#endif
