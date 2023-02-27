// Licensed to Werner Strydom under one or more agreements.
// Werner Strydom licenses this file to you under the MIT license.

#include <version.h>
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

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
#define PHAKA_ARCH "amd64"
#endif

#if defined(i386) || defined(__i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) ||    \
		defined(_M_I86) || defined(_M_IX86) || defined(__X86__) || defined(_X86_) || defined(__THW_INTEL__) ||                 \
		defined(__I86__) || defined(__386)
#define PHAKA_ARCH "i386"
#endif

#ifndef PHAKA_ARCH
#error "Unsupported architecture"
#endif

int main(int argc, char* argv[])
{
	switch (argc)
	{
	case 2:
		if (strcmp(argv[1], "arch") == 0)
		{
			printf("%s\n", PHAKA_ARCH);
			return 0;
		}

		if (strcmp(argv[1], "system") == 0)
		{
			printf("%s\n", PHAKA_SYSTEM);
			return 0;
		}

		if (strcmp(argv[1], "--version") == 0)
		{
			printf("phaka %s\n", phaka_version());
			return 0;
		}
	}
	return 1;
}
