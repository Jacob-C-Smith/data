/** !
 * Header file for relational database
 * 
 * @author Jacob Smith
 * 
 * @file data/relational.h
 */

// Standard library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// data module
#include <data/data.h>

// Preprocessor definitions
#define DATA_RELATIONAL_TABLE_NAME_LENGTH_MAX  127
#define DATA_RELATIONAL_COLUMN_NAME_LENGTH_MAX 127

// Structure declarations
struct data_relational_s;
struct data_relational_statement_s;
struct data_relational_column_definition_s;

// Type definitions
typedef struct data_relational_s data_relational;
typedef struct data_relational_statement_s data_relational_statement;
typedef struct data_relational_column_definition_s data_relational_column_definition;

// Function declarations
/** !
 * Parse a relational database statement
 * 
 * @param pointer        the statement
 * @param return_pointer null pointer OR end of statement
 * @param p_result       the result
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int data_relational_parse_statement ( const char *pointer, const char **const return_pointer, data_relational_statement **pp_result );
