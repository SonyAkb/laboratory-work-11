#include <iostream>
#include <fstream>
#include <string>
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

void insrt_Item(List& list, const int& data, const int& index = 0, int selector = 1); //добавляю новый элемент в конец списка   
void pop_element(List& list, char num_del_el, int n); //удаление элемента
void print_list(List& list); //вывод текущего списка
void del_all_list(List& list); //очищение списка
void writing_to_a_file(List& list, ofstream& file); //запись данных в файл
void recovery(List& list, ifstream& file); //восстановление

int main() {
    setlocale(LC_ALL, "Russian"); //локализация
    system("chcp 1251");
    system("cls");

    ifstream input("F11.txt"); //входной файловый поток
    ofstream output("F11.txt"); //выходной файловый поток

    int n, k, befor_add;
    char symbol, symbol_key;

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
        else insrt_Item(list, symbol, i - 1);
    }

    print_list(list); //вывожу текущий массив

    cout << "Введите КЛЮЧ элемента, который вы хотите удалить ";
    cin >> symbol_key;

    pop_element(list, symbol_key, n); //удаляю элемент
    cout << "Выполнено удаление элемента(-ов) с заданным ключом" << endl;

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
    cout << endl;

    for (int i = 0; i < k; i++) {
        cout << "Введите символ ";
        cin >> symbol;
        if (befor_add == 1 && i == 0) {
            insrt_Item(list, symbol, i, 2);
        }
        else insrt_Item(list, symbol, befor_add - 2 + i);
    }

    print_list(list); //вывожу текущий массив

    cout << "Запись данных в файл ..." << endl;
    writing_to_a_file(list, output);
    cout << "Завершено" << endl << endl;

    cout << "Очищение памяти ..." << endl;
    del_all_list(list);
    cout << "Завершено" << endl;
    print_list(list); //вывожу текущий массив

    cout << "Восстановление списка ..." << endl;
    cin.ignore();
    recovery(list, input);
    cout << "Завершено" << endl;

    print_list(list); //вывожу текущую очередь

    input.close(); //закрываю файл
    output.close();//закрываю файл

    return 0;
}

void insrt_Item(List& list, const int& data, const int& index, int selector) { //добавляю новый элемент в конец списка
    Node* new_node = new Node; //создаю новый динамический узел
    new_node->data = data; //присваиваю полю узла данные

    if (list.head_node == nullptr) { //если список пустой
        list.head_node = new_node; //новый узел - головной узел списка
        list.teil_node = new_node; //новый узел - хвостовой узел списка
    }
    else { //если список не пустой
        if (index == 0 && selector == 2) {
            new_node->ptr_to_next_node = list.head_node; //связываю новый узел с головным
            list.head_node = new_node; //новый головной узел
        }
        else {
            int counter = 0;
            Node* current_node = list.head_node;
            while (counter != index) { //иду ДО элемента, который надо удалять
                current_node = current_node->ptr_to_next_node;
                ++counter;
            }
            new_node->ptr_to_prev_node = current_node;
            if (current_node->ptr_to_next_node != nullptr) {
                new_node->ptr_to_next_node = current_node->ptr_to_next_node; //связываю узлы
                current_node->ptr_to_next_node->ptr_to_prev_node = new_node;
            }
            current_node->ptr_to_next_node = new_node;
            list.teil_node = new_node;
        }
    }
}

void pop_element(List& list, char num_del_el, int n) { //удаление элемента
    if (list.head_node != nullptr) { //если список пустой
        Node* pointer_node = list.head_node;
        while (pointer_node != nullptr) { //пока не дойду до конца
            if (pointer_node->data == num_del_el) { //если найден ключевой элемент
                if (pointer_node == list.head_node) { //если удалять головной элемент
                    Node* new_Head = list.head_node->ptr_to_next_node;
                    delete list.head_node; //удаляю текущий головной элемент
                    list.head_node = new_Head; //новая голова   
                    pointer_node = list.head_node; //текущий элемент остается головным
                }
                else if (pointer_node == list.teil_node) { //если удалять хвостовой элемент
                    Node* new_Teil = list.teil_node->ptr_to_prev_node;
                    new_Teil->ptr_to_next_node = nullptr;
                    delete list.teil_node; //удаляю текущий хвостовой элемент
                    list.teil_node = new_Teil; //новый хвост
                    pointer_node = nullptr;
                }
                else {
                    pointer_node = pointer_node->ptr_to_prev_node;
                    Node* connection_node = pointer_node->ptr_to_next_node; //связываю узлы
                    pointer_node->ptr_to_next_node = connection_node->ptr_to_next_node;
                    connection_node->ptr_to_next_node->ptr_to_prev_node = connection_node->ptr_to_prev_node;
                    delete connection_node; //освобождаю память
                    pointer_node = pointer_node->ptr_to_next_node; //перехожу на следующий элемент
                }
            }
            else {
                pointer_node = pointer_node->ptr_to_next_node; //перехожу на следующий элемент
            }
        }
    }
}

void print_list(List& list) { //вывод текущего списка
    cout << endl << "Текущий список:" << endl;
    Node* current_node = list.head_node;
    if (current_node != nullptr) { //если список не пустой
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

void del_all_list(List& list) {
    Node* ptr_node = list.head_node;
    if (ptr_node != nullptr) {
        while (ptr_node != nullptr) {
            Node* new_Head = list.head_node->ptr_to_next_node;
            delete list.head_node; //удаляю текущий головной элемент
            list.head_node = new_Head; //присваиваю головному элементу новый элемент
            ptr_node = list.head_node;
        }
    }
}

void writing_to_a_file(List& list, ofstream& file) { //запись данных в файл
    if (list.head_node != nullptr) {//если список не пустой
        Node* pointer_q = list.head_node; //указатель на первый элемент
        while (pointer_q != nullptr) { //пока не дойду до конца
            file << pointer_q->data << endl;
            pointer_q = pointer_q->ptr_to_next_node; //перехожу на следующий узел
        }
    }
}

void recovery(List& list, ifstream& file) { //восстановление
    string all_str;
    getline(file, all_str); //считываю строку
    insrt_Item(list, all_str[0]);
    int counter = 0;
    while (getline(file, all_str)) { //пока не пройду весь файл
        insrt_Item(list, all_str[0], counter); //добавляю
        counter++;
    }
}