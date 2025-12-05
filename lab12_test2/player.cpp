#include "player.h"

std::random_device Player::rd;
std::mt19937 Player::gen(Player::rd());
uint8_t plname = 0;

// Конструктор по умолчанию
Player::Player() : p(0), e(0), d(0) {
    name = "Unknown";
    // Выделяем память под 2 карты
    cards = new uint64_t[2];
    cards[0] = 0;
    cards[1] = 0;
}

// Основной конструктор
Player::Player(uint64_t n_p) : p(n_p) {
    // Выделяем память под 2 карты
    cards = new uint64_t[2];
    cards[0] = 0;
    cards[1] = 0;

    name = QString("Player %1").arg(plname++);
    UpdateP(p);
}

// Деструктор: Обязательно удаляем массив!
Player::~Player() {
    if (cards) {
        delete[] cards;
    }
}

// Конструктор копирования (Нужен для std::vector)
// Когда вектор расширяется, он копирует объекты. Без этого будет краш.
Player::Player(const Player& other)
    : p(other.p), e(other.e), d(other.d), name(other.name)
{
    cards = new uint64_t[2];
    cards[0] = other.cards[0];
    cards[1] = other.cards[1];
}

// Оператор присваивания (Нужен для a = b)
Player& Player::operator=(const Player& other) {
    if (this != &other) {
        // Удаляем старое
        delete[] cards;

        // Копируем поля
        p = other.p;
        e = other.e;
        d = other.d;
        name = other.name;

        // Создаем новое и копируем значения
        cards = new uint64_t[2];
        cards[0] = other.cards[0];
        cards[1] = other.cards[1];
    }
    return *this;
}

// Обновленные методы доступа к картам
uint64_t Player::get_card(int index) const {
    if (index >= 0 && index < 2) {
        return cards[index];
    }
    return 0; // Ошибка индекса
}

void Player::set_card(int index, uint64_t new_card) {
    if (index >= 0 && index < 2) {
        cards[index] = new_card;
    }
}

bool Player::operator!=(Player r) {
    return !(r.name == name && r.e == e && r.d == d);
}

// ... Остальные методы (get_d, encrypt, UpdateP) остались без изменений ...
uint64_t Player::get_d() const { return d; }
uint64_t Player::get_e() const { return e; }
uint64_t Player::get_p() const { return p; }
QString Player::get_name() const { return name; }

uint64_t Player::encrypt(uint64_t x) {
    return fast_exp_mod(x, e, p);
}

uint64_t Player::decrypt(uint64_t c) {
    return fast_exp_mod(c, d, p);
}

void Player::UpdateP(uint64_t new_p) {
    uint64_t phi = p - 1;
    uint64_t tmp;
    for (;;) {
        do {
            e = gen() % phi + 3;
        } while (fast_euclid(phi, e, 0, 0, &tmp, &tmp) != 1 && (int64_t)e < 0);

        fast_euclid(e, phi, 0, 0, &d, &tmp);
        if ((int64_t)d > 1 && fast_exp_mod(fast_exp_mod(5, e, p), d, p) == 5) break;
    }
}
