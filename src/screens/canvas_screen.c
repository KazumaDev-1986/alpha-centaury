
#include <stddef.h>

#include "../include/config.h"
#include "../include/level.h"
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

#if defined(__cplusplus)
extern "C" {
#endif

static void _keyboard_events(void);
static void _load_level(Screen *const screen, LevelType type);
static void _unload_level(Screen *const screen);
static LevelType _update_level(Level *const level);
static void _draw_level(const Level *const level);
static void _change_next_level(Screen *const screen, LevelType type);

#if defined(__cplusplus)
}
#endif

// *************************************************
// Public functions implementation.
// *************************************************
Result canvas_screen_create(void) {
  Result result = memory_make_alloc(sizeof(Screen));
  if (result.code == ERROR_CODE_OK) {
    _nextScreenType = SCREEN_TYPE_UNDEFINED;
    ((Screen *)result.data)->type = SCREEN_TYPE_CANVAS;
    ((Screen *)result.data)->content = NULL;
    _load_level(result.data, LEVEL_TYPE_ONE);
#if defined(AC_DEBUG)
    trace_created("SCREEN", "Canvas");
#endif
  }

  return result;
}

void canvas_screen_update(Screen *const screen) {
  if (screen != NULL) {
    _keyboard_events();
    LevelType nextLevel = _update_level(screen->content);
    _change_next_level(screen, nextLevel);
  }
}

void canvas_screen_draw(const Screen *const screen) {
  if (screen != NULL) {
    _draw_level(screen->content);
  }
}

void canvas_screen_destroy(Screen *screen) {
  if (screen != NULL) {
    _unload_level(screen);
    void *tmp = screen;
    memory_free_container(&tmp);
#if defined(AC_DEBUG)
    trace_destroyed("SCREEN", "Canvas");
#endif
  }
}

ScreenType canvas_screen_next_screen_type(void) { return _nextScreenType; }

// *************************************************
// Static functions implementation.
// *************************************************
static void _keyboard_events(void) {
  if (IsKeyPressed(KEY_F1)) {
    _nextScreenType = SCREEN_TYPE_MENU;
  }
}

static void _load_level(Screen *const screen, LevelType type) {
  if (screen != NULL) {
    Result result = {0};
    switch (type) {
    case LEVEL_TYPE_ONE:
      result = one_level_create();
      break;
    case LEVEL_TYPE_TWO:
      result = two_level_create();
      break;
    default:
      break;
    }

    if (result.code == ERROR_CODE_OK) {
      screen->content = result.data;
    }
  }
}
static void _unload_level(Screen *const screen) {
  if (screen != NULL && screen->content != NULL) {
    LevelType type = ((Level *)screen->content)->type;
    switch (type) {
    case LEVEL_TYPE_ONE:
      one_level_destroy(screen->content);
      screen->content = NULL;
      break;
    case LEVEL_TYPE_TWO:
      two_level_destroy(screen->content);
      screen->content = NULL;
      break;
    default:
      break;
    }
  }
}
static LevelType _update_level(Level *const level) {
  LevelType nextLevelType = LEVEL_TYPE_UNDEFINED;

  if (level != NULL) {
    LevelType type = level->type;
    switch (type) {
    case LEVEL_TYPE_ONE:
      one_level_update(level);
      nextLevelType = one_level_next();
      break;
    case LEVEL_TYPE_TWO:
      two_level_update(level);
      nextLevelType = two_level_next();
      break;
    default:
      break;
    }
  }

  return nextLevelType;
}

static void _draw_level(const Level *const level) {
  if (level != NULL) {
    LevelType type = level->type;
    switch (type) {
    case LEVEL_TYPE_ONE:
      one_level_draw(level);
      break;
    case LEVEL_TYPE_TWO:
      two_level_draw(level);
      break;
    default:
      break;
    }
  }
}

static void _change_next_level(Screen *const screen, LevelType type) {
  if (screen != NULL && type != LEVEL_TYPE_UNDEFINED) {
    _unload_level(screen);
    _load_level(screen, type);
  }
}
