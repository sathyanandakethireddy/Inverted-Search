#include "main.h"
int update_database(hash_t *HT, char *fname) 
{
    FILE *fptr = fopen(fname, "r");
    if (fptr == NULL) 
    {
        printf("file coudn't open\n");
        return FAILURE;
    }
    char ch = getc(fptr);
    if (ch != '#') 
    {
        printf("Enter the valid file which contain #\n");
        fclose(fptr);
        return FAILURE;
    }

    char str[100];
    while (fscanf(fptr, "%s", str) != EOF) {
        char *temp = strtok(str, "#;");
        int index = atoi(temp + 1); 
        if (index < 0 || index >= 27) 
        { 
            printf("Index is out of bound");
            fclose(fptr);
            return FAILURE;
        }
        main_node *temp_main = HT[index].link;
        main_node *new_main = malloc(sizeof(main_node));
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
    for (int i = 0; i < 27; i++) 
    { 
        main_node *current_main = HT[i].link;

        while (current_main != NULL) 
        {
            sub_node *current_sub = current_main->sub_node_link;
            Slist *temp_list = *head;
            Slist *prev = NULL;
            while (temp_list != NULL) 
            {
                int found = 0;
                current_sub = current_main->sub_node_link; 

                while (current_sub != NULL) 
                {
                    if (strcmp(temp_list->array, current_sub->file_name) == 0) 
                    {
                        found = 1; 
                        break; 
                    }
                    current_sub = current_sub->subnode_link; 
                }

                if (found) 
                {
                    if (prev == NULL) 
                    {
                        *head = temp_list->link; 
                    } 
                    else
                    {
                        prev->link = temp_list->link; 
                    }
                    Slist *to_delete = temp_list; 
                    temp_list = temp_list->link; 
                    free(to_delete); 
                }
                else 
                {
                    prev = temp_list; 
                    temp_list = temp_list->link; 
                }
            }
            current_main = current_main->main_node_link; 
        }
    }
    print_list(*head);
}
