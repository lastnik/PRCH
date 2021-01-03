#pragma once
#include <cstdint>
#include "BigBinary.hpp"
#include "KindOne.hpp"
#include "KindTwo.hpp"
#include "KindThree.hpp"
#include <memory>
using namespace prch;
namespace app
{
using namespace binary;
struct BaseCfg{};

struct ValueCfg : BaseCfg
{
    uint64_t    size;
    uint64_t    alignBit;
    std::string str;  //hex string
};

struct FileCfg : BaseCfg
{
    std::string str;  //file name and path
};

struct ColoringCfg : BaseCfg
{
    uint64_t byteSize;
};

struct ValueScedulerCfg
{
    uint64_t    maxSize;
    uint64_t    alignByte = 1;
};

class BaseSceduler
{
public:
    virtual void recieve(BaseCfg const*) = 0;
};

class ValSceduler : public BaseSceduler
{
public:
    ValSceduler(ValueScedulerCfg const&);
    ValSceduler() = delete;
    void recieve(BaseCfg const*) final;
private:
    BigBinary value;
    std::unique_ptr<KindOne>   one;
    std::unique_ptr<KindTwo>   two;
    std::unique_ptr<KindThree> three;
    //uint64_t* str;
};
}