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

void insrt_Item(List& list, const int& data, const int& index = 0) { //добавл€ю новый элемент в конец списка
    Node* new_node = new Node; //создаю новый динамический узел
    new_node->data = data; //присваиваю полю узла данные
    
    if (list.head_node == nullptr) {
        list.head_node = new_node;
        list.teil_node = new_node;
        cout << "Ќулевой" << endl;
        return;
    }
    cout << "Ќе нулевой" << endl;
    int counter = 0;

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
            delete list.head_node; //удал€ю текущий головной элемент
            list.head_node = new_Head; //присваиваю головному элементу новый элемент
        }
        else if (num_del_el == n) {
            cout << "n" << endl;
            Node* new_Teil = list.teil_node->ptr_to_prev_node;
            cout << new_Teil->data << endl;
            new_Teil->ptr_to_next_node = nullptr;
            delete list.teil_node; //удал€ю текущий хвостовой элемент
            list.teil_node = new_Teil; //присваиваю хвостовому элементу новый элемент
        }
        else {
            Node* pointer_node = list.head_node;
            for (int i = 0; i < num_del_el - 2; i++) { //иду ƒќ элемента, который надо удал€ть
                pointer_node = pointer_node->ptr_to_next_node;
            }
            cout << "Ёлемент " << pointer_node->data << endl;
            Node* connection_node = pointer_node->ptr_to_next_node; //св€зываю узлы
            pointer_node->ptr_to_next_node = connection_node->ptr_to_next_node;
            connection_node->ptr_to_next_node->ptr_to_prev_node = connection_node->ptr_to_prev_node;
            delete connection_node; //освобождаю пам€ть
        }
    }
}

void print_list(List& list) { //вывод текущего списка
    cout << "“екущий список:" << endl;
    Node* current_node = list.head_node;
    if (current_node != nullptr) {
        while (current_node != nullptr) { //пока не дойду до последнего элемента
            cout << current_node->data << ' '; //вывод данных текущего узла
            current_node = current_node->ptr_to_next_node; //переход к следующему узлу    
        }
    }
    else {
        cout << "—писок пустой!";
    }
    cout << endl << endl;
    delete current_node; //очищаю пам€ть
}

int main() {
    setlocale(LC_ALL, "Russian"); //локализаци€
    system("chcp 1251");
    system("cls");

    int n, k, befor_add;
    char symbol;

    do {
        cout << "¬ведите количество элементов ";
        cin >> n; //количество элементов в списке
    } while (n < 1);
    cout << endl;

    List list; //инициализирую список

    for (int i = 0; i < n; i++) {
        cout << "¬ведите символ ";
        cin >> symbol;
        if (i == 0) insrt_Item(list, symbol); //добавл€ю новый элемент
        else insrt_Item(list, symbol, i-1);
    }

    cout << endl;
    print_list(list); //вывожу текущий массив

    int num_del_el; //номер элемента, который надо удалить
    do {
        cout << "¬ведите номер элемента, который вы хотите удалить ";
        cin >> num_del_el; //Ќќћ≈– элемента
    } while (num_del_el<1 || num_del_el>n);
    cout << endl;

    pop_element(list, num_del_el, n); //удал€ю элемент
    print_list(list); //вывожу текущий массив

    return 0;
}