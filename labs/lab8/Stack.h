#ifndef LAB8_STACK_H
#define LAB8_STACK_H

#include <iostream>

template<typename T>
class Stack {
private:
    int m_size; // размерность (capacity)
    int m_length = 0; // кол-во элементов
    T* m_stack = nullptr; // массив элементов
public:
    // конструктор
    explicit Stack(int size) : m_size(size) {
        if (m_size < 0)
            throw std::bad_alloc();
        m_stack = new T[size];
    }

    // деструктор
    ~Stack(){
        delete[] m_stack;
    }

    // вернуть кол-во элементов стека
    int size() {
        return m_length;
    }

    // проверить пустой ли стек
    bool empty() {
        return m_length == 0;
    }

    // добавить элемент в стек
    void push(const T& el) {
        if (m_length == m_size)
            throw std::overflow_error("Adding of new element in the stack is impossible");
        m_stack[m_length] = el;
        m_length++;
    }

    // извлечь элемент из стека
    void pop(int index) {
        if (this->empty())
            throw std::out_of_range("Extracting of element is impossible because stack is empty");
        for (int i = 0; i < m_length; i++) {
            if (i >= index) {
                m_stack[i] = m_stack[i + 1];
            }
        }
        m_length--;
    }

    // вернуть верхний элемент стека
    T& top() {
        if (this->empty())
            throw std::logic_error("Seeing of top element is impossible because stack is empty");
        return m_stack[m_length - 1];
    }

    // вывод стека в консоль
    void show() {
        std::cout << "Stack:" << std::endl;
        for (int i = m_length - 1; i >= 0; i--) {
            std::cout << m_stack[i] << " ";
        }
        std::cout << std::endl;
    }
};


#endif //LAB8_STACK_H
