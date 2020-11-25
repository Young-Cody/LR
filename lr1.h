#ifndef LR1_H
#define	LR1_H

#include"defs.h"

I closure_lr1(I*);
I move_lr1(I*, string);
int get_index_lr1(I*);
void compute_dfa_lr1();
void compute_action_goto_lr1();
void print_C_lr1();
void print_I_lr1(I*);
void print_action_lr1();
void print_goto_lr1();

extern C c;
extern map<I, int> I2index;
extern DFA dfa;
extern vector<map<string, vector<op>>> action;
extern vector<map<string, int>> Goto;

#endif // 

