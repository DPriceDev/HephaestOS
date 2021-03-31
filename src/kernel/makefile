GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = elf
LDPARAMS = -m elf_i386
build_dir = $(BUILD_DIR)
parent_dir = $(PARENT_DIR)

objects = loader.o memory.o kernel.o TextDisplay.o
ld_objects = $(BUILD_DIR)/loader.o $(BUILD_DIR)/memory.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/TextDisplay.o

%.o: %.cpp
	g++ $(GPPPARAMS) -o $(build_dir)/$@ -c $<

%.o: %.asm
	nasm -f $(ASPARAMS) -o $(build_dir)/$@ $<
	
mykernel.bin: linker.ld $(objects)
	cp -f $< $(build_dir)
	cd $(build_dir)
	ld $(LDPARAMS) -T $(build_dir)/$< -o $(BUILD_DIR)/$@ $(ld_objects)

mykernel.iso: mykernel.bin
	rm -r -f $(BUILD_DIR)/iso
	mkdir $(BUILD_DIR)/iso
	mkdir $(BUILD_DIR)/iso/boot
	mkdir $(BUILD_DIR)/iso/boot/grub
	cp $(BUILD_DIR)/$< $(BUILD_DIR)/iso/boot/
	echo 'set timeout-0' >> $(BUILD_DIR)/iso/boot/grub/grub.cfg
	echo 'set default-0' >> $(BUILD_DIR)/iso/boot/grub/grub.cfg
	echo 'menuentry "My Operating System"{' >> $(BUILD_DIR)/iso/boot/grub/grub.cfg
	echo '  multiboot /boot/mykernel.bin' >> $(BUILD_DIR)/iso/boot/grub/grub.cfg
	echo ' boot' >> $(BUILD_DIR)/iso/boot/grub/grub.cfg
	echo '}' >> $(BUILD_DIR)/iso/boot/grub/grub.cfg
	grub-mkrescue --output=$(PARENT_DIR)/$@ $(BUILD_DIR)/iso
	rm -rf $(BUILD_DIR)/iso 

.PHONY: install
install: mykernel.iso

.PHONY: clean
clean:
	rm -r -f $(build_dir)/$(objects)