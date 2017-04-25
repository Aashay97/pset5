/**
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

typedef struct node
{
    bool end;
    struct node* children[27];
}
node;
typedef node* link;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
 
link create(link newnode)
{
    newnode=(link)malloc(sizeof(node));
    int i;
    for(i=0;i<27;i++)
    {
        newnode->children[i]=NULL;
    }
    new->end=false;
}

bool load(const char *dictionary)
{
    // TODO
    
    FILE *fp=fopen(dictionary,"r");
    
    if(fp==NULL)
    {
        printf("Couldn't open file\n");
        return false;
    }
    
    unsigned int ch=fgetc(fp);
    link root;
    root=create(root);
    link temp=root;
    
    while(ch!=EOF)
    {

        if(isalpha(ch)||ch=='\'')
        {
            if(ch=='\'')
            {
                ch=26;
            }
            
            else
            {
                ch=ch-97;
            }
            
            if(temp->children[ch]==NULL)
            {
                link next=create(next);
                temp->children[ch]=next;
                temp=next;
            }
            
            else
            {
                temp=temp->children[ch];
            }
        }
        
        else
        {
            temp->end=true;
            temp=root;
        }
        
        ch=fgetc(fp);
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
