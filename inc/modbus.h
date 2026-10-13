/**
 * @file modbus.h
 * @author Anders Bjørk (anders.bjoerk.unf@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2026-10-08
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once

#include <stdint.h>
#include "modbus_defines.h"


typedef enum MODBUS_STATUS_Etag
{
    MODBUS_OK = 0,
    MODBUS_ERROR = 1,
    MODBUS_TIMEOUT = 2,
    MODBUS_ERROR_INVALID_PARAM = 3,
} md_status_e;

typedef md_exception_code_e (*Read_registers_cb)(uint16_t starting_address, uint16_t quantity, uint16_t* registers);
typedef md_exception_code_e (*Write_registers_cb)(uint16_t starting_address, uint16_t quantity, uint16_t* registers);
typedef md_exception_code_e (*read_coils_cb)(uint16_t starting_address, uint16_t quantity, uint8_t* coils);
typedef md_exception_code_e (*write_coils_cb)(uint16_t starting_address, uint16_t quantity, uint8_t* coils);

typedef struct MODBUS_SLAVE_CONFIG_Ttag
{
    uint8_t slave_address; // The address of the Modbus slave device
    uint8_t reserved[3]; // Reserved for future use, aligned to 4 bytes
    
    read_coils_cb read_coils; // Function pointer to read coils
    write_coils_cb write_coils; // Function pointer to write coils

    Read_registers_cb read_registers; // Function pointer to read registers
    Write_registers_cb write_registers; // Function pointer to write registers

} md_config, *ptr_md_config;

#if __cplusplus
extern "C" {
#endif
/**
 * Public modbus slave functions
 */
md_status_e modbus_slave_init(ptr_md_config config);
uint32_t modbus_slave_rtu_response(uint8_t* frame, uint32_t length);
uint32_t modbus_slave_ip_response(uint8_t* frame);

/*
* Public Modbus Master functions
*/
md_status_e modbus_master_init();
md_status_e modbus_master_read_coils(uint8_t address, uint16_t );

#if __cplusplus
}
#endif