#include <iostream>
#include <chrono>

using namespace std;

/*
Multiplication: Version 0

1.) 1a = a
2.) (n + 1)a = na + a

Recursive Implementation

Complexity ∈ Ο(n)
∵ n - 1 additions are required when we add a together n times. 
*/
int multiply0(int n, int a)
{   
    assert(n > 0 && a > 0);

    if (n == 1)
    {
        return a; // 1.)
    } else {
        return multiply0(n - 1, a) + a; // 2.)
    }
}

/*
Multiplication: Version 1

This algorithm relies on determining a number to be odd or even.

n = n/2 + n/2 ⟹ even(n)
n = (n - 1)/2 + (n - 1)/2 + 1 ⟹ odd(n)

Complexity = ⌊log(n)⌋ + (v(n) - 1) ∈ Ο(log(n))
where v(n) is the number of 1's in the binary representation (pop count)

Since we half n each time we recurse, the complexity is dropped to log(n)
*/

bool odd(int n) 
{
    return n & 1;
}

int half(int n)
{
    return n >> 1;
}

int multiply1(int n, int a)
{
    assert(n > 0 && a > 0);

    if (n == 1)
    {
        return a;
    }
    int result = multiply1(half(n), a + a);
    if (odd(n))
    {
        result = result + a;
    }
    return result;
}

/*
Since recursive function calls are expensive,
we want to convert the algorithm into an iterative version

We compute r + na where r is the running result that computes the 
partial products of na
*/
int mult_acc0(int r, int n, int a)
{
    assert(r > 0 && n > 0 && a > 0);

    if (n == 1)
    {
        return r + a;
    }
    if (odd(n))
    {
        return mult_acc0(r + a, half(n), a + a);
    }
    return mult_acc0(r, half(n), a + a);
}

/*
We can improve this further by simplifying the recursion. 
The two recursive calls differ only in their first argument. 
Instead of having two recursive calls for the odd and even cases, 
we’ll just modify the value of r before we recurse

This function is tail recursive
*/
int mult_acc1(int r, int n, int a)
{
    if (n == 1)
    {
        return r + a;
    }
    if (odd(n))
    {
        r = r + a;
    }
    return mult_acc1(r, half(n), a + a);
}

/*
Note:
    * n is rarely 1
    * There is no point in checking if n is one if even(n)

Thus we can improve the mult_acc function

By checking odd() first, we reduce the number of comparisons 
`(n == 1)` by a factor of 2
*/
int mult_acc2(int r, int n, int a)
{
    if (odd(n))
    {
        r = r + a;
        if (n == 1)
        {
            return r;
        }
    }
    return mult_acc2(r, half(n), a + a);
}


/*
Still room for improvement
We want to eliminate the recursion to avoid the function call overhead. 
It's easier to do this if the function is strictly tail-recursive.
*/

int mult_acc3(int r, int n, int a)
{
    if (odd(n))
    {
        r = r + a;
        if (n == 1)
        {
            return r;
        }
    }
    n = half(n);
    a = a + a;
    return mult_acc3(r, n, a);
}

// Now we can replace recursion with while(true) loop

int mult_acc4(int r, int n, int a)
{
    while (true)
    {
        if (odd(n))
        {
            r = r + a;
            if (n == 1)
            {
                return r;
            }
        }
        n = half(n);
        a = a + a;
    }
}

/*
Optimal multiplication:

If n is a power of 2, the first thing done is subtract by one
this means that mult_acc4 will be called with a number whose 
binary representation is all 1s, the worst case for this algorithm.

So we’ll avoid this by doing some of the work in advance when n is even, 
halving it (and doubling a) until n becomes odd:
*/
int multiply(int n, int a)
{
    while (!odd(n))
    {
        a = a + a;
        n = half(n);
    }
    if (n == 1)
    {
        return a;
    }
    return mult_acc4(a, half(n - 1), a + a);
}



int main() 
{
    cout << "Hello World" << endl;

    std::chrono::high_resolution_clock::time_point start, end;



    start = std::chrono::high_resolution_clock::now();
    cout << multiply0(5000, 8392) << endl;
    end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> duration = end - start;

    cout << "Mult0 Execution time = " << duration.count() << " seconds" << endl;
    



    start = std::chrono::high_resolution_clock::now();
    cout << multiply1(5000, 8392) << endl;
    end = std::chrono::high_resolution_clock::now();
    
    duration = end - start;

    cout << "Mult1 Execution time = " << duration.count() << " seconds" << endl;
    






    start = std::chrono::high_resolution_clock::now();
    cout << multiply(5000, 8392) << endl;
    end = std::chrono::high_resolution_clock::now();
    
    duration = end - start;

    cout << "Optimal Multiply Execution time = " << duration.count() << " seconds" << endl;
    
    return 0;
}

