cmake -Bbuild -DCMAKE_TOOLCHAIN_FILE=gcc-arm-none-eabi.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=true

https://devblogs.microsoft.com/commandline/connecting-usb-devices-to-wsl/

Serial port to be working on Linux:
sudo chmod 777 /dev/ttyACM0

st-info --probe
modification in the cd /etc/udev/rules.d/  --> stm_link.sh
sudo service udev start

extern "C"
{
    #include "FreeRTOSConfig.h"
    #include "projdefs.h"
    #include "portmacro.h"
    #include "mpu_wrappers.h"
    #include "FreeRTOS.h"
    #include "task.h"
}

Suspend all tasks and ISRs:
    __disable_irq();
    vTaskSuspendAll();

    __enable_irq(); 
    xTaskResumeAll();