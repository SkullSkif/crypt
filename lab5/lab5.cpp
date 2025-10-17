#include "lab5.hpp"

int fast_power(int a, int x, int p)
{
    int binaryX[1000];
    int i = 0;
    while (x > 0)
    {
        binaryX[i] = x % 2;
        x = x / 2;
        i++;
    }

    int y = 1;
    int sum = a;
    for (int j = 0; j < i; j++)
    {
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

int gen_euclid(int *a, int *b)
{
    // if(*a < *b)
    //     return -1;
    if (*a < -1 || *b < -1)
        return -1;
    if (*a == 0 || *b == 0)
    {
        *a = rand() + 1;
        *b = rand() + 1;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 1000);
    if (*a == -1 || *b == -1)
    {
        int flag = 1, flag_a = 1, flag_b = 1;
        while (flag)
        {
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

    if (*a < *b)
    {
        for (int i = 0; i < 3; i++)
        {
            int temp = u[i];
            u[i] = v[i];
            v[i] = temp;
        }
    }

    while (v[0] != 0)
    {
        q = u[0] / v[0];
        T[0] = u[0] % v[0];
        T[1] = u[1] - q * v[1];
        T[2] = u[2] - q * v[2];
        for (int i = 0; i < 3; i++)
        {
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
    if (a == 0)
    {
        a = rand() + 1;
        y = rand() + 1;
        p = rand() + 1;
    }
    // int m = 2;
    // int k = (p+1) / m;
    int m = (int)(sqrt(p) + 1);
    int k = (int)(sqrt(p) + 1);
    int A[m], B[k];
    for (int i = 0; i < m; i++)
    {
        A[i] = (y * (int)pow(a, i)) % p;
        // std::cout << A[i] << ' ';
    }
    // std::cout << '\n';
    for (int i = 0; i < k; i++)
    {
        B[i] = ((int)pow(a, ((i + 1) * m))) % p;
        // std::cout << B[i] << ' ';
    }
    int result = 0;
    std::map<int, int> dict;
    for (int i = 0; i < m; ++i)
        dict[A[i]] = i;
    for (int i = 0; i < k; ++i)
        if (dict.count(B[i]))
        {
            result = (i + 1) * m - dict[B[i]];
            break;
        }
    return result;
}

int DH(int p, int g, int Xa, int Xb)
{
    int Ya = 0, Yb = 0, Za = 0, Zb = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 1000000);
    if (p == 0)
    {
        int flag = 1;
        int sofi = 0;
        while (flag)
        {
            sofi = dist(gen);
            if (ferm(sofi) > 0 && ferm((2 * sofi + 1)))
                flag = 0;
        }
        p = sofi * 2 + 1;
        g = 2;
        for (int i = 2; i < (p - 1); i++)
        {
            if (fast_power(i, sofi, p) != 1)
            {
                g = i;
                break;
            }
        }
        std::uniform_int_distribution<> dist(1, p);
        Xa = dist(gen);
        Xb = dist(gen);
    }
    Ya = fast_power(g, Xa, p);
    std::cout << "\nYa: " << Ya;
    Yb = fast_power(g, Xb, p);
    std::cout << "\nYb: " << Yb;
    Za = fast_power(Yb, Xa, p);
    std::cout << "\nZa: " << Za;
    Zb = fast_power(Ya, Xb, p);
    std::cout << "\nZb: " << Zb << '\n';
    if (Za == Zb)
        return 1;
    return 0;
}

int gcd(int a, int b, int *x, int *y)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return d;
}

void generate_key_pair(int p, int &a, int &b)
{
    int q = p - 1;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, q - 1);

    while (true)
    {
        a = dist(gen);
        int x, y;
        int g = gcd(a, q, &x, &y);
        if (g == 1)
        {
            b = x % q;
            if (b < 0)
                b += q;
            break;
        }
    }
}

int Set_keys(int *p, int *Ca, int *Cb, int *Da, int *Db, int type)
{
    std::ofstream alice("Alice");
    std::ofstream bob("Bob");
    std::ofstream p_key("P");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distp(1, 255);

    if (type)
    {
        // int q = *p - 1;

        generate_key_pair(*p, *Da, *Db);

        alice << *Ca << '\n'
              << *Cb;
        bob << *Da << '\n'
            << *Db;
        p_key << *p;
    }
    else
    {
        // *p = distp(gen);
        // while (ferm(*p) <= 0)
        // {
        //     *p = distp(gen);
        // }

        *p = 67;
        // int q = *p - 1;

        generate_key_pair(*p, *Ca, *Cb);
        generate_key_pair(*p, *Da, *Db);

        alice << *Ca << '\n'
              << *Cb;
        bob << *Da << '\n'
            << *Db;
        p_key << *p;
    }

    bob.close();
    alice.close();
    p_key.close();

    return 0;
}

int Get_keys(int *p, int *Ca, int *Cb, int *Da, int *Db)
{
    std::ifstream alice("Alice");
    std::ifstream bob("Bob");
    std::ifstream p_key("P");
    p_key >> *p;
    bob >> *Da;
    bob >> *Db;
    alice >> *Ca;
    alice >> *Cb;
    // std::cout << *p << '\n' << *Da << '\n' << *Db;
    // std::cout << *Da;
    return 0;
}

int Shamir_encrypt(char m, int p, int Ca, int Cb, int Da)
{
    int x1 = 0, x2 = 0, x3 = 0;
    x1 = fast_power((int)m, Ca, p);
    x2 = fast_power(x1, Cb, p);
    x3 = fast_power(x2, Da, p);
    return x3;
}

int Shamir_decrypt(int x3, int p, int Db)
{
    return fast_power(x3, Db, p);
    ;
}

int Gamel_encrypt(int *a, int *b, int m, int g, int p, int k, int y)
{
    *a = fast_power(g, k, p);
    *b = m * fast_power(y, k, p);
    return 0;
}

int Gamel_decrypt(int a, int b, int x, int p)
{
    return b * fast_power(a, p - 1 - x, p);
}

int Set_gamel_keys(int *p, int *g, int *x, int *y, int *k, int type)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 1000000);

    if (type)
    {
        int flag = 1;
        int sofi = 0;
        while (flag)
        {
            sofi = dist(gen);
            if (ferm(sofi) > 0 && ferm((2 * sofi + 1)))
                flag = 0;
        }
        *p = sofi * 2 + 1;
        *g = 2;
        for (int i = 2; i < (*p - 1); i++)
        {
            if (fast_power(i, sofi, *p) != 1)
            {
                *g = i;
                break;
            }
        }
        // *p = 7; *g = 20;
        std::uniform_int_distribution<> distx(1, *p);

        std::ofstream alice("Alice");
        std::ofstream bob("Bob");
        std::ofstream open_keys("Open");

        open_keys << *p << '\n'
                  << *g << '\n';
        // std::cout << "| " << *g << " |\n";
        open_keys.close();
        *x = distx(gen);
        bob << *x;
        std::ifstream bobreads("Open");
        bobreads >> *p;
        bobreads >> *g;
        bobreads.close();
        *y = fast_power(*g, *x, *p);
        std::ofstream open("Open", std::ios::app | std::ios::ate);
        open << *y;
        open.close();

        // std::ofstream aliceAB("AliceAB");
        std::uniform_int_distribution<> distp(1, *p - 1);
        *k = distp(gen);
        alice << *k;
        // std::ifstream openb("Open");
        // while(!openb.eof()){
        //     openb >> *y;
        // }
        // openb.close();
        // alice.close();
        // int a = fast_power(*g, *k, *p);

        // std::ifstream
    }
    return 0;
    // else{
    //     // p g x
    //     std::uniform_int_distribution<> distp(1, *p-1);
    //     *k = distp(gen);
    //     *y =

    // }
}

int Gamel_encrypt(int m, int *a, int *b)
{
    std::ifstream open("Open");
    std::ifstream alice("Alice");
    int p = 0, g = 0, k = 0, y = 0;
    open >> p >> g >> y;
    alice >> k;
    *a = fast_power(g, k, p);
    *b = m * fast_power(y, k, p);
    std::ofstream out("OUT.en");
    out << *a << *b;
    open.close();
    alice.close();
    out.close();
    //  std::ifstream bob("Bob");
    //  int x = 0;
    //  bob >> x;
    //  std::cout << ((*b * fast_power(*a, p-1-x, p)) % p) << '\n';
    // std::cout << p << ' ' << g << ' ' << y;
    return 0;
}

int Gamel_decrypt(int a, int b)
{
    std::ifstream bob("Bob");
    int x = 0;
    bob >> x;

    int p = 0;
    std::ifstream open("Open");
    open >> p;
    open.close();
    bob.close();

    return ((b * fast_power(a, p - 1 - x, p)) % p);
}