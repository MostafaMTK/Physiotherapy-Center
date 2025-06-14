#include "E_Device.h"

int E_Device::Count = 0;

E_Device::E_Device() :Resource('E', ++Count)
{
}
