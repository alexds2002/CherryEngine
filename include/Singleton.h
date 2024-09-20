#pragma once

/* CRTP */
template <typename T>
class Singleton
{
public:
    static T* GetInstance()
    {
        if(!m_instance) m_instance = new T;
        return m_instance;
    }
    static T& GetRef()
    {
        if(!m_instance) m_instance = new T;
        return *m_instance;
    }
    /*
     *  Destroys the singleton class instance.
     *  Be aware that all references to the single class instance will be
     *  invalid after this method has been executed!
    */
    static void DestroyInstance()
    {
        delete m_instance;
        m_instance = nullptr;
    }

    /*
       Prevent the class from being copied or moved.
     */
    Singleton(Singleton&& source) = delete;
    Singleton(const Singleton& source) = delete;
    Singleton& operator=(Singleton&& source) = delete;
    const Singleton& operator=(const Singleton& source) = delete;
protected:
    /*
       Shield the constructor and destructor to prevent outside sources
       from creating or destroying a CSingleton instance.
     */
    Singleton() = default;
    ~Singleton()
    {
        delete m_instance;
        m_instance = nullptr;
    }
private:
    static T* m_instance;
};

/* static class member initialisation */
template <typename T> T* Singleton<T>::m_instance = nullptr;
