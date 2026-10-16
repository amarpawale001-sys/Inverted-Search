#include "sll.h"

int display_db(hash_t arr[])
{
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
        printf("ERROR: Database is empty. Nothing to display.\n");
        return FAILURE;
    }

    printf("%-10s %-20s %-20s %-20s %-20s\n","Index", "Word", "FileCount", "FileName", "WordCount");

    printf("--------------------------------------------------------------------------------\n");

    for(int i = 0; i < 28; i++)
    {
        if(arr[i].m_link != NULL)
        {
            m_node *mtemp = arr[i].m_link;

            while(mtemp)
            {
                printf("%-10d %-20s %-20d ",i, mtemp->word, mtemp->f_count);

                s_node *stemp = mtemp->s_link;

                if(stemp != NULL)
                {
                    printf("%-20s %-20d",stemp->filename, stemp->w_count);

                    stemp = stemp->s_link;
                }

                while(stemp != NULL)
                {
                    printf("\n");
                    printf("%-10s %-20s %-20s %-20s %-20d","", "", "", stemp->filename, stemp->w_count);

                    stemp = stemp->s_link;
                }

                printf("\n");

                mtemp = mtemp->m_link;
            }
        }
    }

    printf("Display DataBase Successful!\n\n");

    return SUCCESS;
}