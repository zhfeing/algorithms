// 1001

// a.b ^ c

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef vector<int> Vector_i;

// all numbers are presented in lsb->msb
Vector_i add(const Vector_i v1, const Vector_i v2)
{
	Vector_i res;
	int length_1 = v1.size();
	int length_2 = v2.size();
	int max_length, min_length;
	const Vector_i *longer, *shorter;
	if (length_1 > length_2)
	{
		max_length = length_1;
		min_length = length_2;
		longer = &v1;
	}
	else
	{
		max_length = length_2;
		min_length = length_1;
		longer = &v2;
	}
	// res length worse case is max_length
	res.reserve(max_length + 1);
	// res must contain max_length bits
	res.resize(max_length);
	// flag of C
	bool C = 0;
	for (int i = 0; i < min_length; i++)
	{
		res[i] = (v1[i] + v2[i] + C) % 10;
		C = (v1[i] + v2[i] + C) / 10;
	}
	for (int i = min_length; i < max_length; i++)
	{
		res[i] = (longer->at(i) + C) % 10;
		C = (longer->at(i) + C) / 10;
	}
	if (C != 0)
	{
		res.push_back(C);
	}
	return res;
}
Vector_i mul_10(const Vector_i v, const unsigned bits)
{
	Vector_i res(1, 0);
	if (v.size() == 1 && v[0] == 0)
		return res;
	res.resize(bits, 0);
	res.insert(res.end(), v.begin(), v.end());
	return res;
}
// v must be a pure decimal
Vector_i div_10(const Vector_i v, const unsigned bits)
{
	Vector_i res = v;
	for(int i = 0; i < bits; i++)
	{
		res.push_back(0);
	}
	return res;
}
Vector_i multiple(const Vector_i v, unsigned bit)
{
	Vector_i res(1, 0);
	if (bit != 0)
	{
		int length = v.size();
		res.resize(length);
		int C = 0;
		for (int i = 0; i < length; i++)
		{
			res[i] = (v[i] * bit + C) % 10;
			C = (v[i] * bit + C) / 10;
		}
		if (C != 0)
		{
			res.push_back(C);
		}
	}
	return res;
}
Vector_i multiple(const Vector_i v1, const Vector_i v2)
{
	Vector_i res(1, 0);
	for (int i = 0; i < v2.size(); i++)
	{
		res = add(mul_10(multiple(v1, v2[i]), i), res);	// res += v1*v2_i*10^i
	}
	return res;
}
Vector_i exp(const Vector_i v, int n)
{
	if (n == 0)
	{
		return Vector_i(1, 1);
	}
	else if (n == 1)
	{
		return v;
	}
	if (n % 2 == 0)
	{
		return exp(multiple(v, v), n / 2);
	}
	else
	{
		return multiple(exp(v, n - 1), v);
	}
}

int main()
{
	string s;
	int n;
	while (cin >> s >> n)
	{
		Vector_i integer, decimal;
		bool integer_bit = true;
		for (int i = 0; i < 6; i++)
		{
			if (integer_bit)
			{
				if (s[i] != '.')
				{
					integer.push_back(s[i] - '0');
				}
				else
				{
					integer_bit = false;
				}
			}
			else
			{
				decimal.push_back(s[i] - '0');
			}
		}
		reverse(integer.begin(), integer.end());
		reverse(decimal.begin(), decimal.end());
		// shink integer
		while (!integer.empty() && !integer.back())
			integer.pop_back();
		// shink decimal
		while (!decimal.empty() && !decimal.front())
			decimal.erase(decimal.begin());
		if (!decimal.empty() && !integer.empty())
		{
			Vector_i v = decimal;
			v.insert(v.end(), integer.begin(), integer.end());
			int decimal_position = decimal.size()*n;
			Vector_i res = exp(v, n);
			int res_length = res.size();
			// debug
			// cout << "res_length" << res_length << "\t decimal_position" << decimal_position << endl;
			for(int i = res_length - 1; i >= decimal_position; i--)
			{
				cout << res[i];
			}
			cout << ".";
			for(int i = decimal_position - 1; i >= 0; i--)
			{
				cout << res[i];
			}
			cout << endl;
		}
		else if (decimal.empty() && !integer.empty())
		{
			Vector_i res = exp(integer, n);
			for(Vector_i::reverse_iterator iter = res.rbegin(); iter != res.rend(); iter++)
			{
				cout << *iter;
			}
			cout << endl;
		}
		else if (!decimal.empty() && integer.empty())
		{
			int dicimal_length = decimal.size();
			Vector_i res = exp(decimal, n);
			cout << ".";
			for(int i = 0; i < dicimal_length*n-res.size(); i++)
			{
				cout << 0;
			}
			for(Vector_i::reverse_iterator iter = res.rbegin(); iter != res.rend(); iter++)
			{
				cout << *iter;
			}
			cout << endl;
		}
		else
		{
			cout << 0 << endl;
		}
	}
	system("pause");
}
