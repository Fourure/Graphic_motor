#ifndef Logger_hpp
#define Logger_hpp

#include <stdio.h>

#include <iostream>
#include <fstream>
#include <sstream>

class Logger {
    
public:
    virtual ~Logger();
    
    static void SetLogger(Logger* logger);
    
    static void Log(const char* format, ...);
    
    static Logger& Log();
    
    template <class T> Logger& operator<< (const T& toLog){
        std::ostringstream stream;
        stream << toLog;
        Write(stream.str());
        
        return Log();
    }
    
private:
    
    virtual void Write(const std::string& message) = 0;
    
    static Logger* s_instance;
};



class LoggerDebug : public Logger {
private:
    
    virtual void Write(const std::string& message);
};



class LoggerFile : public Logger {

public:
    LoggerFile(const std::string& filename = "logs.txt");
    ~LoggerFile();

private:
    
    virtual void Write(const std::string& message);
    
    std::ofstream m_File;
};


#endif /* Logger_hpp */
