#include <iostream>
#include <string>
#include "polish.h"
#include "time.h"

using namespace std;

int main()
{
    int max_count = 0;
    cout << "Enter number of checks - ";
    cin >> max_count;
    clock_t time;
    clock_t average_time;
    for (unsigned size = 10; size < 1000000; size *= 10) {
	string expr = "1";
	for (int i = 1; i < size; i++) {
	    expr.push_back('+');
	    expr.push_back('1');
	}

	average_time = 0;
	for (unsigned count = 0; count < max_count; count++) {
	    time = clock();
	    Polish::Calculate(Polish::ToPolish(expr));
	    average_time += clock() - time;
	}
	average_time /= max_count;
	cout << "Time is: " << average_time << endl;
    }
    return 0;
}
