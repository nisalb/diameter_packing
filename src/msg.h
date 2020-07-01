#ifndef MSG_H_INCLUDE
#define MSG_H_INCLUDE

#include <stdint.h>

#include "avp.h"

/* Always 1 by specfication */
#define DIAMETER_VERSION 1

#define MSG_REQ 0x80
#define MSG_PXY 0x40
#define MSG_ERR 0x20
#define MSG_RTR 0x10

#define set_4bytes(STR, IDX, DWORD)          \
    {                                        \
        STR[IDX] = (DWORD >> 24) & 0xFF;     \
        STR[IDX + 1] = (DWORD >> 16) & 0xFF; \
        STR[IDX + 2] = (DWORD >> 8) & 0xFF;  \
        STR[IDX + 3] = DWORD & 0xFF;         \
    }

#define set_3bytes(STR, IDX, TRIPLE)         \
    {                                        \
        STR[IDX] = (TRIPLE >> 16) & 0xFF;    \
        STR[IDX + 1] = (TRIPLE >> 8) & 0xFF; \
        STR[IDX + 2] = TRIPLE & 0xFF;        \
    }

#define set_1byte(STR, IDX, BYTE) \
    {                             \
        STR[IDX] = BYTE & 0xFF;   \
    }

struct dm_msg {
    uint8_t  version;  // always 1
    uint32_t length;   // 3 bytes
    uint8_t  flags;
    uint32_t code;  // 3 bytes
    uint32_t appid;
    uint32_t hopid;
    uint32_t e2eid;

    struct dm_avp *avps;
};

struct dm_msg *msg_new(uint32_t code, uint8_t flags, uint32_t appid, uint32_t hopid,
                       uint32_t e2eid);
void           msg_prepend_avp(struct dm_msg *msg, struct dm_avp *avp);
size_t         msg_pack(struct dm_msg *msg, uint8_t **binp);
void           msg_delete(struct dm_msg *msg);

#endif
