#pragma once

#include <stdarg.h>
#include <stdio.h>

#include "common/types.h"

#define HOOK_FUNC __attribute__((noinline)) __attribute__((sysv_abi))

#define HOOK_INIT_VAL(name) info_##name
#define HOOK_INIT(name) HookInformation info_##name;
#define HOOK(addr, name) \
    do { \
        HOOK_INIT_VAL(name) = CreateHook((void*)(base_addr+addr), (void*)name);  \
        if (!EnableHook(&HOOK_INIT_VAL(name))) \
            return false; \
        printf("addr %lx hooked\n", base_addr+addr); \
    } while (0);
#define CONTINUE(name, type, ...) ((type)(info_##name.Trampoline))(__VA_ARGS__);
