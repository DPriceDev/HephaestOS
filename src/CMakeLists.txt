add_subdirectory(os)
add_subdirectory(shared)
add_subdirectory(sysroot)

add_custom_target(
        HephaistOS.iso

        DEPENDS ${CMAKE_BINARY_DIR}/src/os/boot/boot.elf ${CMAKE_BINARY_DIR}/src/os/kernel/kernel.elf
        COMMAND rm -r -f ${CMAKE_BINARY_DIR}/iso
        COMMAND mkdir ${CMAKE_BINARY_DIR}/iso
        COMMAND mkdir ${CMAKE_BINARY_DIR}/iso/boot
        COMMAND mkdir ${CMAKE_BINARY_DIR}/iso/modules
        COMMAND mkdir ${CMAKE_BINARY_DIR}/iso/boot/grub
        COMMAND echo ${CMAKE_BINARY_DIR}
        COMMAND cp ${CMAKE_BINARY_DIR}/src/os/boot/boot.elf ${CMAKE_BINARY_DIR}/iso/boot/
        COMMAND cp ${CMAKE_BINARY_DIR}/src/os/kernel/kernel.elf ${CMAKE_BINARY_DIR}/iso/modules/
        COMMAND echo 'set timeout-1' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo 'set default-0' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo 'menuentry \"HephaistOS\"{' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo ' multiboot /boot/boot.elf' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo ' module /modules/kernel.elf kernel' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo ' boot' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo '}' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND grub-mkrescue -o ${CMAKE_BINARY_DIR}/HephaistOS.iso ${CMAKE_BINARY_DIR}/iso
        COMMAND rm -rf ${CMAKE_BINARY_DIR}/iso
)