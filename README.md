# Mbed CE Macronix Flash Library

This library provides extended support for Macronix flash ICs in Mbed OS.  It provides two block device drivers which can be used by the application.

**MX25R_QSPIFBlockDevice** provides an extended version of [QSPIFBlockDevice](https://mbed-ce.github.io/mbed-os/class_q_s_p_i_f_block_device.html) which adds an additional method for controlling the power management features of MX25R family QSPI NOR flashes (e.g. MX25R6435F).

**MX3x_SPINANDBlockDevice** provides a block device driver for Macronix MX31 and MX35 family QSPI NAND flashes.  This driver includes support for both software and hardware ECC, and will make use of ECC on the host side as needed by the flash device.

## How to start
1. Create a new project according to [MbedCE instructions](https://github.com/mbed-ce/mbed-os/wiki)
2. Add this as submodule to your project via `git submodule add https://github.com/mbed-ce-libraries-examples/MacronixFlash`
3. The top level `CMakeLists.txt` (in root of your project) should be modified to add `add_subdirectory(MacronixFlash)` after the `project(...)` line.
4. Link the `MacronixFlash` library to the code for your application.
5. You can now include the headers and instantate the classes in this library!

### Status:
Library has been converted from PRs by Macronix ([1](https://github.com/mbed-ce/mbed-os/pull/284)) ([2](https://github.com/mbed-ce/mbed-os/pull/258)) into its own repo.  This code has not been tested on real hardware, but the original version was by Macronix.
