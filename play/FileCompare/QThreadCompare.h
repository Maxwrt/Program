/****************************************************************************
** ʱ�䣺2021.01.14
** ���ߣ�����ͤ
** ���ܣ�**
****************************************************************************/
#ifndef QThreadCompare_H
#define QThreadCompare_H

#include <QThread>
#include <QVariantHash>
#include <QMutex>
#include <QVariantList>
#include <QPointer>

class Compare;
class QThreadCompare: public QThread
{
    Q_OBJECT
public:
    QThreadCompare(QObject *parent = 0);
    ~QThreadCompare();
    void stopThread();

public slots:
    void startCompareSlot(const QVariantHash& hash);
    void receiveBaseSlot(const QVariantList& retlist);
    void editStartCompareSlot(const QVariantHash& hash);

signals:
    void finish_compare_thread(const QVariantList& retlist);
    void sendMsg(const QString& msg);

private:
    void compare();

private:
    virtual void run();
    QVariantHash m_hash;
    QPointer<Compare> m_compare;
    bool m_stop;
    bool m_start_compare;
    QMutex m_mutex;
};
#endif // QThreadCompare_H

/**
 *Ĭ�ϵĹ��캯����������������±���ϳɣ���Ϊ(implicit notrivial constructor)
 * 1. ��Ա�к���class object
 * 2. �̳���һ������Ĭ�Ϲ��캯����base class
 * 3. ���ຬ���麯��
 * 4. ��̳���һ����
 * ���������������û�������ϳ�Ĭ�ϵĹ��캯������Ϊ(implicit trivial constructor)
 *
 * Ĭ�ϵĿ������캯��ֻ����û�����ֳ�bitwise copy semanticsʱ����������ϳ�
 * �����������������û�����ֳ�bitwise copy semantics
 * 1.��class�ں�һ��member object�����ߵ�class������һ��copy constructor(�����Ǳ�class�������ȷ��������
 * ���Ǳ��������ϳɵ�)
 * 2.��class�̳���һ��base class�����ߴ���һ��copy consturctorʱ
 * 3.��class������һ������virtual functions
 * 4.��class������һ���̳д�����������һ������vitrual base classʱ
 *
  *QThread�������ڸö��󱻴������߳��У�������QThread::run()����������ʱ���ڵ��߳�
  *Qt::DirectConnection(ֱ����ʽ)(�ź���ۺ�����ϵ�����ں������ã�ͬ��ִ��)
  *���źŷ���ʱ���ۺ�����ֱ�ӱ�����
  *���۲ۺ��������������Ǹ��̣߳��ۺ������ڷ����źŵ��߳���ִ��
  *Qt::QueuedConnection(���з�ʽ)(��ʱ�źű�����Qt���¼�������ź���ۺ�����ϵ��������Ϣͨ�ţ��첽ִ��)
  *���źŷ��������е��źŶ����У���ȵ����ն��������̵߳��¼�ѭ��ȡ�ÿ���Ȩʱ��ȡ�ø��źţ�������Ӧ�Ĳۺ���
  *emit����Ĵ��뽫�ڷ����źź�������ִ������ȵ��ۺ���ִ����ϡ�
  *������Ȩ�ص��������������̵߳��¼�ѭ��ʱ���ۺ��������á�
  *�ۺ����ڽ��������������߳�ִ�С�
  *Qt::AutoConnection(�Զ���ʽ)
  *Qt��Ĭ�����ӷ�ʽ,����źŵķ���������źŵĶ���ͬ��һ���̣߳���ô������ʽ��ֱ����ʽ��ͬ
  *��������ʽ����з�ʽ��ͬ��
  *����ź��ڽ��������������߳��ڷ��䣬���ͬ��ֱ�����ӡ�
  *��������źŵ��̺߳ͽ����źŵ��̲߳�ͬ�����ͬ�ڶ������ӡ�
  *Qt::BlockingQueuedConnection(�źźͲ۱����ڲ�ͬ���߳��У�����Ͳ�������)
  *�ۺ����ĵ������κ�QueuedConnection��ͬ����ͬ���ǵ�ǰ���̻߳�����ס��ֱ���ۺ������ء�
  *Qt::UniqueConnection
  *��Ĭ�Ϲ�����ʽ��ͬ��ֻ�ǲ����ظ�������ͬ���źźͲۣ���Ϊ����ظ����Ӿͻᵼ��һ���źŷ�������Ӧ�ۺ����ͻ�ִ�ж��
  *QThread�����������̵߳ģ�QThread�������������̺߳���������̲߳�����ͬһ�����QThread���������߳̾��Ǵ���
  *QThread������̣߳�QThread������̣߳�����run()�����������̣߳�Ҳ�������̡߳�QThread�������������߳��У�QThread
  *�����slot�����������߳���ִ�У��������ڴ��̡߳�����QThread�������������߳���(ͨ��movetoThread)
  *����ʵ���У�Ϊ�˱��ⶳ�����̵߳��¼�ѭ������������˶�������Ӧ�õ�UI�������еļ��㹤������һ�������Ĺ����߳�����ɵģ�
  *�����߳̽���ʱ����һ���źţ�ͨ���źŵĲ����������̵߳�״̬���͵�GUI�̵߳Ĳۺ����и���GUI���״̬��
  *�̵߳���������
  *����߳�������ִ�й�����ʱ���̶߳�������ʱ�����򽫻����
  *����ʵ�����̶߳���������ڱ�������̵߳������ڡ�
  */
