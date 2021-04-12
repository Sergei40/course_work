#ifndef INPUTEXPRESSION_H
#define INPUTEXPRESSION_H

#include "cl_base.h"

class cl_input_expression : public cl_base
{
public:
	void input();
	string get_expression();

private:
	string expression;
};

#endif
