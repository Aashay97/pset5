/**
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

unsigned int count=0;


typedef struct node
{
    bool end;
    struct node* children[27];
}
node;
typedef node* link;

void freenodes(link curr);

link root=&(node){false,{NULL}};

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    int n=strlen(word),i,ch;
    link temp=root;
    
    for(i=0;i<n;i++)
    {
        if(isalpha(word[i])||word[i]=='\'')
        {
            if(word[i]=='\'')
            {
                ch=26;
            }
            
            else
            {
                ch=tolower(word[i])-97;
            }
            temp=temp->children[ch];
            if(temp==NULL)
            {
                return false; 
            }
            
        }
        
        else
        {
            return false;
        }
    }
    if(temp->end==true)
    {
        return true;
    }
    
    else
    {
    return false;
    }
    
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
    newnode->end=false;
    return newnode;
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
                link next=NULL;
                next=create(next);
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
            count++;
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
    return count;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    int i;
    freenodes(root);
    return true;
}

void freenodes(link curr)
{
    int i;
    for(i=0;i<27;i++)
    {
        if(curr->children[i]!=NULL)
        {
            freenodes(curr->children[i]);
        }
        else
        {
            return;
        }
    }
    free(curr);
}