#include "iostream"
// some algorithmic example from the book, for didactic purposes.
// could be expanded upon at some later time - PC

////////////////////////////////////////
/// CHAPTER ONE: THE FIRST ALGORITHM ///
////////////////////////////////////////

/// AN INITIAL WAY TO PERFORM MULTIPLICATION ALGORITHMICALLY ///
// algorithm for the mathematical process of induction, S(n) = n(n+1)/2
// inefficient but didactic function, where n-1  additions are required
// this simply illustrates that we either want to multiply by 1, or some value greater than one
// such that we assume if it is > 1 i.e. the base case, we simply reutrn its self as its multiplied once
// other wise we continue down the chain for n additions recursively. - PC 
int Multiply0(int n, int a) 
{
	if (n == 1)
	{
		return a;
	}
	return Multiply0(n - 1, a) + a;
}

/// THE FIRST RECORDED ALGORITHM, AN IMPROVEMENT ///
// Egyptian multiplication:
// this algorithm is found from and Egyptian piece of papyrus written by a man called Ahmes
// and shown with some other functions that are required to make it work, this algorithm for multiplication
// reduces the above algorithm which was similar to the process of induction by turning a O(n) algorithm,
// to a OLog(n) algorithm: still not the most efficient as in the case of the number 15 but good enough for most
// cases - PC
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


/// MULTIPLY-ACCUMULATE, A FURTHER IMPROVEMENT ///
// the above "Multiply1" function works well as for as the number of additions is concerned
// but it also does log(n) recursive calls, this expense can be dealt with, adhering to a principle
//  - it is often easier to do more work than less. - thus we will create an effective multiply accumulate function
// to improve our overall algorithm,
// we are going to compute  -  "r + na", where r is a a running result which accumulates the partial products na.
int Mult_acc0(int r, int n, int a)
{
	if (n == 1)
	{
		return r + a;
	}
	if (Odd(n))
	{
		return Mult_acc0(r + a, Half(n), a + a);
	}
	else
	{
		return Mult_acc0(r, Half(n), a + a);
	}
}

// this can be improved further by, simply modifying r before we recurse, as in the odd case above
// this function is "tail-recursive", only recurses in the return value - this will be taken advantage of
// shortly
int Mult_acc1(int r, int n, int a)
{
	if (n == 1)
	{
		return r + a;
	}
	if (Odd(n))
	{
		r = r + a;
	}
	return Mult_acc1(r, Half(n), a + a);
}

// another improvement, two observations about the above algorithm, rarely is n == 1.
// and there is no point in checking if n == 1, if n is even.
// so we can reduce the comparison by a factor of 2 by checking oddness first
int Mult_acc2(int r, int n, int a) // some programmers think the compiler does optimizations like this, but this is rarely the case
{
	if (Odd(n))
	{
		r = r + a;
		if (n == 1)
		{
			return r;
		}
	}
	return Mult_acc2(r, Half(n), a + a);
}

// another improvement, here is that eventually we want to totally eliminate the recursive call overhead
// It is easier to do this if the function is strictly tail recursive as mentioned above.
// It is not yet - strictly recursive however as in order to be strictly recursive it must comply to the following definition:
// "all recursive calls are done with the formal parameters of the procedure being the corresponding arguments"
// thus we assign the valuse before we recurse
int Mult_acc3(int r, int n, int a) 
{
	if (Odd(n))
	{
		r = r + a;
		if (n == 1)
		{
			return r;
		}
	}
	n = Half(n);
	a = a + a;
	return Mult_acc3(r, n, a);
}

// Now it is easier to refactor this in to a iterative approach by replacing the tail recursion with
// a while true construct, for our multiply accumulate
int Mult_acc4(int r, int n, int a)
{
	while (true)
	{
		if (Odd(n))
		{
			r = r + a;
			if (n == 1)
			{
				return r;
			}
		}
		n = Half(n);
		a = a + a;
	}
}

// now with the optimized multiply accumulate function, we can improve our old function
int Multiply2(int n, int a)
{
	if (n == 1)
	{
		return a;
	}
	return Mult_acc4(a, n - 1, a); // r, n, a ---- notice we skip one iteration by having r set to a initially
}

// This is pretty good except when n is a power of 2. The first thing we do is subtract one
// which means that Mult_acc4 will be called with a number whose binary representation is all ones.
// This is the worse case for our algorithm. So we avoid this by doing some of the work in advance
// when n is even, halving it and doubling a, until n becomes odd.
int Multiply3(int n, int a)
{
	while (!Odd(n))
	{
		a = a + a;
		n = Half(n);
	}
	if (n == 1)
	{
		return a;
	}
	return Mult_acc4(a, n - 1, a);
}

// lastly we can improve this further by noticing that we are making Mult_acc4 do one
// unnecessary test for odd(n), because we are calling it with an even number. So we will do one
// halving on the arguments before we call it, giving us our final version:
int Multiply4(int n, int a)
{
	while (!Odd(n))
	{
		a = a + a;
		n = Half(n);
	}
	if (n == 1)
	{
		return a;
	}
	// even(n - 1) ===> n - 1 != 1
	return Mult_acc4(a, Half(n - 1), a + a);
}
// Notes: this process of efficency and improving performance of code is beneficial and analogous
// to the mathematical process of simplification or algebraic expressions.

////////////////////////////////////////////////
/// CHAPTER TWO: ANCIENT GREEK NUMBER THEORY ///
////////////////////////////////////////////////
int main()
{
	return 0;
}