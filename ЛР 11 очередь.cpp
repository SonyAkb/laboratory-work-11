#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node {
	char data; //данные
	Node* ptr_to_next_node; //указатель на следующий элемент
};

struct Queue { //очередь
	int size; //размер
	Node* head_node = nullptr;
	Node* teil_node = nullptr;
};

void init_queue(Queue& line, const char& symbol); //инициализирую очередь
void push_element(Queue& line, const char& symbol); //добавляю элемент в конец очереди
void new_queue(Queue& line, int n); //формирую очередь
void print_queue(Queue& line); //вывод очереди
void pop_element(Queue& line); //удаляю головной элемент из очереди
void delete_key(Queue& line, char symbol); //удаляю элемент по ключу
void insert(Queue& line, int quantity, int number); //вставляю элементы в нужное место
void delete_all_queue(Queue& line);
void writing_to_a_file(Queue& line, ofstream& file); //запись данных в файл	
void recovery(Queue& line, ifstream& file); //восстановление
	

int main() {
	setlocale(LC_ALL, "Russian"); //локализация
	system("chcp 1251");
	system("cls");

	ifstream input("F11.txt"); //входной файловый поток
	ofstream output("F11.txt"); //выходной файловый поток

	Queue line; //создаю очередь

	int n, befor_add, k;
	char symbol_key;

	do {
		cout << "Введите количество элементов ";
		cin >> n; //количество элементов в списке
	} while (n < 1);
	cout << endl;

	new_queue(line, n); //формирую новую очередь
	print_queue(line);//вывожу текущую очередь

	cout << "Введите КЛЮЧ элемента, который вы хотите удалить ";
	cin >> symbol_key;

	delete_key(line, symbol_key); //удаляю ключ
	print_queue(line); //вывожу текущую очередь

	do {
		cout << "Введите номер элемента, ПЕРЕД которым необходимо добавить новые элементы ";
		cin >> befor_add; //НОМЕР элемента
	} while (befor_add < 1 || befor_add > line.size);
	cout << endl;

	do {
		cout << "Введите количество элементов, которые необходимо добавить ";
		cin >> k; //количество элементов, которые надо добавить
	} while (k < 1);
	cout << endl;

	insert(line, k, befor_add); //всавляю новые элементы
	print_queue(line);//вывожу текущую очередь

	cout << "Запись данных в файл ..." << endl;
	writing_to_a_file(line, output);
	cout << "Завершено" << endl << endl;

	cout << "Очищение памяти ..." << endl;
	delete_all_queue(line); //очищаю всю очередь
	cout << "Завершено" << endl;

	print_queue(line); //вывожу текущую очередь

	cout << "Восстановление очереди ..." << endl;
	cin.ignore();
	recovery(line, input);
	cout << "Завершено" << endl;

	print_queue(line); //вывожу текущую очередь

	input.close(); //закрываю файл
	output.close();//закрываю файл
	return 0;
}

void init_queue(Queue& line, const char& symbol) { //инициализирую очередь
	Node* new_node = new Node; //резервирую память под новый элемент
	new_node->data = symbol; //присваиваю данные
	line.head_node = new_node; //головной элемент
	line.teil_node = new_node; //хвостовой элемент
	line.size = 1; //размер очереди, т.к. есть только один элемент
}

void push_element(Queue& line, const char& symbol) { //добавляю элемент в конец очереди
	Node* new_node = new Node; //резервирую память под новый элемент
	line.size++; //увеличиваю текущий размер очереди на один
	new_node->data = symbol; //присваиваю данные
	new_node->ptr_to_next_node = nullptr; //последний элемент не указывает на ч-л
	line.teil_node->ptr_to_next_node = new_node; //прошлый последний элемент указывает на новый последний
	line.teil_node = new_node; //новый хвостовой элемент
}

void new_queue(Queue& line, int n) { //формирую очередь
	char symbol;
	cout << "Введите элемент ";
	cin >> symbol;
	init_queue(line, symbol); //инициализирую первым элементом
	for (int i = 1; i < n; i++) {
		cout << "Введите элемент ";
		cin >> symbol; //ввод элемента
		push_element(line, symbol); //ставлю новый элемент в конец очереди
	}
}

void print_queue(Queue& line) { //вывод очереди
	cout << endl << "Текущая очередь: " << endl;
	if (line.head_node != nullptr) {
		Node* pointer_q = line.head_node; //указатель на первый элемент
		cout << "start -> ";
		while (pointer_q != nullptr) { //пока не дойду до конца
			cout << pointer_q->data << ' '; //вывожу значение текущего элемента
			pointer_q = pointer_q->ptr_to_next_node; //перехожу на следующий узел
		}
		cout << "-> end" << endl << endl;
	}
	else {
		cout << "Очередь пуста!" << endl << endl;
	}
}

void pop_element(Queue& line) { //удаляю головной элемент из очереди
	Node* pointer_q = line.head_node; //указатель на первый элемент
	line.head_node = line.head_node->ptr_to_next_node; //голова - следующий элемент
	--line.size; //уменьшаю длину очереди
	delete pointer_q; //освобождаю память
}

void delete_key(Queue& line, char symbol) { //удаляю элемент по ключу
	int counter = 0; //счетчик
	while (counter != line.size) { //пока не обойду всю очередь
		if (line.head_node->data == symbol) { //если первый элемент - ключ
			pop_element(line); //удаляю голову
		}
		else { //если первый элемент - НЕ ключ
			push_element(line, line.head_node->data); //переставляю головной элемент в конец очереди
			pop_element(line); //удаляю головной элемент
			++counter;
		}
	}
}

void insert(Queue& line, int quantity, int number) { //вставляю элементы в нужное место
	int counter = 1;
	char symbol;
	while (counter != number) { //пока не дойду до number
		push_element(line, line.head_node->data); //переставляю головной элемент в конец очереди
		pop_element(line); //удаляю головной элемент
		++counter;
	}
	for (int i = 0; i < quantity; i++) { //добавляю новые элементы
		cout << "Введите символ ";
		cin >> symbol; //ввожу новый символ
		push_element(line, symbol); //добавляю новый элемент в конец очереди
	}
	for (int i = 0; i <= line.size - quantity - number; i++) { //переставляю оставшиеся элементы
		push_element(line, line.head_node->data); //переставляю головной элемент в конец очереди
		pop_element(line); //удаляю головной элемент
	}
}

void delete_all_queue(Queue& line) {
	while (line.head_node->ptr_to_next_node != nullptr) { //пока не дойду до последнего элемента
		pop_element(line); //удаляю головной элемент
	}
	Node* pointer_q = line.head_node; //указатель на первый элемент
	line.head_node = nullptr;
	--line.size; //уменьшаю размер
	delete pointer_q; //освобождаю память от последнего элемента
}

void writing_to_a_file(Queue& line, ofstream& file) { //запись данных в файл
	if (line.head_node != nullptr) {
		Node* pointer_q = line.head_node; //указатель на первый элемент
		while (pointer_q != nullptr) { //пока не дойду до конца
			file << pointer_q->data << endl;
			pointer_q = pointer_q->ptr_to_next_node; //перехожу на следующий узел
		}
	}
}

void recovery(Queue& line, ifstream& file) { //восстановление
	string all_str;
	getline(file, all_str); //считываю строку
	init_queue(line, all_str[0]); //добавляю в очередь
	while (getline(file, all_str)) { //пока не пройду фесь файл
		push_element(line, all_str[0]); //добавляю в очередь
	}
}