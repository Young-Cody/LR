#include"lr1.h"
#include"cfg.h"
#include"lalr.h"
#include<iostream>
using namespace std;

set<int> v;
map<int, int> old2new;

bool cmp::operator()(const I &l, const I &r) const	//比较两个项目集的产生式和·的位置是否相同
{
	set<pair<int, int>> ls, rs;
	set<set<pair<int, int>>> c;
	for (auto& li : l)
		ls.insert({ li.prodid, li.top });
	for (auto& ri : r)
		rs.insert({ ri.prodid, ri.top });
	return c.key_comp()(ls, rs);
}

//LALR 同心集合并
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
		else	//两个项目集同心，进行合并
		{
			int u = m[c[i]];
			c[u].insert(c[i].begin(),c[i].end());
			old2new[i] = u;		//映射到合并后的状态
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
			if (item.top == p.body.size() || p.body.front() == "eps")
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
		}
	}

	for (auto i:v)
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
				t.property = old2new[dfa[i][str]];
				action[i][str].push_back(t);
			}
			else
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
