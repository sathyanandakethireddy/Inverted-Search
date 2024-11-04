#include "main.h"

int Read_Validate(char *argv[], Slist **head)
{
    FILE *fptr;
    for (int i = 1; argv[i] != NULL; i++) 
    {
        // Check for ".txt" extension
        char *str=strstr(argv[i],".txt");
        if (strlen(str)>4 && strlen(str)==0) 
        {
            printf("Error: Command line arguments must have .txt extension (%s)\n", argv[i]);
            return FAILURE;
        }

        // Try to open the file
        fptr = fopen(argv[i], "r");
        if (fptr == NULL)
        {
            printf("Error: File %s is not present in the directory\n", argv[i]);
            continue;
        }

        // Check if the file is empty
        if (getc(fptr) == EOF)
        {
            printf("Error: File %s is empty\n", argv[i]);
            fclose(fptr);
            continue;
        }
        fclose(fptr);

        // Check for duplicate filenames
        int flag=0;
        for(int j=1;j<i;j++)
        {
            if(strcmp(argv[j],argv[i])==0)
            {
                printf("%s duplicate files are:\n",argv[j]);
                flag=1;
                continue;
            }
        }

        // Insert filename into the linked list
        if(flag==0)
        {
            insert_at_last(head, argv[i]);
        }
    }

    return SUCCESS;
}
