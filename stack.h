#include <stdint.h>

typedef struct STACK {
  int top;
  unsigned capacity;
  uint16_t* array;
} stack16;

extern stack16* create_stack(unsigned capacity);
extern bool isFull(stack16* s);
extern bool isEmpty(stack16* s);
extern void push(stack16* s, uint16_t item);
extern uint16_t pop(stack16* s);
