#include <iostream>
using namespace std;

struct Stack {
	char data; //������
	Stack* ptr_to_prev; //����� �� ���������� �������
};



Stack* make_stack( int n) {
	if (n != 0) {
		char symbol;
		Stack* the_upper_element, * pointer_element = new Stack;
		the_upper_element = NULL;

		cout << "������� ������ ";
		cin >> symbol;

		pointer_element->data = symbol; //���������� �������� ������ ��������
		pointer_element->ptr_to_prev = NULL; //����� �� ���������� �������
		the_upper_element = pointer_element; //������� ������� ������� � �����

		for (int i = 1; i < n; i++) {
			Stack* new_element = new Stack;
			cout << "������� ������ ";
			cin >> symbol;

			new_element->data = symbol;
			new_element->ptr_to_prev = the_upper_element;
			the_upper_element = new_element;
		}
		return the_upper_element;
	}
	return NULL;
}

Stack* push(Stack*& the_upper_element, char symbol) {
	Stack* pointer = new Stack; //������� ������ ��� ������ �����
	pointer->data = symbol; //���������� ������ ������ ��������
	pointer->ptr_to_prev = the_upper_element; //����� ����������� ��������
	the_upper_element = pointer; //����� ������� �������
	return the_upper_element;
}

char pop_element(Stack*& the_upper_element) { //�������� ��������
	Stack* pointer_element = the_upper_element;
	int k = 0;
	while (pointer_element != NULL) {
		k++;
		pointer_element = pointer_element->ptr_to_prev;
	}
	pointer_element = the_upper_element;
	if (k == 1) {
		char t = the_upper_element->data;
		delete pointer_element;
		the_upper_element = NULL;
		return t;
	}
	else {
		Stack* t = pointer_element->ptr_to_prev;
		char u = pointer_element->data;
		the_upper_element = t;
		delete pointer_element;
		return u;
	}
}



void print_stack(Stack* the_upper_element) {
	cout << "������� ����:" << endl;
	if (the_upper_element != NULL) {
		Stack* pointer_element = the_upper_element;
		while (pointer_element != NULL) {
			cout << pointer_element->data << ' ';
			pointer_element = pointer_element->ptr_to_prev;
		}
		//������
	}
	else {
		cout << "���� ����!";
	}
	cout << endl;

}

int main() {
	setlocale(LC_ALL, "Russian"); //�����������

	int n;
	char symbol;

	do {
		cout << "������� ���������� ��������� ";
		cin >> n; //���������� ��������� � ������
	} while (n < 1);
	cout << endl;

	cout << "������� �������� ����� " << endl;

	Stack* st = make_stack(n);
	

	print_stack(st);

	char b;

	cout << "������� ���� ��������, ������� �� ������ ������� ";
	cin >> b;

	int k = 0;
	cout << "1---------1" << endl;
	Stack* st2 = make_stack(0);
	for (int i = 0; i < n; i++) {
		cout << i<<' ' << endl;
		char t = pop_element(st);
		cout << i << ' ' <<t << endl;
		if (t != b) {
			push(st2, t);
		}
		else {
			++k;
		}
	}
	n -= k;
	cout << "2---------2" << endl;
	for (int i = 0; i < n; i++) {
		char t = pop_element(st2);
		push(st, t);
	}
	cout << "3---------3" << endl;
	print_stack(st);

	do {
		cout << "������� ���������� ���������, ������� ���������� �������� ";
		cin >> k; //���������� ���������, ������� ���� ��������
	} while (k < 1);

	int befor_add;

	do {
		cout << "������� ����� ��������, ����� ������� ���������� �������� ����� �������� ";
		cin >> befor_add; //����� ��������
	} while (befor_add < 1 || befor_add > n);
	cout << endl;
	cout << "4---------4" << endl;
	for (int i = 0; i < n - befor_add + 1; i++) {
		char t = pop_element(st);
		push(st2, t);
	}
	cout << "5---------5" << endl;
	for (int i = 0; i < k; i++) {
		cout << "������� ������ ";
		cin >> b;

		push(st, b);
	}
	cout << "6---------6" << endl;
	for (int i = 0; i < n - befor_add + 1; i++) {

		char t = pop_element(st2);
		push(st, t);
	}
	cout << "7---------7" << endl;
	print_stack(st);

	return 0;
}