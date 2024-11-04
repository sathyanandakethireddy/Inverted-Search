#include "main.h"
//Function to insert new node at the end of linked list
int insert_at_last(Slist **head, char *str)
{
    //Allocate memory for new node
    Slist *new = (Slist *)malloc(sizeof(Slist));
    //check for memory allocation
    if (new == NULL)
    {
        //if memory not allocated return FAILURE
        return FAILURE;
    }
    //copy the input string to the newnode array
    strcpy(new->array, str);
    //set the newnode link to null at the end of list
    new->link = NULL;
   //check if list empty currently
    if (*head == NULL)
    {
        //make the new to head of the list if list is empty
        *head = new;
        //return SUCCESS;
        return SUCCESS;
    }
    //Temporary pointer to travers the list
    Slist *temp = *head;
    //travers to the last node
    while (temp->link != NULL)
    {
        //move to the next node
        temp = temp->link;
    }
    //update last node link 
    temp->link = new;
    //return success
    return SUCCESS;
}
//Function to intialize hash table with keys and links to NULL
void create_hashtable(hash_t *HT,int size)
{
    //Loop through each element in hash table
  for(int i=0;i<size;i++)
  {
    //assign each key in hash table to its index
     HT[i].key=i;
     //Ecah index link to NULL
     HT[i].link=NULL;
  }
}
//Functions to print the elements of a linkes list
void print_list(Slist *head)
{
    //check if list is empty
    if (head == NULL)
    {
        //print list is empty
        printf("INFO: List is empty\n");
    }
    else
    {
        //travese the list
        while (head)
        {
            //print each element in the node
            printf("%s -> ", head->array);
            //move to the next node
            head = head->link;
        }
        printf("NULL\n");
    }
}
