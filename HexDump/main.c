#include <stdio.h>

int main()
{
  int c;
  int mem_index = 0;
  while ((c = getchar()) != EOF)
  {
    if (mem_index % 0x10 == 0x0)
    {
      printf("%08x ", mem_index);
    }
    printf("%02x ", c);
    mem_index++;
    if (mem_index % 0x10 == 0x0)
      printf("\n");
  }
  printf("\n");
  return (0);
}
