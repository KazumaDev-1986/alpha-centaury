// #include <stdlib.h>

// #include "include/game.h"
// #include "include/memory.h"
// #if defined(AC_DEBUG)
// #include "include/trace_utils.h"
// #endif

// int main(void) {
//   Result result = game_create();
//   if (result.code == ERROR_CODE_OK) {
//     Game *game = result.data;
//     game_run(game);
//     game_destroy(game);
//   } else {
// #if defined(AC_DEBUG)
//     trace_game_error();
// #endif

//     return EXIT_FAILURE;
//   }
//   return EXIT_SUCCESS;
// }

#include <stdint.h>
#include <stdio.h>

#include "include/file_reader.h"
#include "include/map.h"
#include "include/memory.h"
#include "include/raylib.h"

int main(void) {
  SetTraceLogLevel(LOG_DEBUG);

  FileReader fileReader = file_data("data/levels/level_0.csv");
  if (fileReader.errorCode == ERROR_CODE_OK) {
    Map map = fileReader.map;

    // Draw map.
    for (uint16_t i = 0; i < map.height; i++) {

      for (uint16_t j = 0; j < map.width; j++) {
        uint32_t value = map.buffer[i * map.width + j];
        printf("%d ", value);
      }
      printf("\n");
    }

  } else {
    printf(">>> ERROR to load map.\n");
  }

  return 0;
}
