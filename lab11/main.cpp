#include "lab11.hpp"
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
                     "Euclid\n\t4: Shanks step\n\t5: DH sys:\n\t6: Shamir\n\t7: Gamel\n\t8: RSA\n\t9: Vernam\n\tR: RSA sign\n\tG: Gamel sign\n\tH: GOST sign\n\tF: FIPS sign\n";
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
            if (DH(p, g, Xa, Xb))
                std::cout << "Bob received message\n";
            else
                std::cout << "Bod received incorrect message\n";
            break;
        }
        case '6': {
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
                int type = 0;
                // std::cout << "1 for manual, 0 for full rand";
                // std::cin >> type;
                Set_keys(&p, &Ca, &Cb, &Da, &Db, type);

                std::ifstream fin(input_file, std::ios::binary);
                std::ofstream fout(output_file, std::ios::binary);

                if (!fin || !fout) {
                    std::cerr << "Ошибка открытия файлов\n";
                    return 1;
                }

                char ch;
                while (fin.get(ch)) {
                    int encrypted = Shamir_encrypt(ch, p, Ca, Cb, Da);

                    fout.write(
                            reinterpret_cast<char*>(&encrypted),
                            sizeof(encrypted));
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
                while (fin.read(
                        reinterpret_cast<char*>(&encrypted_value),
                        sizeof(encrypted_value))) {
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
            break;
        }
        case '7': {
            int g = 0, k = 0, type = 1;
            x = 0;
            p = 0;
            y = 0;
            a = 0;
            b = 0;

            int mode = 1;
            std::cout << "Encrypt(1) of Decrypt(0):";
            std::cin >> mode;
            if(mode){
            std::cout << "Manuall(0) or Generate(1)?:";
            std::cin >> type;
            Set_gamel_keys(&p, &g, &x, &y, &k, type);
            std::ifstream file("text.txt", std::ios::binary);
            std::ofstream encrout("OUT.en", std::ios::binary);
            char c;
            while (file.get(c)) {
                // char buffer_m[4];
                int m = 0;
                m = static_cast<uint8_t>(c);
                // file.read(buffer_m, 4);
                // m = static_cast<unsigned char>(buffer_m[0]) |
                // (static_cast<unsigned char>(buffer_m[1]) << 8) |
                // (static_cast<unsigned char>(buffer_m[2]) << 16) |
                // (static_cast<unsigned char>(buffer_m[3]) << 24);
                // file.read(reinterpret_cast<char*>(&m), sizeof(m));
                Gamel_encrypt(m, encrout);
            }
            file.close();
            encrout.close();}else{
            std::ofstream out("OUT.de");
            std::ifstream in("OUT.en", std::ios::binary);
            while (in.read(reinterpret_cast<char*>(&a), sizeof(a))
                   && in.read(reinterpret_cast<char*>(&b), sizeof(b))) {
                char decrypted = Gamel_decrypt(a, b);
                out << decrypted;
            }
        }
            break;
        }
        case '8':{
            int m = 0;
            int type;

            int mode;
            std::cout << "Encrypt(1) or Decode(0)";
            std::cin >> mode;
            if(mode){
            std::cout << "Generate(1) or Manuall(0):";
            std::cin >> type;
            Set_RSA_keys(type);
            std::ifstream in_file("text.txt", std::ios::binary);
            std::ofstream out_encrypted("OUT.en", std::ios::binary);
            char ch = 0;
            while(in_file.get(ch)){
                m = static_cast<uint8_t>(ch);
                RSA_encrypt(m, out_encrypted);
            }
            out_encrypted.close();
            in_file.close();
            }else{
            std::ifstream bob_in("OUT.en", std::ios::binary);
            std::ofstream bob_out("OUT.de", std::ios::binary);
            std::ifstream bob_key("Bob");
            std::ifstream open_key("Open");
            int c, e, N;
            bob_key >> c;
            open_key >> N;
            char res;
            while(bob_in.read(reinterpret_cast<char*>(&e), sizeof(e))){
                res = RSA_decrypt(e, c, N);
                bob_out << res;
            }
        }
            
            break;
        }
        case '9':{
            int k = 0, type = 0;
            std::cout << "Encrypt(1) or Decrypt(0)?";
            std::cin >> type;


            if(type){
                DH_setup();
                k=DH_k(1);
                Vernam_encrypt(k);
            }else{
                k=DH_k(2);     
                Vernam_decrypt(k);           
            }

            break;
        }
        case 'R':{
            int type = 0;
            std::cout << "Encrypt(1) or Decrypt(0)?";
            std::cin >> type;  
            if(type){          
            RSA_sign_encrypt();
            }else{
                RSA_sign_decrypt();
            }
            break;
        }
        case 'G':{
            int type = 0;
            std::cout << "Encrypt(1) or Decrypt(0)?";
            std::cin >> type;  
            if(type){          
            Gamel_sign_encrypt();
            }else{
                Gamel_sign_decrypt();
            }
            break;
        }
        case 'H':{
            int type = 0;
            std::cout << "Encrypt(1) or Decrypt(0)?";
            std::cin >> type;  
            GOST(type);                
            break;
        }
        case 'F':{
            int type = 0;
            std::cout << "Encrypt(1) or Decrypt(0)?";
            std::cin >> type;  
            FIPS(type);                
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
