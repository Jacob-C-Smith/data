/** !
 * Key-Value database shell
 * 
 * @file key_value_main.c
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

// json module
#include <json/json.h>

// data module
#include <data/key_value.h>

// Preprocessor definitions
#define KEY_VALUE_DB_SHELL_INPUT_MAX  1024
#define KEY_VALUE_DB_SHELL_PROMPT_MAX 128

// Structure definitions
struct key_value_property_s
{
    char _key[31 + 1];
    json_value *p_value;
};

// Type definitions
typedef struct key_value_property_s key_value_property;

// Forward declarations
/** !
 * Initialize the key_value database 
 * 
 * @param void
 * 
 * @return 1 on success, 0 on error
 */
int key_value_db_early ( void );

/** !
 * Print the prompt to standard out
 * 
 * @param void
 * 
 * @return 1 on success, 0 on error
 */
int print_prompt ( void );

int key_get ( const char *p_key, json_value *p_value )
{

    if ( p_value == 0 ) return 0;
    if ( p_value->type != JSON_VALUE_STRING ) return 0;
    if ( p_value->string == 0 ) return 0;
    if ( strcmp(p_value->string, p_key) ) return 0;

    // Success
    return 1;
}

// Data
char _prompt[KEY_VALUE_DB_SHELL_PROMPT_MAX] = { ' ', '$', '?', ' ', ' ', '$', '$', ' ', '\0' };
int last_result = 1;

// Forward declarations
/** !
 * Print a usage message to standard out
 * 
 * @param argv0 the name of the program
 * 
 * @return void
 */
void print_usage ( const char *argv0 );

/** !
 * Parse command line arguments program
 * 
 * @param argc             the argc parameter of the entry point
 * @param argv             the argv parameter of the entry point
 * @param pp_database_path result
 * 
 * @return 1 on success, 0 on error
 */
int parse_arguments ( int argc, const char *argv[], const char **pp_database_path );


/** !
 * Example binary tree comparator
 * 
 * @param p_a pointer to a
 * @param p_b pointer to b 
 * 
 * @return 1 on success, 0 on error
*/
int binary_tree_example_comparator ( const void *const p_a, const void *const p_b );

/** !
 * Example binary tree key accessor
 * 
 * @param pp_result result
 * @param p_value   the value to access 
 * 
 * @return 1 on success, 0 on error
*/
const void *const binary_tree_example_key_accessor (const void *const p_value);

/** !
 * Example binary tree node serializer
 * 
 * @param p_file             the file to write to
 * @param p_binary_tree_node the binary tree node to write 
 * 
 * @return 1 on success, 0 on error
*/
int binary_tree_example_serializer ( FILE *p_file, binary_tree_node *p_binary_tree_node );

/** !
 * Example binary tree node parser
 * 
 * @param p_file             the file to read from
 * @param p_binary_tree_node the binary tree node to populate
 * 
 * @return 1 on success, 0 on error
*/
int binary_tree_example_parser ( FILE *p_file, binary_tree_node *p_binary_tree_node );

/** !
 * Print a binary tree node to standard out
 * 
 * @param p_value the value
 * 
 * @return 1 on success, 0 on error
 */
int binary_tree_print_node ( void *p_value );

// Entry point
int main ( int argc, const char *argv[] )
{
    
    // Suppress compiler warnings
    (void) argc;
    (void) argv;

    // Initialized data   
    char         *p_database_path = "out";
    key_value_db *p_key_value_db  = (void *) 0;
    binary_tree *p_binary_tree = 0;
    size_t random_index = ( rand() % 15 ) + 1;
    key_value_property *p_result = 0;
    
    // Parse command line arguments
    //parse_arguments(argc, argv, &p_database_path);

    remove(p_database_path);

    // Log
    fprintf(stderr, "Constructing tree... ");

    // Construct a tree
    if (binary_tree_construct(&p_binary_tree, binary_tree_example_comparator, binary_tree_example_key_accessor, 1008) == 0 ) goto failed_to_construct_tree;

    // Log
    fprintf(stderr, "DONE\nInserting properties...\n");

    // Iterate over each property
    while(!feof(stdin))
    {
        
        // Initialized data
        key_value_property *p_key_value_property = malloc(sizeof(key_value_property));
        json_value *p_value = 0;
        char _buf[1024] = { 0 };

        // Store the key
        if ( fgets(p_key_value_property->_key, 32, stdin) == EOF ) break;

        p_key_value_property->_key[strlen(p_key_value_property->_key) - 1] = '\0';

        // Store the value
        fgets(_buf, 1024, stdin);

        json_value_parse(_buf, 0, &p_key_value_property->p_value);

        // Store the property in the tree
        (void) binary_tree_insert(p_binary_tree, p_key_value_property);
    }
    
    // Log
    fprintf(stderr, "DONE\nSerializing tree... ");

    // Serialize the binary tree to a file
    if ( binary_tree_serialize(p_binary_tree, p_database_path, binary_tree_example_serializer) == 0 ) goto failed_to_serialize_binary_tree;

    // Find a key
    json_value *p_val = 0;
    binary_tree_search(p_binary_tree, "jake", &p_val);
    json_value_print(p_val);

    // Log
    fprintf(stderr, "DONE\nDestroying tree... ");

    // Destroy the binary tree
    if ( binary_tree_destroy(&p_binary_tree) == 0 ) goto failed_to_destroy_binary_tree;

    // Log
    fprintf(stderr, "DONE\nParsing tree... ");

    // Load the binary tree from the file
    if ( binary_tree_parse(&p_binary_tree, p_database_path, binary_tree_example_comparator, binary_tree_example_key_accessor, (fn_binary_tree_parse *) binary_tree_example_parser) == 0 ) goto failed_to_parse_binary_tree;
    
    // Traverse the binary tree using the in order technique
    //binary_tree_traverse_inorder(p_binary_tree, (fn_binary_tree_traverse *)binary_tree_print_node);
    
    // Serialize the binary tree to a file
    if ( binary_tree_serialize(p_binary_tree, p_database_path, binary_tree_example_serializer) == 0 ) goto failed_to_serialize_binary_tree;
    
    // Destroy the binary tree
    if ( binary_tree_destroy(&p_binary_tree) == 0 ) goto failed_to_destroy_binary_tree;

    // Log
    fprintf(stderr, "DONE\nParsing tree... ");

    // Load the binary tree from the file
    if ( binary_tree_parse(&p_binary_tree, p_database_path, binary_tree_example_comparator, binary_tree_example_key_accessor, (fn_binary_tree_parse *) binary_tree_example_parser) == 0 ) goto failed_to_parse_binary_tree;
    
    // Traverse the binary tree using the in order technique
    binary_tree_traverse_inorder(p_binary_tree, (fn_binary_tree_traverse *)binary_tree_print_node);

    // Log
    fprintf(stderr, "\nDONE\nPrinting tree... \n\n");
    
    // Success
    return 1;

    // Error handling
    {

        // Tree errors
        {
            failed_to_construct_tree:
                
                // Write an error message to standard out
                log_error("Error: Failed to construct binary tree!\n");

                // Error
                return EXIT_FAILURE;
            
            failed_to_serialize_binary_tree:
                                
                // Write an error message to standard out
                log_error("Error: Failed to serialize binary tree!\n");

                // Error
                return EXIT_FAILURE;

            failed_to_parse_binary_tree:

                // Write an error message to standard out
                log_error("Error: Failed to parse binary tree!\n");

                // Error
                return EXIT_FAILURE;
            
            failed_to_destroy_binary_tree:

                // Write an error message to standard out
                log_error("Error: Failed to destroy binary tree!\n");

                // Error
                return EXIT_FAILURE;

            failed_to_search_binary_tree:

                // Write an error message to standard out
                log_error("Error: Failed to search binary tree!\n");

                // Error
                return EXIT_FAILURE;
        }
    }
}

void print_usage ( const char *argv0 )
{

    // Argument check
    if ( argv0 == (void *) 0 ) exit(EXIT_FAILURE);

    // Print a usage message to standard out
    printf("Usage: %s database_file\n", argv0);

    // Done
    return;
}

int parse_arguments ( int argc, const char *argv[], const char **pp_database_path )
{

    // Argument check
    if ( argc != 2 ) goto missing_command_line_arguments;

    // Store the database name
    *pp_database_path = argv[1];

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            missing_command_line_arguments:
                
                // Print a usage message to standard out
                print_usage(argv[0]);

                // Abort execution
                exit(EXIT_FAILURE);
        }
    }
}

int binary_tree_example_comparator ( const void *const p_a, const void *const p_b )
{

    // Success
    return strcmp(((key_value_property *)p_b)->_key, ((key_value_property *)p_a)->_key);
}

const void *const binary_tree_example_key_accessor ( const void *const p_value )
{

    // Initialized data
    const key_value_property *p_key_value_property = p_value;

    // Success
    return &p_key_value_property->_key;
}

int binary_tree_example_serializer ( FILE *p_file, binary_tree_node *p_binary_tree_node )
{

    // Initialized data
    size_t value_start = 0,
           value_end   = 0,
           slack       = 0;
    
    // Write the key to the output
    fwrite(((key_value_property *)p_binary_tree_node->p_value)->_key, sizeof(char), 32, p_file);
    
    // Store the start of the value
    value_start = ftell(p_file);

    // Write the value to the output
    json_value_fprint(((key_value_property *)p_binary_tree_node->p_value)->p_value, p_file);
    
    // Store the end of the value
    value_end = ftell(p_file);

    // Compute the slack
    slack = value_end - value_start;
    
    // Pad the output
    for (size_t i = 0; i < (976 - slack); i++)
        fputc('\0', p_file);
    
    // Success
    return 1;
}

int binary_tree_example_parser ( FILE *p_file, binary_tree_node *p_binary_tree_node )
{

    // Initialized data
    key_value_property *p_key_value_property = malloc(sizeof(key_value_property));
    char _buf[976] = { 0 };

    // Read a string from the input
    fread(&p_key_value_property->_key, 32, 1, p_file);

    // Read a double from the input
    fread(_buf, 976, 1, p_file);

    // Parse a json value
    json_value_parse(&_buf, 0, &p_key_value_property->p_value);

    // Allocate memory for the value
    p_binary_tree_node->p_value = p_key_value_property;
    
    // Success
    return 1;
}

int binary_tree_print_node ( void *p_value )
{

    // Print the property
    log_info("%s : ", ((key_value_property *) p_value)->_key);

    // Print the json value
    json_value_print(((key_value_property *) p_value)->p_value);

    // Formatting
    putchar('\n');

    // Success
    return 1;
}


int key_value_db_early ( void )
{

    // Initialized data
    size_t  prompt_len = 0;
    char   *p_prompt = getenv("KEY_VALUE_DB_PROMPT");

    // Error check
    if ( p_prompt == NULL ) goto no_prompt;
    
    // Compute the length of the prompt
    prompt_len = strlen(p_prompt);

    // Copy the prompt
    strncpy(_prompt, p_prompt, prompt_len);

    // Success
    return 1;

    no_prompt:

        // Set the prompt to the default
        putenv("KEY_VALUE_DB_PROMPT=\"[ $? ] > \"");

        // Done
        return 1;
}

int print_prompt ( void )
{

    // Initialized data
    size_t i = 0;

    // Print the prompt
    while ( _prompt[i] )
    {
        
        // Ordinary characters ...
        if ( _prompt[i] != '$' )

            // ... get printed to standard out
            putchar(_prompt[i]);

        // Handle escape sequence
        else
        {

            // Strategy
            switch ( _prompt[i + 1] )
            {

                // Return code
                case '?':

                    // Print the return code
                    printf("%s", last_result ? "\033[92m✔\033[0m" : "\033[91m✘\033[0m");
         
                    // Done
                    break;

                // Dollar sign
                case '$':

                    // Print the return code
                    putchar('$');

                    // Done
                    break;

                // Erroneous prompt
                case '\0':
                default:

                    // Abort
                    exit(EXIT_FAILURE);                
            }

            // Skip
            i++;
        }

        // Increment counter
        i++;
    }
    
    // Success
    return 1;
}

