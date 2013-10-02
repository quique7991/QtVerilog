/****************************************************************************
** Meta object code from reading C++ file 'busconnection.h'
**
** Created: Tue Oct 1 10:13:36 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GUI/busconnection.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'busconnection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_busConnection[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      34,   14,   14,   14, 0x0a,
      52,   14,   14,   14, 0x08,
      78,   14,   14,   14, 0x08,
     105,   14,   14,   14, 0x08,
     134,  129,   14,   14, 0x08,
     165,  129,   14,   14, 0x08,
     196,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_busConnection[] = {
    "busConnection\0\0newOneOneLine(int)\0"
    "newBlockLine(int)\0on_pushButton_3_clicked()\0"
    "on_conectarTodos_clicked()\0"
    "on_pushButton_clicked()\0arg1\0"
    "on_spinBox_5_valueChanged(int)\0"
    "on_spinBox_6_valueChanged(int)\0"
    "on_pushButton_2_clicked()\0"
};

void busConnection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        busConnection *_t = static_cast<busConnection *>(_o);
        switch (_id) {
        case 0: _t->newOneOneLine((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->newBlockLine((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_3_clicked(); break;
        case 3: _t->on_conectarTodos_clicked(); break;
        case 4: _t->on_pushButton_clicked(); break;
        case 5: _t->on_spinBox_5_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_spinBox_6_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_pushButton_2_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData busConnection::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject busConnection::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_busConnection,
      qt_meta_data_busConnection, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &busConnection::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *busConnection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *busConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_busConnection))
        return static_cast<void*>(const_cast< busConnection*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int busConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
