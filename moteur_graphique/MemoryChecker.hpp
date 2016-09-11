#ifndef MemoryChecker_hpp
#define MemoryChecker_hpp

#include <cstdio>
#include "MemoryManager.hpp"

inline void* operator new(std::size_t size, const char* file, int line){
    return MemoryManager::Instance().Allocate(size, file, line, false);
}

inline void* operator new[](std::size_t size, const char* file, int line){
    return MemoryManager::Instance().Allocate(size, file, line, true);
}

inline void operator delete(void* Ptr)
{
    MemoryManager::Instance().Free(Ptr, false);
}

inline void operator delete[](void* Ptr)
{
    MemoryManager::Instance().Free(Ptr, true);
}


inline void operator delete(void* Ptr, const char* File, int Line)
{
    MemoryManager::Instance().NextDelete(File, Line);
    MemoryManager::Instance().Free(Ptr, false);
}

inline void operator delete[](void* Ptr, const char* File, int Line)
{
    MemoryManager::Instance().NextDelete(File, Line);
    MemoryManager::Instance().Free(Ptr, true);
}

#endif /* MemoryChecker_h */

#ifndef new
    #define new new(__FILE__, __LINE__)
    #define delete MemoryManager::Instance().NextDelete(__FILE__, __LINE__), delete
#endif
