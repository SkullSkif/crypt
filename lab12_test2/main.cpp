#include <QApplication>
#include <QCommandLineParser>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("MentalPoker");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Mental Poker Client");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption playersOption(QStringList() << "n" << "players",
                                     "Number of players", "number", "2");
    parser.addOption(playersOption);
    parser.process(a);

    bool ok;
    int playersCount = parser.value(playersOption).toInt(&ok);
    if (!ok || playersCount < 2) playersCount = 2;

    // Создаем окно
    MainWindow w;
    w.show();

    // Запускаем игру (передаем параметры внутрь)
    w.startGame(playersCount);

    return a.exec();
}
