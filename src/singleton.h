#ifndef __COMMON_SINGLETON_H__
#define __COMMON_SINGLETON_H__

#include <pthread.h>

#define DISALLOW_COPY_AND_ASSIGN(TypeName)	\
	TypeName(const TypeName&);				\
	void operator=(const TypeName&)

class NonCopyAble
{
protected:
    NonCopyAble() {}
    virtual ~NonCopyAble() {}
private:
    NonCopyAble &operator=(const NonCopyAble &);
    NonCopyAble(const NonCopyAble &);
};


template<typename T>
class Singleton
{
public:
    static T &Instance() {
        if(m_pInstance == NULL) {
            pthread_mutex_lock(&m_mutexCreate);
            if(m_pInstance == NULL) {
                m_pInstance = new T;
            }
            pthread_mutex_unlock(&m_mutexCreate);
        }
        return *m_pInstance;
    }

    static T &GetInstance() {
        return Instance();
    }

    ~Singleton() {}

private:
    Singleton() {}
    DISALLOW_COPY_AND_ASSIGN(Singleton);

private:
    static T               *m_pInstance;
    static pthread_mutex_t  m_mutexCreate;
};

template<typename T>
T *Singleton<T>::m_pInstance = NULL;

template<typename T>
pthread_mutex_t Singleton<T>::m_mutexCreate = PTHREAD_MUTEX_INITIALIZER;


#endif

