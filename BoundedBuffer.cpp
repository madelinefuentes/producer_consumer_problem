//atomically produce and consume items into the buffer

#include "BoundedBuffer.h"
#include <pthread.h>
#include <cmath>

int head = 0;

//constructor to initiliaze all the variables declared in BoundedBuffer.h
BoundedBuffer::BoundedBuffer(int N){
  buffer = new int[N];
  buffer_size = N;
  buffer_cnt = 0;
  buffer_last = 0;
  head = 0;

  buffer_lock = PTHREAD_MUTEX_INITIALIZER;
  buffer_full = PTHREAD_COND_INITIALIZER;
  buffer_empty = PTHREAD_COND_INITIALIZER;
}

//append a data item to the circular buffer
void BoundedBuffer::append(int data){
  pthread_mutex_lock(&buffer_lock);
  while(buffer_cnt >= buffer_size)
    pthread_cond_wait(&buffer_empty, &buffer_lock);
  
  buffer[buffer_last] = data;
  buffer_cnt++;
  buffer_last++;
  if(buffer_last >= buffer_size)
    buffer_last = 0;
  
  pthread_cond_signal(&buffer_full);
  pthread_mutex_unlock(&buffer_lock);
}

//remove and return a data item from the circular buffer
int BoundedBuffer::remove(){
  pthread_mutex_lock(&buffer_lock);
  while(isEmpty())
    pthread_cond_wait(&buffer_full, &buffer_lock);
  
  int data = buffer[head];
  head++;
  if(head >= buffer_size)
    head = 0;
  
  buffer_cnt--;
  pthread_cond_signal(&buffer_empty);
  pthread_mutex_unlock(&buffer_lock);
  return data;
}

//check if the buffer is empty
bool BoundedBuffer::isEmpty(){
  return(buffer_cnt == 0);
}


