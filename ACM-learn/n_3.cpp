/*1002*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

typedef vector<int> Vint;

Vint *String_to_Vint(const string &s)
{
	Vint *v = new Vint;
	for (string::const_reverse_iterator iter = s.rbegin(); iter != s.rend(); iter++)
	{
		int bit;
		if (*iter >= '0' && *iter <= '9')
		{
			bit = *iter - '0';
			v->push_back(bit);
		}
	}
	return v;
}

Vint *cauculate_sum(Vint &a, Vint &b)
{
	int c = 0;
	int s;
	Vint *result = new Vint;
	int size = max(a.size(), b.size());
	a.resize(size, 0);
	b.resize(size, 0);
	for (int i = 0; i < size; i++)
	{
		s = a[i] + b[i] + c;
		c = s / 10;
		s %= 10;
		result->push_back(s);
	}
	if (c)
	{
		result->push_back(c);
	}
	return result;
}

string Vint_to_string(const Vint &v)
{
	string s;
	int size = v.size();
	s.resize(size);
	for (int i = 0; i < size; i++)
	{
		s[size - i - 1] = v[i] + '0';
	}
	return s;
}

int main()
{
	Vint *a;
	Vint *b;
	vector<Vint*>res(20);
	vector<string> s1(20), s2(20);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> s1[i] >> s2[i];
		a = String_to_Vint(s1[i]);
		b = String_to_Vint(s2[i]);
		res[i] = cauculate_sum(*a, *b);

		delete a;
		delete b;
	}
	for (int i = 0; i < n; i++)
	{
		cout << "Case " << i + 1 << ':' << endl;
		cout << s1[i] << " + " << s2[i] << " = " << Vint_to_string(*(res[i])) << endl;
		if (i != n - 1)
			cout << endl;
		delete res[i];
	}
	//getchar();
	//getchar();
	//getchar();
	return 0;
}