#include <string>
#include <cstring>

static std::string mgmt_prop_min_sid_key = "\x00\x00\x00\x00\x00\x00\x00\x00";
static std::string mgmt_prop_max_sid_key = "\xff\xff\xff\xff\xff\xff\xff\xff";

#define mgmt_prop_sid_prefix "sid_"
static char mgmt_prop_min_sid_key_buf[9] = mgmt_prop_sid_prefix;
static char mgmt_prop_max_sid_key_buf[9] = mgmt_prop_sid_prefix"\xff\xff\xff\xff";

int main() {
    int len1 = mgmt_prop_min_sid_key.size();  // 0
    int len2 = mgmt_prop_max_sid_key.size();
    printf("len1: %u, len2: %u\n", len1, len2);

    for(int i = 0; i < len1; i++) {
        printf("0x%x ", mgmt_prop_min_sid_key[i]);
    }
    printf("\n");
    for(int i = 0; i < len2; i++) {
        printf("0x%x ", mgmt_prop_max_sid_key[i]);
    }
    printf("\n");
    printf("\n");
    
    for(int i = 0; i < sizeof(mgmt_prop_min_sid_key_buf); i++) {
        printf("0x%x ", mgmt_prop_min_sid_key_buf[i]);
    }
    printf("\n");
    for(int i = 0; i < sizeof(mgmt_prop_max_sid_key_buf); i++) {
        printf("0x%x ", mgmt_prop_max_sid_key_buf[i]);
    }
    printf("\n");

    printf("sizeof(mgmt_prop_sid_prefix): %lu strlen(mgmt_prop_sid_prefix): %lu\n", sizeof(mgmt_prop_sid_prefix), strlen(mgmt_prop_sid_prefix));
    
    const char chs[] = "ss\0aa";
    printf("sizeof(chs): %lu strlen(chs): %lu\n", sizeof(chs), strlen(chs));

    return 0;
}
