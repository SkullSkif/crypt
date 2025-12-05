#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <random>
#include "lab12.h"

class Player {
public:
    Player();
    Player(uint64_t n_p);

    // ВАЖНО: Деструктор и правила копирования (Rule of Three)
    ~Player();
    Player(const Player& other); // Конструктор копирования
    Player& operator=(const Player& other); // Оператор присваивания
    bool operator!=(const Player r);

    // Теперь методы принимают индекс (0 или 1)
    uint64_t get_card(int index) const;
    void set_card(int index, uint64_t new_card);

    // Остальные геттеры без изменений
    uint64_t get_d() const;
    uint64_t get_e() const;
    uint64_t get_p() const;
    QString get_name() const;

    uint64_t encrypt(uint64_t msg);
    uint64_t decrypt(uint64_t cipher);

private:
    void UpdateP(uint64_t new_p);

    uint64_t p, e, d;

    // ВАЖНО: Указатель на массив
    uint64_t* cards;

    QString name;

    static std::random_device rd;
    static std::mt19937 gen;
};

#endif // PLAYER_H
