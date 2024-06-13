/** !
 * Implements relational database
 * 
 * @file relational.c
 * 
 * @author Jacob Smith
 */

// Header
#include <data/relational.h>

// Enumeration definitions
enum data_relational_statement_type_e
{
    DATA_RELATIONAL_STATEMENT_INVALID = 0,
    DATA_RELATIONAL_STATEMENT_ALTER   = 1,
    DATA_RELATIONAL_STATEMENT_CREATE  = 2,
    DATA_RELATIONAL_STATEMENT_DELETE  = 3,
    DATA_RELATIONAL_STATEMENT_DROP    = 4,
    DATA_RELATIONAL_STATEMENT_INSERT  = 5,
    DATA_RELATIONAL_STATEMENT_SELECT  = 6,
    DATA_RELATIONAL_STATEMENT_UPDATE  = 7
};

// Structure definitions
struct data_relational_s
{
    int i;
};

struct data_relational_statement_s
{
    enum data_relational_statement_type_e type;

    union
    {
        struct
        {
            char _table_name[DATA_RELATIONAL_TABLE_NAME_LENGTH_MAX + 1];
        } create;
    };
};

struct data_relational_column_definition_s
{
    char _name[DATA_RELATIONAL_TABLE_NAME_LENGTH_MAX + 1];
};

// Function declarations
/** !
 * Parse a create statement
 * 
 * @param pointer        the statement
 * @param return_pointer pointer to text pointer
 * @param p_result       the result
 * 
 * @return 1 on success, 0 on error
 */
int data_relational_parse_create_statement ( const char *pointer, const char **const return_pointer, data_relational_statement **pp_result );

/** !
 * Parse a column definition
 * 
 * @param pointer        the text
 * @param return_pointer pointer to text pointer
 * @param pp_result      
 * 
 * @return 1 on success, 0 on error
 */
int data_relational_parse_column_definition ( const char *pointer, const char **const return_pointer, data_relational_column_definition *p_result );

/** !
 * Search text for a non whitespace character
 * 
 * @param pointer        the text
 * @param return_pointer return
 * 
 * @return 1 on success, 0 on error
 */
int data_relational_parse_whitespace ( const char *pointer, const char **const return_pointer );

int data_relational_parse_statement ( const char *pointer, const char **const return_pointer, data_relational_statement **pp_result )
{

    // Argument check
    if ( pointer   == (void *) 0 ) goto no_pointer;
    if ( pp_result == (void *) 0 ) goto no_result;

    // Initialized data
    data_relational_statement *p_result = DATA_REALLOC(0, sizeof(data_relational_statement));

    // Parse a value
    switch ( *pointer )
    {

        // This branch parses create statements
        case 'C':
        {
            // Initialized data
            char *last_pointer = pointer;
            
            // Parse the create statement
            if ( data_relational_parse_create_statement(pointer, &pointer, p_result) == 0 ) goto failed_to_parse_statement;
            
            // Increment the cursor
            pointer++;

            // Done
            break;
        }
    }

    // Done
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_pointer:
                #ifndef NDEBUG
                    log_error("[data] [relational] Null pointer provided for parameter \"pointer\" in call to function \"%s\"\n");
                #endif

                // Error
                return 0;

            no_result:
                #ifndef NDEBUG
                    log_error("[data] [relational] Null pointer provided for parameter \"pp_result\" in call to function \"%s\"\n");
                #endif

                // Error
                return 0;
        }

        // Data errors
        {
            bad_statement:
                #ifndef NDEBUG
                    log_error("[data] [relational] Bad statement provided in call to function \"%s\"\n");
                #endif

                // Error
                return 0;

            failed_to_parse_statement:
                #ifndef NDEBUG
                    log_error("[data] [relational] Failed to parse statement in call to function \"%s\"\n");
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

int data_relational_parse_create_statement ( const char *pointer, const char **const return_pointer, data_relational_statement **pp_result )
{

    // Argument check
    if ( pointer   == (void *) 0 ) goto no_pointer;
    if ( pp_result == (void *) 0 ) goto no_result;

    // Initialized data
    data_relational_statement *p_result = DATA_REALLOC(0, sizeof(data_relational_statement));
    char   *last_pointer   = pointer;
    size_t  string_len     = 0,
            table_name_len = 0;

    // Eat whitespace
    data_relational_parse_whitespace(pointer, &pointer);

    // Parse CREATE
    if ( strncmp("CREATE", pointer, 6) ) goto failed_to_parse_create_statement;
    pointer += 6;

    // Eat whitespace
    data_relational_parse_whitespace(pointer, &pointer);

    // Parse TABLE
    if ( strncmp("TABLE", pointer, 5) ) goto failed_to_parse_create_statement;
    pointer += 5;

    // Eat whitespace
    data_relational_parse_whitespace(pointer, &pointer);

    // Parse IF NOT EXISTS
    if ( strncmp("IF", pointer, 2) == 0 ) goto parse_not_exists;

    parse_table_name:

    // Store the table name length
    table_name_len = strcspn(pointer, ";");

    // Error check
    if ( table_name_len > DATA_RELATIONAL_TABLE_NAME_LENGTH_MAX ) goto table_name_too_long;

    // Copy the name of the table
    strncpy(p_result->create._table_name, pointer, table_name_len);

    // Store a null terminator
    p_result->create._table_name[table_name_len] = '\0';
    pointer += table_name_len;

    // Eat whitespace
    data_relational_parse_whitespace(pointer, &pointer);

    // Success
    return 1;

    // This branch parses "IF NOT EXISTS" statements
    parse_not_exists:
    {
        pointer += 2;

        // Eat whitespace
        data_relational_parse_whitespace(pointer, &pointer);

        // Parse NOT
        if ( strncmp("NOT", pointer, 3) ) goto failed_to_parse_create_statement;
        pointer += 3;

        // Eat whitespace
        data_relational_parse_whitespace(pointer, &pointer);

        // Parse EXISTS
        if ( strncmp("EXISTS", pointer, 6) ) goto failed_to_parse_create_statement;
        pointer += 6;

        // Done
        goto parse_table_name;
    }

    // Error handling
    {

        // Argument errors
        {
            no_pointer:
                #ifndef NDEBUG
                    log_error("[data] [relational] Null pointer provided for parameter \"pointer\" in call to function \"%s\"\n");
                #endif

                // Error
                return 0;

            no_result:
                #ifndef NDEBUG
                    log_error("[data] [relational] Null pointer provided for parameter \"pp_result\" in call to function \"%s\"\n");
                #endif

                // Error
                return 0;
        }

        // Data errors
        {
            bad_statement:
                #ifndef NDEBUG
                    log_error("[data] [relational] Bad statement provided in call to function \"%s\"\n");
                #endif

                // Error
                return 0;

            failed_to_parse_create_statement:
                #ifndef NDEBUG
                    log_error("[data] [relational] Failed to parse create statement in call to function \"%s\"\n");
                #endif

                // Error
                return 0;

            table_name_too_long:
                #ifndef NDEBUG
                    log_error("[data] [relational] Table name must be less than or equal to %d characters in call to function \"%s\"\n", DATA_RELATIONAL_TABLE_NAME_LENGTH_MAX);
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

int data_relational_parse_column_definition ( const char *pointer, const char **const return_pointer, data_relational_column_definition *p_result )
{
    // Argument check
    if ( pointer  == (void *) 0 ) goto no_pointer;
    if ( p_result == (void *) 0 ) goto no_result;

    // Initialized data
    data_relational_column_definition _result = { 0 }; 
    char *last_pointer = pointer;

    // Error handling
    {

        // Argument errors
        {
            no_pointer:
                #ifndef NDEBUG
                    log_error("[data] [relational] Null pointer provided for parameter \"pointer\" in call to function \"%s\"\n");
                #endif

                // Error
                return 0;

            no_result:
                #ifndef NDEBUG
                    log_error("[data] [relational] Null pointer provided for parameter \"p_result\" in call to function \"%s\"\n");
                #endif

                // Error
                return 0;
        }

        // Data errors
        {
            bad_statement:
                #ifndef NDEBUG
                    log_error("[data] [relational] Bad statement provided in call to function \"%s\"\n");
                #endif

                // Error
                return 0;

            failed_to_parse_column_definition:
                #ifndef NDEBUG
                    log_error("[data] [relational] Failed to parse column definition in call to function \"%s\"\n");
                #endif

                // Error
                return 0;

            column_name_too_long:
                #ifndef NDEBUG
                    log_error("[data] [relational] Column name must be less than or equal to %d characters in call to function \"%s\"\n", DATA_RELATIONAL_COLUMN_NAME_LENGTH_MAX);
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

int data_relational_parse_whitespace ( const char *pointer, const char **const return_pointer )
{

    // Argument check
    if ( pointer  == (void *) 0 ) goto no_pointer;
    if ( *pointer ==       '\0' ) goto done;

    // Skip past spaces, line feed, carriage return, horizontal tab
    while (
        *pointer == ' '  ||
        *pointer == '\n' ||
        *pointer == '\r' ||
        *pointer == '\t' ||
        *pointer == '\0' 
    )
    { pointer++; };

    // Error checking
    if ( *pointer == '\0' ) return 0;
    
    done:
    // Return the new pointer
    *return_pointer = pointer;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_pointer:
                #ifndef NDEBUG
                    printf("[data] [relational] Null pointer provided for parameter \"pointer\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

        }
    }
}
