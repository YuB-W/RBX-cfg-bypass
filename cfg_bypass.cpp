// cfg_bypass.cpp
// ✅ Roblox CFG Bypass - Working After Hyperion Patch
// Hyprion Version: version-ff05edc617954c5b

#include <cstdint>
#include <cstddef>
#include <cstdio>


#define RELOC_FLAG(RelInfo) (((RelInfo) >> 12) == IMAGE_REL_BASED_DIR64)
#define CFG_IDENTITY            0xB3C93940 
#define CFG_PAGE_HASH_KEY       0xA6FC287E 
#define CFG_VALIDATION_XOR      0xF6       

#define HashPage(Page) \
    ((((uintptr_t)(Page) >> 12) ^ CFG_PAGE_HASH_KEY))

#define ValidationByte(Page) \
    ((((uintptr_t)(Page) >> 44) ^ CFG_VALIDATION_XOR))

#define BatchWhitelistRegion(Start, Size)                                         \
{                                                                                 \
    uintptr_t AlignedStart = (uintptr_t)(Start) & ~0xFFFULL;                      \
    uintptr_t AlignedEnd = ((uintptr_t)(Start) + (Size) + 0xFFF) & ~0xFFFULL;     \
    uint32_t Identity = CFG_IDENTITY;                                             \
    for (uintptr_t Page = AlignedStart; Page < AlignedEnd; Page += 0x1000) {      \
        struct {                                                                  \
            uint32_t page_hash;                                                   \
            uint8_t validation;                                                   \
        } PageEntry;                                                              \
        PageEntry.page_hash = HashPage(Page);                                     \
        PageEntry.validation = ValidationByte(Page);                              \
        insert_set(memory_map, &Identity, &PageEntry);                            \
    }                                                                             \
}

// cache after u whitelist !!!!!!!!!!! 
BatchWhitelistRegion(pShared->InternalMapperPage, pShared->InternalMapperSize);

auto UDetourPage = (uintptr_t)(pShared->InternalMapperPage) & ~0xFFFF;
for (auto pg = UDetourPage; pg < UDetourPage + pShared->InternalMapperSize; pg += 0x1000) {
*reinterpret_cast<std::uint32_t*>(*reinterpret_cast<std::uintptr_t*>(bitmap) + (pg >> 0x13)) |=
    1 << ((pg >> 0x10 & 7) % 0x20);
}

BatchWhitelistRegion((std::uintptr_t)pBase, pOpt->SizeOfImage);

pBase &= ~0xFFFF;
for (auto pg = pBase; pg < pBase + pOpt->SizeOfImage; pg += 0x1000) {
*reinterpret_cast<std::uint32_t*>(*reinterpret_cast<std::uintptr_t*>(bitmap) + (pg >> 0x13)) |=
    1 << ((pg >> 0x10 & 7) % 0x20);
}
