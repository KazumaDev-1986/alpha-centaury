#include <stddef.h>

#include "include/config.h"
#include "include/memory.h"
#include "include/package.h"
#include "include/raylib.h"

#if defined(AC_DEBUG)
#include "include/trace_utils.h"
#endif

// *************************************************
// Static functions && variables definition.
// *************************************************
static const char *_texturePathList[] = {
    AC_PACKAGE_PATH_TEXTURE_TILE,
};

static const char *_fontPathList[] = {
    AC_PACKAGE_PATH_FONT_04B03,
};

static void _unload_package(Package **ptrPackage);

static bool _load_textures(Package *const package);
static Texture _load_texture(const char *fileName);
static void _unload_textures(Package *const package);

static bool _load_fonts(Package *const package);
static Font _load_font(const char *fileName);
static void _unload_fonts(Package *const package);

// *************************************************
// Public functions implementation.
// *************************************************
Package *package_create(void) {
  Package *package = NULL;
  Result result = memory_make_alloc(sizeof(Package));
  if (result.code == ERROR_CODE_OK) {
    package = result.data;

    bool hasErrorTextures = _load_textures(package);
    bool hasErrorFonts = _load_fonts(package);
    bool hasError = hasErrorTextures || hasErrorFonts;

    if (hasError) {
      _unload_package(&package);
    } else {
#if defined(AC_DEBUG)
      trace_created("global", "package");
#endif
    }
  } else {
#if defined(AC_DEBUG)
    trace_error_to_reservet_memory("Package");
#endif
  }

  return package;
}

AC void package_destroy(Package **ptrPackage) {
  if (ptrPackage && *ptrPackage) {
    _unload_textures(*ptrPackage);
    _unload_fonts(*ptrPackage);
    _unload_package(ptrPackage);
#if defined(AC_DEBUG)
    trace_destroyed("global", "package");
#endif
  }
}

// *************************************************
// Static functions implementation.
// *************************************************
static void _unload_package(Package **ptrPackage) {
  if (ptrPackage && *ptrPackage) {
    memory_free_container((void **)ptrPackage);
  }
}

static bool _load_textures(Package *const package) {
  bool hasError = false;
  size_t index = 0;

  for (size_t i = 0; i < 1 && !hasError; ++i) {
    Texture texture = _load_texture(_texturePathList[i]);
    if (texture.width != 0) {
      package->textures[i] = texture;
    } else {
      index = i;
      hasError = true;
    }
  }

  for (size_t i = 0; i < index; ++i) {
    UnloadTexture(package->textures[i]);
#if defined(AC_DEBUG)
    trace_unload_data("texture", _texturePathList[i]);
#endif
  }

  return hasError;
}

static void _unload_textures(Package *const package) {
  if (package) {
    for (size_t i = 0; i < AC_PACKAGE_TEXTURES_SIZE; ++i) {
      UnloadTexture(package->textures[i]);
#if defined(AC_DEBUG)
      trace_unload_data("texture", _texturePathList[i]);
#endif
    }
  }
}

static Texture _load_texture(const char *fileName) {
  Texture texture = {0};

  if (FileExists(fileName)) {
    texture = LoadTexture(fileName);
#if defined(AC_DEBUG)
    trace_load_data("texture", fileName);
#endif

  } else {
#if defined(AC_DEBUG)
    trace_file_not_found(fileName);
#endif
  }

  return texture;
}

static bool _load_fonts(Package *const package) {
  bool hasError = false;
  size_t index = 0;

  for (size_t i = 0; i < AC_PACKAGE_FONTS_SIZE && !hasError; ++i) {
    Font font = _load_font(_fontPathList[i]);
    if (font.glyphCount != 0) {
      package->fonts[i] = font;
    } else {
      index = i;
      hasError = true;
    }
  }

  for (size_t i = 0; i < index; ++i) {
    UnloadFont(package->fonts[i]);
#if defined(AC_DEBUG)
    trace_unload_data("font", _fontPathList[i]);
#endif
  }

  return hasError;
}

static Font _load_font(const char *fileName) {
  Font font = {0};
  if (FileExists(fileName)) {
    font = LoadFont(fileName);
#if defined(AC_DEBUG)
    trace_load_data("font", fileName);
#endif
  } else {
#if defined(AC_DEBUG)
    trace_file_not_found(fileName);
#endif
  }

  return font;
}

static void _unload_fonts(Package *const package) {
  if (package) {
    for (size_t i = 0; i < AC_PACKAGE_FONTS_SIZE; ++i) {
      UnloadFont(package->fonts[i]);
#if defined(AC_DEBUG)
      trace_unload_data("font", _fontPathList[i]);
#endif
    }
  }
}
