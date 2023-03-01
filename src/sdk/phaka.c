// Licensed to Werner Strydom under one or more agreements.
// Werner Strydom licenses this file to you under the MIT license.

//
// Created by Werner Strydom on 3/1/23.
//

#include "phaka.h"
#include "private-version.h"
#include "private-platform.h"

const char* phaka_version()
{
	return PHAKA_VERSION;
}

const char* phaka_system_name(void)
{
	return PHAKA_SYSTEM;
}

const char* phaka_system_arch(void)
{
	return PHAKA_ARCH;
}
