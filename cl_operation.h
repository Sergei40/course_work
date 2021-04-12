#ifndef GETOPERAND_H
#define GETOPERAND_H

#include "cl_base.h"

class cl_operation : public cl_base {
public:
    cl_operation();
    void signal_1(const string& s) {};
    void signal_2(const string& s) {};
    void signal_3(const string& s) {};
    void signal_4(const string& s) {};
    void hendler_1(const string& s);
    void hendler_3(const string& s);
    void hendler_2(const string& s);

private:
    int first;
	char operation;
	int second;
};

#endif
