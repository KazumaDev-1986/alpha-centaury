#ifndef AC_GAME_H
#define AC_GAME_H

#include "config.h"
#include "memory.h"

typedef struct {
  // TODO
} Game;

#if defined(__cplusplus)
extern "C" {
#endif

AC Result game_create(void);

AC void game_run(Game *const game);

AC void game_destroy(Game **const ptr);

#if defined(__cplusplus)
}
#endif

#endif // AC_GAME_H
