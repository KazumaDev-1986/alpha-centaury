#ifndef AC_TRACE_UTILS_H
#define AC_TRACE_UTILS_H

#if defined(__cplusplus)
extern "C" {
#endif

void trace_created(const char *type, const char *name);
void trace_destroyed(const char *type, const char *name);
void trace_game_error(void);

#if defined(__cplusplus)
}
#endif

#endif // AC_TRACE_UTILS_H
