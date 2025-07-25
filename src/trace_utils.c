#include "include/raylib.h"
#include "include/trace_utils.h"

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

void trace_file_not_found(const char *fileName) {
  TraceLog(LOG_DEBUG, ">> Error: file: %s not found.", fileName);
}

void trace_map_size_exceeds(const char *fileName) {
  TraceLog(LOG_DEBUG, ">> Error: Map size exceeds %s.", fileName);
}
