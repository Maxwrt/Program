/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
****************************************************************************/
#ifndef COMMON_H
#define COMMON_H

#include "common_global.h"
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QObject>
#include <QDebug>
#include <QSqlDatabase>
#define  OUT qDebug().noquote()

enum FileType
{
  signaltable,
  equiptable,
  excelfile,
  xmlfile
};

enum LOVE
{
  SUSU_GUAGUA,
  OTHERS
};

/**
 * @brief 打印菜单
 */
COMMONSHARED_EXPORT void printMenu();

/**
 * @brief 打印QList
 * @param list
 * @param type
 */
void COMMONSHARED_EXPORT printList(const QList<QHash<QString, QString> >& list, int type);
/**
 * @brief 创建数据库
 * @param dbName
 * @return
 */
COMMONSHARED_EXPORT QSqlDatabase Createdb(const QString& dbName);

/**
 * @brief gbk2string
 * @param gbkData
 * @return
 */

COMMONSHARED_EXPORT QString gbk2string(const char* gbkData);

/**
 * @brief string2gbk
 * @param qtext
 * @return
 */
COMMONSHARED_EXPORT QByteArray string2gbk(QString qtext);

/**
 * @brief 画心
 * @param keywords
 * @param type
 * @param datetime
 * @param wordslist
 * @param isReplace
 * @return
 */

COMMONSHARED_EXPORT QString DrawHeart(const QString& keywords, LOVE type = SUSU_GUAGUA, const QDateTime& datetime = QDateTime(), \
                                      bool isReplace = false, const QStringList& wordslist = QStringList());

/**
 * @brief 加载图片
 * @param imagepath 图片路径
 * @param filter    过滤条件
 * @return
 */
COMMONSHARED_EXPORT QHash<int, QString> LoadImage(const QString& imagepath, const QStringList& filter);
/**
 * @brief checkString
 * @param str
 * @return
 */
QStringList checkString(const QString &str);
QString dealString(const std::list<QString>  &list);

/**
 * @brief 从文件读取时间
 * @param content存储文件中的内容
 * @param day
 * @param hour
 * @param minute
 * @param flag
 */
void getConfig(const QString &content, qint32 &day, qint32 &hour, qint32 &minute, bool &flag);

/**
 * @brief 写日志
 * @param type
 * @param context
 * @param msg
 */
COMMONSHARED_EXPORT void AppLog(QtMsgType type, const QMessageLogContext & context, const QString &msg);

/**
 * @brief 计算两个日期差
 * @param datetime
 * @return
 */
COMMONSHARED_EXPORT QString CalculateDateTime(const QDateTime & datetime, bool isString = true);
/**
 * @brief 设置日志文件名
 * @param appname
 */
COMMONSHARED_EXPORT void SetAppLogName(const QString &appname);

/**
 * @brief 删除>30天或者文件大小>50M的文件
 * @param dirpath
 */
COMMONSHARED_EXPORT void RemoveFileThan30Days(const QString &dirpath, int size = 5);

/**
 * @brief 获取程序名
 * @return
 */
COMMONSHARED_EXPORT QString AppName();

/**
 * @brief 获取程序所在路径
 * @return
 */
COMMONSHARED_EXPORT QString AppPath();

/**
 * @brief 建立随机数种子
 */
COMMONSHARED_EXPORT void InitRand();

/**
 * @brief 新建目录
 * @param dirName
 */
COMMONSHARED_EXPORT void NewDir(const QString &dirName);

/**
 * @brief 设置编码
 */
COMMONSHARED_EXPORT void SetCode();

/**
 * @brief 设置延时
 * @param mesc
 */
COMMONSHARED_EXPORT void Sleep(int mesc);

/**
 * @brief 设置系统时间
 * @param year
 * @param month
 * @param day
 * @param hour
 * @param min
 * @param sec
 */
COMMONSHARED_EXPORT void SetSystemDateTime(const QString &year, const QString &month, const QString &day, \
                                           const QString &hour, const QString &min, const QString &sec);

/**
 * @brief 设置开机启动
 * @param strName
 * @param strPath
 */
COMMONSHARED_EXPORT void RunWithSystem(const QString &strName, const QString &strPath, bool autoRun=true);

/**
 * @brief 是否是ip
 * @param ip
 * @return
 */
COMMONSHARED_EXPORT bool IsIP(const QString &ip);

/**
 * @brief 是否是mac地址
 * @param ip
 * @return
 */
COMMONSHARED_EXPORT bool IsMac(const QString &mac);

/**
 * @brief 是否是电话
 * @param ip
 * @return
 */
COMMONSHARED_EXPORT bool IsTel(const QString &tel);

/**
 * @brief 是否是邮箱
 * @param ip
 * @return
 */
COMMONSHARED_EXPORT bool IsEmail(const QString &email);

/**
 * @brief 16进制字符串转10进制数
 * @param strHex
 * @return
 */
COMMONSHARED_EXPORT int StrHexToDecimal(const QString &strHex);

/**
 * @brief 10进制字符串转10进制数
 * @param strDecimal
 * @return
 */
COMMONSHARED_EXPORT int StrDecimalToDecimal(const QString &strDecimal);

/**
 * @brief 二进制字符串转10进制数
 * @param strBin
 * @return
 */
COMMONSHARED_EXPORT int StrBinToDecimal(const QString &strBin);

/**
 * @brief 16进制字符串转2进制字符串
 * @param strHex
 * @return
 */
COMMONSHARED_EXPORT QString StrHexToStrBin(const QString &strHex);

/**
 * @brief 10进制数转2进制字符串一个字节
 * @param decimal
 * @return
 */
COMMONSHARED_EXPORT QString DecimalToStrBin1Byte(int decimal);

/**
 * @brief 10进制数转2进制字符串两个字节
 * @param decimal
 * @return
 */
COMMONSHARED_EXPORT QString DecimalToStrBin2Byte(int decimal);

/**
 * @brief 10进制数转16进制1字符串
 * @param decimal
 * @return
 */
COMMONSHARED_EXPORT QString DecimalToStrHex(int decimal);


/**
 * @brief int转字节数组
 * @param i
 * @return
 */
COMMONSHARED_EXPORT QByteArray IntToByte(int i);
COMMONSHARED_EXPORT QByteArray IntToByteRec(int i);

/**
 * @brief 字节数组转int
 * @param data
 * @return
 */
COMMONSHARED_EXPORT int ByteToInt(const QByteArray &data);
COMMONSHARED_EXPORT int ByteToIntRec(const QByteArray &data);
COMMONSHARED_EXPORT quint32 ByteToUInt(const QByteArray &data);
COMMONSHARED_EXPORT quint32 ByteToUIntRec(const QByteArray &data);

/**
 * @brief ushort转字节数组
 * @param i
 * @return
 */
COMMONSHARED_EXPORT QByteArray UshortToByte(ushort i);
COMMONSHARED_EXPORT QByteArray UshortToByteRec(ushort i);

/**
 * @brief 字节数组转ushort
 * @param data
 * @return
 */
COMMONSHARED_EXPORT int ByteToUShort(const QByteArray &data);
COMMONSHARED_EXPORT int ByteToUShortRec(const QByteArray &data);

/**
 * @brief 异或加密算法
 * @param str
 * @param key
 * @return
 */
COMMONSHARED_EXPORT QString GetXorEncryptDecrypt(const QString &str, char key);

/**
 * @brief 异或校验
 * @param data
 * @return
 */
COMMONSHARED_EXPORT uchar GetOrCode(const QByteArray &data);


/**
 * @brief 计算校验码
 * @param data
 * @return
 */
COMMONSHARED_EXPORT uchar GetCheckCode(const QByteArray &data);

/**
 * @brief CRC校验
 * @param data 16位CRC校验数据
 * @param len  数据流长度
 * @param init 初始化值
 * @param table 16位CRC查找表
 * @return
 */
COMMONSHARED_EXPORT quint16 GetRevCrc_16(quint8 *data, int len, quint16 init, const quint16 *table);
COMMONSHARED_EXPORT quint16 GetCrc_16(quint8 *data, int len, quint16 init, const quint16 *table);
COMMONSHARED_EXPORT quint16 GetModbus16(quint8 *data, int len);
COMMONSHARED_EXPORT QByteArray GetCRCCode(const QByteArray &data);

/**
 * @brief 判断IP地址及端口是否在线
 * @param ip
 * @param port
 * @param timeout
 * @return
 */
COMMONSHARED_EXPORT bool IpLive(const QString &ip, int port, int timeout = 1000);

/**
 * @brief 获取网页所有源代码
 * @param url
 * @return
 */
COMMONSHARED_EXPORT QString GetHtml(const QString &url);

/**
 * @brief 获取本机公网IP地址
 * @param webCode
 * @return
 */
COMMONSHARED_EXPORT QString GetNetIP(const QString &webCode);

/**
 * @brief 获取本机IP
 * @return
 */
COMMONSHARED_EXPORT QString GetLocalIP();

/**
 * @brief Url地址转为IP地址
 * @param url
 * @return
 */
COMMONSHARED_EXPORT QString UrlToIP(const QString &url);

/**
 * @brief 字符串补全
 * @param value
 * @return
 */
COMMONSHARED_EXPORT QString GetValue(quint8 value);

/**
 * @brief 判断是否通外网
 * @return
 */
COMMONSHARED_EXPORT bool IsWebOk();

bool In(wchar_t start, wchar_t end, wchar_t code);
char Convert(int n);

/**
 * @brief 获取第一个汉字的首字母
 * @param src
 * @return
 */
COMMONSHARED_EXPORT QString GetFirstLetter(const QString &src);

/**
 * @brief 获取所有汉字的首字母
 * @param src
 * @return
 */
COMMONSHARED_EXPORT QString GetJianPin(const QString &src);

/**
 * @brief 获取一个汉字编码的汉语拼音
 * @param code
 * @return
 */
COMMONSHARED_EXPORT QString GetPinyin(int code);

/**
 * @brief 获取所有汉字的汉语拼音,返回的拼音都是小写的
 * @param text
 * @return
 */
COMMONSHARED_EXPORT QString GetPinyins(const QString& text);





















#endif // COMMON_H
