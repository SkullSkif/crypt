#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <random>

int fast_power(int a, int x, int p);
int ferm(int p);
int gen_euclid(int* x, int* y);
int step(int a, int y, int p);
int DH(int p, int g, int Xa, int Xb);
int Shamir_encrypt(char m, int p, int Ca, int Cb, int Da);
int Shamir_decrypt(int x3, int p, int Db);
int Set_keys(int* p, int* Ca, int* Cb, int* Da, int* Db, int type);
int Get_keys(int* p, int* Ca, int* Cb, int* Da, int* Db);
int Set_gamel_keys(int* p, int* g, int* x, int* y, int* k, int type);
int Gamel_encrypt(int m, std::ofstream& out);
char Gamel_decrypt(int a, int b);
void Set_RSA_keys(int type);
void RSA_encrypt(int m, std::ofstream& out);
char RSA_decrypt(int e, int c, int N);