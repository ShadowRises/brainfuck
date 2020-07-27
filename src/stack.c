/* stack -- simple stack data structure
   Copyright (C) 2020 Jean-Baptiste Loutfalla

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#include "stack.h"

#include <stdlib.h>

stack_t
init_stack ()
{
  return (stack_t) { .top = NULL };
}

void
free_stack (stack_t *stack)
{
  if (stack != NULL)
    {
      node_t *curr = stack->top;
      node_t *next;
      
      while (curr != NULL)
        {
          next = curr->next;
          free (curr);
          curr = next;
        }      
    }
}

void
push_stack (long pos, stack_t *stack)
{
  node_t *temp = (node_t*) malloc (sizeof (node_t));
  temp->position = pos;
  temp->next = NULL;
  
  if (stack->top == NULL)
    stack->top = temp;
  else
    {
      temp->next = stack->top;
      stack->top = temp;
    }
}

node_t
pop_stack (stack_t *stack)
{
  if (stack != NULL)
    {
      node_t *temp = stack->top->next;
      node_t res = *temp;
      
      res.next = NULL;
      
      free (stack->top);
      stack->top = temp;

      return res;
    }
  else
    return (node_t) { .position = -1,
                      .next = NULL };
}

node_t
top_stack (stack_t *stack)
{
  node_t res = *(stack->top);
  res.next = NULL;
  return res;
}
