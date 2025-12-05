/****************************************************************************
** Meta object code from reading C++ file 'game.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../game.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_GameEngine_t {
    uint offsetsAndSizes[20];
    char stringdata0[11];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[4];
    char stringdata4[12];
    char stringdata5[6];
    char stringdata6[18];
    char stringdata7[6];
    char stringdata8[5];
    char stringdata9[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_GameEngine_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_GameEngine_t qt_meta_stringdata_GameEngine = {
    {
        QT_MOC_LITERAL(0, 10),  // "GameEngine"
        QT_MOC_LITERAL(11, 10),  // "logMessage"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 3),  // "msg"
        QT_MOC_LITERAL(27, 11),  // "gameStarted"
        QT_MOC_LITERAL(39, 5),  // "count"
        QT_MOC_LITERAL(45, 17),  // "playerInfoUpdated"
        QT_MOC_LITERAL(63, 5),  // "index"
        QT_MOC_LITERAL(69, 4),  // "name"
        QT_MOC_LITERAL(74, 15)   // "handDescription"
    },
    "GameEngine",
    "logMessage",
    "",
    "msg",
    "gameStarted",
    "count",
    "playerInfoUpdated",
    "index",
    "name",
    "handDescription"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_GameEngine[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x06,    1 /* Public */,
       4,    1,   35,    2, 0x06,    3 /* Public */,
       6,    3,   38,    2, 0x06,    5 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,    7,    8,    9,

       0        // eod
};

Q_CONSTINIT const QMetaObject GameEngine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GameEngine.offsetsAndSizes,
    qt_meta_data_GameEngine,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_GameEngine_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GameEngine, std::true_type>,
        // method 'logMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'gameStarted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'playerInfoUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void GameEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameEngine *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->logMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->gameStarted((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->playerInfoUpdated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameEngine::*)(QString );
            if (_t _q_method = &GameEngine::logMessage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GameEngine::*)(int );
            if (_t _q_method = &GameEngine::gameStarted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GameEngine::*)(int , QString , QString );
            if (_t _q_method = &GameEngine::playerInfoUpdated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *GameEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameEngine.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GameEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void GameEngine::logMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GameEngine::gameStarted(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GameEngine::playerInfoUpdated(int _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
