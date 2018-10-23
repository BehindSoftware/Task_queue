#include <stdio.h>
#include "queue.h"


int Task_dequeue( tsk_node_s *headPtr, tsk_node_s *tailPtr, tsk_node_s *node )
{
	int value;
	tsk_node_s tempPtr;

	value = ( *headPtr ) -> data;
	tempPtr = *headPtr;
	*headPtr = ( *headPtr ) -> nextPtr;

	if ( *headPtr == NULL ) {
		*tailPtr = NULL;
	}

	free( tempPtr );
	return value;
}

void Task_enqueue( tsk_node_s *headPtr, tsk_node_s *tailPtr, tsk_node_s *node )
{
	tsk_node_s newPtr;

	newPtr = malloc( sizeof( tsk_node_s ) );

	if ( newPtr != NULL ){
		newPtr->data = node->value;
		newPtr->nextPtr = NULL;

		if ( isEmpty( *headPtr ) ) {
			*headPtr = newPtr;
		}
		else {
			( *tailPtr )->nextPtr = newPtr;
		}

		*tailPtr = newPtr;
	}
	else {
		printf("%c not inserted.No memory available.\n", value );
	}

}

void Task_queue(int n){

	//n terminalden girilen sayı

	tsk_node_s tsk_node_s *headPtr = NULL;
	tsk_node_s tsk_node_s *tailPtr = NULL;

	for(int i=1;i<=n;--i){

		struct tsk_node_s* node = NULL;
		node = malloc(sizeof(struct tsk_node_s));
		node->task_num = i;
		node->task_type = rand() % 3 + 1;
		node->value = rand() % 20 + 1;
		Task_enqueue(&head,&tail,&node);
		free(node);
	}

}

int Insert( lst_node_s *sPtr, int value ){

	lst_node_s newPtr;
	lst_node_s previousPtr;
	lst_node_s currentPtr;

	newPtr = malloc( sizeof( lst_node_s ) );

	if ( newPtr != NULL ) {
		newPtr->data = value;
		newPtr->nextPtr = NULL;

		previousPtr = NULL;
		currentPtr = *sPtr;

		while( currentPtr != NULL && value > currentPtr->data ) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}

		if ( previousPtr == NULL ) {
			newPtr->nextPtr = *sPtr;
			*sPtr = newPtr;
		}
		else {
			previousPtr->nextPtr = newPtr;
			newPtr->nextPtr = currentPtr;
		}
	}
	else {
		printf("%c not inserted. No memory available.\n", value);
		return ERR;
	}

	return OK;
}

int Delete( lst_node_s *sPtr, int value ){

	lst_node_s previousPtr;
	lst_node_s currentPtr;
	lst_node_s tempPtr;

	if( value == ( *sPtr )->data ){
		tempPtr = *sPtr;
		*sPtr = ( *sPtr )->nextPtr;
		free( tempPtr );
		return value;
	}
	else{
		previousPtr = *sPtr;
		currentPtr = ( *sPtr )->nextPtr;

		while ( currentPtr != NULL && currentPtr->data != value ) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}

		if( currentPtr != NULL ){
			tempPtr = currentPtr;
			previousPtr->nextPtr = currentPtr->nextPtr;
			free( tempPtr );
			return value;
		}
	}

	return '\0';
}

int main(int argc, char* argv[])
{

printf("%d adet argüman var.\n",argc);

for(int i=0;i<argc;i++)
	printf("%d argüman: %s\n",i,argv[i]);





return 0;
}




