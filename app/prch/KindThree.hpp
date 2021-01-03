#pragma once
#include "BigBinary.hpp"
#include "Generator.hpp"
#include "KindOne.hpp"
#include <array>
namespace prch
{
using namespace binary;

struct DecodeReq;
struct SetupReq;
struct DecodeInd;
// struct DecodeReq
// {
//     uint64_t size;
//     uint64_t alignBit;
//     BigBinary val;
// };

// struct DecodeInd
// {
//     bool  isDecoded;
//     float efficiency;
// };

// struct SetupReq
// {
//     uint64_t size;
//     uint64_t align;
// };

class KindThree
{
public:
    explicit KindThree(SetupReq const&);
    DecodeInd decode(DecodeReq const&);
private:
    BigBinary part1;
    BigBinary part2;
    BigBinary part3;
};

}