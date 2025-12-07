#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#define BYTES_PER_LINE 16



int main(int argc, char **argv)
{
  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE *in_file = stdin;
  
  if (argc == 2)
  {
    in_file = fopen(argv[1], "rb");
    if (!in_file)
    {
      perror("Error opening file");
      return EXIT_FAILURE;
    }
  }

  
}