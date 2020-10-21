/****************************************************************************
** Meta object code from reading C++ file 'qdialoglogin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CRM/qdialoglogin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdialoglogin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QDialogLogin_t {
    QByteArrayData data[18];
    char stringdata0[253];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QDialogLogin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QDialogLogin_t qt_meta_stringdata_QDialogLogin = {
    {
QT_MOC_LITERAL(0, 0, 12), // "QDialogLogin"
QT_MOC_LITERAL(1, 13, 23), // "on_pushButtonOk_clicked"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 27), // "on_pushButtonCancel_clicked"
QT_MOC_LITERAL(4, 66, 29), // "on_pushButtonRegister_clicked"
QT_MOC_LITERAL(5, 96, 12), // "readsettings"
QT_MOC_LITERAL(6, 109, 13), // "writesettings"
QT_MOC_LITERAL(7, 123, 10), // "initDialog"
QT_MOC_LITERAL(8, 134, 15), // "mousePressEvent"
QT_MOC_LITERAL(9, 150, 12), // "QMouseEvent*"
QT_MOC_LITERAL(10, 163, 5), // "event"
QT_MOC_LITERAL(11, 169, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(12, 184, 17), // "mouseReleaseEvent"
QT_MOC_LITERAL(13, 202, 11), // "eventFilter"
QT_MOC_LITERAL(14, 214, 7), // "watched"
QT_MOC_LITERAL(15, 222, 7), // "QEvent*"
QT_MOC_LITERAL(16, 230, 13), // "encryptPasswd"
QT_MOC_LITERAL(17, 244, 8) // "password"

    },
    "QDialogLogin\0on_pushButtonOk_clicked\0"
    "\0on_pushButtonCancel_clicked\0"
    "on_pushButtonRegister_clicked\0"
    "readsettings\0writesettings\0initDialog\0"
    "mousePressEvent\0QMouseEvent*\0event\0"
    "mouseMoveEvent\0mouseReleaseEvent\0"
    "eventFilter\0watched\0QEvent*\0encryptPasswd\0"
    "password"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QDialogLogin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    1,   75,    2, 0x08 /* Private */,
      11,    1,   78,    2, 0x08 /* Private */,
      12,    1,   81,    2, 0x08 /* Private */,
      13,    2,   84,    2, 0x08 /* Private */,
      16,    1,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 15,   14,   10,
    QMetaType::QString, QMetaType::QString,   17,

       0        // eod
};

void QDialogLogin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QDialogLogin *_t = static_cast<QDialogLogin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonOk_clicked(); break;
        case 1: _t->on_pushButtonCancel_clicked(); break;
        case 2: _t->on_pushButtonRegister_clicked(); break;
        case 3: _t->readsettings(); break;
        case 4: _t->writesettings(); break;
        case 5: _t->initDialog(); break;
        case 6: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 7: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 8: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 9: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { QString _r = _t->encryptPasswd((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject QDialogLogin::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QDialogLogin.data,
      qt_meta_data_QDialogLogin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QDialogLogin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QDialogLogin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QDialogLogin.stringdata0))
        return static_cast<void*>(const_cast< QDialogLogin*>(this));
    return QDialog::qt_metacast(_clname);
}

int QDialogLogin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
