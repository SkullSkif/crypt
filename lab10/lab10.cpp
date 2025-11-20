#include "lab10.hpp"
#include "MD5.h"

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

int DH(int p, int g, int Xa, int Xb)
{
    int Ya = 0, Yb = 0, Za = 0, Zb = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(10000, 1000000);
    if (p == 0) {
        int flag = 1;
        int sofi = 0;
        while (flag) {
            sofi = dist(gen);
            if (ferm(sofi) > 0 && ferm((2 * sofi + 1)))
                flag = 0;
        }
        p = sofi * 2 + 1;
        g = 2;
        for (int i = 2; i < (p - 1); i++) {
            if (fast_power(i, sofi, p) != 1) {
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

int gcd(int a, int b, int* x, int* y)
{
    if (b == 0) {
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

void generate_key_pair(int p, int& a, int& b)
{
    int q = p - 1;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, q - 1);

    while (true) {
        a = dist(gen);
        int x, y;
        int g = gcd(a, q, &x, &y);
        if (g == 1) {
            b = x % q;
            if (b < 0)
                b += q;
            break;
        }
    }
}

int Set_keys(int* p, int* Ca, int* Cb, int* Da, int* Db, int type)
{
    std::ofstream alice("Alice");
    std::ofstream bob("Bob");
    std::ofstream p_key("P");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distp(1, 255);

    if (type) {
        // int q = *p - 1;

        generate_key_pair(*p, *Da, *Db);

        alice << *Ca << '\n' << *Cb;
        bob << *Da << '\n' << *Db;
        p_key << *p;
    } else {
        // *p = distp(gen);
        // while (ferm(*p) <= 0)
        // {
        //     *p = distp(gen);
        // }

        *p = 67;
        // int q = *p - 1;

        generate_key_pair(*p, *Ca, *Cb);
        generate_key_pair(*p, *Da, *Db);

        alice << *Ca << '\n' << *Cb;
        bob << *Da << '\n' << *Db;
        p_key << *p;
    }

    bob.close();
    alice.close();
    p_key.close();

    return 0;
}

int Get_keys(int* p, int* Ca, int* Cb, int* Da, int* Db)
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

int Gamel_encrypt(int* a, int* b, int m, int g, int p, int k, int y)
{
    *a = fast_power(g, k, p);
    *b = m * fast_power(y, k, p);
    return 0;
}

int Gamel_decrypt(int a, int b, int x, int p)
{
    return b * fast_power(a, p - 1 - x, p);
}

int Set_gamel_keys(int* p, int* g, int* x, int* y, int* k, int type)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 1000000);

    if (type) {
        int flag = 1;
        int sofi = 0;
        while (flag) {
            sofi = dist(gen);
            if (ferm(sofi) > 0 && ferm((2 * sofi + 1)))
                flag = 0;
        }
        *p = sofi * 2 + 1;
        *g = 2;
        for (int i = 2; i < (*p - 1); i++) {
            if (fast_power(i, sofi, *p) != 1) {
                *g = i;
                break;
            }
        }
        std::uniform_int_distribution<> distx(1, *p);

        std::ofstream alice("Alice");
        std::ofstream bob("Bob");
        std::ofstream open_keys("Open");

        open_keys << *p << '\n' << *g << '\n';
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

        std::uniform_int_distribution<> distp(1, *p - 1);
        int k_t, p_t;
        *k = distp(gen);
        k_t = *k;
        p_t = *p;
        while (gen_euclid(&k_t, &p_t)) {
            *k = distp(gen);
            k_t = *k;
            p_t = *p;
        }
        alice << *k;
        // *k = distp(gen);
        // alice << *k;
    } else {
        //     // p g x
        std::cout << "Input p: ";
        std::cin >> *p;
        std::cout << "Input g: ";
        std::cin >> *g;
        std::cout << "Input x: ";
        std::cin >> *x;
        std::ofstream alice("Alice");
        std::ofstream bob("Bob");
        std::ofstream open_keys("Open");

        open_keys << *p << '\n' << *g << '\n';
        open_keys.close();
        bob << *x;
        std::ifstream bobreads("Open");
        bobreads >> *p;
        bobreads >> *g;
        bobreads.close();
        *y = fast_power(*g, *x, *p);
        std::ofstream open("Open", std::ios::app | std::ios::ate);
        open << *y;
        open.close();

        std::uniform_int_distribution<> distp(1, *p - 1);
        *k = distp(gen);
        alice << *k;
        //     std::uniform_int_distribution<> distp(1, *p-1);
        //     *k = distp(gen);
        //     *y =
    }
    return 0;
}

int Gamel_encrypt(int m, std::ofstream& out)
{
    std::ifstream open("Open");
    std::ifstream alice("Alice");
    int p = 0, g = 0, k = 0, y = 0, a = 0, b = 0;
    open >> p >> g >> y;
    alice >> k;
    a = fast_power(g, k, p);
    b = ((m * fast_power(y, k, p)) % p);

    out.write(reinterpret_cast<const char*>(&a), sizeof(a));
    out.write(reinterpret_cast<const char*>(&b), sizeof(b));
    open.close();
    alice.close();

    return 0;
}

char Gamel_decrypt(int a, int b)
{
    std::ifstream bob("Bob");
    int x = 0;
    bob >> x;

    int p = 0;
    std::ifstream open("Open");
    open >> p;
    open.close();
    bob.close();
    char m = (char)((b * fast_power(a, p - 1 - x, p)) % p);

    return m;
}

int invert_c(int d, int fi)
{
    int x, y;
    int g = gcd(d, fi, &x, &y);
    if (g != 1) {
        return -1;
    }
    return (x % fi + fi) % fi;
}

void Set_RSA_keys(int type)
{
    int P = 0, Q = 0, d = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    if (type) {
        P = dist(gen);
        while (ferm(P) <= 0)
            P = dist(gen);

        Q = dist(gen);
        while (ferm(Q) <= 0)
            Q = dist(gen);
        int N = P * Q;
        int fi = (P - 1) * (Q - 1);

        std::uniform_int_distribution<> distD(1, fi);
        d = distD(gen);
        int c1 = d;
        int c2 = fi;
        while (d < fi) {
            if (gcd(d, fi, &c1, &c2) == 1) {
                break;
            }
            d = distD(gen);
        }
        // std::cout << "d: " << d << " fi: " << fi;
        int c = invert_c(d, fi);
        // std::cout << " c: " << c << std::endl;

        std::ofstream open_keys_write("Open");
        open_keys_write << N << '\n' << d;
        open_keys_write.close();

        std::ofstream alice_key_write("Alice");
        alice_key_write << c;
        alice_key_write.close();
    } else {
        std::cout << "Input p:";
        std::cin >> P;
        std::cout << "Input q:";
        std::cin >> Q;
        std::cout << "Input d:";
        std::cin >> d;
        int N = P * Q;
        int fi = (P - 1) * (Q - 1);
        // int c1 = d;
        // int c2 = fi;
        // std::uniform_int_distribution<> distD(1, fi);
        // while (d < fi) {
        //     if (gcd(d, fi, &c1, &c2) == 1) {
        //         break;
        //     }
        //     d = distD(gen);
        // }
        std::cout << "d: " << d << " fi: " << fi;
        int c = invert_c(d, fi);
        std::cout << " c: " << c << std::endl;

        std::ofstream open_keys_write("Open");
        open_keys_write << N << '\n' << d;
        open_keys_write.close();

        std::ofstream alice_key_write("Alice");
        alice_key_write << c;
        alice_key_write.close();
    }
}

void RSA_encrypt(int m, std::ofstream& out)
{
    std::ifstream in_alice("Open");
    int N, d;
    in_alice >> N >> d;
    in_alice.close();
    int e = fast_power(m, d, N);
    out.write(reinterpret_cast<const char*>(&e), sizeof(e));
}

char RSA_decrypt(int e, int c, int N)
{
    char m = fast_power(e, c, N);
    return m;
}

void DH_setup()
{
    int Ya = 0, Yb = 0, p = 0, g = 0, Xa = 0, Xb = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 1000000);
    int flag = 1;
    int sofi = 0;
    while (flag) {
        sofi = dist(gen);
        if (ferm(sofi) > 0 && ferm((2 * sofi + 1)))
            flag = 0;
    }
    p = sofi * 2 + 1;
    g = 2;
    for (int i = 2; i < (p - 1); i++) {
        if (fast_power(i, sofi, p) != 1) {
            g = i;
            break;
        }
    }
    std::uniform_int_distribution<> distp(1, p);
    Xa = distp(gen);
    Xb = distp(gen);
    std::ofstream open("Open");
    open << p << '\n' << g;
    std::ofstream alice("Alice");
    std::ofstream bob("Bob");
    alice << Xa;
    bob << Xb;
    open.close();
    alice.close();
    bob.close();
    std::ofstream openY("OpenY");
    Ya = fast_power(g, Xa, p);

    Yb = fast_power(g, Xb, p);

    openY << Ya << '\n' << Yb;
    openY.close();
}

int DH_k(int person)
{
    int p = 0, g = 0;
    if (person) {
        int Xa = 0, Ya = 0, Yb = 0, Za = 0;
        std::ifstream alice("Alice");
        std::ifstream open("Open");
        std::ifstream openY("OpenY");
        alice >> Xa;
        open >> p >> g;
        openY >> Ya >> Yb;
        alice.close();
        open.close();
        openY.close();
        Za = fast_power(Yb, Xa, p);
        return Za;
    } else {
        int Xb = 0, Ya = 0, Yb = 0, Zb = 0;
        std::ifstream bob("Bob");
        std::ifstream open("Open");
        std::ifstream openY("OpenY");
        bob >> Xb;
        open >> p >> g;
        openY >> Ya >> Yb;
        bob.close();
        open.close();
        openY.close();
        Zb = fast_power(Ya, Xb, p);
        return Zb;
    }
}

void Vernam_encrypt(int k)
{
    std::ifstream file("text.txt", std::ios::binary);
    std::ofstream file_en("OUT.en", std::ios::binary);
    int source_byte;
    while ((source_byte = file.get()) != EOF) {
        std::uint8_t encrypted_byte = static_cast<std::uint8_t>(source_byte)
                ^ static_cast<std::uint8_t>(k);
        file_en.write(reinterpret_cast<char*>(&encrypted_byte), 1);
    }
    file.close();
    file_en.close();
}

void Vernam_decrypt(int k)
{
    std::ifstream file("OUT.en", std::ios::binary);
    std::ofstream file_de("OUT.de", std::ios::binary);
    int source_byte;
    while ((source_byte = file.get()) != EOF) {
        std::uint8_t decrypted_byte = static_cast<std::uint8_t>(source_byte)
                ^ static_cast<std::uint8_t>(k);
        file_de.write(reinterpret_cast<char*>(&decrypted_byte), 1);
    }

    file_de.close();
    file.close();
}

std::vector<unsigned char> MD5bytes(const std::string& str)
{
    std::string hex_str = md5(str);

    std::vector<unsigned char> bytes;
    for (size_t i = 0; i < hex_str.length(); i += 2) {
        std::string byte_string = hex_str.substr(i, 2);
        unsigned char byte = static_cast<unsigned char>(
                std::stoul(byte_string, nullptr, 16));
        bytes.push_back(byte);
    }

    return bytes;
}

void RSA_sign_encrypt()
{
    std::ifstream file("text.txt");

    std::string m, m_;
    while (std::getline(file, m_)) {
        m += m_ + '\n';
    }
    file.close();

    std::vector<unsigned char> bytes = MD5bytes(m);

    // for (auto b : hash_bytes) {
    //     std::cout << std::hex << (int)b << " ";
    // }
    // std::cout << std::endl;

    Set_RSA_keys(1);
    std::ifstream closed_key("Alice");
    std::ifstream open_key("Open");
    int c, N;
    closed_key >> c;
    open_key >> N;
    closed_key.close();
    open_key.close();
    std::ofstream sign("Sign");

    for (unsigned char hb : bytes) {
        int encrypted = fast_power(static_cast<int>(hb), c, N);
        sign << encrypted << " ";
    }

    sign.close();
}

void RSA_sign_decrypt()
{
    std::ifstream file("text.txt");

    std::string m, m_;
    while (std::getline(file, m_)) {
        m += m_ + '\n';
    }
    file.close();
    std::vector<unsigned char> hash_bytes = MD5bytes(m);

    std::ifstream sign("Sign");
    std::vector<int> signed_hash;
    int signed_hash_element;
    while (sign >> signed_hash_element) {
        signed_hash.push_back(signed_hash_element);
    }
    sign.close();

    std::ifstream open_key("Open");
    int d, N;
    open_key >> N;
    open_key >> d;
    open_key.close();

    for (size_t i = 0; i < signed_hash.size(); i++) {
        int decrypted = fast_power(signed_hash[i], d, N);
        std::cout << decrypted << ':' << (int)hash_bytes[i] << std::endl;

        if (decrypted != static_cast<int>(hash_bytes[i])) {
            std::cout << "incorrect decrypt: " << i << std::endl;
            break;
        }
    }
}

void Set_sign_gamel_keys()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 1000000);
    int p, g, k, x, y;
    int flag = 1;
    int sofi = 0;
    while (flag) {
        sofi = dist(gen);
        if (ferm(sofi) > 0 && ferm((2 * sofi + 1)))
            flag = 0;
    }
    p = sofi * 2 + 1;
    g = 2;
    for (int i = 2; i < (p - 1); i++) {
        if (fast_power(i, sofi, p) != 1) {
            g = i;
            break;
        }
    }
    std::uniform_int_distribution<> distx(1, p - 1);

    std::ofstream alice("Alice");
    std::ofstream open_keys("Open");

    open_keys << p << '\n' << g << '\n';
    open_keys.close();
    x = distx(gen);
    alice << x << '\n';
    y = fast_power(g, x, p);
    std::ofstream open("Open", std::ios::app | std::ios::ate);
    open << y;
    open.close();

    std::uniform_int_distribution<> distk(1, p - 2);
    k = distk(gen);
    
    int c1,c2;
    while (gcd(k, p-1,&c1,&c2) != 1) {
        k = distk(gen);
    }    
    
    alice << k << '\n';
    int r = fast_power(g, k, p);
    alice << r;
    alice.close();
}

void Gamel_sign_encrypt()
{
    std::ifstream file("text.txt");
    std::string m, m_;
    while (std::getline(file, m_)) {
        m += m_ + '\n';
    }
    file.close();

    std::vector<unsigned char> bytes = MD5bytes(m);
    Set_sign_gamel_keys();
    
    std::ifstream closed_keys("Alice");
    int x, k, r;
    closed_keys >> x >> k >> r;
    closed_keys.close();
    
    std::ifstream open_keys("Open");
    int p;
    open_keys >> p;
    open_keys.close();
    
    std::ofstream sign("Sign");
    sign << r << " ";
    
    for (unsigned char hb : bytes) {
        int H = static_cast<int>(hb);
        
        int u = (H - x * r) % (p-1);
        if (u < 0) u += (p-1); 
        
        int k_inv = invert_c(k, p-1);
        
        int s = (k_inv * u) % (p-1);
        if (s < 0) s += (p-1);
        
        sign << s << " ";
    }
    sign.close();
}

void Gamel_sign_decrypt()
{
    std::ifstream file("text.txt");
    std::string m, m_;
    while (std::getline(file, m_)) {
        m += m_ + '\n';
    }
    file.close();
    std::vector<unsigned char> hash_bytes = MD5bytes(m);

    std::ifstream sign("Sign");
    int r;
    sign >> r;
    
    std::vector<int> signed_hash;
    int signed_hash_element;
    while (sign >> signed_hash_element) {
        signed_hash.push_back(signed_hash_element);
    }
    sign.close();    
    
    std::ifstream open("Open");
    int p, g, y;
    open >> p >> g >> y;
    open.close();

    for (size_t i = 0; i < signed_hash.size(); i++) {
        int hb = static_cast<int>(hash_bytes[i]);
        int s = signed_hash[i];
        
        int decrypt_l = fast_power(g, hb, p);
        
        int ypow = fast_power(y, r, p);
        int rpow = fast_power(r, s, p);
        int decrypt_r = (ypow * rpow) % p;
        
        std::cout << "byte: " << i << "[" << decrypt_l 
                  << " | " << decrypt_r << "]" << std::endl;
        
        if (decrypt_l != decrypt_r) {
            std::cout << "incorrect decrypt: " << i << std::endl;
        }
    }
}

uint32_t hash_to_int(const std::string& hash, uint32_t q) {
    uint32_t result = 0;
    
    for (size_t i = 0; i < hash.size(); ++i) {
        uint64_t temp = (static_cast<uint64_t>(result) * 256 + 
                        static_cast<unsigned char>(hash[i]));
        result = temp % q;
    }
    
    return result;
}

// uint32_t mul(uint32_t a, uint32_t b, uint32_t mod) {
//     return ((a % mod) * (b % mod)) % mod;
// }

uint32_t mul(uint32_t a, uint32_t b, uint32_t q) {
    uint64_t mul_result = static_cast<uint64_t>(a) * static_cast<uint64_t>(b);
    return static_cast<uint32_t>(mul_result % q);
}

void GOST(int type){
    if (type){
    uint32_t p = 0;
    uint16_t q = 0;
    uint32_t b;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1000, 10000);   
    q = dist(gen);
    while (ferm(q) <= 0)
        q = dist(gen);    
    uint32_t max_b = 0xFFFF / q;

    for (b = 2; b <= max_b && b <= 10000; ++b) {
        p = b * q + 1;
        
        if (p > 0xFFFFFFFF) continue;
        
        if (ferm(p)) {
            break;
        }
    }

    std::uniform_int_distribution<> distg(2, p-2);
    uint32_t g = distg(gen);
    uint32_t a = fast_power(g,b,p);
    while(a<=1){
        g = distg(gen);
        a = fast_power(g,b,p);
    }
    std::uniform_int_distribution<> distx(1, q-1);
    
    uint32_t y, x;
    x = distx(gen);
    y = fast_power(a,x,p); 
    std::ifstream file("text.txt");

    std::string m, m_;

    while (std::getline(file, m_)) {
        m += m_ + '\n';
    }
    file.close();
 
    auto hash_string = md5(m);
    uint64_t h = hash_to_int(hash_string, q);
    if(h==0) h=1;
    uint32_t k;
    uint32_t r = 0;

    uint32_t s = 0;

   while((r==0) || (s==0)){
        k = distx(gen);
        r = (fast_power(a, k, p) % q);
        if (r==0) continue;
    uint64_t s_temp = (static_cast<uint64_t>(k) * h + static_cast<uint64_t>(x) * r) % q;
    s = static_cast<uint32_t>(s_temp);
        // uint32_t s_1 = mul(k, h, q);
        // uint32_t s_2 = mul(x, r, q);
        //     s = (s_1 + s_2) % q;    
    }
                                           
    std::ofstream sign("Sign");
    sign << r << '\n';

    sign << s;
    sign.close();
    std::ofstream open("Open");
    open << p << ' ' << q << ' ' << a << ' ' << y;
    open.close();
    } else {
            
        std::ifstream file("text.txt");

        std::string m, m_;

        while (std::getline(file, m_)) {
            m += m_ + '\n';
        }
        file.close();     
        uint32_t p, a, y;
        uint16_t q;
        std::ifstream open("Open");
        open >> p >> q >> a >> y;
        open.close();
    
        auto hash_string = md5(m);
        uint64_t h = hash_to_int(hash_string, q);
        if(h==0) h=1;
      

        uint32_t r, s;
        std::ifstream sign("Sign");
        sign >> r >> s;  

        sign.close();    
        
        if ((s>0)&&(s<q)){
            std::cout << "S_OK!\n";
        } else{
            std::cout << "S_ERROR!\n";
        }
        if ((r>0)&&(r<q)){
            std::cout << "R_OK!\n";
        } else{
            std::cout << "R_ERROR!\n";
        }
        uint32_t u1, u2, v,h_inv;
        uint32_t a_u1, y_u2, temp;

        h_inv = invert_c(h,q);
        u1 = mul(s, h_inv, q);
        u2 = mul((q - r) % q, h_inv, q);

        a_u1 = fast_power(a, u1, p);
        y_u2 = fast_power(y, u2, p);
        temp = mul(a_u1, y_u2, p);
        v = temp % q;

// std::cout << "  q: " << q << "\n";
// std::cout << "  p: " << p << "\n";
//                 std::cout << "  h_inv: " << h_inv << ", u1: " << u1 << ", u2: " << u2 << "\n";
//                 std::cout << "  a_u1: " << a_u1 << ", y_u2: " << y_u2 << "\n";
                // std::cout << "  temp: " << temp << ", v: " << v << ", r: " << r << ", s: " << s << "\n";        
            if(v!=r){
                std::cout << "INCORRECT_SIGN!\n";
            }else{
                std::cout << "CORRECT_SIGN\n";
            }


    }
}