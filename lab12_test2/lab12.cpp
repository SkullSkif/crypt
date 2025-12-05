#include "lab12.h"

uint64_t modInverse(uint64_t k, uint64_t m) {
    int64_t m0 = m;
    int64_t y = 0, x = 1;

    if (m == 1) return 0;

    while (k > 1) {
        int64_t q = k / m0;
        int64_t t = m0;

        m0 = k % m0, k = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0) x += m;

    return x;
}

uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t m) {
    return (uint64_t)(((unsigned __int128)a * b) % m);
}

// y = a^x mod b
uint64_t fast_exp_mod(uint64_t number, uint64_t exp, uint64_t module) {
    uint64_t answ = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            answ = mul_mod(answ, number, module);
        number = mul_mod(number, number, module);
        exp = exp / 2;
    }
    return answ % module;
}

uint64_t hash_to_bigint_mod_q(const std::string& hash_bytes, uint64_t q) {
    unsigned __int128 current_value = 0;
    for (unsigned char byte : hash_bytes) {
        current_value <<= 8;
        current_value |= byte;
        current_value %= q;
    }

    return (uint64_t)current_value;
}

//ferm simple test
bool fast_test_ferma(uint64_t number) {
    if (number < 6) {
        if (number == 1 || number == 4)
            return false;
        else
            return true;
    }
    if (!(number % 2) || !(number % 3) || !(number % 5))
        return false;
    for (uint64_t second_its = 0; second_its < 100; second_its++) {
        uint64_t scnd_test = rand() % (number - 1) + 2;
        if (fast_exp_mod(scnd_test, (number - 1) / 2, number) == (uint64_t)1 || fast_exp_mod(scnd_test, (number - 1) / 2, number) == (uint64_t)-1)
            return true;
    }
    return false;
}

// if gen == 1 then gen non simple, if gen and simple then gen simple else if a == b == 0 the std::cin
uint64_t fast_euclid(uint64_t a, uint64_t b, bool gen, bool simple, uint64_t *x, uint64_t *y) {
    uint64_t new_x, new_y, gcd, q, tmpx;
    uint64_t koef[6] = {1, 0, 0, 1};
    if (!gen && a == 0 && b == 0) {
        std::cout << "enter x and y\n";
        std::cin >> new_x >> new_y;
    }
    else if (gen){
        if (simple) {
            for (new_x = rand(); !fast_test_ferma((uint64_t)new_x); new_x = rand());
            for (new_y = rand(); !fast_test_ferma((uint64_t)new_y); new_y = rand());
        }
        else {
            new_x = rand();
            new_y = rand();
        }
        simple ? std::cout << " simple gen is: " : std::cout << "not simple gen is: ";
        std::cout << "gen x is: " << new_x << " gen y is: " << new_y;
    }
    else {
        new_x = a;
        new_y = b;
    }
    if (new_y > new_x) {
        uint64_t tmp = new_x;
        new_x = new_y;
        new_y = tmp;
        koef[0] = 0;
        koef[1] = 1;
        koef[2] = 1;
        koef[3] = 0;
    }
    tmpx = new_x;
    for (;new_x % new_y != 0;) {
        q = new_x / new_y;
        gcd = new_x % new_y;
        koef[4] = koef[0] - q * koef[2];
        koef[5] = koef[1] - q * koef[3];
        tmpx = new_x;
        new_x = new_y;
        new_y = tmpx % new_y;
        koef[0] = koef[2];
        koef[1] = koef[3];
        koef[2] = koef[4];
        koef[3] = koef[5];
    }
    *x = koef[2];
    *y = koef[3];
    return gcd;
}

// gen = 0, a = 0 == std::cin, gen = 1 == gen
uint64_t baby_giant_steps(uint64_t a, uint64_t p, uint64_t y, bool gen) {
    if (!gen) {
        if (a != 0) {
            if (p < y || !fast_test_ferma(p))
                return -1;
        }
        else {
            std::cout << "enter a, p, y\n";
            std::cin >> a >> p >> y;
        }
    }
    else {
        a = std::rand();
        y = std::rand();
    }

    uint64_t m = sqrt((long double)p) + 1;
    uint64_t for_m[m], for_vel[m];

    for (uint64_t i = 0; i < m; i++) {
        for_m[i] = (y * (a ^ i)) % p;
        std::cout << "mel i: " << i << " is: " << for_m[i] << '\n';
    }
    for (uint64_t i = 1; i < m; i++) {
        for_vel[i] = (a ^ (i * m)) % p;
        std::cout << "for_vel i: " << i << " is: " << for_vel[i] << '\n';
        for (uint64_t j = 0; j < m; j++) {
            if (for_m[j] == for_vel[i])
                //if (fast_exp_mod(a, for_vel[i], p) == y)
                return i * m - (j + 1);
        }
    }
    return -1;
}

uint64_t diffi_helm(uint64_t p, uint64_t g, uint64_t xA, uint64_t xB, bool gen) {
    if (!gen) {
        if (p == 0 && g == 0 && xA == 0 && xB == 0)
            std::cin >> p >> g >> xA >> xB;
    }
    else {
        p = rand();
        g = rand();
        xA = rand();
        xB = rand();
    }
    uint64_t key, a, b; // a and b public
    a = fast_exp_mod(g, xA, p);
    b = fast_exp_mod(g, xB, p);
    // B get a, A get b
    key = fast_exp_mod(b, xA, p);
    if (key != fast_exp_mod(a, xB, p))
        return 0;
    return key;
}
