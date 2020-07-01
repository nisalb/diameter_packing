#include <stdlib.h>
#include <string.h>

#include "avp.h"
#include "msg.h"

#define MSG_VERS_LENGTH 1
#define MSG_LNGT_LENGTH 3
#define MSG_FLAG_LENGTH 1
#define MSG_CODE_LENGTH 3
#define MSG_APPI_LENGTH 4
#define MSG_HOPI_LENGTH 4
#define MSG_E2EI_LENGTH 4

#define MSG_VERS_OFFSET 0
#define MSG_LNGT_OFFSET MSG_VERS_OFFSET + MSG_VERS_LENGTH
#define MSG_FLAG_OFFSET MSG_LNGT_OFFSET + MSG_LNGT_LENGTH
#define MSG_CODE_OFFSET MSG_FLAG_OFFSET + MSG_FLAG_LENGTH
#define MSG_APPI_OFFSET MSG_CODE_OFFSET + MSG_CODE_LENGTH
#define MSG_HOPI_OFFSET MSG_APPI_OFFSET + MSG_APPI_LENGTH
#define MSG_E2EI_OFFSET MSG_HOPI_OFFSET + MSG_HOPI_LENGTH
#define MSG_AVPS_OFFSET MSG_E2EI_OFFSET + MSG_E2EI_LENGTH

#define MSG_HEADER_LENGTH                                                                     \
    MSG_VERS_LENGTH + MSG_LNGT_LENGTH + MSG_FLAG_LENGTH + MSG_CODE_LENGTH + MSG_APPI_LENGTH + \
        MSG_HOPI_LENGTH + MSG_E2EI_LENGTH

struct dm_msg *
msg_new(uint32_t code, uint8_t flags, uint32_t appid, uint32_t hopid, uint32_t e2eid)
{
    struct dm_msg *msg = malloc(sizeof *msg);
    if (msg == NULL)
        return NULL;

    msg->version = DIAMETER_VERSION;
    msg->length = MSG_HEADER_LENGTH;
    msg->flags = flags;
    msg->code = code;
    msg->appid = appid;
    msg->hopid = hopid;
    msg->e2eid = e2eid;

    msg->avps = NULL;

    return msg;
}

void
msg_delete(struct dm_msg *msg)
{
    if (msg) {
        struct dm_avp *p = msg->avps;
        struct dm_avp *next;
        while (p) {
            next = p->sibling;
            avp_delete(p);
            p = next;
        }
        free(msg);
    }
}

void
msg_prepend_avp(struct dm_msg *msg, struct dm_avp *avp)
{
    if (!msg || !avp)
        return;

    avp->sibling = msg->avps;
    msg->avps = avp;
    msg->length += avp_boundary(avp->length);
}

size_t
msg_pack(struct dm_msg *msg, uint8_t **binp)
{
    if (!msg)
        return 0;

    size_t   packlen = msg->length;
    uint8_t *bin = malloc(packlen * sizeof *bin);
    if (bin == NULL)
        return 0;

    memset(bin, 0, packlen);

    set_1byte(bin, MSG_VERS_OFFSET, msg->version);
    set_3bytes(bin, MSG_LNGT_OFFSET, msg->length);
    set_1byte(bin, MSG_FLAG_OFFSET, msg->flags);
    set_3bytes(bin, MSG_CODE_OFFSET, msg->code);
    set_4bytes(bin, MSG_APPI_OFFSET, msg->appid);
    set_4bytes(bin, MSG_HOPI_OFFSET, msg->hopid);
    set_4bytes(bin, MSG_E2EI_OFFSET, msg->e2eid);

    uint8_t *      avpsp = bin + MSG_AVPS_OFFSET;
    uint8_t *      abin = NULL;
    size_t         ablen = 0;
    struct dm_avp *avp = msg->avps;

    while (avp) {
        ablen = avp_pack(avp, &abin);
        memcpy(avpsp, abin, ablen);
        avpsp += ablen;
        free(abin);
        avp = avp->sibling;
    }

    *binp = bin;
    return packlen;
}
