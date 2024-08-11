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
