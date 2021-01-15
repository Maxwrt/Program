/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
****************************************************************************/
#ifndef LUATEXTEDIT_H
#define LUATEXTEDIT_H

#include "mytextedit.h"

class LuaTextEdit : public MyTextEdit
{
	Q_OBJECT

public:
	LuaTextEdit(QWidget* parent = NULL);
};

#endif // LUATEXTEDIT_H
