
/* 
File name is linked_list.c
 Purpose: file contains functions for manipulating singly linked list
 
 Created By
 Doron Nussbaum 2016
 
 Modifications:
 November 2017 - minor modifications
 
 Function Modifications:
 Farzyab Gohar November 2017
 
 
 Copyright 2017
 
 */

/******************************************************************/
// INCLUDE 

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "linked_list.h"


/************************************************************************/
// Define 



/************************************************************************/

/*
Purpose: insert a new node into the list as the first element
input
id - id of person
firstName - first name of person
familyName - family name of person

input/output
head - head of linked list

return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/

PersonalInfo *insertToList(PersonalInfo **head, unsigned int id, 
        char *firstName, char *familyName)
{
	//pointer initialisation
	PersonalInfo *new_node = NULL;
	
	//memory allocation
	new_node = (PersonalInfo*)malloc(sizeof(PersonalInfo));
	
	if (new_node == NULL){return NULL;}
	
	//set data
	new_node->id = id;
	strcpy(new_node->firstName, firstName);
	strcpy(new_node->familyName, familyName);
	
	//make new node point to first node of the list
	new_node->next = *head;
	
	//update head
	*head = new_node;
	
	return new_node;
}


/************************************************************************/
/*
Purpose: insert a new node into the list after the given node  

Input
node - the node after which the new node must be added to the list
id - id of person
firstName - first name of person
familyName - family name of person


return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/


PersonalInfo *insertAfter(PersonalInfo *node, unsigned int id, char *firstName, char *familyName)
{
	//pointer initialisation
	PersonalInfo *new_node = NULL;
	
	//memory allocation
	new_node = (PersonalInfo*)malloc(sizeof(PersonalInfo));
	if (new_node == NULL){return NULL;}
	
	//copy data
	new_node->id = id;
	strcpy(new_node->firstName, firstName);
	strcpy(new_node->familyName, familyName);
	
	//make new node point to what the node before was pointing to
	new_node->next = node->next;
	//make the node before point to new node
	node->next = new_node;
	
	return new_node;
	


}

/************************************************************************/
/*
Purpose: create a new node and insert it into the end of the list
Input
head - the head of the list
id - id of person
firstName - first name of person
familyName - family name of person


return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/


PersonalInfo *insertLast(PersonalInfo **head, unsigned int id, char *firstName, char *familyName)
{
	//pointer initialisation and memory allocation
	PersonalInfo *new_node = NULL;
	new_node = (PersonalInfo*)malloc(sizeof(PersonalInfo));
	if (new_node == NULL){return NULL;}
	
	//copy data, and make new node point to NULL since it will become the new tail of the list
	new_node->id = id;
	strcpy(new_node->firstName, firstName);
	strcpy(new_node->familyName, familyName);
	new_node->next = NULL;	
	
	//if list is empty make new node the head
	if (*head == NULL){
		*head = new_node;
		return new_node;
	}
	
	//holds current position in list
	PersonalInfo *pos = *head;
	
	//keep traversing list until last node is reached
	while((pos->next)!=NULL){
		pos=pos->next;
	}
	
	
	//make last node point to new node
	pos->next = new_node;
	
	return new_node;
	
}


/************************************************************************/
/*
Purpose: search for the first node with the matching firstName
Input
head - the head of the list
firstName - first name of person

return
a pointer to the node that was found.
NULL - if no node was found or list empty

*/


PersonalInfo *searchByName(PersonalInfo *head, char *firstName)
{
	//check if list is empty
	if(head == NULL){return NULL;}
	
	
	//pos maintains the current position in the linked list
	PersonalInfo *pos = head; 
	
	//return the position of the node if match is found, else keep traversing list until
	//no more nodes exist to be compared
	do {
		if (strcmp(pos->firstName, firstName)==0){
			return pos;
		}
		pos = pos->next;
	}while (pos!=NULL);
	
	
	return NULL;

}

/************************************************************************/
/*
Purpose: search for the first node with the matching id
Input
head - the head of the list
id - id of person person

return
a pointer to the node that was allocated.  

NULL - if no node was found or list empty 

*/


PersonalInfo *searchById(PersonalInfo *head, unsigned int id)
{
	//check if list is empty
	if(head == NULL){return NULL;}
	
	//pos maintains the current position in the linked list
	PersonalInfo *pos = head; 
	
	//traverse the entire list and return the location of the matching node, else keep traversing until 
	//no more nodes left to be checked
	do {
		if (pos->id == id){
			return pos;
		}
		pos = pos->next;
	}while (pos!=NULL);
	
	
	return NULL;
    
}

/***************************************************************/

/*
Purpose: delete the first node from the list
Input
head - the head of the list

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return

0 if node was deleted
1 if node was not deleted or list is empty

*/


int deleteFromList(PersonalInfo **head, unsigned int *id,
	char *firstName, char *familyName)

{
	  
	
	
	//check if list is empty.
	if (*head == NULL){
		return 1;
	}
	
	//store head in p
	PersonalInfo *p = *head;
	//copy data of deleted node
	strcpy(firstName, p->firstName);
	strcpy(familyName, p->familyName);
	*id = p->id;
		
	//update head
	*head = p->next;
	
	//free memory
	free(p);
	return 0;
}


/***************************************************************/

/*
Purpose: delete the last node from the list
Input
head - the head of the list

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return

0 if node was deleted  
1 if node was not deleted or list is empty 

*/


int deleteLast(PersonalInfo **head, unsigned int *id,
                char *firstName, char *familyName)

{

   //check if list is empty
   if(*head == NULL){return 1;}
   
   //temporary storage
   PersonalInfo *p = *head;
   
   //check if only 1 element in list
   if (p->next == NULL){
		//update head
		*head = NULL;
		//copy data of deleted node
		strcpy(firstName, p->firstName);
		strcpy(familyName, p->familyName);
		*id = p->id;
		//free memory
		free(p);
		return 0;
	}

	//pos holds current position in list
	PersonalInfo *pos = *head;
	
	
	//keep traversing until the tail is found
	while((pos->next)->next!=NULL){
		pos=pos->next;
	}
	
	//copy node to be deleted into p
	p=pos->next;
	//copy the data
	strcpy(firstName, p->firstName);
	strcpy(familyName, p->familyName);
	*id = p->id;
	
	//update pointer to last node
	pos->next = NULL;
	
	//free memory
	
	free(p);
	return 0;
}



/************************************************************************/

/*
Purpose: delete the record after the given node 
Input
node - a node in the list

output
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return
0 if node was deleted 
1 if node was not deleted (either input node is NULL or input node was the lastnode in the list)

*/



int deleteAfter(PersonalInfo *node, unsigned int *id,
                char *firstName, char *familyName)

{
	//check if null node is passed
	if (node == NULL){
		return 1;
	}
	
	//check if last node
	if (node->next == NULL){
		return 1;
	}
	
	//temp for storage
    PersonalInfo *temp = NULL;
    
    //store the node to be deleted
    temp = node->next;
    //copy data
    strcpy(firstName, temp->firstName);
	strcpy(familyName, temp->familyName);
	*id = temp->id;
    //make the node that we are deleting after point to whatever the deleted node was pointing to
    node->next = temp->next;
    

    //free memory
	free(temp);
	return 0;
}

/************************************************************************/

/*
Purpose: delete the first node with the matching firstName
Input
head - the head of the list
firstName - first name of person

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return
0  if node was deleted
1 if node was not found (e.g., list is empty, no such node exists)

*/


int deleteNodeByName(PersonalInfo **head, char *firstName,
	char *familyName, unsigned int *id)
{
	//check if empty list
	if(*head==NULL){
		return 1;
	} 
	//pointer intialisation
	PersonalInfo *p = NULL;
	
	//stores the found node
	p = searchByName(*head, firstName);
	
	//check if node exists
	if (p==NULL){
		free(p);
		return 1;
	}
	
	//for 1 element in list
	if ((*head)->next == NULL){
		//store head in p and update head
		p = *head;
		*head = NULL;
		//copy contents to output
		strcpy(firstName, p->firstName);
		strcpy(familyName, p->familyName);
		*id = p->id;
		//free memory
		free(p);
		return 0;
	}
	
	//for more than 1 element
	
	//stores the node that points to the deleted node
	PersonalInfo *prev = *head;
	//stores the node to be deleted
	p = *head;
	
	//keep iterating until match is found
	do {
		prev = p;
		p = p->next;
	}while(strcmp(p->firstName, firstName)!=0);
	
	//copy data
	strcpy(firstName, p->firstName);
	strcpy(familyName, p->familyName);
	*id = p->id;
	
	//update the pointer before node to be deleted
	prev->next=p->next;
	
	//free memory
	free(p);
	return 0;
	
	
	

}
/************************************************************************/
/*
Purpose: deletes all nodes from the list
input/output
head - the head of the list


*/


void deleteList(PersonalInfo **head)
{
	//check if list is empty
	
	if (*head == NULL){
		printf("List is empty!");
		return;
	}
	
	//stores each node so we can free it from memory
	PersonalInfo *p = NULL;
	
	//traverses through list, freeing nodes one at a time
	do {
		p = *head;
		*head = (*head)->next;
		free(p);
	}while((*head)!=NULL);
}



/************************************************************************/
/*
Purpose: prints the fields of a node
input:
node - a pointer to a given node

*/


void printNode(PersonalInfo *node)
{
	printf("%-20s %-20s %7d \n",node->firstName, node->familyName, node->id);

}


/************************************************************************/
/*
Purpose: prints all the records in the list

input
head - the head of the list
*/


void printList(PersonalInfo *head)
{
	//check if list empty
	if (head==NULL){
		printf("List is empty!");
		return;
	}
	
	//store address of first node
	PersonalInfo *p = head;
	
	//traverse through array and print until we reach the end
	do{
		printNode(p);
		p=p->next;
	}while(p!=NULL);
	//free memory
	free(p);
}

/************************************************************************/
/*
Purpose: counts the number of nodes in the list
input
head - the head of the list

return 
the number of nodes in the list

*/


int listSize(PersonalInfo *head)
{
	
	//check if list empty
	if(head==NULL){
		return 0;
	}
	
	//store size
	int size = 0;
	
	//store address of first node
	PersonalInfo *p = head;
	
	//traverse through array and increment size for each node until end is reached
	do{
		size = size+1;
		p=p->next;
	}while(p!=NULL);
	//free memory
	free(p);
	
	//return size of list
	return size;
}

/************************************************************************/
/*
Purpose: counts the number of nodes in the list with a matching firstName
input
head - the head of the list

return 
the number of nodes in the list that match the firstName


*/


int countRecords(PersonalInfo *head, char *firstName)
{
	//check if list empty
	if (head==NULL){
		return 0;
	}
	
	//initialize count
	int count = 0;
	
	//set starting position
	PersonalInfo *p = head;
	
	//runs searchByName to find all matching records and increments count by 1 for each match
	//the starting position given to searchByName each time (with the exception of the initial match)
	//is 1 + the most recent match found
	//loops continues until end of list is reached
	do {
		p = searchByName(p, firstName);
		if (p!=NULL){
			count = count+1;
			p = p->next;
		}
	}while(p!=NULL);
	
	//free memory
	free(p);
	//return number of matches found
	return count;
	
}




/************************************************************************/
/*

Purpose: removes all duplicates records from the list.  Duplicate records are determined by their first name. 
You can assume that the listed is sorted by first name.

input
head - the head of the  list



*/




void removeDuplicates(PersonalInfo *head)
{
	//check if list empty
	if(head==NULL){
		printf("List is empty!");
		return;
	}

	//initialize starting position and temp storage for duplicates to delete
	PersonalInfo *pos = head;
	PersonalInfo *temp = NULL;
	
	//go through list until last node is reached
	//check if the node after the current one is a duplicate of the current one
	//if it is a duplicate, update the pointers and delete the duplicate
	//if no more duplicates for the current node are found, change the current node to the one after
	while (pos->next!=NULL){
		if(strcmp(pos->firstName, (pos->next)->firstName)==0){
			temp = pos->next;
			pos->next=temp->next;
			free(temp);
		} else{
			pos = pos->next;
		}
	}
}

