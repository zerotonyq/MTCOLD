#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <array>
#include <mutex>
#include <string>
#include <chrono>

namespace Logs {

class Output_to_file
{
public:
    Output_to_file(const std::string& file_name);
    void write(const std::string& data);

private:
    std::ofstream m_output;
    std::mutex m_mutex;
};

class Output_to_console
{
public:
    void write(const std::string& data);
};


class Logger
{
public:

    Logger(const std::string& file_name, bool file, bool cons);
    void log(std::string level, const std::string& source, const std::string& message);
    void log_packet_in_log(std::string level, const std::string& source, MainPacket packet);

private:
    Output_to_console m_output_to_console;
    Output_to_file m_output_to_file;
    bool m_write_to_file;
    bool m_write_to_console;
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
