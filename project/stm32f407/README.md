### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. HDC1080

#### 3.1 Command Instruction

1. Show hdc1080 chip and driver information.

   ```shell
   hdc1080 (-i | --information)
   ```

2. Show hdc1080 help.

   ```shell
   hdc1080 (-h | --help)
   ```

3. Show hdc1080 pin connections of the current board.

   ```shell
   hdc1080 (-p | --port)
   ```

4. Run hdc1080 register test.

    ```shell
    hdc1080 (-t reg | --test=reg)
    ```

5. Run hdc1080 read test, num means test times.

    ```shell
    hdc1080 (-t read | --test=read) [--times=<num>]
    ```

6. Run hdc1080 read function, num means test times.

   ```shell
   hdc1080 (-e read | --example=read) [--times=<num>]
   ```

#### 3.2 Command Example

```shell
hdc1080 -i

hdc1080: chip is Texas Instruments HDC1080.
hdc1080: manufacturer is Texas Instruments.
hdc1080: interface is IIC.
hdc1080: driver version is 1.0.
hdc1080: min supply voltage is 2.7V.
hdc1080: max supply voltage is 5.5V.
hdc1080: max current is 7.20mA.
hdc1080: max temperature is 125.0C.
hdc1080: min temperature is -40.0C.
```

```shell
hdc1080 -p

hdc1080: SCL connected to GPIOB PIN8.
hdc1080: SDA connected to GPIOB PIN9.
```

```shell
hdc1080 -t reg

hdc1080: chip is Texas Instruments HDC1080.
hdc1080: manufacturer is Texas Instruments.
hdc1080: interface is IIC.
hdc1080: driver version is 1.0.
hdc1080: min supply voltage is 2.7V.
hdc1080: max supply voltage is 5.5V.
hdc1080: max current is 7.20mA.
hdc1080: max temperature is 125.0C.
hdc1080: min temperature is -40.0C.
hdc1080: start register test.
hdc1080: hdc1080_get_serial_id test.
hdc1080: serial id is 0x01 0xFB 0x54 0x8F 0x02 0x00.
hdc1080: hdc1080_get_battery_status test.
hdc1080: battery status is over 2.8V.
hdc1080: hdc1080_set_heater/hdc1080_get_heater test.
hdc1080: disable heater.
hdc1080: check heater ok.
hdc1080: enable heater.
hdc1080: check heater ok.
hdc1080: hdc1080_set_mode/hdc1080_get_mode test.
hdc1080: temperature or humidity is acquired mode.
hdc1080: check mode ok.
hdc1080: temperature and humidity are acquired in sequence mode.
hdc1080: check mode ok.
hdc1080: hdc1080_set_temperature_resolution/hdc1080_get_temperature_resolution test.
hdc1080: set temperature resolution 11 bit.
hdc1080: check temperature resolution ok.
hdc1080: set temperature resolution 14 bit.
hdc1080: check temperature resolution ok.
hdc1080: hdc1080_set_humidity_resolution/hdc1080_get_humidity_resolution test.
hdc1080: set humidity resolution 8 bit.
hdc1080: check humidity resolution ok.
hdc1080: set humidity resolution 11 bit.
hdc1080: check humidity resolution ok.
hdc1080: set humidity resolution 14 bit.
hdc1080: check humidity resolution ok.
hdc1080: hdc1080_software_reset test.
hdc1080: finish register test.
```

```shell
hdc1080 -t read --times=3

hdc1080: chip is Texas Instruments HDC1080.
hdc1080: manufacturer is Texas Instruments.
hdc1080: interface is IIC.
hdc1080: driver version is 1.0.
hdc1080: min supply voltage is 2.7V.
hdc1080: max supply voltage is 5.5V.
hdc1080: max current is 7.20mA.
hdc1080: max temperature is 125.0C.
hdc1080: min temperature is -40.0C.
hdc1080: start read test.
hdc1080: set temperature resolution 11 bit.
hdc1080: temperature is 28.58C, humidity is 55.05%.
hdc1080: temperature is 28.70C, humidity is 55.12%.
hdc1080: temperature is 28.72C, humidity is 55.02%.
hdc1080: set temperature resolution 14 bit.
hdc1080: temperature is 28.73C, humidity is 54.93%.
hdc1080: temperature is 28.73C, humidity is 54.93%.
hdc1080: temperature is 28.74C, humidity is 54.93%.
hdc1080: set humidity resolution 8 bit.
hdc1080: temperature is 28.74C, humidity is 55.62%.
hdc1080: temperature is 28.76C, humidity is 55.22%.
hdc1080: temperature is 28.74C, humidity is 54.23%.
hdc1080: set humidity resolution 11 bit.
hdc1080: temperature is 28.76C, humidity is 54.82%.
hdc1080: temperature is 28.76C, humidity is 54.82%.
hdc1080: temperature is 28.76C, humidity is 54.63%.
hdc1080: set humidity resolution 14 bit.
hdc1080: temperature is 28.77C, humidity is 54.53%.
hdc1080: temperature is 28.77C, humidity is 54.43%.
hdc1080: temperature is 28.77C, humidity is 54.33%.
hdc1080: hdc1080_read_temperature test.
hdc1080: temperature is 28.77C.
hdc1080: temperature is 28.76C.
hdc1080: temperature is 28.80C.
hdc1080: hdc1080_read_humidity test.
hdc1080: humidity is 54.43%.
hdc1080: humidity is 54.33%.
hdc1080: humidity is 54.23%.
hdc1080: finish read test.
```

```shell
hdc1080 -e read --times=3

hdc1080: 1/3.
hdc1080: temperature is 28.67C.
hdc1080: humidity is 55.64%.
hdc1080: 2/3.
hdc1080: temperature is 28.73C.
hdc1080: humidity is 55.22%.
hdc1080: 3/3.
hdc1080: temperature is 28.76C.
hdc1080: humidity is 55.12%.
```

```shell
hdc1080 -h

Usage:
  hdc1080 (-i | --information)
  hdc1080 (-h | --help)
  hdc1080 (-p | --port)
  hdc1080 (-t reg | --test=reg)
  hdc1080 (-t read | --test=read) [--times=<num>]
  hdc1080 (-e read | --example=read) [--times=<num>]

Options:
  -e <read>, --example=<read>    Run the driver example.
  -h, --help                     Show the help.
  -i, --information              Show the chip information.
  -p, --port                     Display the pin connections of the current board.
  -t <reg | read>, --test=<reg | read>
                                 Run the driver test.
      --times=<num>              Set the running times.([default: 3])
```

