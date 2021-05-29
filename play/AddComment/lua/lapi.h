/****************************************************************************
** 版权所有: 小王同学
** 版本号: 1.0.0
** 文件名: D:/2020/WRT/Program/play/AddComment/lua/lapi.h
** 时间: 2021.05.24
** 作者: 王瑞亭
** 功能: **
** 其他: 
** 修改记录: 
****************************************************************************/
/*
** $Id: lapi.h,v 2.9.1.1 2017/04/19 17:20:42 roberto Exp $
** Auxiliary functions from Lua API
** See Copyright Notice in lua.h
*/

#ifndef lapi_h
#define lapi_h


#include "llimits.h"
#include "lstate.h"

#define api_incr_top(L)   {L->top++; api_check(L, L->top <= L->ci->top, \
				"stack overflow");}

#define adjustresults(L,nres) \
    { if ((nres) == LUA_MULTRET && L->ci->top < L->top) L->ci->top = L->top; }

#define api_checknelems(L,n)	api_check(L, (n) < (L->top - L->ci->func), \
				  "not enough elements in the stack")


#endif
