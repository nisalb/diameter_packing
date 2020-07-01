#ifndef AVP_H_INCLUDE
#define AVP_H_INCLUDE

#include <stdint.h>
#include <stdlib.h>

// can't use 0 to indicate no vendor id
// https://www.iana.org/assignments/enterprise-numbers/enterprise-numbers
#define NO_VENDOR_ID 0xEFFFFFFF

#define avp_boundary(L) (((L) > 0 && (L) % 4 != 0) ? (((L) / 4 + 1) * 4) : (L))

#define AVP_PFLAG     0
#define AVP_MANDATORY 0x40
#define AVP_VENDORS   0x80

struct dm_avp {
    uint32_t code;
    uint8_t  flags;
    uint32_t length;
    uint32_t vnid;
    uint8_t *data;
    size_t   datasz;

    struct dm_avp *sibling;
    struct dm_avp *children;
};

// Convert Diameter data types in to a binary stream
size_t hextobin(char *hex, uint8_t **binp);
size_t asciitobin(char *str, uint8_t **binp);
size_t i32tobin(uint32_t val, uint8_t **binp);

// AVP management
struct dm_avp *avp_new(uint32_t code, uint8_t flags, uint8_t *data, size_t datasz);
void           avp_delete(struct dm_avp *avp);
void           avp_prepend_child(struct dm_avp *avp, struct dm_avp *child);
size_t         avp_pack(struct dm_avp *avp, uint8_t **binp);
void           avp_set_vendorid(struct dm_avp *avp, uint32_t vnid);

#endif
