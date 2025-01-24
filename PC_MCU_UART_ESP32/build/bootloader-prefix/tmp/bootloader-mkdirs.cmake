# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/hp/esp/v5.1.1/esp-idf/components/bootloader/subproject"
  "C:/PC_MCU_UART/PC_MCU_UART_ESP32/build/bootloader"
  "C:/PC_MCU_UART/PC_MCU_UART_ESP32/build/bootloader-prefix"
  "C:/PC_MCU_UART/PC_MCU_UART_ESP32/build/bootloader-prefix/tmp"
  "C:/PC_MCU_UART/PC_MCU_UART_ESP32/build/bootloader-prefix/src/bootloader-stamp"
  "C:/PC_MCU_UART/PC_MCU_UART_ESP32/build/bootloader-prefix/src"
  "C:/PC_MCU_UART/PC_MCU_UART_ESP32/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/PC_MCU_UART/PC_MCU_UART_ESP32/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/PC_MCU_UART/PC_MCU_UART_ESP32/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
