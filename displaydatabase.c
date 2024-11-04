#include "main.h"
//function to display contents of the hash_table
void display_database(hash_t *HT, int size)
{
    //print the header with table with columun values
    printf("%-5s %-10s %-10s %-15s %-5s\n", "Index", "Word", "File_count", "File_name", "Count");
    
    //loop through each index in the hash_table
    for (int i = 0; i < size; i++) 
    { 
        //check if there is any main_node link at the index
        if (HT[i].link != NULL)
        { 
            //take a temporary pointer to traverse through the main node
            main_node *temp_m = HT[i].link; 
            //Traverse all main_nodes links 
            while (temp_m)
            { 
                //print the current index
                printf("%-6d", i); 
                //print the word
                printf("%-11s", temp_m->word); 
                //print the file count
                printf("%-11d", temp_m->filecount); 
                //Temporary to traverse through the sub_node
                sub_node *temp_s = temp_m->sub_node_link; 
                //Traverse all the subnodes
                while (temp_s) 
                { 
                    //print the file_name
                    printf("%-16s\t", temp_s->file_name); 
                    //print the word_count
                    printf("%-6d\t", temp_s->word_count); 
                    //move to the next subnode
                    temp_s = temp_s->subnode_link; 
                   
                }
                //move to the next line
                printf("\n"); 
                //move to the next mainnode
                temp_m = temp_m->main_node_link; 
            }
           
        }
    }
    //return SUCCESS; // Return success status
}
