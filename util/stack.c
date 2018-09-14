#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"

stack16* create_stack(unsigned capacity) {
  stack16* s = malloc(sizeof(stack16));
  s -> capacity = capacity;
  s -> top = -1;
  s -> array = malloc(s -> capacity * sizeof(uint16_t));
  return s;
}

bool isFull(stack16* s) { return s -> top == s -> capacity - 1; }
bool isEmpty(stack16* s) { return s -> top == -1; }

void push(stack16* s, uint16_t item) {
  if (isFull(s)) return;
  s -> array[++s -> top] = item;
}

uint16_t pop(stack16* s) {
  if(isEmpty(s)) exit(255);
  return s -> array[s -> top--];
}
