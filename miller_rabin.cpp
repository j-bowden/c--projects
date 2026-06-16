#include <iostream>
#include <random>

// This program implements the Miller-Rabin primality test


int findGCD(int b, int N) {
    // This function computes the greatest common divisor of the two inputs by the division algorithm

    while (b != 0) {
        int remainder = N % b; // isolate the remainder of N divided by b
        N = b;                 // replace N by the quotient
        b = remainder;         // replace b by the remainder
    }
    return N;
}

int exp2(int N) {
    // this function computes the power of 2 in the prime factorisation of N-1
    int numer = N - 1;
    int s = 0;
    
    while (numer % 2 == 0) {
        s += 1;
        numer /= 2;
    }

    return s;
}

int exp_modN(long long b, long long exp, long long N) {
    long long output = 1;

    while (exp > 0) {
        if (exp % 2 == 1) {
            output = (output * b) % N;
        }

        b = (b * b) % N; // exponent is now even; replace base with its square
        exp /= 2;

    }

    output = output % N;
    return output;
}

int main() {

    int N = 200819; // fix the number to be factorised

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(2, N - 1); // bases should be between 1 and N exclusive

    int b = distrib(gen); // generate a pseudorandom number

    b = b % N; // bring the number b into the correct range 0 < b < N

    int gcd = findGCD(b, N); // if this fails then b is a nontrivial factor of N, i.e. N is composite

    if (gcd > 1) {
        std::cout << N << " contains " << gcd << " as a factor. It is composite." << std::endl;
        return 0;
    }
    else {
        int s = exp2(N);
        int t = (N - 1) / pow(2, s);

        int b_to_t = exp_modN(b, t, N);
        if (b_to_t % N == 1) {
            std::cout << N << " passes the strong test to base " << b << "." << std::endl;
            std::cout << "The Miller-Rabin primality test is undetermined." << std::endl;
            return 0;
        }

        else {
            int r = 0;
            while (r < s) {
                int power = t * pow(2, r);
                int cand = exp_modN(b, power, N);

                if (cand % N == N-1) {
                    std::cout << N << " passes the strong test to base " << b << "." << std::endl;
                    std::cout << "The Miller-Rabin primality test is undetermined." << std::endl;
                    std::cout << N << " is composite with probability at most 1/4." << std::endl;
                    return 0;
                }

                r += 1;
            }

            std::cout << N << " fails the strong test to base " << b << "." << std::endl;
            std::cout << N << " is therefore composite." << std::endl;
            return 0;
        }
        
    }

}