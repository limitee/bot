#pragma once
#include <list>

template<typename T>  
class BlockingQueue  
{  
public:  
    BlockingQueue():_queue()  
    {
		g_hMutex = CreateMutex(NULL,FALSE,NULL);
    }  
  
    void Put(const T& task)  
    {  
        WaitForSingleObject(g_hMutex ,INFINITE);
        _queue.push_back (task);  
        ReleaseMutex(g_hMutex); 
    }  
  
    T Take ()  
    {  
        DWORD dw = WaitForSingleObject(g_hMutex ,0);
		if (WAIT_OBJECT_0 != dw)
		{
			ReleaseMutex(g_hMutex);
			return T();
		}
		if (_queue.empty())
		{
			ReleaseMutex(g_hMutex);
			return T();
		}
        T front (_queue.front ());  
        _queue.pop_front (); 
		ReleaseMutex(g_hMutex);
        return front;
    }

private:  
    BlockingQueue (const BlockingQueue& rhs);  
    BlockingQueue& operator = (const BlockingQueue& rhs);  
  
private:
	HANDLE g_hMutex;
    std::list<T> _queue;  
};