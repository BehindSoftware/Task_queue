#include <stdio.h>
#include "queue.h"

TskNodePtr headPtr = NULL;
TskNodePtr tailPtr = NULL;

int Task_dequeue( TskNodePtr *headPtr, TskNodePtr *tailPtr, Tsk_node_s *node )
{
	int value;
	TskNodePtr tempPtr;

	node = *headPtr;
//	node->task_num = (*headPtr)->task_num;
//	node->task_type= (*headPtr)->task_type;
//	node->value = (*headPtr)->value;

	value = ( *headPtr ) -> value;
	tempPtr = *headPtr;
	*headPtr = ( *headPtr ) -> next;

	if (*headPtr == NULL){
		*tailPtr = NULL;
	}


	free(tempPtr);
	return value;
}

void Task_enqueue(TskNodePtr *headPtr, TskNodePtr *tailPtr, Tsk_node_s *node)
{
	TskNodePtr newPtr;

	newPtr = malloc(sizeof(Tsk_node_s));		//create new ptr for task

	if(newPtr != NULL){				//if malloc is successful
		newPtr->value = node->value;		//my task data assingning...
//		newPtr->task_num = node->task_num;
//		newPtr->task_type = node->task_type;
		newPtr->next = NULL;			//nextPtr is not certain yet.

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

}

void Task_queue(int n){
	int i=0;

	for(i=1;i<=n;i++){
		Tsk_node_s nodetoqueue;
		nodetoqueue.task_num = i;
		nodetoqueue.task_type = rand() % 3 + 1;
		nodetoqueue.value = rand() % 20 + 1;
		Task_enqueue(&headPtr,&tailPtr,&nodetoqueue);
	}

	for(i=1;i<(n+1);i++){
		Tsk_node_s nodefromqueue;
		Task_dequeue(&headPtr,&tailPtr,&nodefromqueue);
		printf("%d\n",nodefromqueue.value);

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




