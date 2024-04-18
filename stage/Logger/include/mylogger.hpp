#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <array>
#include <mutex>
#include <string>
#include <chrono>

namespace Logs {

class FileSink
{
public:
    FileSink(const std::string& file_name);
    void write(const std::string& data);

private:
    std::ofstream m_output;
    std::mutex m_mutex;
};

class ConsoleSink
{
public:
    void write(const std::string& data);
};


class Logger
{
public:

    Logger(const std::string& file_name, bool file, bool cons);
    void log(std::string level, const char* source, const std::string& message);
    void log_packet_in_log(std::string level, const char* source, MainPocket packet);
    
private:
    ConsoleSink m_consoleSink;
    FileSink m_fileSink;
    bool m_writeToFile;
    bool m_writeToConsole;
};

} 

#define STR_(x) #x
#define STR(x) STR_(x)

#define LOG_DEBUG(message) logger.log("DEBUG", __FILE__ ":" STR(__LINE__), (message))
#define LOG_TRACE(message) logger.log("TRACE", __FILE__ ":" STR(__LINE__), (message))
#define LOG_INFO(message) logger.log("INFO", __FILE__ ":" STR(__LINE__), (message))
#define LOG_WARN(message) logger.log("WARN", __FILE__ ":" STR(__LINE__), (message))
#define LOG_ERROR(message) logger.log("ERROR", __FILE__ ":" STR(__LINE__), (message))
#define LOG_FATAL(message) logger.log("FATAL", __FILE__ ":" STR(__LINE__), (message))
#define LOG_PACKET(pac) logger.log_packet_in_log("PACKET", __FILE__ ":" STR(__LINE__), (pac))
#define logger(file_name, file, consol)  Logs::Logger logger(file_name, file, consol)

#endif

