#include "game.h"
#include <algorithm>

GameEngine::GameEngine(QObject *parent) : QObject(parent) {}

void GameEngine::initGame(int playerCount)
{
    stage = 0;
    players.clear();
    deck.clear();

    createPlayers(playerCount);
    emit gameStarted(playerCount);
}

void GameEngine::createPlayers(int count)
{
    uint64_t p;
    std::random_device rd;
    do {
        p = rd();
    } while (p < 54 || !fast_test_ferma(p));

    emit logMessage(QString("Open P: %1").arg(p));

    players.reserve(count);
    for(int i = 0; i < count; ++i) {
        players.emplace_back(p);
        // emit logMessage(QString("Created %1").arg(players.back().get_name()));
    }
}

void GameEngine::nextStep()
{
    switch(stage) {
    case 0:
        shuffleAndEncryptDeck();
        break;
    case 1:
        decryptCardsStep();
        break;
    case 2:
        getLastFiveCards();
        break;
    default:
        emit logMessage("End");
    }
    stage++;
}

void GameEngine::shuffleAndEncryptDeck()
{
    deck.reserve(52);
    for (uint64_t c = 2; c < 54; c++) {
        uint64_t tmp = c;
        for (auto& p : players) {
            tmp = p.encrypt(tmp);
        }
        deck.push_back(tmp);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);

    emit logMessage("Deck shuffled and encrypted!");
}

void GameEngine::decryptCardsStep()
{
    // Индекс текущей карты в колоде
    int deckIndex = 0;

    for(auto& player : players) {

        // Раздаем ПЕРВУЮ карту игроку (index 0)
        if (deckIndex < deck.size()) {
            uint64_t encryptedCard1 = deck[deckIndex++];


            // Здесь должна быть логика расшифровки
            // Пока просто отдаем как есть (или применяем decrypt)
            // uint64_t card1 = player.decrypt(encryptedCard1);

            player.set_card(0, encryptedCard1);

            QString cardName = cardToString(encryptedCard1);
            emit logMessage(QString("%1 got 1st card: %2").arg(player.get_name(), cardName));
        }

        // Раздаем ВТОРУЮ карту игроку (index 1)
        if (deckIndex < deck.size()) {
            uint64_t encryptedCard2 = deck[deckIndex++];

            player.set_card(1, encryptedCard2);

            QString cardName = cardToString(encryptedCard2);
            emit logMessage(QString("%1 got 2nd card: %2").arg(player.get_name(), cardName));
        }
        for (auto& p : players) {
            if (p != player) {
                player.set_card(0, p.decrypt(player.get_card(0)));
                player.set_card(1, p.decrypt(player.get_card(1)));
            }
        }
        player.set_card(0, player.decrypt(player.get_card(0)));
        player.set_card(1, player.decrypt(player.get_card(1)));
        emit logMessage(QString::fromStdString(player.get_name().toStdString() + " get cards " + std::to_string(player.get_card(0)) + " " + std::to_string(player.get_card(1)) + "\n"));
        emit playerInfoUpdated((deckIndex-2)/2, player.get_name(), QString(cardToString(player.get_card(0)) + " " + cardToString(player.get_card(1))));
    }

    emit logMessage("Cards distributed to all players.");
}

void GameEngine::getLastFiveCards() {
    emit logMessage(QString::fromStdString("cards on table: "));
    for (int i = 0; i < 5; i++) {
        uint64_t card_now = deck[(players.size()*2)+i];
        for (auto& player : players) {
            card_now = player.decrypt(card_now);
        }
        emit logMessage(cardToString(card_now));
    }
    for(auto item : players){
        emit logMessage(QString::fromStdString(item.get_name().toStdString() + ": " + std::to_string(item.get_e()) + " " + std::to_string(item.get_d())));
    }
    emit logMessage("\n");
}

QString GameEngine::cardToString(uint64_t card) {
    QString out, rank;
    switch ((card-2) / 13) {
    case 0:
        out.append("Трефы: ");
        break;
    case 1:
        out.append("Бубны: ");
        break;
    case 2:
        out.append("Черви: ");
        break;
    case 3:
        out.append("Пики: ");
        break;
    }
    switch ((card-2) % 13) {
    case 0: rank = "2"; break;
    case 1: rank = "3"; break;
    case 2: rank = "4"; break;
    case 3: rank = "5"; break;
    case 4: rank = "6"; break;
    case 5: rank = "7"; break;
    case 6: rank = "8"; break;
    case 7: rank = "9"; break;
    case 8: rank = "10"; break;
    case 9: rank = "J"; break;
    case 10: rank = "Q"; break;
    case 11: rank = "K"; break;
    case 12: rank = "A"; break;
    default: rank = "?"; break;
    }
    out.append(rank);

    return out;
}
