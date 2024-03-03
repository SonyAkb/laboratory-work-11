#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node {
    char data; //данные
    Node* ptr_to_next_node = nullptr; //указатель на следующий элемент
};

struct List {
    Node* head_node = nullptr;
    Node* teil_node = nullptr;
};

void pushBack(List& list, const int& data); //добавляю новый элемент в конец списка
void add_elements(List& list, int befor_number); //добавляю новый элемент
void print_list(List& list); //вывод текущего списка
void pop_element(List& list, char num_del_el); //удаление элемента
void del_all_list(List& list); //освобождение памяти
void writing_to_a_file(List& list, ofstream& file); //запись данных в файл
void recovery(List& list, ifstream& file); //восстановление
    
int main() {
    setlocale(LC_ALL, "Russian"); //локализация
    system("chcp 1251");
    system("cls");

    ifstream input("F11.txt"); //входной файловый поток
    ofstream output("F11.txt"); //выходной файловый поток

    int n, k, befor_add;
    char symbol_key;

    do {
        cout << "Введите количество элементов ";
        cin >> n;
    } while (n < 1);
    cout << endl;

    List list; //инициализирую список

    for (int i = 0; i < n; i++) {
        cout << "Введите символ ";
        cin >> symbol_key;
        pushBack(list, symbol_key);
    }

    print_list(list); //вывожу текущий массив

    cout << "Введите КЛЮЧ элемента, который вы хотите удалить ";
    cin >> symbol_key;

    pop_element(list, symbol_key); //удаляю элемент
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
        add_elements(list, befor_add + i);
    }
    print_list(list); //вывожу текущий массив

    cout << endl << "Запись данных в файл ..." << endl;
    writing_to_a_file(list, output);
    cout << "Завершено" << endl;

    print_list(list); //вывожу текущий массив
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

void add_elements(List& list, int befor_number) { //добавляю новый элемент
    char element;
    cout << "Введите новый элемент ";
    cin >> element;

    Node* new_node = new Node; //создаю новый узел
    new_node->data = element; //присваиваю значение данных

    if (befor_number == 1) { //если ввовдить новый элемент перед первым элементом
        new_node->ptr_to_next_node = list.head_node;
        list.head_node = new_node;
    }
    else {
        Node* pointer_node = list.head_node;
        for (int i = 0; i < befor_number - 2; i++) { //иду ДО элемента перед которым над добавить новый
            pointer_node = pointer_node->ptr_to_next_node; //элемент перед необходимым элементом
        }
        new_node->ptr_to_next_node = pointer_node->ptr_to_next_node; //связываю новый узел со следующим
        pointer_node->ptr_to_next_node = new_node; //связываю новый узел с предыдущим

    }
}

void print_list(List& list) { //вывод текущего списка
    cout << endl << "Текущий список:" << endl;
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

void pop_element(List& list, char num_del_el) { //удаление элемента
    if (list.head_node != nullptr) { //если список НЕ пустой
        Node* pointer_node = list.head_node;
        while (pointer_node != nullptr) { //пока не дойду до конца
            if (pointer_node->data == num_del_el) {
                if (pointer_node == list.head_node) { //если надо удалить первый элемент
                    Node* new_Head = list.head_node->ptr_to_next_node;
                    delete list.head_node; //удаляю текущий головной элемент
                    list.head_node = new_Head; //присваиваю головному элементу новый элемент
                    pointer_node = list.head_node;
                }
                else { //если удалять НЕ первый элемент
                    Node* before_deletion = list.head_node;
                    while (before_deletion->ptr_to_next_node != pointer_node) {
                        before_deletion = before_deletion->ptr_to_next_node;
                    }
                    before_deletion->ptr_to_next_node = pointer_node->ptr_to_next_node; //связываю узлы
                    pointer_node = before_deletion;
                }
            }
            else {
                pointer_node = pointer_node->ptr_to_next_node; //перехожу на следующий элемент
            }
        }
    }
}

void del_all_list(List& list) { //освобожденеи памяти
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
    Node* new_node = new Node; //создаю новый динамический узел
    new_node->data = all_str[0]; //присваиваю полю узла данные
    list.head_node = new_node; //новый узел - головной узел списка
    list.teil_node = new_node; //новый узел - хвостовой узел списка
    while (getline(file, all_str)) { //пока не пройду весь файл
        pushBack(list, all_str[0]); //добавляю
    }
}