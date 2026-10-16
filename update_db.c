#include "sll.h"

int update_db(hash_t *arr)
{
    // Check whether database already contains data 

    int count = 0;

    for(int i = 0; i < 28; i++)
    {
        if(arr[i].m_link != NULL)
        {
            count++;
            break;
        }
    }

    // If database already contains data, don't update
    if(count != 0)
    {
        printf("Database already contains data. Update not allowed!\n\n");
        return FAILURE;
    }

    char str[30];

    // Read backup file name
    printf("Enter the backup file name: ");
    scanf("%29s", str);

    // Validate file name
    if(strstr(str, ".txt") == NULL)
    {
        printf("Invalid file name. File type should be .txt\n");
        return FAILURE;
    }

    // Open backup file
    FILE *fptr = fopen(str, "r");

    if(fptr == NULL)
    {
        printf("Unable to open backup file\n");
        return FAILURE;
    }

    // Check first character
    char ch;

    fscanf(fptr, "%c", &ch);

    if(ch != '#')
    {
        printf("Invalid backup file\n");
        fclose(fptr);
        return FAILURE;
    }

    // Check last character
    fseek(fptr, -2, SEEK_END);
    fscanf(fptr, "%c", &ch);

    if(ch != '#')
    {
       printf("Invalid backup file\n");
       fclose(fptr);
       return FAILURE;
    }

    // Move file pointer back to beginning
    rewind(fptr);

    int index;
    int file_count;
    char word[30];

    // Read each main node from backup file
   while(fscanf(fptr, "#%d;%29[^;];%d;",&index, word, &file_count) == 3)
    {
        if(index < 0 || index >= 28 || file_count <= 0)
         { 
          printf("Invalid backup file\n");
          fclose(fptr);
          return FAILURE;
        }
        // Create main node
        m_node *mnew = malloc(sizeof(m_node));

        if(mnew == NULL)
        {
            printf("Memory allocation failed\n");
            fclose(fptr);
            return FAILURE;
        }

        // Fill main node
        strcpy(mnew->word, word);
        mnew->f_count = file_count;
        mnew->m_link = NULL;
        mnew->s_link = NULL;

        // Create sub nodes
        s_node *sprev = NULL;

        for(int i = 0; i < file_count; i++)
        {
            char fname[30];
            int word_count;

            // Read file name and word count
          if(fscanf(fptr, "%29[^;];%d;",fname, &word_count) != 2)
            {
                printf("Invalid backup file\n");
                fclose(fptr);
                return FAILURE;
            }
            if(word_count <= 0)
             {
               printf("Invalid backup file\n");
               fclose(fptr);
               return FAILURE;
             }

            // Create sub node
            s_node *snew = malloc(sizeof(s_node));

            if(snew == NULL)
            {
                printf("Memory allocation failed\n");
                fclose(fptr);
                return FAILURE;
            }

            // Fill sub node
            strcpy(snew->filename, fname);
            snew->w_count = word_count;
            snew->s_link = NULL;

            // First sub node
            if(mnew->s_link == NULL)
            {
                mnew->s_link = snew;
            }
            else
            {
                sprev->s_link = snew;
            }

            sprev = snew;
        }

        // Read and discard '#' and newline
        fscanf(fptr, "%c", &ch);
        fscanf(fptr, "%c", &ch);

        // Insert main node into hash table
        if(arr[index].m_link == NULL)
        {
            arr[index].m_link = mnew;
        }
        else
        {
            m_node *temp = arr[index].m_link;

            while(temp->m_link != NULL)
            {
                temp = temp->m_link;
            }

            temp->m_link = mnew;
        }
    }

    fclose(fptr);

    printf("Update DataBase Successful!\n\n");

    return SUCCESS;
}