/**
 * Licensed to Werner Strydom under one or more agreements.
 * Werner Strydom licenses this file to you under the MIT license.
 * See the LICENSE file in the project root for more information.
 **/

/**
 * @file phaka.h
 * @author Werner Strydom
 * @brief The Phaka API.
 *
 */

#ifndef PHAKA_H
#define PHAKA_H

#include <phaka_export.h>

/**
 * @brief Get the version of the phaka library
 * @return The version of the phaka library (major.minor.patch)
 */
PHAKA_API const char* phaka_version(void);

/**
 * @brief Get the name of the operating system
 * @return The name of the system (linux, darwin, windows)
 */
PHAKA_API const char* phaka_system_name(void);

/**
 * @brief Get the architecture of the system
 * @return The architecture of the system (amd64, i386, arm, arm64)
 */
PHAKA_API const char* phaka_system_arch(void);

#endif //PHAKA_H
