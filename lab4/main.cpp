#include "lab4.hpp"
#include <iostream>

// #include <math.h>

int main()
{
    // std::cout << "hello";
    char input;
    // std::cout << "Input method:\n1: manually\n2: generate rand\n3:generate
    // rand even number";
    char flag = 1;
    int a = 0, x = 0, p = 0, res = 0, y = 0, b = 0;
    while (flag) {
        std::cout << "Choose task: \n\t1: Fast_power\n\t2: Ferma\n\t3: "
                     "Euclid\n\t4: Shanks step\n\t5: DH sys:\n";
        std::cin >> input;
        switch (input) {
        case '1': {
            a = 0;
            x = 0;
            p = 0;
            std::cout << "Input a,x,p:\n";
            std::cout << "\ta: ";
            std::cin >> a;
            std::cout << '\n';
            std::cout << "\tx: ";
            std::cin >> x;
            std::cout << '\n';
            std::cout << "\tp: ";
            std::cin >> p;
            std::cout << '\n';
            std::cout << "Result: " << fast_power(a, x, p) << '\n';
            break;
        }
        case '2': {
            p = 0;
            std::cout << "Input number: ";
            std::cin >> p;

            res = ferm(p);
            if (res > 0) {
                std::cout << "Result: Number is prime\n";
            } else {
                if (res == 0)
                    std::cout << "Result: Number not prime\n";
                else
                    std::cout << "Incorrect number\n";
            }
            break;
        }
        case '3': {
            a = -2;
            res = 0;
            b = -2;
            std::cout << "Input a (0 for random; -1 for prime random): ";
            std::cin >> a;
            if (a > 0) {
                std::cout << "Input b (0 for random; -1 for prime random): ";
                std::cin >> b;
            } else {
                if (a == 0 || b == 0) {
                    a = 0;
                    b = 0;
                }
                if (a == -1 || b == -1) {
                    a = -1;
                    b = -1;
                }
            }
            res = gen_euclid(&a, &b);
            if (res < 0) {
                std::cout << "Incorrect number\n";
                break;
            }
            std::cout << "Result:\n\tgdc: " << res << "\n\tx: " << a
                      << "\n\ty: " << b << '\n';
            break;
        }
        case '4': {
            a = 0;
            y = 0;
            p = 0;
            int flag_rand_step = 1;
            std::cout << "Input a (0 for random): ";
            std::cin >> a;
            if (a == 0)
                flag_rand_step = 0;
            if (flag_rand_step) {
                std::cout << "Input y: ";
                std::cin >> y;
                std::cout << "Input p: ";
                std::cin >> p;
            }
            std::cout << '\n' << step(a, y, p);
            // step(a, y, p);
            break;
        }
        case '5': {
            p = 0;
            int g = 0, Xa = 0, Xb = 0;
            
            int flag_rand_DH = 1;
            std::cout << "Input p (0 for random): ";
            std::cin >> p;
            if (p == 0)
                flag_rand_DH = 0;
            if (flag_rand_DH) {
                std::cout << "Input g: ";
                std::cin >> g;
                std::cout << "Input Xa: ";
                std::cin >> Xa;
                std::cout << "Input Xb: ";
                std::cin >> Xb;
            }
            if(DH(p, g, Xa, Xb))
                std::cout << "Bob received message\n";
            else
                std::cout << "Bod received incorrect message\n";
            break;
        }
        case '6': {
            
            // p = 0;
            // int m = 0, Ca = 0, Cb = 0;
            
            // int flag_rand_DH = 1;
            // std::cout << "Input p (0 for random): ";
            // std::cin >> p;
            // if (p == 0)
            //     flag_rand_DH = 0;
            // if (flag_rand_DH) {
            //     std::cout << "Input g: ";
            //     std::cin >> g;
            //     std::cout << "Input Xa: ";
            //     std::cin >> Xa;
            //     std::cout << "Input Xb: ";
            //     std::cin >> Xb;
            // }
            // if(DH(p, g, Xa, Xb))
            //     std::cout << "Bob received message\n";
            // else
            //     std::cout << "Bod received incorrect message\n";
            break;
        }
        }
        std::cout << "Continue? [y/n]: ";
        std::cin >> input;
        if (input != 'y')
            flag = 0;
        else
            std::cout << "\n\n\n";
    }
    return 0;
}