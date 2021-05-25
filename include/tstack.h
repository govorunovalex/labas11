#pragma once

#include <iostream>
#include "exception.h"

using namespace std;

template < typename StackType > class TStack {
  protected:
    int size;
    int top;
    StackType *memory;
  public:
    int GetSize() {
	return size;
    }
    TStack(int n = 0);
    TStack(const TStack < StackType > &S);
    TStack & operator=(const TStack < StackType > &stack);
    ~TStack() {
	delete[]memory;
    }

    StackType Get();
    StackType ShowLast();
    void Put(StackType A);
    bool IsFull();
    bool IsEmpty();
    void PrintStack();

    bool operator!=(const TStack < StackType > &stack) const;
    bool operator==(const TStack < StackType > &stack) const;
};

//----------------------------------------------------------------------
template < typename StackType > TStack < StackType >::TStack(int n)
{
    if (n < 0)
	throw TException(" Negative size.");
    else
if (n == 0) {
    size = 0;
    top = 0;
    memory = NULL;
} else {
    size = n;
    top = 0;
    memory = new StackType[size];
    for (int i = 0; i < size; i++)
	memory[i] = 0;
}
}

//----------------------------------------------------------------------
template < typename StackType >
    TStack < StackType >::TStack(const TStack < StackType > &S)
{
    size = S.size;
    top = S.top;
    if (size == 0)
	memory = NULL;
    else {
	memory = new StackType[size];
	for (int i = 0; i < size; i++)
	    memory[i] = S.memory[i];
    }
}

//----------------------------------------------------------------------
template < typename StackType >
    TStack < StackType > &TStack < StackType >::operator=(const TStack <
							  StackType >
							  &stack)
{
    if (this != &stack) {
	top = stack.top;
	if (size != stack.size) {
	    size = stack.size;
	    delete[]memory;
	    memory = new StackType[size];
	}
	for (int i = 0; i < size; i++) {
	    memory[i] = stack.memory[i];
	}
    }
    return *this;
}

//----------------------------------------------------------------------
template < typename StackType > void TStack < StackType >::Put(StackType A)
{
    if (IsFull()) {
	throw TException("Stack is full");
    } else {
	memory[top] = A;
	top++;
    }
}

//----------------------------------------------------------------------
template < typename StackType > StackType TStack < StackType >::Get()
{
    if (IsEmpty())
	throw TException("Stack is empty");
    else
    {
	top--;
	return memory[top];
    }
}

//----------------------------------------------------------------------
template < typename StackType > StackType TStack < StackType >::ShowLast()
{
    if (IsEmpty())
	throw TException("Stack is empty");
    else
    {
	return memory[top - 1];
    }
}

//----------------------------------------------------------------------
template < typename StackType > bool TStack < StackType >::IsFull()
{
    //ternary operator
    return top >= size ? true : false;
}

//----------------------------------------------------------------------
template < typename StackType > bool TStack < StackType >::IsEmpty()
{
    return !top;
}

//----------------------------------------------------------------------
template < typename StackType >
    bool TStack < StackType >::operator==(const TStack < StackType >
					  &stack) const
{
    if (top != stack.top || size != stack.size)
	return false;
    for (int i = 0; i < top; i++) {
	if (memory[i] != stack.memory[i])
	    return false;
    }
    return true;
}

//----------------------------------------------------------------------
template < typename StackType >
    bool TStack < StackType >::operator!=(const TStack < StackType >
					  &stack) const
{
    return !(*this == stack);
}

//----------------------------------------------------------------------
template < typename StackType > void TStack < StackType >::PrintStack()
{
    for (int i = top - 1; i >= 0; i--)
	cout << "\t|" << memory[i] << "|" << endl;
}
