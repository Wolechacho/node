#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main() {
  DIR* dir;
  struct dirent* entry;

  dir = opendir("/sandbox");
  assert(dir != NULL);

  errno = 0;
  while (NULL != (entry = readdir(dir))) {
    if (strcmp(entry->d_name, "input.txt") == 0 ||
        strcmp(entry->d_name, "input2.txt") == 0 ||
        strcmp(entry->d_name, "notadir") == 0) {
      assert(entry->d_type == DT_REG);
    } else if (strcmp(entry->d_name, "subdir") == 0) {
      assert(entry->d_type == DT_DIR);
    } else {
      assert("unexpected file");
    }
  }

  assert(errno == 0);
  closedir(dir);
  return 0;
}
