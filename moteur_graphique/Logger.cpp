#include "Logger.hpp"

Logger* Logger::s_instance = NULL;

Logger::~Logger() {}

void Logger::SetLogger(Logger *logger){
    if ( s_instance != NULL ) {
        delete s_instance;
        s_instance = NULL;
    }
    
    s_instance = logger;
}

Logger& Logger::Log(){
    return *s_instance;
}

void Logger::Log(const char *format, ...){
    char buffer[512];
    
    va_list params;
    va_start(params, format);
    vsprintf(buffer, format, params);
    va_end(params);
    
    s_instance->Write(buffer);
}

void LoggerDebug::Write(const std::string &message){
    std::cerr << message << std::endl;
}

LoggerFile::LoggerFile(const std::string& filename): m_File(filename)
{
}

LoggerFile::~LoggerFile(){
    m_File.close();
}

void LoggerFile::Write(const std::string &message){
    m_File << message << std::endl;
}