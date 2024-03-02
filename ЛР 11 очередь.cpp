#include <iostream>
using namespace std;


struct Node {
	char data; //������
	Node* ptr_to_next_node; //��������� �� ��������� �������
};


struct Queue { //�������
	int size; //������
	Node* head_node = nullptr;
	Node* teil_node = nullptr;
};


void init_queue(Queue& q, const char& symbol) { //������������� �������
	Node* new_node = new Node; //���������� ������ ��� ����� �������
	new_node->data = symbol; //���������� ������
	q.head_node = new_node; //�������� �������
	q.teil_node = new_node; //��������� �������
	q.size = 1; //������ �������, �.�. ���� ������ ���� �������
}


void push(Queue& q, const char& symbol) { //�������� ������� � ����� �������
	Node* new_node = new Node; //���������� ������ ��� ����� �������
	q.size++; //���������� ������� ������ ������� �� ����
	new_node->data = symbol; //���������� ������
	new_node->ptr_to_next_node = nullptr; //��������� ������� �� ��������� �� �-�
	q.teil_node ->ptr_to_next_node = new_node; //������� ��������� ������� ��������� �� ����� ���������
	q.teil_node = new_node; //����� ��������� �������
}



void new_queue(Queue& q, int n) { //�������� �������
	char symbol;
	cout << "������� ������� ";
	cin >> symbol;
	init_queue(q, symbol); //������������� ������ ���������
	for (int i = 1; i < n; i++) {
		cout << "������� ������� ";
		cin >> symbol; //���� ��������
		push(q, symbol); //������ ����� ������� � ����� �������
	}
}


void print_queue(Queue& q) { //����� �������
	cout << endl << "������� �������: " << endl;
	Node* tmp = q.head_node; //��������� �� ������ �������
	cout << "start -> ";
	while (tmp != nullptr) { //���� �� ����� �� �����
		cout << tmp -> data << ' '; //������ �������� �������� ��������
		tmp = tmp->ptr_to_next_node; //�������� �� ��������� ����
	}
	cout << "end" << endl;
}

void pop_element(Queue& q) { //������ �������� ������� �� �������
	Node* tmp = q.head_node; //��������� �� ������ �������
	q.head_node = q.head_node->ptr_to_next_node; //������ - ��������� �������
	--q.size; //�������� ����� �������
	delete tmp; //���������� ������
}

void delete_key(Queue& q, char symbol) {
	int counter = 0;
	while (counter != q.size) { //���� �� ������ ��� �������
		if (q.head_node->data == symbol) { //���� ������ ������� - ����
			pop_element(q); //������ ������
		}
		else { //���� ������ ������� - �� ����
			push(q, q.head_node->data); //����������� �������� ������� � ����� �������
			pop_element(q); //������ �������� �������
			++counter;
		}
	}
}

void insert(Queue& q, int quantity, int number) { //�������� �������� � ������ �����
	int counter = 1;
	while (counter != number) { //���� �� ����� �� number
		push(q, q.head_node->data); //����������� �������� ������� � ����� �������
		pop_element(q); //������ �������� �������
		++counter;
		print_queue(q);
	}
	char symbol;
	cout << "----" << endl;
	for (int i = 0; i < quantity; i++) { //�������� ����� ��������
		cout << "������� ������ ";
		cin >> symbol; //����� ����� ������
		push(q, symbol); //�������� ����� ������� � ����� �������
		print_queue(q);
	}
	cout << "----"<< q.size - quantity - number<<' '<< q.size << ' ' << quantity << ' ' << number << endl;
	for (int i = 0; i <= q.size - quantity - number; i++) {

		push(q, q.head_node->data); //����������� �������� ������� � ����� �������
		pop_element(q); //������ �������� �������
		print_queue(q);
	}
}

int main() {
	setlocale(LC_ALL, "Russian"); //�����������
	system("chcp 1251");
	system("cls");

	Queue q;
	int n;

	do {
		cout << "������� ���������� ��������� ";
		cin >> n; //���������� ��������� � ������
	} while (n < 1);
	cout << endl;

	new_queue(q, n); //�������� ����� �������
	print_queue(q);//������ ������� �������

	char symbol_key;

	cout << "������� ���� ��������, ������� �� ������ ������� ";
	cin >> symbol_key;

	delete_key(q, symbol_key); //������ ����
	print_queue(q);//������ ������� �������

	int befor_add, k;

	do {
		cout << "������� ����� ��������, ����� ������� ���������� �������� ����� �������� ";
		cin >> befor_add; //����� ��������
	} while (befor_add < 1 || befor_add > n);
	cout << endl;

	do {
		cout << "������� ���������� ���������, ������� ���������� �������� ";
		cin >> k; //���������� ���������, ������� ���� ��������
	} while (k < 1);
	cout << endl;

	insert(q, k, befor_add);
	print_queue(q);//������ ������� �������

	return 0;
}