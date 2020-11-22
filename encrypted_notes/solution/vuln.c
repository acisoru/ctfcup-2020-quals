#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *notes[8];

void menu()
{
  puts("|======MENU======|");
  puts("[1] Create Note.");
  puts("[2] Read Note.");
  puts("[3] Update Note.");
  puts("[4] Delete Note.");
  puts("[5] Exit.");
  printf("[/root] #> ");
}

void create()
{
  char key;
  int idx;
  unsigned int size;

  puts("[!] Enter index:");
  scanf("%d", &idx);
  getchar();

  if ((idx < 0) || (idx > 7))
    exit(0);

  if (notes[idx] != NULL)
    exit(0);

  puts("[!] Enter size:");
  scanf("%u", &size);
  getchar();

  notes[idx] = malloc(size);

  puts("[!] Enter encryption key:");
  scanf("%c", &key);
  getchar();

  puts("[!] Enter content:");
  fgets(notes[idx], size, stdin);

  for(int i = 0; i < size; i++)
    notes[idx][i] ^= key;
}

void view()
{
  char key;
  int idx;

  puts("[!] Enter index:");
  scanf("%d", &idx);
  getchar();

  if ((idx < 0) || (idx > 7))
    exit(0);

  if (notes[idx] == NULL)
    exit(0);


  int size = strlen(notes[idx]);

  puts("[!] Enter encryption key:");
  scanf("%c", &key);
  getchar();

  for(int i = 0; i < size; i++)
    notes[idx][i] ^= key;

  puts("[+] Content:");
  printf("%s\n", notes[idx]);

  for(int i = 0; i < size; i++)
    notes[idx][i] ^= key;

}

void update()
{
  char key;
  int idx;

  puts("[!] Enter index:");
  scanf("%d", &idx);
  getchar();

  if ((idx < 0) || (idx > 7))
    exit(0);

  if (notes[idx] == NULL)
    exit(0);

  int size = strlen(notes[idx]);

  puts("[!] Enter encryption key:");
  scanf("%c", &key);
  getchar();

  puts("[!] Enter content:");
  fgets(notes[idx], size, stdin);
  //notes[idx][strlen(notes[idx] -1)] = '\0';


  for(int i = 0; i < size; i++)
    notes[idx][i] ^= key;


}

void delete()
{
  char key;
  int idx;

  puts("[!] Enter index:");
  scanf("%d", &idx);
  getchar();

  if ((idx < 0) || (idx > 7))
    exit(0);

  if (notes[idx] == NULL)
    exit(0);

  free(notes[idx]);

  notes[idx] = NULL;
}

int main()
{
  int input;
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);

  while (1)
  {
    menu();
    scanf("%d", &input);
    getchar();
    switch(input)
    {
      case 1:
        create();
        break;
      case 2:
        view();
        break;
      case 3:
        update();
        break;
      case 4:
        delete();
        break;
      case 5:
        puts("[+] BYE!");
        exit(0);
        break;
      default:
        puts("[!] WRONG OPTION!");
    }
  }

  return 0;
}
