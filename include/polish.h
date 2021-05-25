#pragma once

#include <iostream>
#include <stdlib.h>
#include <string>
#include <cctype>
#include "tqueue.h"
#include "exception.h"

using namespace std;

namespace Polish {
    namespace {
	inline int GetPriority(const char operation) {
	    if (operation == '+' || operation == '-')
		return 3;
	    if (operation == '*' || operation == '/')
		return 4;
	    if (operation == ')')
		return 2;
	    if (operation == '(')
		return 1;
	    if (isdigit(operation))
		return 0;
	    return -1;
	} inline int Convert(const char symbol) {
	    return isdigit(symbol) ? symbol - '0' : -1;
	}
    }

    TQueue < char >ToPolish(string str) {
	TStack < char >operations_stack(str.size());
	TQueue < char >result(str.size());
	int priority = 0;

	for (string::iterator it = str.begin(); it != str.end(); it++) {
	    priority = GetPriority(*it);
	    if (priority == -1) {
		throw TException("Wrong symbol");
	    } else if (priority == 0) {
		result.Put(*it);
	    } else if (priority == 1) {
		operations_stack.Put(*it);
	    } else if (priority == 2) {
		for (;;) {
		    if (GetPriority(operations_stack.ShowLast()) == 1) {
			operations_stack.Get();
			break;
		    } else {
			result.Put(operations_stack.Get());
		    }
		}
	    } else {
		while (!operations_stack.IsEmpty()
		       && GetPriority(operations_stack.ShowLast()) >=
		       priority) {
		    result.Put(operations_stack.Get());
		}
		operations_stack.Put(*it);
	    }
	}

	while (!operations_stack.IsEmpty()) {
	    result.Put(operations_stack.Get());
	}
	return result;
    }

    double Calculate(TQueue < char >polish) {
	TStack < double >digits_stack(polish.GetSize());
	int priority = 0;
	double var1, var2;
	while (!polish.IsEmpty()) {
	    char const element = polish.Get();
	    priority = GetPriority(element);
	    if (priority == -1 || priority == 1 || priority == 2) {
		throw TException("Wrong string format");
	    }
	    if (priority == 0) {
		digits_stack.Put(Convert(element));
	    } else {
		var1 = digits_stack.Get();
		var2 = digits_stack.Get();
		switch (element) {
		case '+':
		    digits_stack.Put(var2 + var1);
		    break;
		case '-':
		    digits_stack.Put(var2 - var1);
		    break;
		case '*':
		    digits_stack.Put(var2 * var1);
		    break;
		case '/':
		    digits_stack.Put(var2 / var1);
		    break;
		}
	    }
	}
	return digits_stack.Get();
    }
};
