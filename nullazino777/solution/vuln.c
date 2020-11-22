#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account
{
  char name[512];
  int wins;
};

struct Account **list_users;

int current_id = -1;

void regist_menu()
{
  puts("[+++] NULLazino777 [+++]");
  puts("[1] Login.");
  puts("[2] Register.");
  printf("#> ");
}

void prize()
{
  int id;
  puts("[!!!] Congratz! [+++]");
  puts("You prize: ");
  scanf("%d", &id);
  getchar();

  if ((id < 0) || (id > 15))
  {
    puts("[!] Wrong uid!");
    exit(0);
  }

  puts("Content:");
  fgets(list_users[id], 511, stdin);
}

void test_luck()
{
  puts("[+] 777 [+]");
  sleep(1);
  puts("[3]");
  sleep(0.5);
  puts("[2]");
  sleep(0.5);
  puts("[1]");
  sleep(0.5);

  int win = rand();

  if (win != 0)
  {
    puts("[!!!!!] !You loose! [+++]");
    exit(0);
  }
  else
  {
    list_users[current_id]->wins++;
    puts("[++] YOU WIN!");
    printf("[+] You need to win %d times to get you prize!", 10-list_users[current_id]->wins);
  }

  if (list_users[current_id]->wins == 10)
    prize();
}

void regist()
{
  char name[512];
  int id;
  puts("Hello, stranger!");

  puts("Enter username: ");
  fgets(name, 511, stdin);

  puts("Enter user id:");
  scanf("%d", &id);

  if ((id < 0) || (id > 15))
  {
    puts("[!] Wrong uid!");
    exit(0);
  }

  list_users[id] = malloc(sizeof(struct Account));
  strncpy(list_users[id]->name, name, 512);
  list_users[id]->wins = 0;

  current_id = id;
}

void menu()
{
  puts("[+++] NULLazino777 [+++]");
  puts("[1] Test you luck.");
  puts("[2] Print account info.");
  puts("[3] Delete account.");
  puts("[4] Log out.");
  printf("[/root/task]#> ");
}

void baaaaaackd0000000000r()
{
  long long int ind;
  puts("[+] If you find me, you are a hacker.");
  puts("[+] Now you can delete any account:");

  scanf("%lld", &ind);

  list_users[ind] = NULL;
}

void print_info()
{
  puts("You account:");
  printf("[NAME]: %s\n", list_users[current_id]->name);
  printf("[WINS]: %d\n", list_users[current_id]->wins);
}

int main()
{
  int input;

  list_users = malloc(sizeof(void *)*16);

  memset(list_users, 0, sizeof(void *)*16);

  srand(time(NULL));

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);

  while (1)
  {
    regist_menu();
    scanf("%d", &input);
    getchar();

    if (input == 1)
    {
      puts("Enter you id:");
      scanf("%d", &current_id);
      if ((current_id < 0) || (current_id > 15))
      {
          puts("Wrong current id!");
          exit(0);
      }
      if (list_users[current_id] == NULL)
      {
        puts("User not created!");
        exit(0);
      }
    } else if (input == 2)
    {
      regist();
    } else if (input == 3)
    {
      puts("Goodbye!");
      exit(0);
    } else
    {
      puts("Wrong option!");
      exit(0);
    }

    if (current_id == -1)
    {
      puts("Wrong current id!");
      exit(0);
    }

    while (1)
    {
      menu();
      scanf("%d", &input);
      getchar();

      if (input == 1)
      {
        test_luck();
      } else if (input == 2)
      {
        print_info();
      } else if (input == 3)
      {
        free(list_users[current_id]);
        break;
      } else if (input == 4)
      {
        puts("Bye!");
        break;
      } else if (input == 31337)
      {
        baaaaaackd0000000000r();
      } else
      {
        puts("Wrong option!");
        exit(0);
      }
    }
  }

  return 0;
}
