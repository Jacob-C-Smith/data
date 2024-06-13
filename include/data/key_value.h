/** !
 * Header file for key value database
 * 
 * @author Jacob Smith
 * 
 * @file data/key_value.h
 */

// Standard library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// log module
#include <log/log.h>

// array module
#include <array/array.h>

// dict module
#include <dict/dict.h>

// json module
#include <json/json.h>

// data module
#include <data/data.h>

// Structure declarations
struct key_value_db_s;
struct key_value_db_property_s;

// Type definitions
typedef struct key_value_db_s          key_value_db;
typedef struct key_value_db_property_s key_value_db_property;

// Function declarations
// Allocators
/** !
 * Allocate a key value database
 * 
 * @param pp_key_value the key value database
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int key_value_db_create ( key_value_db **pp_key_value );

DLLEXPORT int key_value_db_construct ( key_value_db **pp_key_value );

DLLEXPORT int key_value_db_parse_statement ( key_value_db *p_key_value, char *p_instruction );

