#ifndef AC_LEVEL_H
#define AC_LEVEL_H

#include "config.h"
#include "memory.h"

AC typedef enum {
  LEVEL_TYPE_UNDEFINED = -1,
  LEVEL_TYPE_ONE,
} LevelType;

AC typedef struct {
  LevelType type;
} Level;

#if defined(__cplusplus)
extern "C" {
#endif

AC Result one_level_create();
AC void one_level_update(Level *const level);
AC void one_level_draw(const Level *const level);
AC LevelType on_level_next(void);

#if defined(__cplusplus)
}
#endif

#endif  // AC_LEVEL_H
