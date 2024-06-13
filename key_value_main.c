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

// data module
#include <data/key_value.h>

// Preprocessor definitions
#define KEY_VALUE_DB_SHELL_INPUT_MAX  1024
#define KEY_VALUE_DB_SHELL_PROMPT_MAX 128

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

// Data
char _prompt[KEY_VALUE_DB_SHELL_PROMPT_MAX] = { ' ', '$', '?', ' ', ' ', '$', '$', ' ', '\0' };
int last_result = 1;

// Entry point
int main ( int argc, const char *argv[] )
{

    // Suppress compiler warnings
    (void) argc;
    (void) argv;

    // Initialized data
    char _input[KEY_VALUE_DB_SHELL_INPUT_MAX] = { 0 };
    key_value_db *p_key_value_db = (void *) 0;

    key_value_db_construct(&p_key_value_db);

    // Read, Evaluate, Print loop
    while( !feof(stdin) )
    {
        
        // Prompt
        print_prompt();

        // Read a line from standard in
        fgets(_input, KEY_VALUE_DB_SHELL_INPUT_MAX, stdin);

        // Add a null terminator
        _input[strlen(_input) - 1] = '\0';

        // Evaluate
        {
            if ( strncmp(_input, "exit", KEY_VALUE_DB_SHELL_PROMPT_MAX) == 0 ) break;
            
            last_result = key_value_db_parse_statement(p_key_value_db,_input);

        }

        // Print
        //
    }

    // Formatting
    putchar('\r');

    // Success
    return EXIT_SUCCESS;
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

