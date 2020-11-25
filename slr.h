#ifndef SLR_H
#define	SLR_H

#include"defs.h"

I closure_slr(I *);
I move_slr(I *, string);
int get_index_slr(I*);
void compute_dfa_slr();
void compute_action_goto_slr();
void print_C_slr();
void print_I_slr(I *);
void print_action_slr();
void print_goto_slr();

extern C c;
extern map<I, int> I2index;
extern DFA dfa;
extern vector<map<string, vector<op>>> action;
extern vector<map<string, int>> Goto;

#endif // 
