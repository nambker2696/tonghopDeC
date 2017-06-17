//Soundex code as implemented by Kevin Setter, 8/27/97
//Usage: soundex [-f] <name1> <name2> ...

//-f treats the first character of name just like the others.
//If no names are specified in the arguments, soundex will read
//from the standard input until end of file is encountered.
//Note that names of two characters or less are disregarded.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXNAMELEN 50
#define MAXLINELEN 500

int FullFlag;

//Deletes the first word from a string
char *delfirstword(char *s)
{
char *sout = (char *)malloc(strlen(s));
int i = 0, i2 = 0;

if (s[0] == (char)NULL) return s;
while (isspace(s[i])) i++;
while ((!isspace(s[i])) && (s[i] != (char)NULL)) i++;
if (s[i] == (char)NULL) return "";
while ((isspace(s[i])) && (s[i] != (char)NULL)) i++;
while (s[i] != (char)NULL)
{
sout[i2] = s[i];
i++; i2++;
}
sout[i2] = (char)NULL;
return sout;
}

//Returns the soundex equivalent to In
char *Soundex(char *In)
{
int Iin, Iout;
char C, PrevDig, *Out = (char *)malloc(10);

if (FullFlag)
{Iin = 0; Iout = 0; PrevDig = '*';}
else
{Iin = 1; Iout = 1;
Out[0] = tolower(In[0]); PrevDig = Out[0];}

while ((In[Iin] != (char)NULL) && (Iout <= 4))
{
In[Iin] = tolower(In[Iin]);
switch (In[Iin])
{
case 'b' : C = '1'; break;
case 'p' : C = '1'; break;
case 'f' : C = '1'; break;
case 'v' : C = '1'; break;
case 'c' : C = '2'; break;
case 's' : C = '2'; break;
case 'k' : C = '2'; break;
case 'g' : C = '2'; break;
case 'j' : C = '2'; break;
case 'q' : C = '2'; break;
case 'x' : C = '2'; break;
case 'z' : C = '2'; break;
case 'd' : C = '3'; break;
case 't' : C = '3'; break;
case 'l' : C = '4'; break;
case 'm' : C = '5'; break;
case 'n' : C = '5'; break;
case 'r' : C = '6'; break;
default : C = '*';
}
if ((C != PrevDig) && (C != '*'))
{
Out[Iout] = C;
PrevDig = Out[Iout];
Iout++;
}
Iin++;
}

if (Iout < 4)
for (Iin=Iout; Iin<4; Iin++)
Out[Iin] = '0';

Out[4] = NULL;
return Out;
}

//Main function
int main(int argc, char *argv[])
{
char *Name = (char *)malloc(MAXNAMELEN), *Line = (char *)malloc(MAXLINELEN);
int I;

FullFlag = 0;

if (argc >= 2)
{
if (!strcmp(argv[1], "-f"))
FullFlag = 1;
if ((!strcmp(argv[1], "-h")) || (!strcmp(argv[1], "-?")) ||
(!strcmp(argv[1], "?")))
{
printf("\nSoundex code as implemented by Kevin Setter, 8/27/97\n");
printf("Usage: soundex [-f] <name1> <name2> ...\n\n");
printf("-f treats the first character of name just like the others.\n");
printf("If no names are specified in the arguments, soundex will read\n");
printf("from the standard input until end of file is encountered.\n");
printf("Note that names of two characters or less are disregarded.\n");
}
}


if (FullFlag && (argc >= 3))
{
for (I=2; I<=(argc-1); I++)
if (strlen(argv[I]) >= 3)
printf("%s ", Soundex(argv[I]));
printf("\n");
return 0;
}
if ((!FullFlag) && (argc >= 2))
{
for (I=1; I<=(argc-1); I++)
if (strlen(argv[I]) >= 3)
printf("%s ", Soundex(argv[I]));
printf("\n");
return 0;
}

while (gets(Line) != NULL)
{
while (strcmp(Line, ""))
{
sscanf(Line, "%s", Name);
if (strlen(Name) >= 3)
printf("%s ", Soundex(Name));
strcpy(Line, delfirstword(Line));
}
printf ("\n");
}

free(Line); free(Name);
return 0;
}
