/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

#include "dictionary.h"

unsigned int count = 0;

node* root;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* trav;
    trav = root;
    int check = 0;
    for (int i = 0, word_len = strlen(word); i < word_len; i++)
    {
        if (word[i] != '\'')
        {
            int c = tolower(word[i]);
            if (trav->children[c-'a'] != NULL)
            {
                trav = trav->children[c-'a'];
            }
            else
            {
                check = 0;
                break;
            }
            if (trav->is_word == true && i == word_len-1)
            {
                check = 1;
                break;
            }
        }
        else
        {
            if(trav->children[26] != NULL)
            {
                trav = trav->children[26];
            }
            else
            {
                check = 0;
                break;
            }
            if (trav->is_word == true && i == word_len-1)
            {
                check = 1;
                break;
            }
        }
    }
    if (check == 1)
        return true;
    else
        return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        return false;
    }
    else
    {
        root = malloc(sizeof(node));
        node* new_node, *trav;
        trav = root;
        for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
        {
            if (c == '\n')
            {
                    trav->is_word = true;
                    count++;
                    trav = root;
            }
            else if (c != '\'')
            {
                if (trav->children[c-'a'] == NULL)
                {
                    new_node = malloc(sizeof(node));
                    trav->children[c-'a'] = new_node;
                    trav = new_node;
                }
                else
                {
                    trav = trav->children[c-'a'];
                }
                if(trav->is_word!=true)
                    trav->is_word = false;
            }
            else
            {
                if (trav->children[26] == NULL)
                {
                    new_node = malloc(sizeof(node));
                    trav->children[26] = new_node;
                    trav = new_node;
                }
                else
                {
                    trav = trav->children[26];
                }
                if(trav->is_word!=true)
                    trav->is_word = false;
            }
        }
    fclose(fp);
    return true;
    }
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    freeTrie(root);
    return true;
    
}
void freeTrie(node* trav)
{
    for (int i = 0; i < 27; i++)
    {
        if(trav->children[i] != NULL)
        {
            freeTrie(trav->children[i]);
        }
    }
    free(trav);
}
