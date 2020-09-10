#include <stdio.h> 
#include <stdlib.h> 
#include "queue.h"


Queue* createQueue(int cap){
  Queue* queue = (Queue*)malloc(sizeof(Queue));
  queue->capacity = cap;
  queue->head=queue->tail=0;
  queue->a = (int*)malloc(sizeof(int) * cap);

  return queue;
}

int queueEmpty(Queue* queue){
  return queue->head==queue->tail;
}

int queueFull(Queue* queue){
  return queue->head == ((queue->tail) + 1) % queue->capacity;
}

void enqueue(Queue* queue, int x){
  if(queueFull(queue))
    printf("Overflow Error!!\n");
  else{
    queue->a[queue->tail] = x;
    if(queue->tail == queue->capacity)
      queue->tail=1;
    else (queue->tail)++;
  }
}

int dequeue(Queue* queue){
  int x;
  if(queueEmpty(queue))
    printf("Underflow error!!\n");
  else{
    x = queue->a[queue->head];
    if(queue->head==queue->capacity)
      queue->head=1;
    else queue->head++;
    return x;
  }
}

int queue_head(Queue* queue) {
  return queue->head;
}

int queue_tail(Queue* queue) {
  return queue->tail;
}