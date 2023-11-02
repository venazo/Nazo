#include "Memory.h"
#include "Logger.h"

static unsigned int memoryUsing = 0;

namespace Zewada
{
    void PrintMemory()
    {
        Z_INFO(memoryUsing);
    }
}

void* operator new(size_t size)
{
    memoryUsing += size;
    return malloc(size);
}

void operator delete(void* memory, size_t size)
{
    memoryUsing -= size;
    free(memory);
}