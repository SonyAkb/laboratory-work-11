#include <iostream>
using namespace std;

struct Node {
    char data; //������
    Node* ptr_to_next_node = nullptr; //��������� �� ��������� �������
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

void add_elements(List& list, int befor_number) { //�������� ����� �������
    char element;
    cout << "������� ����� ������� ";
    cin >> element;

    Node* new_node = new Node; //������ ����� ����
    new_node->data = element; //���������� �������� ������

    if (befor_number == 1) { //���� �������� ����� ������� ����� ������ ���������
        new_node->ptr_to_next_node = list.head_node;
        list.head_node = new_node;
    }
    else {
        Node* pointer_node = list.head_node;
        for (int i = 0; i < befor_number - 2; i++) { //��� �� �������� ����� ������� ��� �������� �����
            pointer_node = pointer_node->ptr_to_next_node; //������� ����� ����������� ���������
        }
        new_node->ptr_to_next_node = pointer_node->ptr_to_next_node; //�������� ����� ���� �� ���������
        pointer_node->ptr_to_next_node = new_node; //�������� ����� ���� � ����������

    }
}

void print_list(List& list) { //����� �������� ������
    cout << "������� ������:" << endl;
    Node* current_node = list.head_node;
    if (current_node != nullptr) {
        while (current_node != nullptr) { //���� �� ����� �� ���������� ��������
            cout << current_node->data << ' '; //����� ������ �������� ����
            current_node = current_node->ptr_to_next_node; //������� � ���������� ����    
        }
    }
    else {
        cout << "������ ������!";
    }
    cout << endl << endl;
    delete current_node; //������ ������
}

void pop_element(List& list, char num_del_el) { //�������� ��������
    if (list.head_node != nullptr) { //���� ������ �� ������
        Node* pointer_node = list.head_node;
        while (pointer_node != nullptr) { //���� �� ����� �� �����
            if (pointer_node->data == num_del_el) {
                if (pointer_node == list.head_node) { //���� ���� ������� ������ �������
                    Node* new_Head = list.head_node->ptr_to_next_node;
                    delete list.head_node; //������ ������� �������� �������
                    list.head_node = new_Head; //���������� ��������� �������� ����� �������
                    pointer_node = list.head_node;
                }
                else { //���� ������� �� ������ �������
                    Node* before_deletion = list.head_node;
                    while (before_deletion->ptr_to_next_node != pointer_node) {
                        before_deletion = before_deletion->ptr_to_next_node;
                    }
                    before_deletion->ptr_to_next_node = pointer_node->ptr_to_next_node; //�������� ����
                    pointer_node = before_deletion;

                }
            }
            else {
                pointer_node = pointer_node->ptr_to_next_node; //�������� �� ��������� �������
            }
        }
    }
}

void del_all_list(List& list) {
    Node* ptr_node = list.head_node;
    if (ptr_node != nullptr) {
        while (ptr_node != nullptr) {
            Node* new_Head = list.head_node->ptr_to_next_node;
            delete list.head_node; //������ ������� �������� �������
            list.head_node = new_Head; //���������� ��������� �������� ����� �������
            ptr_node = list.head_node;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian"); //�����������
    system("chcp 1251");
    system("cls");

    int n, k, befor_add;
    char symbol_key;

    do {
        cout << "������� ���������� ��������� ";
        cin >> n;
    } while (n < 1);
    cout << endl;

    List list; //������������� ������

    for (int i = 0; i < n; i++) {
        cout << "������� ������ ";
        cin >> symbol_key;
        pushBack(list, symbol_key);
    }
    cout << endl;

    print_list(list); //������ ������� ������

    cout << "������� ���� ��������, ������� �� ������ ������� ";
    cin >> symbol_key;

    cout << endl;
    pop_element(list, symbol_key); //������ �������
    cout << "------" << endl;
    --n; //������� ����� ������
    print_list(list); //������ ������� ������

    do {
        cout << "������� ����� ��������, ����� ������� ���������� �������� ����� �������� ";
        cin >> befor_add; //����� ��������
    } while (befor_add < 1 || befor_add > n);
    cout << endl;

    do {
        cout << "������� ���������� ���������, ������� ���������� �������� ";
        cin >> k; //���������� ���������, ������� ���� ��������
    } while (k < 1);
    n += k; //������� ����� ������
    cout << endl;

    for (int i = 0; i < k; i++) { //�������� ����� ��������
        add_elements(list, befor_add + i);
    }
    cout << endl;
    print_list(list); //������ ������� ������
    cout << "�������� ������ ..." << endl;
    del_all_list(list);

    cout << "���������" << endl;
    cout << endl;
    print_list(list); //������ ������� ������

    return 0;
}