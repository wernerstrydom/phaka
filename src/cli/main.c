// Licensed to Werner Strydom under one or more agreements.
// Werner Strydom licenses this file to you under the MIT license.

#include <phaka.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	switch (argc)
	{
	case 2:
		if (strcmp(argv[1], "arch") == 0)
		{
			printf("%s\n", phaka_system_arch());
			return 0;
		}

		if (strcmp(argv[1], "system") == 0)
		{
			printf("%s\n", phaka_system_name());
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
