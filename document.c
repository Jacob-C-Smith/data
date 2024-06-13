/** !
 * Implementation of document database
 * 
 * @file document.c
 * 
 * @author Jacob Smith
 */

// Header 
#include <data/document.h>

// Preprocessor definitions
#define DATA_DOCUMENT_COLLECTION_NAME_LENGTH_MAX 64

// Structure definitions
struct data_document_s
{
    dict *p_keys;
};

struct data_document_collection_s
{
    char _name[DATA_DOCUMENT_COLLECTION_NAME_LENGTH_MAX];
};

// Function definitions
int data_document_create ( data_document **pp_data_document )
{

    // Argument check
    if ( pp_data_document == (void *) 0 ) goto no_data_document;

    // Initialized data
    data_document *p_data_document = DATA_REALLOC(0, sizeof(data_document));

    // Error check
    if ( p_data_document == (void *) 0 ) goto no_mem;

    // Initialize memory
    memset(p_data_document, 0, sizeof(data_document));

    // Return a pointer to the caller
    *pp_data_document = p_data_document;

    // Success
    return 1;

    // Error handling
    {
        
        // Argument errors
        {
            no_data_document:
                #ifndef NDEBUG
                    log_error("[data] [document] Null pointer provided for parameter \"pp_data_document\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Standard library
        {

            no_mem:
                #ifndef NDEBUG
                    log_error("[Standard library] Failed to allocate memory in call to function \"%s\"\n");
                #endif

                // Error
                return 0;
        }
    }
}

int data_document_construct ( data_document **pp_data_document )
{

   // Argument check
    if ( pp_data_document == (void *) 0 ) goto no_data_document;

    // Initialized data
    data_document *p_data_document = (void *) 0;

    // Error check
    if ( data_document_create(&p_data_document) == 0 ) goto failed_to_allocate_document_db;

    // Construct a dictionary for collections
    dict_construct(&p_data_document->p_collections, 64, 0);

    // Return a pointer to the caller
    *pp_data_document = p_data_document;

    // Success
    return 1;

    // Error handling
    {
        
        // Data errors
        {

            failed_to_allocate_document_db:
                #ifndef NDEBUG
                    log_error("[data] [document] Failed to allocate document database in call to function \"%s\"\n");
                #endif

                // Error
                return 0;
        }

        // Argument errors
        {
            no_data_document:
                #ifndef NDEBUG
                    log_error("[data] [document] Null pointer provided for parameter \"pp_data_document\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

void print_collection ( const void *const p_collection, size_t i )
{
    log_info("[%d] %s\n", i, ((data_document_collection *)p_collection)->_name);
}

int data_document_parse_statement ( data_document *p_data_document, char *p_instruction )
{
    
    if ( strncmp(p_instruction, "set", 3) == 0 )
    {
        p_instruction += 3;
        size_t len = strlen(p_instruction);
        data_document_collection *p_collection = DATA_REALLOC(0, sizeof(data_document_collection));
        strncpy(p_collection->_name, p_instruction, len);
        dict_add(p_data_document->p_collections, p_collection->_name, p_collection);
        log_info("[data] [document] Declared collection \"%s\"\n", p_instruction);
    }
    else if ( strncmp(p_instruction, "list", 4) == 0 )
    {
        dict_foreach(p_data_document->p_collections, print_collection);
    }

    // Success
    return 1;
}
