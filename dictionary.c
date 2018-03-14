/**
 * Implements a dictionary's functionality.
 */

#include <ctype.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    bool is_word;
   struct node *dict[27];
}node;

node *root=NULL;
node *trav=NULL;
int c=0;
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    node *trav2=root;
    int i,x;
    char w[50];
        for(i=0;word[i]!='\0';i++)
        w[i]=tolower(word[i]);
        w[i]='\0';
    for(i=0;w[i]!='\0';i++)
    {
        if(isalpha(w[i]))
        x=w[i]-97;
        else
        x=26;
        if(trav2->dict[x]!=NULL)
        {
            trav2=trav2->dict[x];
            if(w[i+1]=='\0')
            {
                if(trav2->is_word==true)
                break;
                else 
                return false;
            }
        }
        else
        return false;
    }
    return true;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    root=(node*)malloc(sizeof(node));
    if(root==NULL)
    return false;
    node *trav3=root;
    trav=root;
    char x;
    int n;
    FILE *file=fopen(dictionary,"r");
    if(file==NULL)
    return false;
    while(!feof(file))
    {
        x=fgetc(file);
        if(isalpha(x))
        n=x-97;
        else if(x=='\'')
        n=26;
        if(x=='\n')
        {
        trav3->is_word=true;
        trav3=root;
        }
        else if(trav3->dict[n]==NULL)
        {
            trav3->dict[n]=(node*)malloc(sizeof(node));
            if(trav3->dict[n]==NULL)
            {
            printf("Error \n");
            return false;
            }
            trav3=trav3->dict[n];
        }
        else 
        trav3=trav3->dict[n];
    }
    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    node *trav3=NULL;
    int arr[27];
    int d=0;
    for(int i=0;i<27;i++)
    {
        if(trav->dict[i]!=NULL)
        {
            arr[d]=i;
            d++;
        }
    }
        if(trav->is_word==true)
        c++;
        for(int j=0;j<d;j++)
        {
            trav3=trav;
            trav=trav->dict[(arr[j])];
            size();
            trav=trav3;
        }
    return c;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    node *trav1=NULL;
   int c1=0;
    int arr[27];
    int d=0;
    for(int i=0;i<27;i++)
    {
        if(trav->dict[i]==NULL)
        c1++;
        else
        {
            arr[d]=i;
            d++;
        }
    }
        for(int j=0;j<d;j++)
        {
            trav1=trav;
            trav=trav->dict[(arr[j])];
            unload();
            trav1->dict[(arr[j])]=NULL;
            c1++;
            trav=trav1;
        }
    if(c1==27)
    free(trav);
    return true;
}
