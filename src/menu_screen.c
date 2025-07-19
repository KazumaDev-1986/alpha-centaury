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
Result menu_screen_create(void) {
  Result result = memory_make_alloc(sizeof(Screen));
  if (result.code == ERROR_CODE_OK) {
    ((Screen *)result.data)->type = SCREEN_TYPE_MENU;
  }

  return result;
}

void menu_screen_update(Screen *const screen) {
  // TODO
}

void menu_screen_draw(const Screen *const screen) { ClearBackground(GREEN); }

void menu_screen_destroy(Screen **const ptr) {
  void *tmp = *ptr;
  memory_free_container(&tmp);
}

ScreenType menu_screen_next_screen_type(void) { return _nextScreenType; }
