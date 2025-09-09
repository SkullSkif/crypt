#include "lab1.hpp"
#include <iostream>

// #include <math.h>

int main()
{
    // std::cout << "hello";
    char input;
    // std::cout << "Input method:\n1: manually\n2: generate rand\n3:generate
    // rand even number";
    char flag = 1;
    int a = 0, x = 0, p = 0, res = 0;
    while (flag) {
        std::cout
                << "Choose task: \n\t1: Fast_power\n\t2: Ferma\n\t3: Euclid\n";
        std::cin >> input;
        switch (input) {
        case '1':
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
        case '2':
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
        case '3':
            int a = -2, b = -2, res = 0;
            std::cout << "Input a (0 for random; -1 for prime random): ";
            std::cin >> a;
            if(a>0){
            std::cout << "Input b (0 for random; -1 for prime random): ";
            std::cin >> b;
            }else{
                if(a==0 || b==0){
                    a = 0; b = 0;
                }
                if(a == -1 || b == -1){
                    a = -1; b = -1;
                }
            }
            res = gen_euclid(&a,&b);
            if(res<0){
                std::cout << "Incorrect number\n";
                break;
            }
            std::cout << "Result:\n\tgdc: " << res << "\n\tx: " << a << "\n\ty: " << b << '\n';
        // default:
        //     return 0;
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