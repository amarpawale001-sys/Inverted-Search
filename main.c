/*
Name: Amarnath Pawale

Batch: 26005B_029

Project Name: Inverted Search

Description:

The Inverted Search project is implemented in C. 
It is used to search for a word in multiple text files and find out which files contain the word and how many times it appears.
In this project, I used hashing and linked lists to store the file and word information. 
The input files are given through command-line arguments. 
The program first checks the files and then creates a database.
The project is menu-driven and provides options like Create Database, Display Database, Search Database, Save Database, Update Database, and Exit.
 The database can also be saved in a backup file and updated later using the backup file.
*/

#include "sll.h"

int main(int argc,char *argv[])
{
    Slist_t *file_head = NULL;

    hash_t arr[28] = {0};
    create_HT(arr,28);
     
    if(argc == 1)
    {
        printf("Error: No files are passed\n");
        return FAILURE;
    }

    read_validate(argv,&file_head);

    int choice;
    do
    {
        printf("-----MENU-----\n");
        printf("1.Create DataBase\n2.Display DataBase\n3.Search DataBase\n4.Save DataBase\n5.Update DataBase\n6.Exit\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            if(create_db(&file_head,arr)==FAILURE)
            {
                printf("ERROR: Create DataBase Failed\n");
            }
            break;

            case 2:
            if(display_db(arr) == FAILURE)
            {
                printf("ERROR: Display DataBase Failed\n");
            }
            break;

            case 3:
            if(search_db(arr) == FAILURE)
            {
                printf("ERROR: Search DataBase Failed\n");
            }
            break;

            case 4:
            if(save_db(arr) == FAILURE)
            {
                printf("ERROR: Save DataBase Failed\n");
            }
            break;

            case 5:
            if(update_db(arr) == FAILURE)
            {
                printf("ERROR: Update DataBase Failed\n");
            }
            break;

        }
    }while(choice != 6);

    return SUCCESS;
}