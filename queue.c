#include <stdio.h>
#include "queue.h"

#define OK		0
#define ERR 	1

TskNodePtr headPtr = NULL;
TskNodePtr tailPtr = NULL;
LstNodePtr startPtr = NULL;

void printList( LstNodePtr currentPtr ){
	if(currentPtr == NULL){
		printf("List is empty.\n");
	}
	else {
		printf("\nThe list is:");

		while(currentPtr!= NULL){		//print of all list
			printf("%d-",currentPtr->data);
			currentPtr = currentPtr->next;
		}

		printf("NULL\n");
	}
}

void find_and_deleteDuplicates(LstNodePtr *sPtr)
{
	LstNodePtr current = *sPtr;
	LstNodePtr next_next;

	if (current == NULL)		//our list is empty, exit from function
		return;

	while (current->next != NULL)			//travel in list from start to end(NULL)
	{
		if (current->data == current->next->data)	//compare two node in sequence, if they are equal
		{
			next_next = current->next->next;
			free(current->next);					//delete one of them.
			current->next = next_next;
		}
		else // If current node and next node are not equal in list, nobody is deleted.
		{
			current = current->next;
		}
	}
}

int Insert( LstNodePtr *sPtr, int value ){

	LstNodePtr newPtr;
	LstNodePtr previousPtr;
	LstNodePtr currentPtr;

	newPtr = malloc( sizeof( Lst_node_s ) );		//create new node field

	if ( newPtr != NULL ) {
		newPtr->data = value;			//assing our value to list
		newPtr->next = NULL;

		previousPtr = NULL;
		currentPtr = *sPtr;

		while( currentPtr != NULL && value > currentPtr->data ) {		//insert ascending order
			previousPtr = currentPtr;
			currentPtr = currentPtr->next;
		}

		if ( previousPtr == NULL ) {		//our value should be first
			newPtr->next = *sPtr;
			*sPtr = newPtr;
		}
		else {					//add to sorted list
			previousPtr->next = newPtr;
			newPtr->next = currentPtr;
		}
	}
	else {
		printf("%c not inserted. No memory available.\n", value);
		return ERR;
	}

	return OK;
}

int Delete( LstNodePtr *sPtr, int value ){

	LstNodePtr previousPtr;
	LstNodePtr currentPtr;
	LstNodePtr tempPtr;

	if( value == ( *sPtr )->data ){	//the first is our value ?
		tempPtr = *sPtr;			//yes it is, so skip(delete) it.
		*sPtr = ( *sPtr )->next;
		free( tempPtr );			//delete that malloc area part
		return OK;
	}
	else{
		previousPtr = *sPtr;
		currentPtr = ( *sPtr )->next;

		while ( currentPtr != NULL && currentPtr->data != value ) {	//find it in list
			previousPtr = currentPtr;
			currentPtr = currentPtr->next;
		}

		if( currentPtr != NULL ){		//if we found it, so delete it
			tempPtr = currentPtr;
			previousPtr->next = currentPtr->next;
			free( tempPtr );
			return OK;
		}
	}

	return ERR;					//we don't have it, so return ERR.
}

int Search(LstNodePtr *head, int value)
{
	LstNodePtr current = *head;  // Initialize current
	while (current != NULL)		//we have node in list ?
	{
		if (current->data == value)		//our list has this value ?
			return OK;					//yes we have
		current = current->next;		//travel in list
	}
	return ERR;						//we don't have it, so return ERR.
}

int do_list_process(Tsk_node_s *node){
	int ret=ERR;

	switch(node->task_type){		//switch-case for insert, delete and search and debug section

	case 0:
		ret=Insert(&startPtr,node->value);
		if(ret!=OK){
			printf("task %d-insert %d: %d cannot be inserted\n",node->task_num,node->value,node->value);
		}else{
			printf("task %d-insert %d: %d is inserted\n",node->task_num,node->value,node->value);
		}
		find_and_deleteDuplicates(&startPtr);
		break;
	case 1:
		if(startPtr!=NULL){
			ret=Delete(&startPtr,node->value);
			if(ret!=OK){
				printf("task %d-delete %d: %d cannot be deleted\n",node->task_num,node->value,node->value);
			}else{
				printf("task %d-delete %d: %d is deleted\n",node->task_num,node->value,node->value);
			}
		}else{
			printf("task %d-delete %d: %d cannot be deleted\n",node->task_num,node->value,node->value);
		}
		break;
	case 2:
		ret=Search(&startPtr,node->value);
		if(ret!=OK){
			printf("task %d-search %d: %d is not found\n",node->task_num,node->value,node->value);
		}else{
			printf("task %d-search %d: %d is found\n",node->task_num,node->value,node->value);
		}
		break;

	default:
		break;
	}
	return 0;
}

int Task_dequeue( TskNodePtr *headPtr, TskNodePtr *tailPtr, Tsk_node_s *node)
{
	TskNodePtr tempPtr;

	node->task_num = (*headPtr)->task_num;		//we take first node because of FIFO
	node->task_type = (*headPtr)->task_type;
	node->value = (*headPtr)->value;

	tempPtr = *headPtr;							//taking node is took out from queue
	*headPtr = ( *headPtr ) -> next;

	if (*headPtr == NULL){						//if queue is empty
		*tailPtr = NULL;
	}

	free(tempPtr);
	return 0;
}

void Task_enqueue(TskNodePtr *headPtr, TskNodePtr *tailPtr, Tsk_node_s *node)
{
	TskNodePtr newPtr;

	newPtr = malloc(sizeof(Tsk_node_s));		//create new ptr for task

	if(newPtr != NULL){				//if malloc is successful
		newPtr->value = node->value;		//my task data assingning...
		newPtr->task_num = node->task_num;
		newPtr->task_type = node->task_type;
		newPtr->next = NULL;			//nextPtr is not certain yet.

		printf("Enqueue newPtr->task_num = %d, Enqueue newPtr->task_type = %d , Enqueue newPtr->value = %d\n",newPtr->task_num,newPtr->task_type,newPtr->value);

		if(*headPtr == NULL){			//control whether first node is exist
			*headPtr = newPtr;			//this is head of queue
		}
		else {
			(*tailPtr)->next = newPtr;		//this is not first, it should connect to tail
		}

		*tailPtr = newPtr;	//our node should be tail
	}
	else {
		printf("%c not inserted.No memory available.\n", node->value );	//malloc is unsuccessful
	}

}

void Task_queue(int n){
	int i=0;
	Tsk_node_s task_node;

	printf("Generated %d random list tasks...\n",n);
	for(i=1;i<=n;i++){			//creating task nodes and add to enqueue

		task_node.task_num = i;
		task_node.task_type = rand() % 3;
		task_node.value = rand() % 20 + 1;
		Task_enqueue(&headPtr,&tailPtr,&task_node);

	}

	while(headPtr!=NULL){			//taking task nodes with dequeue from queue
		Task_dequeue(&headPtr,&tailPtr,&task_node);
		do_list_process(&task_node);
	}

	printList(startPtr);
}

int main(int argc, char* argv[])
{
	int task_count=0;

	//we take number of task from user as parameter.

	if(argv[1]!=NULL){
		task_count=atoi(argv[1]);
		printf("task_count = %d\n",task_count);
		Task_queue(task_count);
	}else{
		printf("You should enter task number as parameter.\n");
		return ERR;
	}

	return OK;
}




