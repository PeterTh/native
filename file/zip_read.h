#ifndef _WIN32
#include <zip.h>
#endif

#include <string.h>

#include "base/basictypes.h"
#include "file/vfs.h"

// Direct readers. deallocate using delete [].
uint8_t *ReadLocalFile(const char *filename, size_t *size);

class AssetReader {
public:
  // use delete[]
  virtual uint8_t *ReadAsset(const char *path, size_t *size) = 0;
};

#ifndef _WIN32
uint8_t *ReadFromZip(zip *archive, const char* filename, size_t *size);
class ZipAssetReader : public AssetReader {
public:
  ZipAssetReader(const char *zip_file, const char *in_zip_path);
  ~ZipAssetReader();
  // use delete[]
  virtual uint8_t *ReadAsset(const char *path, size_t *size);

private:
  zip *zip_file_;
  char in_zip_path_[256];
};
#endif

class DirectoryAssetReader : public AssetReader {
public:
  DirectoryAssetReader(const char *path) {
    strcpy(path_, path);
  }
  // use delete[]
  virtual uint8_t *ReadAsset(const char *path, size_t *size);

private:
  char path_[512];
};
