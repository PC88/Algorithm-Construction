#include "iostream"
// some algorithmic example from the book, for didactic purposes.

int Multiply0(int n, int a)
{
	if (n == 1)
	{
		return a;
	}
	return Multiply0(n - 1, a) + a;
}

int main()
{
	return 0;
}