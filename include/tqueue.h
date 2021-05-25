#pragma once

#include "tstack.h"

template < typename QueueType > class TQueue:public TStack < QueueType > {
  protected:
    int start;
    int count;
  public:
    TQueue(int n = 0);
    TQueue(const TQueue < QueueType > &Q);
    TQueue & operator=(const TQueue < QueueType > &queue);

    QueueType Get();
    void Put(QueueType Q);
    bool IsFull();
    bool IsEmpty();
    void PrintQueue();

    bool operator!=(const TQueue < QueueType > &queue) const;
    bool operator==(const TQueue < QueueType > &queue) const;
};

//-----------------------------------------------------------------
template < typename QueueType >
    TQueue < QueueType >::TQueue(int n):TStack < QueueType > (n)
{
    start = 0;
    count = 0;
}

//-----------------------------------------------------------------
template < typename QueueType >
    TQueue < QueueType >::TQueue(const TQueue < QueueType > &Q):TStack <
    QueueType > (Q)
{
    start = Q.start;
    count = Q.count;
}

//-----------------------------------------------------------------
template < typename QueueType >
    TQueue < QueueType > &TQueue < QueueType >::operator=(const TQueue <
							  QueueType >
							  &queue)
{
    if (this == &queue)
	return *this;

    start = queue.start;
    count = queue.count;
    TStack < QueueType >::top = queue.top;

    if (TStack < QueueType >::size != queue.size) {
	TStack < QueueType >::size = queue.size;
	delete[]TStack < QueueType >::memory;
	TStack < QueueType >::memory =
	    new QueueType[TStack < QueueType >::size];
    }

    for (int i = start; i < count + start; i++) {
	TStack < QueueType >::memory[i % TStack < QueueType >::size] =
	    queue.memory[i % TStack < QueueType >::size];
    }
    return *this;
}

//-----------------------------------------------------------------
template < typename QueueType >
    void TQueue < QueueType >::Put(QueueType el)
{
    if (IsFull())
	throw TException("Queue is full.");
    else
    {
	TStack < QueueType >::memory[TStack < QueueType >::top] = el;
	TStack < QueueType >::top =
	    ++TStack < QueueType >::top % TStack < QueueType >::size;
	count++;
    }
}

//-----------------------------------------------------------------
template < typename QueueType > QueueType TQueue < QueueType >::Get()
{
    if (IsEmpty())
	throw TException("Queue is empty.");
    else
    {
	QueueType buf = TStack < QueueType >::memory[start];
	start = ++start % TStack < QueueType >::size;
	count--;

	return buf;
    }
}

//-----------------------------------------------------------------
template < typename QueueType > bool TQueue < QueueType >::IsFull()
{
    return count == TStack < QueueType >::size ? true : false;
}

//-----------------------------------------------------------------
template < typename QueueType > bool TQueue < QueueType >::IsEmpty()
{
    return count == 0 ? true : false;
}

//-----------------------------------------------------------------
template < typename QueueType >
    bool TQueue < QueueType >::operator==(const TQueue < QueueType >
					  &queue) const
{

    if (TStack < QueueType >::top != queue.top
	|| TStack < QueueType >::size != queue.size || count != queue.count
	|| start != queue.start)
	return false;
    for (int i = start; i < count + start; i++) {
	if (TStack < QueueType >::memory[i % TStack < QueueType >::size] !=
	    queue.memory[i % TStack < QueueType >::size])
	    return false;
    }
    return true;
}

//-----------------------------------------------------------------
template < typename QueueType >
    bool TQueue < QueueType >::operator!=(const TQueue < QueueType >
					  &queue) const
{
    return !(*this == queue);
}

template < typename QueueType > void TQueue < QueueType >::PrintQueue()
{
    for (int i = start; i < count + start; i++) {
	cout << TStack < QueueType >::memory[i % TStack <
					     QueueType >::size] << " | ";
    }

    cout << endl;
}
