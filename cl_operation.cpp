#include "cl_operation.h"
cl_operation::cl_operation() {
	set_state(1);
}

void cl_operation::hendler_1(const string& s) {
	first = stoi(s);
}

void cl_operation::hendler_2(const string& s) {
	operation = s[0];
}

void cl_operation::hendler_3(const string& s) {
	int result = 0;
	second = stoi(s);

	switch (operation) {
	case '+':
		result = first + second;
		break;
	case '*':
		result = first * second;
		break;
	case '-':
		result = first - second;
		break;
	case '%':
		result = first % second;
		break;
	}
    string str_out = "";
    str_out = str_out + to_string(first) + " " + operation + " ";
    first = result;

    str_out = str_out + to_string(second) + " = ";

    str_out = str_out + to_string(result);

	this->emit_signal(SIGNAL_D(signal_4), str_out);
	str_out.clear();
}
