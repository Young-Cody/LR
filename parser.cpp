#include"parser.h"
#include"cfg.h"
#include"lr1.h"
#include"lalr.h"
#include"slr.h"
#include<iomanip>
#include<iostream>
using namespace std;

C c;
map<I, int> I2index;
DFA dfa;
ACTION action;
GOTO Goto;
vector<string> s;
vector<string> input_buffer;
op o;
int is;
int ip;

void input()
{
	s.clear();
	input_buffer.clear();
	int n;
	cin >> n;
	while (n--)
	{
		string str;
		cin >> str;
		input_buffer.push_back(str);
	}
	ip = 0;
	s.push_back("0");
	input_buffer.push_back("$");
}

void print_sr()
{
	for (auto& str : s)
		cout << str << ' ';
	cout << setw(10) << ' ';
	for (int i = ip; i < input_buffer.size(); i++)
		cout << input_buffer[i] << ' ';
	cout << setw(10) << ' ';
	if (o.type == 0)
		cout << "shift\n";
	else if (o.type == 1)
	{
		cout << "reduce ";
		cout << G[o.property].head << " -> ";
		for (auto& str : G[o.property].body)
			cout << str << ' ';
		cout << "\n";
	}
	else if (o.type == 2)
		cout << "accept\n";
	else if (o.type == 3)
		cout << "error\n";
}

void error()
{
	cerr << "parse error\n";
}

void shift_reduce()
{
	while (1)
	{
		int state = atoi(s.back().c_str());
		string a = input_buffer[ip];
		if (action[state].find(a) == action[state].end())
		{
			o.type = 3;
			print_sr();
			error();
			break;
		}
			
		o = action[state][a][0];
		if (o.type == 0)
		{
			print_sr();
			s.push_back(a);
			s.push_back(to_string(o.property));
			ip++;
		}
		else if (o.type == 1)
		{
			print_sr();
			int n;
			if(G[o.property].body[0] == "eps")
				n = 0;
			else
				n = G[o.property].body.size();
			for (int i = 0; i < n * 2; i++)
				s.pop_back();
			int ts = atoi(s.back().c_str());
			s.push_back(G[o.property].head);
			s.push_back(to_string(Goto[ts][G[o.property].head]));
		}
		else if (o.type == 2)
		{
			print_sr();
			break;
		}
		else error();
	}
}

void lr1()
{
	compute_dfa_lr1();
	compute_action_goto_lr1();
	print_C_lr1();
	print_action_lr1();
	print_goto_lr1();
}

void slr()
{
	compute_dfa_slr();
	compute_action_goto_slr();
	print_C_slr();
	print_action_slr();
	print_goto_slr();
}

void lalr()
{
	compute_dfa_lr1();
	core_union();
	compute_action_goto_lalr();
	print_C_lalr();
	print_action_lalr();
	print_goto_lalr();
}

void parser(int lr)
{
	cfg_init();
	print_first();
	print_follow();
	if (lr == SLR)
		slr();
	else if (lr == LR1)
		lr1();
	else if (lr == LALR)
		lalr();
	int n;
	cin>>n;
	while(n--)
	{
		input();
		shift_reduce();

		cout<<'\n';
	}
}