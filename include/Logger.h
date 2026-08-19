#include<iostream>
#include<string>
#include<fstream>
#include<mutex>
enum class LogLevel{
    Info=0,
    Warning=1,
    Error=2
};
class Logger{
public:
    static void log(LogLevel level,const std::string& message);
    static void info(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);
    static void setLevel(LogLevel min_level);
    
private:
    static std::string getCurrentTime();
    static std::string levelToString(LogLevel level);
    static void writeLog(std::ostream& out,const std::string& time,const std::string& level,const std::string& message);
    static std::ofstream file;
    static std::mutex mutex;
    static LogLevel minLevel;
};