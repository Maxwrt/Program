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
