#pragma once

#include <memory>

void* operator new(size_t size);

void operator delete(void* memory);

namespace Zewada
{
    void PrintMemory();
}