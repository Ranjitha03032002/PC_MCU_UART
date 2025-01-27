idf_component_register(SRCS 
                            "main.c"
                            "./EEPROM/eeprom.c"
                            "./TIMER/timer.c"
                            "./UART/uart.c"

                        INCLUDE_DIRS 
                                "."
                                "./EEPROM"
                                "./TIMER" 
                                "./UART"
                    )