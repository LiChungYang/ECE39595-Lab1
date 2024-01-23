#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include "hash_list.h"
using std::cout;
using std::cin;
using std::endl;

void _test_no_constructor_zero_node() {
    hash_list list;
	hash_list list_cpy(list);

	assert(list.get_size() == list_cpy.get_size());
	cout << "_test_no_constructor_zero_node() passed" << endl;
}
void _test_copy_constructor_one_node(){
    hash_list list;
    list.insert(1,1);
    assert(list.get_size() == 1 && list.get_value(1).value_or(0) == 1);

    hash_list list_cpy(list);
    assert(list_cpy.get_size() == 1);
    assert(list_cpy.get_value(1).value_or(0) == list.get_value(1).value_or(0));
    cout << "_test_copy_constructor_one_node passed" <<endl;
}

void _test_copy_constructor_three_node(){
    hash_list list;
    list.insert(1,1);
    list.insert(2,2);
    list.insert(3,3);

    assert(list.get_size() == 3); 
    assert(list.get_value(1).value_or(0) == 1);
    assert(list.get_value(2).value_or(0) == 2);
	assert(list.get_value(3).value_or(0) == 3);
	
    hash_list list_cpy(list);
    assert(list_cpy.get_size() == 3);
    assert(list_cpy.get_value(1).value_or(0) == list.get_value(1).value_or(0));
    assert(list_cpy.get_value(2).value_or(0) == list.get_value(2).value_or(0));
    assert(list_cpy.get_value(3).value_or(0) == list.get_value(3).value_or(0));
    cout << "_test_copy_constructor_three_node passed" <<endl;
}

void _test_copy_constructor_six_nodes() {

    hash_list list;
    list.insert(1,1);
    list.insert(2,2);
    list.insert(3,3);
    list.insert(4,4);
    list.insert(5,5);
    list.insert(6,6);

	assert(list.get_size() == 6);

	hash_list list_cpy(list);
    assert(list_cpy.get_size() == list.get_size());
    assert(list_cpy.get_value(1).value_or(0) == list.get_value(1).value_or(0));
    assert(list_cpy.get_value(2).value_or(0) == list.get_value(2).value_or(0));
    assert(list_cpy.get_value(3).value_or(0) == list.get_value(3).value_or(0));
    assert(list_cpy.get_value(4).value_or(0) == list.get_value(4).value_or(0));
    assert(list_cpy.get_value(5).value_or(0) == list.get_value(5).value_or(0));
    assert(list_cpy.get_value(6).value_or(0) == list.get_value(6).value_or(0));

	cout << "_test_copy_constructor_six_nodes() passed " << endl; 
}

void _test_equal_self() {
	hash_list list;
	list.insert(1,1);

	list = list;
}

void _test_equal_operator() {
	hash_list list;
	list.insert(1,1);

	hash_list other = list;

	assert(other.get_size() == list.get_size());
	assert(other.get_value(1) == list.get_value(1));
	cout << "_test_equal_operator() passed" << endl;
}

void _test_equal_six_nodes() {
    hash_list list;
    list.insert(1,1);
    list.insert(2,2);
    list.insert(3,3);
    list.insert(4,4);
    list.insert(5,5);
    list.insert(6,6);

	hash_list list_cpy = list;
	assert(list_cpy.get_size() == list.get_size());
	assert(list_cpy.get_value(1) == list.get_value(1));
	assert(list_cpy.get_value(2) == list.get_value(2));
	assert(list_cpy.get_value(3) == list.get_value(3));
	assert(list_cpy.get_value(4) == list.get_value(4));
	assert(list_cpy.get_value(5) == list.get_value(5));
	assert(list_cpy.get_value(6) == list.get_value(6));
	cout << "_test_equal_six_nodes() passed" << endl;
}

void _test_A_eq_B_eq_C_operator() {
    hash_list list;
    list.insert(1,1);

    hash_list list_cpy_1;
	hash_list list_cpy_2;

	list_cpy_2 = list_cpy_1 = list;

    assert(list_cpy_1.get_size() == (list_cpy_1.get_size() == list_cpy_2.get_size()));
    assert(list_cpy_1.get_value(1) == (list.get_value(1) == list_cpy_2.get_value(1)));
    cout << " _test_A_eq_B_eq_C_operator() passed" << endl;    
}

void _test_A_eq_B_same_size_diff_val(){
    hash_list list;
    list.insert(1,1);
    hash_list list1;
    list1.insert(1,2);
    list1 = list;

    assert(list1.get_size() == list.get_size());
    assert(list1.get_value(1) == list.get_value(1));
    cout<< "_test_A_eq_B_same_size_diff_val() passed" << endl;
}

int main(int argc, char *argv[]) {
	_test_no_constructor_zero_node();
    _test_copy_constructor_one_node();
	_test_copy_constructor_three_node();
	_test_copy_constructor_six_nodes();
	_test_equal_self();
	_test_equal_operator();
	_test_equal_six_nodes();
	_test_A_eq_B_eq_C_operator();
    _test_A_eq_B_same_size_diff_val();
	return EXIT_SUCCESS;
}
