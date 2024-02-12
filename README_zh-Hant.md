[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver HDC1080

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/hdc1080/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

HDC1080是一款具有集成溫度感測器的數位濕度感測器，其能够以超低功耗提供出色的測量精度。 HDC1080支持較寬的工作電源電壓範圍，並且相比競爭解決方案，該器件可為各類常見應用提供低成本和低功耗優勢。 濕度和溫度感測器均經過出廠校準。

LibDriver HDC1080是LibDriver推出的HDC1080全功能驅動，該驅動提供溫度、相對濕度讀取的功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver HDC1080的源文件。

/interface目錄包含了LibDriver HDC1080與平台無關的IIC總線模板。

/test目錄包含了LibDriver HDC1080驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver HDC1080編程範例。

/doc目錄包含了LibDriver HDC1080離線文檔。

/datasheet目錄包含了HDC1080數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，/interface目錄和/example目錄加入工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/hdc1080/index.html](https://www.libdriver.com/docs/hdc1080/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。
