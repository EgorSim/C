#include <iostream>
#include <string>

template <typename T>
class Node {
private:
    T data;
    Node* prev;
    Node* next;

public:
    Node(T data) {
        this->data = data;
        this->prev = this->next = nullptr;
    }

    template<typename U> friend class LinkedList;
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList() {
        head = tail = nullptr;
    }

    ~LinkedList() {
        while (head != nullptr) {
            pop_front();
        }
    }

    void push_front(T data) {
        Node<T>* ptr = new Node<T>(data);
        ptr->next = head;
        if (head != nullptr)
            head->prev = ptr;
        if (tail == nullptr)
            tail = ptr;
        head = ptr;
    }

    void push_back(T data) {
        Node<T>* ptr = new Node<T>(data);
        ptr->prev = tail;
        if (tail != nullptr)
            tail->next = ptr;
        if (head == nullptr)
            head = ptr;
        tail = ptr;
    }

    void pop_front() {
        if (head == nullptr) return;

        Node<T>* ptr = head->next;
        if (ptr != nullptr)
            ptr->prev = nullptr;
        else
            tail = nullptr;
        delete head;
        head = ptr;
    }

    void pop_back() {
        if (tail == nullptr) return;

        Node<T>* ptr = tail->prev;  
        if (ptr != nullptr)
            ptr->next = nullptr;
        else
            head = nullptr;
        delete tail;
        tail = ptr;
    }

    void print() {
        if (head == nullptr) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    LinkedList<int> intList;
    intList.push_back(1);
    intList.push_back(2);
    intList.push_front(0);

    std::cout << "Int List: ";
    intList.print();

    intList.pop_front();
    std::cout << "After pop_front: ";
    intList.print();

    intList.pop_back();
    std::cout << "After pop_back: ";
    intList.print();

    LinkedList<std::string> strList;
    strList.push_back("Hello");
    strList.push_back("World");
    strList.push_front("Start");

    std::cout << "String list: ";
    strList.print();

    strList.pop_back();
    std::cout << "After pop_back: ";
    strList.print();

    return 0;
}