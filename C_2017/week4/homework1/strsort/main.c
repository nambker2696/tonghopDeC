#include <stdio.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

// strsort


// void main()
// {
//   JRB b;
//   JRB bn;
//   IS is;

//   is = new_inputstruct(NULL);
//   b = make_jrb();
//   printf("Program strsort");
//   while (get_line(is) >= 0) {
//     (void) jrb_insert_str(b, strdup(is->text1), new_jval_v(NULL));
//   }

//   jrb_traverse(bn, b) {
//     printf("%s", jval_s(bn->key));
//   }
// }


// strsort1

// #include <stdio.h>
// #include <string.h>
// #include "jrb.h"
// #include "fields.h"

// main()
// {
//   JRB b;
//   JRB bn;
//   IS is;

//   is = new_inputstruct(NULL);
//   b = make_jrb();

//   while (get_line(is) >= 0) {
//     (void) jrb_insert_str(b, strdup(is->text1), new_jval_v(NULL));
//   }

//   jrb_rtraverse(bn, b) {
//     printf("%s", jval_s(bn->key));
//   }
// }





// strsort2
#include <stdio.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

int revcomp(Jval k1, Jval k2)
{
  return -strcmp(k1.s, k2.s);
}

int main()
{
  JRB b;
  JRB bn;
  IS is;

  is = new_inputstruct("doc.txt");
  b = make_jrb();

  while (get_line(is) >= 0) {
    (void) jrb_insert_gen(b, new_jval_s(strdup(is->text1)),
                               new_jval_v(NULL), revcomp);
  }

  jrb_traverse(bn, b) {
    printf("%s", jval_s(bn->key));
  }
}
