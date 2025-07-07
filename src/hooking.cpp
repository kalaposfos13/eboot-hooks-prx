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
extern "C" {

s32 attr_public plugin_load(s32 argc, const char* argv[]) {
    LOG_INFO("called");
    return 0;
}

s32 attr_public plugin_unload(s32 argc, const char* argv[]) {
    LOG_INFO("called");
    return 0;
}

s32 attr_module_hidden module_start(s64 argc, const void* args) {
    LOG_INFO("called");
    return 0;
}

s32 attr_module_hidden module_stop(s64 argc, const void* args) {
    LOG_INFO("called");
    return 0;
}
}