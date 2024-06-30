#ifndef CONFIG_H
#define CONFIG_H

#define JOY_UP      4
#define JOY_DOWN    5
#define JOY_LEFT    6
#define JOY_RIGHT   7
#define JOY_FIRE    3
#define JOY_PADDLEA A0
#define JOY_PADDLEB A1

#define LED_UP     11
#define LED_DOWN   8
#define LED_LEFT   9
#define LED_RIGHT 10 
#define LED_FIRE  12

#define LED_DEMO_DELAY 100 // ms

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 34 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

//#define SHOW_BAR // show bar or line for paddle

#endif //  CONFIG_H