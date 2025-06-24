#include <stddef.h>

#include "include/config.h"
#include "include/game.h"
#include "include/memory.h"
#include "include/raylib.h"
#include "include/screen.h"

// *************************************************
// Static functions definition.
// *************************************************
#if defined(__cplusplus)
extern "C" {
#endif

static void _init_window(void);
static void _destroy_elements(Game **const ptr);

static void _screen_create(Game *const game, ScreenType type);
static void _screen_destroy(Game *const game);
static void _screen_update(Game *const game);
static void _screen_draw(const Game *const game);

#if defined(__cplusplus)
}
#endif

// *************************************************
// Public functions implementation.
// *************************************************
AC ResultMemory game_create(void) {
  ResultMemory result = memory_make_alloc(sizeof(Game));
  if (result.code == ERROR_CODE_OK) {
    _init_window();
    _screen_create(result.data, SCREEN_TYPE_MENU);
  }

  return result;
}

AC void game_run(Game *const game) {
  while (!WindowShouldClose()) {
    _screen_update(game);
    BeginDrawing();
    _screen_draw(game);
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
static void _init_window(void) {
#if defined(AC_DEBUG)
  SetTraceLogLevel(LOG_DEBUG);
#endif
  InitWindow(AC_SCREEN_WIDTH, AC_SCREEN_HEIGHT, AC_SCREEN_TITLE);
  SetTargetFPS(AC_SCREEN_FPS);
}

static void _destroy_elements(Game **const ptr) {
  if (ptr && *ptr) {
    _screen_destroy(*ptr);
    MemFree(*ptr);
    *ptr = NULL;
  }
}

static void _screen_create(Game *const game, ScreenType type) {
  ResultMemory (*fn)(void) = NULL;

  switch (type) {
    case SCREEN_TYPE_MENU:
      fn = screen_menu_create;
      break;
    case SCREEN_TYPE_CANVAS:
      fn = screen_canvas_create;
      break;
    default:
      break;
  }

  if (fn != NULL) {
    ResultMemory result = fn();
    if (result.code == ERROR_CODE_OK) {
      game->screen = result.data;
    }
  }
}

static void _screen_destroy(Game *const game) {
  ScreenType type = game->screen->type;
  void (*fn)(Screen **const) = NULL;

  switch (type) {
    case SCREEN_TYPE_MENU:
      fn = screen_menu_destroy;
      break;
    case SCREEN_TYPE_CANVAS:
      fn = screen_canvas_destroy;
      break;
    default:
      break;
  }

  if (fn != NULL) {
    fn(&game->screen);
    game->screen = NULL;
  }
}

static void _screen_update(Game *const game) {
  ScreenType type = game->screen->type;
  switch (type) {
    case SCREEN_TYPE_MENU:
      screen_menu_update(game->screen);
      break;
    case SCREEN_TYPE_CANVAS:
      screen_canvas_update(game->screen);
      break;
    default:
      break;
  }
}

static void _screen_draw(const Game *const game) {
  ScreenType type = game->screen->type;
  switch (type) {
    case SCREEN_TYPE_MENU:
      screen_menu_draw(game->screen);
      break;
    case SCREEN_TYPE_CANVAS:
      screen_canvas_draw(game->screen);
      break;
    default:
      break;
  }
}
