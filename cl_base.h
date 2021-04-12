#ifndef CL_BASE_H
#define CL_BASE_H

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

class cl_base;

typedef void (cl_base::* SIGNAL_TYPE) (std::string&);
typedef void (cl_base::* HANDLER_TYPE)(std::string&);

#define SIGNAL_D(signal_f)(SIGNAL_TYPE)(&signal_f)
#define HENDLER_D(hendler_f)(HANDLER_TYPE)(&hendler_f)

using namespace std;

class cl_base
{
public:
	cl_base(cl_base* p_parent = 0);
	void set_object_name(string s_object_name);
	string get_object_name();

	// object hierarchy
	void set_parent(cl_base* p_parent);
	void add_child(cl_base* p_child);
	void delete_child(string s_object_name);
	cl_base* take_child(string s_object_name);
	cl_base* get_child(string s_object_name);
	// state of objects
	void set_state(int i_state);
	int get_state();
	cl_base* get_pointer(string s);
	//
	void show_object_state();
	void show_object_tree();
	void show_ob();
	//signals
	void set_connect(SIGNAL_TYPE p_ingal, cl_base* p_ob_hendler,
                    HANDLER_TYPE p_hendler);
	void emit_signal(SIGNAL_TYPE s_ingal, string& s_command);

private:
	struct o_sh {
	    SIGNAL_TYPE p_ignal;
		cl_base* p_cl_base;
		HANDLER_TYPE p_hendler;
	};
	vector<cl_base*> children;
	vector<cl_base*>::iterator it_child;

	vector<o_sh*> connects;
	vector<o_sh*>::iterator it_connects;

	string object_name;
	cl_base* p_parent;
	int i_state;

	cl_base* get_object_root();
	void show_state_next(cl_base * ob_parent);
	void show_object_next(cl_base*ob_parent, int i_level);

};

#endif
