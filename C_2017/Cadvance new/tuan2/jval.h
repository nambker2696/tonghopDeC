typedef union {
int i;
long l;
float f;
double d;
void *v;
char *s;
char c;
} jval;

jval new_jval_i(int);
jval new_jval_f(float);
jval new_jval_d(double);
jval new_jval_s(char *);

int jval_i(jval);
float jval_f(jval);
double jval_d(jval);
char* jval_s(jval);
