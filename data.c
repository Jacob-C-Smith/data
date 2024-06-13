/** !
 * Implements general database functions 
 * 
 * @file data.c
 * 
 * @author Jacob Smith
 */ 

// Header
#include <data/data.h>

void data_init ( void )
{

    // Initialize libraries
    log_init();
    sync_init();
    dict_init();
    hash_cache_init();
    json_init();

    // Done
    return;
}

void data_quit ( void )
{

    // Done
    return;
}
