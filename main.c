#include "main.h"
int main(int argc, char *argv[]) 
{
    // Check if at least two file arguments are provided
    if (argc < 2) 
    { 
        printf("Enter more than one argument\n");
        return FAILURE;
    }

    Slist *head = NULL;

    // Validate and read files into linked list
    if (Read_Validate(argv, &head) == FAILURE) 
    {
        printf("Read_Validate failed.\n");
        return FAILURE;
    } 
    else 
    {
        printf("Read_Validate executed successfully.\n");
    }
    // Print the linked list contents
    print_list(head);

   // Define the hash table size and create the hash table
    int size = 28;
    hash_t HT[size];
    create_hashtable(HT, size);
    // Flag to check if database is created
    int flag=0;
    // Flag to check if database update is done
    int update=0;
// Menu loop for user interaction
    int choice;
    while (1) {
        // Display menu options
        printf("\nMenu:\n");
        if(flag==0)
        {
          printf("1. Create database\n");
        }
        printf("2. Display database\n");
        printf("3. Search database\n");
        printf("4. Save database\n");
        if(update==0)
        {
          printf("5. Update database\n");
        }
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); // Read user's choice

        switch (choice) {
            case 1: 
                // Create the database from the linked list
                if(flag==0)
                {
                    if (create_database(head, HT) == SUCCESS) 
                    {
                       printf("Created database successfully:\n");
                       flag=1;
                    }
                    else
                    {
                      printf("Failed to create database.\n");
                    }
                    

                }
                else
                {
                    printf("Already Created Database");
                }
                break;
            case 2:
                // Display the database
                printf("Displaying the Database:\n");
                display_database(HT, size);
                break;

            case 3: 
                // Search within the database
                if (search_database(HT) == FAILURE) { 
                    printf("Word NOT Found\n");
                }
                break;

            case 4:
                // Save the database to a file
                if (SaveDatabase(HT, size) == SUCCESS) {
                    printf("SaveDatabase successfully\n");
                } else {
                    printf("SaveDatabase not successful\n");
                }
                break;

            case 5:
                // Update entries in the database
                if(flag==0)
                {
                    char fname[50];
                    printf("Enter the backup file name:");
                    scanf( "%s",fname);
                    char *str=strstr(fname,".txt");
                    int len=strlen(str);
                    if(len==4 &&update==0)
                    {
                        if (update_database(HT,fname) == SUCCESS) 
                        {
                           printf("Update database successfully:\n");
                           RemoveDuplicate(HT,&head);
                           update=1;
                        } 
                        else 
                        {
                           printf("Update database not successful:\n");
                        }
                    }
                    else
                    {
                       printf("File name is not in .txt");
                    }
                }
                else
                {
                    printf("database created previously is done,can't update the database");
                }
                break;

            case 6:
                // Exit the program
                printf("Exiting the program.\n");
                exit(0);

            default:
                // Handle invalid choices
                printf("Invalid choice. Please try again.\n");
        }
    }


    return 0;
}
