#include "TStack.h"
#include <iostream>

using namespace std;

void main() {
    setlocale(LC_ALL, "RUS");
    string infixExpression;

    cout << "������� ���������(���������) ���������: ";
    getline(cin, infixExpression);

    try {
        TCalc calculator;

        calculator.setinfix(infixExpression);

        calculator.ToPostfix();
     
        cout << "����������� �����: " << calculator.getpostfix() << endl;
    	cout << "�����: " << calculator.Calc() << endl;
    }
    catch (int err) {
        cout << "��������� ������: ��� " << err << endl;
    }
    catch (std::exception& ex) {
        cout << "��������� ������: " << ex.what() << endl;
    }
}
//��������� ������:     p=1+2*3      q=1+2*(3+4)         v=(1+2)*(3+4)