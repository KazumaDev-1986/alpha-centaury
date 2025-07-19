#include "include/game.h"
#include "include/config.h"
#include "include/memory.h"
#include "include/raylib.h"
#include "include/screen.h"

#include <stddef.h>

// *************************************************
// Static functions definition.
// *************************************************
#if defined(__cplusplus)
extern "C" {
#endif

static void _init_window(void);
static void _destroy_elements(Game **const ptr);

static void _load_screen(Game *game, ScreenType type);
static void _unload_screen(Game *game);
static void _update_screen(Game *game);
static void _draw_screen(Game *const game);

#if defined(__cplusplus)
}
#endif

// *************************************************
// Public functions implementation.
// *************************************************
AC Result game_create(void) {
  Result result = memory_make_alloc(sizeof(Game));
  if (result.code == ERROR_CODE_OK) {
    _init_window();
    ((Game *)result.data)->currentScreen = NULL;
    _load_screen(result.data, SCREEN_TYPE_MENU);
    if (((Game *)result.data)->currentScreen == NULL) {
      void *tmp = result.data;
      memory_free_container(&tmp);
      result.data = NULL;
    }
  }

  return result;
}

AC void game_run(Game *game) {
  while (!WindowShouldClose()) {
    _update_screen(game);
    BeginDrawing();
    ClearBackground(SKYBLUE);
    _draw_screen(game);
    EndDrawing();
  }
}

AC void game_destroy(Game **const ptr) {
  _destroy_elements(ptr);
  CloseWindow();
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
    _unload_screen(*ptr);
    void *tmp = *ptr;
    memory_free_container(&tmp);
  }
}

static void _load_screen(Game *game, ScreenType type) {
  Result result = {0};

  switch (type) {
  case SCREEN_TYPE_MENU:
    result = menu_screen_create();
    break;
  case SCREEN_TYPE_CANVAS:
    result = canvas_screen_create();
    break;
  default:
    break;
  }

  if (result.code == ERROR_CODE_OK) {
    game->currentScreen = result.data;
  }
}

static void _unload_screen(Game *game) {
  if (game->currentScreen != NULL) {
    Screen *screen = game->currentScreen;

    switch (screen->type) {
    case SCREEN_TYPE_MENU:
      menu_screen_destroy(&screen);
      break;
    case SCREEN_TYPE_CANVAS:
      canvas_screen_destroy(&screen);
      break;
    default:
      break;
    }
    game->currentScreen = NULL;
  }
}

static void _update_screen(Game *game) {
  if (game->currentScreen != NULL) {
    Screen *screen = game->currentScreen;
    ScreenType newScreenType = SCREEN_TYPE_EMPTY;

    switch (screen->type) {
    case SCREEN_TYPE_MENU:
      menu_screen_update(screen);
      newScreenType = menu_screen_next_screen_type();
      break;
    case SCREEN_TYPE_CANVAS:
      canvas_screen_update(screen);
      newScreenType = canvas_screen_next_screen_type();
      break;
    default:
      break;
    }

    if (newScreenType != SCREEN_TYPE_EMPTY) {
      _unload_screen(game);
      _load_screen(game, newScreenType);
    }
  }
}

static void _draw_screen(Game *const game) {
  if (game->currentScreen != NULL) {
    Screen *screen = game->currentScreen;

    switch (screen->type) {
    case SCREEN_TYPE_MENU:
      menu_screen_draw(screen);
      break;
    case SCREEN_TYPE_CANVAS:
      canvas_screen_draw(screen);
      break;
    default:
      break;
    }
  }
}
