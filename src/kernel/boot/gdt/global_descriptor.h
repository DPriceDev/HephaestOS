//
// Created by david on 15/07/2021.
//

#ifndef HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_H
#define HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_H

namespace kernel::boot::gdt {

    struct Access {
        bool accessed: 1;
        bool ReadWritable: 1;
        bool isConforming: 1;
        bool isExecutable: 1;
        bool descriptorType: 1;
        uint8_t privilege: 2;
        bool present: 1;
    } __attribute__((packed));

    struct Flags {
        uint8_t unused: 2;
        bool size: 1;
        bool granularity: 1;
    } __attribute__((packed));

    struct GlobalDescriptor {
        uint16_t lowerLimit;
        uint32_t lowerBase: 24;
        Access access;
        uint8_t upperLimit: 4;
        bool available: 1;
        bool longMode: 1;
        bool size: 1;
        bool granularity: 1;
        uint8_t upperBase;
    } __attribute__((packed));

    constexpr Access zeroAccess {false, false, false, false, false, 0, false};
    constexpr Access codeKernelAccess {false, true, true, true, true, 0, true};
    constexpr Access dataKernelAccess {false, true, true, false, true, 0, true};
    constexpr Access codeUserAccess {false, true, true, true, true, 3, true};
    constexpr Access dataUserAccess {false, true, true, false, true, 3, true};

    constexpr Flags zeroFlags {0, false, false};
    constexpr Flags gran32Flags {0, true, true};
}

#endif // HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_H