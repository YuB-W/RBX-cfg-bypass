// cfg_bypass.cpp
// ✅ Roblox CFG Bypass - Working After Hyperion Patch
// Hyprion Version: version-ff05edc617954c5b

#include <cstdint>
#include <cstddef>
#include <cstdio>


#define RELOC_FLAG(RelInfo) (((RelInfo) >> 12) == IMAGE_REL_BASED_DIR64)
#define CFG_IDENTITY            0xBD8CCB27
#define CFG_PAGE_HASH_KEY       0xDBDB3027
#define CFG_VALIDATION_XOR      0x7E

#define HashPage(Page) \
    ((((uintptr_t)(Page) >> 0xC) ^ CFG_PAGE_HASH_KEY))

#define ValidationByte(Page) \
    ((((uintptr_t)(Page) >> 0x2C) ^ CFG_VALIDATION_XOR))

#define BatchWhitelistRegion(Start, Size)                                         \
{                                                                             \
    uintptr_t AlignedStart = (uintptr_t)(Start) & ~0xFFFULL;                 \
    uintptr_t AlignedEnd = ((uintptr_t)(Start) + (Size) + 0xFFF) & ~0xFFFULL; \
    uint32_t Identity = CFG_IDENTITY;                                        \
    for (uintptr_t Page = AlignedStart; Page < AlignedEnd; Page += 0x1000) { \
        struct {                                                             \
            uint32_t page_hash;                                              \
            uint8_t validation;                                              \
        } PageEntry;                                                         \
        PageEntry.page_hash = HashPage(Page);                                \
        PageEntry.validation = ValidationByte(Page);                         \
        insert_set(memory_map, &Identity, &PageEntry);                       \
    }                                                                         \
}

// cache after u whitelist !!!!!!!!!!! 
Base &= -0x10000;
for (auto pg = Base; pg < Base + Size; pg += 0x1000) {
	*reinterpret_cast<std::uint32_t*>(*reinterpret_cast<std::uintptr_t*>(bitmap) + (pg >> 0x13)) |= 1 << ((pg >> 0x10 & 7) % 0x20);
}
