#ifndef AC_PACKAGE_H
#define AC_PACKAGE_H

#include <stddef.h>

#include "config.h"
#include "raylib.h"

typedef enum {
  TEXTURE_TYPE_EMPTY = -1,
  TEXTURE_TYPE_GLOBAL_TILE = 0
} TextureType;

typedef enum {
  FONT_FAMILY_04b_03 = 0,
} FontFamily;

typedef struct {
  Texture textures[AC_PACKAGE_TEXTURES_SIZE];
  Font fonts[AC_PACKAGE_FONTS_SIZE];
} Package;

#if defined(__cplusplus)
extern "C" {
#endif

AC Package *package_create(void);
AC void package_destroy(Package **ptrPackage);

#if defined(__cplusplus)
}
#endif

#endif // AC_PACKAGE_H
