#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "a.h"

void printS(S s) {
    void** ptr = (void**) s->arr;
    printf("ptr: %p    v:%d    n:%d  arr:", s, s->val, s->sz);
    for (int i = 0; i < s->sz; i++) {
        printf(" %p", ptr[i]);
    }
    printf("\n");
}

S mkS() {
    printf("sz: %d    arrOff:%ld\n", sizeof(struct s), offsetof(struct s, arr));
    int sz = 2;
    S s0 = malloc(offsetof(struct s, arr)  + sz * sizeof(S));
    s0->sz = sz;
    s0->val = 0;

    S s1 = malloc(sizeof(struct s));
    s1->sz = 0;
    s1->val = 10;
    ((S*)(s0->arr))[0] = s1;

    S s2 = malloc(sizeof(struct s));
    s2->sz = 0;
    s2->val = 20;
    ((S*)(s0->arr))[1] = s2;

    return s0;
}

void printSS(SS ss) {
    if (0 == ss->t) {
        printf("ptr: %p    v:%d\n", ss, ss->val);
    } else if (1 == ss->t) {
        printf("ptr: %p    ref:%p\n", ss, ss->val, ss->ref);
    } else if (2 == ss->t) {
        void** ptr = (void**) ss->arr;
        printf("ptr: %p    n:%d  arr:", ss, ss->val, ss->sz);
        for (int i = 0; i < ss->sz; i++) {
            printf(" %p", ptr[i]);
        }
        printf("\n");
    }
}

SS mkSS() {
    SS ss0 = malloc(offsetof(struct ss, ref)  + sizeof(SS));
    ss0->t = 1;

    SS s11 = malloc(sizeof(struct ss));
    s11->t = 0;
    s11->val = 11;
    SS s12 = malloc(sizeof(struct ss));
    s12->t = 0;
    s12->val = 12;

    SS s10 = malloc(offsetof(struct ss, arr)  + 2 * sizeof(SS));
    s10->t = 2;
    s10->sz = 2;
    ((SS*)(s10->arr))[0] = s11;
    ((SS*)(s10->arr))[1] = s12;

    ss0->ref = s10;

    return ss0;
}

void printAllSS(SS ss) {
    printSS(ss);
    SS r = ss->ref;
    printSS(r);
    printSS(((SS*)(r->arr))[0]);
    printSS(((SS*)(r->arr))[1]);
}

// void main() {
//     S s = mkS();
//     printS(s);
//     printS(((S*)(s->arr))[0]);
//     printS(((S*)(s->arr))[1]);

    // SS ss = mkSS();
    // printSS(ss);
    // SS r = ss->ref;
    // printSS(r);
    // printSS(((SS*)(r->arr))[0]);
    // printSS(((SS*)(r->arr))[1]);
// }
