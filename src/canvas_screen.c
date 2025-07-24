
#include "include/config.h"
#include "include/memory.h"
#include "include/raylib.h"
#include "include/screen.h"

#include <stddef.h>

// *************************************************
// Static functions and variables definition.
// *************************************************
static ScreenType _nextScreenType = SCREEN_TYPE_EMPTY;

// *************************************************
// Public functions implementation.
// *************************************************
AC Result canvas_screen_create(void) {
  Result result = memory_make_alloc(sizeof(Screen));
  if (result.code == ERROR_CODE_OK) {
    _nextScreenType = SCREEN_TYPE_EMPTY;
    ((Screen *)result.data)->type = SCREEN_TYPE_CANVAS;
  }

  return result;
}

AC void canvas_screen_update(Screen *const screen) {
  if (IsKeyPressed(KEY_F1)) {
    _nextScreenType = SCREEN_TYPE_MENU;
  }
}

AC void canvas_screen_draw(const Screen *const screen) { ClearBackground(RED); }

AC void canvas_screen_destroy(Screen *screen) {
  void *tmp = screen;
  memory_free_container(&tmp);
}

AC ScreenType canvas_screen_next_screen_type(void) { return _nextScreenType; }
