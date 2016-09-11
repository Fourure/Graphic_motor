#include <iomanip>

#include "MemoryManager.hpp"
#include "Logger.hpp"

MemoryManager::MemoryManager(): m_Blocks(), m_File("memory_log.txt",std::ofstream::out), m_DeleteStack(){
    
}

MemoryManager::~MemoryManager(){
    if (m_Blocks.empty()) {
        m_File << " ***  No leak detected *** " << std::endl;
    }
    else {
        m_File << " *** WARNING : Leaks detected *** " << std::endl;
        Report_Leaks();
    }
    
    m_File.close();
}

void* MemoryManager::Allocate(std::size_t Size, const char *file, int line, bool array){

    void* Ptr = malloc(Size);
    
    MemoryBlock NewBlock;
    NewBlock.Size = Size;
    NewBlock.File = file;
    NewBlock.Line = line;
    NewBlock.Array = array;
    
    m_Blocks[Ptr] = NewBlock;
    
    m_File << "++ Allocation    | 0x" << Ptr
        << " | " << std::setw(7) << std::setfill(' ')
        << static_cast<int>(NewBlock.Size) << " octets"
        << " | " << NewBlock.File
        << "(" << NewBlock.Line << ")" << std::endl;
    
    return Ptr;
}

void MemoryManager::Free(void *Ptr, bool array){
    
    std::map<void*, MemoryBlock>::iterator It = m_Blocks.find(Ptr);
    
    if (It == m_Blocks.end()) {
        free(Ptr);
        return;
    }
    
    MemoryBlock& Block = It->second;
    
    if (Block.Array != array) {
        //TODO : Meilleur message dans le log (alloué avec tab à tel endroit et désaloué sans tab ou vice versa)
        Logger::Log() << "Desalocation error \n";
    }
    
    m_File << "-- Désallocation | 0x" << Ptr
        << " | " << std::setw(7) << std::setfill(' ')
        << static_cast<int>(It->second.Size) << " octets"
        << " | " << m_DeleteStack.top().File
        << " (" << m_DeleteStack.top().Line << ")" << std::endl;
    
    m_Blocks.erase(It);
    m_DeleteStack.pop();
    
    free(Ptr);
}

void MemoryManager::NextDelete(const char *file, int line){
    MemoryBlock Next_Delete;
    
    Next_Delete.File = file;
    Next_Delete.Line = line;
    
    m_DeleteStack.push(Next_Delete);
}

void MemoryManager::Report_Leaks(){
    std::size_t total_leaks = 0;
    
    for (std::map<void*, MemoryBlock>::iterator it = m_Blocks.begin(); it != m_Blocks.end(); it++) {
        
        MemoryBlock& block = it->second;
        
        total_leaks += block.Size;
        
        
        m_File << "-> 0x" << it->first
            << " | "   << std::setw(7) << std::setfill(' ')
            << static_cast<int>(block.Size) << " octets"
            << " | "   << block.File
            << " (" << block.Line << ")" << std::endl;
        
        free(it->first);
    }
    
    m_File << std::endl << std::endl << "-- "
        << static_cast<int>(m_Blocks.size()) << " blocs non-libéré(s), "
        << static_cast<int>(total_leaks)     << " octets --"
        << std::endl;
}