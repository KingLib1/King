#include "kprobability.h"

#include "kmath.h"

long long permutation(unsigned int n, unsigned int m)
{
    long long int p = n;
    for (unsigned int i = 1; i < m; ++i)
        p *= n - i;
    return p;
}

long long combination(unsigned int n, unsigned int m)
{
    if (m == 0)
        return 1;
    m = kMin(m, n - m);
    long long mfact = 1;
    for (unsigned int i = 2; i <= m; ++i)
        mfact *= i;
    return permutation(n, m) / mfact;
}
