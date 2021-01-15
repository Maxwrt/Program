#ifndef LUAWRITE_H
#define LUAWRITE_H

#include <QObject>
#include <QPointer>
#include <QDebug>
#include "lua53.h"
#define  OUT qDebug().noquote()

class LuaWrite : public QObject
{
    Q_OBJECT
public:
    explicit LuaWrite(QObject *parent = 0);

signals:

public slots:
};

class LuaEngine : public QObject
{
    Q_OBJECT
public:
    static LuaEngine* Int()
    {
        static LuaEngine *ptr = QPointer<LuaEngine>(new LuaEngine());
        return ptr;
    }

    ~LuaEngine()
    {
        if (LuaEngine::Int())
            delete LuaEngine::Int();
    }

private:
    LuaEngine();

private:
    lua_State *m_luastate;
}

#endif // LUAWRITE_H
