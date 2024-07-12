#pragma once

class ThreadPool;

class ThreadWorker
{
public:
    ThreadWorker(ThreadPool* _thread_pool);
    void StartThread();
private:
    ThreadPool* m_thread_pool;
};
