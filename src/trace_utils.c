#include "include/trace_utils.h"
#include "include/raylib.h"

// *************************************************
// Public functions implementation.
// *************************************************
void trace_created(const char *type, const char *name) {
  TraceLog(LOG_DEBUG, ">> [%s] name: '%s' created.", type, name);
}

void trace_destroyed(const char *type, const char *name) {
  TraceLog(LOG_DEBUG, ">> [%s] name: '%s' destroyed.", type, name);
}

void trace_game_error(void) {
  TraceLog(LOG_DEBUG, ">> Error to initialize the game.");
}
