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
                     "Euclid\n\t4: Shanks step\n\t5: DH sys:\n\t6: Shamir\n";
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
            // int p = 0, Ca = 0, Cb = 0, Da = 0, Db = 0;
            // std::ifstream in("t.txt", std::ios::binary);
            // std::ofstream out("out",std::ios::binary);
        //     char m = 0;
        //     int mode = 1;
            
        //     // in.get(m);
        //     std::cout << "Original:" << (int)m << std::endl;   
        //     std::cout << "1 for encrypt; 0 for decrypt:" << '\n';
        //     std::cin >> mode;
        //     if(mode){        
        //     Set_keys(&p, &Ca, &Cb, &Da, &Db, 0);
        //     Get_keys(&p, &Ca, &Cb, &Da, &Db);
        //     std::string name;
        //     std::cin >> name;
        //     std::ifstream in(name, std::ios::binary);
        //     std::ofstream out_e("out.e", std::ios::binary);
        //     while(!in.eof()){
        //         in.get(m);
        //         char x = (char)Shamir_encrypt(m, p, Ca, Cb, Da);
        //         // out.write((char)x,1);
        //         out_e << x;
        //     }
        //     in.close();
        //     out_e.close();
        // }else{
        //     std::ifstream in_d("out.e",std::ios::binary);
        //     std::ofstream out_d("out.d", std::ios::binary);
        //     char x3 = 0;
        //     while(!in_d.eof()){
        //         x3 = in_d.get();
        //         out_d << Shamir_decrypt((int)x3, p,Db);
        //     }
        //     out_d.close();
        //     in_d.close();
        // }


    int p, Ca, Cb, Da, Db;
    int mode;
    std::string input_file, output_file;

    std::cout << "Выберите режим (0 - шифрование, 1 - расшифрование): ";
    std::cin >> mode;
    std::cout << "Введите имя входного файла: ";
    std::cin >> input_file;
    std::cout << "Введите имя выходного файла: ";
    std::cin >> output_file;

    if (mode == 0) {

        Set_keys(&p, &Ca, &Cb, &Da, &Db, 0);

        std::ifstream fin(input_file, std::ios::binary);
        std::ofstream fout(output_file, std::ios::binary);

        if (!fin || !fout) {
            std::cerr << "Ошибка открытия файлов\n";
            return 1;
        }

        char ch;
        while (fin.get(ch)) {
            int encrypted = Shamir_encrypt(ch, p, Ca, Cb, Da);
            
            fout.write(reinterpret_cast<char*>(&encrypted), sizeof(encrypted));
        }

        fin.close();
        fout.close();
        std::cout << "Шифрование завершено.\n";

    } else if (mode == 1) {
        Get_keys(&p, &Ca, &Cb, &Da, &Db);

        std::ifstream fin(input_file, std::ios::binary);
        std::ofstream fout(output_file);

        if (!fin || !fout) {
            std::cerr << "Ошибка открытия файлов\n";
            return 1;
        }

        int encrypted_value;
        while (fin.read(reinterpret_cast<char*>(&encrypted_value), sizeof(encrypted_value))) {
            int decrypted = Shamir_decrypt(encrypted_value, p, Db);
            char ch = static_cast<char>(decrypted);
            fout.put(ch);
        }

        fin.close();
        fout.close();
        std::cout << "Расшифрование завершено.\n";

    } else {
        std::cerr << "Неверный режим.\n";
        return 1;
    }       
            
            // int x3 = Shamir_encrypt(m, p, Ca, Cb, Da);
            // std::cout << "Crypt: " << x3 << std::endl;
            // std::cout << "Decrypt: " << Shamir_decrypt(x3, p, Db) << std::endl;
            
            // std::cout << Da << "|" << Db;
            
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