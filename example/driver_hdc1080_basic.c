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
 * @file      driver_hdc1080_basic.c
 * @brief     driver hdc1080 basic source file
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

#include "driver_hdc1080_basic.h"

static hdc1080_handle_t gs_handle;        /**< hdc1080 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t hdc1080_basic_init(void)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_HDC1080_LINK_INIT(&gs_handle, hdc1080_handle_t); 
    DRIVER_HDC1080_LINK_IIC_INIT(&gs_handle, hdc1080_interface_iic_init);
    DRIVER_HDC1080_LINK_IIC_DEINIT(&gs_handle, hdc1080_interface_iic_deinit);
    DRIVER_HDC1080_LINK_IIC_READ(&gs_handle, hdc1080_interface_iic_read);
    DRIVER_HDC1080_LINK_IIC_READ_WITH_WAIT(&gs_handle, hdc1080_interface_iic_read_with_wait);
    DRIVER_HDC1080_LINK_IIC_WRITE(&gs_handle, hdc1080_interface_iic_write);
    DRIVER_HDC1080_LINK_DELAY_MS(&gs_handle, hdc1080_interface_delay_ms);
    DRIVER_HDC1080_LINK_DEBUG_PRINT(&gs_handle, hdc1080_interface_debug_print);
    
    /* hdc1080 init */
    res = hdc1080_init(&gs_handle);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: init failed.\n");
        
        return 1;
    }
    
    /* set default heater */
    res = hdc1080_set_heater(&gs_handle, HDC1080_BASIC_DEFAULT_HEATER);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set heater failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default mode */
    res = hdc1080_set_mode(&gs_handle, HDC1080_BASIC_DEFAULT_MODE);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set mode failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default temperature resolution */
    res = hdc1080_set_temperature_resolution(&gs_handle, HDC1080_BASIC_DEFAULT_TEMPERATURE_RESOLUTION);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set temperature resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default humidity resolution */
    res = hdc1080_set_humidity_resolution(&gs_handle, HDC1080_BASIC_DEFAULT_HUMIDITY_RESOLUTION);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set humidity resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *temperature pointer to a converted temperature buffer
 * @param[out] *humidity pointer to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t hdc1080_basic_read(float *temperature, float *humidity)
{
    uint16_t temperature_raw;
    uint16_t humidity_raw;
    
    /* read temperature and humidity */
    if (hdc1080_read_temperature_humidity(&gs_handle, (uint16_t *)&temperature_raw, temperature, 
                                         (uint16_t *)&humidity_raw, humidity) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t hdc1080_basic_deinit(void)
{
    /* deinit hdc1080 and close bus */
    if (hdc1080_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
