#pragma once
#include "BigBinary.hpp"
#include "Memory.hpp"
namespace prch
{
using namespace binary;
using namespace memory;

inline bool operator==(const BigBinary&, const BigBinary&) __attribute__((always_inline));
inline bool operator==(const BigBinary& a, const BigBinary& b)
{
    uint64_t minSize = std::min(a.getSize(), b.getSize());
    auto* ptrA = a.data();
    auto* ptrB = b.data();
    for(uint64_t i = 0; i < minSize; i++)
    {
        if(*ptrA != *ptrB)
            return false;
        ptrA++;
        ptrB++;
    }
    return true;
}
inline bool operator>(const BigBinary&, const BigBinary&) __attribute__((always_inline));
inline bool operator>(const BigBinary& a, const BigBinary& b)
{
    uint64_t maxSize = std::max(a.getSize(), b.getSize());
    bool isB = (maxSize == a.getSize()) ? false : true;
    uint64_t minSize = std::min(a.getSize(), b.getSize());
    auto* ptrA = a.data();
    auto* ptrB = b.data();
    for(uint64_t i = maxSize - 1; i >= minSize; i--)
    {
        if(isB)
        {
            if(*(ptrA + i) != 0)
                return true;
        }else
        {
            if(*(ptrB + i) != 0)
                return false;
        }
    }
    for(int64_t i = minSize - 1; i >= 0; i--)
    {
        if(*(ptrA + i) < *(ptrB + i))
            return false;
        if(*(ptrA + i) > *(ptrB + i))
            return true;
    }
    return false;
}

inline void concatination(const BigBinary&, const BigBinary&, BigBinary&, uint64_t sizeBitA, uint64_t sizeBitB) __attribute__((always_inline));
inline void concatination(const BigBinary&a, const BigBinary& b, BigBinary& c, uint64_t sizeBitA, uint64_t sizeBitB)
{
    auto sizeA    = mem_align(sizeBitA, 64) >> 6;
    auto sizeB    = mem_align(sizeBitB, 64) >> 6;
    auto endA     = sizeBitA & (64 - 1);
    c.set(a.data(), 0, sizeA);
    if(endA != 0)
    {
        uint64_t end = *(a.data() + (sizeA - 1));
        auto* ptrB = b.data();
        for(uint64_t i = 0; i < sizeB; i++)
        {
            uint64_t val = (*ptrB << endA) | end;
            c.set(val, sizeA - 1 + i, 1);
            // end = (*ptrB >> 1) & (~(uint64_t(1) << 63));
            end = (*ptrB >> (63 - endA));
            ptrB++;
        }
        if(end != 0)
        {
            c.set(end, sizeA - 1 + sizeB, 1);
        }
    }
    else
    {
        c.set(b.data(), sizeA, sizeB);
    }
}

}