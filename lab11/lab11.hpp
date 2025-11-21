#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <random>
#include <algorithm>
#include <climits>


long long fast_power(long long a, long long x, long long p);
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
void DH_setup();
int DH_k(int person);
void Vernam_encrypt(int k);
void Vernam_decrypt(int k);
void RSA_sign_encrypt();
void RSA_sign_decrypt();
void Set_sign_gamel_keys();
void Gamel_sign_encrypt();
void Gamel_sign_decrypt();
void GOST(int type);
void FIPS(int type);
