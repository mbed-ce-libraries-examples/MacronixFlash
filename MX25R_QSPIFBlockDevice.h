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

#ifndef MBED_POWER_MANAGEMENT_BLOCK_DEVICE_H
#define MBED_POWER_MANAGEMENT_BLOCK_DEVICE_H

#include "BlockDevice.h"
#include "platform/mbed_assert.h"
#include "QSPIF/QSPIFBlockDevice.h"



namespace mbed {

/**
 * @brief Driver for MX25R family QSPI flashes.  Adds power management features.
 */
class MX25R_QSPIFBlockDevice : public QSPIFBlockDevice {
public:

    // Inherit constructor from QSPIFBlockDevice
    using QSPIFBlockDevice::QSPIFBlockDevice;

    /// Possible power modes that the flash can be in
    enum PowerMode {
        HIGH_PERFORMANCE, ///< Flash runs at full speed
        LOW_POWER ///< Clock speed is limited, but power consumption is decreased by 30-50%
    };

    /**
     * @brief Switch the Block Device power management mode
     *
     * This sets the flash to run in high performance or low power mode.
     * Since the power mode is changing, you will need to consult your datasheet
     * to find the correct frequency to run the flash at in this power mode.
     *
     * @param pm_mode Power management mode of Block Device
     * @param new_spi_freq New SPI frequency to set in Hz
     * @return 0 on success, negative error code on failure
     */
    virtual int switch_power_management_mode(PowerMode pm_mode, float new_spi_freq);

    /**
     * @brief Enter deep power down mode.  Standby current will be reduced
     * significantly, but no other commands can be used until exit_deep_powerdown() is called.
     *
     * @return 0 on success, negative error code on failure
     */
    virtual int enter_deep_powerdown();

    /**
     * @brief Exit deep power down mode.
     *
     * @return 0 on success, negative error code on failure
     */
    virtual int exit_deep_powerdown();

private:
    BlockDevice *_bd;
};

} // namespace mbed

// Added "using" for backwards compatibility
#ifndef MBED_NO_GLOBAL_USING_DIRECTIVE
using mbed::MX25R_QSPIFBlockDevice;
#endif

#endif

/** @}*/