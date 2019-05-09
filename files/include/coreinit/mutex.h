#pragma once

#include "threadqueue.h"

struct OSMutex;

struct OSMutexLink
{
   OSMutex *next;
   OSMutex *prev;
};

#define OS_MUTEX_TAG 0x6D557458u

struct OSMutex
{
   //! Should always be set to the value OS_MUTEX_TAG.
   unsigned int tag;

   //! Name set by OSInitMutexEx.
   const char *name;

   unsigned int reserved;

   //! Queue of threads waiting for this mutex to unlock.
   OSThreadQueue queue;

   //! Current owner of mutex.
   void *owner; // TODO: OSThread

   //! Current recursion lock count of mutex.
   int count;

   //! Link used inside OSThread's mutex queue.
   OSMutexLink link;
};
