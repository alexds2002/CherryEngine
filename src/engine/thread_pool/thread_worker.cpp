#include "thread_worker.h"
#include "thread_pool.h"

ThreadWorker::ThreadWorker(ThreadPool* _thread_pool) :
              m_thread_pool(_thread_pool)
{
}

void ThreadWorker::StartThread()
{
    if(m_thread_pool->Busy_Threads() >= m_thread_pool->Get_Number_Of_Threads())
    {
    }
}
