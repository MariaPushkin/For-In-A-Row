#ifndef MYLIST_H
#define MYLIST_H


template <typename T>
struct node // структура, выполняющая роль узла списка
{
    T *data;
    //AuthCode auth;
    //int number;
    node* next;
};

template <typename T>
class list // класс список
{
private:
    node<T> *top; // указатель на первый элемент списка
    int length; // переменная для длины списка
public:
    list();
    list(const list<T> &); // конструктор копирования
    ~list(); // деструктор

    node<T> *getTop() const; // селекторы
    int getLength();

    bool isEmpty(); // проверка на пустоту
    void push(T *); // добавление элемента
    void clear();
    //void Add(const AuthCode *);
    bool pop(const int n); // удаление элемента

    T &operator [](int a);

private:
    //Node* top;
};

template <typename T>
list<T>::list()
{
    //head=new Node;
    top=NULL; // присваивание первому элементу списка NULL
    length = -1;
}

template <typename T>
list<T>::list (const list<T> & newL) //конструктор копирования
{
    top = new node<T>;
    node<T> *currOld;
    node<T> *currNew;
    node<T> *currNextNew;

    top->data = newL.top->data;
    currOld = newL.top;
    currNew = top;

    while(currOld->next != NULL)
    {
        currOld = currOld->next;
        currNextNew = new node<T>;
        currNew->next = currNextNew;
        currNextNew->data = currOld->data;
        currNew=currNextNew;
    }
    length = newL.length;
}

template <typename T>
list<T>::~list()
{

}

template <typename T>
bool list<T>::isEmpty() // проверка на пустоту
{
    if(length == -1)
        return true;
    else
        return false;
}

template <typename T>
node<T> *list<T>::getTop() const // получение первого элемента списка
{
    return top;
}

template <typename T>
int list<T>::getLength() // получение длины списка
{
    return length;
}

template <typename T>
void list<T>::push(T *newData) // добавление записи в список
{
    if(isEmpty())
    {
        node<T> *newnode = new node<T>; // выделение памяти под новую запись
        newnode->data = newData; // добавление содержимого в узел списка
        top = newnode; // присваивание значения нового первому элементу списка
        newnode->next = NULL; // инициализация следующего элемента NULL
    }
    else
    {
        node<T> *newnode = new node<T>;
        node<T> *temp;
        newnode->data = newData;
        temp = top;
        while ((temp->next) != NULL) // пока не встетится следующий элемент NULL
           temp = temp->next; // переход к следующему узлу списка
        temp->next = newnode;
        newnode->next = NULL;
    }
    length++;
}


template <typename T>
bool list<T>::pop(int n) // удаление элемента
{
    node<T> *temp=top;
    node<T> *k;
    if ((top!=NULL) && (n>=0) && (n<=length)) // если список не пустой и элемент выбран верно
    {
        for (int i=0;i<n && temp!= NULL;i++) // цикл, идущий по списку
           temp=temp->next;
        if (temp!= NULL) // если встретили такой элемент
        {
            if (temp==top) // если элемент первый
            {
                top = top->next; // присваиваем значение следующего элемента первому
                delete(temp); // освобождение памяти
                temp = top; // присваивание переменной temp значения первого элемента
                length--;
                return true;
            }
            else
            {
                k = top; // обращение к началу списка
                while (k->next != temp) // проход по списку
                k = k->next; // переход к следующему элементу
                k->next = temp->next; //присваивание элементу k->next значение узла temp->next
                delete(temp); //освобождение памяти
                temp=k;  //присваивание temp значения k
                length--;
                return true;
            }
        }
    }
    else
        return false;
}

template <typename T>
void list<T>::clear()
{
    node<T> *temp = top;
    node<T> *nextt = temp->next;
    while (nextt != NULL)//пока есть что удалять - удаляем
    {
    temp = nextt;
    nextt = nextt->next;
    delete temp;
    }
    top = new node<T>;
    top = NULL;
    length = 0;
}


template <typename T>
T &list<T>::operator [](int a)
{
        node<T> *curr = top;
        for(int i=0;i!=a;i++,curr = curr->next);  //находим элемент под номером a
        return *(curr->data);
}

#endif // MYLIST_H
