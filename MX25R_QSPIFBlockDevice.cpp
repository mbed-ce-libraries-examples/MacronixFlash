/* mbed Microcontroller Library
 * Copyright (c) 2022, Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "MX25R_QSPIFBlockDevice.h"
#include "platform/mbed_error.h"

#include "mbed_wait_api.h"

#define QSPI_CMD_WREN    0x06
#define QSPI_CMD_RDCR0   0x15
#define QSPI_CMD_WRSR    0x01
#define QSPI_CMD_RDSR    0x05
#define QSPI_CMD_NOP     0x00
#define QSPI_CMD_DP      0xB9
#define QSPI_LH_BIT_MASK   0x02

// Time to delay after sending deep power down command before doing anything else
#define DEEP_POWERDOWN_DELAY_TIME_US 40

// Time to wait for the device to exit deep powerdown mode
#define DEEP_POWERDOWN_RECOVERY_TIME_US 35

namespace mbed
{

int MX25R_QSPIFBlockDevice::switch_power_management_mode(PowerMode pm_mode, float new_spi_freq)
{
    uint8_t wren_inst = QSPI_CMD_WREN;
    uint8_t sr_reg[3] = {0};
    uint8_t rdcr_inst = QSPI_CMD_RDCR0, wrsr_inst = QSPI_CMD_WRSR, rdsr_inst = QSPI_CMD_RDSR;

    if (QSPI_STATUS_OK != _qspi.command_transfer(wren_inst, -1, NULL, 0, NULL, 0)) {
        return QSPIF_BD_ERROR_DEVICE_ERROR;
    }

    // Read status register and configuration registers
    if (QSPI_STATUS_OK != _qspi.command_transfer(rdsr_inst, -1, NULL, 0, (const char *)&sr_reg[0], 1)) {
        return QSPIF_BD_ERROR_DEVICE_ERROR;
    }

    if (QSPI_STATUS_OK != _qspi.command_transfer(rdcr_inst, -1, NULL, 0, (const char *)&sr_reg[1], 2)) {
        return QSPIF_BD_ERROR_DEVICE_ERROR;
    }

    switch (pm_mode) {
        case HIGH_PERFORMANCE:
            sr_reg[2] |= QSPI_LH_BIT_MASK;
            break;
        case LOW_POWER:
            sr_reg[2] &= ~QSPI_LH_BIT_MASK;
            break;
        default:
            return QSPIF_BD_ERROR_INVALID_ARGUMENT;
    }

    // Write new status register + configuration register values
    if (QSPI_STATUS_OK != _qspi.command_transfer(wrsr_inst, -1, (const char *)&sr_reg[0], 3, NULL, 0)) {
        return QSPIF_BD_ERROR_DEVICE_ERROR;
    }

    return QSPIF_BD_ERROR_OK;
}

int mbed::MX25R_QSPIFBlockDevice::enter_deep_powerdown()
{
    if (QSPI_STATUS_OK != _qspi.command_transfer(QSPI_CMD_DP, -1, NULL, 0, NULL, 0)) {
        return QSPIF_BD_ERROR_DEVICE_ERROR;
    }

    wait_us(DEEP_POWERDOWN_DELAY_TIME_US);

    return QSPIF_BD_ERROR_OK;
}

int mbed::MX25R_QSPIFBlockDevice::exit_deep_powerdown()
{
    // Just need to toggle CS for >20ns in order to wake it up.
    if (QSPI_STATUS_OK != _qspi.command_transfer(QSPI_CMD_NOP, -1, NULL, 0, NULL, 0)) {
        return QSPIF_BD_ERROR_DEVICE_ERROR;
    }

    wait_us(DEEP_POWERDOWN_RECOVERY_TIME_US);

    return QSPIF_BD_ERROR_OK;
}

} // namespace mbed

/** @}*/