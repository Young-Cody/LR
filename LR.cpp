#include<iostream>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<iomanip>
#include<string>
using namespace std;

vector<string> s;
vector<string> input_buffer;
op o;
int is;
int ip;
void input()
{
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
}

void error()
{
	cerr << "parse error\n";
}

void solve()
{
	input();
	while (1)
	{
		int state = atoi(s.back().c_str());
		string a = input_buffer[ip];
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
			for (int i = 0; i < G[o.property].body.size() * 2; i++)
				s.pop_back();
			int ts = atoi(s.back().c_str());;
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


int main()
{
	solve();
}

