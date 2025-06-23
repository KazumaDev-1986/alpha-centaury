#include "include/game.h"
#include "include/config.h"
#include "include/memory.h"
#include "include/raylib.h"

#include <stddef.h>

// *************************************************
// Static functions definition.
// *************************************************
#if defined(__cplusplus)
extern "C" {
#endif

static void _init_window(void);
static void _destroy_elements(Game **const ptr);

#if defined(__cplusplus)
}
#endif

// *************************************************
// Public functions implementation.
// *************************************************
AC Result game_create(void) {
  Result result = memory_make_alloc(sizeof(Game));
  if (result.code == ERR_OK) {
    _init_window();
  }

  return result;
}

AC void game_run(Game *const game) {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(SKYBLUE);
    // TODO
    EndDrawing();
  }
}

AC void game_destroy(Game **const ptr) {
  CloseWindow();
  _destroy_elements(ptr);
}

// *************************************************
// Static functions implementation.
// *************************************************
void _init_window(void) {
#if defined(AC_DEBUG)
  SetTraceLogLevel(LOG_DEBUG);
#endif
  InitWindow(AC_SCREEN_WIDTH, AC_SCREEN_HEIGHT, AC_SCREEN_TITLE);
  SetTargetFPS(AC_SCREEN_FPS);
}

void _destroy_elements(Game **const ptr) {
  if (ptr && *ptr) {
    MemFree(*ptr);
    *ptr = NULL;
  }
}
