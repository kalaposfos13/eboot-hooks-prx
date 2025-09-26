// SPDX-FileCopyrightText: Copyright 2025 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "common/LightHook.h"
#include "common/assert.h"
#include "common/logging.h"
#include "common/types.h"
#include "hooking.h"

#include "orbis/libkernel.h"

HOOK_INIT(HookableFunction)

int HOOK_FUNC HookableFunction(int a) {
    LOG_INFO("Successfully hooked function, a: {}, returning 13", a);
    int ret = CONTINUE(HookableFunction, int(*)(int), a);
    LOG_INFO("Original return: {}", ret);
    return 13;
}

bool eboot_hook(u64 base_addr) {
    LOG_INFO("Hooking eboot functions");

    HOOK(0x00420500 - 0x00400000, HookableFunction);

    return true;
}

extern "C" int __wrap__init() {
    LOG_INFO("called");
    OrbisKernelModuleInfo* module_info = new OrbisKernelModuleInfo();
    module_info->size = sizeof(OrbisKernelModuleInfo);
    sceKernelGetModuleInfo(0, module_info);
    LOG_INFO("Module 0 base address: {}", module_info->segmentInfo[0].address);
    if (!eboot_hook((u64)module_info->segmentInfo[0].address)) {
        LOG_ERROR("Something went wrong with hooking setup!");
    }
    return 0;
}

// will never be called probably, the compiler just complains if this isn't here
extern "C" void _start() {
    LOG_INFO("called");
    return;
}
