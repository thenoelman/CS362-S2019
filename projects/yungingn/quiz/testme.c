#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	int i;
	int num;
	num = (rand() % 9) + 1;

	switch (num)
	{
		case 1:
			return '[';
		case 2:
			return '(';
		case 3:
			return '{';
		case 4:
			return ' ';
		case 5:
			return 'a';
		case 6:
			return 'x';
		case 7:
			return '}';
		case 8:
			return ')';
		case 9:
			return ']';
	}
}

char *inputString()
{
	int i;
	int num;
	num = (rand() % 8) + 1;

	switch (num)
	{
		case 1:
			return "reset";
		case 2:
			return "nope";
		case 3:
			return "whatever";
		case 4:
			return "something";
		case 5:
			return "banana";
		case 6:
			return "apple";
		case 7:
			return "peaches";
		case 8:
			return "pineapple";
	}
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
