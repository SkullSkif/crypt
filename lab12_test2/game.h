#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <vector>
#include <QString>
#include "player.h"

class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = nullptr);

    void initGame(int playerCount);
    void nextStep();

signals:
    void logMessage(QString msg);
    void gameStarted(int count);       // Сигнал о старте

    // НОВЫЙ СИГНАЛ: Обновить конкретного игрока
    // handDescription - это уже готовая строка HTML с картами
    void playerInfoUpdated(int index, QString name, QString handDescription);

private:
    std::vector<Player> players;
    std::vector<uint64_t> deck;
    int stage = 0;

    void createPlayers(int count);
    void shuffleAndEncryptDeck();
    void decryptCardsStep();
    void getLastFiveCards();

    QString cardToString(uint64_t card);
};

#endif // GAMEENGINE_H
