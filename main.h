#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<ctype.h>

#define SUCCESS 1
#define FAILURE 0
//Node structure for single linked list
typedef struct node
{
    char array[50];   // Array to hold filename or data
    struct node *link;  // Pointer to the next node
} Slist;
// Structure for each entry in hash table
typedef struct hash_table
{
    int key;                  // Key value for hash table index
    struct main_node*link;    // Link to the first main node in the bucket
}hash_t;
// Structure for main nodes in the database
typedef struct main_node
{
    int filecount;              // Number of associated files
    char word[50];              // Word associated with this node
    struct main_node*main_node_link;  // Link to the next main node
    struct sub_node *sub_node_link;   // Link to the first sub-node
}main_node;
// Structure for sub-nodes linked to each main node
typedef struct sub_node
{
    int word_count;              // Count of occurrences in the file
    char file_name[50];          // Name of the file
    struct sub_node *subnode_link;  // Link to the next sub-node
}sub_node;         

// Function prototypes
// Reads and validates file input
int Read_Validate(char *argv[], Slist **head);
// Inserts a node at the end of linked list
int insert_at_last(Slist **head, char *str);
// Prints the linked list
void print_list(Slist *head);
// Initializes the hash table
void create_hashtable(hash_t *HT,int size);
// Creates a database from linked list and stores in hash table
int create_database(Slist *head,hash_t *HT);
// Displays contents of the hash table
void display_database(hash_t *HT,int size);
// Searches the hash table for an entry
int search_database(hash_t *HT);
// Saves the hash table contents to a file
int SaveDatabase(hash_t *HT,int size);
// Updates hash table from a file
int update_database(hash_t *HT,char *fptr);
// Removes duplicate entries from linked list
void RemoveDuplicate(hash_t *HT, Slist **head);

#endif // MAIN_H
