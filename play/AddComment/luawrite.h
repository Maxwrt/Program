/****************************************************************************
** 版权所有: 小王同学
** 版本号: 1.0.0
** 文件名: D:/2020/WRT/Program/play/AddComment/luawrite.h
** 时间: 2021.05.24
** 作者: 王瑞亭
** 功能: **
** 其他: 
** 修改记录: 
****************************************************************************/
#ifndef LUAWRITE_H
#define LUAWRITE_H

#if 0
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
    static QPointer<LuaEngine> Int()
    {
        static QPointer<LuaEngine> ptr = QPointer<LuaEngine>(new LuaEngine());
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
#endif
#endif // LUAWRITE_H
