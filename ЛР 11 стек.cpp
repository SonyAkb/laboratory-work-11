#include <iostream>
using namespace std;

struct Stack {
	char data; //данные
	Stack* ptr_to_prev; //адрес на предыдущий элемент
};



Stack* make_stack( int n) {
	if (n != 0) {
		char symbol;
		Stack* the_upper_element, * pointer_element = new Stack;
		the_upper_element = NULL;

		cout << "Введите символ ";
		cin >> symbol;

		pointer_element->data = symbol; //присваиваю знаяение новому элементу
		pointer_element->ptr_to_prev = NULL; //адрес на предыдущий элемент
		the_upper_element = pointer_element; //изменяю верхний элемент в стеке

		for (int i = 1; i < n; i++) {
			Stack* new_element = new Stack;
			cout << "Введите символ ";
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
	Stack* pointer = new Stack; //выделяю память для нового стека
	pointer->data = symbol; //присваиваю данные новому элементу
	pointer->ptr_to_prev = the_upper_element; //адрес предыдущего элемента
	the_upper_element = pointer; //новый верхний элемент
	return the_upper_element;
}

char pop_element(Stack*& the_upper_element) { //удаление элемента
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
	cout << "Текущий стек:" << endl;
	if (the_upper_element != NULL) {
		Stack* pointer_element = the_upper_element;
		while (pointer_element != NULL) {
			cout << pointer_element->data << ' ';
			pointer_element = pointer_element->ptr_to_prev;
		}
		//память
	}
	else {
		cout << "Стек пуст!";
	}
	cout << endl;

}

int main() {
	setlocale(LC_ALL, "Russian"); //локализация

	int n;
	char symbol;

	do {
		cout << "Введите количество элементов ";
		cin >> n; //количество элементов в списке
	} while (n < 1);
	cout << endl;

	cout << "Введите элементы стека " << endl;

	Stack* st = make_stack(n);
	

	print_stack(st);

	char b;

	cout << "Введите КЛЮЧ элемента, который вы хотите удалить ";
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
		cout << "Введите количество элементов, которые необходимо добавить ";
		cin >> k; //количество элементов, которые надо добавить
	} while (k < 1);

	int befor_add;

	do {
		cout << "Введите номер элемента, ПЕРЕД которым необходимо добавить новые элементы ";
		cin >> befor_add; //НОМЕР элемента
	} while (befor_add < 1 || befor_add > n);
	cout << endl;
	cout << "4---------4" << endl;
	for (int i = 0; i < n - befor_add + 1; i++) {
		char t = pop_element(st);
		push(st2, t);
	}
	cout << "5---------5" << endl;
	for (int i = 0; i < k; i++) {
		cout << "Введите символ ";
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