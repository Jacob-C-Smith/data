/** !
 * Document database shell
 * 
 * @file document_main.c
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
#include <data/document.h>

// Preprocessor definitions
#define DOCUMENT_DB_SHELL_INPUT_MAX  1024
#define DOCUMENT_DB_SHELL_PROMPT_MAX 128

/** !
 * Initialize the document database 
 * 
 * @param void
 * 
 * @return 1 on success, 0 on error
 */
int document_db_early ( void );

/** !
 * Print the prompt to standard out
 * 
 * @param void
 * 
 * @return 1 on success, 0 on error
 */
int print_prompt ( void );

// Data
char _prompt[DOCUMENT_DB_SHELL_PROMPT_MAX] = { '[', ' ', '$', '?', ' ', ']', ' ', '>', ' ', '\0' };
int last_result = 0;

// Entry point
int main ( int argc, const char *argv[] )
{

    // Suppress compiler warnings
    (void) argc;
    (void) argv;

    // Initialized data
    char _input[DOCUMENT_DB_SHELL_INPUT_MAX] = { 0 };
    data_document *p_document_database = { 0 };

    data_document_construct(&p_document_database);

    // Read, Evaluate, Print loop
    while( !feof(stdin) )
    {
        
        // Prompt
        print_prompt();

        // Read a line from standard in
        fgets(_input, DOCUMENT_DB_SHELL_INPUT_MAX, stdin);

        // Add a null terminator
        _input[strlen(_input) - 1] = '\0';

        // Evaluate
        {
            if ( strncmp(_input, "exit", DOCUMENT_DB_SHELL_PROMPT_MAX) == 0 ) break;
            
            data_document_parse_statement(p_document_database,_input);

        }

        // Print
        //
    }

    // Formatting
    putchar('\r');

    // Success
    return EXIT_SUCCESS;
}

int document_db_early ( void )
{

    // Initialized data
    size_t  prompt_len = 0;
    char   *p_prompt = getenv("DOCUMENT_DB_PROMPT");

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
        putenv("DOCUMENT_DB_PROMPT=\"[ $? ] > \"");

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
                    printf("%d", last_result);

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

