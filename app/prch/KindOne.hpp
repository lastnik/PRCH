#pragma once
#include "BigBinary.hpp"
#include "Generator.hpp"
#include <array>
namespace prch
{
using namespace binary;

struct DecodeReq
{
    uint64_t size;
    uint64_t alignBit;
    BigBinary val;
};

struct DecodeInd
{
    bool  isDecoded;
    float efficiency;
};

struct SetupReq
{
    uint64_t size;
    uint64_t align;
};

class KindOne
{
public:
    explicit KindOne(SetupReq const&);
    //void decode(DecodeReq const&);
    DecodeInd decode(DecodeReq const&);
private:
    std::array<BigBinary, static_cast<uint32_t>(PrchType::num)> data;
};
}