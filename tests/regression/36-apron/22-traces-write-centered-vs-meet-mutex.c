// SKIP PARAM: --set ana.activated[+] apron --set ana.path_sens[+] threadflag --enable ana.sv-comp.functions --set ana.relation.privatization mutex-meet
extern int __VERIFIER_nondet_int();

#include <pthread.h>
#include <goblint.h>

int g = 0;
int h = 0;
int i = 0;
pthread_mutex_t A = PTHREAD_MUTEX_INITIALIZER; // h <= g
pthread_mutex_t B = PTHREAD_MUTEX_INITIALIZER; // h == g
pthread_mutex_t C = PTHREAD_MUTEX_INITIALIZER;

void *t_fun(void *arg) {
  int x = __VERIFIER_nondet_int(); //rand
  int y = __VERIFIER_nondet_int(); //rand
  int z = __VERIFIER_nondet_int(); //rand
  if (x < 1000) { // avoid overflow
    pthread_mutex_lock(&C);
    pthread_mutex_lock(&A);
    x = g;
    y = h;
    __goblint_check(y <= x);
    pthread_mutex_lock(&B);
    __goblint_check(x == y); // mutex-meet succeeds, (now-defunct) write unknown
    pthread_mutex_unlock(&B);
    i = x + 31;
    z = i;
    __goblint_check(z >= x); // TODO ((now-defunct) write succeeds, mutex-meet unknown)
    pthread_mutex_unlock(&A);
    pthread_mutex_unlock(&C);
  }
  return NULL;
}

int main(void) {
  int x = __VERIFIER_nondet_int(); //rand
  if (x > -1000) { // avoid underflow
    pthread_t id;
    pthread_create(&id, NULL, t_fun, NULL);

    pthread_mutex_lock(&B);
    pthread_mutex_lock(&A);
    i = 11;
    g = x;
    h = x - 17;
    pthread_mutex_unlock(&A);
    pthread_mutex_lock(&A);
    h = x;
    pthread_mutex_unlock(&A);
    pthread_mutex_unlock(&B);
    pthread_mutex_lock(&C);
    i = 3;
    pthread_mutex_unlock(&C);
  }
  return 0;
}
