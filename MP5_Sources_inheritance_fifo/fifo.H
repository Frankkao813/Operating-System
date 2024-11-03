#define MAX_THREADS 5

#ifndef FIFO_SCHEDULER_H
#define FIFO_SCHEDULER_H

#include "scheduler.H"
#include "thread.H"  // Include any additional dependencies

class FIFOScheduler : public Scheduler {
/* The scheduler may need private members... */
private:
   Thread* ready_queue[MAX_THREADS]; // Array for the ready queue (use circular queue)
   Thread* zombie_queue[MAX_THREADS]; // Array for the zombite queue (just a simple array to append element)
   int front;                        // Index for dequeueing
   int rear;                         // Index for enqueueing
   int ready_count;                  // Number of threads in the queue
   int zombie_count;                 // Number of threads in the zombie queue

  
public:
    FIFOScheduler();
    void yield() override;
    void resume(Thread * _thread) override;
    void add(Thread * _thread) override;
    void terminate(Thread * _thread) override;
    void terminate_ready_thread(Thread* _thread)  override;
};
	

#endif