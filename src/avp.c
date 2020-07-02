#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avp.h"
#include "msg.h"

#define AVP_CODE_LENGTH 4
#define AVP_FLAG_LENGTH 1
#define AVP_LNGT_LENGTH 3
#define AVP_VNID_LENGTH 4

#define AVP_CODE_OFFSET 0
#define AVP_FLAG_OFFSET AVP_CODE_OFFSET + AVP_CODE_LENGTH
#define AVP_LNGT_OFFSET AVP_FLAG_OFFSET + AVP_FLAG_LENGTH
#define AVP_VNID_OFFSET AVP_LNGT_OFFSET + AVP_LNGT_LENGTH
#define AVP_DATA_OFFSET AVP_LNGT_OFFSET + AVP_LNGT_LENGTH
#define AVP_VDTA_OFFSET AVP_VNID_OFFSET + AVP_VNID_LENGTH

static int
is_little_endian()
{
    // workaround for __BYTE_ORDER__ in older compilers
    volatile uint32_t i = 0x01234567;
    return (*((uint8_t *) (&i))) == 0x67;
}

static int
xtoi(int x)
{
    if (isalpha(x))
        x = tolower(x);

    if (isdigit(x))
        return x - '0';
    else if (isxdigit(x))
        return 10 + x - 'a';

    return -1;
}

size_t
i32tobin(uint32_t val, uint8_t **binp)
{
    uint8_t *bin = malloc(4 * sizeof *bin);
    if (bin == NULL)
        return 0;

    uint32_t i = val;
    uint8_t *p = (uint8_t *) &i;

    //#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    if (is_little_endian()) {
        bin[0] = p[3];
        bin[1] = p[2];
        bin[2] = p[1];
        bin[3] = p[0];
    } else {
        //#else
        bin[0] = p[0];
        bin[1] = p[1];
        bin[2] = p[2];
        bin[3] = p[3];
    }
    //#endif

    *binp = bin;
    return 4;
}

size_t
hextobin(char *hex, uint8_t **binp)
{
    if (hex == NULL)
        return 0;

    size_t xdigits = 0;
    char * p = hex;
    int    add_lead_zero = 0;

    while (*p)
        if (isxdigit(*p++))
            xdigits++;
    if (xdigits % 2 != 0) {
        add_lead_zero = 1;
        xdigits++;
    }

    char *cleaned = malloc(xdigits * sizeof *cleaned);
    if (cleaned == NULL)
        return 0;

    char *q = cleaned;
    if (add_lead_zero)
        *q++ = '0';

    p = hex;
    while (*p) {
        if (isxdigit(*p)) {
            *q = *p;
            q++;
        }
        p++;
    }

    size_t   nbytes = xdigits / 2;
    uint8_t *bin = malloc(nbytes * sizeof *bin);
    if (bin == NULL) {
        free(cleaned);
        return 0;
    }

    size_t i, j;
    for (i = 0, j = 0; i < xdigits; i += 2, j++) {
        bin[j] = xtoi(cleaned[i]) * 16 + xtoi(cleaned[i + 1]);
    }

    free(cleaned);
    *binp = bin;
    return nbytes;
}

size_t
asciitobin(char *str, uint8_t **binp)
{
    if (str == NULL)
        return 0;

    size_t   length = strlen(str);
    uint8_t *bin = malloc((length + 1) * sizeof *bin);
    if (bin == NULL)
        return 0;

    memset(bin, 0, length + 1);
    memcpy(bin, str, length);

    *binp = bin;
    return length;
}

struct dm_avp *
avp_new(uint32_t code, uint8_t flags, uint8_t *data, size_t datasz)
{
    struct dm_avp *avp = malloc(sizeof *avp);
    if (avp == NULL)
        return NULL;

    avp->code = code;
    avp->flags = flags;
    avp->vnid = NO_VENDOR_ID;
    avp->length = 8;
    avp->data = data;
    avp->datasz = datasz;
    if (data != NULL)
        avp->length += datasz;

    avp->sibling = avp->children = NULL;

    return avp;
}

void
avp_delete(struct dm_avp *avp)
{
    if (avp) {
        if (avp->children) {
            struct dm_avp *p;
            for (p = avp->children; p;) {
                struct dm_avp *next = p->sibling;
                avp_delete(p);
                p = next;
            }
        }

        if (avp->data) {
            free(avp->data);
        }

        free(avp);
    }
}

void
avp_prepend_child(struct dm_avp *avp, struct dm_avp *child)
{
    if (!avp || !child)
        return;

    child->sibling = avp->children;
    avp->children = child;

    avp->length += avp_boundary(child->length);
}

void
avp_set_vendorid(struct dm_avp *avp, uint32_t vnid)
{
    if (!avp)
        return;

    avp->vnid = vnid;
    avp->length += AVP_VNID_LENGTH;
}

size_t
avp_pack(struct dm_avp *avp, uint8_t **binp)
{
    if (!avp || (!avp->data && !avp->children))
        return 0;

    size_t   packlen = avp_boundary(avp->length);
    uint8_t *bin = malloc(packlen * sizeof *bin);
    if (bin == NULL)
        return 0;

    memset(bin, 0, packlen);
    set_4bytes(bin, AVP_CODE_OFFSET, avp->code);
    set_1byte(bin, AVP_FLAG_OFFSET, avp->flags);
    set_3bytes(bin, AVP_LNGT_OFFSET, avp->length);

    uint8_t *datap;
    if (avp->vnid != NO_VENDOR_ID) {
        set_4bytes(bin, AVP_VNID_OFFSET, avp->vnid);
        datap = bin + AVP_VDTA_OFFSET;
    } else {
        datap = bin + AVP_DATA_OFFSET;
    }

    if (avp->children) {
        struct dm_avp *pchld = avp->children;
        uint8_t *      cdata;
        size_t         cdlen = 0;

        while (pchld) {
            cdlen = avp_pack(pchld, &cdata);
            memcpy(datap, cdata, cdlen);
            datap += cdlen;
            free(cdata);
            pchld = pchld->sibling;
        }
    } else if (avp->data) {
        // primitive AVP
        memcpy(datap, avp->data, avp->datasz);
    }

    *binp = bin;
    return packlen;
}
