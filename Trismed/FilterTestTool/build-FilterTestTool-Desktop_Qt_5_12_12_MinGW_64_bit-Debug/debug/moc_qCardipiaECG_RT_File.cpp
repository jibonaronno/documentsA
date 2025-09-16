/****************************************************************************
** Meta object code from reading C++ file 'qCardipiaECG_RT_File.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FilterTestTool/qCardipiaECG_RT_File.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qCardipiaECG_RT_File.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qCardipiaECG_RT_File_t {
    QByteArrayData data[1];
    char stringdata0[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qCardipiaECG_RT_File_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qCardipiaECG_RT_File_t qt_meta_stringdata_qCardipiaECG_RT_File = {
    {
QT_MOC_LITERAL(0, 0, 20) // "qCardipiaECG_RT_File"

    },
    "qCardipiaECG_RT_File"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qCardipiaECG_RT_File[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void qCardipiaECG_RT_File::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject qCardipiaECG_RT_File::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_qCardipiaECG_RT_File.data,
    qt_meta_data_qCardipiaECG_RT_File,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *qCardipiaECG_RT_File::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qCardipiaECG_RT_File::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qCardipiaECG_RT_File.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int qCardipiaECG_RT_File::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
