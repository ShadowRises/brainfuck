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
#include <string.h>

#define PROGRAM_NAME "brainfuck"

#define ERR_AND_DIE(X)    \
  if (X == NULL)          \
    {                     \
      perror("Error");    \
      exit(EXIT_FAILURE); \
    }

void
usage (int status)
{
  printf ("\
Usage: %s FILE\n\
", PROGRAM_NAME);

  fputs ("\
Read a FILE writen in Brainfuck programming language and interpret it.\n\
", stdout);
  exit (status);
}

int
main (int argc, char* argv[])
{
  FILE* file;
  
  if (argc < 2)
    usage (EXIT_FAILURE);
  else if (strncmp (argv[1], "-h", 2) == 0 ||
           strncmp (argv[1], "--help", 2) == 0)
    usage (EXIT_SUCCESS);

  file = fopen (argv[1], "r");
  ERR_AND_DIE (file);
  fclose (file);
  
  return EXIT_SUCCESS;
}
