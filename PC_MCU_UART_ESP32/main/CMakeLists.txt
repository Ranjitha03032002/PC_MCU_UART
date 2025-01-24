idf_component_register(SRCS 
                            "main.c"
                            "./EEPROM/eeprom_conf.c" "./EEPROM/eeprom_hal.c" "./EEPROM/eeprom_mngr.c"
                            "./TIMER/timer_conf.c" "./TIMER/timer_hal.c" "./TIMER/timer_mngr.c"
                            "./UART/uart_conf.c" "./UART/uart_hal.c" "./UART/uart_mngr.c"

                        INCLUDE_DIRS 
                                "."
                                "./EEPROM"
                                "./TIMER" 
                                "./UART"
                    )