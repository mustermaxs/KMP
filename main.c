#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// bla

struct node
{
    int index;
    struct node *next;
} typedef node;

node *getLastNode(node *head)
{
    if (head == NULL)
        return head;

    while (head->next != NULL)
    {
        head = head->next;
    }

    return head;
}
node *appendNode(node *head, node *newNode)
{
    node *lastNode;

    if (head == NULL)
        return newNode;

    lastNode = getLastNode(head);

    lastNode->next = newNode;
    newNode->next = NULL;

    return head;
}

void printNodes(node *head)
{
    while (head != NULL)
    {
        printf("\nmatch at: %d", head->index);
        head = head->next;
    }
}

int *createPrefixList(char *pattern);
void findMatches(char *string, char *pattern, int *prefixList);
void printPrefixList(int *list, int length)
{
    for (int index = 0; index < length; index++)
        printf("%d ", list[index]);
}

node *createNodeFromValue(int value)
{
    node *newNode = (node *)calloc(1, sizeof(node));

    newNode->index = value;
    newNode->next = NULL;

    return newNode;
}

int main()
{
    node *matches;
    char startNewSearch = 'y';

    while (startNewSearch != 'n')
    {
        char pattern[10000];
        char string[20000];

        printf("\nText: ");
        scanf(" %[^\n]s", string);
        printf("\nSuchwort: ");
        scanf(" %[^\n]s", pattern);

        int *prefixList = createPrefixList(pattern);

        findMatches(string, pattern, prefixList);
        // printNodes(matches);

        printf("\nNew search? (y/n): ");
        scanf(" %c", &startNewSearch);
    }

    return 0;
}

void findMatches(char *string, char *pattern, int *prefixList)
{
    int indexStr = 0;
    int indexPattern = 0;
    int lengthPattern = strlen(pattern);
    int lengthString = strlen(string);
    int matchIndex = 0;
    node *matchesHead = (node *)calloc(1, sizeof(node));
    matchesHead = NULL;

    while (string[indexStr] != '\0' && indexStr < lengthString)
    {
        matchIndex = indexStr;
        if (indexStr >= lengthString)
            break;
        while (string[indexStr] == pattern[indexPattern] && indexStr < lengthString)
        {
            if (indexPattern == lengthPattern - 1)
            {
                // matchesHead = appendNode(matchesHead, createNodeFromValue(matchIndex));
                printf("\nmatch at: %d", matchIndex);
                break;
            }

            ++indexStr;
            ++indexPattern;
        }

        if (indexStr >= lengthString)
            break;

        indexStr += prefixList[indexPattern] + 1;
        indexPattern = 0;
    }

    // return matchesHead;
}

int *createPrefixList(char *pattern)
{
    int patternLength = strlen(pattern);
    int *prefixList = (int *)calloc(patternLength - 1, sizeof(int));
    int i = 0, j = 1, prefixLength = 0;

    while (i < patternLength)
    {
        if (pattern[j] == pattern[i])
        {
            ++prefixLength;
            i++;
            j++;
            prefixList[i] = prefixLength;
        }
        else
        {
            prefixList[i] = prefixLength;
            prefixLength = 0;
            j = 0;
            ++i;
        }
    }

    return prefixList;
}