#include <iostream>
#include <fstream>
#include <random>
#include "MD5.h"
#include <cstdint>
#include <stdexcept>
#include <climits>
#include <string>
#include <sstream>
#include <cmath>
#include <numeric>
#include <vector>



uint32_t hash_to_int(const std::string& hash, uint64_t q) {
    uint32_t result = 0;
    
    for (size_t i = 0; i < hash.size(); ++i) {
        uint64_t temp = (static_cast<uint64_t>(result) * 256 + 
                        static_cast<unsigned char>(hash[i]));
        result = temp % q;
    }
    
    return result;
}

bool ferma(uint64_t n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (uint64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int64_t euclid(int64_t a, int64_t b, int64_t& x, int64_t& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    
    int64_t x1, y1;
    int64_t gcd = euclid(b, a % b, x1, y1);
    
    x = y1;
    y = x1 - (a / b) * y1;
    
    return gcd;
}

uint64_t mod_pow(uint64_t x, uint64_t y, uint64_t p) {
    if (p == 1) return 0;
    
    x = x % p;
    uint64_t result = 1;
    
    while (y > 0) {
        if (y & 1) {
            result = (static_cast<unsigned __int128>(result) * x) % p;
        }
        x = (static_cast<unsigned __int128>(x) * x) % p;
        y >>= 1;
    }
    
    return result;
}

int64_t mod_inverse(int64_t a, int64_t m) {
    int64_t x, y;
    int64_t gcd = euclid(a, m, x, y);
    
    if (gcd != 1) {
        return -1; 
    }
    
    return (x % m + m) % m;
}

void server_set_Blind_vote() {
    uint64_t P, Q;
    
    std::random_device rd;
    std::mt19937_64 gen(rd());
    
    std::uniform_int_distribution<uint64_t> dist(10000, 50000);
    
    do {
        P = dist(gen);
    } while (!ferma(P));
    
    do {
        Q = dist(gen);
    } while (!ferma(Q) || Q == P);
    
    uint64_t N = P * Q;
    uint64_t fi = (P - 1) * (Q - 1);
    
    uint64_t d = dist(gen);
    do {
        d = dist(gen);
    } while (!ferma(d));    
    if (d >= fi) {
        d = 17; 
    }
    
    int64_t x, y;
    while (euclid(static_cast<int64_t>(d), static_cast<int64_t>(fi), x, y) != 1) {
        d += 2;
        if (d >= fi) d = 3;
    }
    
    int64_t c_int = mod_inverse(static_cast<int64_t>(d), static_cast<int64_t>(fi));
    uint64_t c = (c_int < 0) ? c_int + fi : c_int;
    
    uint64_t check = (static_cast<unsigned __int128>(d) * c) % fi;
    
    std::cout << "Server keys generated:" << std::endl;
    std::cout << "P = " << P << ", Q = " << Q << std::endl;
    std::cout << "N = " << N << std::endl;
    std::cout << "fi = " << fi << std::endl;
    std::cout << "Public d = " << d << std::endl;
    std::cout << "Private c = " << c << std::endl;
    std::cout << "Check: d * c mod fi = " << check << std::endl;
    
    std::ofstream open_keys_write("Open.txt");
    open_keys_write << N << '\n' << d;
    open_keys_write.close();
    
    std::ofstream server_key_write("Server.txt");
    server_key_write << c << '\n' << N;
    server_key_write.close();
}

std::pair<uint64_t, uint64_t> alice_set_Blind_vote(char voice) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint32_t> dist_rnd(1, 0xFFFFFFFF);
    uint32_t rnd = dist_rnd(gen);
    
    uint32_t v = 0;
    switch(voice) {
        case 'Y':
        case 'y':
            v = 1;
            break;
        case 'N':
        case 'n':
            v = 0;
            break;
        case 'A':
        case 'a':
            v = 2;
            break;
        default:
            v = 2;
            break;
    }
    
    uint64_t n = (static_cast<uint64_t>(rnd) << 32) | v;
    std::cout << "\nAlice: Generated n = " << n << std::endl;
    std::cout << "  rnd = " << rnd << ", vote = " << v << std::endl;
    
    std::ifstream open_keys_read("Open.txt");
    uint64_t N, d;
    open_keys_read >> N >> d;
    open_keys_read.close();
    
    std::cout << "\nAlice: Loaded public key:" << std::endl;
    std::cout << "  N = " << N << std::endl;
    std::cout << "  d = " << d << std::endl;
    
    auto hash_str = md5(std::to_string(n));
    uint64_t h = hash_to_int(hash_str, N);
    std::cout << "\nAlice: Hash h = " << h << " (mod N)" << std::endl;
    
    uint64_t r;
    std::uniform_int_distribution<uint64_t> dist_r(2, N-1);
    int64_t x, y;
    
    do {
        r = dist_r(gen);
    } while (euclid(r, N, x, y) != 1);
    
    std::cout << "\nAlice: Generated r = " << r << std::endl;
    
    uint64_t r_pow_d = mod_pow(r, d, N);
    uint64_t h_bar = (static_cast<unsigned __int128>(h) * r_pow_d) % N;
    
    std::cout << "\nAlice: Sending h_bar = " << h_bar << " to server" << std::endl;
    
    std::ifstream server_key_read("Server.txt");
    uint64_t c, N_server;
    server_key_read >> c >> N_server;
    server_key_read.close();
    
    if (N != N_server) {
        std::cerr << "Error: N mismatch between keys!" << std::endl;
        return {0, 0};
    }
    
    uint64_t s_bar = mod_pow(h_bar, c, N);
    std::cout << "\nServer: Signed message s_bar = " << s_bar << std::endl;
    
    int64_t r_inv = mod_inverse(static_cast<int64_t>(r), static_cast<int64_t>(N));
    if (r_inv == -1) {
        std::cerr << "Error: Cannot find inverse of r mod N!" << std::endl;
        return {0, 0};
    }
    
    uint64_t s = (static_cast<unsigned __int128>(s_bar) * static_cast<uint64_t>(r_inv)) % N;
    
    std::cout << "\nAlice: Removed encode" << std::endl;
    std::cout << "  r^(-1) mod N = " << r_inv << std::endl;
    std::cout << "  Final signature s = " << s << std::endl;
    
    uint64_t check = mod_pow(s, d, N);
    std::cout << "\nAlice: Checking signature locally:" << std::endl;
    std::cout << "  s^d mod N = " << check << std::endl;
    std::cout << "  h mod N = " << (h % N) << std::endl;
    std::cout << "  Signature is " << ((check == (h % N)) ? "VALID" : "INVALID") << std::endl;
    
    return std::make_pair(n, s);
}

bool server_verify_vote(uint64_t n, uint64_t s) {
    std::ifstream open_keys_read("Open.txt");
    uint64_t N, d;
    open_keys_read >> N >> d;
    open_keys_read.close();
    
    auto hash_str = md5(std::to_string(n));
    uint64_t h = hash_to_int(hash_str, N);
    
    uint64_t s_pow_d = mod_pow(s, d, N);
    uint64_t h_mod_N = h % N;
    
    std::cout << "\nServer verification:" << std::endl;
    std::cout << "  n = " << n << std::endl;
    std::cout << "  s = " << s << std::endl;
    std::cout << "  h = " << h << std::endl;
    std::cout << "  h mod N = " << h_mod_N << std::endl;
    std::cout << "  s^d mod N = " << s_pow_d << std::endl;
    
    bool valid = (h_mod_N == s_pow_d);
    std::cout << "  Vote is " << (valid ? "VALID" : "INVALID") << std::endl;
    
    return valid;
}

int main() {
        std::cout << "||||| Step 1: Server generates keys |||||" << std::endl;
        server_set_Blind_vote();
        
        std::cout << "\n||||| Step 2: Alice votes |||||" << std::endl;
        char vote;
        std::cout << "Enter vote (Y/N/A): ";
        std::cin >> vote;
        
        auto bulletin = alice_set_Blind_vote(vote);
        
        if (bulletin.first == 0 && bulletin.second == 0) {
            std::cerr << "Error creating bulletin!" << std::endl;
            return 1;
        }
        
        std::cout << "\n|||| Step 3: Alice sends to voting server ||||" << std::endl;
        std::cout << "bulletin: <n=" << bulletin.first << ", s=" << bulletin.second << ">" << std::endl;
        
        std::cout << "\n||||| Step 4: Server verifies !! |||||" << std::endl;
        bool isValid = server_verify_vote(bulletin.first, bulletin.second);
        
        if (isValid) {
            std::cout << "\nVote successfully counted!" << std::endl;
            uint32_t vote_result = static_cast<uint32_t>(bulletin.first & 0xFFFFFFFF);
            std::cout << "Vote value: " << vote_result << " (";
            switch(vote_result) {
                case 0: std::cout << "No"; break;
                case 1: std::cout << "Yes"; break;
                case 2: std::cout << "Abstain"; break;
                default: std::cout << "Unknown"; break;
            }
            std::cout << ")" << std::endl;
        } else {
            std::cout << "\nVote rejected!" << std::endl;
        }
        

    
    return 0;
}