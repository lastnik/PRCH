#pragma once
#include "BigBinary.hpp"
#include "Generator.hpp"
#include "KindOne.hpp"
#include <vector>
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

class KindTwo
{
public:
    explicit KindTwo(SetupReq const&);
    DecodeInd decode(DecodeReq const&);
private:
    uint64_t mod(uint64_t, uint64_t);

    BigBinary divider;
    BigBinary residue;
    BigBinary collect;
    BigBinary variable;
    BigBinary zero;
    std::vector<uint8_t> table;
};

}