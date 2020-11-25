#include"lr1.h"
#include"cfg.h"
#include"lalr.h"
#include<iostream>
using namespace std;

set<int> v;
map<int, int> old2new;

void core_union()
{
	map<I, int, cmp> m;
	for (int i = 0; i < c.size(); i++)
	{
		if (m.find(c[i]) == m.end())
		{
			v.insert(i);
			old2new[i] = i;
			m[c[i]] = i;
		}
		else
		{
			int u = m[c[i]];
			c[u].insert(c[i].begin(),c[i].end());
			old2new[i] = u;
		}
	}
}

void compute_action_goto_lalr()
{
	action.resize(c.size());
	Goto.resize(c.size());
	for (auto& i : v)
	{
		for (auto& item : c[i])
		{
			production p = G[item.prodid];
			if (item.top == p.body.size())
			{
				if (p.head == start && item.next == "$")
				{
					op t;
					t.type = 2;
					action[i]["$"] = vector<op>({ t });
				}
				else
				{
					if (action[i].find(item.next) == action[i].end())
						action[i][item.next] = vector<op>();
					op t;
					t.type = 1;
					t.property = item.prodid;
					action[i][item.next].push_back(t);
				}
			}
			else if (NT.find(p.body[item.top]) == NT.end())
			{
				string next = p.body[item.top];
				op t;
				t.type = 0;
				t.property = old2new[dfa[i][next]];
				if (action[i].find(next) == action[i].end())
					action[i][next] = vector<op>();
				action[i][next].push_back(t);
			}
		}
	}

	for (auto& i : action)
	{
		for (auto& str : i)
		{
			set<op> ops = set<op>(str.second.begin(), str.second.end());
			str.second = vector<op>(ops.begin(), ops.end());
		}
	}

	for (auto i:v)
	{
		for (auto& str : NT)
		{
			if (dfa[i].find(str) == dfa[i].end())
				continue;
			Goto[i][str] = old2new[dfa[i][str]];
		}
	}
}

void print_C_lalr()
{
	for (auto& i : v)
	{
		cout << "I" << i << "\n";
		print_I_lr1(&c[i]);
	}
}

void print_I_lalr(I* items)
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
		cout << ", " << item.next;
		cout << "\n";
	}
}

void print_action_lalr()
{
	cout << "\naction\n\n";
	symbol.insert("$");
	for (auto &i:v)
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

void print_goto_lalr()
{
	cout << "\ngoto\n\n";
	for (auto &i:v)
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

bool cmp::operator()(const I &l, const I &r) const
{
	set<pair<int, int>> ls, rs;
	set<set<pair<int, int>>> c;
	for (auto& li : l)
		ls.insert({ li.prodid, li.top });
	c.insert(ls);
	for (auto& ri : r)
		rs.insert({ ri.prodid, ri.top });
	return c.key_comp()(ls, rs);
}