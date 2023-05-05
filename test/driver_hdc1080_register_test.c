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
 * @file      driver_hdc1080_register_test.c
 * @brief     driver hdc1080 register test source file
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
 
#include "driver_hdc1080_register_test.h"

static hdc1080_handle_t gs_handle;        /**< hdc1080 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t hdc1080_register_test(void)
{
    uint8_t res;
    uint8_t id[6];
    hdc1080_info_t info;
    hdc1080_bool_t enable;
    hdc1080_battery_status_t status;
    hdc1080_mode_t mode;
    hdc1080_temperature_resolution_t t_resolution;
    hdc1080_humidity_resolution_t h_resolution;

    /* link interface function */
    DRIVER_HDC1080_LINK_INIT(&gs_handle, hdc1080_handle_t); 
    DRIVER_HDC1080_LINK_IIC_INIT(&gs_handle, hdc1080_interface_iic_init);
    DRIVER_HDC1080_LINK_IIC_DEINIT(&gs_handle, hdc1080_interface_iic_deinit);
    DRIVER_HDC1080_LINK_IIC_READ(&gs_handle, hdc1080_interface_iic_read);
    DRIVER_HDC1080_LINK_IIC_READ_WITH_WAIT(&gs_handle, hdc1080_interface_iic_read_with_wait);
    DRIVER_HDC1080_LINK_IIC_WRITE(&gs_handle, hdc1080_interface_iic_write);
    DRIVER_HDC1080_LINK_DELAY_MS(&gs_handle, hdc1080_interface_delay_ms);
    DRIVER_HDC1080_LINK_DEBUG_PRINT(&gs_handle, hdc1080_interface_debug_print);
    
    /* get information */
    res = hdc1080_info(&info);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip info */
        hdc1080_interface_debug_print("hdc1080: chip is %s.\n", info.chip_name);
        hdc1080_interface_debug_print("hdc1080: manufacturer is %s.\n", info.manufacturer_name);
        hdc1080_interface_debug_print("hdc1080: interface is %s.\n", info.interface);
        hdc1080_interface_debug_print("hdc1080: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        hdc1080_interface_debug_print("hdc1080: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        hdc1080_interface_debug_print("hdc1080: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        hdc1080_interface_debug_print("hdc1080: max current is %0.2fmA.\n", info.max_current_ma);
        hdc1080_interface_debug_print("hdc1080: max temperature is %0.1fC.\n", info.temperature_max);
        hdc1080_interface_debug_print("hdc1080: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start register test */
    hdc1080_interface_debug_print("hdc1080: start register test.\n");
    
    /* init */
    res = hdc1080_init(&gs_handle);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: init failed.\n");
        
        return 1;
    }
    
    /* hdc1080_get_serial_id test */
    hdc1080_interface_debug_print("hdc1080: hdc1080_get_serial_id test.\n");
    
    /* get serial id */
    res = hdc1080_get_serial_id(&gs_handle, id);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: get serial id failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: serial id is 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X.\n",
                                  id[0], id[1], id[2], id[3], id[4], id[5]);
    
    /* hdc1080_get_battery_status test */
    hdc1080_interface_debug_print("hdc1080: hdc1080_get_battery_status test.\n");
    
    /* get battery status */
    res = hdc1080_get_battery_status(&gs_handle, &status);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: get battery status failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: battery status is %s.\n",
                                  status == HDC1080_BATTERY_STATUS_OVER_2P8_V ? "over 2.8V" : "less 2.8V");
    
    /* hdc1080_set_heater/hdc1080_get_heater test test */
    hdc1080_interface_debug_print("hdc1080: hdc1080_set_heater/hdc1080_get_heater test.\n");
    
    /* disable heater */
    res = hdc1080_set_heater(&gs_handle, HDC1080_BOOL_FALSE);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set heater failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable heater */
    hdc1080_interface_debug_print("hdc1080: disable heater.\n");
    
    /* get heater */
    res = hdc1080_get_heater(&gs_handle, &enable);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: get heater failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: check heater %s.\n", enable == HDC1080_BOOL_FALSE ? "ok" : "error");
    
    /* enable heater */
    res = hdc1080_set_heater(&gs_handle, HDC1080_BOOL_TRUE);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set heater failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable heater */
    hdc1080_interface_debug_print("hdc1080: enable heater.\n");
    
    /* get heater */
    res = hdc1080_get_heater(&gs_handle, &enable);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: get heater failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: check heater %s.\n", enable == HDC1080_BOOL_TRUE ? "ok" : "error");
    
    /* hdc1080_set_mode/hdc1080_get_mode test */
    hdc1080_interface_debug_print("hdc1080: hdc1080_set_mode/hdc1080_get_mode test.\n");
    
    /* temperature or humidity is acquired mode */
    res = hdc1080_set_mode(&gs_handle, HDC1080_MODE_OR);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set mode failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* temperature or humidity is acquired mode */
    hdc1080_interface_debug_print("hdc1080: temperature or humidity is acquired mode.\n");
    
    /* get mode */
    res = hdc1080_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: get mode failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: check mode %s.\n", mode == HDC1080_MODE_OR ? "ok" : "error");
    
    /* temperature and humidity are acquired in sequence */
    res = hdc1080_set_mode(&gs_handle, HDC1080_MODE_SEQUENCE);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set mode failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* temperature and humidity are acquired in sequence mode */
    hdc1080_interface_debug_print("hdc1080: temperature and humidity are acquired in sequence mode.\n");
    
    /* get mode */
    res = hdc1080_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: get mode failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: check mode %s.\n", mode == HDC1080_MODE_SEQUENCE ? "ok" : "error");
    
    /* hdc1080_set_temperature_resolution/hdc1080_get_temperature_resolution test */
    hdc1080_interface_debug_print("hdc1080: hdc1080_set_temperature_resolution/hdc1080_get_temperature_resolution test.\n");
    
    /* 11 bit */
    res = hdc1080_set_temperature_resolution(&gs_handle, HDC1080_TEMPERATURE_RESOLUTION_11_BIT);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set temperature resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* 11 bit */
    hdc1080_interface_debug_print("hdc1080: set temperature resolution 11 bit.\n");
    
    /* get temperature resolution */
    res = hdc1080_get_temperature_resolution(&gs_handle, &t_resolution);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: get temperature resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: check temperature resolution %s.\n", t_resolution == HDC1080_TEMPERATURE_RESOLUTION_11_BIT ? "ok" : "error");
    
    /* 14 bit */
    res = hdc1080_set_temperature_resolution(&gs_handle, HDC1080_TEMPERATURE_RESOLUTION_14_BIT);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set temperature resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* 14 bit */
    hdc1080_interface_debug_print("hdc1080: set temperature resolution 14 bit.\n");
    
    /* get temperature resolution */
    res = hdc1080_get_temperature_resolution(&gs_handle, &t_resolution);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: get temperature resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: check temperature resolution %s.\n", t_resolution == HDC1080_TEMPERATURE_RESOLUTION_14_BIT ? "ok" : "error");
    
    /* hdc1080_set_humidity_resolution/hdc1080_get_humidity_resolution test */
    hdc1080_interface_debug_print("hdc1080: hdc1080_set_humidity_resolution/hdc1080_get_humidity_resolution test.\n");
    
    /* 8 bit */
    res = hdc1080_set_humidity_resolution(&gs_handle, HDC1080_HUMIDITY_RESOLUTION_8_BIT);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set humidity resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set humidity resolution 8 bit */
    hdc1080_interface_debug_print("hdc1080: set humidity resolution 8 bit.\n");
    
    /* get humidity resolution */
    res = hdc1080_get_humidity_resolution(&gs_handle, &h_resolution);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: get humidity resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: check humidity resolution %s.\n", h_resolution == HDC1080_HUMIDITY_RESOLUTION_8_BIT ? "ok" : "error");
    
    /* 11 bit */
    res = hdc1080_set_humidity_resolution(&gs_handle, HDC1080_HUMIDITY_RESOLUTION_11_BIT);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set humidity resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set humidity resolution 11 bit */
    hdc1080_interface_debug_print("hdc1080: set humidity resolution 11 bit.\n");
    
    /* get humidity resolution */
    res = hdc1080_get_humidity_resolution(&gs_handle, &h_resolution);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: get humidity resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: check humidity resolution %s.\n", h_resolution == HDC1080_HUMIDITY_RESOLUTION_11_BIT ? "ok" : "error");
    
    /* 14 bit */
    res = hdc1080_set_humidity_resolution(&gs_handle, HDC1080_HUMIDITY_RESOLUTION_14_BIT);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set humidity resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set humidity resolution 14 bit */
    hdc1080_interface_debug_print("hdc1080: set humidity resolution 14 bit.\n");
    
    /* get humidity resolution */
    res = hdc1080_get_humidity_resolution(&gs_handle, &h_resolution);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: get humidity resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: check humidity resolution %s.\n", h_resolution == HDC1080_HUMIDITY_RESOLUTION_14_BIT ? "ok" : "error");
    
    /* hdc1080_software_reset test */
    hdc1080_interface_debug_print("hdc1080: hdc1080_software_reset test.\n");
    
    /* software reset */
    res = hdc1080_software_reset(&gs_handle);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: software reset failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* finish register */
    hdc1080_interface_debug_print("hdc1080: finish register test.\n");
    (void)hdc1080_deinit(&gs_handle);
    
    return 0;
}
