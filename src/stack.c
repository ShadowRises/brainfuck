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
push_stack (long s_pos, long e_pos, stack_t *stack)
{
  node_t *temp = (node_t*) malloc (sizeof (node_t));
  temp->start_position = s_pos;
  temp->end_position = e_pos;
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
  node_t res = { .start_position = -1,
                 .end_position = -1 };
  
  if (stack != NULL && stack->top != NULL)
    {
      node_t *temp = stack->top->next;
      if (temp != NULL)
        res = *temp;
      
      res.next = NULL;
      
      free (stack->top);
      stack->top = temp;

      return res;
    }
  else
    return res; 
}

node_t
top_stack (stack_t *stack)
{
  node_t res;
  if (stack->top)
    res = *(stack->top);
  else
    res = (node_t) { .start_position = -1,
                     .end_position = -1 };
  res.next = NULL;
  return res;
}

void
update_top_stack (long end, stack_t *stack)
{
  if (stack != NULL && stack->top != NULL)
    stack->top->end_position = end;
}
