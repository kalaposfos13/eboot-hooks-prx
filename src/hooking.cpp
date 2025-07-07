// SPDX-FileCopyrightText: Copyright 2025 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "common/LightHook.h"
#include "common/assert.h"
#include "common/logging.h"
#include "common/types.h"
#include "hooking.h"

#include "orbis/libkernel.h"

HOOK_INIT(SearchFlagInGlobalArgv);

bool HOOK_FUNC SearchFlagInGlobalArgv(char* flag) {
    LOG_WARNING("Checked flag: {}", flag);

    bool ret = CONTINUE(SearchFlagInGlobalArgv, bool (*)(char*), flag);

    LOG_INFO("return: {}", ret);
    return ret;
}

bool eboot_hook(u64 base_addr) {
    LOG_INFO("Hooking eboot functions");

    HOOK(0x00557830 - 0x00400000, SearchFlagInGlobalArgv);

    return true;
}

extern "C" int __wrap__init() {
    LOG_INFO("called");
    if (!eboot_hook(0x800000000)) {
        LOG_ERROR("Something went wrong with hooking setup!");
    }
    return 0;
}

// will never be called probably, the compiler just complains if this isn't here
extern "C" void _start() {
    LOG_INFO("called");
    return;
}
