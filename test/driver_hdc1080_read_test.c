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
 * @file      driver_hdc1080_read_test.c
 * @brief     driver hdc1080 read test source file
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

#include "driver_hdc1080_read_test.h"

static hdc1080_handle_t gs_handle;        /**< hdc1080 handle */

/**
 * @brief     read test
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 read failed
 * @note      none
 */
uint8_t hdc1080_read_test(uint32_t times)
{
    uint8_t res;
    uint32_t i;
    hdc1080_info_t info;
   
    /* link interface function */
    DRIVER_HDC1080_LINK_INIT(&gs_handle, hdc1080_handle_t); 
    DRIVER_HDC1080_LINK_IIC_INIT(&gs_handle, hdc1080_interface_iic_init);
    DRIVER_HDC1080_LINK_IIC_DEINIT(&gs_handle, hdc1080_interface_iic_deinit);
    DRIVER_HDC1080_LINK_IIC_READ(&gs_handle, hdc1080_interface_iic_read);
    DRIVER_HDC1080_LINK_IIC_READ_WITH_WAIT(&gs_handle, hdc1080_interface_iic_read_with_wait);
    DRIVER_HDC1080_LINK_IIC_WRITE(&gs_handle, hdc1080_interface_iic_write);
    DRIVER_HDC1080_LINK_DELAY_MS(&gs_handle, hdc1080_interface_delay_ms);
    DRIVER_HDC1080_LINK_DEBUG_PRINT(&gs_handle, hdc1080_interface_debug_print);

    /* get hdc1080 information */
    res = hdc1080_info(&info);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print hdc1080 information */
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
    
    /* start basic read test */
    hdc1080_interface_debug_print("hdc1080: start read test.\n");
    
    /* hdc1080 init */
    res = hdc1080_init(&gs_handle);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: init failed.\n");
       
        return 1;
    }
    
    /* enable heater */
    res = hdc1080_set_heater(&gs_handle, HDC1080_BOOL_TRUE);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set heater failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* temperature and humidity are acquired in sequence */
    res = hdc1080_set_mode(&gs_handle, HDC1080_MODE_SEQUENCE);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set mode failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* 11 bit */
    res = hdc1080_set_temperature_resolution(&gs_handle, HDC1080_TEMPERATURE_RESOLUTION_11_BIT);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set temperature resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: set temperature resolution 11 bit.\n");
    
    /* loop */
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        /* delay 1000ms */
        hdc1080_interface_delay_ms(1000);
        
        /* read temperature humidity */
        res = hdc1080_read_temperature_humidity(&gs_handle, &temperature_raw, &temperature_s,
                                                &humidity_raw, &humidity_s);
        if (res != 0)
        {
            hdc1080_interface_debug_print("hdc1080: read temperature humidity failed.\n");
            (void)hdc1080_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        hdc1080_interface_debug_print("hdc1080: temperature is %0.2fC, humidity is %0.2f%%.\n", temperature_s, humidity_s);
    }
    
    /* 14 bit */
    res = hdc1080_set_temperature_resolution(&gs_handle, HDC1080_TEMPERATURE_RESOLUTION_14_BIT);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set temperature resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: set temperature resolution 14 bit.\n");
    
    /* loop */
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        /* delay 1000ms */
        hdc1080_interface_delay_ms(1000);
        
        /* read temperature humidity */
        res = hdc1080_read_temperature_humidity(&gs_handle, &temperature_raw, &temperature_s,
                                                &humidity_raw, &humidity_s);
        if (res != 0)
        {
            hdc1080_interface_debug_print("hdc1080: read temperature humidity failed.\n");
            (void)hdc1080_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        hdc1080_interface_debug_print("hdc1080: temperature is %0.2fC, humidity is %0.2f%%.\n", temperature_s, humidity_s);
    }
    
    /* 8 bit */
    res = hdc1080_set_humidity_resolution(&gs_handle, HDC1080_HUMIDITY_RESOLUTION_8_BIT);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set humidity resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: set humidity resolution 8 bit.\n");
    
    /* loop */
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        /* delay 1000ms */
        hdc1080_interface_delay_ms(1000);
        
        /* read temperature humidity */
        res = hdc1080_read_temperature_humidity(&gs_handle, &temperature_raw, &temperature_s,
                                                &humidity_raw, &humidity_s);
        if (res != 0)
        {
            hdc1080_interface_debug_print("hdc1080: read temperature humidity failed.\n");
            (void)hdc1080_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        hdc1080_interface_debug_print("hdc1080: temperature is %0.2fC, humidity is %0.2f%%.\n", temperature_s, humidity_s);
    }
    
    /* 11 bit */
    res = hdc1080_set_humidity_resolution(&gs_handle, HDC1080_HUMIDITY_RESOLUTION_11_BIT);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set humidity resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: set humidity resolution 11 bit.\n");
    
    /* loop */
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        /* delay 1000ms */
        hdc1080_interface_delay_ms(1000);
        
        /* read temperature humidity */
        res = hdc1080_read_temperature_humidity(&gs_handle, &temperature_raw, &temperature_s,
                                                &humidity_raw, &humidity_s);
        if (res != 0)
        {
            hdc1080_interface_debug_print("hdc1080: read temperature humidity failed.\n");
            (void)hdc1080_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        hdc1080_interface_debug_print("hdc1080: temperature is %0.2fC, humidity is %0.2f%%.\n", temperature_s, humidity_s);
    }
    
    /* 14 bit */
    res = hdc1080_set_humidity_resolution(&gs_handle, HDC1080_HUMIDITY_RESOLUTION_14_BIT);
    if (res != 0)
    {
        hdc1080_interface_debug_print("hdc1080: set humidity resolution failed.\n");
        (void)hdc1080_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: set humidity resolution 14 bit.\n");
    
    /* loop */
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        /* delay 1000ms */
        hdc1080_interface_delay_ms(1000);
        
        /* read temperature humidity */
        res = hdc1080_read_temperature_humidity(&gs_handle, &temperature_raw, &temperature_s,
                                                &humidity_raw, &humidity_s);
        if (res != 0)
        {
            hdc1080_interface_debug_print("hdc1080: read temperature humidity failed.\n");
            (void)hdc1080_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        hdc1080_interface_debug_print("hdc1080: temperature is %0.2fC, humidity is %0.2f%%.\n", temperature_s, humidity_s);
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: hdc1080_read_temperature test.\n");
    
    /* loop */
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        
        /* delay 1000ms */
        hdc1080_interface_delay_ms(1000);
        
        /* read temperature humidity */
        res = hdc1080_read_temperature(&gs_handle, &temperature_raw, &temperature_s);
        if (res != 0)
        {
            hdc1080_interface_debug_print("hdc1080: read temperature failed.\n");
            (void)hdc1080_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        hdc1080_interface_debug_print("hdc1080: temperature is %0.2fC.\n", temperature_s);
    }
    
    /* output */
    hdc1080_interface_debug_print("hdc1080: hdc1080_read_humidity test.\n");
    
    /* loop */
    for (i = 0; i < times; i++)
    {
        uint16_t humidity_raw;
        float humidity_s;
        
        /* delay 1000ms */
        hdc1080_interface_delay_ms(1000);
        
        /* read humidity */
        res = hdc1080_read_humidity(&gs_handle, &humidity_raw, &humidity_s);
        if (res != 0)
        {
            hdc1080_interface_debug_print("hdc1080: read humidity failed.\n");
            (void)hdc1080_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        hdc1080_interface_debug_print("hdc1080: humidity is %0.2f%%.\n", humidity_s);
    }
    
    /* finish basic read test and exit */
    hdc1080_interface_debug_print("hdc1080: finish read test.\n");
    (void)hdc1080_deinit(&gs_handle);
    
    return 0;
}
