#include "sll.h"

int search_db(hash_t *arr)
{
    int count = 0;

    // Check whether database is empty
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
        printf("ERROR: Database is empty. Search_DB is not possible.\n");
        return FAILURE;
    }

    // Read word from user
    char word[20];

    printf("Enter the word to search: ");
    scanf("%19s", word);

    // Find index
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

    // Check whether index contains any main node
    if(arr[ind].m_link == NULL)
    {
        printf("Word does not exist in DB\n");
        return FAILURE;
    }

    // Traverse main nodes
    m_node *mtemp = arr[ind].m_link;

    while(mtemp)
    {
        if(strcmp(word, mtemp->word) == 0)
        {
            break;
        }

        mtemp = mtemp->m_link;
    }

    // Word not found
    if(mtemp == NULL)
    {
        printf("Word does not exist in DB\n");
        return FAILURE;
    }

    // Word found
    printf("\nWord '%s' is present in %d files\n",word, mtemp->f_count);

    // Traverse subnodes
    s_node *stemp = mtemp->s_link;

    while(stemp)
    {
        printf("%s -> %d\n",stemp->filename,stemp->w_count);

        stemp = stemp->s_link;
    }

    printf("\nSearch DB Successful!\n\n");

    return SUCCESS;
}
