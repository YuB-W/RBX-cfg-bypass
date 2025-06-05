// cfg_bypass.cpp
// ✅ Roblox CFG Bypass - Working After Hyperion Patch
// Hyprion Version: version-e1da58b32b1c4d64 

#include <cstdint>
#include <cstddef>
#include <cstdio>

#define RELOC_FLAG(RelInfo) (((RelInfo) >> 12) == IMAGE_REL_BASED_DIR64)

#define CFG_PAGE_HASH_KEY       0x9c19a3df
#define CFG_VALIDATION_XOR      0x49

#define HashPage(Page) \
    ((((uintptr_t)(Page) >> 12) ^ CFG_PAGE_HASH_KEY))

#define ValidationByte(Page) \
    ((((uintptr_t)(Page) >> 44) ^ CFG_VALIDATION_XOR))

#define BatchWhitelistRegion(Start, Size)                                                             \
{                                                                                                     \
    uint8_t stack_block[0x40] = {};                                                                   \
    uintptr_t AlignedStart = (uintptr_t)(Start) & ~0xFFFULL;                                          \
    uintptr_t AlignedEnd   = ((uintptr_t)(Start) + (Size) + 0xFFFULL) & ~0xFFFULL;                    \
                                                                                                      \
    for (uintptr_t Page = AlignedStart; Page < AlignedEnd; Page += 0x1000)                            \
    {                                                                                                 \
        uint32_t page_hash = HashPage(Page);                                                          \
        uint8_t validation = ValidationByte(Page);                                                    \
                                                                                                      \
        *reinterpret_cast<uint32_t*>(stack_block + 0x18) = page_hash;                                 \
        *reinterpret_cast<uint8_t*>(stack_block + 0x1C) = validation;                                 \
                                                                                                      \
        insert_set(whitelist,                                                                         \
                   stack_block + 0x28,                                                                \
                   stack_block + 0x18);                                                               \
    }                                                                                                 \
}

// cache after u whitelist !!!!!!!!!!! 
BatchWhitelistRegion((std::uintptr_t)pBase, pOpt->SizeOfImage);

pBase &= ~0xFFFF;
for (auto pg = pBase; pg < pBase + pOpt->SizeOfImage; pg += 0x1000) {
*reinterpret_cast<std::uint32_t*>(*reinterpret_cast<std::uintptr_t*>(bitmap) + (pg >> 0x13)) |=
    1 << ((pg >> 0x10 & 7) % 0x20);
}
