#include <iostream>
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


void init_queue(Queue& q, const char& symbol) { //инициализирую очередь
	Node* new_node = new Node; //резервирую память под новый элемент
	new_node->data = symbol; //присваиваю данные
	q.head_node = new_node; //головной элемент
	q.teil_node = new_node; //хвостовой элемент
	q.size = 1; //размер очереди, т.к. есть только один элемент
}


void push(Queue& q, const char& symbol) { //добавляю элемент в конец очереди
	Node* new_node = new Node; //резервирую память под новый элемент
	q.size++; //увеличиваю текущий размер очереди на один
	new_node->data = symbol; //присваиваю данные
	new_node->ptr_to_next_node = nullptr; //последний элемент не указывает на ч-л
	q.teil_node ->ptr_to_next_node = new_node; //прошлый последний элемент указывает на новый последний
	q.teil_node = new_node; //новый хвостовой элемент
}



void new_queue(Queue& q, int n) { //формирую очередь
	char symbol;
	cout << "Введите элемент ";
	cin >> symbol;
	init_queue(q, symbol); //инициализирую первым элементом
	for (int i = 1; i < n; i++) {
		cout << "Введите элемент ";
		cin >> symbol; //ввод элемента
		push(q, symbol); //ставлю новый элемент в конец очереди
	}
}


void print_queue(Queue& q) { //вывод очереди
	cout << endl << "Текущая очередь: " << endl;
	Node* tmp = q.head_node; //указатель на первый элемент
	cout << "start -> ";
	while (tmp != nullptr) { //пока не дойду до конца
		cout << tmp -> data << ' '; //вывожу значение текущего элемента
		tmp = tmp->ptr_to_next_node; //перехожу на следующий узел
	}
	cout << "end" << endl;
}

void pop_element(Queue& q) { //удаляю головной элемент из очереди
	Node* tmp = q.head_node; //указатель на первый элемент
	q.head_node = q.head_node->ptr_to_next_node; //голова - следующий элемент
	--q.size; //уменьшаю длину очереди
	delete tmp; //освобождаю память
}

void delete_key(Queue& q, char symbol) {
	int counter = 0;
	while (counter != q.size) { //пока не обойду всю очередь
		if (q.head_node->data == symbol) { //если первый элемент - ключ
			pop_element(q); //удаляю голову
		}
		else { //если первый элемент - НЕ ключ
			push(q, q.head_node->data); //переставляю головной элемент в конец очереди
			pop_element(q); //удаляю головной элемент
			++counter;
		}
	}
}

void insert(Queue& q, int quantity, int number) { //вставляю элементы в нужное место
	int counter = 1;
	while (counter != number) { //пока не дойду до number
		push(q, q.head_node->data); //переставляю головной элемент в конец очереди
		pop_element(q); //удаляю головной элемент
		++counter;
		print_queue(q);
	}
	char symbol;
	cout << "----" << endl;
	for (int i = 0; i < quantity; i++) { //добавляю новые элементы
		cout << "Введите символ ";
		cin >> symbol; //ввожу новый символ
		push(q, symbol); //добавляю новый элемент в конец очереди
		print_queue(q);
	}
	cout << "----"<< q.size - quantity - number<<' '<< q.size << ' ' << quantity << ' ' << number << endl;
	for (int i = 0; i <= q.size - quantity - number; i++) {

		push(q, q.head_node->data); //переставляю головной элемент в конец очереди
		pop_element(q); //удаляю головной элемент
		print_queue(q);
	}
}

int main() {
	setlocale(LC_ALL, "Russian"); //локализация
	system("chcp 1251");
	system("cls");

	Queue q;
	int n;

	do {
		cout << "Введите количество элементов ";
		cin >> n; //количество элементов в списке
	} while (n < 1);
	cout << endl;

	new_queue(q, n); //формирую новую очередь
	print_queue(q);//вывожу текущую очередь

	char symbol_key;

	cout << "Введите КЛЮЧ элемента, который вы хотите удалить ";
	cin >> symbol_key;

	delete_key(q, symbol_key); //удаляю ключ
	print_queue(q);//вывожу текущую очередь

	int befor_add, k;

	do {
		cout << "Введите номер элемента, ПЕРЕД которым необходимо добавить новые элементы ";
		cin >> befor_add; //НОМЕР элемента
	} while (befor_add < 1 || befor_add > n);
	cout << endl;

	do {
		cout << "Введите количество элементов, которые необходимо добавить ";
		cin >> k; //количество элементов, которые надо добавить
	} while (k < 1);
	cout << endl;

	insert(q, k, befor_add);
	print_queue(q);//вывожу текущую очередь

	return 0;
}