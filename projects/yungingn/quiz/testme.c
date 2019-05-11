#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	int i;
	int num;
	num = (rand() % 33) + 1;

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
		case 10:
			return 'b';
		case 11:
			return 'c';
		case 12:
			return 'd';
		case 13:
			return 'e';
		case 14:
			return 'f';
		case 15:
			return 'g';
		case 16:
			return 'h';
		case 17:
			return 'i';
		case 18:
			return 'j';
		case 19:
			return 'k';
		case 20:
			return 'l';
		case 21:
			return 'm';
		case 22:
			return 'n';
		case 23:
			return 'o';
		case 24:
			return 'p';
		case 25:
			return 'q';
		case 26:
			return 'r';
		case 27:
			return 's';
		case 28:
			return 't';
		case 29:
			return 'u';
		case 30:
			return 'v';
		case 31:
			return 'w';
		case 32:
			return 'x';
		case 33:
			return 'y';
	}
}

char *inputString()
{
	int num;
	num = (rand() % 100) + 1;

	switch (num)
	{
		case 1:
			return "reset";
		case 2:
			return "rabat";
		case 3:
			return "rabbi";
		case 4:
			return "rabic";
		case 5:
			return "rabic";
		case 6:
			return "raced";
		case 7:
			return "racer";
		case 8:
			return "races";
		case 9:
			return "racks";
		case 10:
			return "racon";
		case 11:
			return "radar";
		case 12:
			return "radii";
		case 13:
			return "radio";
		case 14:
			return "radix";
		case 15:
			return "radon";
		case 16:
			return "raffs";
		case 17:
			return "rafts";
		case 18:
			return "ragas";
		case 19:
			return "raged";
		case 20:
			return "rages";
		case 21:
			return "raggy";
		case 22:
			return "ragis";
		case 23:
			return "raias";
		case 24:
			return "raids";
		case 25:
			return "rails";
		case 26:
			return "rains";
		case 27:
			return "rainy";
		case 28:
			return "raise";
		case 29:
			return "rajah";
		case 30:
			return "rajas";
		case 31:
			return "rajes";
		case 32:
			return "raked";
		case 33:
			return "rakee";
		case 34:
			return "raker";
		case 35:
			return "rakes";
		case 36:
			return "rakis";
		case 37:
			return "rales";
		case 38:
			return "rally";
		case 39:
			return "ralph";
		case 40:
			return "ramee";
		case 41:
			return "ramen";
		case 42:
			return "ramet";
		case 43:
			return "ramie";
		case 44:
			return "rammy";
		case 45:
			return "ramps";
		case 46:
			return "ramus";
		case 47:
			return "rance";
		case 48:
			return "ranch";
		case 49:
			return "rands";
		case 50:
			return "randy";
		case 51:
			return "ranee";
		case 52:
			return "range";
		case 53:
			return "rangy";
		case 54:
			return "ranid";
		case 55:
			return "ranis";
		case 56:
			return "ranks";
		case 57:
			return "rants";
		case 58:
			return "raped";
		case 59:
			return "raper";
		case 60:
			return "rapes";
		case 61:
			return "raphe";
		case 62:
			return "rapid";
		case 63:
			return "rared";
		case 64:
			return "rarer";
		case 65:
			return "rares";
		case 66:
			return "rased";
		case 67:
			return "raser";
		case 68:
			return "rases";
		case 69:
			return "rasps";
		case 70:
			return "raspy";
		case 71:
			return "ratal";
		case 72:
			return "ratan";
		case 73:
			return "ratch";
		case 74:
			return "rated";
		case 75:
			return "ratel";
		case 76:
			return "rater";
		case 77:
			return "rates";
		case 78:
			return "rathe";
		case 79:
			return "ratio";
		case 80:
			return "ratos";
		case 81:
			return "ratty";
		case 82:
			return "raved";
		case 83:
			return "ravel";
		case 84:
			return "raven";
		case 85:
			return "raver";
		case 86:
			return "raves";
		case 87:
			return "ravin";
		case 88:
			return "rawer";
		case 89:
			return "rawin";
		case 90:
			return "rawly";
		case 91:
			return "raxed";
		case 92:
			return "raxes";
		case 93:
			return "rayah";
		case 94:
			return "rayas";
		case 95:
			return "rayed";
		case 96:
			return "rayon";
		case 97:
			return "razed";
		case 98:
			return "razee";
		case 99:
			return "razer";
		case 100:
			return "razes";
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
