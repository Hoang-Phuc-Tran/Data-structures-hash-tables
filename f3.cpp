/*
 * Project:	    Focused 3
 * Author:	    Hoang Phuc Tran
 * Student ID:  8789102
 * Date:		June 16, 2022
 * Description:  a program that stores words in a Hash Table and then searches for the words.
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996)


#define STRING_LENGTH 21
#define MAX_HASH 11


// Prototype
unsigned long hash(char* str);
unsigned long myHashFunction(char* str);
int insert(struct WordNode** head, char* str);
struct WordNode* findWord(struct WordNode* head, char* str);
void freeAll(WordNode* head);


 // Define a struct called WordNode
struct WordNode {
	char name[STRING_LENGTH];
	struct WordNode* next;
};



int main()
{
	// The hash table will be an array of 11 pointers to a struct called WordNode
	struct WordNode *hashTable[MAX_HASH];
	
	int j = 0;
	int i = 0;
	int compare = 1;
	int search = 1;

	// Use loop to assign NULL to 11 pointers
	for (i = 0; i < MAX_HASH; i++)
	{
		hashTable[i] = NULL;
	}

	// Check if user inputs '.' character
	while(compare)
	{
		int returnValue = 0;
		unsigned long numberHash = 0;
		char inputName[STRING_LENGTH] = { 0 };

		printf("Please enter a word no more than 20 characters long\n");
		fgets(inputName, sizeof(inputName), stdin);

		// Get rid of newline character
		inputName[strcspn(inputName, "\n")] = '\0';

		compare = strcmp(inputName, ".");

		// If user does not input '.' character
		if (compare != 0) 
		{
			// Call myHashFunction and assign its return value to numberHash variable
			numberHash = myHashFunction(inputName);

			returnValue = insert(&hashTable[numberHash], inputName);

			// Check if the allocation of newBlock runs out of memnory
			if (returnValue == -1)
			{
				printf("Error! No more memory!\n");
				return -1;
			}

		}

	}

	// Check if user inputs '.' character
	while (search)
	{
		struct WordNode* foundNode = NULL;

		unsigned long hashNumber = 0;

		char inputSearch[STRING_LENGTH] = { 0 };

		printf("\nPlease enter a word you would like to search for\n");
		fgets(inputSearch, sizeof(inputSearch), stdin);

		// Get rid of newline character
		inputSearch[strcspn(inputSearch, "\n")] = '\0';

		search = strcmp(inputSearch, ".");

		// If user does not input '.' character
		if (search != 0)
		{
			hashNumber = myHashFunction(inputSearch);

			/* returns a pointer to the node containing a flight, if both the destination and date
			are matched then assign it to foundNode variable */
			foundNode = findWord(hashTable[hashNumber], inputSearch);

			// If foundNode is not NULL, the string is found
			if (foundNode != NULL)
			{
				printf("%s\n", foundNode->name);
				printf("Success!\n");
			}
			else
			{
				printf("Not there!\n");
			}

		}
	}

	// Free all the memory of hash table
	for (j = 0; j < MAX_HASH; j++)
	{
		freeAll(hashTable[j]);
		hashTable[j] = NULL;
	}

}


/*
 * Author: Dan Bernstein
 * Function: hash()
 * Description: This function will calculate a string and return a number (unsigned long)
 * Parameters:  char *firstName: string containing a name
 * Returns: unsigned long
*/
unsigned long hash(char* str)
{
	unsigned long hash = 5381;
	int c = 0;
	while ((c = *str++) != '\0')
	{
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}


/*
 * Function: myHashFunction()
 * Description: This function will calculate a string and return a number that moduled to 11 (unsigned long)
 * Parameters:  char *firstName: string containing a name
 * Returns: unsigned long 
*/
unsigned long myHashFunction(char* str)
{
	unsigned long number = 0;

	number = hash(str);

	return number % 11;
}

/*
 * Function: insert()
 * Description: This function inserts an element in the correct location in the list, sorted alphabetically.
 * Parameters:  char *firstName: string containing the firstName
 *				WordNode **head: POINTERS TO head of the list
 * Returns: 1 if the insertion failed, 0 otherwise
*/
int insert(struct WordNode **head, char* str)
{
	WordNode* newBlock = NULL;
	WordNode* ptr = NULL;
	WordNode* prev = NULL;

	// allocate a block of memory for new record
	newBlock = (WordNode *)malloc(sizeof(WordNode));

	if (newBlock == NULL)
	{
		return -1;
	}

	strcpy(newBlock->name, str);

	newBlock->next = NULL;

	// now link this record to the list in the appropriate place
	if (*head == NULL)
	{
		// empty list, so set head
		*head = newBlock;
	}
	else if (strcmp((*head)->name, newBlock->name) >= 0) // special case
	{
		
		// location that used to be at the front of the list
		newBlock->next = *head;
		// set first_number to point to the new start of the list
		*head = newBlock;
	}
	else
	{
		prev = *head;		// first item in list
		ptr = (*head)->next;	// second item in list 

		while (ptr != NULL)
		{
			if (strcmp(ptr->name, newBlock->name) >= 0)
			{
				// we've found a name in the list that is either equal to or greater 
				// than the one we're entering now
				break;
			}
			prev = ptr;
			ptr = ptr->next;
		}	/* end while */

		// add the new node here, between prev and ptr
		newBlock->next = ptr;
		prev->next = newBlock;

	}
	return 0;
}

/*
* Function: WordNode* findWord()
* Description : This function will return NULL if a string is not found or it returns a
pointer to the node containing the string, if the string is matched
* Parameters : 2 parameter(WordNode *head: start of the linked list - char *str: pointer
to null-terminated string containing name).
* Returns : A node
*/
struct WordNode* findWord(struct WordNode* head, char* str)
{
	WordNode* curr = NULL;
	curr = head;

	while (curr != NULL)
	{
		// found it?
		if (strcmp(curr->name, str) == 0)
		{
			return curr;
		}
		curr = curr->next;

	}
	return NULL;
}

/*
 * Function: freeAll(WordNode *head)
 * Description: This function will free all allocated memory in the linked list.
 * Parameter: WordNode *head(a double pointer): start of the linked list
 * Returns: void
 */
void freeAll(WordNode* head)
{
	WordNode* curr = NULL;
	WordNode* next = NULL;

	curr = head;

	// traverse the list, being careful to not access freed blocks
	while (curr != NULL)
	{
		// keep a pointer to the next block so we can go there after it's freed
		next = curr->next;
		free(curr);
		curr = next;
	}

}