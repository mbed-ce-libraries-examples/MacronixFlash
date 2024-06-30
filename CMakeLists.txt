#[[https://github.com/mbed-ce/mbed-os/wiki/MbedOS-configuration#libraries-in-your-application]]

add_library(MacronixFlash STATIC 
	MX3x_SPINANDBlockDevice.cpp
	MX25R_QSPIFBlockDevice.cpp)

#[[ Include .h files]]
target_include_directories(MacronixFlash INTERFACE .)

#[[Link library to mbed-core-flags but if the library needs to use RTOS
 features, then have to be add also mbed-rtos-flags]]
target_link_libraries(MacronixFlash PUBLIC mbed-core-flags)