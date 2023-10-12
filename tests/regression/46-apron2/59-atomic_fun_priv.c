// PARAM: --enable ana.sv-comp.functions --set ana.activated[+] apron --set ana.relation.privatization mutex-meet --set ana.base.privatization none
#include <pthread.h>
#include <goblint.h>

int myglobal = 5;

// atomic by function name prefix
void __VERIFIER_atomic_fun() {
  __goblint_check(myglobal == 5);
  myglobal++;
  __goblint_check(myglobal == 6);
  myglobal--;
  __goblint_check(myglobal == 5);
}

void *t_fun(void *arg) {
  __VERIFIER_atomic_fun();
  return NULL;
}

int main(void) {
  pthread_t id;
  pthread_create(&id, NULL, t_fun, NULL);
  __goblint_check(myglobal == 5);
  __VERIFIER_atomic_begin();
  __goblint_check(myglobal == 5);
  __VERIFIER_atomic_end();
  pthread_join (id, NULL);
  return 0;
}
