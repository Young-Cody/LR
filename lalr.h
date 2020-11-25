#pragma once
#include"defs.h"

struct cmp {
	bool operator()(const I &l, const I &r) const;
};

void core_union();
void compute_action_goto_lalr();
void print_C_lalr();
void print_I_lalr(I*);
void print_action_lalr();
void print_goto_lalr();
