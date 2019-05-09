#pragma once

struct OSThreadQueue
{
   void *head; // TODO: OSThread
   void *tail; // TODO: OSThread
   void *parent;
   unsigned int reserved;
};
