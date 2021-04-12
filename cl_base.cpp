#include "cl_base.h"
#include <iostream>
#include <string.h>
using namespace std;

cl_base::cl_base(cl_base * p_parent) {
	set_object_name("cl_base");

	if (p_parent)
    {
		this->p_parent = p_parent;
		p_parent->add_child(this);
	}
	else
	{
		this->p_parent = 0;
	}
}

void cl_base::set_object_name(string s_object_name) {
	object_name = s_object_name;
}

string cl_base::get_object_name() {
	return object_name;
}

void cl_base::set_parent(cl_base * p_parent) {
	if (p_parent)
	{
		this->p_parent = p_parent;
		p_parent->children.push_back(this);
	}
}

void cl_base::add_child(cl_base * p_child) {
	this->children.push_back(p_child);
}

void cl_base::delete_child(string s_object_name) {
	if (children.size() == 0) return;

	it_child = children.begin();

	while (it_child != children.end())
	{
		if ((*it_child)->get_object_name() == s_object_name)
		{

			children.erase(it_child);
			return;
		}
		it_child++;
	}
}

cl_base * cl_base::take_child(string s_object_name) {
	cl_base * ob_child;

	ob_child = get_child(s_object_name);

	if (ob_child == 0) return 0;

	delete_child(s_object_name);

	return ob_child;
}

cl_base * cl_base::get_child(string s_object_name) {
	if (children.size() == 0) return 0;

	it_child = children.begin();

	while (it_child != children.end())
	{

		if ((*it_child)->get_object_name() == s_object_name)
		{
			return (*it_child);
		}
		it_child++;
	}

	return 0;
}

void cl_base::set_state(int i_state) {
	this->i_state = i_state;
}

int cl_base::get_state() {
	return i_state;
}

void cl_base::show_object_state() {
	show_state_next((cl_base*)this);
}

void cl_base::show_object_tree() {
	int i_level = 0;
	show_object_next(this, i_level);
}

cl_base * cl_base::get_object_root() {

	cl_base * p_parent_previous;

	if (object_name == "root") return this;

	p_parent_previous = p_parent;

	while (p_parent_previous->p_parent)
	{

		p_parent_previous = p_parent_previous->p_parent;
	}
	return p_parent_previous;
}

void cl_base::show_state_next(cl_base * ob_parent) {

	if (ob_parent->get_state() == 1)
	{
		cout << "The object " << ob_parent->get_object_name();
		cout << " is ready" << endl;
	}
	else
	{
		cout << "The object " << ob_parent->get_object_name();
		cout << " is not ready" << endl;
	}

	if (ob_parent->children.size() == 0) return;

	ob_parent->it_child = ob_parent->children.begin();

	while (ob_parent->it_child != ob_parent->children.end())
	{
		show_state_next((*(ob_parent->it_child)));
		ob_parent->it_child++;
	}
}

void cl_base::show_object_next(cl_base * ob_parent, int i_level) {
	string s_space;
	s_space.append(4 * i_level, ' ');
	cout << s_space << ob_parent->get_object_name();
	if (ob_parent->children.size() == 0) return;

	ob_parent->it_child = ob_parent->children.begin();

	while (ob_parent->it_child != ob_parent->children.end()) {
		cout << endl;
		show_object_next((cl_base*)(*(ob_parent->it_child)), i_level + 1);
		ob_parent->it_child++;
	}
}

void cl_base::emit_signal(SIGNAL_TYPE s_ignal, string& s_command) {
	HANDLER_TYPE p_hendler;

	if (connects.empty()) return;
	it_connects = connects.begin();

	bool flag = false;
	while (it_connects != connects.end()){
	    o_sh* p_value = *it_connects;
	    if (p_value -> p_ignal == s_ignal) {
	        flag = true;
        }
        it_connects++;
    }
    if (!flag) return;
    it_connects = connects.begin();
    while (it_connects != connects.end()){
        if (((*it_connects)->p_ignal) == s_ignal) {
            p_hendler = (*it_connects)->p_hendler;
            ((*it_connects)->p_cl_base->*p_hendler)(s_command);
        }
        if (it_connects != connects.end()) {
            it_connects++;
        }
    }
}

void cl_base::set_connect(SIGNAL_TYPE p_signal, cl_base *p_ob_hendler,
                          HANDLER_TYPE p_hendler) {
	SIGNAL_TYPE p_key;
	o_sh* p_value;
	if (connects.size() > 0) {
		it_connects = connects.begin();
		while (it_connects != connects.end()) {
			p_value = *it_connects;
			p_key = p_value->p_ignal;
			if ((p_key) == p_signal &&
                (p_value->p_cl_base) == p_ob_hendler &&
                (p_value->p_hendler) == p_hendler)
                return;
			it_connects++;
		}
	}
    p_value = new o_sh;
    p_value -> p_ignal = p_signal;
    p_value -> p_cl_base = p_ob_hendler;
    p_value -> p_hendler = p_hendler;
    connects.push_back(p_value);
}

cl_base* cl_base::get_pointer(string s) {
	string buff = "";
	bool flag = true;
	int len = s.size();
	int i = 1;
	char sym = 0;
	cl_base *th = this->get_object_root();
	cl_base *th1 = th;
	string name = th1->get_object_name();
	while (true) {
		for (i; i <= len; i++) {
			if (s[i] != '/' && s[i] != '\0') {
				buff += s[i];
			}
			else {
				sym = s[i];
				i++;
				break;
			}
		}
		if ((name == buff) && (flag)) {
			if (sym == '\0') {
				return th;
			}
			else {
				buff.clear();
				flag = false;
				continue;
			}
		}
		if ((!flag)) {
			th = th->get_child(buff);
			if (!th) { return 0; }
			buff.clear();
			if (sym == '\0') {
				return th;
			}
		}
		else return 0;
	}
}
