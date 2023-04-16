#pragma once

#include "quantum.h"

#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

#ifdef RGB_MATRIX_ENABLE
#include <ch.h>
#include <hal.h>
#include "i2c_master.h"
#include "drivers/led/issi/is31fl3733.h"
#endif
