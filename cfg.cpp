#include "cfg.h"
#include<iostream>
using namespace std;

string start;
set<string> NT;
set<string> symbol;
h2bs_t h2bs;
CFG G;
FIFO FIRST;
FIFO FOLLOW;

void cfg_init()
{
	input_cfg();
	init_first();
	init_follow();
}

void input_cfg()
{
	int n;
	cin >> n;
	cin >> start;
	while (n--)
	{
		string str;
		production p;
		cin >> str;
		p.head = str;
		if (NT.find(str) == NT.end())
		{
			h2bs[str] = vector<int>();
			NT.insert(str);
			symbol.insert(str);
		}
		int t;
		cin >> t;
		vector<string> input;
		while (t--)
		{
			string str;
			cin >> str;
			input.push_back(str);
			symbol.insert(str);
		}
		p.body = input;
		h2bs[str].push_back(G.size());
		G.push_back(p);
	}
	symbol.erase("eps");
}

void insert(FIFO* FF, string str, set<string>* s, bool* flag)
{
	int sz = (*FF)[str].size();
	(*FF)[str].insert(s->begin(), s->end());
	if ((*FF)[str].size() > sz)
		*flag = true;
}

void init_first()
{
	for (auto& str : symbol)
		FIRST[str] = set<string>();
	bool flag = true;
	while (flag)
	{
		flag = false;
		for (auto& str : symbol)
		{
			if (NT.find(str) == NT.end()) //ÖÕ½á·û
			{
				insert(&FIRST, str, &set<string>({ str }), &flag);
				continue;
			}

			for (auto i : h2bs[str]) //·ÇÖÕ½á·û
			{
				production p = G[i];
				if (p.body[0] == "eps") //epison
				{
					insert(&FIRST, str, &set<string>({ "eps" }), &flag);
					continue;
				}
				int i = 0;
				for (; i < p.body.size(); i++)
				{
					insert(&FIRST, str, &FIRST[p.body[i]], &flag);
					if (FIRST[p.body[i]].find("eps") == FIRST[p.body[i]].end())
						break;
				}
				if (i >= p.body.size())
					insert(&FIRST, str, &set<string>({ "eps" }), &flag);
			}
		}
	}
	FIRST["$"] = set<string>({ "$" });
}

void init_follow()
{
	for (auto& str : NT)
		FOLLOW[str] = set<string>();
	FOLLOW[start].insert("$");
	bool flag = true;
	while (flag)
	{
		flag = false;
		for (auto& p : G)
		{
			for (auto i = p.body.begin(); i != p.body.end(); i++)
			{
				if (NT.find(*i) != NT.end())
				{
					set<string> f = get_first(&vector<string>(i + 1, p.body.end()));

					if (f.find("eps") != f.end())
					{
						f.erase("eps");
						insert(&FOLLOW, *i, &f, &flag);
						insert(&FOLLOW, *i, &FOLLOW[p.head], &flag);
					}
					else
						insert(&FOLLOW, *i, &f, &flag);
				}
			}
		}
	}
}

set<string> get_first(vector<string> *a)
{
	set<string> result;
	int i = 0;
	for (; i < a->size(); i++)
	{
		result.insert(FIRST[(*a)[i]].begin(), FIRST[(*a)[i]].end());
		if (FIRST[(*a)[i]].find("eps") == FIRST[(*a)[i]].end())
			break;
		result.erase("eps");
	}

	if (i == a->size())
		result.insert("eps");

	return result;
}

void print_first()
{
	cout << "\n";
	for (auto& str : symbol)
	{
		cout << "FIRST(" << str << ") = {";

		for (auto& i : FIRST[str])
			cout << i << " ";
		cout << "}\n";
	}
}

void print_follow()
{
	cout << "\n";
	for (auto& str : NT)
	{
		cout << "FOLLOW(" << str << ") = {";

		for (auto& i : FOLLOW[str])
			cout << i << " ";
		cout << "}\n";
	}
}
