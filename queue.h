#include <stdio.h>
#include <stdlib.h>

/* Struct for list nodes */
struct lst_node_s {
int data;
struct lst_node_s* next;
};

typedef struct lst_node_s Lst_node_s;
typedef Lst_node_s *LstNodePtr;

/* Struct for task nodes */
struct tsk_node_s {
int task_num; //starting from 0
int task_type; // insert:0, delete:1, search:2
int value;
struct tsk_node_s* next;
};

typedef struct tsk_node_s Tsk_node_s;
typedef Tsk_node_s *TskNodePtr;



/* List operations */
int Insert(int value);
int Search(int value);
int Delete(int value);

/* Task queue functions */
void Task_queue(int n); //generate n random tasks for the task queue
void Task_enqueue(TskNodePtr *headPtr, TskNodePtr *tailPtr, Tsk_node_s *node); //insert a new task into task queue
int Task_dequeue(TskNodePtr *headPtr, TskNodePtr *tailPtr, Tsk_node_s *node); //take a task from task queue
