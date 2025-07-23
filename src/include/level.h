#ifndef AC_LEVEL_H
#define AC_LEVEL_H

#include "config.h"
#include "memory.h"

AC typedef enum {
  LEVEL_TYPE_UNDEFINED = -1,
  LEVEL_TYPE_ONE,
  LEVEL_TYPE_TWO,
} LevelType;

AC typedef struct {
  LevelType type;
} Level;

#if defined(__cplusplus)
extern "C" {
#endif

AC Result one_level_create(void);
AC void one_level_update(Level *const level);
AC void one_level_draw(const Level *const level);
AC void one_level_destroy(Level *level);
AC LevelType one_level_next(void);

AC Result two_level_create(void);
AC void two_level_update(Level *const level);
AC void two_level_draw(const Level *const level);
AC void two_level_destroy(Level *level);
AC LevelType two_level_next(void);

#if defined(__cplusplus)
}
#endif

#endif  // AC_LEVEL_H
