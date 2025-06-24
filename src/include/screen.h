#ifndef AC_SCREEN_H
#define AC_SCREEN_H

#include "memory.h"

typedef enum {
  SCREEN_TYPE_EMPTY = 0,
  SCREEN_TYPE_MENU,
  SCREEN_TYPE_CANVAS
} ScreenType;

typedef struct {
  ScreenType type;
  // TODO: Add objetcs.
} Screen;

#if defined(__cplusplus)
extern "C" {
#endif

ResultMemory screen_menu_create(void);
void screen_menu_update(Screen *const screen);
void screen_menu_draw(const Screen *const screen);
ScreenType screen_menu_next_screen(void);
void screen_menu_destroy(Screen **const ptr);

ResultMemory screen_canvas_create(void);
void screen_canvas_update(Screen *const screen);
void screen_canvas_draw(const Screen *const screen);
ScreenType screen_canvas_next_screen(void);
void screen_canvas_destroy(Screen **const ptr);

#if defined(__cplusplus)
}
#endif
#endif  // AC_SCREEN_H
