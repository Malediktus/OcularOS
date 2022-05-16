#ifndef MOS_PCI_H
#define MOS_PCI_H

#include "port.h"
#include "../lib/types.h"

struct PeripheralComponentInterconnectDeviceDescriptor {
    uint32_t portBase;
    uint32_t interrupt;
            
    uint16_t bus;
    uint16_t device;
    uint16_t function;

    uint16_t vendor_id;
    uint16_t device_id;
            
    uint8_t class_id;
    uint8_t subclass_id;
    uint8_t interface_id;

    uint8_t revision;
            
};
            
uint32_t Read(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset);
void Write(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset, uint32_t value);
int DeviceHasFunctions(uint16_t bus, uint16_t device);
            
void SelectDrivers();
struct PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(uint16_t bus, uint16_t device, uint16_t function);

#endif