#include <stddef.h>

#include "../include/memory.h"
#include "../include/raylib.h"
#include "../include/screen.h"

// *************************************************
// Static functions and variables definition.
// *************************************************
static ScreenType _nextScreenType = SCREEN_TYPE_UNDEFINED;

#if defined(__cplusplus)
extern "C" {
#endif

AC static void _reset_variables(void);

#if defined(__cplusplus)
}
#endif

// *************************************************
// Public functions implementation.
// *************************************************
Result menu_screen_create(void) {
  Result result = memory_make_alloc(sizeof(Screen));
  if (result.code == ERROR_CODE_OK) {
    _reset_variables();
    ((Screen *)result.data)->type = SCREEN_TYPE_MENU;
    ((Screen *)result.data)->content = NULL;
  }

  return result;
}

void menu_screen_update(Screen *const screen) {
  if (IsKeyPressed(KEY_F2)) {
    _nextScreenType = SCREEN_TYPE_CANVAS;
  }
}

void menu_screen_draw(const Screen *const screen) { ClearBackground(SKYBLUE); }

void menu_screen_destroy(Screen **const ptr) {
  void *tmp = *ptr;
  memory_free_container(&tmp);
}

ScreenType menu_screen_next_screen_type(void) { return _nextScreenType; }

// *************************************************
// Static functions definition.
// *************************************************
static void _reset_variables(void) {
  _nextScreenType = SCREEN_TYPE_UNDEFINED;
}
