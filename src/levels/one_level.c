#include "../include/level.h"
#include "../include/memory.h"

#if defined(AC_DEBUG)
#include "../include/trace_utils.h"
#endif

static LevelType _nextType = LEVEL_TYPE_UNDEFINED;
static Color _backgroundColor = {0};

// *************************************************
// Static functions definition.
// *************************************************
static void _reset_variables(void);
static void _keyboard_events(void);

// *************************************************
// Public functions implementation.
// *************************************************
Result one_level_create(void) {
  Result result = memory_make_alloc(sizeof(Level));
  if (result.code == ERROR_CODE_OK) {
    _reset_variables();
    ((Level *)result.data)->type = LEVEL_TYPE_ONE;
#if defined(AC_DEBUG)
    trace_created("LEVEL", "One");
#endif
  }

  return result;
}

void one_level_update(Level *const level) { _keyboard_events(); }

void one_level_draw(const Level *const level) {
  ClearBackground(_backgroundColor);
}

void one_level_destroy(Level *level) {
  void *ptr = level;
  memory_free_container(&ptr);
#if defined(AC_DEBUG)
  trace_destroyed("LEVEL", "One");
#endif
}

LevelType one_level_next(void) { return _nextType; }

// *************************************************
// Static functions implementation.
// *************************************************
static void _reset_variables(void) {
  _nextType = LEVEL_TYPE_UNDEFINED;
  _backgroundColor = GetColor(AC_COLOR_4);
}

static void _keyboard_events(void) {
  if (IsKeyPressed(KEY_TWO)) {
    _nextType = LEVEL_TYPE_TWO;
  }
}
