#include <stddef.h>

#include "../include/memory.h"
#include "../include/raylib.h"
#include "../include/screen.h"

#if defined(AC_DEBUG)
#include "../include/trace_utils.h"
#endif

// *************************************************
// Static functions and variables definition.
// *************************************************
static ScreenType _nextScreenType = SCREEN_TYPE_UNDEFINED;
static Color _backgroundColor = {0};

static void _reset_variables(void);

// *************************************************
// Public functions implementation.
// *************************************************
Result menu_screen_create(void) {
  Result result = memory_make_alloc(sizeof(Screen));
  if (result.code == ERROR_CODE_OK) {
    _reset_variables();
    ((Screen *)result.data)->type = SCREEN_TYPE_MENU;
    ((Screen *)result.data)->content = NULL;
#if defined(AC_DEBUG)
    trace_created("SCREEN", "Menu");
#endif
  }

  return result;
}

void menu_screen_update(Screen *const screen) {
  if (IsKeyPressed(KEY_F2)) {
    _nextScreenType = SCREEN_TYPE_CANVAS;
  }
}

void menu_screen_draw(const Screen *const screen) {
  ClearBackground(_backgroundColor);
}

void menu_screen_destroy(Screen *screen) {
  if (screen) {
    void *tmp = screen;
    memory_free_container(&tmp);
#if defined(AC_DEBUG)
    trace_destroyed("SCREEN", "Menu");
#endif
  }
}

ScreenType menu_screen_next_screen_type(void) { return _nextScreenType; }

// *************************************************
// Static functions definition.
// *************************************************
static void _reset_variables(void) {
  _nextScreenType = SCREEN_TYPE_UNDEFINED;
  _backgroundColor = GetColor(AC_COLOR_7);
}
