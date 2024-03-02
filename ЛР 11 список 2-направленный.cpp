#include <iostream>
using namespace std;

struct Node {
    char data; //������
    Node* ptr_to_prev_node = nullptr; //��������� �� ���������� �������
    Node* ptr_to_next_node = nullptr; //��������� �� ��������� �������
};

struct List {
    Node* head_node = nullptr;
    Node* teil_node = nullptr;
};

void insrt_Item(List& list, const int& data, const int& index = 0, int selector = 1) { //�������� ����� ������� � ����� ������
    Node* new_node = new Node; //������ ����� ������������ ����
    new_node->data = data; //���������� ���� ���� ������

    if (list.head_node == nullptr) { //���� ������ ������
        list.head_node = new_node; //����� ���� - �������� ���� ������
        list.teil_node = new_node; //����� ���� - ��������� ���� ������
    }
    else { //���� ������ �� ������
        if (index == 0 && selector == 2) {
            new_node->ptr_to_next_node = list.head_node; //�������� ����� ���� � ��������
            list.head_node = new_node; //����� �������� ����
        }
        else {
            int counter = 0;
            Node* current_node = list.head_node;
            while (counter != index) { //��� �� ��������, ������� ���� �������
                current_node = current_node->ptr_to_next_node;
                ++counter;
            }
            new_node->ptr_to_prev_node = current_node;
            if (current_node->ptr_to_next_node != nullptr) {
                new_node->ptr_to_next_node = current_node->ptr_to_next_node; //�������� ����
                current_node->ptr_to_next_node->ptr_to_prev_node = new_node;
            }
            current_node->ptr_to_next_node = new_node;
            list.teil_node = new_node;
        }
    }
}

void pop_element(List& list, char num_del_el, int n) { //�������� ��������
    if (list.head_node != nullptr) { //���� ������ ������
        Node* pointer_node = list.head_node;
        while (pointer_node != nullptr) { //���� �� ����� �� �����
            if (pointer_node->data == num_del_el) { //���� ������ �������� �������
                if (pointer_node == list.head_node) { //���� ������� �������� �������
                    Node* new_Head = list.head_node->ptr_to_next_node;
                    delete list.head_node; //������ ������� �������� �������
                    list.head_node = new_Head; //����� ������   
                    pointer_node = list.head_node; //������� ������� �������� ��������
                }
                else if (pointer_node == list.teil_node) { //���� ������� ��������� �������
                    Node* new_Teil = list.teil_node->ptr_to_prev_node;
                    new_Teil->ptr_to_next_node = nullptr;
                    delete list.teil_node; //������ ������� ��������� �������
                    list.teil_node = new_Teil; //����� �����
                    pointer_node = nullptr;
                }
                else {
                    pointer_node = pointer_node->ptr_to_prev_node;
                    Node* connection_node = pointer_node->ptr_to_next_node; //�������� ����
                    pointer_node->ptr_to_next_node = connection_node->ptr_to_next_node;
                    connection_node->ptr_to_next_node->ptr_to_prev_node = connection_node->ptr_to_prev_node;
                    delete connection_node; //���������� ������
                    pointer_node = pointer_node->ptr_to_next_node; //�������� �� ��������� �������
                }

            }
            else {
                pointer_node = pointer_node->ptr_to_next_node; //�������� �� ��������� �������
            }
        }
    }

}

void print_list(List& list) { //����� �������� ������
    cout << endl << "������� ������:" << endl;
    Node* current_node = list.head_node;
    if (current_node != nullptr) { //���� ������ �� ������
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

int main() {
    setlocale(LC_ALL, "Russian"); //�����������
    system("chcp 1251");
    system("cls");

    int n, k, befor_add;
    char symbol;

    do {
        cout << "������� ���������� ��������� ";
        cin >> n; //���������� ��������� � ������
    } while (n < 1);
    cout << endl;

    List list; //������������� ������

    for (int i = 0; i < n; i++) {
        cout << "������� ������ ";
        cin >> symbol;
        if (i == 0) insrt_Item(list, symbol); //�������� ����� �������
        else insrt_Item(list, symbol, i - 1);
    }

    print_list(list); //������ ������� ������

    int num_del_el; //����� ��������, ������� ���� �������
    char symbol_key;

    cout << "������� ���� ��������, ������� �� ������ ������� ";
    cin >> symbol_key;

    pop_element(list, symbol_key, n); //������ �������
    cout << "��������� �������� ��������(-��) � �������� ������" << endl;

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
    cout << endl;

    for (int i = 0; i < k; i++) {
        cout << "������� ������ ";
        cin >> symbol;
        if (befor_add == 1 && i == 0) {
            insrt_Item(list, symbol, i, 2);
        }
        else insrt_Item(list, symbol, befor_add - 2 + i);
    }

    print_list(list); //������ ������� ������

    return 0;
}