#include "main.h"
int SaveDatabase(hash_t *HT,int size)
{
    // Declare character array to store the file name
    char fname[50];
    printf("Enter the file name:");
    // Read file name from user input
    scanf("%s",fname);
    // Check if the file name has ".txt" extension
    char *str=strstr(fname,".txt");
    // Length of extension to validate
    int len=strlen(str);
    // Open file in write mode
    FILE *fptr=fopen(fname,"w");
    // Check if file opened successfully
    if(fptr==NULL)
    {
        return FAILURE;
    }
     // Proceed if file name is valid and has ".txt" extension
    if(len==4 && len!=0)
    {
         // Loop through each index in the hash table
        for(int i=0;i<size;i++)
        {
            // Pointer to traverse main nodes
            main_node *temp=HT[i].link;
            // Traverse through main nodes in linked list
            while(temp!=0)
            {
                 // Write main node data to file
                fprintf(fptr,"#[%d];%s;%d;",i,temp->word,temp->filecount);
                // Pointer to traverse sub nodes
                sub_node *temp1=temp->sub_node_link;
                // Traverse through sub nodes in linked list
                while(temp1!=0)
                {
                    // Write sub node data to file
                    fprintf(fptr,"%s;%d#",temp1->file_name,temp1->word_count);
                    // Move to the next sub node
                    temp1=temp1->subnode_link;
                }
                // Move to the next main node
                temp=temp->main_node_link;
                // Newline for each main node entry
                fprintf(fptr,"\n");
            }
        }
        // Close the file after writing
        fclose(fptr);
    }
    // Return success status
    return SUCCESS;
}
