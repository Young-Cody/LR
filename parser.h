#ifndef PARSER_H
#define PARSER_H

#include"defs.h"
void input();
void print_sr();
void error();
void shift_reduce();
void parser(int);

extern C c;
extern map<I, int> I2index;
extern DFA dfa;
extern vector<map<string, vector<op>>> action;
extern vector<map<string, int>> Goto;
extern vector<string> s;
extern vector<string> input_buffer;
extern op o;
extern int is;
extern int ip;

#endif // !PARSER
