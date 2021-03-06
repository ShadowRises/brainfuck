/* brainfuck -- read and interpret Brainfuck programming language
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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "stack.h"

#define PROGRAM_NAME ("brainfuck")

#define ERR_AND_DIE(X)     \
  if (X == NULL)           \
    {                      \
      perror ("Error");    \
      exit (EXIT_FAILURE); \
    }

#define BUFF_SIZE 30000

void
usage (int status)
{
  printf ("\
Usage: %s FILE\n\
", PROGRAM_NAME);

  fputs ("\
Read a FILE written in Brainfuck programming language and interpret it.\n\
", stdout);
  exit (status);
}

int
main (int argc, char* argv[])
{
  uint8_t BUFF[BUFF_SIZE] = { 0 };
  uint8_t *ptr = BUFF;
  
  int c;
  FILE* file;
  stack_t stack;
  
  if (argc < 2)
    usage (EXIT_FAILURE);
  else if (strncmp (argv[1], "-h", 2) == 0 ||
           strncmp (argv[1], "--help", 2) == 0)
    usage (EXIT_SUCCESS);

  file = fopen (argv[1], "r");
  ERR_AND_DIE (file);

  stack = init_stack ();
  while ((c = fgetc (file)) != EOF)
    {
      node_t top;
      switch (c)
        {
        case '+':
          (*ptr)++;
          break;

        case '-':
          (*ptr)--;
          break;

        case '>':
          if (ptr == BUFF + BUFF_SIZE - 1)
            ptr = BUFF;
          else
            ptr++;
          break;

        case '<':
          if (ptr == BUFF)
            ptr = BUFF + BUFF_SIZE - 1;
          else
            ptr--;
          break;

        case '.':
          printf ("%c", *ptr);
          break;

        case ',':
          *ptr = fgetc (stdin);
          break;

        case '[':
          top = top_stack (&stack);
          
          if (*ptr != 0)
            push_stack (ftell(file), -1, &stack);
          else if (top.end_position != -1 && ftell (file) == top.start_position)
              fseek (file, top.end_position, SEEK_SET);
          else
            {
              while ((c = fgetc (file)) != EOF)
                {
                  if (c == '[')
                    {
                      push_stack (ftell (file), -1, &stack);
                      continue;
                    }
                  else if (c == ']')
                    {
                      node_t pop = pop_stack (&stack);
                      if (pop.start_position == top.start_position)
                        break;
                    }
                }
            }
          break;

        case ']':
          top = top_stack (&stack);
          if (top.start_position == -1)
            {
              fprintf (stderr,
                       "Error : no matching '[' for ']' at %ld\n",
                       ftell (file));
              free_stack (&stack);
              exit (-1);
            }
          else if (*ptr != 0)
            {

              if (top.end_position == -1)
                  update_top_stack (ftell (file), &stack);
              
              fseek(file, top.start_position, SEEK_SET);
            }
          else
            pop_stack (&stack);

          break;
        
      
        default:
          break;
        }
    }
  
  fclose (file);
  free_stack (&stack);
  
  return EXIT_SUCCESS;
}
