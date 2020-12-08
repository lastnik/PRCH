#include "Logger.hpp"

namespace logger
{

LoggerDescriptor* logger = nullptr;


void open(const char* str)
{
    if(logger != nullptr)
    {
        LOG_WRG("Try to open logger twice");
        return;
    }
    logger = new LoggerDescriptor();
    logger->fd = fopen(str, "w");
}


void open()
{
    if(logger != nullptr)
    {
        LOG_WRG("Try to open logger twice");
        return;
    }
    logger = new LoggerDescriptor();
    logger->fd = stdout;
}

void close()
{
    if(logger == nullptr)
    {
        LOG_WRG("Try to close uninited logger");
        return;
    }
    if(logger->fd != stdout)
    {
        fclose(logger->fd);
    }
    logger->fd = nullptr;
}

}