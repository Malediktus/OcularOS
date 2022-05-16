#include "../../include/hardware/pci.h"
#include "../../include/lib/utils.h"

uint32_t Read(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset)
{
    uint32_t id =
        0x1 << 31
        | ((bus & 0xFF) << 16)
        | ((device & 0x1F) << 11)
        | ((function & 0x07) << 8)
        | (registeroffset & 0xFC);
    //commandPort.Write(id);
    __asm__ volatile("outl %0, %1" : : "a"(id), "Nd" (0xCF8));
    //uint32_t result = dataPort.Read();
    uint32_t result;
    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (0xCFC));
    return result >> (8* (registeroffset % 4));
}

void Write(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset, uint32_t value)
{
    uint32_t id =
        0x1 << 31
        | ((bus & 0xFF) << 16)
        | ((device & 0x1F) << 11)
        | ((function & 0x07) << 8)
        | (registeroffset & 0xFC);
    //commandPort.Write(id);
    __asm__ volatile("outl %0, %1" : : "a"(id), "Nd" (0xCF8));
    //dataPort.Write(value);
    __asm__ volatile("outl %0, %1" : : "a"(value), "Nd" (0xCFC));
}

int DeviceHasFunctions(uint16_t bus, uint16_t device)
{
    return Read(bus, device, 0, 0x0E) & (1<<7);
}

void SelectDrivers()
{
    for(int bus = 0; bus < 8; bus++)
    {
        for(int device = 0; device < 32; device++)
        {
            int numFunctions = DeviceHasFunctions(bus, device) ? 8 : 1;
            for(int function = 0; function < numFunctions; function++)
            {
                struct PeripheralComponentInterconnectDeviceDescriptor dev = GetDeviceDescriptor(bus, device, function);
                
                if(dev.vendor_id == 0x0000 || dev.vendor_id == 0xFFFF)
                    break;
                
                switch(dev.vendor_id)
                {
                    case 0x1022: // AMD
                        switch(dev.device_id)
                        {
                            case 0x2000: // am79c973
                                break;
                        }
                        break;

                    case 0x8086: // Intel
                        break;
                }
                
                
                switch(dev.class_id)
                {
                    case 0x03: // graphics
                        switch(dev.subclass_id)
                        {
                            case 0x00: // VGA
                                break;
                        }
                        break;
                }
                
                printf("PCI BUS ");
                printfHex(bus & 0xFF);
                
                printf(", DEVICE ");
                printfHex(device & 0xFF);

                printf(", FUNCTION ");
                printfHex(function & 0xFF);
                
                printf(" = VENDOR ");
                printfHex((dev.vendor_id & 0xFF00) >> 8);
                printfHex(dev.vendor_id & 0xFF);
                printf(", DEVICE ");
                printfHex((dev.device_id & 0xFF00) >> 8);
                printfHex(dev.device_id & 0xFF);
                printf("\n");
            }
        }
    }
}

struct PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(uint16_t bus, uint16_t device, uint16_t function)
{
    struct PeripheralComponentInterconnectDeviceDescriptor result;
    
    result.bus = bus;
    result.device = device;
    result.function = function;
    
    result.vendor_id = Read(bus, device, function, 0x00);
    result.device_id = Read(bus, device, function, 0x02);

    result.class_id = Read(bus, device, function, 0x0b);
    result.subclass_id = Read(bus, device, function, 0x0a);
    result.interface_id = Read(bus, device, function, 0x09);

    result.revision = Read(bus, device, function, 0x08);
    result.interrupt = Read(bus, device, function, 0x3c);
    
    return result;
}