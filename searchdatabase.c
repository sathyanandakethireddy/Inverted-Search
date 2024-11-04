#include "main.h"
//Fuction to search for word in hash_table
int search_database(hash_t *HT)
{
  //Declare a string to hold a word
   char str[50];
   printf("Enter the string:");
   //Read the input word
   scanf(" %s",str);
   //calculate the index of word based on first character of the word
   int index=str[0]%97;
   //check if there is linked list at the calculated index
   if(HT[index].link!=NULL)
   {
     //temporary pointer to traverse the mainnode at this index
      main_node *temp=HT[index].link;
      //Traverse all the mainnodes at this index
      while(temp!=0)
      {
        //compare current word with input word
        if(strcmp(temp->word,str)==0)
        {
          //print the details of word found
            printf("WORD:%s FILECOUNT:%d\n",temp->word,temp->filecount);
            //Temporary pointer to travers the sub_node
            sub_node *temp1=temp->sub_node_link;
            //Traverse all the subnode of current mainnode
            while(temp1!=0)
            {
              //print the word count and file name for each subnode
                printf("WORDCOUNT:%d FILENAME:%s\n",temp1->word_count,temp1->file_name);
                //move to the next subnode
                temp1=temp1->subnode_link;
            }
            //return SUCCESS if the word found
            return SUCCESS;
        }
        //move to the next main_node
        temp=temp->main_node_link;
      }
   }
   //if word not found return FAILURE
   return FAILURE;
}
