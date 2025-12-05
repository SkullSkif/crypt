#ifndef MYCRYPTO
#define MYCRYPTO
#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <cstring>
#include <bits/stdc++.h>

// Возвращает k^-1 mod m
uint64_t modInverse(uint64_t k, uint64_t m);

uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t m);

// y = a^x mod b
uint64_t fast_exp_mod(uint64_t number, uint64_t exp, uint64_t module);

uint64_t hash_to_bigint_mod_q(const std::string& hash_bytes, uint64_t q);

bool fast_test_ferma(uint64_t number);

// if gen == 1 then gen non simple, if gen and simple then gen simple else if a == b == 0 the std::cin
uint64_t fast_euclid(uint64_t a, uint64_t b, bool gen, bool simple, uint64_t *x, uint64_t *y);

// gen = 0, a = 0 == std::cin, gen = 1 == gen
uint64_t baby_giant_steps(uint64_t a, uint64_t p, uint64_t y, bool gen);

uint64_t diffi_helm(uint64_t p, uint64_t g, uint64_t xA, uint64_t xB, bool gen);

// uint64_t fast_euler(uint64_t x) {
//     uint64_t out = 0;
//     for (uint64_t q = 1; q < x; q++) {
//         if (fast_test_ferma(q) && )
//     }
// }

// uint64_t shamirs (uint64_t p, uint64_t m) {
// uint64_t Ca = rand(), Cb = rand(), Da = rand(), Db = rand();
// for (;(Da * Ca) % (p - 1) != 1; Da = rand());
// for (;(Db * Cb) % (p - 1) != 1; Db = rand());
//     uint64_t a_num, b_num;
//     передача по шифру Шамира
//     a_num = fast_exp_mod(m, Ca, p);
//     b_num = fast_exp_mod(a_num, Cb, p);
//     a_num = fast_exp_mod(b_num, Da, p);
//     b_num = fast_exp_mod(a_num, Db, p);
// }
#endif

