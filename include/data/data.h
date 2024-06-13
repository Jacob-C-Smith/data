/** ! 
 * Header file for database library
 * 
 * @file data/data.h
 * 
 * @author Jacob Smith
 */ 

// Standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// log module
#include <log/log.h>

// sync module
#include <sync/sync.h>

// array module
#include <array/array.h>

// dict module
#include <dict/dict.h>

// json module
#include <json/json.h>

// Platform dependent macros
#ifdef _WIN64
#define DLLEXPORT extern __declspec(dllexport)
#else
#define DLLEXPORT
#endif

// Set the reallocator for the dict module
#ifdef DICT_REALLOC
    #undef DICT_REALLOC
    #define DICT_REALLOC(p, sz) realloc(p, sz)
#endif

// Set the reallocator for the array module
#ifdef ARRAY_REALLOC
    #undef ARRAY_REALLOC
    #define ARRAY_REALLOC(p, sz) realloc(p, sz)
#endif

// Set the reallocator for the json module
#ifdef JSON_REALLOC
    #undef JSON_REALLOC
    #define JSON_REALLOC(p, sz) realloc(p, sz)
#endif

// Memory management macro
#ifndef DATA_REALLOC
    #define DATA_REALLOC(p, sz) realloc(p,sz)
#endif

/** !
 * Initialize the database library
 * 
 * @param void
 * 
 * @return 1 on success, 0 on error
 */
void data_init ( void ) __attribute__((constructor));

/** !
 * Teardown the database library
 * 
 * @param void
 * 
 * @return 1 on success, 0 on error
 */

void data_quit ( void ) __attribute__((destructor));
