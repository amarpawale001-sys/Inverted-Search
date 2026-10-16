#ifndef SLL_H
#define SLL_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define SUCCESS 0
#define FAILURE -1
#define DATA_NOT_FOUND 2

typedef struct node
{
    char file[30];
    struct node* link;
}Slist_t;

typedef struct mainode
{
    char word[30];
    int f_count;
    struct mainode *m_link;
    struct subnode *s_link;
    
}m_node;

typedef struct subnode
{
    char filename [30];
    int w_count;
    struct subnode *s_link;
}s_node;

typedef struct hash
{
    int index;
    m_node *m_link;
}hash_t;

void read_validate(char *argv[],Slist_t **head);
int create_db(Slist_t **file_head,hash_t *arr);
void create_HT(hash_t *HT, int size);
int display_db(hash_t *arr);
int search_db(hash_t *arr);
int save_db(hash_t *arr);
int update_db(hash_t *arr);
int insert_last(Slist_t **head,char* file);
void print_list(Slist_t *head);

#endif
