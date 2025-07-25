#include <stdlib.h>

#include "include/game.h"
#include "include/memory.h"
#if defined(AC_DEBUG)
#include "include/trace_utils.h"
#endif

int main(void) {
  Result result = game_create();
  if (result.code == ERROR_CODE_OK) {
    Game *game = result.data;
    game_run(game);
    game_destroy(game);
  } else {
#if defined(AC_DEBUG)
    trace_game_error();
#endif

    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
