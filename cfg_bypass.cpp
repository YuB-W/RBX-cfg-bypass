// YuB-X Version: 2.0.8
// Roblox Version: version-2a06298afe3947ab
// Dump Time:      2025-07-24 11:36:07

#include <cstdint>
#include <cstddef>
#include <cstdio>

#define RELOC_FLAG(RelInfo) (((RelInfo) >> 12) == IMAGE_REL_BASED_DIR64)

#define CFG_PAGE_HASH_KEY  0xF7455279
#define CFG_VALIDATION_XOR 0xA9

#define HashPage(Page) \
    (((uintptr_t)(Page) >> 12) ^ CFG_PAGE_HASH_KEY)

#define ValidationByte(Page) \
    (((uintptr_t)(Page) >> 44) ^ CFG_VALIDATION_XOR)

#define BatchWhitelistRegion(Start, Size)                                                    \
{                                                                                            \
    uintptr_t __wl_start = (uintptr_t)(Start);                                               \
    uintptr_t __wl_size = (uintptr_t)(Size);                                                 \
    uintptr_t __wl_aligned_start = __wl_start & ~0xFFFULL;                                   \
    uintptr_t __wl_aligned_end = (__wl_start + __wl_size + 0xFFFULL) & ~0xFFFULL;            \
    for (uintptr_t __wl_page = __wl_aligned_start; __wl_page < __wl_aligned_end; __wl_page += 0x1000) \
    {                                                                                        \
        uint8_t __wl_stack_block[0x40] = {};                                                 \
        *reinterpret_cast<uint32_t*>(__wl_stack_block + 0x18) = HashPage(__wl_page);         \
        *reinterpret_cast<uint8_t*>(__wl_stack_block + 0x1C) = ValidationByte(__wl_page);    \
        insert_set(whitelist, __wl_stack_block + 0x14, __wl_stack_block + 0x18);             \
    }                                                                                        \
}

// cache after u whitelist !!!!!!!!!!! 
BatchWhitelistRegion((std::uintptr_t)pBase, pOpt->SizeOfImage);

pBase &= ~0xFFFF;
for (auto pg = pBase; pg < pBase + pOpt->SizeOfImage; pg += 0x1000) {
*reinterpret_cast<std::uint32_t*>(*reinterpret_cast<std::uintptr_t*>(bitmap) + (pg >> 0x13)) |=
    1 << ((pg >> 0x10 & 7) % 0x20);
}

