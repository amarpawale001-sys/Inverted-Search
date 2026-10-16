#include "sll.h"

int save_db(hash_t *arr)
{
    // Check whether database is empty or not
    int count = 0;

    for(int i = 0; i < 28; i++)
    {
        if(arr[i].m_link != NULL)
        {
            count++;
            break;
        }
    }

    if(count == 0)
    {
        printf("ERROR: Database is empty. Save_DB is not possible.\n");
        return FAILURE;
    }

    // Read file name from user
    char str[20];

    printf("Enter file name: ");
    scanf("%19s", str);

    // Validate file name
    if(strstr(str, ".txt") == NULL)
    {
        printf("ERROR: Invalid Filename, It should contain .txt\n");
        return FAILURE;
    }

    // Open file in write mode
    FILE *fptr = fopen(str, "w");

    if(fptr == NULL)
    {
        printf("ERROR: File open failed\n");
        return FAILURE;
    }

    // Traverse through hash table
    for(int i = 0; i < 28; i++)
    {
        if(arr[i].m_link != NULL)
        {
            // Traverse main nodes
            m_node *mtemp = arr[i].m_link;

            while(mtemp)
            {
                // Store index, word and file count
                fprintf(fptr, "#%d;%s;%d;",
                        i,
                        mtemp->word,
                        mtemp->f_count);

                // Traverse sub nodes
                s_node *stemp = mtemp->s_link;

                while(stemp)
                {
                    // Store file name and word count
                    fprintf(fptr, "%s;%d;",
                            stemp->filename,
                            stemp->w_count);

                    stemp = stemp->s_link;
                }

                // Mark the end of current main node
                fprintf(fptr, "#\n");

                // Move to next main node
                mtemp = mtemp->m_link;
            }
        }
    }

    // Close the file
    fclose(fptr);

    printf("Save DataBase Successful!\n");

    return SUCCESS;
}