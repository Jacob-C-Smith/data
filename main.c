/** !
 * Database example
 * 
 * @file main.c
 * 
 * @author Jacob Smith 
 */

// Standard library
#include <stdio.h>
#include <stdlib.h>

// log
#include <log/log.h>

// data
#include <data/data.h>
#include <data/key_value.h>

// Global
bool preserve_databases = false;

// Enumeration definitions
enum data_examples_e
{
    DATA_KEY_VALUE_EXAMPLE   = 0,
    DATA_WIDE_COLUMN_EXAMPLE = 1,
    DATA_DOCUMENT_EXAMPLE    = 2,
    DATA_RELATIONAL_EXAMPLE  = 3,
    DATA_GRAPH_EXAMPLE       = 4, 
    DATA_SPATIAL_EXAMPLE     = 5, 
    DATA_EXAMPLE_QUANTITY    = 6
};

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
 * Parse command line arguments
 * 
 * @param argc            the argc parameter of the entry point
 * @param argv            the argv parameter of the entry point
 * @param examples_to_run return
 * 
 * @return void on success, program abort on failure
 */
void parse_command_line_arguments ( int argc, const char *argv[], bool *examples_to_run );

/** !
 * Key value database example program
 * 
 * @param argc the argc parameter of the entry point
 * @param argv the argv parameter of the entry point
 * 
 * @return 1 on success, 0 on error
 */
int data_key_value_example ( int argc, const char *argv[] );

// Entry point
int main ( int argc, const char *argv[] )
{
    
    // Initialized data
    bool examples_to_run[DATA_EXAMPLE_QUANTITY] = { 0 };

    // Parse command line arguments
    parse_command_line_arguments(argc, argv, examples_to_run);

    // Initialize parallel
    if ( data_init() == 0 ) goto failed_to_initialize_data;

    // Formatting
    printf(
        "╭──────────────╮\n"\
        "│ data example │\n"\
        "╰──────────────╯\n"\
    );

    // Formatting
    printf(
        "The data library provides high level abstractions for databases.\n"\
        "Data provides %d database abstractions. The key value, the wide column, the document,\n"\
        "the relational, the and the graph databases.\n\n"\
        "TODO: Describe key value database\n"\
        "TODO: Describe wide column database\n"\
        "TODO: Describe document database\n"\
        "TODO: Describe relational database\n"\
        "TODO: Describe graph database\n"\
        "TODO: Describe spatial database\n\n",
        DATA_EXAMPLE_QUANTITY
    );

    //////////////////////
    // Run the examples //
    //////////////////////

    // Run the key value example program
    if ( examples_to_run[DATA_KEY_VALUE_EXAMPLE] )

        // Error check
        if ( data_key_value_example(argc, argv) == 0 ) goto failed_to_run_key_value_example;

    // Clean up data
    data_quit();

    // Success
    return EXIT_SUCCESS;

    // Error handling
    {
        
        failed_to_initialize_data:

            // Write an error message to standard out
            printf("Failed to initialize data!\n");

            // Error
            return EXIT_FAILURE;

        failed_to_run_key_value_example:

            // Print an error message
            printf("Failed to run key value example!\n");

            // Error
            return EXIT_FAILURE;
    }
}

void print_usage ( const char *argv0 )
{

    // Argument check
    if ( argv0 == (void *) 0 ) exit(EXIT_FAILURE);

    // Print a usage message to standard out
    printf("Usage: %s [key-value] [wide-column] [document] [relational] [graph]\n", argv0);

    // Done
    return;
}

void parse_command_line_arguments ( int argc, const char *argv[], bool *examples_to_run )
{

    // If no command line arguments are supplied, run all the examples
    if ( argc == 1 ) goto all_examples;

    // Error check
    if ( argc > DATA_EXAMPLE_QUANTITY + 1 ) goto invalid_arguments;

    // Iterate through each command line argument
    for (int i = 1; i < argc; i++)
    {
        
        // Key value example?
        if ( strcmp(argv[i], "key-value") == 0 )

            // Set the key value example flag
            examples_to_run[DATA_KEY_VALUE_EXAMPLE] = true;

        // Wide column example?
        else if ( strcmp(argv[i], "wide-column") == 0 )
            
            // Set the wide column example flag
            examples_to_run[DATA_WIDE_COLUMN_EXAMPLE] = true;

        // Document example?
        else if ( strcmp(argv[i], "document") == 0 )

            // Set the document example flag
            examples_to_run[DATA_DOCUMENT_EXAMPLE] = true;

        // Relational example?
        else if ( strcmp(argv[i], "relational") == 0 )

            // Set the schedule example flag
            examples_to_run[DATA_RELATIONAL_EXAMPLE] = true;
        
        // Graph example?
        else if ( strcmp(argv[i], "graph") == 0 )

            // Set the graph example flag
            examples_to_run[DATA_GRAPH_EXAMPLE] = true;
        
        // Spatial example?
        else if ( strcmp(argv[i], "spatial") == 0 )

            // Set the spatial example flag
            examples_to_run[DATA_SPATIAL_EXAMPLE] = true;

        // Preserve db files?
        else if ( strcmp(argv[i], "--preserve-database-files") == 0 )
            
            // Set the preserve flag
            preserve_databases = true;

        // Default
        else goto invalid_arguments;
    }
    
    // Success
    return;

    // Set each example flag
    all_examples:
    {

        // For each example ...
        for (size_t i = 0; i < DATA_EXAMPLE_QUANTITY; i++)
        
            // ... set the example flag
            examples_to_run[i] = true;
        
        // Success
        return;
    }

    // Error handling
    {

        // Argument errors
        {
            invalid_arguments:
                
                // Print a usage message to standard out
                print_usage(argv[0]);

                // Abort
                exit(EXIT_FAILURE);
        }
    }
}

int data_key_value_example ( int argc, const char *argv[] )
{
    
    // Supress warnings
    (void) argc;
    (void) argv;

    // Formatting
    printf(
        "╭───────────────────╮\n"\
        "│ key value example │\n"\
        "╰───────────────────╯\n"\
        "TODO: Describe example.\n\n"
    );

    // Initialized data
    data_key_value *p_key_value = (void *) 0;
    void *p_key   = (void *) 0,
         *p_value = (void *) 0;

    // TODO: Declare, document, and define all these functions
    /*
    // Construct a key value database
    data_key_value_construct(&p_key_value, 0);

    // Create x5
    data_key_value_create(p_key_value, "A", "value");
    data_key_value_create(p_key_value, "B", "value");
    data_key_value_create(p_key_value, "C", "value");
    data_key_value_create(p_key_value, "D", "value");
    data_key_value_create(p_key_value, "E", "value");

    // Save -> Close -> Load
    data_key_value_save(p_key_value, "key_value.db");
    data_key_value_close(&p_key_value);
    data_key_value_load(&p_key_value, "key_value.db");

    // Delete x1
    data_key_value_delete(p_key_value, "E");

    // Save -> Close -> Load
    data_key_value_save(p_key_value, "key_value.db");
    data_key_value_close(&p_key_value);
    data_key_value_load(&p_key_value, "key_value.db");

    // Read
    data_key_value_read(&p_key_value, "A", &p_value);

    // Update
    data_key_value_read(&p_key_value, "A", "VALUE");

    // Read
    data_key_value_read(&p_key_value, "A", "VALUE");
    
    // Save -> Close -> Load
    data_key_value_save(p_key_value, "key_value.db");
    data_key_value_close(&p_key_value);
    data_key_value_load(&p_key_value, "key_value.db");

    // Read
    data_key_value_read(&p_key_value, "A", "VALUE");

    // Save -> Close
    data_key_value_save(p_key_value, "key_value.db");
    data_key_value_close(&p_key_value);
    
    // Clean up
    if ( preserve_databases == false ) 

        // Remove the file
        remove("key_value.db");
    */

    // Success
    return 1;

    // Error handling
    {

        // Data errors
        {
            
        }
    }
}
