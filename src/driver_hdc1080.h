/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_hdc1080.h
 * @brief     driver hdc1080 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2023-04-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2023/04/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_HDC1080_H
#define DRIVER_HDC1080_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup hdc1080_driver hdc1080 driver function
 * @brief    hdc1080 driver modules
 * @{
 */

/**
 * @addtogroup hdc1080_base_driver
 * @{
 */

/**
 * @brief hdc1080 bool enumeration definition
 */
typedef enum
{
    HDC1080_BOOL_FALSE = 0x00,        /**< disable */
    HDC1080_BOOL_TRUE  = 0x01,        /**< enable */
} hdc1080_bool_t;

/**
 * @brief hdc1080 mode enumeration definition
 */
typedef enum
{
    HDC1080_MODE_OR       = 0x00,        /**< temperature or humidity is acquired */
    HDC1080_MODE_SEQUENCE = 0x01,        /**< temperature and humidity are acquired in sequence, temperature first */
} hdc1080_mode_t;

/**
 * @brief hdc1080 temperature resolution enumeration definition
 */
typedef enum
{
    HDC1080_TEMPERATURE_RESOLUTION_14_BIT = 0x00,        /**< 14 bit */
    HDC1080_TEMPERATURE_RESOLUTION_11_BIT = 0x01,        /**< 11 bit */
} hdc1080_temperature_resolution_t;

/**
 * @brief hdc1080 humidity resolution enumeration definition
 */
typedef enum
{
    HDC1080_HUMIDITY_RESOLUTION_14_BIT = 0x00,        /**< 14 bit */
    HDC1080_HUMIDITY_RESOLUTION_11_BIT = 0x01,        /**< 11 bit */
    HDC1080_HUMIDITY_RESOLUTION_8_BIT  = 0x02,        /**< 8 bit */
} hdc1080_humidity_resolution_t;

/**
 * @brief hdc1080 battery status enumeration definition
 */
typedef enum
{
    HDC1080_BATTERY_STATUS_OVER_2P8_V = 0x00,        /**< battery voltage > 2.8v */
    HDC1080_BATTERY_STATUS_LESS_2P8_V = 0x01,        /**< battery voltage < 2.8v */
} hdc1080_battery_status_t;

/**
 * @brief hdc1080 handle structure definition
 */
typedef struct hdc1080_handle_s
{
    uint8_t (*iic_init)(void);                                                         /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                       /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);       /**< point to an iic_write function address */
    uint8_t (*iic_read_with_wait)(uint8_t addr, uint8_t reg,
                                  uint8_t *buf, uint16_t len);                         /**< point to an iic_read_with_wait function address */
    void (*delay_ms)(uint32_t ms);                                                     /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                   /**< point to a debug_print function address */
    uint8_t inited;                                                                    /**< inited flag */
} hdc1080_handle_t;

/**
 * @brief hdc1080 information structure definition
 */
typedef struct hdc1080_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} hdc1080_info_t;

/**
 * @}
 */

/**
 * @defgroup hdc1080_link_driver hdc1080 link driver function
 * @brief    hdc1080 link driver modules
 * @ingroup  hdc1080_driver
 * @{
 */

/**
 * @brief     initialize hdc1080_handle_t structure
 * @param[in] HANDLE pointer to an hdc1080 handle structure
 * @param[in] STRUCTURE hdc1080_handle_t
 * @note      none
 */
#define DRIVER_HDC1080_LINK_INIT(HANDLE, STRUCTURE)             memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE pointer to an hdc1080 handle structure
 * @param[in] FUC pointer to an iic_init function address
 * @note      none
 */
#define DRIVER_HDC1080_LINK_IIC_INIT(HANDLE, FUC)              (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE pointer to an hdc1080 handle structure
 * @param[in] FUC pointer to an iic_deinit function address
 * @note      none
 */
#define DRIVER_HDC1080_LINK_IIC_DEINIT(HANDLE, FUC)            (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE pointer to an hdc1080 handle structure
 * @param[in] FUC pointer to an iic_read function address
 * @note      none
 */
#define DRIVER_HDC1080_LINK_IIC_READ(HANDLE, FUC)              (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_read_with_wait function
 * @param[in] HANDLE pointer to an hdc1080 handle structure
 * @param[in] FUC pointer to an iic_read_with_wait function address
 * @note      none
 */
#define DRIVER_HDC1080_LINK_IIC_READ_WITH_WAIT(HANDLE, FUC)    (HANDLE)->iic_read_with_wait = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE pointer to an hdc1080 handle structure
 * @param[in] FUC pointer to an iic_write function address
 * @note      none
 */
#define DRIVER_HDC1080_LINK_IIC_WRITE(HANDLE, FUC)             (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to an hdc1080 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_HDC1080_LINK_DELAY_MS(HANDLE, FUC)              (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to an hdc1080 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_HDC1080_LINK_DEBUG_PRINT(HANDLE, FUC)           (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup hdc1080_base_driver hdc1080 base driver function
 * @brief    hdc1080 base driver modules
 * @ingroup  hdc1080_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to an hdc1080 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t hdc1080_info(hdc1080_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to an hdc1080 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic init failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 read id failed
 *            - 5 id is invalid
 *            - 6 reset failed
 * @note      none
 */
uint8_t hdc1080_init(hdc1080_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to an hdc1080 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hdc1080_deinit(hdc1080_handle_t *handle);

/**
 * @brief      read the temperature and humidity data
 * @param[in]  *handle pointer to an hdc1080 handle structure
 * @param[out] *temperature_raw pointer to a raw temperature buffer
 * @param[out] *temperature_s pointer to a converted temperature buffer
 * @param[out] *humidity_raw pointer to a raw humidity buffer
 * @param[out] *humidity_s pointer to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature humidity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_read_temperature_humidity(hdc1080_handle_t *handle, uint16_t *temperature_raw, float *temperature_s,
                                          uint16_t *humidity_raw, float *humidity_s);

/**
 * @brief      read the temperature
 * @param[in]  *handle pointer to an hdc1080 handle structure
 * @param[out] *temperature_raw pointer to a raw temperature buffer
 * @param[out] *temperature_s pointer to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_read_temperature(hdc1080_handle_t *handle, uint16_t *temperature_raw, float *temperature_s);

/**
 * @brief      read the humidity data
 * @param[in]  *handle pointer to an hdc1080 handle structure
 * @param[out] *humidity_raw pointer to a raw humidity buffer
 * @param[out] *humidity_s pointer to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read humidity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_read_humidity(hdc1080_handle_t *handle, uint16_t *humidity_raw, float *humidity_s);

/**
 * @brief     software reset
 * @param[in] *handle pointer to an hdc1080 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 software reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hdc1080_software_reset(hdc1080_handle_t *handle);

/**
 * @brief     enable or disable heater
 * @param[in] *handle pointer to an hdc1080 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set heater failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hdc1080_set_heater(hdc1080_handle_t *handle, hdc1080_bool_t enable);

/**
 * @brief      get the heater status
 * @param[in]  *handle pointer to an hdc1080 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get heater failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_get_heater(hdc1080_handle_t *handle, hdc1080_bool_t *enable);

/**
 * @brief     set the chip mode
 * @param[in] *handle pointer to an hdc1080 handle structure
 * @param[in] mode chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hdc1080_set_mode(hdc1080_handle_t *handle, hdc1080_mode_t mode);

/**
 * @brief      get the chip mode
 * @param[in]  *handle pointer to an hdc1080 handle structure
 * @param[out] *mode pointer to a mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_get_mode(hdc1080_handle_t *handle, hdc1080_mode_t *mode);

/**
 * @brief      get battery status
 * @param[in]  *handle pointer to an hdc1080 handle structure
 * @param[out] *status pointer to a battery status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get battery status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_get_battery_status(hdc1080_handle_t *handle, hdc1080_battery_status_t *status);

/**
 * @brief     set temperature resolution
 * @param[in] *handle pointer to an hdc1080 handle structure
 * @param[in] resolution temperature resolution
 * @return    status code
 *            - 0 success
 *            - 1 set temperature resolution failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hdc1080_set_temperature_resolution(hdc1080_handle_t *handle, hdc1080_temperature_resolution_t resolution);

/**
 * @brief      get temperature resolution
 * @param[in]  *handle pointer to an hdc1080 handle structure
 * @param[out] *resolution pointer to a temperature resolution buffer
 * @return     status code
 *             - 0 success
 *             - 1 get temperature resolution failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_get_temperature_resolution(hdc1080_handle_t *handle, hdc1080_temperature_resolution_t *resolution);

/**
 * @brief     set humidity resolution
 * @param[in] *handle pointer to an hdc1080 handle structure
 * @param[in] resolution humidity resolution
 * @return    status code
 *            - 0 success
 *            - 1 set humidity resolution failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hdc1080_set_humidity_resolution(hdc1080_handle_t *handle, hdc1080_humidity_resolution_t resolution);

/**
 * @brief      get humidity resolution
 * @param[in]  *handle pointer to an hdc1080 handle structure
 * @param[out] *resolution pointer to a humidity resolution buffer
 * @return     status code
 *             - 0 success
 *             - 1 get humidity resolution failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_get_humidity_resolution(hdc1080_handle_t *handle, hdc1080_humidity_resolution_t *resolution);

/**
 * @brief      get serial id
 * @param[in]  *handle pointer to an hdc1080 handle structure
 * @param[out] *id pointer to an id buffer
 * @return     status code
 *             - 0 success
 *             - 1 get serial id failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_get_serial_id(hdc1080_handle_t *handle, uint8_t id[6]);

/**
 * @}
 */

/**
 * @defgroup hdc1080_extend_driver hdc1080 extend driver function
 * @brief    hdc1080 extend driver modules
 * @ingroup  hdc1080_driver
 * @{
 */

/**
 * @brief     set chip register
 * @param[in] *handle pointer to an hdc1080 handle structure
 * @param[in] reg register address
 * @param[in] data written data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hdc1080_set_reg(hdc1080_handle_t *handle, uint8_t reg, uint16_t data);

/**
 * @brief      get chip register
 * @param[in]  *handle pointer to an hdc1080 handle structure
 * @param[in]  reg register address
 * @param[out] *data pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_get_reg(hdc1080_handle_t *handle, uint8_t reg, uint16_t *data);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
