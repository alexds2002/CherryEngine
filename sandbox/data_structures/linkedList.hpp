#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>

// Alex Template Library
namespace atl
{

template <typename T>
struct Node final
{
    explicit Node() : data{0}, next{nullptr} { }
    explicit Node(T data_) : data{data_}, next{nullptr} { }

    T data;
    Node<T>* next;
};

template <typename T>
struct List final
{
    List() : head{nullptr} { }
    explicit List(T val) : head{new Node<T>(val)} { }
    ~List() { _free_list(); }

    void print_list() const noexcept
    {
        Node<T>* tmp = head;
        while(tmp)
        {
            std::cout << tmp->data << '\n';
            tmp = tmp->next;
        }
    }

    void push_front(T val)
    {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = head;
        head = newNode;
    }

    void push_back(T val)
    {
        if(!head) { head = new Node<T>(val); return; }
        Node<T>* tmp = head;
        while(tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = new Node<T>(val);
    }

    void pop_front()
    {
        if (!head) return; // Check if the list is empty
        Node<T>* tmp = head;
        head = head->next;
        delete tmp;
    }

    void pop_back()
    {
        if (!head) return; // Check if the list is empty
        if (!head->next) // If there's only one element
        {
            delete head;
            head = nullptr;
            return;
        }
        Node<T>* tmp = head;
        while(tmp->next->next)
        {
            tmp = tmp->next;
        }
        delete tmp->next;
        tmp->next = nullptr;
    }

    Node<T>* head;
private:
    void _free_list()
    {
        while(head)
        {
            Node<T>* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};

} // namespace atl

#endif // !LINKED_LIST_HPP
