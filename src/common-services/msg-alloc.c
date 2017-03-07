/**
 * @file       common-services/msg-alloc.c
 * @brief      Deadlock Common Services - Central Message Allocator
 */

#include "ch.h"
#include "msg-alloc.h"
#include "message.h"


dl_cma_status dcsCmaInit(void *buf, size_t size) {
    // TODO
    return DCS_CMA_ERR;
}

dl_cma_status dcsCmaAlloc(void *allocated_message, size_t msg_size, msg_tag_t tag) {
    // TODO
    return DCS_CMA_ERR;
}

dl_cma_status dcsCmaFree(void* msg) {
    // TODO
    return DCS_CMA_ERR;
}

dl_cma_status dcsCmaFreeAll(msg_tag_t tag) {
    // TODO
    return DCS_CMA_ERR;
}
