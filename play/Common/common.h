/****************************************************************************
** ʱ�䣺2021.01.14
** ���ߣ�����ͤ
** ���ܣ�**
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
 * @brief ��ӡ�˵�
 */
COMMONSHARED_EXPORT void printMenu();

/**
 * @brief ��ӡQList
 * @param list
 * @param type
 */
void COMMONSHARED_EXPORT printList(const QList<QHash<QString, QString> >& list, int type);
/**
 * @brief �������ݿ�
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
 * @brief ����
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
 * @brief ����ͼƬ
 * @param imagepath ͼƬ·��
 * @param filter    ��������
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
 * @brief ���ļ���ȡʱ��
 * @param content�洢�ļ��е�����
 * @param day
 * @param hour
 * @param minute
 * @param flag
 */
void getConfig(const QString &content, qint32 &day, qint32 &hour, qint32 &minute, bool &flag);

/**
 * @brief д��־
 * @param type
 * @param context
 * @param msg
 */
COMMONSHARED_EXPORT void AppLog(QtMsgType type, const QMessageLogContext & context, const QString &msg);

/**
 * @brief �����������ڲ�
 * @param datetime
 * @return
 */
COMMONSHARED_EXPORT QString CalculateDateTime(const QDateTime & datetime, bool isString = true);
/**
 * @brief ������־�ļ���
 * @param appname
 */
COMMONSHARED_EXPORT void SetAppLogName(const QString &appname);

/**
 * @brief ɾ��>30������ļ���С>50M���ļ�
 * @param dirpath
 */
COMMONSHARED_EXPORT void RemoveFileThan30Days(const QString &dirpath, int size = 5);

/**
 * @brief ��ȡ������
 * @return
 */
COMMONSHARED_EXPORT QString AppName();

/**
 * @brief ��ȡ��������·��
 * @return
 */
COMMONSHARED_EXPORT QString AppPath();

/**
 * @brief �������������
 */
COMMONSHARED_EXPORT void InitRand();

/**
 * @brief �½�Ŀ¼
 * @param dirName
 */
COMMONSHARED_EXPORT void NewDir(const QString &dirName);

/**
 * @brief ���ñ���
 */
COMMONSHARED_EXPORT void SetCode();

/**
 * @brief ������ʱ
 * @param mesc
 */
COMMONSHARED_EXPORT void Sleep(int mesc);

/**
 * @brief ����ϵͳʱ��
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
 * @brief ���ÿ�������
 * @param strName
 * @param strPath
 */
COMMONSHARED_EXPORT void RunWithSystem(const QString &strName, const QString &strPath, bool autoRun=true);

/**
 * @brief �Ƿ���ip
 * @param ip
 * @return
 */
COMMONSHARED_EXPORT bool IsIP(const QString &ip);

/**
 * @brief �Ƿ���mac��ַ
 * @param ip
 * @return
 */
COMMONSHARED_EXPORT bool IsMac(const QString &mac);

/**
 * @brief �Ƿ��ǵ绰
 * @param ip
 * @return
 */
COMMONSHARED_EXPORT bool IsTel(const QString &tel);

/**
 * @brief �Ƿ�������
 * @param ip
 * @return
 */
COMMONSHARED_EXPORT bool IsEmail(const QString &email);

/**
 * @brief 16�����ַ���ת10������
 * @param strHex
 * @return
 */
COMMONSHARED_EXPORT int StrHexToDecimal(const QString &strHex);

/**
 * @brief 10�����ַ���ת10������
 * @param strDecimal
 * @return
 */
COMMONSHARED_EXPORT int StrDecimalToDecimal(const QString &strDecimal);

/**
 * @brief �������ַ���ת10������
 * @param strBin
 * @return
 */
COMMONSHARED_EXPORT int StrBinToDecimal(const QString &strBin);

/**
 * @brief 16�����ַ���ת2�����ַ���
 * @param strHex
 * @return
 */
COMMONSHARED_EXPORT QString StrHexToStrBin(const QString &strHex);

/**
 * @brief 10������ת2�����ַ���һ���ֽ�
 * @param decimal
 * @return
 */
COMMONSHARED_EXPORT QString DecimalToStrBin1Byte(int decimal);

/**
 * @brief 10������ת2�����ַ��������ֽ�
 * @param decimal
 * @return
 */
COMMONSHARED_EXPORT QString DecimalToStrBin2Byte(int decimal);

/**
 * @brief 10������ת16����1�ַ���
 * @param decimal
 * @return
 */
COMMONSHARED_EXPORT QString DecimalToStrHex(int decimal);


/**
 * @brief intת�ֽ�����
 * @param i
 * @return
 */
COMMONSHARED_EXPORT QByteArray IntToByte(int i);
COMMONSHARED_EXPORT QByteArray IntToByteRec(int i);

/**
 * @brief �ֽ�����תint
 * @param data
 * @return
 */
COMMONSHARED_EXPORT int ByteToInt(const QByteArray &data);
COMMONSHARED_EXPORT int ByteToIntRec(const QByteArray &data);
COMMONSHARED_EXPORT quint32 ByteToUInt(const QByteArray &data);
COMMONSHARED_EXPORT quint32 ByteToUIntRec(const QByteArray &data);

/**
 * @brief ushortת�ֽ�����
 * @param i
 * @return
 */
COMMONSHARED_EXPORT QByteArray UshortToByte(ushort i);
COMMONSHARED_EXPORT QByteArray UshortToByteRec(ushort i);

/**
 * @brief �ֽ�����תushort
 * @param data
 * @return
 */
COMMONSHARED_EXPORT int ByteToUShort(const QByteArray &data);
COMMONSHARED_EXPORT int ByteToUShortRec(const QByteArray &data);

/**
 * @brief �������㷨
 * @param str
 * @param key
 * @return
 */
COMMONSHARED_EXPORT QString GetXorEncryptDecrypt(const QString &str, char key);

/**
 * @brief ���У��
 * @param data
 * @return
 */
COMMONSHARED_EXPORT uchar GetOrCode(const QByteArray &data);


/**
 * @brief ����У����
 * @param data
 * @return
 */
COMMONSHARED_EXPORT uchar GetCheckCode(const QByteArray &data);

/**
 * @brief CRCУ��
 * @param data 16λCRCУ������
 * @param len  ����������
 * @param init ��ʼ��ֵ
 * @param table 16λCRC���ұ�
 * @return
 */
COMMONSHARED_EXPORT quint16 GetRevCrc_16(quint8 *data, int len, quint16 init, const quint16 *table);
COMMONSHARED_EXPORT quint16 GetCrc_16(quint8 *data, int len, quint16 init, const quint16 *table);
COMMONSHARED_EXPORT quint16 GetModbus16(quint8 *data, int len);
COMMONSHARED_EXPORT QByteArray GetCRCCode(const QByteArray &data);

/**
 * @brief �ж�IP��ַ���˿��Ƿ�����
 * @param ip
 * @param port
 * @param timeout
 * @return
 */
COMMONSHARED_EXPORT bool IpLive(const QString &ip, int port, int timeout = 1000);

/**
 * @brief ��ȡ��ҳ����Դ����
 * @param url
 * @return
 */
COMMONSHARED_EXPORT QString GetHtml(const QString &url);

/**
 * @brief ��ȡ��������IP��ַ
 * @param webCode
 * @return
 */
COMMONSHARED_EXPORT QString GetNetIP(const QString &webCode);

/**
 * @brief ��ȡ����IP
 * @return
 */
COMMONSHARED_EXPORT QString GetLocalIP();

/**
 * @brief Url��ַתΪIP��ַ
 * @param url
 * @return
 */
COMMONSHARED_EXPORT QString UrlToIP(const QString &url);

/**
 * @brief �ַ�����ȫ
 * @param value
 * @return
 */
COMMONSHARED_EXPORT QString GetValue(quint8 value);

/**
 * @brief �ж��Ƿ�ͨ����
 * @return
 */
COMMONSHARED_EXPORT bool IsWebOk();

bool In(wchar_t start, wchar_t end, wchar_t code);
char Convert(int n);

/**
 * @brief ��ȡ��һ�����ֵ�����ĸ
 * @param src
 * @return
 */
COMMONSHARED_EXPORT QString GetFirstLetter(const QString &src);

/**
 * @brief ��ȡ���к��ֵ�����ĸ
 * @param src
 * @return
 */
COMMONSHARED_EXPORT QString GetJianPin(const QString &src);

/**
 * @brief ��ȡһ�����ֱ���ĺ���ƴ��
 * @param code
 * @return
 */
COMMONSHARED_EXPORT QString GetPinyin(int code);

/**
 * @brief ��ȡ���к��ֵĺ���ƴ��,���ص�ƴ������Сд��
 * @param text
 * @return
 */
COMMONSHARED_EXPORT QString GetPinyins(const QString& text);





















#endif // COMMON_H
