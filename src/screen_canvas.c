#include <stddef.h>

#include "include/memory.h"
#include "include/raylib.h"
#include "include/screen.h"

// *************************************************
// Static functions & variables definition.
// *************************************************
static ScreenType _nextScreenType = SCREEN_TYPE_EMPTY;

// *************************************************
// Public functions implementation.
// *************************************************
ResultMemory screen_canvas_create(void) {
  ResultMemory result = memory_make_alloc(sizeof(Screen));
  if (result.code == ERROR_CODE_OK) {
    ((Screen *)result.data)->type = SCREEN_TYPE_CANVAS;
  }

  return result;
}

void screen_canvas_update(Screen *const screen) {
  // TODO
}

void screen_canvas_draw(const Screen *const screen) {
  ClearBackground(RED);
  // TODO
}

ScreenType screen_canvas_next_screen(void) { return _nextScreenType; }

void screen_canvas_destroy(Screen **const ptr) {
  if (ptr && *ptr) {
    MemFree(*ptr);
    *ptr = NULL;
  }
}
