#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void vuln(int test)
{
  char input[256];
  double array[64];
  int size = 0;

  if (test != 0xdeadbeef)
    exit(0);

  puts("[+] BABY PWN [+]");
  printf("Enter number of floats: ");
  scanf("%d", &size);

  if (size > 64)
  {
    puts("HACKER");
    exit(0);
  }

  puts("pwn, pwn, pwn, pwn\nEnter floats:");
  for(size_t i = 0; i < (size_t)size; i++)
  {
    scanf("%lf", &array[i]);
    if (i >= 128)
      break;
  }

  return;
}

int main()
{
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);

  vuln(0xdeadbeef);
}
