//
// Copyright (c) 2019 The nanoFramework project contributors
// Portions Copyright (c) Microsoft Corporation.  All rights reserved.
// See LICENSE file in the project root for full license information.
//

#ifndef _Touch_DRIVER_H_
#define _Touch_DRIVER_H_ 1


#include "nanohal.h"
#include "CPU_GPIO_decl.h"
#include "Display_driver_base.h"
#include "TouchPanel_decl.h"

********************* /
#define XPT2046_IRQ 25

#define XPT2046_AVG 4
#define XPT2046_X_MIN       1000
#define XPT2046_Y_MIN       1000
#define XPT2046_X_MAX       3200
#define XPT2046_Y_MAX       2000
#define XPT2046_X_INV       1
#define XPT2046_Y_INV       1

void xpt2046_init(void);
bool xpt2046_read(lv_indev_data_t* data);

#endif
