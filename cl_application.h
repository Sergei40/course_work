#ifndef CL_APPLICATION_H
#define CL_APPLICATION_H

#include "cl_operation.h"
#include "cl_input_expression.h"
#include "cl_output_result.h"

class cl_application : public cl_base
{
public:
    cl_application();
    ~cl_application();
    void bild_tree_objects();
    void exec_app();
    void calculation();

private:
	cl_operation * ob_operation;
	cl_input_expression * ob_input_expression;
	cl_output_result * ob_output_result;

};

#endif
