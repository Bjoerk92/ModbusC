/**
 * @file modbus.h
 * @author Anders Bjørk (anders.bjoerk.unf@gmail.com)
 * @brief General modbus definitions and functions.
 * @version 0.1
 * @date 2026-10-08
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#pragma once

#include <stdint.h>

#define MODBUS_RTU_MAX_LENGTH 256
#define MODBUS_TCP_MAX_LENGTH 260
#define MODBUS_UDP_MAX_LENGTH 260

#if !defined(SWAP_16)
static inline uint16_t SWAP_16(uint16_t x)
{
    return (x << 8) | (x >> 8);
}
#endif


/**
 * @brief Defines the function codes used in Modbus communication.
 * 
 */
typedef enum MODBUS_FUNCTION_CODE_Etag
{
    READ_COILS                          = 0x01, // Read multiple coils (0x01)
    READ_DISCRETE_INPUTS                = 0x02, // Read multiple discrete inputs (0x02)
    READ_HOLDING_REGISTERS              = 0x03, // Read multiple holding registers (0x03)
    READ_INPUT_REGISTERS                = 0x04, // Read multiple input registers (0x04)
    WRITE_SINGLE_COIL                   = 0x05, // Write single coil (0x05)
    WRITE_SINGLE_REGISTER               = 0x06, // Write single holding register (0x06)
    READ_EXCEPTION_STATUS               = 0x07, // Read exception status - Serial only(0x07)
    DIAGNOSTICS                         = 0x08, // Diagnostics - Serial only (0x08)
    GET_COMM_EVENT_COUNTER              = 0x0B, // Get comm event counter - Serial only (0x0B)
    GET_COMM_EVENT_LOG                  = 0x0C, // Get comm event log - Serial only (0x0C)
    WRITE_MULTIPLE_COILS                = 0x0F, // Write multiple coils (0x0F)
    WRITE_MULTIPLE_REGISTERS            = 0x10, // Write multiple holding registers (0x10)
    REPORT_SERVER_ID                     = 0x11, // Report server ID (0x11)
    READ_FILE_RECORDS                   = 0x14, // Read file records (0x14)
    WRITE_FILE_RECORDS                  = 0x15, // Write file records (0x15)
    MASK_WRITE_REGISTER                 = 0x16, // Mask write register (0x16)
    READ_WRITE_MULTIPLE_REGISTERS       = 0x17, // Read/write multiple registers (0x17)
    READ_FIFO_QUEUE                     = 0x18, // Read FIFO queue (0x18)
    ENCAPSULATED_INTERFACE_TRANSPORT    = 0x2B  // Encapsulated interface transport (0x2B)
} MODBUS_FUNCTION_CODE;

/**
 * @brief Defines the exception codes used in Modbus communication.
 * 
 */
typedef enum MODBUS_EXCEPTION_CODE_Etag
{
    ILLEGAL_FUNCTION                        = 0x01, // Illegal function (0x01)
    ILLEGAL_DATA_ADDRESS                    = 0x02, // Illegal data address (0x02)
    ILLEGAL_DATA_VALUE                      = 0x03, // Illegal data value (0x03)
    SLAVE_DEVICE_FAILURE                    = 0x04, // Slave device failure (0x04)
    ACKNOWLEDGE                             = 0x05, // Acknowledge (0x05)
    SLAVE_DEVICE_BUSY                       = 0x06, // Slave device busy (0x06)
    MEMORY_PARITY_ERROR                     = 0x08, // Memory parity error (0x08)
    GATEWAY_PATH_UNAVAILABLE                = 0x0A, // Gateway path unavailable (0x0A)
    GATEWAY_TARGET_DEVICE_FAILED_TO_RESPOND = 0x0B // Gateway target device failed to respond (0x0B)
} md_exception_code_e;

/**
 * @brief Defines the structure of a Modbus header, which includes the address, function code, and data.
 * @note This header can be used both for Modbus master and slave communication, depending on the context.
 * 
 */
typedef struct MODBUS_HEADER_Ttag
{
    uint8_t                 Address;            // modbus address, either slave or master address depending on the context
    MODBUS_FUNCTION_CODE    function_code : 8;  // fnction code, see MODBUS_FUNCTION_CODE enum
    uint8_t                 data[];             // data, max 252 bytes, see modbus specification for details
} md_header_t;

/**
 * @brief Defines the structure for Modbus MBAP
 * 
 */
typedef struct MBAP_Ttag
{
    uint16_t transaction_id;        // Transaction Identifier
    uint16_t protocol_id;           // Protocol Identifier (0 for Modbus)
    uint16_t length;                // Length of the remaining bytes in the message
    uint8_t unit_id;                // Unit Identifier (slave address)
    md_header_t modbus_header;      // Modbus header containing the function code and data
} MBAP_t;

typedef struct MODBUS_EXCEPTION_RSP_Ttag
{
    uint8_t exception;
}md_exception_t;

/**
 * @brief Defines the structure of a Modbus request to read coils, including the starting address and quantity of coils to read.
 * 
 */
typedef struct READ_COILS_REQUEST_Ttag
{
    uint16_t starting_address; // Starting address of the coils to read
    uint16_t quantity;         // Number of coils to read
} READ_COILS_REQUEST;

/**
 * @brief Defines the structure of a Modbus response for reading coils, including the byte count and the status of the coils.
 * 
 */
typedef struct READ_COILS_RESPONSE_Ttag
{
    uint8_t byte_count;        // Number of data bytes to follow
    uint8_t coil_status[];     // Status of the coils, packed as bits (1 = ON, 0 = OFF)
} READ_COILS_RESPONSE;

/**
 * @brief Defines the structure of a Modbus request to read discrete inputs, including the starting address and quantity of inputs to read.
 * 
 */
typedef struct READ_DISCRETE_INPUTS_REQUEST_Ttag
{
    uint16_t starting_address; // Starting address of the discrete inputs to read
    uint16_t quantity;         // Number of discrete inputs to read
} READ_DISCRETE_INPUTS_REQUEST;

/**
 * @brief Defines the structure of a Modbus response for reading discrete inputs, including the byte count and the status of the inputs.
 * 
 */
typedef struct READ_DISCRETE_INPUTS_RESPONSE_Ttag
{
    uint8_t byte_count;        // Number of data bytes to follow
    uint8_t input_status[];    // Status of the discrete inputs, packed as bits (1 = ON, 0 = OFF)
} READ_DISCRETE_INPUTS_RESPONSE;

