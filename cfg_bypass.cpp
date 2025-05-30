// cfg_bypass.cpp
// ✅ Roblox CFG Bypass - Working After Hyperion Patch
// Hyprion Version: version-ad3ee47cdc5e44f6

#include <cstdint>
#include <cstddef>
#include <cstdio>

#define RELOC_FLAG(RelInfo) (((RelInfo) >> 12) == IMAGE_REL_BASED_DIR64)

#define CFG_IDENTITY            0x331c2089
#define CFG_PAGE_HASH_KEY       0xaa9f8e1b
#define CFG_VALIDATION_XOR      0x27

#define HashPage(Page) \
    ((((uintptr_t)(Page) >> 12) ^ CFG_PAGE_HASH_KEY))

#define ValidationByte(Page) \
    ((((uintptr_t)(Page) >> 44) ^ CFG_VALIDATION_XOR))

#define BatchWhitelistRegion(Start, Size)                                                                     \
{                                                                                                             \
    uintptr_t AlignedStart = (uintptr_t)(Start) & ~0xFFFULL;                                                  \
    uintptr_t AlignedEnd = ((uintptr_t)(Start) + (Size) + 0xFFFULL) & ~0xFFFULL;                              \
                                                                                                              \
    uint64_t rbx_1 = 0xFFFFFFFFFFFFFFFF - 0x78BE7A9697D2CD0FULL + 1;                                          \
                                                                                                              \
    for (uintptr_t Page = AlignedStart; Page < AlignedEnd; Page += 0x1000) {                                  \
        void* table = whitelist;                                                                              \
        uint64_t i_1 = 0;                                                                                     \
                                                                                                              \
        if (whitelist != (void*)rbx_1) {                                                                      \
            table = whitelist2;                                                                               \
            i_1 = Page;                                                                                       \
        } else {                                                                                              \
            rbx_1 = *(uint64_t*)((uintptr_t)NtCurrentTeb() + rbx_1 - 0x4BAD1330) * 0xE5312586;                \
            i_1 = (uintptr_t)whitelist;                                                                       \
        }                                                                                                     \
                                                                                                              \
        struct {                                                                                              \
            uint32_t page_hash;                                                                               \
            uint8_t validation;                                                                               \
        } PageEntry;                                                                                          \
                                                                                                              \
        PageEntry.page_hash = HashPage(i_1);                                                                  \
        PageEntry.validation = ValidationByte(Page);                                                          \
                                                                                                              \
        uint32_t Identity = CFG_IDENTITY;                                                                     \
        insert_set(table, &Identity, &PageEntry);                                                             \
    }                                                                                                         \
}

// cache after u whitelist !!!!!!!!!!! 
BatchWhitelistRegion((std::uintptr_t)pBase, pOpt->SizeOfImage);

pBase &= ~0xFFFF;
for (auto pg = pBase; pg < pBase + pOpt->SizeOfImage; pg += 0x1000) {
*reinterpret_cast<std::uint32_t*>(*reinterpret_cast<std::uintptr_t*>(bitmap) + (pg >> 0x13)) |=
    1 << ((pg >> 0x10 & 7) % 0x20);
}
