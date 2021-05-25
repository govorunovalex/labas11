#include <iostream>
#include <locale.h>
#include <string>

#include "polish.h"
#include "tqueue.h"

using namespace std;

int main()
{
    string calc_exp;
    cout << "Enter string: " << endl;
    cin >> calc_exp;

    TQueue < char >polish = Polish::ToPolish(calc_exp);
    cout << "Result is: " << Polish::Calculate(polish) << endl;
    return 0;
}
