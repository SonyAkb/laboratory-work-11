#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Stack { //стек
	char data; //данные
	Stack* ptr_to_prev; //адрес на предыдущий элемент
};

Stack* make_stack(int n);
Stack* push(Stack*& the_upper_element, char symbol);
char pop_element(Stack*& the_upper_element); //нахожу верхний элемент	
void from_stack_to_stack(Stack*& stack_num_1, Stack*& stack_num_2, int n);	
void print_stack(Stack* the_upper_element); //вывод стека	
void del_all_stack(Stack*& the_upper_element); //удаление всех элементов стека	
void writing_to_a_file(Stack* the_upper_element, ofstream& file); //запись данных в файл
void recovery(Stack*& the_upper_element, ifstream& file, int n); //восстановление стека

int main() {
	setlocale(LC_ALL, "Russian"); //локализация
	system("chcp 1251");
	system("cls");

	ifstream input("F11.txt"); //входной файловый поток
	ofstream output("F11.txt"); //выходной файловый поток

	int n, k = 0, befor_add;
	char symbol_key;

	do {
		cout << "Введите количество элементов ";
		cin >> n; //количество элементов в списке
	} while (n < 1);
	cout << endl;

	Stack* stack_1 = make_stack(n); //создаю стек
	print_stack(stack_1); //вывожу текущий стек

	cout << "Введите КЛЮЧ элемента, который вы хотите удалить ";
	cin >> symbol_key;

	Stack* stack_2 = make_stack(0); //создаю пустой стек
	for (int i = 0; i < n; i++) {
		//перенос всех элементов кроме элемента с КЛЮЧОМ во второй стек
		char t = pop_element(stack_1); //извлекаю верхний элемент
		if (t != symbol_key) { //если символ не равен ключевому
			push(stack_2, t); //переношу во второй стек
		}
		else { //если символ равен ключевому
			++k; //увеличиваю количество ключевых символов
		}
	}
	n -= k;//изменяю количество элементов в стеке

	from_stack_to_stack(stack_2, stack_1, n);
	print_stack(stack_1); //вывожу текущий стек

	do {
		cout << "Введите количество элементов, которые необходимо ДОБАВИТЬ ";
		cin >> k; //количество элементов, которые надо добавить
	} while (k < 1);
	cout << endl;

	do {
		cout << "Введите номер элемента, ПЕРЕД которым необходимо добавить новые элементы ";
		cin >> befor_add; //НОМЕР элемента
	} while (befor_add < 1 || befor_add > n);
	cout << endl;
	
	from_stack_to_stack(stack_1, stack_2, n - befor_add + 1);

	cout << "Введите новые элементы стека:" << endl;
	for (int i = 0; i < k; i++) {
		cout << "Введите символ ";
		cin >> symbol_key;
		push(stack_1, symbol_key); //добавляю символ в стек 1
	}

	from_stack_to_stack(stack_2, stack_1, n - befor_add + 1);
	print_stack(stack_1); //вывожу текущий стек

	n += k;//изменяю количество элементов в стеке

	cout << "Запись данных в файл ..." << endl;
	writing_to_a_file(stack_1, output);
	cout << "Завершено" << endl << endl;

	cout << "Очищение памяти ..." << endl;
	del_all_stack(stack_1); //очищаю весь стек
	cout << "Завершено" << endl;
	print_stack(stack_1);//вывожу текущий стек

	cout << "Восстановление стека ..." << endl;
	cin.ignore();
	recovery(stack_1, input, n);
	cout << "Завершено" << endl;

	print_stack(stack_1); //вывожу текущую очередь

	input.close(); //закрываю файл
	output.close();//закрываю файл
	return 0;
}

Stack* make_stack(int n) {
	if (n != 0) {
		char symbol;
		Stack* the_upper_element, * pointer_element = new Stack;
		the_upper_element = NULL;

		cout << "Введите элемент ";
		cin >> symbol;

		pointer_element->data = symbol; //присваиваю знаяение новому элементу
		pointer_element->ptr_to_prev = NULL; //адрес на предыдущий элемент
		the_upper_element = pointer_element; //изменяю верхний элемент в стеке

		for (int i = 1; i < n; i++) { //добавление новых элемнтов
			Stack* new_element = new Stack;
			cout << "Введите элемент ";
			cin >> symbol;

			new_element->data = symbol;
			new_element->ptr_to_prev = the_upper_element;
			the_upper_element = new_element;
		}
		return the_upper_element;
	}
	return NULL;
}

Stack* push(Stack*& the_upper_element, char symbol) { //добавление элемента
	Stack* pointer = new Stack; //выделяю память для нового стека
	pointer->data = symbol; //присваиваю данные новому элементу
	pointer->ptr_to_prev = the_upper_element; //адрес предыдущего элемента
	the_upper_element = pointer; //новый верхний элемент
	return the_upper_element; //возвращаю новый верхний элемент
}

char pop_element(Stack*& the_upper_element) { //нахожу верхний элемент
	Stack* pointer_element = the_upper_element;
	int k = 0;
	while (pointer_element != NULL) {
		k++;
		pointer_element = pointer_element->ptr_to_prev;
	}
	pointer_element = the_upper_element;

	if (k == 1) {
		char data_upper = the_upper_element->data; //данные верхнего элемента
		delete pointer_element;
		the_upper_element = NULL;
		return data_upper;
	}
	else {
		Stack* t = pointer_element->ptr_to_prev;
		char data_ptr = pointer_element->data; //данные необходимого элемента
		the_upper_element = t; //меняю верхний элемент
		delete pointer_element;
		return data_ptr;
	}
	//the_upper_element - верхний элемент
}

void from_stack_to_stack(Stack*& stack_num_1, Stack*& stack_num_2, int n) {
	//перенос элементов из стека в стек
	for (int i = 0; i < n; i++) { //переношу элементы из стека 1 в стек 2
		char t = pop_element(stack_num_1); //извлекаю верхний элемент из первого
		push(stack_num_2, t); //переношу элементы во второй стек
	}
}

void print_stack(Stack* the_upper_element) { //вывод стека
	cout << endl << "Текущий стек:" << endl;
	if (the_upper_element != NULL) { //если стек не пустой
		Stack* pointer_element = the_upper_element; //указатель на первый элемент
		while (pointer_element != NULL) { //пока не дойду до нижнего элемента
			cout << pointer_element->data << ' ';
			pointer_element = pointer_element->ptr_to_prev;
		}
		delete pointer_element; //освобождаю память
	}
	else { //если стек пуст
		cout << "Стек пуст!";
	}
	cout << endl << endl;
}

void del_all_stack(Stack*& the_upper_element) { //удаление всех элементов стека
	while (the_upper_element->ptr_to_prev != NULL) {
		Stack* pointer_element = the_upper_element->ptr_to_prev;
		delete the_upper_element; //освобождение памяти верхнего элемента
		the_upper_element = pointer_element;
	}
	the_upper_element = NULL;
}

void writing_to_a_file(Stack* the_upper_element, ofstream& file) { //запись данных в файл
	if (the_upper_element != NULL) { //если стек не пустой
		Stack* pointer_element = the_upper_element; //указатель на первый элемент
		while (pointer_element != NULL) { //пока не дойду до нижнего элемента
			file << pointer_element->data << endl;
			pointer_element = pointer_element->ptr_to_prev;
		}
		delete pointer_element; //освобождаю память
	}
}

void recovery(Stack*& the_upper_element, ifstream& file, int n) { //восстановление стека
	Stack* the_new_stack, * pointer_element = new Stack;
	the_new_stack = NULL;

	string all_str;
	getline(file, all_str); //считываю строку

	pointer_element->data = all_str[0]; //присваиваю знаяение новому элементу
	pointer_element->ptr_to_prev = NULL; //адрес на предыдущий элемент
	the_new_stack = pointer_element; //изменяю верхний элемент в стеке

	while (getline(file, all_str)) { //пока не пройду весь файл
		push(the_new_stack, all_str[0]); //переношу элементы во временный стек
	}
	from_stack_to_stack(the_new_stack, the_upper_element, n); //переношу элементы в главный стек
}