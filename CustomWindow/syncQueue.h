/*
����:  ��ͬ�����첽���������ͬ�����У��̳߳��첽����
����:  C++11��׼
Ҫ��:  ������ʹ��list

20170715
vector,liast,deque��ʹ������
1 �������Ҫ��Ч���漴��ȡ�������ں������ɾ����Ч�ʣ�ʹ��vector
2 �������Ҫ�����Ĳ����ɾ�������������漴��ȡ����Ӧʹ��list
3 �������Ҫ�漴��ȡ�����ҹ����������ݵĲ����ɾ������Ӧʹ��deque
*/

#include <mutex>
#include <list>
#include <thread>
#include <condition_variable>
#include <iostream>

using namespace std;

template<class T>
class SyncQueue
{
public:
    SyncQueue(int size) : m_maxSize(size)
    {

    }

    void Put(const T& x)
    {
        //д����
        //std::lock_quard<std::mutex> locker(m_mutex);

        //д����
        //std::unique_lock<std::mutex> locker(m_mutex);

        //д����
        //while (IsFull())
        //{
        //    cout << "���������ˣ���Ҫ�ȴ�..." << endl;
        //    m_notFull.wait(m_mutex);
        //}

        //д����
        //m_notFull.wait(locker, [this] void (){return m_needStop || NotFull(); });

        //if (m_needStop)
        //{
        //    return;
        //}

        //m_queue.push_back(x);
        //m_notEmpty.notify_one();
        Add(x);
    }

    void Put(T&& x)
    {
        //Add(std::forward(x));
        Add(x);
    }

    void Take(std::list<T>& list)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_notEmpty.wait(locker, [this]{return m_needStop || NotEmpty(); });

        if (m_needStop)
        {
            return;
        }

        list = std::move(m_queue);
        m_notFull.notify_one();
    }

    void Take(T& x)
    {
        std::lock_guard<std::mutex> locker(m_mutex);

        m_notEmpty.wait(locker, [this]{return m_needStop || NotEmpty(); });

        //while (IsEmpty())
        //{
        //    cout << "���������ˣ���Ҫ�ȴ�..." << endl;
        //    m_notEmpty.wait(m_mutex);
        //}
        if (m_needStop)
        {
            return;
        }

        x = m_queue.front();
        m_queue.pop_front();
        m_notFull.notify_one();
    }

    void Stop()
    {
        {
            std::lock_guard<std::mutex> locker(m_mutex);

            m_needStop = true;
        }

        m_notFull.notify_all();
        m_notEmpty.notify_all();
    }

    bool Empty()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.empty();
    }

    bool Full()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size() == m_maxSize;
    }

    size_t Size()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size();
    }

private:
    bool NotFull() const
    {
        bool full = m_queue.size() >= m_maxSize;

        if (full)
        {
            cout << "���������ˣ���Ҫ�ȴ�..." << endl;
        }

        return !full;
    }

    bool NotEmpty() const
    {
        bool empty = m_queue.empty();

        if (empty)
        {
            cout << "���������ˣ���Ҫ�ȴ�...���첽����߳�ID��" << std::this_thread::get_id() << endl;
        }

        return !empty;
    }

    template<typename F>
    void Add(F&& x)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_notFull.wait(locker, [this]{return m_needStop || NotFull(); });

        if (m_needStop)
        {
            return;
        }

        m_queue.emplace_back(std::forward<F>(x));
        m_notEmpty.notify_one();
    }

private:
    std::list<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_notEmpty;
    std::condition_variable m_notFull;
    int m_maxSize;
    bool m_needStop;
};
