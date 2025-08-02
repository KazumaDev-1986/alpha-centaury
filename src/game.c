#include <stddef.h>

#include "include/config.h"
#include "include/game.h"
#include "include/memory.h"
#include "include/raylib.h"
#include "include/screen.h"

// *************************************************
// Static functions && variables definition.
// *************************************************
static void _init_window(void);
static void _destroy_elements(Game *game);
static void _update_game(Game *const game);
static void _draw_game(const Game *const game);
static void _keyboard_events(Game *const game);
static void _load_screen(Game *const game, ScreenType type);
static void _unload_screen(Game *const game);
static ScreenType _update_screen(Screen *const screen);
static void _draw_screen(const Screen *const screen);
static void _change_next_screen(Game *const game, ScreenType type);

// *************************************************
// Public functions implementation.
// *************************************************
Result game_create(void) {
  Result result = memory_make_alloc(sizeof(Game));
  if (result.code == ERROR_CODE_OK) {
    _init_window();
    ((Game *)result.data)->currentScreen = NULL;
    ((Game *)result.data)->isRunning = true;
    _load_screen(result.data, SCREEN_TYPE_CANVAS);
    if (((Game *)result.data)->currentScreen == NULL) {
      void *tmp = result.data;
      memory_free_container(&tmp);
      result.data = NULL;
    }
  }

  return result;
}

void game_run(Game *const game) {
  while (game->isRunning) {
    _update_game(game);
    _draw_game(game);
  }
}

void game_destroy(Game *game) {
  _destroy_elements(game);
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

static void _destroy_elements(Game *game) {
  if (game != NULL) {
    _unload_screen(game);
    void *tmp = game;
    memory_free_container(&tmp);
  }
}

static void _update_game(Game *const game) {
  if (game != NULL) {
    ScreenType newScreen = _update_screen(game->currentScreen);
    _change_next_screen(game, newScreen);
    _keyboard_events(game);
  }
}

static void _draw_game(const Game *const game) {
  if (game != NULL) {
    BeginDrawing();
    _draw_screen(game->currentScreen);
    EndDrawing();
  }
}

static void _keyboard_events(Game *const game) {
  if (IsKeyPressed(KEY_ESCAPE)) {
    game->isRunning = false;
  }
}

static void _load_screen(Game *const game, ScreenType type) {
  if (game != NULL) {
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
}

static void _unload_screen(Game *const game) {
  if (game != NULL && game->currentScreen != NULL) {
    Screen *screen = game->currentScreen;

    switch (screen->type) {
    case SCREEN_TYPE_MENU:
      menu_screen_destroy(screen);
      break;
    case SCREEN_TYPE_CANVAS:
      canvas_screen_destroy(screen);
      break;
    default:
      break;
    }
    game->currentScreen = NULL;
  }
}

static ScreenType _update_screen(Screen *const screen) {
  ScreenType nextScreenType = SCREEN_TYPE_UNDEFINED;
  if (screen != NULL) {
    switch (screen->type) {
    case SCREEN_TYPE_MENU:
      menu_screen_update(screen);
      nextScreenType = menu_screen_next_screen_type();
      break;
    case SCREEN_TYPE_CANVAS:
      canvas_screen_update(screen);
      nextScreenType = canvas_screen_next_screen_type();
      break;
    default:
      break;
    }
  }

  return nextScreenType;
}

static void _draw_screen(const Screen *const screen) {
  if (screen != NULL) {
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

static void _change_next_screen(Game *const game, ScreenType type) {
  if (game != NULL && type != SCREEN_TYPE_UNDEFINED) {
    _unload_screen(game);
    _load_screen(game, type);
  }
}
