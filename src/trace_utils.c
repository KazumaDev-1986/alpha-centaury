#include <stdint.h>

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

void trace_map_size_exceeds(const char *fileName, uint16_t height,
                            uint16_t width) {
  TraceLog(LOG_DEBUG, ">> Error: Map size exceeds:'%s', h:'%d', w:'%d' .",
           fileName, height, width);
}

void trace_error_to_reservet_memory(const char *name) {
  TraceLog(LOG_DEBUG, ">> Error: to reservet memory:'%s'", name);
}

void trace_load_data(const char *type, const char *name) {
  TraceLog(LOG_DEBUG, ">> load '%s' - '%s'", type, name);
}

void trace_unload_data(const char *type, const char *name) {
  TraceLog(LOG_DEBUG, ">> unload '%s' - '%s'", type, name);
}
