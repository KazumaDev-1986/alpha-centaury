
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
AC Result two_level_create(void) {
  Result result = memory_make_alloc(sizeof(Level));
  if (result.code == ERROR_CODE_OK) {
    _reset_variables();
    ((Level *)result.data)->type = LEVEL_TYPE_TWO;
  }

  return result;
}

AC void two_level_update(Level *const level) {
  // TODO
}

AC void two_level_draw(const Level *const level) { ClearBackground(YELLOW); }

AC void two_level_destroy(Level *level) {
  void *ptr = level;
  memory_free_container(&ptr);
}

AC LevelType two_level_next(void) { return _nextType; }

// *************************************************
// Static functions implementation.
// *************************************************
static void _reset_variables(void) { _nextType = LEVEL_TYPE_UNDEFINED; }
