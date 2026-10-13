/**
 * @file modbus_crc.h
 * @author Anders Bjørk (anders.bjoerk.unf@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2026-10-09
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * Public Function
 */
uint16_t modbus_crc16(const uint8_t* data, size_t length);
bool modbus_validate_crc16(const uint8_t* data, size_t length);
void modbus_add_crc16(uint8_t* data, size_t length);