#ifndef LAB5_VECTOR_BOOL_H
#define LAB5_VECTOR_BOOL_H

#include "Vector.h"

// специализация шаблона для vector из булевых значений
template<>
class Vector<bool> {
private:
    char* m_data; // массив для хранения булевых значений
    int m_size; // кол-во элементов

private:
    // структура для работы с одним битом в байте
    struct BitReference {
    private:
        char* m_num; // указатель на байт
        int m_idx; // индекс бита
    public:
        // конструктор
        BitReference(char* num, int idx) : m_num(num), m_idx(idx) {}

        // оператор присваивания по биту
        BitReference& operator=(bool val) {
            if (val) {
                *m_num |= (1 << m_idx);
            } else {
                *m_num &= ~(1 << m_idx);
            }
            return *this;
        }

        // оператор присваивания типа bool
        operator bool() const {
            return (*m_num & (1 << m_idx)) != 0; // true - соответствующий бит установлен в байте, false - его нет
        }
    };
public:
    // конструктор
    Vector() {
        m_data = nullptr;
        m_size = 0;
    }

    // деструктор
    ~Vector() {
        delete[] m_data;
    }

    // функция добавления значения в конец
    void push_back(bool value) {
        if (m_size % 8 == 0) {
            char* new_data = new char[m_size / 8 + 1];
            for (int i = 0; i < m_size / 8; i++) {
                new_data[i] = m_data[i];
            }
            delete[] m_data;
            m_data = new_data;
        }
        if (value) {
            m_data[m_size / 8] |= 1 << (m_size % 8);
        } else {
            m_data[m_size / 8] &= ~(1 << (m_size % 8));
        }
        m_size++;
    }

    // оператор получения и изменения значения по индексу
    BitReference operator[](int idx) const {
        return {m_data + idx / 8, idx % 8};
    }

    // метод получения кол-ва значений
    [[nodiscard]] int getSize() const {
        return m_size;
    }

    // метод вставки элемента в массив
    void insert(int index, bool value) {
        if (index == m_size) {
            push_back(value);
        } else {
            push_back(operator[](m_size - 1));
            for (int i = m_size - 2; i > index; i--) {
                operator[](i) = operator[](i - 1);
            }
            operator[](index) = value;
        }
    }

    // метод вырезки значения из массива
    void erase(int index) {
        for (int i = index; i < m_size - 1; i++)
            operator[](i) = operator[](i + 1);
        m_size--;
        if (m_size % 8 == 0) {
            char* new_data = new char[m_size / 8];
            for (int i = 0; i < m_size / 8; i++)
                new_data[i] = m_data[i];
            delete[] m_data;
            m_data = new_data;
        }
    }
};

#endif
