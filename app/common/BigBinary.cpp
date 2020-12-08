#include "BigBinary.hpp"
#include "Memory.hpp"
namespace binary
{

using namespace memory;

BigBinary::BigBinary(uint64_t size, uint64_t align)
    : pimpl(std::make_shared<BigBinaryImpl>(size, align))
{
}

BigBinaryImpl::BigBinaryImpl(uint64_t size, uint64_t align)
{
    uint64_t num = mem_align(size * align, 8);
    num = (num == 0) ? 1 : num;
    mem_alloc(ptr, num);
    bitSize  = size * align * 8;
    byteSize = size * align;
    size     = num;
}

BigBinaryImpl::~BigBinaryImpl()
{
    mem_free(ptr);
}

void BigBinary::set(uint64_t* src, uint64_t start, uint64_t size, uint64_t align)
{
    uint64_t num   = mem_align(size * align, 8);
    uint64_t begin = mem_align(start * align, 8);
    mem_copy(pimpl->ptr + begin, src, num);
}

void BigBinary::zero()
{
    mem_zero(pimpl->ptr, pimpl->size);
}

}