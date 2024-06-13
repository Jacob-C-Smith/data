/** !
 * Header file for document database
 * 
 * @author Jacob Smith
 * 
 * @file data/document.h
 */

// Standard library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// log module
#include <log/log.h>

// dict module
#include <dict/dict.h>

// data module
#include <data/data.h>

// Structure declarations
struct data_document_s;
struct data_document_collection_s;

// Type definitions
typedef struct data_document_s data_document;
typedef struct data_document_collection_s data_document_collection;

// Function declarations
// Allocators
/** !
 * Allocate a document database
 * 
 * @param p_data_document the document database
 * 
 * @return 1 on success, 0 on error
 */
DLLEXPORT int data_document_create ( data_document **pp_data_document );

DLLEXPORT int data_document_construct ( data_document **pp_data_document );

DLLEXPORT int data_document_parse_statement ( data_document *p_data_document, char *p_instruction );

