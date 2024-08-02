/**
 * \file
 * \brief BitField hardware abstraction layer
 *
 * Autogenerated with yoda-gen 1.1.0. Do not modify
 *
 * \copyright Copyright (c) 2020 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

 #ifndef __ADRV9001_BF_HAL_H__
 #define __ADRV9001_BF_HAL_H__

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * \brief Write a field within a register (read, modify, write)
 *
 * Example:
 * Say we have a register at address 0xBEEF with a FIELD in [d2:d1]:
 *   | d7 | d6 | d5 | d4 | d3 |  FIELD  | d0 |
 *
 * To write to the FIELD a value of 2, call
 * \code
 * adi_bf_hal_Field_Write(device, 0xBEEF, 0x2, 0x6, 0x1);
 * \endcode
 *
 * Bits [d7:d3] and d0 should not be modified, generally requiring a read, modify, and write
 *
 * \param[in] device    Context variable
 * \param[in] address   The address of the register
 * \param[in] value     The value to be written
 * \param[in] mask      The mask of the field within the register
 * \param[in] startBit  The starting (lsb) bit position of the field
 *
 * \returns Zero (0) to indicate success; error otherwise
 */
int32_t adi_bf_hal_Field_Write(void *device, uint16_t address, uint8_t value, uint8_t mask, uint8_t startBit);

/**
 * \brief Read a field within a register
 *
 * \param[in]  device   Context variable
 * \param[in]  address  The address of the register
 * \param[out] value    The value to be written
 * \param[in]  mask     The mask of the field within the register
 * \param[in]  startBit The starting (lsb) bit position of the field
 *
 * \returns Zero (0) to indicate success; error otherwise
 */
int32_t adi_bf_hal_Field_Read(void *device, uint16_t address, uint8_t *value, uint8_t mask, uint8_t startBit);

/**
 * \brief Write to a register
 *
 * \param[in] device    Context variable
 * \param[in] address   The address of the register
 * \param[in] value     The value to be written
 *
 * \returns Zero (0) to indicate success; error otherwise
 */
int32_t adi_bf_hal_Register_Write(void *device, uint16_t address, uint8_t value);

/**
 * \brief Read from a register
 *
 * \param[in]  device   Context variable
 * \param[in]  address  The address of the register
 * \param[out] value    The value to be written
 *
 * \returns Zero (0) to indicate success; error otherwise
 */
int32_t adi_bf_hal_Register_Read(void *device, uint16_t address, uint8_t *value);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __ADRV9001_BF_HAL_H__