/****************************************************************************
** 时间：2021.01.14
** 作者：王瑞亭
** 功能：**
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
 *默认的构造函数在以下四种情况下必须合成，称为(implicit notrivial constructor)
 * 1. 成员中含有class object
 * 2. 继承了一个带有默认构造函数的base class
 * 3. 该类含有虚函数
 * 4. 虚继承了一个类
 * 其他情况编译器并没有真正合成默认的构造函数，称为(implicit trivial constructor)
 *
 * 默认的拷贝构造函数只有类没有体现出bitwise copy semantics时编译器必须合成
 * 以下四种情况编译器没有体现出bitwise copy semantics
 * 1.当class内含一个member object而后者的class声明有一个copy constructor(不论是被class设计者明确的声明，
 * 还是被编译器合成的)
 * 2.当class继承自一个base class而后者存在一个copy consturctor时
 * 3.当class声明了一个或多个virtual functions
 * 4.当class派生自一个继承串链，其中有一个或多个vitrual base class时
 *
  *QThread对象存活于该对象被创建的线程中，而并非QThread::run()函数被调用时所在的线程
  *Qt::DirectConnection(直连方式)(信号与槽函数关系类似于函数调用，同步执行)
  *当信号发射时，槽函数将直接被调用
  *无论槽函数所属对象在那个线程，槽函数都在发射信号的线程内执行
  *Qt::QueuedConnection(队列方式)(此时信号被塞到Qt的事件队列里，信号与槽函数关系类似于消息通信，异步执行)
  *当信号发出后，排列到信号队列中，需等到接收对象所属线程的事件循环取得控制权时才取得该信号，调用相应的槽函数
  *emit语句后的代码将在发出信号后立即被执行无需等到槽函数执行完毕。
  *当控制权回到接收者所依附线程的事件循环时，槽函数被调用。
  *槽函数在接受者所依附的线程执行。
  *Qt::AutoConnection(自动方式)
  *Qt的默认连接方式,如果信号的发出与接收信号的对象同属一个线程，那么工作方式与直连方式相同
  *否则工作方式与队列方式相同。
  *如果信号在接受者所依附的线程内发射，则等同于直接连接。
  *如果发射信号的线程和接受信号的线程不同，则等同于队列连接。
  *Qt::BlockingQueuedConnection(信号和槽必须在不同的线程中，否则就产生死锁)
  *槽函数的调用情形和QueuedConnection相同，不同的是当前的线程会阻塞住，直到槽函数返回。
  *Qt::UniqueConnection
  *与默认工作方式相同，只是不能重复连接相同的信号和槽，因为如果重复连接就会导致一个信号发出，对应槽函数就会执行多次
  *QThread是用来管理线程的，QThread对象所依附的线程和所管理的线程并不是同一个概念。QThread所依附的线程就是创建
  *QThread对象的线程，QThread管理的线程，就是run()函数启动的线程，也就是新线程。QThread对象依附在主线程中，QThread
  *对象的slot函数会在主线程中执行，而不是在次线程。除非QThread对象依附到次线程中(通过movetoThread)
  *工程实践中，为了避免冻结主线程的事件循环（即避免因此而冻结了应用的UI），所有的计算工作是在一个单独的工作线程中完成的，
  *工作线程结束时发射一个信号，通过信号的参数将工作线程的状态发送到GUI线程的槽函数中更新GUI组件状态。
  *线程的生命周期
  *如果线程正处于执行过程中时，线程对象被销毁时，程序将会出错。
  *工程实践中线程对象的生命期必须大于线程的生命期。
  */
