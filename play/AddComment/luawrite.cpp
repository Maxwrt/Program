#if 0
#include "luawrite.h"
#include <QCoreApplication>

LuaWrite::LuaWrite(QObject *parent) : QObject(parent)
{

}


LuaEngine::LuaEngine()
{
    m_luastate = luaL_newstate();
    if (NULL == m_luastate)
    {
        OUT << QString::fromLocal8Bit("�ڴ�����ʧ��");
        QCoreApplication::instance()->exit(1);
    }
}
#endif
