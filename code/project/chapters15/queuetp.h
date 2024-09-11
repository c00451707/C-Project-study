#ifndef QUEUETP_H_
#define QUEUETP_H_

template <class T>
class QueueTp
{
    private:
        enum {Q_SIZE = 10};
        // 内部类
        class Node
        {
            public:
                T item;
                Node * next;
                Node (const T & it) :item(it), next(0) {};
        };
        Node * front;
        Node * rear;
        int items;
        const int qsize;
        QueueTp(const QueueTp & q) : qsize(0) {}
        QueueTp & operator=(const QueueTp & q)
        {
            return *this;
        }
    public:
        QueueTp(int qs = Q_SIZE);
        ~QueueTp();
        bool isempty() const
        {
            return items == 0;
        }
        bool isfull() const
        {
            return items == qsize;
        }
        int queuecount() const
        {
            return items;
        }

        bool enqueue(const T &item);
        bool dequeue(T &item);
};

/*
 *  模板方法只能放在头文件中定义
 */
template <class T>
QueueTp<T>::QueueTp(int qs) : qsize(qs)
{
    front = rear = 0;
    items = 0;
}

template <class T>
QueueTp<T>::~QueueTp()
{
    Node * temp;
    while(front != 0)
    {
        temp = front;
        front = front -> next;
        delete temp;
    }
}

template <class T>
bool QueueTp<T>::enqueue(const T & item)
{
    if (isfull())
    {
        return false;
    }
    Node * add = new Node(item);
    items++;
    if (front == 0)
    {
        front = add;
    }
    else
    {
        rear -> next = add;
    }
    rear = add;
    return true;
}

template <class T>
bool QueueTp<T>::dequeue(T & item)
{
    if (front == 0)
    {
        return false;
    }
    item = front -> item;
    items--;
    Node * temp = front;
    front = front -> next;
    delete temp;
    if (items == 0)
        rear = 0;
    return true;
}

#endif