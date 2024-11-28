#pragma once
#include <string>
#include <iostream>

using namespace std;

template <class T>
class TStack {
	T* pMem;
	int MaxSize, num;
public:
	TStack(int);
	~TStack();
	TStack(const TStack&);
	TStack& operator =(const TStack&);
	bool operator ==(const TStack&) const;
	bool operator !=(const TStack&) const;
	bool empty(const TStack&) const;
	bool full(const TStack&) const;
	T pop();
	T top() const;
	bool isEmpty() const;
	bool isFull() const;
	void push(T);
	void clear() {
		num = -1;
	};
};

template <class T>
TStack<T>::TStack(int _MaxSize) {
	if (_MaxSize <= 0) {
		throw -1;
	}

	MaxSize = _MaxSize;
	num = -1;
	pMem = new T[MaxSize];
}

template <class T>
TStack<T>::~TStack() {
	delete[] pMem;
}

template<class T>
TStack<T>::TStack(const TStack& st) {
	MaxSize = st.MaxSize;
	num = st.num;
	pMem = new T[MaxSize];
	for (int i = 0; i <= num; i++) {
		pMem[i] = st.pMem[i];
	}
}

template<class T>
TStack<T>& TStack<T>::operator =(const TStack& st)
{
	if (this != &st) {
		if (MaxSize != st.MaxSize) {
			MaxSize = st.MaxSize;
			delete[] pMem;
			pMem = new T[MaxSize];
		}
		num = st.num;
		for (int i = 0; i < MaxSize; i++) pMem[i] = st.pMem[i];
	}
	return *this;
}

template<class T>
bool TStack<T>:: operator==(const TStack& st) const {
	if (num != st.num) return false;
	for (int i = 0; i <= num; i++) {
		if (pMem[i] != st.pMem[i]) return false;
	}
	return true;
}

template<class T>
bool TStack<T>:: operator!=(const TStack& st) const {
	return !(*this == st);
}

template<class T>
bool TStack<T>::empty(const TStack& st) const
{
	if (st.num == st.MaxSize - 1) return true;
	return false;
}

template<class T>
bool TStack<T>::full(const TStack& st) const
{
	if (st.num == 0) return true;
	return false;
}

template<class T>
bool TStack<T>::isEmpty() const {
	return num == -1;
}

template<class T>
bool TStack<T>::isFull() const {
	return num == MaxSize - 1;
}
template<class T>
T TStack<T>::top() const {
	if (isEmpty()) {
		throw -2;
	}
	return pMem[num];
}

template<class T>
T TStack<T>::pop() {
	if (this->isEmpty()) { throw -3; }
	T tmp = pMem[num];
	num--;
	cerr << "Pop: " << tmp << ", New num=" << num << endl;
	return tmp;
}

template<class T>
void TStack<T>::push(T val) {
	if (this->isFull()) throw -4;
	num++;
	pMem[num] = val;
}

class TCalc {
	string infix;
	string postfix;
	TStack <double> stackwnum;
	TStack <char> stackwchar;
	bool isUnaryMinus(size_t i) const {
		if (i == 0) return 0;;
		string s = "(" + infix + ")";
		return s[i] == '-' && (i == 0 || (i > 0 && s[i - 1] == '('));
	}
public:
	TCalc() : infix(""), postfix(""), stackwnum(100), stackwchar(100) {}
	TCalc(const string& in, const string& post, int stackSize) : infix(in), postfix(post), stackwnum(stackSize), stackwchar(stackSize) {}
	void setpostfix(string post) { postfix=post; };
	string getpostfix() { return postfix; };
	void setinfix(string in) {  infix=in; };
	string getinfix() { return infix; };
	void ToPostfix();
	double CalcPostfix();
    double Calc();
	int Priority(char op);
	double stod_custom(const string& str) {
		double result = 0.0;
		bool negative = false;
		size_t i = 0;

		if (i < str.size() && str[i] == '-') {
			negative = true;
			i++;
		}
		else if (i < str.size() && str[i] == '+') {
			i++;
		}

		while (i < str.size() && isdigit(str[i])) {
			result = result * 10 + (str[i] - '0');
			i++;
		}

		if (i < str.size() && str[i] == '.') {
			i++;
			double fraction = 1.0;
			while (i < str.size() && isdigit(str[i])) {
				fraction /= 10;
				result += (str[i] - '0') * fraction;
				i++;
			}
		}

		if (i < str.size()) {
			throw invalid_argument("Неправильная входная строка");
		}
		return negative ? -result : result;
	}
};

inline void TCalc::ToPostfix()
{                                                                                                                                                                                                                                                                                                                  
	postfix = "";
	stackwchar.clear();
	string s = "(" + infix + ")";
	for (int i = 0; i < s.length(); i++) {
		cout << "Processing character " << s[i] << " at index " << i << endl;
		if (s[i] == '(') stackwchar.push(s[i]);
		else if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.'|| (i < s.length() && isUnaryMinus(i))) {
			size_t idx = i;
			while (idx < s.length() && ((s[idx] >= '0' && s[idx] <= '9') || s[idx] == '.' || isUnaryMinus(idx))) {
				postfix += s[idx];
				idx++;
			}
			postfix += " ";
			i = idx - 1;
		}

		else if (s[i] - '0' <= 9 && s[i] - '0' >= 0) { 
			postfix += s[i];
			while (i + 1 < s.length() && (s[i + 1] >= '0' && s[i + 1] <= '9')) {
				i++;
				postfix += s[i];
			}
			postfix += " "; 
		}
		
		else if (s[i] == ')') {
			if (stackwchar.isEmpty()) {
				throw runtime_error("Стек пуст(");
			}
			char a = stackwchar.pop();
			while (a != '(') { 
				postfix += a; 
				postfix += " ";
				if (stackwchar.isEmpty()) {  
					throw runtime_error("Стек пуст");
				}
				a = stackwchar.pop();
			}
		}
		else if (s[i] == '+'|| s[i] == '-' || s[i] == '/' || s[i] == '*') {
			while (!stackwchar.isEmpty() && Priority(stackwchar.top()) >= Priority(s[i])) { postfix += stackwchar.pop();  postfix += " ";}
			stackwchar.push(s[i]);
		}
	}

}



inline double TCalc::CalcPostfix()
{
	stackwnum.clear();

	size_t i = 0;
	while (i < postfix.size()) {
		char ch = postfix[i];

		if (ch == ' ') {
			i++;
			continue;
		}

		if ((ch >= '0' && ch <= '9') || ch == '.' || (ch == '-' &&
			(i == 0 || postfix[i - 1] == ' '))) {
			size_t idx = i;
			string number;

			while (idx < postfix.size() && ((postfix[idx] >= '0' && postfix[idx] <= '9') || postfix[idx] == '.' || postfix[idx] == '-')) {
				number += postfix[idx];
				idx++;
			}

			stackwnum.push(stod_custom(number)); // -> double
			i = idx; 
			continue;
		}

		if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
			double secondNum = stackwnum.pop();
			double firstNum = stackwnum.pop();

			if (ch == '+') {
				stackwnum.push(round((firstNum + secondNum) * 100) / 100);
			}
			else if (ch == '-') {
				stackwnum.push(round((firstNum - secondNum) * 100) / 100);
			}
			else if (ch == '*') {
				stackwnum.push(round((firstNum * secondNum) * 100) / 100);
			}
			else if (ch == '/') {
				if (secondNum == 0) {
					throw runtime_error("Деление на ноль(");
				}
				stackwnum.push(round((firstNum / secondNum) * 100) / 100);
			}
		}
		i++;
	}

	return stackwnum.pop();
}

inline double TCalc::Calc()
{  
	string str = "(" + infix + ")";
	stackwchar.clear();
	stackwnum.clear();
	for (int i = 0; i < str.size(); i++) {
		cout << "Processing character " << str[i] << " at index " << i << endl;
		char tmp = str[i];
		if (tmp == '(')
			stackwchar.push(tmp);

		else if ((tmp >= '0' && tmp <= '9') || tmp == '.' || (i < str.size() && isUnaryMinus(i))) {
			size_t idx = i;
			string number;
			while (idx < str.size() && ((str[idx] >= '0' && str[idx] <= '9') || str[idx] == '.' || isUnaryMinus(idx))) {
				number += str[idx];
				idx++;
			}
			stackwnum.push(stod_custom(number));  // -> double
			i = idx - 1;
		}

		else if (str[i] == ')') {
			char a = stackwchar.pop();
			while (a != '(') {
				double sec_num = stackwnum.pop();
				double fir_num = stackwnum.pop();
				if (a == '+')stackwnum.push(round((fir_num + sec_num) * 100) / 100);
				else if (a == '-')stackwnum.push(round((fir_num - sec_num) * 100) / 100);
				else if (a == '*')stackwnum.push(round((fir_num * sec_num) * 100) / 100);
				else if (a == '/') {
					if (sec_num == 0)
						throw -5;
					stackwnum.push(round((fir_num / sec_num) * 100) / 100);
				}
				
				a = stackwchar.pop();
			}
		}
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ) {
			while (!stackwchar.isEmpty() && Priority(stackwchar.top()) >= Priority(str[i])) {
				double sec_num = stackwnum.pop();
				double fir_num = stackwnum.pop();
				char a = stackwchar.pop();
				if (a == '+')stackwnum.push(round((fir_num + sec_num) * 100) / 100);
				else if (a == '-') stackwnum.push(round((fir_num - sec_num) * 100) / 100);
				else if (a == '*') stackwnum.push(round((fir_num * sec_num) * 100) / 100);
				else if (a == '/') {
					if (sec_num == 0) throw -6;
					stackwnum.push(round((fir_num / sec_num) * 100) / 100);
				}
			}
			stackwchar.push(str[i]);
		}
			
	}
	return stackwnum.pop();		
}

inline int TCalc::Priority(char op) {
	switch (op) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '(':
		return 0;
	case ')':
		return -1;
	default:
		return -1;
	}
}