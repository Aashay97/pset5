/**
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

//to count no. of words;
unsigned int count=0;

//define basic structure for a trie 
typedef struct node
{
    bool end;
    struct node* children[27];
}
node;
typedef node* link;

//declare additional functions
void freenodes(link curr);
link create(link newnode);

//global variable root of the trie
link root=&(node){false,{NULL}};

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int n=strlen(word),i,ch;
    link temp=root;     //to traverse the trie
    
    //traverse through the trie till the end of the word
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
    
    //check the boolean
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
bool load(const char *dictionary)
{
    //open dictionary in the read mode
    FILE *fp=fopen(dictionary,"r");
    
    if(fp==NULL)
    {
        printf("Couldn't open file\n");
        return false;
    }
    
    unsigned int ch=fgetc(fp);
    link temp=root;     //variable to traverse the list
    
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
            
            //only create a new node if it doesn't exist before
            if(temp->children[ch]==NULL)
            {
                link next=NULL;
                next=create(next);
                temp->children[ch]=next;    //link the new node
                temp=next;                  
            }
            
            else
            {
                temp=temp->children[ch];
            }
        }
        
        else
        {
            temp->end=true;     //if the word has ended,make the boolean true.
            temp=root;          //go back to the beginning of the trie
            count++;            //counts number of words loaded
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
    return count;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // root has not been allocated heap memory so one can only free its children and not root itself
    int i;
    for(i=0;i<27;i++)
    {
        if(root->children[i]!=NULL)
        {
            freenodes(root->children[i]);
        }
    }
    return true;
}

//function to initialize a new node 
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

//function to recursively free a node and its children
void freenodes(link curr)
{
    int i;
    for(i=0;i<27;i++)
    {
        if(curr->children[i]!=NULL)
        {
            freenodes(curr->children[i]);
        }
    }
    free(curr);
}