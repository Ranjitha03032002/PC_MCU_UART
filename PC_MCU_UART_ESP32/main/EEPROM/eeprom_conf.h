#ifndef EEPROM_CONF_H
#define EEPROM_CONF_H

#include "stdint.h"


extern const char handle[]   ;

extern const char vi_blob[];
extern const uint8_t vi_vin_init[];
extern const uint8_t vi_bat_init[];
extern const uint8_t vi_firm_init[];

extern const char tds_i8[]     ;
extern const int tds_pointer_init;

extern const char cl_i8[];
extern const uint8_t cl_init;

extern const char odo_i16[];
extern const uint32_t odo_value_init;

extern const char tid_i16[];
extern const uint32_t tid_value_init;

extern const char ltt_u32[];
extern const uint32_t ltt_value_init;

extern const char eco_u32[];               
extern const uint32_t eco_value_init;      
 
extern const char fit_u32[];               
extern const uint32_t fit_value_init;      
 
extern const char usr_u32[];              
extern const uint32_t usr_value_init;      
 
extern const char urb_u32[];               
extern const uint32_t urb_value_init;  

extern const char Pri_u32[];
extern const uint8_t pri_value_init;

#endif //EEPROM_CONF_H