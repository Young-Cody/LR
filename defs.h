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
	string head;			 //产生式左部
	vector<string> body;	//产生式右部
} production;				//产生式

typedef vector<production> CFG;				//上下文无关文法
typedef map<string, vector<int>> h2bs_t; 	//非终结符映射到它的所有产生式
typedef map<string, set<string>> FIFO;		//FIRST集和FOLLOW集
typedef vector<map<string, int>> DFA;		//DFA

typedef struct item {
	int top;			//栈顶的位置
	int prodid;			//产生式的索引
	string next;		//向前搜索符，LR(1)项目中用到
	bool operator <(const item& s) const {
		if (prodid != s.prodid) return prodid < s.prodid;
		else if (top != s.top)return top < s.top;
		else return next < s.next;
	}
} item_t;				//项目

typedef set<item_t> I;	//项目集
typedef vector<I> C;	//项目集规范族

/**
 * action表中的动作
 * type：0--shift，property：移进后栈顶的状态
 * 		1--reduce，property：进行归约的产生式的索引
 *     2--accept
 **/
typedef struct
{
	int type;
	int property;
} op;		
						

typedef vector<map<string, vector<op>>> ACTION;		//action表，action[state][T]
typedef vector<map<string, int>> GOTO;				//goto表，goto[state][NT]

#endif // !DEFS