#pragma once
#include <cstdint>

namespace unordered_set {
    using insert = void* (__fastcall*)(void*, void*, void*);
}


static const uintptr_t set_insert = 0xD77510;
static const uintptr_t Bitmap = 0x2855A8;
static const uintptr_t whitelist_page = 0x29cbd6;
static const uintptr_t whitelist_page2 = 0x2A3820;
