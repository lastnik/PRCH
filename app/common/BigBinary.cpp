#include "BigBinary.hpp"
#include "Memory.hpp"
#include <algorithm>
#include "Logger.hpp"

namespace binary
{

using namespace memory;

BigBinary::BigBinary(uint64_t size, uint64_t align)
    : pimpl(std::make_shared<BigBinaryImpl>(size, align))
{
}

BigBinaryImpl::BigBinaryImpl(uint64_t _size, uint64_t align)
{
    uint64_t num = mem_align(_size * align, sizeOfPiece) / sizeOfPiece;
    num = (num == 0) ? 1 : num;
    mem_alloc(ptr, num);
    bitSize  = _size * align * 8;
    byteSize = _size * align;
    size     = num;
    LOG_DBG("bitSize %d byteSize %d size %d", bitSize, byteSize, size);
}

BigBinaryImpl::~BigBinaryImpl()
{
    mem_free(ptr);
}

void BigBinary::set(uint64_t const* src, uint64_t start, uint64_t size, uint64_t align)
{
    uint64_t num   = mem_align(size * align, BigBinaryImpl::sizeOfPiece) / BigBinaryImpl::sizeOfPiece;
    uint64_t begin = mem_align(start * align, BigBinaryImpl::sizeOfPiece) / BigBinaryImpl::sizeOfPiece;
    mem_copy(pimpl->ptr + begin, src, num);
}

void BigBinary::set(uint64_t src, uint64_t start, uint64_t size, uint64_t align)
{
    uint64_t num   = mem_align(size * align, BigBinaryImpl::sizeOfPiece) / BigBinaryImpl::sizeOfPiece;
    uint64_t begin = mem_align(start * align, BigBinaryImpl::sizeOfPiece) / BigBinaryImpl::sizeOfPiece;
    std::fill_n(pimpl->ptr + begin, num, src);
}

void BigBinary::zero()
{
    mem_zero(pimpl->ptr, pimpl->size);
}

}