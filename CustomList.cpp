#include "CustomList.h"

template<typename T>
CustomNode<T>::CustomNode(const T& newData)
    : data(newData)
{
}

template<typename T>
CustomNode<T>::~CustomNode()
{
    prior = nullptr;
    next = nullptr;
}

template<typename T>
CustomList<T>::~CustomList()
{
    popAll();
}

template<typename T>
CustomNode<T>* CustomList<T>::push(const T& value)
{
    CustomNode<T>* node = new CustomNode<T>(value);
    if (tail) {
        node->prior = tail;
        tail->next = node;
    }
    tail = node;
    return node;
}

template<typename T>
CustomNode<T>* CustomList<T>::insert(CustomNode<T>* node, const T& value)
{
    if (!node) {
        return push(value);
    }

    CustomNode<T>* newNode = new CustomNode<T>(value);
    if (node->prior) {
        auto prior = node->prior;
        node->prior = newNode;
        prior->next = newNode;

        newNode->prior = prior;
    }
    newNode->next = node;

    return newNode;
}

template<typename T>
CustomNode<T>* CustomList<T>::find(const T& value)
{
    auto node = tail;
    while (node) {
        if (node->data == value){
            return node;
        }
        node = node->prior;
    }

    return nullptr;
}

template<typename T>
void CustomList<T>::remove(CustomNode<T>* node)
{
    if (!node) {
        return;
    }
    if (node->prior) {
        auto prior = node->prior;
        if (node->next) {
            prior->next = node->next;
            node->next->prior = prior;
        }
        else {
            prior->next = nullptr;
        }
        if (node == tail) {
            tail = prior;
        }
    }
    else if (node->next) {
        auto next = node->next;
        next->prior = nullptr;
    }

    delete node;
}

template<typename T>
void CustomList<T>::popAll()
{
    while (tail) {
        auto prior = tail->prior;
        delete tail;
        tail = prior;
    }
}