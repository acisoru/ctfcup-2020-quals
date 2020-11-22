#include <stdio.h>
#include <string.h>

void vuln()
{
  char input[256];

  puts("[+] EASY PWN? [+]");
  printf("payload: ");
  fgets(input, 512, stdin);

  puts("You entered: ");
  printf(input);
  putchar('\n');
}

int main()
{
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);

  vuln();

  return 0;
}
