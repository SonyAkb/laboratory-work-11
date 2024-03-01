#include <iostream>
using namespace std;

struct Node {
    char data;
    Node* ptr_to_next_node = nullptr;
};

struct List {
    Node* head_node = nullptr;
    Node* teil_node = nullptr;
};

void pushBack(List& list, const int& data) { //�������� ����� ������� � ����� ������
    Node* new_node = new Node; //������ ����� ������������ ����
    new_node->data = data; //���������� ���� ���� ������

    if (list.head_node == nullptr) { //���� ������ ������
        list.head_node = new_node; //����� ���� - �������� ���� ������
        list.teil_node = new_node; //����� ���� - ��������� ���� ������
    }
    else { // ���� ������ �� �����
        list.teil_node->ptr_to_next_node = new_node; //�������� ����� ���� � ���������
        list.teil_node = new_node; //����� ��������� ���� �� �����
    }
}

void pop_element(List& list, int n) { //�������� ��������
    if (list.head_node == nullptr) { //���� ������ ������
        return;
    }

    int num_del_el;

    do {
        cout << "������� ����� ��������, ������� �� ������ ������� ";
        cin >> num_del_el; //����� ��������
    } while (num_del_el<1 || num_del_el>n);

    if (num_del_el == 1) { //���� ���� ������� ������ �������
        Node* new_Head = list.head_node->ptr_to_next_node;
        delete list.head_node;
        list.head_node = new_Head;
        return;
    }
    
    Node* pointer_node = list.head_node;
    for (int i = 0; i < num_del_el - 2; i++) {
        pointer_node = pointer_node->ptr_to_next_node;
    }
    cout << pointer_node->data<<endl;

    Node* prev = pointer_node->ptr_to_next_node;
    pointer_node->ptr_to_next_node = prev->ptr_to_next_node;
    delete prev;

}

void add_elements(List& list, int befor_number) {
    int element;
    cout << "������� ����� ������� ";
    cin >> element;

    if (befor_number == 1) {
        Node* new_head = new Node;
        new_head->data = element;
        new_head->ptr_to_next_node = list.head_node;
        list.head_node = new_head;
        return;
    }

    Node* pointer_node = list.head_node;
    for (int i = 0; i < befor_number - 2; i++) {
        pointer_node = pointer_node->ptr_to_next_node; //������� ����� ����������� ���������
    }
    cout << pointer_node->data << endl;

    Node* new_node = new Node; //������ ����� ����
    new_node->data = element;
    new_node->ptr_to_next_node = pointer_node->ptr_to_next_node;
    pointer_node->ptr_to_next_node = new_node;   
}

void print_list(List& list) { //����� �������� ������
    Node* current_node = list.head_node;
    while (current_node != nullptr) {
        cout << current_node->data << ' '; //����� ������ �������� ����
        current_node = current_node->ptr_to_next_node; //������� � ���������� ����    
    }
    cout << endl;
    delete current_node;

}

int main() {
    setlocale(LC_ALL, "Russian"); //�����������
    system("chcp 1251");
    system("cls");

    int n, k, befor_add;
    char symbol;

    do {
        cout << "������� ���������� ��������� ";
        cin >> n;
    } while (n < 1);

    List list; //������������� ������

    for (int i = 0; i < n; i++) {
        cout << "������� ������ ";
        cin >> symbol;
        pushBack(list, symbol);
    }

    print_list(list); //������ ������� ������

    pop_element(list, n); //������ �������
    --n; //������� ����� ������
    print_list(list); //������ ������� ������

    do {
        cout << "������� ����� ��������, ����� ������� ���������� �������� ����� �������� ";
        cin >> befor_add; //����� ��������
    } while (befor_add < 1 || befor_add > n);
    do {
        cout << "������� ���������� ���������, ������� ���������� �������� ";
        cin >> k; //���������� ���������, ������� ���� ��������
    } while (k<1);

    for (int i = 0; i < k; i++) { //�������� ����� ��������
        add_elements(list, befor_add);
    }

    print_list(list); //������ ������� ������

    return 0;
}