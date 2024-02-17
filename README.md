[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver HDC1080

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/hdc1080/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The HDC1080 is a digital humidity sensor with integrated temperature sensor that provides excellent measurement accuracy at very low power. The HDC1080 operates over a wide supply range, and is a low cost, low power alternative to competitive solutions in a wide range of common applications. The humidity and temperature sensors are factory calibrated.

LibDriver HDC1080 is the full function driver of HDC1080 launched by LibDriver.It provides the function of reading temperature and relative humidity. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver HDC1080 source files.

/interface includes LibDriver HDC1080 IIC platform independent template.

/test includes LibDriver HDC1080 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver HDC1080 sample code.

/doc includes LibDriver HDC1080 offline document.

/datasheet includes HDC1080 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_hdc1080_basic.h"

uint8_t res;
uint32_t i;
float temperature;
float humidity;

/* basic init */
res = hdc1080_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < times; i++)
{
    /* delay 2000ms */
    hdc1080_interface_delay_ms(2000);

    /* read data */
    res = hdc1080_basic_read((float *)&temperature, (float *)&humidity);
    if (res != 0)
    {
        (void)hdc1080_basic_deinit();

        return 1;
    }

    /* output */
    hdc1080_interface_debug_print("hdc1080: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
    hdc1080_interface_debug_print("hdc1080: temperature is %0.2fC.\n", temperature);
    hdc1080_interface_debug_print("hdc1080: humidity is %0.2f%%.\n", humidity); 
    
    ...
}

...
    
/* deinit */
(void)hdc1080_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/hdc1080/index.html](https://www.libdriver.com/docs/hdc1080/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please sent an e-mail to lishifenging@outlook.com.