#include <iostream>
using namespace std;

struct Node {
    char data; //данные
    Node* ptr_to_next_node = nullptr; //указатель на следующий элемент
};

struct List {
    Node* head_node = nullptr;
    Node* teil_node = nullptr;
};

void pushBack(List& list, const int& data) { //добавляю новый элемент в конец списка
    Node* new_node = new Node; //создаю новый динамический узел
    new_node->data = data; //присваиваю полю узла данные
    if (list.head_node == nullptr) { //если список пустой
        list.head_node = new_node; //новый узел - головной узел списка
        list.teil_node = new_node; //новый узел - хвостовой узел списка
    }
    else { // если список не путой
        list.teil_node->ptr_to_next_node = new_node; //связываю новый узел с хвостовым
        list.teil_node = new_node; //меняю хвостовой узел на новый
    }
}

void pop_element(List& list, int num_del_el) { //удаление элемента
    if (list.head_node != nullptr) { //если список пустой
        if (num_del_el == 1) { //если надо удалить первый элемент
            Node* new_Head = list.head_node->ptr_to_next_node;
            delete list.head_node; //удаляю текущий головной элемент
            list.head_node = new_Head; //присваиваю головному элементу новый элемент
        }
        else { //если удалять НЕ первый элемент
            Node* pointer_node = list.head_node;
            for (int i = 0; i < num_del_el - 2; i++) { //иду ДО элемента, который надо удалять
                pointer_node = pointer_node->ptr_to_next_node;
            }
            Node* connection_node = pointer_node->ptr_to_next_node; //связываю узлы
            pointer_node->ptr_to_next_node = connection_node->ptr_to_next_node; //связываю узлы
            delete connection_node; //освобождаю память
        }
    }
}

void add_elements(List& list, int befor_number) { //добавляю новый элемент
    char element;
    cout << "Введите новый элемент ";
    cin >> element;

    Node* new_node = new Node; //создаю новый узел
    new_node->data = element; //присваиваю значение данных

    if (befor_number == 1) { //если ввовдить новый элемент перед первым элементом
        //Node* new_head = new Node;
        //new_head->data = element; //присваиваю значение данных
        new_node->ptr_to_next_node = list.head_node;
        list.head_node = new_node;
    }
    else {
        Node* pointer_node = list.head_node;
        for (int i = 0; i < befor_number - 2; i++) { //иду ДО элемента перед которым над добавить новый
            pointer_node = pointer_node->ptr_to_next_node; //элемент перед необходимым элементом
        }
        //Node* new_node = new Node; //создаю новый узел
        //new_node->data = element; //присваиваю значение данных
        new_node->ptr_to_next_node = pointer_node->ptr_to_next_node; //связываю новый узел со следующим
        pointer_node->ptr_to_next_node = new_node; //связываю новый узел с предыдущим
        
    }
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
        cin >> n;
    } while (n < 1);
    cout << endl;

    List list; //инициализирую список

    for (int i = 0; i < n; i++) {
        cout << "Введите символ ";
        cin >> symbol;
        pushBack(list, symbol);
    }
    cout << endl;

    print_list(list); //вывожу текущий массив

    int num_del_el; //номер элемента, который надо удалить
    do {
        cout << "Введите номер элемента, который вы хотите удалить ";
        cin >> num_del_el; //НОМЕР элемента
    } while (num_del_el<1 || num_del_el>n);
    cout << endl;
    pop_element(list, num_del_el); //удаляю элемент
    --n; //изменяю длину списка
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
    n += k; //изменяю длину списка
    cout << endl;

    for (int i = 0; i < k; i++) { //добавляю новые элементы
        add_elements(list, befor_add);
    }
    cout << endl;
    print_list(list); //вывожу текущий массив
    cout << n << endl;
    cout << "Очищение памяти ..." << endl;
    for (int i = n; i >= 0; i--) { //добавляю новые элементы
        pop_element(list, i);
    }

    cout << "Завершено" << endl;
    cout << endl;
    print_list(list); //вывожу текущий массив

    return 0;
}