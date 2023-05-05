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
 * @file      driver_hdc1080.c
 * @brief     driver hdc1080 source file
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

#include "driver_hdc1080.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Texas Instruments HDC1080"        /**< chip name */
#define MANUFACTURER_NAME         "Texas Instruments"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.7f                               /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                               /**< chip max supply voltage */
#define MAX_CURRENT               7.2f                               /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                             /**< chip min operating temperature */
#define TEMPERATURE_MAX           125.0f                             /**< chip max operating temperature */
#define DRIVER_VERSION            1000                               /**< driver version */

/**
 * @brief chip address definition
 */
#define HDC1080_ADDRESS             0x80        /**< iic device address */

/**
 * @brief chip register definition
 */
#define HDC1080_REG_TEMPERATURE        0x00        /**< temperature register */
#define HDC1080_REG_HUMIDITY           0x01        /**< humidity register */
#define HDC1080_REG_CONFIG             0x02        /**< configuration register */
#define HDC1080_REG_SERIAL_ID_0        0xFB        /**< serial id 0 register */
#define HDC1080_REG_SERIAL_ID_1        0xFC        /**< serial id 1 register */
#define HDC1080_REG_SERIAL_ID_2        0xFD        /**< serial id 2 register */
#define HDC1080_REG_MANUFACTURER_ID    0xFE        /**< manufacturer id register */
#define HDC1080_REG_DEVICE_ID          0xFF        /**< device id register */

/**
 * @brief      read data with wait
 * @param[in]  *handle points to an hdc1080 handle structure
 * @param[in]  reg is the read register address
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_hdc1080_iic_read_with_wait(hdc1080_handle_t *handle, uint8_t reg, uint16_t *data)
{
    uint8_t buf[2];
    
    if (handle->iic_read_with_wait(HDC1080_ADDRESS, reg, buf, 2) != 0)        /* read the register */
    {
        return 1;                                                             /* return error */
    }
    else
    {
        *data = (uint16_t)((uint16_t)buf[0] << 8 | buf[1]);                   /* get data */
        
        return 0;                                                             /* success return 0 */
    }
}

/**
 * @brief      read data
 * @param[in]  *handle points to an hdc1080 handle structure
 * @param[in]  reg is the read register address
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_hdc1080_iic_read(hdc1080_handle_t *handle, uint8_t reg, uint16_t *data)
{
    uint8_t buf[2];
    
    if (handle->iic_read(HDC1080_ADDRESS, reg, buf, 2) != 0)        /* read the register */
    {
        return 1;                                                   /* return error */
    }
    else
    {
        *data = (uint16_t)((uint16_t)buf[0] << 8 | buf[1]);         /* get data */
        
        return 0;                                                   /* success return 0 */
    }
}

/**
 * @brief     write data
 * @param[in] *handle points to an hdc1080 handle structure
 * @param[in] reg is the write register address
 * @param[in] data is the write data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_hdc1080_iic_write(hdc1080_handle_t *handle, uint8_t reg, uint16_t data)
{
    uint8_t buf[2];
    
    buf[0] = (data >> 8) & 0xFF;                                     /* msb */
    buf[1] = (data >> 0) & 0xFF;                                     /* lsb */
    if (handle->iic_write(HDC1080_ADDRESS, reg, buf, 2) != 0)        /* write the register */
    {
        return 1;                                                    /* return error */
    }
    else
    {
        return 0;                                                    /* success return 0 */
    }
}

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an hdc1080 handle structure
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
uint8_t hdc1080_init(hdc1080_handle_t *handle)
{
    uint8_t res;
    uint16_t data;
    uint16_t id;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->debug_print == NULL)                                           /* check debug_print */
    {
        return 3;                                                              /* return error */
    }
    if (handle->iic_init == NULL)                                              /* check iic_init */
    {
        handle->debug_print("hdc1080: iic_init is null.\n");                   /* iic_init is null */
        
        return 3;                                                              /* return error */
    }
    if (handle->iic_deinit == NULL)                                            /* check iic_deinit */
    {
        handle->debug_print("hdc1080: iic_deinit is null.\n");                 /* iic_deinit is null */
        
        return 3;                                                              /* return error */
    }
    if (handle->iic_read == NULL)                                              /* check iic_read */
    {
        handle->debug_print("hdc1080: iic_read is null.\n");                   /* iic_read is null */
        
        return 3;                                                              /* return error */
    }
    if (handle->iic_read_with_wait == NULL)                                    /* check iic_read_with_wait */
    {
        handle->debug_print("hdc1080: iic_read_with_wait is null.\n");         /* iic_read_with_wait is null */
        
        return 3;                                                              /* return error */
    }
    if (handle->iic_write == NULL)                                             /* check iic_write */
    {
        handle->debug_print("hdc1080: iic_write is null.\n");                  /* iic_write is null */
        
        return 3;                                                              /* return error */
    }
    if (handle->delay_ms == NULL)                                              /* check delay_ms */
    {
        handle->debug_print("hdc1080: delay_ms is null.\n");                   /* delay_ms is null */
        
        return 3;                                                              /* return error */
    }
    
    if (handle->iic_init() != 0)                                               /* iic init */
    {
        handle->debug_print("hdc1080: iic init failed.\n");                    /* iic init failed */
        
        return 1;                                                              /* return error */
    }
    res = a_hdc1080_iic_read(handle, HDC1080_REG_MANUFACTURER_ID, &id);        /* read manufacturer id */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("hdc1080: read manufacturer id failed.\n");        /* read manufacturer id failed */
        (void)handle->iic_deinit();                                            /* iic deinit */
        
        return 4;                                                              /* return error */
    }
    if (id != 0x5449)                                                          /* check id */
    {
        handle->debug_print("hdc1080: manufacturer id is invalid.\n");         /* read manufacturer id failed */
        (void)handle->iic_deinit();                                            /* iic deinit */
        
        return 5;                                                              /* return error */
    }
    res = a_hdc1080_iic_read(handle, HDC1080_REG_DEVICE_ID, &id);              /* read device id */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("hdc1080: read device id failed.\n");              /* read device id failed */
        (void)handle->iic_deinit();                                            /* iic deinit */
        
        return 4;                                                              /* return error */
    }
    if (id != 0x1050)                                                          /* check id */
    {
        handle->debug_print("hdc1080: device id is invalid.\n");               /* read device id failed */
        (void)handle->iic_deinit();                                            /* iic deinit */
        
        return 5;                                                              /* return error */
    }
    
    res = a_hdc1080_iic_read(handle, HDC1080_REG_CONFIG, &data);               /* read config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("hdc1080: read config failed.\n");                 /* read config failed */
        (void)handle->iic_deinit();                                            /* iic deinit */
        
        return 6;                                                              /* return error */
    }
    data &= ~(1 << 15);                                                        /* clear settings */
    data |= 1 << 15;                                                           /* software reset */
    res = a_hdc1080_iic_write(handle, HDC1080_REG_CONFIG, data);               /* write config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("hdc1080: write config failed.\n");                /* write config failed */
        (void)handle->iic_deinit();                                            /* iic deinit */
        
        return 6;                                                              /* return error */
    }
    handle->delay_ms(100);                                                     /* delay 100ms */
    handle->inited = 1;                                                        /* flag finish initialization */
    
    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     close the chip
 * @param[in] *handle points to an hdc1080 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hdc1080_deinit(hdc1080_handle_t *handle)
{
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    if (handle->iic_deinit() != 0)                                 /* iic deinit */
    {
        handle->debug_print("hdc1080: iic deinit failed.\n");      /* iic deinit failed */
        
        return 1;                                                  /* return error */
    }
    handle->inited = 0;                                            /* set closed flag */
    
    return 0;                                                      /* success return 0 */
}

/**
 * @brief      read the temperature and humidity data
 * @param[in]  *handle points to an hdc1080 handle structure
 * @param[out] *temperature_raw points to a raw temperature buffer
 * @param[out] *temperature_s points to a converted temperature buffer
 * @param[out] *humidity_raw points to a raw humidity buffer
 * @param[out] *humidity_s points to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature humidity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_read_temperature_humidity(hdc1080_handle_t *handle, uint16_t *temperature_raw, float *temperature_s,
                                          uint16_t *humidity_raw, float *humidity_s)
{
    uint8_t res;
    
    if (handle == NULL)                                                                /* check handle */
    {
        return 2;                                                                      /* return error */
    }
    if (handle->inited != 1)                                                           /* check handle initialization */
    {
        return 3;                                                                      /* return error */
    }
    
    res = a_hdc1080_iic_read_with_wait(handle, HDC1080_REG_TEMPERATURE, 
                                       temperature_raw);                               /* read temperature */
    if (res != 0)                                                                      /* check result */
    {
        handle->debug_print("hdc1080: read temperature failed.\n");                    /* read temperature failed */
        
        return 1;                                                                      /* return error */
    }
    *temperature_s = (float)(*temperature_raw) / 65536.0f * 165.0f - 40.0f;            /* convert temperature */
    res = a_hdc1080_iic_read_with_wait(handle, HDC1080_REG_HUMIDITY, humidity_raw);    /* read humidity */
    if (res != 0)                                                                      /* check result */
    {
        handle->debug_print("hdc1080: read humidity failed.\n");                       /* read humidity failed */
        
        return 1;                                                                      /* return error */
    }
    *humidity_s = (float)(*humidity_raw) / 65536.0f * 100.0f;                          /* get humidity */
    
    return 0;                                                                          /* success return 0 */
}

/**
 * @brief      read the temperature
 * @param[in]  *handle points to an hdc1080 handle structure
 * @param[out] *temperature_raw points to a raw temperature buffer
 * @param[out] *temperature_s points to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_read_temperature(hdc1080_handle_t *handle, uint16_t *temperature_raw, float *temperature_s)
{
    uint8_t res;
    
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    
    res = a_hdc1080_iic_read_with_wait(handle, HDC1080_REG_TEMPERATURE, temperature_raw);        /* read temperature */
    if (res != 0)                                                                                /* check result */
    {
        handle->debug_print("hdc1080: read temperature failed.\n");                              /* read temperature failed */
        
        return 1;                                                                                /* return error */
    }
    *temperature_s = (float)(*temperature_raw) / 65536.0f * 165.0f - 40.0f;                      /* convert temperature */
    
    return 0;                                                                                    /* success return 0 */
}

/**
 * @brief      read the humidity data
 * @param[in]  *handle points to an hdc1080 handle structure
 * @param[out] *humidity_raw points to a raw humidity buffer
 * @param[out] *humidity_s points to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read humidity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_read_humidity(hdc1080_handle_t *handle, uint16_t *humidity_raw, float *humidity_s)
{
    uint8_t res;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    res = a_hdc1080_iic_read_with_wait(handle, HDC1080_REG_HUMIDITY, humidity_raw);        /* read humidity */
    if (res != 0)                                                                          /* check result */
    {
        handle->debug_print("hdc1080: read humidity failed.\n");                           /* read humidity failed */
        
        return 1;                                                                          /* return error */
    }
    *humidity_s = (float)(*humidity_raw) / 65536.0f * 100.0f;                              /* get humidity */
    
    return 0;                                                                              /* success return 0 */
}

/**
 * @brief     software reset
 * @param[in] *handle points to an hdc1080 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 software reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hdc1080_software_reset(hdc1080_handle_t *handle)
{
    uint8_t res;
    uint16_t data;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_hdc1080_iic_read(handle, HDC1080_REG_CONFIG, &data);        /* read config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: read config failed.\n");          /* read config failed */
        
        return 1;                                                       /* return error */
    }
    data &= ~(1 << 15);                                                 /* clear settings */
    data |= 1 << 15;                                                    /* software reset */
    res = a_hdc1080_iic_write(handle, HDC1080_REG_CONFIG, data);        /* write config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: write config failed.\n");         /* write config failed */
        
        return 1;                                                       /* return error */
    }
    handle->delay_ms(100);                                              /* delay 100ms */
    
    return 0;                                                           /* success return 0 */
}

/**
 * @brief     enable or disable heater
 * @param[in] *handle points to an hdc1080 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set heater failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hdc1080_set_heater(hdc1080_handle_t *handle, hdc1080_bool_t enable)
{
    uint8_t res;
    uint16_t data;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_hdc1080_iic_read(handle, HDC1080_REG_CONFIG, &data);        /* read config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: read config failed.\n");          /* read config failed */
        
        return 1;                                                       /* return error */
    }
    data &= ~(1 << 13);                                                 /* clear settings */
    data |= enable << 13;                                               /* set bool */
    res = a_hdc1080_iic_write(handle, HDC1080_REG_CONFIG, data);        /* write config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: write config failed.\n");         /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

/**
 * @brief      get the heater status
 * @param[in]  *handle points to an hdc1080 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get heater failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_get_heater(hdc1080_handle_t *handle, hdc1080_bool_t *enable)
{
    uint8_t res;
    uint16_t data;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_hdc1080_iic_read(handle, HDC1080_REG_CONFIG, &data);        /* read config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: read config failed.\n");          /* read config failed */
        
        return 1;                                                       /* return error */
    }
    *enable = (hdc1080_bool_t)((data >> 13) & 0x1);                     /* get the bool */
    
    return 0;                                                           /* success return 0 */
}

/**
 * @brief     set the chip mode
 * @param[in] *handle points to an hdc1080 handle structure
 * @param[in] mode is the set mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hdc1080_set_mode(hdc1080_handle_t *handle, hdc1080_mode_t mode)
{
    uint8_t res;
    uint16_t data;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_hdc1080_iic_read(handle, HDC1080_REG_CONFIG, &data);        /* read config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: read config failed.\n");          /* read config failed */
        
        return 1;                                                       /* return error */
    }
    data &= ~(1 << 12);                                                 /* clear settings */
    data |= mode << 12;                                                 /* set mode */
    res = a_hdc1080_iic_write(handle, HDC1080_REG_CONFIG, data);        /* write config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: write config failed.\n");         /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

/**
 * @brief      get the chip mode
 * @param[in]  *handle points to an hdc1080 handle structure
 * @param[out] *mode points to a mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_get_mode(hdc1080_handle_t *handle, hdc1080_mode_t *mode)
{
    uint8_t res;
    uint16_t data;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_hdc1080_iic_read(handle, HDC1080_REG_CONFIG, &data);        /* read config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: read config failed.\n");          /* read config failed */
        
        return 1;                                                       /* return error */
    }
    *mode = (hdc1080_mode_t)((data >> 12) & 0x1);                       /* get the mode */
    
    return 0;                                                           /* success return 0 */
}

/**
 * @brief      get battery status
 * @param[in]  *handle points to an hdc1080 handle structure
 * @param[out] *status points to a battery status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get battery status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_get_battery_status(hdc1080_handle_t *handle, hdc1080_battery_status_t *status)
{
    uint8_t res;
    uint16_t data;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_hdc1080_iic_read(handle, HDC1080_REG_CONFIG, &data);        /* read config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: read config failed.\n");          /* read config failed */
        
        return 1;                                                       /* return error */
    }
    *status = (hdc1080_battery_status_t)((data >> 11) & 0x1);           /* get the status */
    
    return 0;                                                           /* success return 0 */
}

/**
 * @brief     set temperature resolution
 * @param[in] *handle points to an hdc1080 handle structure
 * @param[in] resolution is the temperature resolution
 * @return    status code
 *            - 0 success
 *            - 1 set temperature resolution failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hdc1080_set_temperature_resolution(hdc1080_handle_t *handle, hdc1080_temperature_resolution_t resolution)
{
    uint8_t res;
    uint16_t data;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_hdc1080_iic_read(handle, HDC1080_REG_CONFIG, &data);        /* read config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: read config failed.\n");          /* read config failed */
        
        return 1;                                                       /* return error */
    }
    data &= ~(1 << 10);                                                 /* clear settings */
    data |= resolution << 10;                                           /* set resolution */
    res = a_hdc1080_iic_write(handle, HDC1080_REG_CONFIG, data);        /* write config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: write config failed.\n");         /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

/**
 * @brief      get temperature resolution
 * @param[in]  *handle points to an hdc1080 handle structure
 * @param[out] *resolution points to a temperature resolution buffer
 * @return     status code
 *             - 0 success
 *             - 1 get temperature resolution failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_get_temperature_resolution(hdc1080_handle_t *handle, hdc1080_temperature_resolution_t *resolution)
{
    uint8_t res;
    uint16_t data;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_hdc1080_iic_read(handle, HDC1080_REG_CONFIG, &data);                 /* read config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: read config failed.\n");                   /* read config failed */
        
        return 1;                                                                /* return error */
    }
    *resolution = (hdc1080_temperature_resolution_t)((data >> 10) & 0x1);        /* get the resolution */
    
    return 0;                                                                    /* success return 0 */
}

/**
 * @brief     set humidity resolution
 * @param[in] *handle points to an hdc1080 handle structure
 * @param[in] resolution is the humidity resolution
 * @return    status code
 *            - 0 success
 *            - 1 set humidity resolution failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hdc1080_set_humidity_resolution(hdc1080_handle_t *handle, hdc1080_humidity_resolution_t resolution)
{
    uint8_t res;
    uint16_t data;
    
    if (handle == NULL)                                                 /* check handle */
    {
        return 2;                                                       /* return error */
    }
    if (handle->inited != 1)                                            /* check handle initialization */
    {
        return 3;                                                       /* return error */
    }
    
    res = a_hdc1080_iic_read(handle, HDC1080_REG_CONFIG, &data);        /* read config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: read config failed.\n");          /* read config failed */
        
        return 1;                                                       /* return error */
    }
    data &= ~(3 << 8);                                                  /* clear settings */
    data |= resolution << 8;                                            /* set resolution */
    res = a_hdc1080_iic_write(handle, HDC1080_REG_CONFIG, data);        /* write config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: write config failed.\n");         /* write config failed */
        
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

/**
 * @brief      get humidity resolution
 * @param[in]  *handle points to an hdc1080 handle structure
 * @param[out] *resolution points to a humidity resolution buffer
 * @return     status code
 *             - 0 success
 *             - 1 get humidity resolution failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_get_humidity_resolution(hdc1080_handle_t *handle, hdc1080_humidity_resolution_t *resolution)
{
    uint8_t res;
    uint16_t data;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_hdc1080_iic_read(handle, HDC1080_REG_CONFIG, &data);             /* read config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: read config failed.\n");               /* read config failed */
        
        return 1;                                                            /* return error */
    }
    *resolution = (hdc1080_humidity_resolution_t)((data >> 8) & 0x3);        /* get the resolution */
    
    return 0;                                                                /* success return 0 */
}

/**
 * @brief      get serial id
 * @param[in]  *handle points to an hdc1080 handle structure
 * @param[out] *id points to an id buffer
 * @return     status code
 *             - 0 success
 *             - 1 get serial id failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_get_serial_id(hdc1080_handle_t *handle, uint8_t id[6])
{
    uint8_t res;
    uint16_t data;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_hdc1080_iic_read(handle, HDC1080_REG_SERIAL_ID_0, &data);        /* read config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: read serial id 0  failed.\n");         /* read serial id 0 failed */
        
        return 1;                                                            /* return error */
    }
    id[0] = (data >> 8) & 0xFF;                                              /* id0 */
    id[1] = (data >> 0) & 0xFF;                                              /* id1 */
    res = a_hdc1080_iic_read(handle, HDC1080_REG_SERIAL_ID_1, &data);        /* read config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: read serial id 1  failed.\n");         /* read serial id 1 failed */
        
        return 1;                                                            /* return error */
    }
    id[2] = (data >> 8) & 0xFF;                                              /* id2 */
    id[3] = (data >> 0) & 0xFF;                                              /* id3 */
    res = a_hdc1080_iic_read(handle, HDC1080_REG_SERIAL_ID_2, &data);        /* read config */
    if (res != 0)
    {
        handle->debug_print("hdc1080: read serial id 2  failed.\n");         /* read serial id 2 failed */
        
        return 1;                                                            /* return error */
    }
    id[4] = (data >> 8) & 0xFF;                                              /* id4 */
    id[5] = (data >> 0) & 0xFF;                                              /* id5 */
    
    return 0;                                                                /* success return 0 */
}

/**
 * @brief     set chip register
 * @param[in] *handle points to an hdc1080 handle structure
 * @param[in] reg is the write register address
 * @param[in] data is the write data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hdc1080_set_reg(hdc1080_handle_t *handle, uint8_t reg, uint16_t data)
{
    if (handle == NULL)                                  /* check handle */
    {
        return 2;                                        /* return error */
    }
    if (handle->inited != 1)                             /* check handle initialization */
    {
        return 3;                                        /* return error */
    } 
    
    if (a_hdc1080_iic_write(handle, reg, data) != 0)     /* write data */
    {
        return 1;                                        /* return error */
    }
    else
    {
        return 0;                                        /* success return 0 */
    }
}

/**
 * @brief      get chip register
 * @param[in]  *handle points to an hdc1080 handle structure
 * @param[in]  reg is the read register address
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hdc1080_get_reg(hdc1080_handle_t *handle, uint8_t reg, uint16_t *data)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    } 
    
    if (a_hdc1080_iic_read(handle, reg, data) != 0)     /* read data */
    {
        return 1;                                       /* return error */
    }
    else
    {
        return 0;                                       /* success return 0 */
    }
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an hdc1080 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t hdc1080_info(hdc1080_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(hdc1080_info_t));                        /* initialize hdc1080 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
