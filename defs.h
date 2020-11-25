#ifndef DEFS_H
#define DEFS_H

#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

#define SLR 0
#define LR1 1
#define LALR 2

typedef struct {
	string head;
	vector<string> body;
}production;
typedef vector<production> CFG;
typedef map<string, vector<int>> h2bs_t;
typedef map<string, set<string>> FIFO;
typedef vector<map<string, int>> DFA;

typedef struct item {
	int top;
	int prodid;
	string next;
	bool operator <(const item& s) const {
		if (prodid != s.prodid) return prodid < s.prodid;
		else if (top != s.top)return top < s.top;
		else return next < s.next;
	}
} item_t;

typedef set<item_t> I;
typedef vector<I> C;

typedef struct opi
{
	int type;
	int property;
	bool operator <(const opi& s) const {
		if (type != s.type) return type < s.type;
		return property < s.property;
	}
} op;

#endif // !DEFS