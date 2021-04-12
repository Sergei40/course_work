#include "cl_application.h"

cl_application::cl_application() {
	set_object_name("root");

	set_state(1);
}

cl_application::~cl_application() {
    delete ob_operation;
    delete ob_output_result;
    delete ob_input_expression;
}

void cl_application::bild_tree_objects() {
	ob_operation = new cl_operation();
	ob_operation->set_object_name("ob_operation");
	ob_operation->set_parent(this);

	ob_input_expression = new cl_input_expression();
	ob_input_expression->set_object_name("ob_input_expression");
	ob_input_expression->set_parent(this);

	ob_output_result = new cl_output_result();
	ob_output_result->set_object_name("ob_output_result");
	ob_output_result->set_parent(this);
}

void cl_application::exec_app() {
    ob_operation->set_connect(SIGNAL_D(cl_operation::signal_1), ob_operation,
                            HENDLER_D(cl_operation::hendler_1));

	ob_operation->set_connect(SIGNAL_D(cl_operation::signal_2), ob_operation,
                            HENDLER_D(cl_operation::hendler_2));

	ob_operation->set_connect(SIGNAL_D(cl_operation::signal_3), ob_operation,
                            HENDLER_D(cl_operation::hendler_3));

	ob_operation->set_connect(SIGNAL_D(cl_operation::signal_4),
                            ob_output_result,
                            HENDLER_D(cl_output_result::hendler_4));
    calculation();
}

void cl_application::calculation() {
    string operand = "";
	string operation;
	string result = "";

	//entering an arithmetic expression
	ob_input_expression->input();
	string expression =  ob_input_expression->get_expression();

	//Defining the first operand
	int it = expression.find(" ");
	for (int i = 0; i < it; i++) {
		operand += expression[i];
	}

	//calling "signal_1" and passing the first operand
	ob_operation->emit_signal(SIGNAL_D(cl_operation::signal_1), operand);
    operand.clear();

    //Loop to the end of an arithmetic expression
	int length_of_expression = expression.length();
	while (it < length_of_expression)
	{
		//getting the symbol of the next operation
		it++;
		operation += expression[it];

		//calling "signal_2" and passing the operation symbol.
		ob_operation->emit_signal(SIGNAL_D(cl_operation::signal_2), operation);
        operation.clear();

        //Defining the next operand.
		it = it + 2;
		while ((it < length_of_expression) && (expression[it] != ' ')) {
			operand += expression[it];
			it++;
		}

        //calling "signal_3" and passing the next operand.
		ob_operation->emit_signal(SIGNAL_D(cl_operation::signal_3), operand);
        operand.clear();
	}
}
