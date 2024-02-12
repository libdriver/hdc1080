[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver HDC1080
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/hdc1080/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der HDC1080 ist ein digitaler Feuchtigkeitssensor mit integriertem Temperatursensor, der eine hervorragende Messgenauigkeit bei sehr geringem Stromverbrauch bietet. Der HDC1080 arbeitet über einen großen Versorgungsbereich und ist eine kostengünstige, stromsparende Alternative zu Wettbewerbslösungen in einer Vielzahl gängiger Anwendungen. Die Feuchtigkeits- und Temperatursensoren sind werkseitig kalibriert.

LibDriver HDC1080 ist der Treiber mit vollem Funktionsumfang von HDC1080, der von LibDriver gestartet wurde. Er bietet die Funktion zum Lesen von Temperatur und relativer Luftfeuchtigkeit. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver HDC1080-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver HDC1080 IIC.

/test enthält den Testcode des LibDriver HDC1080-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver HDC1080-Beispielcode.

/doc enthält das LibDriver HDC1080-Offlinedokument.

/Datenblatt enthält HDC1080-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie /src, /interface und /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis/example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/hdc1080/index.html](https://www.libdriver.com/docs/hdc1080/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.