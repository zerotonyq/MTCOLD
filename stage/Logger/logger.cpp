#include "logger.h"

namespace Logs {

FileSink::FileSink(const std::string& file_name)
    : m_output(file_name)
{
    if(!m_output.is_open()){
        throw std::runtime_error("File was not created");
    }
}

void FileSink::write(const std::string& data)
{
    const std::size_t data_size = data.size();
    std::lock_guard<std::mutex> lock(m_mutex);
    m_output.write(data.data(), data_size);
}

void ConsoleSink::write(const std::string& data)
{
    std::cout << data;
}

Logger::Logger(const std::string& file_name, bool file, bool console)
    : m_fileSink(file_name), m_writeToFile(file), m_writeToConsole(console)
{
}



void Logger::log(std::string level, const std::string& source, const std::string& message)
{
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
    std::string time = std::ctime(&currentTime_t);
    const std::string formatted_message = time + "[" + level + "] -- " + source + " -- " + message + "\n";
    if(m_writeToFile && m_writeToConsole){
        m_consoleSink.write(formatted_message);
        m_fileSink.write(formatted_message);
    }
    else if (m_writeToFile){
        m_fileSink.write(formatted_message);
    }
    else if (m_writeToConsole){
        m_consoleSink.write(formatted_message);
    }
}



void Logger::log_packet_in_log(std::string level, const std::string& source, MainPacket packet)
{
    std::string message;
    if (packet.command == COMMAND_GET_INDICATORS_COUNT){
        sIndicatorsCountPack coutsIndicatorsCountPack;
        coutsIndicatorsCountPack.deserializeData(packet.data);
        message = "COMMAND_GET_INDICATORS_COUNT ( Command: " + std::to_string(coutsIndicatorsCountPack.command) + ", IndicatorIndex: " + std::to_string(coutsIndicatorsCountPack.indicatorsCount) + ", crc32: " + std::to_string(coutsIndicatorsCountPack.crc32) + " )";
    }
    else if (packet.command == COMMAND_GET_STAT){
        sIndicatorStatisticsPack coutsIndicatorStatisticsPack;
        coutsIndicatorStatisticsPack.deserializeData(packet.data);
        //std::to_string(coutsIndicatorStatisticsPack.IndicatorData.SerialNum);
        message = "COMMAND_GET_STAT ( Command: " + std::to_string(coutsIndicatorStatisticsPack.command) + ", IndicatorIndex: " + std::to_string(coutsIndicatorStatisticsPack.indicatorIndex) + ", crc32: " + std::to_string(coutsIndicatorStatisticsPack.crc32) + ", sOneIndicatorStats: ( SerialNum: " + std::to_string(coutsIndicatorStatisticsPack.indicatorData.serialNumber) + ", Type: " + std::to_string(coutsIndicatorStatisticsPack.indicatorData.type) + ", Power: " + std::to_string(coutsIndicatorStatisticsPack.indicatorData.power) + ", Color: " + std::to_string(coutsIndicatorStatisticsPack.indicatorData.color) + ", Current_mA: " + std::to_string(coutsIndicatorStatisticsPack.indicatorData.current_ma) + ", ErrorCode: " + std::to_string(coutsIndicatorStatisticsPack.indicatorData.error_code) + "))";

    }
    else if (packet.command == COMMAND_INDIC_ACTION_ON){
        message = "COMMAND_INDIC_ACTION_ON";
    }
    else if (packet.command == COMMAND_INDIC_ACTION_OFF){
        message = "COMMAND_INDIC_ACTION_OFF";
    }
    else{
        message = "No such command";
    }
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
    std::string time = std::ctime(&currentTime_t);
    const std::string formatted_message = time + "[" + level + "] -- " + source + " -- " + message + "\n";
    if(m_writeToFile && m_writeToConsole){
        m_consoleSink.write(formatted_message);
        m_fileSink.write(formatted_message);
    }
    else if (m_writeToFile){
        m_fileSink.write(formatted_message);
    }
    else if (m_writeToConsole){
        m_consoleSink.write(formatted_message);
    }
}


}
