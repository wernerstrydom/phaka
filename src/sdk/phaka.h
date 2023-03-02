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
 * @brief The error type
 * @details This type is used to return errors from the Phaka API.
 * @see phaka_error_t
 * @see phaka_error_message
 * @see phaka_error_code
 * @see phaka_error_free
 * @see phaka_error_new
  */
struct phaka_error_t {
	int code;
	char* message;
};

/**
 * @brief The error type
 * @details This type is used to return errors from the Phaka API.
 * @see phaka_error_t
 * @see phaka_error_message
 * @see phaka_error_code
 * @see phaka_error_free
 * @see phaka_error_new
 */
typedef struct phaka_error_t phaka_error_t;

/**
 * @brief Get the error message
 * @param error The error
 * @return The error message
 */
PHAKA_API const char* phaka_error_message(phaka_error_t* error);

/**
 * @brief Get the error code
 * @param error The error
 * @return The error code
 */
PHAKA_API int phaka_error_code(phaka_error_t* error);

/**
 * @brief Free the error
 * @param error The error
 */
PHAKA_API void phaka_error_free(phaka_error_t* error);

/**
 * @brief Create a new error
 * @param code The error code
 * @param message The error message
 * @return The error
 */
PHAKA_API phaka_error_t* phaka_error_new(int code, const char* message);


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

/**
 * @brief Defines a phaka server
 */
struct phaka_server_t;

/**
  * @brief Defines a phaka server
  */
typedef struct phaka_server_t phaka_server_t;

/**
  * @brief Create a new phaka server
  * @param port The port to listen on
  * @param threads The number of threads to use
  * @param connections The number of connections to accept
  * @param timeout The number of seconds to wait before timing out
  * @return The server
  */
PHAKA_API phaka_server_t* phaka_server_new(int port);

/**
  * @brief Free the server
  * @param server The server
  */
PHAKA_API void phaka_server_free(phaka_server_t* server);

/**
  * @brief Runs the server
  */
PHAKA_API void phaka_server_run(phaka_server_t* server, phaka_error_t** error);

#endif//PHAKA_H
