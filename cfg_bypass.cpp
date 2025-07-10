// YuB-X Version: 2.0.8
// Roblox Version: version-765338e04cf54fde
// Dump Time:      2025-07-09 22:43:00

#include <cstdint>
#include <cstddef>
#include <cstdio>

#define RELOC_FLAG(RelInfo) (((RelInfo) >> 12) == IMAGE_REL_BASED_DIR64)

#define WHITELIST_MODE_TAG 0xd0698f90;
#define CFG_PAGE_HASH_KEY  0xC9E94648;
#define CFG_VALIDATION_XOR 0xD;

#define HashPage(Page) \
    ((((uintptr_t)(Page) >> 12) ^ CFG_PAGE_HASH_KEY))

#define ValidationByte(Page) \
    ((((uintptr_t)(Page) >> 44) ^ CFG_VALIDATION_XOR))

#define BatchWhitelistRegion(Start, Size)                                                      \
{                                                                                              \
    uint8_t stack_block[0x40] = {};                                                            \
    *reinterpret_cast<uint32_t*>(stack_block + 0x14) = WHITELIST_MODE_TAG;                     \
                                                                                               \
    uintptr_t AlignedStart = (uintptr_t)(Start) & ~0xFFFULL;                                   \
    uintptr_t AlignedEnd   = ((uintptr_t)(Start) + (Size) + 0xFFFULL) & ~0xFFFULL;             \
    for (uintptr_t Page = AlignedStart; Page < AlignedEnd; Page += 0x1000)                     \
    {                                                                                          \
        *reinterpret_cast<uint32_t*>(stack_block + 0x18) = HashPage(Page);                     \
        *reinterpret_cast<uint8_t*>(stack_block + 0x1C) = ValidationByte(Page);                \
                                                                                               \
        insert_set(whitelist,                                                                  \
                   stack_block + 0x14,                                                         \
                   stack_block + 0x18);                                                        \
    }                                                                                          \
}

// cache after u whitelist !!!!!!!!!!! 
BatchWhitelistRegion((std::uintptr_t)pBase, pOpt->SizeOfImage);

pBase &= ~0xFFFF;
for (auto pg = pBase; pg < pBase + pOpt->SizeOfImage; pg += 0x1000) {
*reinterpret_cast<std::uint32_t*>(*reinterpret_cast<std::uintptr_t*>(bitmap) + (pg >> 0x13)) |=
    1 << ((pg >> 0x10 & 7) % 0x20);
}

