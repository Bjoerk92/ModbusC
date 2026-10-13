/**
 * @file modbus_slave.c
 * @author Anders Bjørk (anders.bjoerk.unf@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2026-10-08
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "modbus.h"
#include "modbus_crc.h"

static md_config slave_config = {};

/****** Private function prototypes ******/
static uint32_t write_exception_response(md_header_t* frame, md_exception_code_e exception);
static uint32_t handle_frame(uint8_t* frame);
static uint32_t read_coils(uint8_t* frame);


/**
 * @brief Function to configure the Modbus slave.
 * 
 * @param config pointer to modbus configuration setup
 * @return md_status_e Modbus status
 */
md_status_e modbus_slave_init(ptr_md_config config)
{
    if (config == NULL)
    {
        return MODBUS_ERROR_INVALID_PARAM;
    }

    slave_config = *config;

    return MODBUS_OK;
}

/**
 * @brief Function will handle the modbus RTU request. 
 * 
 * @param frame pointer to request buffer. note same buffer is used for response
 * @param length number of bytes in request.
 * @return uint32_t number of bytes in response.
 */
uint32_t modbus_slave_rtu_response(uint8_t* frame, uint32_t length)
{
    uint32_t ret_size = 0;  // size of returning frame. 0 = dropped response
    
    if (modbus_validate_crc16(frame, length))
    {
        // handle frame
        ret_size = handle_frame(frame);

        // add crc to the frame. 
        modbus_add_crc16(frame, ret_size);
        ret_size += 2; // add crc byte into length.
    }

    // return the size of the frame.
    return ret_size;
}


uint32_t modbus_slave_ip_response(uint8_t* frame)
{
    uint32_t ret_size = 0;

   

    return ret_size;
}



static uint32_t write_exception_response(md_header_t* frame, md_exception_code_e exception)
{
    frame->function_code |= 80;

    md_exception_t* excetpion_code = (md_exception_t*)&frame->data[0];
    excetpion_code->exception = exception;
    return ((uint32_t)(sizeof(md_header_t) + sizeof(md_exception_code_e)));
}

static uint32_t handle_frame(uint8_t* frame)
{
    uint32_t ret_size = 0;
    md_header_t* header = (md_header_t*)frame; 

    if (header->Address == slave_config.slave_address)
    {
        switch (header->function_code)
        {
            case READ_COILS:
            {
                break;
            }
            default:
            {
                ret_size = write_exception_response(header, ILLEGAL_FUNCTION);
            }
        }
    }

    return ret_size;
}

static uint32_t read_coils(uint8_t* frame)
{
    READ_COILS_REQUEST* req = (READ_COILS_REQUEST*)frame;
    READ_COILS_RESPONSE* rsp = (READ_COILS_RESPONSE*)frame;
    uint32_t ret_size = 0;
    
    if (slave_config.read_coils != NULL)
    {
        uint32_t coil_bytes = (req->quantity + 7U) / 8U;
        uint8_t coils[coil_bytes];

        slave_config.read_coils(req->starting_address, req->quantity, coils);

        rsp->byte_count = coil_bytes;
        for (uint32_t i = 0; i < coil_bytes; i++)
        {
            rsp->coil_status[i] = coils[i];
        }
    }
    else
    {
        ret_size = write_exception_response((md_header_t*)frame, ILLEGAL_FUNCTION);
    }
    return ret_size;
}