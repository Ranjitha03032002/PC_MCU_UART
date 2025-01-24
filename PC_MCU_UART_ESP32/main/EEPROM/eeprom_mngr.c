// eeprom_mngr.c

#include "eeprom_mngr.h"

void EEPROM_Init()
{
    esp_err_t ret;
    ret = init_eeprom();
    if (ret != ESP_OK)
    {
        // ESP_LOGE(EEPROM_TAG, "Init Fail%x", ret);e
        return;
    }
}