/* 
To compile: gcc -pthread -o test_threads test_threads.cpp
To run: ./test_threads
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <queue>
#include "server/ServerSocket.h"

void *use_socket(void *ptr);

struct ThreadArg {
  // Used to send more than one argument 
  // to `transferData`, where we need two 
  // sockets
  ServerSocket one; /* socket descriptor */
  ServerSocket two; /* file descriptor */
};

int main(int argc, char* argv[]) {

  pthread_t thread1; 
  
  // Create two sockets
  ServerSocket *sock1;
  ServerSocket *sock2;

  // Create the structure to send as a void pointer
  // IDK if this is the way make this, but all I want 
  // is to create a `ThreadArg`.
  struct ThreadArg *arg = malloc(sizeof(struct ThreadArg)); 
  arg->one = *sock1;
  arg->two = *sock2;

  // Create the thread
  int thread1_return = pthread_create(&thread1, NULL, use_socket, (void *) arg);

  pthread_join(thread1, NULL);

  usleep(300);

  return 0;
}

void *use_socket(void *ptr) {
  struct ThreadArg *thArg = (struct ThreadArg *)ptr;
  pthread_exit(NULL);
}

