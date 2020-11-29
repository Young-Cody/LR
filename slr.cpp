#include"slr.h"
#include"cfg.h"
#include<iostream>
using namespace std;

I closure_slr(I* Ii)
{
	I result = *Ii;
	vector<item_t> s(Ii->begin(), Ii->end());
	while (!s.empty())
	{
		item_t item = s.back();
		s.pop_back();
		production p = G[item.prodid];
		if (item.top < p.body.size() && NT.find(p.body[item.top]) != NT.end())
		{
			string next = p.body[item.top];
			for (auto i : h2bs[next])
			{
				item_t it;
				it.prodid = i;
				it.top = 0;
				if (result.find(it) == result.end())
				{
					result.insert(it);
					s.push_back(it);
				}
			}
		}
	}

	return result;
}

I move_slr(I* t, string x)
{
	I result;
	for (auto& i : *t)
	{
		production p = G[i.prodid];
		if (i.top < p.body.size() && p.body[i.top] == x)
		{
			item_t r;
			r.prodid = i.prodid;
			r.top = i.top + 1;
			result.insert(r);
		}
	}
	return result;
}

void compute_dfa_slr()
{
	item_t item;
	item.prodid = h2bs[start][0];
	item.top = 0;
	I I0({ item });
	I0 = closure_slr(&I0);

	vector<int> q;
	q.push_back(get_index_slr(&I0));
	while (!q.empty())
	{
		int t = q.back();
		q.pop_back();
		for (auto& str : symbol)
		{
			I Ii = move_slr(&c[t], str);
			Ii = closure_slr(&Ii);
			if (Ii.size() == 0) continue;
			if (I2index.find(Ii) == I2index.end())
			{
				int to = get_index_slr(&Ii);
				q.push_back(to);
			}
			int v = get_index_slr(&Ii);
			dfa[t][str] = v;
		}
	}
}

int get_index_slr(I* items)
{
	if (I2index.find(*items) == I2index.end())
	{
		I2index[*items] = c.size();
		dfa.push_back(map<string, int>());
		c.push_back(*items);
	}
	return I2index[*items];
}

void compute_action_goto_slr()
{
	action.resize(c.size());
	Goto.resize(c.size());
	for (int i = 0; i < c.size(); i++)
	{
		for (auto& item : c[i])
		{
			production p = G[item.prodid];
			if (item.top == p.body.size() || p.body.front() == "eps")
			{
				if (p.head == start)
				{
					op t;
					t.type = 2;
					action[i]["$"] = vector<op>({ t });
				}
				else
				{
					for (auto& str : FOLLOW[p.head])
					{
						if (action[i].find(str) == action[i].end())
							action[i][str] = vector<op>();
						op t;
						t.type = 1;
						t.property = item.prodid;
						action[i][str].push_back(t);
					}
				}
			}
		}
	}

	for (int i = 0; i < c.size(); i++)
	{
		for (auto& str : symbol)
		{
			if (dfa[i].find(str) == dfa[i].end())
				continue;
			if(NT.find(str) == NT.end())
			{
				if (action[i].find(str) == action[i].end())
					action[i][str] = vector<op>();
				op t;
				t.type = 0;
				t.property = dfa[i][str];
				action[i][str].push_back(t);
			}
			else
				Goto[i][str] = dfa[i][str];
		}
	}
}

void print_C_slr()
{
	for (int i = 0; i < c.size(); i++)
	{
		cout << "I" << i << "\n";
		print_I_slr(&c[i]);
	}
}

void print_I_slr(I* items)
{
	for (auto item : *items)
	{
		production p = G[item.prodid];
		cout << p.head << " -> ";
		for (int i = 0; i < p.body.size(); i++)
		{
			if (item.top == i) cout << ". ";
			cout << p.body[i] << " ";
		}
		if (item.top == p.body.size()) cout << ". ";
		cout << "\n";
	}
}
void print_action_slr()
{
	cout << "\naction\n\n";
	symbol.insert("$");
	for (int i = 0; i < c.size(); i++)
	{
		cout << i << "  ";
		for (auto& str : symbol)
		{
			if (NT.find(str) != NT.end()) continue;
			if (action[i].find(str) == action[i].end())
				continue;
			for (auto& o : action[i][str])
			{
				cout << str << " ";
				if (o.type == 2) cout << "acc  ";
				else if (o.type == 0) cout << "s" << o.property << "  ";
				else if (o.type == 1) cout << "r" << o.property << "  ";
			}
		}
		cout << '\n';
	}
	symbol.erase("$");
}

void print_goto_slr()
{
	cout << "\ngoto\n\n";
	for (int i = 0; i < c.size(); i++)
	{
		cout << i << "  ";
		for (auto& str : NT)
		{
			if (Goto[i].find(str) == Goto[i].end())
				continue;
			cout << str << " " << Goto[i][str] << "  ";
		}
		cout << '\n';
	}
}