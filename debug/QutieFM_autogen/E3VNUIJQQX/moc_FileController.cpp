/****************************************************************************
** Meta object code from reading C++ file 'FileController.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Controller/FileController/FileController.hpp"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FileController.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSFileControllerENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSFileControllerENDCLASS = QtMocHelpers::stringData(
    "FileController",
    "operate",
    "",
    "pause",
    "updatePath",
    "std::filesystem::path",
    "pathChanged",
    "std::unordered_map<std::filesystem::path,std::filesystem::file_time_ty"
    "pe>",
    "paths",
    "contentChanged",
    "FileEvent",
    "event",
    "update",
    "path",
    "newPath"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFileControllerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x06,    1 /* Public */,
       3,    0,   57,    2, 0x06,    2 /* Public */,
       4,    1,   58,    2, 0x06,    3 /* Public */,
       6,    1,   61,    2, 0x06,    5 /* Public */,
       9,    2,   64,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      12,    2,   69,    2, 0x08,   10 /* Private */,
      14,    1,   74,    2, 0x08,   13 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 10,    2,   11,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 10,   13,    2,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

Q_CONSTINIT const QMetaObject FileController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSFileControllerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFileControllerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSFileControllerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FileController, std::true_type>,
        // method 'operate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pause'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updatePath'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::filesystem::path &, std::false_type>,
        // method 'pathChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::unordered_map<std::filesystem::path,std::filesystem::file_time_type>, std::false_type>,
        // method 'contentChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::filesystem::path, std::false_type>,
        QtPrivate::TypeAndForceComplete<FileEvent, std::false_type>,
        // method 'update'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::filesystem::path, std::false_type>,
        QtPrivate::TypeAndForceComplete<const FileEvent, std::false_type>,
        // method 'newPath'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::unordered_map<std::filesystem::path,std::filesystem::file_time_type>, std::false_type>
    >,
    nullptr
} };

void FileController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FileController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->operate(); break;
        case 1: _t->pause(); break;
        case 2: _t->updatePath((*reinterpret_cast< std::add_pointer_t<std::filesystem::path>>(_a[1]))); break;
        case 3: _t->pathChanged((*reinterpret_cast< std::add_pointer_t<std::unordered_map<std::filesystem::path,std::filesystem::file_time_type>>>(_a[1]))); break;
        case 4: _t->contentChanged((*reinterpret_cast< std::add_pointer_t<std::filesystem::path>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<FileEvent>>(_a[2]))); break;
        case 5: _t->update((*reinterpret_cast< std::add_pointer_t<std::filesystem::path>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<FileEvent>>(_a[2]))); break;
        case 6: _t->newPath((*reinterpret_cast< std::add_pointer_t<std::unordered_map<std::filesystem::path,std::filesystem::file_time_type>>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FileController::*)();
            if (_t _q_method = &FileController::operate; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FileController::*)();
            if (_t _q_method = &FileController::pause; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FileController::*)(const std::filesystem::path & );
            if (_t _q_method = &FileController::updatePath; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FileController::*)(const std::unordered_map<std::filesystem::path,std::filesystem::file_time_type> );
            if (_t _q_method = &FileController::pathChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FileController::*)(std::filesystem::path , FileEvent );
            if (_t _q_method = &FileController::contentChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *FileController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFileControllerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FileController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void FileController::operate()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FileController::pause()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void FileController::updatePath(const std::filesystem::path & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FileController::pathChanged(const std::unordered_map<std::filesystem::path,std::filesystem::file_time_type> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FileController::contentChanged(std::filesystem::path _t1, FileEvent _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
