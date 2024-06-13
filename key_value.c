/** !
 * Header file for key value database
 * 
 * @author Jacob Smith
 * 
 * @file data/key_value.h
 */

// Header
#include <data/key_value.h>

// Structure declarations
struct key_value_db_s
{
    dict *p_properties;
};

struct key_value_db_property_s
{
    char _key[128];
    json_value *p_value;
};

// Function declarations
// Allocators
/** !
 * Allocate a key value database
 * 
 * @param pp_key_value the key value database
 * 
 * @return 1 on success, 0 on error
 */
int key_value_db_create ( key_value_db **pp_key_value_db )
{

    // Argument errors
    if ( pp_key_value_db == (void *) 0 ) goto no_key_value_db;

    // Initialized data
    key_value_db *p_key_value_db = DATA_REALLOC(0, sizeof(key_value_db));

    // Error handling
    if ( p_key_value_db == (void *) 0 ) goto no_mem;

    // Initialize memory
    memset(p_key_value_db, 0, sizeof(key_value_db));

    // Return a pointer to the caller
    *pp_key_value_db = p_key_value_db;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_key_value_db:
                #ifndef NDEBUG
                    log_error("[data] [key value] Null pointer provided for parameter \"pp_key_value_db\" in call to function \"%s\"\n", __FUNCTION__);
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

int key_value_db_construct ( key_value_db **pp_key_value_db )
{

    // Argument errors
    if ( pp_key_value_db == (void *) 0 ) goto no_key_value_db;

    // Initialized data
    key_value_db *p_key_value_db = (void *) 0;

    // Allocate a key value database
    if ( key_value_db_create(&p_key_value_db) == 0 ) goto failed_to_allocate_key_value_db;

    // Allocate a dictionary 
    if ( dict_construct(&p_key_value_db->p_properties, 64, 0) == 0 ) goto failed_to_allocate_dictionary;

    // Return a pointer to the caller
    *pp_key_value_db = p_key_value_db;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_key_value_db:
                #ifndef NDEBUG
                    log_error("[data] [key value] Null pointer provided for parameter \"pp_key_value_db\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Data errors
        {
            failed_to_allocate_key_value_db:
                #ifndef NDEBUG
                    log_error("[data] [key value] Failed to allocate memory for key value database in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Dictionary errors
        {
            failed_to_allocate_dictionary:
                #ifndef NDEBUG
                    log_error("[data] [key value] Failed to allocate memory for dictionary in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

void print_keys ( const void *const p_property, size_t i )
{
    log_info("[%d] %s\n", i, ((key_value_db_property *)p_property)->_key);
}

int key_value_db_parse_statement ( key_value_db *p_key_value_db, char *p_instruction )
{

    // Argument errors
    if ( p_key_value_db == (void *) 0 ) goto no_key_value_db;

    if ( strlen(p_instruction) == 0 ) return 1;

    if ( strncmp(p_instruction, "set", 3) == 0 )
    {
        p_instruction += 4;
        size_t len = strlen(p_instruction);
        key_value_db_property *p_property = DATA_REALLOC(0, sizeof(key_value_db_property));
        strncpy(p_property->_key, p_instruction, len);
        dict_add(p_key_value_db->p_properties, p_property->_key, p_property);
        printf("[ OK ]\n");
 

        // Success
        return 1;
    }
    else if ( strncmp(p_instruction, "list", 4) == 0 )
    {
        dict_foreach(p_key_value_db->p_properties, print_keys);

        // Success
        return 1;
    }
    
    printf("Hey jackass, try typing a command\n");

    // Error
    return 0;

    // Error handling
    {

        // Argument errors
        {
            no_key_value_db:
                #ifndef NDEBUG
                    log_error("[data] [key value] Null pointer provided for parameter \"p_key_value_db\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

