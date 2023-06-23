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
 * @file      driver_hdc1080_basic.h
 * @brief     driver hdc1080 basic header file
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

#ifndef DRIVER_HDC1080_BASIC_H
#define DRIVER_HDC1080_BASIC_H

#include "driver_hdc1080_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup hdc1080_example_driver hdc1080 example driver function
 * @brief    hdc1080 example driver modules
 * @ingroup  hdc1080_driver
 * @{
 */

/**
 * @brief hdc1080 basic example default definition
 */
#define HDC1080_BASIC_DEFAULT_HEATER                         HDC1080_BOOL_FALSE                           /**< disable heater */
#define HDC1080_BASIC_DEFAULT_MODE                           HDC1080_MODE_SEQUENCE                        /**< temperature and humidity are acquired in sequence */
#define HDC1080_BASIC_DEFAULT_TEMPERATURE_RESOLUTION         HDC1080_TEMPERATURE_RESOLUTION_14_BIT        /**< 14 bit */
#define HDC1080_BASIC_DEFAULT_HUMIDITY_RESOLUTION            HDC1080_HUMIDITY_RESOLUTION_14_BIT           /**< 14 bit */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t hdc1080_basic_init(void);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t hdc1080_basic_deinit(void);

/**
 * @brief      basic example read
 * @param[out] *temperature points to a converted temperature buffer
 * @param[out] *humidity points to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t hdc1080_basic_read(float *temperature, float *humidity);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
