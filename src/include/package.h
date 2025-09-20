#ifndef AC_PACKAGE_H
#define AC_PACKAGE_H

#include <stddef.h>

#include "config.h"
#include "raylib.h"

typedef enum {
  TEXTURE_TYPE_EMPTY = -1,
  TEXTURE_TYPE_GLOBAL_TILE = 0
}TextureType;

typedef struct {
  Texture *list;
  size_t size;
}TextureList;

typedef struct {
  TextureList textures;
  
} Package;

#if defined(__cplusplus)
extern "C" {
#endif

AC Package *package_create(void);
AC const Texture *package_get_texture_by_type(const Package *const package, TextureType type);
AC void package_destroy(Package ** ptrPackage);

#if defined(__cplusplus)
}
#endif

#endif //AC_PACKAGE_H
