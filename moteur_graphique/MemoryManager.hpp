#ifndef MemoryManager_hpp
#define MemoryManager_hpp

#include <cstdio>
#include <map>
#include <stack>
#include <fstream>

struct MemoryBlock {
    std::size_t Size;
    const char* File;
    int         Line;
    bool        Array;
};

class MemoryManager {

protected:
    
    std::map<void*, MemoryBlock>    m_Blocks;
    std::ofstream                   m_File;
    std::stack<MemoryBlock>         m_DeleteStack;
    
public:
    
    static MemoryManager& Instance();
    
    void* Allocate(std::size_t Size, const char* file, int line, bool array);
    
    void Free(void* Ptr, bool array);
    
    void NextDelete(const char* file, int line);
    
private:
    
    MemoryManager();
    
    ~MemoryManager();
    
    void Report_Leaks();
};

MemoryManager& MemoryManager::Instance(){
    static MemoryManager instance;
    return instance;
}

#endif /* MemoryManager_hpp */
