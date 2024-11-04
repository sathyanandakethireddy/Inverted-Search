#include "main.h"
int update_database(hash_t *HT, char *fname) 
{
    //create a file pointer for fname in read mode
    FILE *fptr = fopen(fname, "r");
    //check the file pointer contain null or not
    if (fptr == NULL) 
    {
        //if NULL file pointer doesnt created for file fname
        //print file coudnt open
        printf("file coudn't open\n");
        return FAILURE;
    }
    //create a char variable for storing first character of the pointer
    char ch = getc(fptr);
    //check char ch=='#' or not
    if (ch != '#') 
    {
        printf("Enter the valid file which contain #\n");
        fclose(fptr);
        return FAILURE;
    }

    char str[100];
    while (fscanf(fptr, "%s", str) != EOF) {
        // Use strtok to to get filename,filecount,word
        char *temp = strtok(str, "#;");
         // Extract index from the brackets
        int index = atoi(temp + 1); 
        //check for index out of bound or not
        if (index < 0 || index >= 27) 
        { 
            printf("Index is out of bound");
            fclose(fptr);
            return FAILURE;
        }
       //create a pointer to traverse through hash link
        main_node *temp_main = HT[index].link;
        //create a new main node 
        main_node *new_main = malloc(sizeof(main_node));
        //if new_main==NULL
        if (new_main == NULL) 
        {
            printf("Memory allocation failed\n");
            fclose(fptr);
            return FAILURE;
        }
        temp = strtok(NULL, ";");
        strcpy(new_main->word, temp);
        temp = strtok(NULL, ";");
        new_main->filecount = atoi(temp);
        new_main->sub_node_link = NULL;
        new_main->main_node_link = NULL;

        // create a pointer last_sub intially NULL ,to traverse through subnodes
        sub_node *last_sub = NULL;
        for (int i = 0; i < new_main->filecount; i++) 
        {
            sub_node *new_sub = malloc(sizeof(sub_node));
            if (new_sub == NULL) 
            {
                printf("Memory allocation failed for subnodes\n");
                free(new_main);
                fclose(fptr);
                return FAILURE;
            }
            temp = strtok(NULL, ";#");
            strcpy(new_sub->file_name, temp);
            temp = strtok(NULL, ";#");
            new_sub->word_count = atoi(temp);
            new_sub->subnode_link = NULL;
            // Link the subnodes
            if (last_sub == NULL) 
            {
                new_main->sub_node_link = new_sub;
            } 
            else 
            {
                last_sub->subnode_link = new_sub;
            }
            last_sub = new_sub;
        }

        // Link the main nodes
        if (temp_main == NULL) 
        {
            HT[index].link = new_main;
        } 
        else 
        {
            while (temp_main->main_node_link != NULL) 
            {
                temp_main = temp_main->main_node_link;
            }
            temp_main->main_node_link = new_main;
        }
    }

    fclose(fptr);
    return SUCCESS;
}
void RemoveDuplicate(hash_t *HT, Slist **head) 
{
    //Iterate through each index in hash table
    for (int i = 0; i < 27; i++) 
    { 
        main_node *current_main = HT[i].link;

        while (current_main != NULL) 
        {
            //for each mainnode iterate through all subnodes
            sub_node *current_sub = current_main->sub_node_link;
            
            //create temporary pointer to hold the address of the head
            Slist *temp_list = *head;
            Slist *prev = NULL;

           //iterate through linked list 
            while (temp_list != NULL) 
            {
                //initially found=0 for track the file name is present in hash table
                int found = 0;
                // Reset current_sub for each file in the linked list
                current_sub = current_main->sub_node_link; 

                while (current_sub != NULL) 
                {
                    if (strcmp(temp_list->array, current_sub->file_name) == 0) 
                    {
                        found = 1; 
                        break; 
                    }
                    // Move to the next sub_node
                    current_sub = current_sub->subnode_link; 
                }

                if (found) 
                {
                    // Remove temp_list from the linked list
                    if (prev == NULL) 
                    {
                        //update the linked list
                        *head = temp_list->link; 
                    } 
                    else
                    {
                        prev->link = temp_list->link; 
                    }
                    Slist *to_delete = temp_list; 
                    temp_list = temp_list->link; 
                    // Free memory of the removed node
                    free(to_delete); 
                }
                else 
                {
                    // Move to the next node
                    prev = temp_list; 
                    // Move to the next node
                    temp_list = temp_list->link; 
                }
            }
            // Move to the next main_node
            current_main = current_main->main_node_link; 
        }
    }
    print_list(*head);
}
