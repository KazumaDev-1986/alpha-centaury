#include "../include/level.h"
#include "../include/memory.h"

static LevelType _nextType = LEVEL_TYPE_UNDEFINED;

// *************************************************
// Static functions definition.
// *************************************************

#if defined(__cplusplus)
extern "C" {
#endif

static void _reset_variables(void);

#if defined(__cplusplus)
}
#endif

// *************************************************
// Public functions implementation.
// *************************************************
AC Result one_level_create(void) {
  Result result = memory_make_alloc(sizeof(Level));
  if (result.code == ERROR_CODE_OK) {
    _reset_variables();
    ((Level *)result.data)->type = LEVEL_TYPE_ONE;
  }

  return result;
}

AC void one_level_update(Level *const level) {
  // TODO
}

AC void one_level_draw(const Level *const level) { ClearBackground(ORANGE); }

AC void one_level_destroy(Level *level) {
  void *ptr = level;
  memory_free_container(&ptr);
}

AC LevelType one_level_next(void) { return _nextType; }

// *************************************************
// Static functions implementation.
// *************************************************
static void _reset_variables(void) { _nextType = LEVEL_TYPE_UNDEFINED; }
