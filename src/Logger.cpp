#include "Logger.h"
#include <chrono>
#include <ctime>
#include<iomanip>
#include<sstream>
std::ofstream Logger::file("app.log",std::ios::app);
std::mutex Logger::mutex;
LogLevel Logger::minLevel=LogLevel::Info;
std::string Logger::levelToString(LogLevel level){
    switch(level){
        case(LogLevel::Info):
            return "INFO";
        case(LogLevel::Warning):
            return "WARNING";
        case(LogLevel::Error):
            return "ERROR";
        default:
            break;
    }
    return "levelToString function fault";
}
void Logger::log(LogLevel level,const std::string& message){

    std::lock_guard<std::mutex> lock(Logger::mutex);
    if(static_cast<int>(level)<static_cast<int>(minLevel)) return;
    auto time=getCurrentTime();
    auto levelString=levelToString(level);
    
    Logger::writeLog(std::cout,time,levelString,message);
    if(!file.is_open()){
        std::cerr<<"Failed to open log file\n";
    }else Logger::writeLog(file,time,levelString,message);
}
void Logger::info(const std::string& message){
    log(LogLevel::Info,message);
}
void Logger::warning(const std::string& message){
    log(LogLevel::Warning,message);
}
void Logger::error(const std::string& message){
    log(LogLevel::Error,message);
}
std::string Logger::getCurrentTime(){
    auto now=std::chrono::system_clock::now();
    std::time_t current_time=std::chrono::system_clock::to_time_t(now);
    std::tm* local_time=std::localtime(&current_time);
    std::ostringstream oos;
    oos<<std::setfill('0')
        <<local_time->tm_year+1900<<"-"
        <<std::setw(2)<<local_time->tm_mon+1<<"-"
        <<std::setw(2)<<local_time->tm_mday<<" "
        <<std::setw(2)<<local_time->tm_hour<<":"
        <<std::setw(2)<<local_time->tm_min<<":"
        <<std::setw(2)<<local_time->tm_sec;
        
        return oos.str();
}
void Logger::setLevel(LogLevel min_level){
    std::lock_guard<std::mutex> lock(Logger::mutex);
    minLevel=min_level;
}
void Logger::writeLog(std::ostream& out,const std::string& time,const std::string& level,const std::string& message){
    out<<"["<<time<<"] "
        <<"["<<level<<"] "
        <<message<<'\n';
}