#ifndef EEPROM_HAL_H
#define EEPROM_HAL_H

#include "nvs_flash.h"

#include "eeprom_conf.h"

extern esp_err_t init_eeprom();
// extern esp_err_t write_TripID_eeprom(void);
// extern esp_err_t read_TripID_eeprom(void);

extern esp_err_t write_TripID_byte_eeprom(uint8_t byte_to_store, uint16_t offset);
extern esp_err_t read_TripID_bytes_eeprom(uint8_t *buffer, uint16_t length);
extern esp_err_t erase_eeprom(void);
extern esp_err_t write_TripID_chunk_eeprom(const uint8_t *buffer, size_t length, size_t offset);
#endif // EEPROM_HAL_H
