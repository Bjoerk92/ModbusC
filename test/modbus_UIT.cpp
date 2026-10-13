/**
 * @file modbus_UIT.cpp
 * @author Anders Bjørk (anders.bjoerk.unf@gmail.com)
 * @brief Modbus Unit test 
 * @version 0.1
 * @date 2026-10-13
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include <gtest/gtest.h>
#include "modbus.h"


TEST(modbus_slave_init, HandlesZeroInput)
{
    ptr_md_config config = NULL;
    EXPECT_EQ(modbus_slave_init(config), MODBUS_ERROR_INVALID_PARAM);
}