#include <Arduino.h>
#include "LCD_AIP31068_I2C_WCHAR.h"

void LCD_AIP31068_I2C_WCHAR::clear() {
  LiquidCrystal_AIP31068_I2C::clear();
  for (int i=0; i<8; i++) {
    stored_chars[i] = 0;
  }
}

void LCD_AIP31068_I2C_WCHAR::printwc(const wchar_t a) {
  int sz = char_mapping_size / sizeof(CharMap);

  for (int i=0; i<sz; i++) {
    CharMap cm;
    memcpy_P( &cm, &char_mapping[i], sizeof(CharMap));

    if (cm.a == a) { // custom character

      char b = cm.b;
      if (b == 0) { // character without equivalent
          print_and_store(a, cm.img);      
      }
      else {
        LiquidCrystal_AIP31068_I2C::print(b); // print ascii equvalent
      }
      return;
    }
  }  
  
  LiquidCrystal_AIP31068_I2C::print((char)a); // print not customized char
}

void LCD_AIP31068_I2C_WCHAR::print_and_store(wchar_t a, uint8_t * img) {
  // try to find in memory
  for (int i=0; i<8; i++) {
    if (stored_chars[i] == a) {
      write(i);
      return;
    }
  }

  //not found ... create char
  uint8_t x, y;
  x = getCursorCol();
  y = getCursorRow();        
  createChar(store_index, img);
  setCursor(x, y);
  write(store_index);

  stored_chars[store_index] = a;
  store_index++;

  if (store_index == 8) // next time start rewriting CGRAM from index 0
    store_index = 0;
}

LCD_AIP31068_I2C_WCHAR::LCD_AIP31068_I2C_WCHAR(uint8_t lcd_addr,uint8_t lcd_cols,uint8_t lcd_rows) : LiquidCrystal_AIP31068_I2C(lcd_addr, lcd_cols, lcd_rows){
  cursor_col = 0;
  cursor_row = 0;

  store_index = 0;
  for (int i=0; i<8; i++) {
    stored_chars[i] = 0;
  }
}

void LCD_AIP31068_I2C_WCHAR::setCursor(uint8_t col, uint8_t row)
{
  cursor_col = col;
  cursor_row = row;
  LiquidCrystal_AIP31068_I2C::setCursor(cursor_col, cursor_row);
}

uint8_t LCD_AIP31068_I2C_WCHAR::getCursorCol()
{
  return cursor_col;
}

uint8_t LCD_AIP31068_I2C_WCHAR::getCursorRow()
{
  return cursor_row;
}

void LCD_AIP31068_I2C_WCHAR::print(const char *c_str) {
  wchar_t _str;
  int current_char = 0;
  int size = strlen(c_str);

  while (current_char < size)
  {
    current_char += mbtowc(&_str, (char *)c_str + current_char, 2);
    printwc(_str);
    cursor_col++;
  }
}

void LCD_AIP31068_I2C_WCHAR::print(int val, int base) {
  cursor_col += LiquidCrystal_AIP31068_I2C::print(val, base);
}

void LCD_AIP31068_I2C_WCHAR::print(unsigned int val, int base) {
  cursor_col += LiquidCrystal_AIP31068_I2C::print(val, base);
}

void LCD_AIP31068_I2C_WCHAR::print(long val, int base) {
  cursor_col += LiquidCrystal_AIP31068_I2C::print(val, base);
}
void LCD_AIP31068_I2C_WCHAR::print(unsigned long val, int base) {
  cursor_col += LiquidCrystal_AIP31068_I2C::print(val, base);
}

void LCD_AIP31068_I2C_WCHAR::print(char val, int base) {
  cursor_col += LiquidCrystal_AIP31068_I2C::print(val, base);
}

void LCD_AIP31068_I2C_WCHAR::print(unsigned char val, int base) {
  cursor_col += LiquidCrystal_AIP31068_I2C::print(val, base);
}

void LCD_AIP31068_I2C_WCHAR::print(const String &str) {
  wchar_t _str;
  const char *c_str = str.c_str();
  int current_char = 0;
  int size = str.length();

  while (current_char < size)
  {
    current_char += mbtowc(&_str, (char*)c_str + current_char, 2);
    printwc(_str);
    cursor_col++;
  }
}

void LCD_AIP31068_I2C_WCHAR::print(double val, int base) {
  cursor_col += LiquidCrystal_AIP31068_I2C::print(val, base);
}

void LCD_AIP31068_I2C_WCHAR::print(const wchar_t *_str) {
  int current_char  = 0;
  int size = 0;

  while (_str[size] != 0)
  {
    size++;
  }

  while (current_char < size)
  {
    printwc(_str[current_char]);
    current_char++;
    cursor_col++;
  }

}

uint8_t LCD_AIP31068_I2C_WCHAR::mbtowc(wchar_t *_chr, char *_str, uint8_t mb_num) {
  if (mb_num != 2) return 0;
  if ((_str[0] & 0xC0) == 0xC0 && (_str[1] & 0x80) == 0x80) {
    *_chr = ((_str[0] & 0x1F) << 6) + (_str[1] & 0x3F);
    return 2;
  }
  else {
    *_chr = _str[0];
    return 1;
  }
}


