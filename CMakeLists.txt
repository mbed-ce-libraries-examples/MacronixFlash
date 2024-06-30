#[[https://github.com/mbed-ce/mbed-os/wiki/MbedOS-configuration#libraries-in-your-application]]

if(NOT "DEVICE_QSPI=1" IN_LIST MBED_TARGET_DEFINITIONS)
	message(FATAL_ERROR "MacronixFlash library requires an Mbed target with QSPI support!")
endif()

add_library(MacronixFlash STATIC 
	MX3x_SPINANDBlockDevice.cpp
	MX25R_QSPIFBlockDevice.cpp
	bch.c)

#[[ Include .h files]]
target_include_directories(MacronixFlash INTERFACE .)

#[[Link library to mbed-core-flags but if the library needs to use RTOS
 features, then have to be add also mbed-rtos-flags]]
target_link_libraries(MacronixFlash PUBLIC
	mbed-core-flags
	mbed-storage-blockdevice
	mbed-storage-qspif)