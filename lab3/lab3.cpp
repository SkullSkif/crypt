#include "lab3.hpp"

int fast_power(int a, int x, int p)
{
    int binaryX[1000];
    int i = 0;
    while (x > 0) {
        binaryX[i] = x % 2;
        x = x / 2;
        i++;
    }

    int y = 1;
    int sum = a;
    for (int j = 0; j < i; j++) {
        if (binaryX[j] == 1)
            y = y * sum % p;
        sum = sum * sum % p;
    }
    return y;
}

int ferm(int p)
{
    if (p < 0)
        return -1;
    if (p < 2)
        return 0;
    if (p == 3 || p == 4)
        return 1;
    if (fast_power(2, p - 1, p) == 1)
        return 1;
    return 0;
}

int gen_euclid(int* a, int* b)
{
    // if(*a < *b)
    //     return -1;
    if (*a < -1 || *b < -1)
        return -1;
    if (*a == 0 || *b == 0) {
        *a = rand() + 1;
        *b = rand() + 1;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 1000);
    if (*a == -1 || *b == -1) {
        int flag = 1, flag_a = 1, flag_b = 1;
        while (flag) {
            if (flag_a)
                *a = dist(gen);
            if (flag_b)
                *b = dist(gen);
            if (ferm(*a) > 0)
                flag_a = 0;
            if (ferm(*b) > 0)
                flag_b = 0;
            if (flag_a == 0 && flag_b == 0)
                flag = 0;
        }
    }
    int u[3] = {*a, 1, 0};
    int v[3] = {*b, 0, 1};
    int T[3] = {0};
    int q = 0;

    if (*a < *b) {
        for (int i = 0; i < 3; i++) {
            int temp = u[i];
            u[i] = v[i];
            v[i] = temp;
        }
    }

    while (v[0] != 0) {
        q = u[0] / v[0];
        T[0] = u[0] % v[0];
        T[1] = u[1] - q * v[1];
        T[2] = u[2] - q * v[2];
        for (int i = 0; i < 3; i++) {
            u[i] = v[i];
            v[i] = T[i];
        }
    }
    *a = u[1];
    *b = u[2];
    return u[0];
}

int step(int a, int y, int p)
{
    if (a == 0) {
        a = rand() + 1;
        y = rand() + 1;
        p = rand() + 1;
    }
    // int m = 2;
    // int k = (p+1) / m;
    int m = (int)(sqrt(p) + 1);
    int k = (int)(sqrt(p) + 1);
    int A[m], B[k];
    for (int i = 0; i < m; i++) {
        A[i] = (y * (int)pow(a, i)) % p;
        // std::cout << A[i] << ' ';
    }
    // std::cout << '\n';
    for (int i = 0; i < k; i++) {
        B[i] = ((int)pow(a, ((i + 1) * m))) % p;
        // std::cout << B[i] << ' ';
    }
    int result = 0;
    std::map<int, int> dict;
    for (int i = 0; i < m; ++i)
        dict[A[i]] = i;
    for (int i = 0; i < k; ++i)
        if (dict.count(B[i])) {
            result = (i + 1) * m - dict[B[i]];
            break;
        }
    return result;
}

int DH(int p, int g, int Xa, int Xb ){
    
return 0;
    
}