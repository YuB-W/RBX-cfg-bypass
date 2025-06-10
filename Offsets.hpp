#pragma once
#include <cstdint>

namespace unordered_set {
    using insert = void* (__fastcall*)(void*, void*, void*);
}


static const uintptr_t set_insert = 0xDC8280;
static const uintptr_t Bitmap = 0x2843D8;
static const uintptr_t whitelist_page = 0x2834b8;
