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

		for (int i = 1; i < n; i++) { //���������� ����� ��������
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
	return the_upper_element; //��������� ����� ������� �������
}

char pop_element(Stack*& the_upper_element) { //������ ������� �������
	Stack* pointer_element = the_upper_element;
	int k = 0;
	while (pointer_element != NULL) {
		k++;
		pointer_element = pointer_element->ptr_to_prev;
	}
	pointer_element = the_upper_element;

	if (k == 1) {
		char data_upper = the_upper_element->data; //������ �������� ��������
		delete pointer_element;
		the_upper_element = NULL;
		return data_upper;
	}
	else {
		Stack* t = pointer_element->ptr_to_prev;
		char data_ptr = pointer_element->data; //������ ������������ ��������
		the_upper_element = t; //����� ������� �������
		delete pointer_element;
		return data_ptr;
	}
	//the_upper_element - ������� �������
}

void from_stack_to_stack(Stack*& stack_num_1, Stack*& stack_num_2, int n) {
	//������� ��������� �� ����� � ����
	for (int i = 0; i < n; i++) { //�������� �������� �� ����� 1 � ���� 2
		char t = pop_element(stack_num_1); //�������� ������� ������� �� �������
		push(stack_num_2, t); //�������� �������� �� ������ ����
	}
}


void print_stack(Stack* the_upper_element) {
	cout << endl << "������� ����:" << endl;
	if (the_upper_element != NULL) { //���� ���� �� ������
		Stack* pointer_element = the_upper_element;
		while (pointer_element != NULL) { //���� �� ����� �� ������� ��������
			cout << pointer_element->data << ' ';
			pointer_element = pointer_element->ptr_to_prev;
		}
		delete pointer_element; //���������� ������
	}
	else { //���� ���� ����
		cout << "���� ����!";
	}
	cout << endl << endl;
}

void del_all_stack(Stack*& the_upper_element) { //�������� ���� ��������� �����
	while (the_upper_element->ptr_to_prev != NULL) {
		Stack* pointer_element = the_upper_element->ptr_to_prev;
		delete the_upper_element; //������������ ������ �������� ��������
		the_upper_element = pointer_element;
	}
	the_upper_element = NULL;
}

int main() {
	setlocale(LC_ALL, "Russian"); //�����������
	system("chcp 1251");
	system("cls");

	int n, k = 0, befor_add;
	char symbol_key;

	do {
		cout << "������� ���������� ��������� ";
		cin >> n; //���������� ��������� � ������
	} while (n < 1);
	cout << endl;

	cout << "������� �������� �����:" << endl;

	Stack* stack_1 = make_stack(n); //������ ����
	print_stack(stack_1); //������ ������� ����

	cout << "������� ���� ��������, ������� �� ������ ������� ";
	cin >> symbol_key;

	Stack* stack_2 = make_stack(0); //������ ������ ����
	for (int i = 0; i < n; i++) {
		//������� ���� ��������� ����� �������� � ������ �� ������ ����
		char t = pop_element(stack_1); //�������� ������� �������
		if (t != symbol_key) { //���� ������ �� ����� ���������
			push(stack_2, t); //�������� �� ������ ����
		}
		else { //���� ������ ����� ���������
			++k; //���������� ���������� �������� ��������
		}
	}
	n -= k;//������� ���������� ��������� � �����

	from_stack_to_stack(stack_2, stack_1, n);
	print_stack(stack_1); //������ ������� ����

	do {
		cout << "������� ���������� ���������, ������� ���������� �������� ";
		cin >> k; //���������� ���������, ������� ���� ��������
	} while (k < 1);
	cout << endl;

	do {
		cout << "������� ����� ��������, ����� ������� ���������� �������� ����� �������� ";
		cin >> befor_add; //����� ��������
	} while (befor_add < 1 || befor_add > n);
	cout << endl;
	
	from_stack_to_stack(stack_1, stack_2, n - befor_add + 1);

	cout << "������� ����� �������� �����:" << endl;
	for (int i = 0; i < k; i++) {
		cout << "������� ������ ";
		cin >> symbol_key;
		push(stack_1, symbol_key); //�������� ������ � ���� 1
	}

	from_stack_to_stack(stack_2, stack_1, n - befor_add + 1);
	print_stack(stack_1); //������ ������� ����

	n += k;//������� ���������� ��������� � �����
	cout << "�������� ������ ..." << endl;
	del_all_stack(stack_1); //
	print_stack(stack_1);//������ ������� ����
	return 0;
}