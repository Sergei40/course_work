#include "cl_output_result.h"

cl_output_result::cl_output_result() {
    flag = false;
}

void cl_output_result::hendler_4(string& s) {
	if (!flag) {
		cout << s;
		flag = true;
	}
	else {
		cout << endl;
		cout << s;
	}
}
