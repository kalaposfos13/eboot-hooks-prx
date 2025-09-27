#pragma once

#include <stdarg.h>
#include <stdio.h>

#include "common/types.h"
#include "fmt/format.h"

#define HOOK_FUNC __attribute__((noinline)) __attribute__((sysv_abi))

#define HOOK_INIT_VAL(name) info_##name
#define HOOK_INIT(name) HookInformation info_##name;
#define HOOK(addr, name)                                                                           \
    do {                                                                                           \
        HOOK_INIT_VAL(name) = CreateHook((void*)(base_addr + addr), (void*)name);                  \
        if (!EnableHook(&HOOK_INIT_VAL(name))) {                                                   \
            LOG_ERROR("addr {:#x} failed to hook", (base_addr + addr));                          \
            return false;                                                                          \
        }                                                                                          \
        LOG_INFO("addr {:#x} hooked", (base_addr + addr));                                       \
    } while (0);
#define CONTINUE(name, type, ...) ((type)(info_##name.Trampoline))(__VA_ARGS__);
