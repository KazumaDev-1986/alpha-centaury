#include "../include/level.h"
#include "../include/memory.h"
#include "../include/package.h"

#if defined(AC_DEBUG)
#include "../include/trace_utils.h"
#endif

extern Package *globalPackage;

// *************************************************
// Static functions definition.
// *************************************************
static LevelType _nextType = LEVEL_TYPE_UNDEFINED;
static Color _backgroundColor = {0};

static void _reset_variables(void);
static void _keyboard_events(void);

// *************************************************
// Public functions implementation.
// *************************************************
Result one_level_create(void) {
  Result result = memory_make_alloc(sizeof(Level));
  if (result.code == ERROR_CODE_OK) {
    _reset_variables();
    _backgroundColor = globalPackage->colors[10];
    ((Level *)result.data)->type = LEVEL_TYPE_ONE;
    ((Level *)result.data)->map = map_load("data/maps/map_0.csv");
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

void one_level_destroy(Level **ptrLevel) {
  if (ptrLevel && *ptrLevel) {
    map_unload(&(*ptrLevel)->map);
    memory_free_container((void **)ptrLevel);
#if defined(AC_DEBUG)
    trace_destroyed("LEVEL", "One");
#endif
  }
}

LevelType one_level_next(void) { return _nextType; }

// *************************************************
// Static functions implementation.
// *************************************************
static void _reset_variables(void) {
  _nextType = LEVEL_TYPE_UNDEFINED;
  _backgroundColor = (Color){0};
}

static void _keyboard_events(void) {
  if (IsKeyPressed(KEY_TWO)) {
    _nextType = LEVEL_TYPE_TWO;
  }
}
