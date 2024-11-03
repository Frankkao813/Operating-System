/*
 File: scheduler.C
 
 Author:
 Date  :
 
 */

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include "scheduler.H"
#include "thread.H"
#include "console.H"
#include "utils.H"
#include "assert.H"

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* METHODS FOR CLASS   S c h e d u l e r  */
/*--------------------------------------------------------------------------*/

Scheduler::Scheduler() {
    front = 0;
    rear = 0;
    ready_count = 0;
    zombie_count = 0;

}

void Scheduler::yield() {
    //if (count > 0) {
      // select the next thread, and check if the thread is valid
      Thread* next_thread = ready_queue[front];
      if (next_thread){
            Console::puts("Passing the control to the next thread ... We are passing to: \n");
            Console::puti(next_thread -> ThreadId());
            Console::puts("\n");
            Console::puts("The thread in the system...: ");
            Console::puti(ready_count);
            Console::puts("\n");
            ready_queue[front] = nullptr;
            front = (front + 1) % MAX_THREADS; // Move front to the next position circularly
            ready_count--;
            Thread::dispatch_to(next_thread);
            Console::puts("Scheduler yield is called. \n");
      }
      else{
        Console::puts("No available thread in the system to dispatch \n");
      }

    // cleaning the thread 
}

void Scheduler::resume(Thread * _thread) {

    if (ready_count < MAX_THREADS) {
        // add _thread at the ready queue
        ready_queue[rear] = _thread; 
        // circularly compute the rear index
        rear = (rear + 1) % MAX_THREADS;
        ready_count++;
        Console::puts("Scheduler resume is called. \n");
    } else {
        // when the queue is full, output error message  (should not happen)
        Console::puts("Ready Queue is Full. \n");
        assert(false);
    }

}

void Scheduler::add(Thread * _thread) {
  resume(_thread);
  Console::puts("Scheduler add is called. \n");
}

void Scheduler::terminate(Thread* _thread) {
    // push the thread to zombie queue
    zombie_queue[zombie_count++] = _thread;
    Console::puts("Scheduler terminate is called.\n");
}

void Scheduler::terminate_ready_thread(Thread* _thread) {
    // goal: remove the thread from the ready queue
    // First keep the temp_queue to store the thread that is valid
    Thread* temp_queue[MAX_THREADS];
    int temp_count = 0;

    for (int i = 0; i < ready_count; i++) {
        // Remove each thread from the front of the ready queue, remove in a circular way
        Thread* cur = ready_queue[front];
        front = (front + 1) % MAX_THREADS; 

        // If the current thread is not the one to terminate, keep it in temp_queue
        if (cur->ThreadId() != _thread->ThreadId()) {
            temp_queue[temp_count++] = cur;
        }
    }

    // Rebuild ready_queue from temp_queue
    front = 0;
    rear = temp_count;
    ready_count = temp_count;
    for (int i = 0; i < temp_count; i++) {
        ready_queue[i] = temp_queue[i];
    }

    Console::puts("Scheduler terminate thread in ready queue is called.\n");

}

