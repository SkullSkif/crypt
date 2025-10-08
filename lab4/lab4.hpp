#include <math.h>
#include <random>
#include <map>
#include <iostream>
#include <fstream>

int fast_power(int a, int x, int p);
int ferm(int p);
int gen_euclid(int* x, int* y);
int step(int a, int y, int p);
int DH(int p, int g, int Xa, int Xb);
int Shamir(std::fstream alice, std::fstream bob, std::fstream text, std::ofstream result, int p, int Ca, int Cb);