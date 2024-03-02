#include <iostream>
using namespace std;

struct Node {
    char data; //данные
    Node* ptr_to_prev_node = nullptr; //указатель на предыдущий элемент
    Node* ptr_to_next_node = nullptr; //указатель на следующий элемент
};

struct List {
    Node* head_node = nullptr;
    Node* teil_node = nullptr;
};

void insrt_Item(List& list, const int& data, const int& index = 0, int selector = 1) { //добавляю новый элемент в конец списка
    Node* new_node = new Node; //создаю новый динамический узел
    new_node->data = data; //присваиваю полю узла данные
    
    if (list.head_node == nullptr) {
        list.head_node = new_node;
        list.teil_node = new_node;
        //cout << "Нулевой" << endl;
        return;
    }
    //cout << "Не нулевой" << endl;
    int counter = 0;

    if (index == 0 && selector == 2) {
        //cout << "Протокол 2" << endl;
        //cout << new_node->data << '|' << list.head_node->data <<endl;

        new_node->ptr_to_next_node = list.head_node;
        list.head_node = new_node;
        
        //cout << list.head_node->data << " | " << list.head_node->ptr_to_next_node->data << endl;
        //cout << list.head_node->data << ' ' << list.head_node->ptr_to_next_node->data << ' ' << list.head_node->ptr_to_next_node->ptr_to_next_node->data << ' ' << list.head_node->ptr_to_next_node->ptr_to_next_node->ptr_to_next_node->data;
        //cout << endl;
        return;
    }

    Node* current_node = list.head_node;
    while (counter != index) {
        current_node = current_node->ptr_to_next_node;
        ++counter;
    }

    new_node->ptr_to_prev_node = current_node;
    if (current_node->ptr_to_next_node != nullptr) {
        new_node->ptr_to_next_node = current_node->ptr_to_next_node;
        current_node->ptr_to_next_node->ptr_to_prev_node = new_node;
    }
    current_node->ptr_to_next_node = new_node;
    list.teil_node = new_node;
}

void pop_element(List& list, int num_del_el, int n) { //удаление элемента
    if (list.head_node != nullptr) { //если список пустой
        if (num_del_el == 1) { //если надо удалить первый элемент
            Node* new_Head = list.head_node->ptr_to_next_node;
            delete list.head_node; //удаляю текущий головной элемент
            list.head_node = new_Head; //присваиваю головному элементу новый элемент
        }
        else if (num_del_el == n) {
            Node* new_Teil = list.teil_node->ptr_to_prev_node;
            new_Teil->ptr_to_next_node = nullptr;
            delete list.teil_node; //удаляю текущий хвостовой элемент
            list.teil_node = new_Teil; //присваиваю хвостовому элементу новый элемент
        }
        else {
            Node* pointer_node = list.head_node;
            for (int i = 0; i < num_del_el - 2; i++) { //иду ДО элемента, который надо удалять
                pointer_node = pointer_node->ptr_to_next_node;
            }
            Node* connection_node = pointer_node->ptr_to_next_node; //связываю узлы
            pointer_node->ptr_to_next_node = connection_node->ptr_to_next_node;
            connection_node->ptr_to_next_node->ptr_to_prev_node = connection_node->ptr_to_prev_node;
            delete connection_node; //освобождаю память
        }
    }
    //n - всего элементов в списке
    //num_del_el - индекс элемента который надо удалить
}

void print_list(List& list) { //вывод текущего списка
    cout << "Текущий список:" << endl;
    Node* current_node = list.head_node;
    if (current_node != nullptr) {
        while (current_node != nullptr) { //пока не дойду до последнего элемента
            cout << current_node->data << ' '; //вывод данных текущего узла
            current_node = current_node->ptr_to_next_node; //переход к следующему узлу    
        }
    }
    else {
        cout << "Список пустой!";
    }
    cout << endl << endl;
    delete current_node; //очищаю память
}

int main() {
    setlocale(LC_ALL, "Russian"); //локализация
    system("chcp 1251");
    system("cls");

    int n, k, befor_add;
    char symbol;

    do {
        cout << "Введите количество элементов ";
        cin >> n; //количество элементов в списке
    } while (n < 1);
    cout << endl;

    List list; //инициализирую список

    for (int i = 0; i < n; i++) {
        cout << "Введите символ ";
        cin >> symbol;
        if (i == 0) insrt_Item(list, symbol); //добавляю новый элемент
        else insrt_Item(list, symbol, i-1);
    }

    cout << endl;
    print_list(list); //вывожу текущий массив

    int num_del_el; //номер элемента, который надо удалить
    do {
        cout << "Введите номер элемента, который вы хотите удалить ";
        cin >> num_del_el; //НОМЕР элемента
    } while (num_del_el<1 || num_del_el>n);
    cout << endl;

    pop_element(list, num_del_el, n); //удаляю элемент
    --n;
    print_list(list); //вывожу текущий массив

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

    for (int i = 0; i < k; i++) {
        cout << "Введите символ ";
        cin >> symbol;
        if (befor_add == 1 && i == 0 ) {
            insrt_Item(list, symbol, i, 2);
        }
        else insrt_Item(list, symbol, befor_add - 2 + i); 
    }

    print_list(list); //вывожу текущий массив

    return 0;
}