#include <stdexcept>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
    };

    Node* topNode;
    size_t stackSize;

public:
    Stack() : topNode(nullptr), stackSize(0) {}
    ~Stack() { clear(); }

    void push(const T& value) {
        topNode = new Node(value, topNode);
        stackSize++;
    }

    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        Node* temp = topNode;
        T value = temp->data;
        topNode = topNode->next;
        delete temp;
        stackSize--;
        return value;
    }

    const T& top() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return topNode->data;
    }

    bool isEmpty() const { return topNode == nullptr; }

    size_t size() const { return stackSize; }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};
