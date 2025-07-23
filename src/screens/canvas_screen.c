
#include <stddef.h>

#include "../include/config.h"
#include "../include/level.h"
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

static void _load_level(Screen *const level, LevelType type);
static void _unload_level(Screen *const level);
static void _update_level(Screen *const level);
static void _draw_level(const Screen *const level);

#if defined(__cplusplus)
}
#endif

// *************************************************
// Public functions implementation.
// *************************************************
AC Result canvas_screen_create(void) {
  Result result = memory_make_alloc(sizeof(Screen));
  if (result.code == ERROR_CODE_OK) {
    _nextScreenType = SCREEN_TYPE_UNDEFINED;
    ((Screen *)result.data)->type = SCREEN_TYPE_CANVAS;
    ((Screen *)result.data)->content = NULL;
  }

  return result;
}

AC void canvas_screen_update(Screen *const screen) {
  if (IsKeyPressed(KEY_F1)) {
    _nextScreenType = SCREEN_TYPE_MENU;
  }
}

AC void canvas_screen_draw(const Screen *const screen) { ClearBackground(RED); }

AC void canvas_screen_destroy(Screen **const ptr) {
  void *tmp = *ptr;
  memory_free_container(&tmp);
}

AC ScreenType canvas_screen_next_screen_type(void) { return _nextScreenType; }

// *************************************************
// Static functions implementation.
// *************************************************
static void _load_level(Screen *const screen, LevelType type) {
  Result result = {0};
  switch (type) {
    case LEVEL_TYPE_ONE:
      break;
    case LEVEL_TYPE_TWO:
      break;
    default:
      break;
  }

  if (result.code == ERROR_CODE_OK) {
    screen->content = result.data;
  }
}
static void _unload_level(Screen *const screen) {
  if (screen->content != NULL) {
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
static void _update_level(Screen *const screen) {
  if (screen->content != NULL) {
    LevelType type = ((Level *)screen->content)->type;
    switch (type) {
      case LEVEL_TYPE_ONE:
        one_level_update(screen->content);
        break;
      case LEVEL_TYPE_TWO:
        two_level_update(screen->content);        
        break;
      default:
        break;
    }
  }
}
static void _draw_level(const Screen *const screen) {
  if (screen->content != NULL) {
    LevelType type = ((Level *)screen->content)->type;
    switch (type) {
      case LEVEL_TYPE_ONE:
        one_level_draw(screen->content);
        break;
      case LEVEL_TYPE_TWO:
        two_level_draw(screen->content);        
        break;
      default:
        break;
    }
  }
}
