#ifndef __LCD_AIP31068_I2C_WCHAR_H__
#define __LCD_AIP31068_I2C_WCHAR_H__

#include <Arduino.h>
#include <Wire.h>
#include <inttypes.h>
#include <LiquidCrystal_AIP31068_I2C.h>
#include <Print.h>

#define BYTE 0

struct CharMap {
  wchar_t a;
  char b;         // equivalent ASCII char  (or 0 if no such char)
  uint8_t img[8]; // 5x8 binary image
};

extern const CharMap char_mapping[];   // should be defined as PROGMEM in charmap include in main sketch
extern const size_t char_mapping_size; // should be defined as PROGMEM in charmap include in main sketch

class LCD_AIP31068_I2C_WCHAR : public LiquidCrystal_AIP31068_I2C
{
public:
	LCD_AIP31068_I2C_WCHAR(uint8_t lcd_addr,uint8_t lcd_cols,uint8_t lcd_rows);

  void clear();
  void setCursor(uint8_t, uint8_t); 
  uint8_t getCursorCol(); 
  uint8_t getCursorRow(); 

  void print(const wchar_t[]);
  void print(const char[]);
  void print(int, int = DEC);
  void print(unsigned int, int = DEC);
  void print(long, int = DEC);
  void print(unsigned long, int = DEC);
  void print(const String &);
  void print(char, int = BYTE);
  void print(unsigned char, int = BYTE);
  void print(double, int = 2); 

private:
  uint8_t cursor_col;
  uint8_t cursor_row;

  void printwc(const wchar_t);
  uint8_t mbtowc(wchar_t *, char *, uint8_t);

  wchar_t stored_chars[8];
  uint8_t store_index;

  void print_and_store(wchar_t a, uint8_t * img);
};

#endif