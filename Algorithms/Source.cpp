#include "iostream"
// some algorithmic example from the book, for didactic purposes.


// algorithm for the mathematical process of induction, S(n) = n(n+1)/2
// inefficient but didactic function, where n-1  additions are required
// this simply illustrates that we either want to multiply by 1, or some value greater than one
// such that we assume if it is >1 i.e. the base case, we simply reutrn its self as its multiplied once
// other wise we continue down the chain for n additions recursively. - PC 
int Multiply0(int n, int a) 
{
	if (n == 1)
	{
		return a;
	}
	return Multiply0(n - 1, a) + a;
}

// Egyptian multiplication:
// this algorithm is found from and Egyptian piece of papyrus written by a man called Ahmes
// and shown with some other functions that are required to make it work
bool Odd(int n)
{
	return n & 0x1; // test least significant bit of n to see if it is odd.
}

int Half(int n)
{
	return n >> 1; // half n by a single right shift
}


int Multiply1(int n, int a)
{
	if (n == 1)
	{
		return a;
	}
	int result = Multiply1(Half(n), a + a);
	if (Odd(n))
	{
		result = result + a;
	}
	return result;
}

int main()
{
	return 0;
}