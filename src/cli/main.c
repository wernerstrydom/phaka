#include <stdio.h>
#include <string.h>

#if defined(__linux__)
#define PHAKA_SYSTEM "linux"
#elif defined(__APPLE__)
#define PHAKA_SYSTEM "darwin"
#elif defined(_WIN32)
#define PHAKA_SYSTEM "windows"
#else
#error "Unsupported system"
#endif

#if defined(__x86_64__)
#define PHAKA_ARCH "amd64"
#elif defined(__i386__)
#define PHAKA_ARCH "i386"
#elif defined(__arm__)
#define PHAKA_ARCH "arm"
#else
#error "Unsupported architecture"
#endif

int main(int argc, char *argv[]) {
  switch (argc) {
  case 2:
    if (strcmp(argv[1], "arch") == 0) {
      printf("%s\n", PHAKA_ARCH);
      return 0;
    }

    if (strcmp(argv[1], "system") == 0) {
      printf("%s\n", PHAKA_SYSTEM);
      return 0;
    }

    if (strcmp(argv[1], "--version") == 0) {
      printf("phaka 0.1.0\n");
      return 0;
    }
  }
  return 1;
}
