#include "compare.h"
#include <QDebug>
#include <QThread>
Compare::Compare()
{
    m_base = new Base(this);
    connect(m_base, SIGNAL(finishCompare(const QVariantList& )), this, SLOT(finishCompareSlot(const QVariantList&)));
}

Compare::~Compare()
{
    delete m_base;
}

void Compare::compareSlot(const QVariantHash& hash)
{
    m_mutex.lock();
    m_base->compare(hash);
    m_mutex.unlock();
}

void Compare::finishCompareSlot(const QVariantList& retlist)
{
    qDebug().noquote()<<tr("Compare receive compare over signal");
    emit finishCompareSignal(retlist);
}
