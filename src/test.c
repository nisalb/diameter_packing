#include <stdio.h>

#include "avp.h"
#include "msg.h"

void
hexdump(uint8_t *str, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++) {
        printf("%02hhx ", str[i]);
        if ((i + 1) % 4 == 0)
            printf("\n");
    }
    printf("\n");
}

int
main(void)
{
    uint8_t *bin = NULL;
    size_t   len = 0;

    printf("Test #hextobin\n");

    len = hextobin("03e923", &bin);
    hexdump(bin, len);
    free(bin);

    len = hextobin("3e923", &bin);
    hexdump(bin, len);
    free(bin);

    printf("Test #asciitobin\n");

    len = asciitobin("12344", &bin);
    hexdump(bin, len);
    free(bin);

    printf("Test #i32tobin\n");

    len = i32tobin(0x1234, &bin);
    hexdump(bin, len);
    free(bin);

    printf("Test #avps\n");

    len = i32tobin(0x0, &bin);
    struct dm_avp *sub_id_type = avp_new(450, AVP_MANDATORY, bin, len);

    len = asciitobin("94719100344", &bin);
    struct dm_avp *sub_id_data = avp_new(444, AVP_MANDATORY, bin, len);

    struct dm_avp *sub_id = avp_new(443, AVP_MANDATORY, NULL, 0);
    avp_prepend_child(sub_id, sub_id_data);
    avp_prepend_child(sub_id, sub_id_type);

    len = avp_pack(sub_id, &bin);
    hexdump(bin, len);
    free(bin);

    // avp_delete(sub_id);

    printf("Test #msgs\n");

    len = asciitobin("IT_SMS_GW_5.mobitel;lk", &bin);
    struct dm_avp *origin_host = avp_new(264, AVP_MANDATORY, bin, len);

    len = asciitobin("172.19.147.38", &bin);
    struct dm_avp *origin_realm = avp_new(296, AVP_MANDATORY, bin, len);

    len = hextobin("0001ac139326", &bin);
    struct dm_avp *host_ip_addr = avp_new(257, AVP_MANDATORY, bin, len);

    len = hextobin("000003e9", &bin);
    struct dm_avp *vendor_id = avp_new(266, AVP_MANDATORY, bin, len);

    len = hextobin("41434354", &bin);
    struct dm_avp *product_name = avp_new(269, 0, bin, len);

    len = hextobin("501f5d3a", &bin);
    struct dm_avp *origin_state_id = avp_new(278, AVP_MANDATORY, bin, len);

    len = hextobin("00000004", &bin);
    struct dm_avp *auth_app_id = avp_new(258, AVP_MANDATORY, bin, len);

    len = hextobin("000003ea", &bin);
    struct dm_avp *acct_app_id = avp_new(259, AVP_MANDATORY, bin, len);

    struct dm_msg *msg = msg_new(257, MSG_REQ, 0x3eb, 0xce000001, 0xd3acf861);
    // msg_prepend_avp(msg, sub_id);
    msg_prepend_avp(msg, acct_app_id);
    msg_prepend_avp(msg, auth_app_id);
    msg_prepend_avp(msg, origin_state_id);
    msg_prepend_avp(msg, product_name);
    msg_prepend_avp(msg, vendor_id);
    msg_prepend_avp(msg, host_ip_addr);
    msg_prepend_avp(msg, origin_realm);
    msg_prepend_avp(msg, origin_host);

    printf("length = %d\n", msg->length);

    len = msg_pack(msg, &bin);
    hexdump(bin, len);
    free(bin);

    msg_delete(msg);

    return 0;
}
