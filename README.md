# About LCD_AIP31068_I2C_WCHAR
This is Arduino library for multilingual character printing on LCD modules with AIP31068 chip via I2C

# Credits
- The library is based and depends on [LiquidCrystal_AIP31068](https://github.com/red-scorp/LiquidCrystal_AIP31068)
- Russian character support copied from [LCD_1602_RUS](https://github.com/ssilver2007/LCD_1602_RUS)

# How to use the library
## Basic usage
Currently, only russian character support is included into the library

- Connect your LCD Module to Arduino Board via I2C
- Add library to Arduino IDE via library manager or copy library to your sketch / workspace library folder
- Add library includes to your sketch

The sketch should look like
```
#include <LCD_AIP31068_I2C_WCHAR.h>
#include <LCD_CharMap_RUS.h>

#define LCD_ADDRESS 0x7c>>1

LCD_AIP31068_I2C_WCHAR lcd(LCD_ADDRESS,16,2);

void setup() {

    lcd.init();
    
    lcd.setCursor(0,0);
    lcd.print("LCD1602 AIP31068");
    lcd.setCursor(2,1);
    lcd.print("русские буквы");
}

void loop() {
    delay(100);
}
```

## Adding support for other languages

You can define character mappings for other languages. See **LCD_CharMap_RUS.h** for an example.
It is important to include your new mapping file in main sketch **.ino** file, so Arduino IDE build system can correctly parse PROGMEM macros.
