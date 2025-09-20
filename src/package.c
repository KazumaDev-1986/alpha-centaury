#include <stddef.h>

#include "include/config.h"
#include "include/memory.h"
#include "include/package.h"
#include "include/raylib.h"
#include "include/trace_utils.h"

// *************************************************
// Static functions && variables definition.
// *************************************************
static const char *_texturePathList[] = {
    AC_PACKAGE_PATH_TEXTURE_TILE,
};

static void _unload_package(Package **ptrPackage);
static bool _load_textures(Package *const package);
static void _unload_textures(Package *const package);
static Texture _load_texture(const char *fileName);

// *************************************************
// Public functions implementation.
// *************************************************
Package *package_create(void) {
  Package *package = NULL;

  Result result = memory_make_alloc(sizeof(Package));
  if (result.code == ERROR_CODE_OK) {
    package = result.data;

    bool hasError = _load_textures(package);
    if (hasError) {
      _unload_textures(package);
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

AC const Texture *package_get_texture_by_type(const Package *const package,
                                              TextureType type) {
  Texture *texture = NULL;

  if (package && package->textures.size < (size_t)type) {
    texture = &package->textures.list[type];
  }

  return texture;
}

AC void package_destroy(Package **ptrPackage) {
  if (ptrPackage && *ptrPackage) {
    _unload_textures(*ptrPackage);
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
  package->textures = (TextureList){0};

  Result result = memory_make_alloc(sizeof(Texture) * AC_PACKAGE_TEXTURES_SIZE);
  if (result.code == ERROR_CODE_OK) {
    package->textures.list = result.data;
    package->textures.size = 0;

    // Load global sprite texture.
    for (size_t i = 0; i < 1 && !hasError; ++i) {
      Texture texture = _load_texture(_texturePathList[i]);
      if (texture.width != 0) {
        package->textures.list[0] = texture;
        ++package->textures.size;
      } else {
        hasError = true;
      }
    }
  } else {
    hasError = true;
  }

  return hasError;
}

static void _unload_textures(Package *const package) {
  if (package) {
    for (size_t i = 0; i < package->textures.size; ++i) {
      UnloadTexture(package->textures.list[i]);
    }
    memory_free_container((void **)&package->textures);
  }
}

static Texture _load_texture(const char *fileName) {
  Texture texture = {0};

  if (FileExists(fileName)) {
    texture = LoadTexture(fileName);
  } else {
#if defined(AC_DEBUG)
    trace_file_not_found(fileName);
#endif
  }

  return texture;
}
