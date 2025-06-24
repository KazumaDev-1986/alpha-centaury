#include "include/game.h"
#include "include/memory.h"

int main(void) {
  ResultMemory result = game_create();
  if (result.code == ERROR_CODE_OK) {
    Game *game = result.data;
    game_run(game);
    game_destroy(&game);
  }

  return 0;
}
