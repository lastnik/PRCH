#pragma once

#include <cstdint>
#include <cstdio>

#define LOG_DBG(STR, args...) \
    if(logger->base <= Level::debug) \
    { \
        print("DEBUG    : "); \
        print(STR, ##args); \
        print("\n");\
    }
#define LOG_INF(STR, args...) \
    if(logger->base <= Level::info) \
    { \
        print("INFO     : "); \
        print(STR, ##args); \
        print("\n");\
    }
#define LOG_WRG(STR, args...) \
    if(logger->base <= Level::waring) \
    { \
        print("WARNING  : "); \
        print(STR, ##args); \
        print("\n");\
    }
#define LOG_ERR(STR, args...) \
    if(logger->base <= Level::error) \
    { \
        print("ERROR    : "); \
        print(STR, ##args); \
        print("\n");\
    }
#define LOG_CRT(STR, args...) \
    if(logger->base <= Level::critical) \
    { \
        print("CRITICAL : "); \
        print(STR, ##args); \
        print("\n");\
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

    LoggerDescriptor(LoggerDescriptor const&) = delete;
private:
    LoggerDescriptor() = default;
    FILE* fd   = nullptr;
    Level base = Level::waring;
};

template<typename... Args>
void print(const char* str, Args... vals)
{
    fprintf(logger->fd, str, vals...);
}


}