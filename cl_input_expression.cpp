#include "cl_input_expression.h"

void cl_input_expression::input() {
    cout << "enter an integer expression (example 1 + 5 - 3 * 4 % 2):\n";
	getline(cin, expression);
}

string cl_input_expression::get_expression() {
    return expression;
}
