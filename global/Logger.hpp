#pragma once

#include <cstdint>
#include <cstdio>

#define LOG_DBG(STR, args...) \
    if(logger::logger->base <= logger::Level::debug) \
    { \
        logger::print("DEBUG    : "); \
        logger::print(STR, ##args); \
        logger::print("\n");\
    }
#define LOG_INF(STR, args...) \
    if(logger::logger->base <= logger::Level::info) \
    { \
        logger::print("INFO     : "); \
        logger::print(STR, ##args); \
        logger::print("\n");\
    }
#define LOG_WRG(STR, args...) \
    if(logger::logger->base <= logger::Level::waring) \
    { \
        logger::print("WARNING  : "); \
        logger::print(STR, ##args); \
        logger::print("\n");\
    }
#define LOG_ERR(STR, args...) \
    if(logger::logger->base <= logger::Level::error) \
    { \
        logger::print("ERROR    : "); \
        logger::print(STR, ##args); \
        logger::print("\n");\
    }
#define LOG_CRT(STR, args...) \
    if(logger::logger->base <= logger::Level::critical) \
    { \
        logger::print("CRITICAL : "); \
        logger::print(STR, ##args); \
        logger::print("\n");\
    }
namespace logger
{

enum class Level : uint32_t
{
      debug = 0
    , info
    , waring
    , error
    , critical
};

class LoggerDescriptor;
extern LoggerDescriptor* logger;

void open(const char* str);
void open();
void close();
void setLevel(Level);
template<typename... Args>
void print(Level lvl, const char* str, Args... vals);

class LoggerDescriptor
{

public:
    template<typename... Args>
    friend void logger::print(const char* str, Args... vals);

    friend void logger::open(const char* str);
    friend void logger::open();
    friend void logger::close();
    friend void logger::setLevel(Level);
    LoggerDescriptor(LoggerDescriptor const&) = delete;
private:
    LoggerDescriptor() = default;
    FILE* fd   = nullptr;
public:
    Level base = Level::debug;
};

template<typename... Args>
void print(const char* str, Args... vals)
{
    fprintf(logger->fd, str, vals...);
}


}