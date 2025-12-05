#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>
#include <vector>
#include "game.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void startGame(int playerCount);

public slots:
    void appendLog(QString msg);

    // Слоты для обновления графики
    void onGameStarted(int count);
    void onPlayerUpdated(int index, QString name, QString handHtml);

private:
    QWidget *centralWidget;

    // Левая часть
    QTextEdit *logArea;
    QPushButton *btnNextStep;

    // Правая часть (Контейнер для игроков)
    QWidget *playersContainerWidget;
    QHBoxLayout *playersLayout;

    // Список лейблов, чтобы обращаться к ним по индексу
    // index 0 -> лейбл первого игрока и т.д.
    std::vector<QLabel*> playerLabels;

    GameEngine *engine;
};
#endif
