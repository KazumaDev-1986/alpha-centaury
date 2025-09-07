// #include <stdio.h>
// #include <stdlib.h>

// #include "include/game.h"
// #include "include/memory.h"
// #if defined(AC_DEBUG)
// #include "include/trace_utils.h"
// #endif

// int main(void) {
//   bool hasError = false;
//   if (freopen("logs.txt", "w", stderr)) {
//     Result result = game_create();
//     if (result.code == ERROR_CODE_OK) {
//       Game *game = result.data;
//       game_run(game);
//       game_destroy(game);
//     } else {
// #if defined(AC_DEBUG)
//       trace_game_error();
// #endif
//       hasError = true;
//     }
//   } else {
//     printf("Error to create 'logs.txt' file.\n");
//     hasError = true;
//   }

//   return hasError ? EXIT_FAILURE : EXIT_SUCCESS;
// }

#include <stdio.h>

#include "include/map.h"
#include "include/pathfinder.h"
#include "include/raylib.h"
#include "include/types.h"

int main(void) {
  SetTraceLogLevel(LOG_DEBUG);
  Map *map = map_load("data/maps/map_1.csv");
  if (!map) {
    TraceLog(LOG_DEBUG, "Error to load Map....");
    return 0;
  }

  Pathfinder *pathfinder = pathfinder_create(map);
  if (!pathfinder) {
    map_unload(map);
    return 0;
  }

  ui16Point startPoint = (ui16Point){.x = 0, .y = 0};
  ui16Point endPoint = (ui16Point){.x = 6, .y = 1};
  ui16Point endPoint1 = (ui16Point){.x = 5, .y = 6};

  Square *square = pathfinder_search(pathfinder, startPoint, endPoint1);
  if (!square) {
    TraceLog(LOG_DEBUG, "Square is NULL.");
  }

  pathfider_reset(pathfinder);
  square = pathfinder_search(pathfinder, startPoint, endPoint1);
  if (!square) {
    TraceLog(LOG_DEBUG, "Square0 is NULL.");
  }


  for (Square *tmp = square; tmp != NULL; tmp = tmp->parent) {
    TraceLog(LOG_DEBUG, "x: %d, y: %d", tmp->x, tmp->y);
    map->buffer[tmp->y * map->width + tmp->x] = 2;
  }

  // Draw
  printf("\n");
  for (uint16_t i = 0; i < map->height; ++i) {
    for (uint16_t j = 0; j < map->width; ++j) {
      printf("%d ", map->buffer[i * map->height + j]);
    }
    printf("\n");
  }
  printf("\n");

  pathfinder_destroy(&pathfinder);
  map_unload(map);

  return 0;
}
