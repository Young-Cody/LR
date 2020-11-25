#ifndef CFG_H
#define CFG_H

#include"defs.h"


void cfg_init();
void input_cfg();
void insert(FIFO *, string, set<string> *, bool *);
void init_first();
void init_follow();
set<string> get_first(vector<string>*);
void print_first();
void print_follow();

extern string start;
extern set<string> NT;
extern set<string> symbol;
extern h2bs_t h2bs;
extern CFG G;
extern FIFO FIRST;
extern FIFO FOLLOW;

#endif // !CFG