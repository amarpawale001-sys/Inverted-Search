#include "sll.h"

void read_validate(char *argv[],Slist_t **head)
{
    int i = 1;
    while(argv[i])
    {
        if(strstr(argv[i],".txt") == NULL)
        {
            printf("Invalid file type %s \n",argv[i]);
            i++;
            continue;
        }

         //check whether file exits or not
        FILE *fptr = fopen(argv[i],"r");
        if(fptr == NULL) 
         {
            printf("%s file does not exits \n",argv[i]);
            i++;
            continue;
         }

        //check if file is not empty
        fseek(fptr,0,SEEK_END);
        int size = ftell(fptr);
        if(size == 0)
        {
             printf("%s File is empty\n",argv[i]);
             fclose(fptr);
             i++;
             continue;
        }
        fclose(fptr);
        
        //check if file is repeated or not and store in Slist
        if(*head == NULL) //list is empty
        {
            insert_last(head,argv[i]);
            i++;
            continue;
        }
        else
        {
            int flag = 0;
            Slist_t *temp = *head;
            while(temp != NULL)
            {
                if(strcmp(temp->file,argv[i]) == 0 )
                {
                    flag = 1;
                    break;
                }
                temp = temp->link;
            }
            if(flag == 0)
            {
                insert_last(head,argv[i]);
            }
            else
            {
                  printf("%s file is repeated\n", argv[i]);
            }
            i++;
        }
    }

    if(*head == NULL)
    {
    printf("ERROR: No valid files available.\n");
    return;
    }

    printf("List of File Names\n");
    print_list(*head);
    printf("Read and Validated Successfully\n");
}

void print_list(Slist_t *head)
{
    if(head == NULL)
    {
        printf("INFO: List is Empty\n");
    }
    else
    {
        while(head)
        {
            printf("%s-> ",head->file); //pass by vaule, so no temp or ptr required
            head = head->link;
        }
        printf("NULL\n");
    }
}

int insert_last(Slist_t **head,char *file)
{
    Slist_t *new = malloc(sizeof(Slist_t));
    if(new == NULL)
    {
        printf("Memory allocation failed\n");
        return FAILURE;
    }
    strcpy(new->file,file);

    new->link = NULL;

    if(*head == NULL)
    {
        *head = new;
    }
    else
    {
        Slist_t *temp = *head;
        while(temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = new;
    }
    return SUCCESS;
}