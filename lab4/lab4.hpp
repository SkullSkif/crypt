#include <math.h>
#include <random>
#include <map>
#include <iostream>

int fast_power(int a, int x, int p);
int ferm(int p);
int gen_euclid(int* x, int* y);
int step(int a, int y, int p);
int DH(int p, int g, int Xa, int Xb);
int Shamir_encrypt(int m, int p, int Ca, int Cb, int Da, int Db);