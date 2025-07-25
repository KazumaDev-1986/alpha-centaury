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
#include "include/raylib.h"

int main(void) {
  SetTraceLogLevel(LOG_DEBUG);
  FileReader fileReader = file_data("data/levels/level_0.csv");

  uint32_t width = fileReader.width;
  uint32_t height = fileReader.height;
  printf("width: %d\n", width);
  printf("height:%d\n", height);
  for (uint32_t i = 0; i < height; ++i) {
    for (uint32_t j = 0; j < width; ++j) {
      uint32_t value = fileReader.buffer[i * width + j];
      printf("%d ", value);
    }
    printf("\n");
  }

  return 0;
}
