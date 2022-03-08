#pragma once
struct StackNode {
    void* data = nullptr;
    StackNode* next = nullptr;
    int size;

    StackNode(int valueSize) {
        size = valueSize;
        next = nullptr;
    }
};

class CustomStack
{
public:
    CustomStack()
    {
        top = nullptr;
    }
    ~CustomStack()
    {
        auto p = top;
        while (p) {
            auto a = p->next;
            delete p;
            p = nullptr;
            if (a) {
                p = a;
            }
        }
    }

    template<typename T>
    void push(T value)
    {
        int size = sizeof(value);
        StackNode* temp = new StackNode(size);
        temp->data = new T(value);

        if (top) {
            auto p = top;
            while (p) {
                if (p->next) {
                    p = p->next;
                }
                else {
                    break;
                }
            }
            p->next = temp;
        }
        else {
            top = temp;
        }
    }

    template<typename T>
    void pop(T& value)
    {
        if (top == nullptr) {
            return;
        }
        auto temp = top->next;
        T* p = (T*)top->data;
        memcpy(&value, p, top->size);
        delete top->data;
        delete top;
        top = temp;
    }
private:
    StackNode* top;
};

