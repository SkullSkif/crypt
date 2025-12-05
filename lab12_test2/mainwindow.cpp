#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 1. Увеличиваем размер окна при запуске
    resize(1200, 800);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Главный вертикальный слой: Сверху Логи, Снизу Игроки
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // --- ВЕРХНЯЯ ЧАСТЬ (LOGS) ---
    QVBoxLayout *topLayout = new QVBoxLayout();

    logArea = new QTextEdit();
    logArea->setReadOnly(true);
    // Шрифт логов покрупнее
    QFont logFont = logArea->font();
    logFont.setPointSize(10);
    logArea->setFont(logFont);

    btnNextStep = new QPushButton("Next Step / Action");
    btnNextStep->setMinimumHeight(50); // Кнопка побольше
    btnNextStep->setStyleSheet("font-size: 14px; font-weight: bold;");

    topLayout->addWidget(logArea);
    topLayout->addWidget(btnNextStep);

    // Добавляем верхнюю часть (логи)
    mainLayout->addLayout(topLayout, 1);


    // --- НИЖНЯЯ ЧАСТЬ (PLAYERS) ---
    // Используем ScrollArea для горизонтальной прокрутки игроков
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем вертикальную прокрутку

    playersContainerWidget = new QWidget();
    // Меняем на горизонтальный layout для игроков
    playersLayout = new QHBoxLayout(playersContainerWidget);
    playersLayout->setAlignment(Qt::AlignLeft); // Выравнивание по левому краю

    scrollArea->setWidget(playersContainerWidget);

    // Добавляем нижнюю часть (игроки)
    mainLayout->addWidget(scrollArea, 1);


    // --- ЛОГИКА ---
    engine = new GameEngine(this);

    connect(engine, &GameEngine::logMessage, this, &MainWindow::appendLog);
    connect(btnNextStep, &QPushButton::clicked, engine, &GameEngine::nextStep);

    // Подключаем новые сигналы
    connect(engine, &GameEngine::gameStarted, this, &MainWindow::onGameStarted);
    connect(engine, &GameEngine::playerInfoUpdated, this, &MainWindow::onPlayerUpdated);
}

MainWindow::~MainWindow() {}

void MainWindow::startGame(int playerCount)
{
    engine->initGame(playerCount);
}

void MainWindow::appendLog(QString msg)
{
    logArea->append(msg);
}

// Создаем "карточки" игроков (виджеты)
void MainWindow::onGameStarted(int count)
{
    // 1. Очищаем старые виджеты
    QLayoutItem *item;
    while ((item = playersLayout->takeAt(0)) != nullptr) {
        if (item->widget()) delete item->widget();
        delete item;
    }
    playerLabels.clear();

    // 2. Создаем новые
    for(int i = 0; i < count; ++i) {
        QGroupBox *box = new QGroupBox(QString("Player %1").arg(i));
        // Немного изменяем стиль для горизонтального расположения
        box->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid gray; border-radius: 5px; margin: 5px; min-width: 200px; } "
                           "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top center; padding: 0 3px;}");

        QVBoxLayout *boxLayout = new QVBoxLayout(box);

        QLabel *cardsLabel = new QLabel("Waiting...");
        cardsLabel->setAlignment(Qt::AlignCenter);
        // Делаем шрифт карт большим
        QFont f = cardsLabel->font();
        f.setPointSize(16);
        cardsLabel->setFont(f);

        // Для горизонтального расположения можно ограничить высоту
        box->setMaximumWidth(250);

        boxLayout->addWidget(cardsLabel);

        // Добавляем в интерфейс
        playersLayout->addWidget(box);

        // Запоминаем лейбл, чтобы потом менять текст
        playerLabels.push_back(cardsLabel);
    }
}

// Обновляем текст внутри конкретного игрока
void MainWindow::onPlayerUpdated(int index, QString name, QString handHtml)
{
    if (index >= 0 && index < playerLabels.size()) {
        // Обновляем имя группы (рамки)
        QGroupBox *box = qobject_cast<QGroupBox*>(playerLabels[index]->parentWidget());
        if (box) box->setTitle(name);

        // Обновляем текст карт (поддерживает HTML цвета)
        playerLabels[index]->setText(handHtml);
    }
}
