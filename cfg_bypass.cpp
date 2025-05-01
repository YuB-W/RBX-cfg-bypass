// cfg_bypass.cpp
// ✅ Roblox CFG Bypass - Working After Hyperion Patch
// Hyperion version-c3c1514fd260482e


#include <cstdint>
#include <cstddef>
#include <cstdio>

// --- Constants ---
#define CFG_IDENTITY             0xbff1e47f
#define CFG_PAGE_HASH_KEY        0x7b822ce4
#define CFG_VALIDATION_XOR       0x11

// --- Hash Functions ---
#define HashPage(Page)           ((((uintptr_t)(Page) >> 0xC) ^ CFG_PAGE_HASH_KEY))
#define ValidationByte(Page)     ((((uintptr_t)(Page) >> 0x2C) ^ CFG_VALIDATION_XOR))

// --- External Insert Function (You must implement this based on your environment) ---
extern void insert_set(void* memory_map, const void* identity, const void* page_entry);

// --- Whitelist Function ---
#define BatchWhitelistRegion(Start, Size)                                                   \
{                                                                                           \
    uintptr_t AlignedStart = (uintptr_t)(Start) & 0xfffffffffffff000;                       \
    uintptr_t AlignedEnd   = ((uintptr_t)(Start) + (Size) + 0xfff) & 0xfffffffffffff000;    \
    uint32_t Identity = CFG_IDENTITY;                                                       \
    for (uintptr_t Page = AlignedStart; Page < AlignedEnd; Page += 0x1000)                  \
    {                                                                                       \
        struct { uint32_t page_hash; uint8_t validation; } PageEntry;                       \
        PageEntry.page_hash = HashPage(Page);                                               \
        PageEntry.validation = ValidationByte(Page);                                        \
        insert_set(memory_map, &Identity, &PageEntry);                                      \
    }                                                                                       \
}

// --- Bitmap Cache Patch ---
void PatchCFGCache(uintptr_t Base, size_t Size, void* bitmap)
{
    uintptr_t alignedBase = Base & ~0xFFFF;

    for (uintptr_t pg = alignedBase; pg < Base + Size; pg += 0x1000)
    {
        uintptr_t* bitmapBase = reinterpret_cast<uintptr_t*>(bitmap);
        uint32_t* entry = reinterpret_cast<uint32_t*>(bitmapBase[(pg >> 0x13)]);
        uint32_t bit = ((pg >> 0x10) & 7) % 0x20;
        *entry |= (1 << bit);
    }
}

// ✅ Example Usage:

// Dummy insert_set implementation for demonstration
void insert_set(void* memory_map, const void* identity, const void* page_entry)
{
    auto* page = static_cast<const uint32_t*>(page_entry);
    printf("[Insert] PageHash: 0x%08X | Validation: 0x%02X | Identity: 0x%08X\n",
        page[0], *((const uint8_t*)page + 4), *((const uint32_t*)identity));
}

int main()
{
    void* dummy_map = nullptr;
    uintptr_t dllBase = 0x0; 
    size_t dllSize = 0x0;   

    // Step 1: Whitelist pages with correct hash/validation
    BatchWhitelistRegion(dllBase, dllSize);

    // Step 2: Patch CFG bitmap to activate pages
    void* fakeBitmap = calloc(1, 0x10000); // replace with real bitmap 
    PatchCFGCache(dllBase, dllSize, fakeBitmap);

    free(fakeBitmap);
    return 0;
}
