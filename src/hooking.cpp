// SPDX-FileCopyrightText: Copyright 2025 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "common/assert.h"
#include "common/logging.h"
#include "common/types.h"

#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <fcntl.h>

#include <orbis/libkernel.h>

extern "C" void _start() {
    fmt::print("Hello World!\n");
    return;
}
