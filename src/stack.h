/* Stack data structure utility
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

#ifndef STACK_H
#define STACK_H

typedef enum
  {
   OPEN_BRACK,
   CLOSE_BRACK
  } TYPE_STACK;

typedef struct node_t
{
  long position;
  struct node_t *next;
} node_t;

typedef struct
{
  node_t *top;
} stack_t;

stack_t
init_stack ();

void
free_stack (stack_t*);

void
push_stack (long, stack_t*);

node_t
pop_stack (stack_t*);

node_t
top_stack (stack_t*);

#endif /* STACK_H */
