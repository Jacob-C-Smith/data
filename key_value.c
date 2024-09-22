/** !
 * Header file for key value database
 * 
 * @author Jacob Smith
 * 
 * @file data/key_value.h
 */

// Header
#include <data/key_value.h>

// Binary tree
#include <tree/binary.h>

// Structure declarations
struct key_value_db_s
{
    binary_tree *p_binary_tree;
    char         _database_file[FILENAME_MAX];
};

struct key_value_db_property_s
{
    char        _key[KEY_VALUE_DB_PROPERTY_KEY_LENGTH_MAX];
    char        _value[KEY_VALUE_DB_PROPERTY_VALUE_LENGTH_MAX];
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

// Parsers
/** !
 * Parse a key value database node
 * 
 * @param p_file             the file
 * @param p_binary_tree_node pointer to the binary tree node
 * 
 * @return 1 on success, 0 on error
 */
int key_value_db_property_parse ( FILE *p_file, binary_tree_node *p_binary_tree_node );

int key_value_db_construct ( key_value_db **pp_key_value_db, key_value_db_create_info *p_key_value_db_create_info )
{

    // Argument errors
    if ( pp_key_value_db == (void *) 0 ) goto no_key_value_db;

    // Initialized data
    key_value_db *p_key_value_db = (void *) 0;
    FILE *p_file = (void *) 0;

    // Allocate a key value database
    if ( key_value_db_create(&p_key_value_db) == 0 ) goto failed_to_allocate_key_value_db;

    // Store the database file path
    strncpy(&p_key_value_db->_database_file, p_key_value_db_create_info->p_database_file, strlen(p_key_value_db_create_info->p_database_file));

    // Open the file 
    p_file = fopen(p_key_value_db_create_info->p_database_file, "r");

    // If the file exists ...
    if ( p_file )
    {

        // ... close the file ...
        fclose(p_file);

        // ... and parse the binary tree ...
        binary_tree_parse(&p_key_value_db->p_binary_tree, p_key_value_db_create_info->p_database_file, strcmp, key_value_db_property_parse);
    }

    // ... if the file doesn't exist ...
    else
    {

        // ... construct a binary tree 
        if ( binary_tree_construct(&p_key_value_db->p_binary_tree, strcmp, KEY_VALUE_DB_NODE_SIZE_BYTES) == 0 ) goto failed_to_allocate_dictionary;
    }

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
    //

    // Initialized data
    size_t l = strlen(p_key);
    key_value_db_property *p_property = 0;

    // Error check
    if ( l > KEY_VALUE_DB_PROPERTY_KEY_LENGTH_MAX ) return 0;

    // Allocate memory for a property
    p_property = realloc(0, sizeof(key_value_db_property));

    // Error check
    if ( p_property == (void *) 0 ) goto no_mem;

    // Copy the key
    memcpy(p_property->_key, p_key, l);

    // Store the value
    p_property->p_value = p_value;

    // Insert the property into the tree
    binary_tree_insert(p_key_value_db->p_binary_tree, p_property->_key, p_property->p_value);

    // Success
    return 1;

    // TODO: Error handling
    {

        // Argument errors
        {
            no_mem:
                #ifndef NDEBUG
                    // TODO
                #endif

                // Error
                return 0;
        }
    }
}

int key_value_db_get ( key_value_db *p_key_value_db, char *p_db_key, FILE *p_file )
{

    // TODO: Argument check
    //

    // Initialized data
    json_value *p_value = (void *) 0;

    // Search the binary tree
    binary_tree_search(p_key_value_db->p_binary_tree, p_db_key, &p_value);

    // Print the value to the file
    json_value_print(p_value);

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

int key_value_db_property_print ( void *p_key, void *p_value )
{

    // 
    printf("%s : ", p_key);

    json_value_print(p_value);

    putchar('\n');

    // Success
    return 1;
}

int key_value_db_property_serialize ( FILE *p_f, binary_tree_node *p_binary_tree_node )
{

    fwrite(p_binary_tree_node->p_key, 1, 32, p_f);

    size_t value_length = json_value_fprint(p_binary_tree_node->p_value, p_f) + 2;

    //json_value_print(p_binary_tree_node->p_value);

    // Pad the output ...
    for (size_t i = 0; i < ( (KEY_VALUE_DB_NODE_SIZE_BYTES - KEY_VALUE_DB_PROPERTY_KEY_LENGTH_MAX) - value_length) ; i++)

        // ... with zeros
        fputc('\0', p_f);

    // Success
    return 1;
}

int key_value_db_property_parse ( FILE *p_file, binary_tree_node *p_binary_tree_node )
{

    // TODO: Argument check
    //

    // Initialized data
    key_value_db_property *p_property = realloc(0, sizeof(key_value_db_property));

    // Initialize data
    memset(p_property, 0, sizeof(key_value_db_property));

    // Error check
    //

    // Read a key from the input
    fread(&p_property->_key, KEY_VALUE_DB_PROPERTY_KEY_LENGTH_MAX, 1, p_file);

    // Read a value from the input
    fread(&p_property->_value, KEY_VALUE_DB_PROPERTY_VALUE_LENGTH_MAX, 1, p_file);

    // Parse the json text into a json value
    if ( json_value_parse(p_property->_value, 0, &p_property->p_value) == 0 ) goto failed_to_parse_json_value;

    p_binary_tree_node->p_key = p_property->_key;
    p_binary_tree_node->p_value = p_property->p_value;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            
        }
        
        // json errors
        {
            failed_to_parse_json_value:

                // Error
                return 0;
        }
    }

}
int key_value_db_parse_statement ( key_value_db *p_key_value_db, char *p_input, char *p_output )
{

    // Argument errors
    if ( p_key_value_db == (void *) 0 ) goto no_key_value_db;

    // Initialized data
    int ret = 0;

    // Fast exit
    if ( strlen(p_input) == 0 ) return 1;

    // Set
    if ( strncmp(p_input, "set", 3) == 0 ) goto set_instruction;

    // Get
    else if ( strncmp(p_input, "get", 3) == 0 ) goto get_instruction;

    // List instruction
    else if ( strncmp(p_input, "list", 4) == 0 ) goto list_instruction;

    // Write
    else if ( strncmp(p_input, "write", 5) == 0 ) goto write_instruction;
    
    // Dones
    done:

    // Done
    return ret;

    // Set instruction
    set_instruction:
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
        ret = key_value_db_post(p_key_value_db, p_post_key, p_value);

        // Done
        goto done;
    }

    // Get instruction
    get_instruction:
    {
       
        // Initialized data
        char *p_get_key = 0;
        json_value *p_value = 0;

        strtok(p_instruction, " \n");

        p_get_key = strtok(0, "\n");
        p_get_key[strlen(p_get_key)]='\0';
        if (p_get_key) key_value_db_get(p_key_value_db, p_get_key, stdout);

        putchar('\n');

        // Success
        return 1;
    }

    // List instruction
    list_instruction:
    {

        // List the contents of the database
        binary_tree_traverse_inorder(p_key_value_db->p_binary_tree, key_value_db_property_print);

        // Success
        return 1;
    }

    // Write instruction
    write_instruction:
    {

        // Serialize the database
        binary_tree_serialize(p_key_value_db->p_binary_tree, &p_key_value_db->_database_file, key_value_db_property_serialize);

        // Success
        return 1;
    }

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

