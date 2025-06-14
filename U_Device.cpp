#include "U_Device.h"

int U_Device::Count = 0;

U_Device::U_Device() :Resource('U', ++Count)
{
}
