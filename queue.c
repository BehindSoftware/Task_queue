#include <stdio.h>
#include "queue.h"

#define OK		0
#define ERR 	1


TskNodePtr headPtr = NULL;
TskNodePtr tailPtr = NULL;
LstNodePtr startPtr = NULL;

int Insert( LstNodePtr *sPtr, int value ){

	LstNodePtr newPtr;
	LstNodePtr previousPtr;
	LstNodePtr currentPtr;

	newPtr = malloc( sizeof( Lst_node_s ) );

	if ( newPtr != NULL ) {
		newPtr->data = value;
		newPtr->next = NULL;

		previousPtr = NULL;
		currentPtr = *sPtr;

		while( currentPtr != NULL && value > currentPtr->data ) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->next;
		}

		if ( previousPtr == NULL ) {
			newPtr->next = *sPtr;
			*sPtr = newPtr;
		}
		else {
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

	if( value == ( *sPtr )->data ){
		tempPtr = *sPtr;
		*sPtr = ( *sPtr )->next;
		free( tempPtr );
		return value;
	}
	else{
		previousPtr = *sPtr;
		currentPtr = ( *sPtr )->next;

		while ( currentPtr != NULL && currentPtr->data != value ) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->next;
		}

		if( currentPtr != NULL ){
			tempPtr = currentPtr;
			previousPtr->next = currentPtr->next;
			free( tempPtr );
			return value;
		}
	}

	return ERR;
}

int do_list_process(Tsk_node_s *node){

	switch(node->task_type){

	case 0:
		printf("Inserting... \r\n");
		Insert(&startPtr,node->value);
		break;
	case 1:
		printf("Deleting... \r\n");
		if(!(startPtr==NULL)){
			Delete(&startPtr,node->value);
		}
		break;
	case 2:
		printf("Searching... \r\n");
		//Search(node->value);
		break;

	default:
		break;
	}
	return 0;
}

int Task_dequeue( TskNodePtr *headPtr, TskNodePtr *tailPtr, Tsk_node_s *node)
{
	//int ret=ERR;
	TskNodePtr tempPtr;

	node->task_num = (*headPtr)->task_num;
	node->task_type = (*headPtr)->task_type;
	node->value = (*headPtr)->value;

	printf("\n Dequeue headPtr->task_num = %d, Dequeue headPtr->task_type = %d , Dequeue headPtr->value = %d",node->task_num,node->task_type,node->value);

	tempPtr = *headPtr;
	*headPtr = ( *headPtr ) -> next;

	if (*headPtr == NULL){
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

		printf("\n Enqueue newPtr->task_num = %d, Enqueue newPtr->task_type = %d , Enqueue newPtr->value = %d",newPtr->task_num,newPtr->task_type,newPtr->value);

		if(*headPtr == NULL){			//control whether first node is exist
			*headPtr = newPtr;			//this is first, right
		}
		else {
			(*tailPtr)->next = newPtr;		//this is not first, so connect to tail
		}

		*tailPtr = newPtr;	//our node should be tail
	}
	else {
		printf("%c not inserted.No memory available.\n", node->value );	//malloc is unsuccessful
	}

	//printf("\n Enqueue tailPtr->task_num = %d, Enqueue tailPtr->task_type = %d , Enqueue tailPtr->value = %d",(*tailPtr)->task_num,(*tailPtr)->task_type,(*tailPtr)->value);

}

void Task_queue(int n){
	int i=0;

	for(i=1;i<=n;i++){
		Tsk_node_s nodetoqueue;
		nodetoqueue.task_num = i;
		nodetoqueue.task_type = rand() % 3;
		nodetoqueue.value = rand() % 20 + 1;
		printf("\n Gönderiyorum nodetoqueue.task_num = %d, Gönderiyorum nodetoqueue.task_type = %d , Gönderiyorum nodetoqueue.value = %d",nodetoqueue.task_num,nodetoqueue.task_type,nodetoqueue.value);
		Task_enqueue(&headPtr,&tailPtr,&nodetoqueue);
	}

	for(i=1;i<(n+1);i++){
		Tsk_node_s nodefromqueue;
		Task_dequeue(&headPtr,&tailPtr,&nodefromqueue);
		printf("\n Alıyorum nodefromqueue.task_num = %d, Alıyorum nodefromqueue.task_type = %d , Alıyorum nodefromqueue.value = %d",nodefromqueue.task_num,nodefromqueue.task_type,nodefromqueue.value);
		do_list_process(&nodefromqueue);
	}
}

int main(int argc, char* argv[])
{
	int task_count=0;

	printf("%d adet argüman var.\n",argc);

//	for(int i=0;i<argc;i++){
//		printf("%d argüman: %s\n",i,argv[i]);
//		task_count=atoi(argv[1]);
//
//	}
	task_count=atoi(argv[1]);
	printf("task_count = %d\n",task_count);
	Task_queue(task_count);

	return 0;
}




