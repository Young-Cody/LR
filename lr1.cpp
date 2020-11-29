#include"lr1.h"
#include"cfg.h"
#include<iostream>
using namespace std;



I closure_lr1(I* Ii)
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
			string h = p.body[item.top];
			for (auto i : h2bs[h])
			{
				item_t it;
				it.prodid = i;
				it.top = 0;
				vector<string> str(p.body.begin() + item.top + 1, p.body.end());
				str.push_back(item.next);
				set<string> first = get_first(&str);
				for (auto& i : first)
				{
					it.next = i;
					if (result.find(it) == result.end())
					{
						result.insert(it);
						s.push_back(it);
					}
				}
			}
		}
	}
	return result;
}

I move_lr1(I* t, string x)
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
			r.next = i.next;
			result.insert(r);
		}
	}
	return result;
}

void compute_dfa_lr1()
{
	item_t item;
	item.prodid = h2bs[start][0];
	item.top = 0;
	item.next = "$";

	I I0{ item };
	I0 = closure_lr1(&I0);

	vector<int> q;
	q.push_back(get_index_lr1(&I0));
	while (!q.empty())
	{
		int t = q.back();
		q.pop_back();
		for (auto& str : symbol)
		{
			I Ii = move_lr1(&c[t], str);
			Ii = closure_lr1(&Ii);
			if (Ii.size() == 0) continue;
			if (I2index.find(Ii) == I2index.end())
			{
				int to = get_index_lr1(&Ii);
				q.push_back(to);
			}
			int v = get_index_lr1(&Ii);
			dfa[t][str] = v;
		}
	}
}

int get_index_lr1(I* items)
{
	if (I2index.find(*items) == I2index.end())
	{
		I2index[*items] = c.size();
		dfa.push_back(map<string, int>());
		c.push_back(*items);
	}
	return I2index[*items];
}

void compute_action_goto_lr1()
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

void print_C_lr1()
{
	for (int i = 0; i < c.size(); i++)
	{
		cout << "I" << i << "\n";
		print_I_lr1(&c[i]);
	}
}

void print_I_lr1(I* items)
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
		cout << ", "<<item.next;
		cout << "\n";
	}
}
void print_action_lr1()
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

void print_goto_lr1()
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