#ifndef AC_SCREEN_H
#define AC_SCREEN_H

#include "config.h"
#include "memory.h"

typedef enum {
  SCREEN_TYPE_UNDEFINED = 0,
  SCREEN_TYPE_MENU,
  SCREEN_TYPE_CANVAS,
} ScreenType;

typedef struct {
  ScreenType type;
} Screen;

#if defined(__cplusplus)
extern "C" {
#endif

Result menu_screen_create(void);
void menu_screen_update(Screen *const screen);
void menu_screen_draw(const Screen *const screen);
void menu_screen_destroy(Screen **const ptr);
ScreenType menu_screen_next_screen_type(void);

Result canvas_screen_create(void);
void canvas_screen_update(Screen *const screen);
void canvas_screen_draw(const Screen *const screen);
void canvas_screen_destroy(Screen **const ptr);
ScreenType canvas_screen_next_screen_type(void);

#if defined(__cplusplus)
}
#endif

#endif  // AC_SCREEN_H
