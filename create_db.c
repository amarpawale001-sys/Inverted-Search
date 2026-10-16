#include "sll.h"

// Check whether file is already present in database
int check_file_in_db(hash_t arr[], char *temp)
{
    // Traverse all 28 indexes
    for(int i = 0; i < 28; i++)
    {
        // Take main node
        m_node *mtemp = arr[i].m_link;

        // Traverse all main nodes
        while(mtemp)
        {
            // Take sub node
            s_node *stemp = mtemp->s_link;

            // Traverse all sub nodes
            while(stemp)
            {
                // Check whether file name is already present
                if(strcmp(stemp->filename, temp) == 0)
                {
                    return SUCCESS;
                }

                stemp = stemp->s_link;
            }

            mtemp = mtemp->m_link;
        }
    }

    return FAILURE;
}

int create_db(Slist_t **file_head,hash_t *arr)
{
  //Check if file name list is empty
    if(*file_head == NULL)
    {
        printf("ERROR: No valid files available. Create_DB not possible.\n");
        return FAILURE;
    }

    //Take first file
    Slist_t *temp = *file_head;

    //Declare word to read from file
    char word[20];

    //Traverse all command line files
    while(temp)
    {
        //Check whether current file is already present in database
        if(check_file_in_db(arr, temp->file) == SUCCESS)
        {
            printf("INFO: %s is already present in database. Skipping...\n", temp->file);

            temp = temp->link;
            continue;
        }

        //Current file is a new file
        printf("INFO: %s is a new file. Adding to database...\n", temp->file);

        //Open file in read mode
        FILE *fptr = fopen(temp->file, "r");

        //Validate file opening
        if(fptr == NULL)
        {
            printf("ERROR: Unable to open %s\n", temp->file);

            temp = temp->link;
            continue;
        }

        //Read each word from file
        while(fscanf(fptr, "%19s", word) == 1)
        {
           //Find index using first character
            int ind;
            if(isalpha(word[0]))
            {
              ind = tolower(word[0]) - 'a';
            }
            else if(isdigit(word[0]))
            {
             ind = 26;
            }
            else
            {
             ind = 27;
            }    

    //Case 1: Index is Empty
    if(arr[ind].m_link == NULL)
    {
        //create main node
        m_node* mnew = malloc(sizeof(m_node));
        if(mnew == NULL)
        {
            fclose(fptr);
            return FAILURE;
        }

        //update main node
        strcpy(mnew->word,word);
        mnew->f_count = 1;
        mnew->m_link = NULL;
        mnew->s_link = NULL;
        
        //create subnode
        s_node *snew = malloc(sizeof(s_node));
        if(snew == NULL)
        {
            free(mnew);
            fclose(fptr);
            return FAILURE;
        }
        strcpy(snew->filename, temp->file);
        snew->w_count = 1;
        snew->s_link = NULL; 
        
        //Link mainnode to subnode
        mnew->s_link = snew;

        //store mainode address in array
        arr[ind].m_link = mnew;
    }
     
    //case 2: Index already contains mainodes
    else
    {
        //Take mainnode and traverse
        m_node *mtemp = arr[ind].m_link;

        m_node *mprev = NULL;

        //search for word
        while(mtemp)
        {
            if(strcmp(mtemp->word,word) == 0)
            {
                break;
            }
            mprev = mtemp;
            mtemp = mtemp->m_link;
        }
            //case 2a: Word does not exit
            if(mtemp == NULL)
            {
                //create new mainode
                m_node *mnew = malloc(sizeof(m_node));
                if(mnew == NULL)
                {
                    fclose(fptr);
                    return FAILURE;
                }
                strcpy(mnew->word,word);
                mnew->f_count = 1;
                mnew->m_link = NULL;
                mnew->s_link = NULL;

                //create subnode
                s_node *snew = malloc(sizeof(s_node));
                if(snew == NULL)
                {
                    free(mnew);
                    fclose(fptr);
                    return FAILURE;
                }

                //Update subnode
                snew->w_count = 1;
                strcpy(snew->filename,temp->file);
                snew->s_link = NULL;

                 //Link mainnode to subnode
                 mnew->s_link = snew;

                 //Link new mainnode to previous mainnode
                 mprev->m_link = mnew;
            }

            //Case 2B: Word already exists
            else
            {
                // Take subnode
                s_node *stemp = mtemp->s_link;

                s_node *sprev = NULL;

                //Search for current file in subnodes
                while(stemp)
                {
                    if(strcmp(stemp->filename,temp->file) == 0)
                    {
                        break;
                    }
                    sprev = stemp;
                    stemp = stemp->s_link;
                }
                //File already exists for this word
                if(stemp != NULL)
                {
                      //Increment word count
                    stemp->w_count++;
                }

                //File does not exist for this word
                else
                {
                    //Create new subnode
                    s_node *snew = malloc(sizeof(s_node));
                    if(snew == NULL)
                    {
                        fclose(fptr);
                        return FAILURE;
                    }

                        //Update subnode
                        snew->w_count = 1;
                        strcpy(snew->filename,temp->file);
                        snew->s_link = NULL;

                         //Link new subnode
                        sprev->s_link = snew;

                         //Increase file count
                           mtemp->f_count++;
                }
            }
        }
    }
    // Close current file
         fclose(fptr);

    // Move to next file
    temp = temp->link;
}
    printf("\n");
    printf("Create DataBase Successful!\n");
    printf("\n");

    return SUCCESS;
}






     

  