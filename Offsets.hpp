#pragma once
#include "Windows.h"
#include <cstdint>

// Hyprion Version: version-ff05edc617954c5b

namespace ofssetss_new
{
    // whitelist stuff
    static constexpr auto set_insert = 0xe5c390;  // set_insert function 0xba15b0
    static constexpr auto whitelist_page = 0x29d1d0;  // whitelist function (same as set_insert now) 0x2856b8
    static constexpr auto Bitmap = 0x283ac0;  // whitelist function (same as set_insert now) 0x299ac0
}
