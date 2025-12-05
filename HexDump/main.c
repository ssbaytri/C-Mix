#include <stdio.h>
#include <stdlib.h>

int main()
{
  int c;
  while ((c = getchar()) != EOF)
  {
    printf("%c", c);
  }
  return (0);
}
