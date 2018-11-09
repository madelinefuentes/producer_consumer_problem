//class reponsible for synchronizing producer and consumer threads

#include "ProducerConsumer.h"
#include <pthread.h>
#include <signal.h>

//add BoundedBuffer, locks and any global variables
BoundedBuffer buffer = BoundedBuffer(0);
pthread_mutex_t lock;
int add;
int added;
int removed;
int proSleep;
int conSleep;
int timeT;

//initialize producer and consumer threads
void InitProducerConsumer(int p, int c, int psleep, int csleep, int items){
  buffer = BoundedBuffer(items);
  lock = PTHREAD_MUTEX_INITIALIZER;
  add = items;
  added = 0;
  removed = 0;
  timeT = 0;
  proSleep = psleep;
  conSleep = csleep;
  pthread_t producers[p];
  pthread_t consumers[c];

  remove("output.txt");

  //create threads
  for(int i = 0; i < p; i++)
    pthread_create(&producers[i], NULL, producer, &producers[i]);
  
  for(int i = 0; i < c; i++)
    pthread_create(&consumers[i], NULL, consumer, &consumers[i]);

  //wait for threads to complete
  for(int i = 0; i < p; i++)
    pthread_join(producers[i], NULL);
  
  for(int i = 0; i < c; i++){
    pthread_join(consumers[i], NULL);
  }
}

//producer thread puts item into buffer
void* producer(void* threadID){
  while(added < add){
    usleep(proSleep);
    int data = rand();
    buffer.append(data);
    added++;
    pthread_mutex_lock(&lock);
    if(added > add)
      continue;
    
    ofstream file;
    file.open("output.txt", ios_base::app);
    file << "Producer #" << pthread_self() << " time = " << timeT++;
    file << ", producing data item #" << added << ", item value = " << data << "\n";
    pthread_mutex_unlock(&lock);
  }
  pthread_exit(0);
  return threadID;
}

//consumer thread consumes item from buffer
void* consumer(void* threadID){
  while(removed < add){
    usleep(conSleep);
    int data = buffer.remove();
    removed++;
    if(removed > add)
      continue;
       
    ofstream file;
    file.open("output.txt", ios_base::app);
    file << "Consumer #" << pthread_self() << ", time = " << timeT++;
    file << ", consuming data item with value =  " << data << "\n";
  }
  pthread_exit(0);
  return threadID;
}
