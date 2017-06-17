jval new_jval_i(int i) { jval j; j.i = i; return j; }
jval new_jval_l(long l) { jval j; j.l = l; return j; }
jval new_jval_f(float f) { jval j; j.f = f; return j; }
jval new_jval_d(double d) { jval j; j.d = d; return j; }
jval new_jval_v(void *v) { jval j; j.v = v; return j; }

int jval_i(jval j) { return j.i; }
long jval_l(jval j) { return j.l; }
float jval_f(jval j) { return j.f; }
double jval_d(jval j) { return j.d; }
void *jval_v(jval j) { return j.v; }
