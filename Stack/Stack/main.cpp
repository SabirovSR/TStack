#include "TStack.h"
#include <iostream>

using namespace std;

void main() {
    setlocale(LC_ALL, "RUS");
    string infixExpression;

    cout << "Введите инфиксное(привычное) выражение: ";
    getline(cin, infixExpression);

    try {
        TCalc calculator;

        calculator.setinfix(infixExpression);

        calculator.ToPostfix();
     
        cout << "Постфиксная форма: " << calculator.getpostfix() << endl;
    	cout << "Ответ: " << calculator.Calc() << endl;
    }
    catch (int err) {
        cout << "Произошла ошибка: код " << err << endl;
    }
    catch (std::exception& ex) {
        cout << "Произошла ошибка: " << ex.what() << endl;
    }
}
//Инфиксная запись:     p=1+2*3      q=1+2*(3+4)         v=(1+2)*(3+4)