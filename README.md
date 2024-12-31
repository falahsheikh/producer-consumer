# Producer-Consumer Problem (POSIX)

This program implements the classic producer-consumer problem using POSIX threads, semaphores, and mutexes. It demonstrates synchronization between a producer and a consumer interacting with a shared buffer.

## How It Works

- **Producer** generates random items and inserts them into the buffer.
- **Consumer** removes items from the buffer and processes them.
- **Synchronization** is handled using:
  - A mutex to ensure mutual exclusion when accessing the buffer.
  - Semaphores to manage the buffer slots (empty and full).

## Requirements

- GCC or any C compiler that supports POSIX threads and semaphores.
- POSIX libraries for thread and semaphore support.

## Compilation

To compile the program, use the following command:

```bash
gcc -o producer_consumer producer_consumer.c -pthread -lrt
