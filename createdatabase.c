#include "main.h"
//Define the create_database with passing head and hash table HT
int create_database(Slist *head, hash_t *HT)
{
    //create a file pointer fptr
    FILE *fptr;
    //create a temporary pointer to store header address to traverse entire linked list
    Slist *temp = head;
    //traverse all nodes in linked list
    while (temp != NULL)
    {
        //open every file in linked list in read mode
        fptr = fopen(temp->array, "r");
        if (fptr == NULL)
        {
            //return FAILURE TO open File
            return FAILURE; 
        }
        //Declare word with character array of size 20
        char word1[20];
        //Declare index variable as int
        int index;
        //use fscanf to scan the open file from linked list until inside pointer reaches end
        while (fscanf(fptr, "%s", word1) != EOF)
        {
            //Find the index to store word1 by using first character
            index = word1[0] % 97;
            //create a temporary pointer to traverse all the mainnodes
            main_node *temp1 = HT[index].link;
            //create another temporary pointer that can hold previous mainnode  link
            main_node *prev = NULL;
            //Declare word_found as int variable with intialization=0
            int word_found = 0;

            // Traverse all the mainnodes
            while (temp1 != NULL)
            {
                //compare words in file,with word that is scaned by scanf function
                if (strcmp(temp1->word, word1) == 0)
                {
                    //words are matched ,initalize word_found=1
                    word_found = 1;
                    break; 
                }
                //update prev to mainnode
                prev = temp1;
                //move the temp pointer to next mainnode
                temp1 = temp1->main_node_link;
            }
            //if word_found=1 here its true
            if (word_found)
            {
                //create a temporary pointer that to traversa all the sub_nodes
                sub_node *temp2 = temp1->sub_node_link;
                //create another pointe prev to store prvoius of temp2 link
                sub_node *prev_sub = NULL;
                //intialize file_found=0,to check word is find in same file or not
                int file_found = 0;
                //run while loop until sub_nod_link reaches NULL
                while (temp2 != NULL)
                {
                    //if word found is in same file
                    if (strcmp(temp2->file_name, temp->array) == 0)
                    {
                        //Increment the word count
                        temp2->word_count++; 
                        //file found intialize to 1
                        file_found = 1;
                        break;
                    }
                    //update prev sub to temp2
                    prev_sub = temp2;
                    //upate temp2 to temp2->subnode_link
                    temp2 = temp2->subnode_link;
                }
                //check file found or not
                //if file not found enter the if loop
                if (!file_found)
                {
                    //Allocate memory for newsubnode
                    sub_node *new_subnode = malloc(sizeof(sub_node));
                    //check if new_sunode is created or not
                    if (new_subnode == NULL)
                    {
                        //if new_subnode not created close the pointer and return FAIURE
                        fclose(fptr);
                        return FAILURE; 
                    }
                    //if subnode is created copy the file name to new_subnode file name
                    strcpy(new_subnode->file_name, temp->array);
                    //increment the file count in main_node
                    temp1->filecount++;
                    //Initialize the word_count =1 in new_subnode word_count
                    new_subnode->word_count = 1;
                    //and also new_subnode->link to NULL
                    new_subnode->subnode_link = NULL;

                    //if prev_sub not equal to NULL connect the new_subnode to prev_sub link
                    if (prev_sub != NULL)
                    {
                        prev_sub->subnode_link = new_subnode;
                    }
                    else
                    {
                        //if no prev_sub link connect the new_subnode to main_node sub_link
                        temp1->sub_node_link = new_subnode;
                    }
                }
            }
            //no word found and no file found else case will be executed
            else
            {
               //Allocate memory for new mainnode
                main_node *new_mainnode = malloc(sizeof(main_node));
                //Allocate memory for new subnode
                sub_node *new_subnode = malloc(sizeof(sub_node));
                //check for memory allocation
                if (new_mainnode == NULL || new_subnode == NULL)
                {
                    //If memory not allocated return FAILURE
                    fclose(fptr);
                    return FAILURE; 
                }

              //copy word1 to new_mainnode->word
                strcpy(new_mainnode->word, word1);
                //Initialize the new_mainnode->file count=1;
                new_mainnode->filecount = 1;
                //new_mainnode->main_node_link=NULL;
                new_mainnode->main_node_link = NULL;
                //new_mainnode->sub_node_link connect to new_subnode
                new_mainnode->sub_node_link = new_subnode;

                //copy the file name of fptr to the new_subnode->file name
                strcpy(new_subnode->file_name, temp->array);
                //Intialize the word_count=1
                new_subnode->word_count = 1;
                //its new_subnode link to NULL
                new_subnode->subnode_link = NULL;

              //check if hash index link ==NULL
                if (HT[index].link == NULL)
                {
                    //condition true attach HT[index].link to new_mainnode
                    HT[index].link = new_mainnode; 
                }
                else
                {
                    //else prev->main_node_link to new_mainnode
                    prev->main_node_link = new_mainnode; 
                }
            }
        }
        //close the file pointer fptr
        fclose(fptr); 
        //move mainnode to next mainnode
        temp = temp->link;
    }
    //return SUCCESS;
    return SUCCESS;
}
