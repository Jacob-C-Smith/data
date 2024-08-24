/** !
 * Header file for key value database
 * 
 * @author Jacob Smith
 * 
 * @file data/key_value.h
 */

// Header
#include <data/key_value.h>

#include <tree/binary.h>

// Structure declarations
struct key_value_db_s
{
    binary_tree *p_binary_tree;
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

int key_value_db_construct ( key_value_db **pp_key_value_db, key_value_db_create_info *p_key_value_db_create_info )
{

    // Argument errors
    if ( pp_key_value_db == (void *) 0 ) goto no_key_value_db;

    // Initialized data
    key_value_db *p_key_value_db = (void *) 0;

    // Allocate a key value database
    if ( key_value_db_create(&p_key_value_db) == 0 ) goto failed_to_allocate_key_value_db;

    // Allocate a dictionary 
    if ( binary_tree_construct(&p_key_value_db->p_binary_tree, p_key_value_db_create_info->pfn_key_get, 4096) == 0 ) goto failed_to_allocate_dictionary;

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

int key_value_db_post ( key_value_db *p_key_value_db, char *p_key, json_value *p_value )
{

    // TODO: Argument check
    char *m = TREE_REALLOC(0, 4096);

    json_value_serialize(p_value, m);

    // Insert the property into the tree
    binary_tree_insert(p_key_value_db->p_binary_tree, p_key, m);

    // Success
    return 1;

    // TODO: Error handling
    { }
}

int key_value_db_get ( key_value_db *p_key_value_db, char *p_db_key, FILE *p_file )
{

    // TODO: Argument check
    //

    // Initialized data
    char *p_value = (void *) 0;

    // Search the binary tree
    binary_tree_search(p_key_value_db->p_binary_tree, p_db_key, &p_value);

    // Print the value to the file
    printf(p_value);

    // Success
    return 1;

    // TODO: Error handling
    { }
}

int key_value_db_put ( key_value_db *p_key_value_db, json_value *p_db_value )
{

    // Argument check
    //

    // Initialized data

    // Success
    return 1;

    // Error handling
    { }
}

int key_value_db_delete ( key_value_db *p_key_value_db, char *p_db_key )
{

    // Argument check
    //

    // Initialized data

    // Success
    return 1;

    // Error handling
    { }
}

void print_keys ( const void *const p_property, size_t i )
{
;
}

int key_value_db_parse_statement ( key_value_db *p_key_value_db, char *p_instruction )
{

    // Argument errors
    if ( p_key_value_db == (void *) 0 ) goto no_key_value_db;

    if ( strlen(p_instruction) == 0 ) return 1;

    if ( strncmp(p_instruction, "set", 3) == 0 )
    {
       
        // Initialized data
        char *p_post_key = 0;
        char *p_post_value = 0;
        json_value *p_value = 0;

        strtok(p_instruction, " \n");

        p_post_key = strtok(0, " \n");
        p_post_value = strtok(0, "\n");

        // Parse the value
        if ( json_value_parse(p_post_value, 0, &p_value ) == 0 ) goto failed_to_parse_json_value;

        // Update the value
        key_value_db_post(p_key_value_db, p_post_key, p_value);

        // Success
        return 1;
    }

    else if ( strncmp(p_instruction, "get", 3) == 0 )
    {
       
        // Initialized data
        char *p_get_key = 0;
        json_value *p_value = 0;

        strtok(p_instruction, " \n");

        p_get_key = strtok(0, "\n");
        p_get_key[strlen(p_get_key)-1]='\0';
        if (p_get_key)
        key_value_db_get(p_key_value_db, p_get_key, stdout);

        putchar('\n');

        // Success
        return 1;
    }


    else if ( strncmp(p_instruction, "list", 4) == 0 )
    {

        // Success
        return 1;
    }
    
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

        // json errors
        {
            failed_to_parse_json_value:
                #ifndef NDEBUG
                    log_error("[data] [key value] Failed to parse json value in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

