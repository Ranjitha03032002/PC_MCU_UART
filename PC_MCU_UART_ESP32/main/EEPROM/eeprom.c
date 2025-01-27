// eeprom_hal.c

#include "eeprom.h"
const char handle[] = "storage";
esp_err_t init_eeprom()
{
    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        // NVS partition was truncated, erase and re-initialize
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    return ret;
}

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

esp_err_t write_TripID_eeprom(void)
{
    // nvs_handle_t TripID_handle;
    // esp_err_t ret;
    // uint16_t tripidset = 0;

    // ret = nvs_open(handle, NVS_READWRITE, &TripID_handle);
    // if (ret != ESP_OK)
    // {
    //     return ret;
    // }

    // ret = nvs_set_u16(TripID_handle, tid_i16, tripidset);
    // if (ret != ESP_OK)
    // {
    //     return ret;
    // }

    // ret = nvs_commit(TripID_handle);
    // if (ret != ESP_OK)
    // {
    //     return ret;
    // }

    // nvs_close(TripID_handle);
    return ESP_OK;
}

esp_err_t read_TripID_eeprom(void)
{
    // nvs_handle_t TripID_handle;
    // esp_err_t ret;

    // ret = nvs_open(handle, NVS_READONLY, &TripID_handle);
    // if (ret != ESP_OK)
    // {
    //     nvs_close(TripID_handle);
    //     return ESP_OK;
    // }

    // ret = nvs_get_u16(TripID_handle, tid_i16, &TripId_EEE);
    // if (ret == ESP_ERR_NVS_NOT_FOUND)
    // {
    //     // Data not found, initialize with dummy data
    //     TripId_EEE = tid_value_init;
    // }
    return ESP_OK;
}

esp_err_t write_TripID_byte_eeprom(uint8_t byte_to_store, uint16_t offset)
{
    nvs_handle_t TripID_handle;
    esp_err_t ret;

    // Open NVS storage handle
    ret = nvs_open(handle, NVS_READWRITE, &TripID_handle);
    if (ret != ESP_OK)
    {
        return ret;
    }

    // Write the byte at the given offset
    char key[16];
    snprintf(key, sizeof(key), "byte_%d", offset);       // Generate a unique key for each byte
    ret = nvs_set_u8(TripID_handle, key, byte_to_store); // Store the byte
    if (ret != ESP_OK)
    {
        nvs_close(TripID_handle);
        return ret;
    }

    // Commit changes to ensure the byte is saved
    ret = nvs_commit(TripID_handle);
    if (ret != ESP_OK)
    {
        nvs_close(TripID_handle);
        return ret;
    }

    // Close the handle
    nvs_close(TripID_handle);
    return ESP_OK;
}

esp_err_t read_TripID_bytes_eeprom(uint8_t *buffer, uint16_t length)
{
    nvs_handle_t TripID_handle;
    esp_err_t ret;

    ret = nvs_open(handle, NVS_READONLY, &TripID_handle);
    if (ret != ESP_OK)
    {
        return ret;
    }

    for (uint16_t i = 0; i < length; i++)
    {
        char key[16];
        snprintf(key, sizeof(key), "byte_%d", i);

        uint8_t byte_value = 0;
        ret = nvs_get_u8(TripID_handle, key, &byte_value);
        if (ret != ESP_OK)
        {
            nvs_close(TripID_handle);
            return ret;
        }
        buffer[i] = byte_value;
        // Print the retrieved value
        printf("Read from EEPROM: Key='%s', Value='%c' (0x%02X)\n", key, byte_value, byte_value);
        // if (byte_value >= 32 && byte_value <= 126) // Printable ASCII range
        // {
        //     printf("%c", byte_value);
        // }
        // else
        // {
        //     printf("\\x%02X", byte_value); // Non-printable characters as hex
        // }
    }

    nvs_close(TripID_handle);
    return ESP_OK;
}

esp_err_t erase_eeprom(void)
{
    nvs_handle_t erase_eeprom_handle;
    esp_err_t ret;
    ret = nvs_open(handle, NVS_READWRITE, &erase_eeprom_handle);
    if (ret == ESP_OK)
    {
        ret = nvs_erase_all(handle);
        nvs_commit(handle);
        nvs_close(handle);
    }
    return ret;
}

esp_err_t write_TripID_chunk_eeprom(const uint8_t *buffer, size_t length, size_t offset)
{
    nvs_handle_t TripID_handle;
    esp_err_t ret;

    ret = nvs_open(handle, NVS_READWRITE, &TripID_handle);
    if (ret != ESP_OK)
    {
        return ret;
    }

    char key[16];
    snprintf(key, sizeof(key), "chunk_%d", offset);

    ret = nvs_set_blob(TripID_handle, key, buffer, length);
    if (ret != ESP_OK)
    {
        nvs_close(TripID_handle);
        return ret;
    }

    ret = nvs_commit(TripID_handle);
    nvs_close(TripID_handle);
    return ret;
}
