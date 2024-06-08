#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <array>
#include <mutex>
#include <string>
#include <chrono>

namespace Logs {

class Output_location
{
public:
    virtual ~Output_location() = default;
    virtual void write(const std::string& data) = 0;
};

class Output_to_file : public Output_location
{
public:
    Output_to_file(const std::string& file_name);
    void write(const std::string& data) override;

private:
    std::ofstream m_output;
    std::mutex m_mutex;
};

class Output_to_console : public Output_location
{
public:
    void write(const std::string& data) override;
};

class Logger
{
public:
    enum class Log_output
    {
        File_and_console_case,
        File_only_case,
        Console_only_case
    };

    Logger(const std::string& file_name, Log_output output);
    void log(std::string level, const std::string& source, const std::string& message);
    void log_packet_in_log(std::string level, const std::string& source, MainPacket packet);

private:
    void write_log(const std::string& formatted_message);
    std::string format_message(const std::string& level, const std::string& source, const std::string& message);

    Output_to_console m_consoleSink;
    Output_to_file m_fileSink;
    Log_output m_output;
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
#define File_and_console Logs::Logger::Log_output::File_and_console_case
#define Console_only Logs::Logger::Log_output::Console_only_case
#define File_only Logs::Logger::Log_output::File_only_case
#define logger(file_name, output)  Logs::Logger logger(file_name, output)

#endif
