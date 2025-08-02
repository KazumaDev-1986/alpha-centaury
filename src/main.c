#include <stdio.h>
#include <stdlib.h>

#include "include/game.h"
#include "include/memory.h"
#if defined(AC_DEBUG)
#include "include/trace_utils.h"
#endif

int main(void) {
  bool hasError = false;
  if (freopen("logs.txt", "w", stderr)) {
    Result result = game_create();
    if (result.code == ERROR_CODE_OK) {
      Game *game = result.data;
      game_run(game);
      game_destroy(game);
    } else {
#if defined(AC_DEBUG)
      trace_game_error();
#endif
      hasError = true;
    }
  } else {
    printf("Error to create 'logs.txt' file.\n");
    hasError = true;
  }

  return hasError ? EXIT_FAILURE : EXIT_SUCCESS;
}
