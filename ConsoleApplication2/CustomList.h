#pragma once

#include <iostream>

template<typename T>
struct CustomNode
{
public:
    CustomNode* prior = nullptr;
    CustomNode* next = nullptr;
    T data;

    CustomNode() = default;
    CustomNode(const T& newData);
    ~CustomNode();
};

template<typename T>
class CustomList
{
public:
    CustomList() = default;
    CustomList(const CustomList& list) = default;
    ~CustomList();

    CustomNode<T>* push(const T& value);
    CustomNode<T>* insert(CustomNode<T>* node, const T& value);
    CustomNode<T>* find(const T& value);

    void remove(CustomNode<T>* node);
    void popAll();

private:
    CustomNode<T>* tail;
};

