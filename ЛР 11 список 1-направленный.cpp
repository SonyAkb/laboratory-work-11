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

void pushBack(List& list, const int& data) { //добавл€ю новый элемент в конец списка
    Node* new_node = new Node; //создаю новый динамический узел
    new_node->data = data; //присваиваю полю узла данные

    if (list.head_node == nullptr) { //если список пустой
        list.head_node = new_node; //новый узел - головной узел списка
        list.teil_node = new_node; //новый узел - хвостовой узел списка
    }
    else { // если список не путой
        list.teil_node->ptr_to_next_node = new_node; //св€зываю новый узел с хвостовым
        list.teil_node = new_node; //мен€ю хвостовой узел на новый
    }
}

void pop_element(List& list, int n) { //удаление элемента
    if (list.head_node == nullptr) { //если список пустой
        return;
    }

    int num_del_el;

    do {
        cout << "¬ведите номер элемента, который вы хотите удалить ";
        cin >> num_del_el; //Ќќћ≈– элемента
    } while (num_del_el<1 || num_del_el>n);

    if (num_del_el == 1) { //если надо удалить первый элемент
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
    cout << "¬ведите новый элемент ";
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
        pointer_node = pointer_node->ptr_to_next_node; //элемент перед необходимым элементом
    }
    cout << pointer_node->data << endl;

    Node* new_node = new Node; //создаю новый узел
    new_node->data = element;
    new_node->ptr_to_next_node = pointer_node->ptr_to_next_node;
    pointer_node->ptr_to_next_node = new_node;   
}

void print_list(List& list) { //вывод текущего списка
    Node* current_node = list.head_node;
    while (current_node != nullptr) {
        cout << current_node->data << ' '; //вывод данных текущего узла
        current_node = current_node->ptr_to_next_node; //переход к следующему узлу    
    }
    cout << endl;
    delete current_node;

}

int main() {
    setlocale(LC_ALL, "Russian"); //локализаци€
    system("chcp 1251");
    system("cls");

    int n, k, befor_add;
    char symbol;

    do {
        cout << "¬ведите количество элементов ";
        cin >> n;
    } while (n < 1);

    List list; //инициализирую список

    for (int i = 0; i < n; i++) {
        cout << "¬ведите символ ";
        cin >> symbol;
        pushBack(list, symbol);
    }

    print_list(list); //вывожу текущий массив

    pop_element(list, n); //удал€ю элемент
    --n; //измен€ю длину списка
    print_list(list); //вывожу текущий массив

    do {
        cout << "¬ведите номер элемента, перед которым необходимо добавить новые элементы ";
        cin >> befor_add; //Ќќћ≈– элемента
    } while (befor_add < 1 || befor_add > n);
    do {
        cout << "¬ведите количество элементов, которые необходимо добавить ";
        cin >> k; //количество элементов, которые надо добавить
    } while (k<1);

    for (int i = 0; i < k; i++) { //добавл€ю новые элементы
        add_elements(list, befor_add);
    }

    print_list(list); //вывожу текущий массив

    return 0;
}