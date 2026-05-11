#!/bin/bash
set -e

BASE_DIR=$(dirname "$0")/..
BUILD_DIR=$BASE_DIR/build
KERNEL_DIR=$BASE_DIR/kernel
ISO_DIR=$BASE_DIR/iso

# 1. Prepare the build and output directories
mkdir -p "$BUILD_DIR"
mkdir -p "$ISO_DIR/boot/grub"

# 2. Mirror the kernel directory structure inside build/ 
# This handles subfolders like kernel/drivers/ or kernel/cpu/
find "$KERNEL_DIR" -type d | sed "s|^$KERNEL_DIR|$BUILD_DIR|" | xargs mkdir -p

# 3. Assemble the boot.s file
i686-elf-as "$BASE_DIR/kernel/boot.s" -o "$BUILD_DIR/boot.o"

# 4. Compile every .c file
# This puts kernel/main.c -> build/main.o, etc.
for f in $(find "$KERNEL_DIR" -name "*.c"); do
    # Calculate the output path by replacing the kernel path with build path
    REL_PATH=${f#$KERNEL_DIR/}
    OBJ_PATH="$BUILD_DIR/${REL_PATH%.c}.o"
    
    echo "Compiling $f..."
    i686-elf-gcc -c "$f" -o "$OBJ_PATH" -std=gnu99 -ffreestanding -O2 -Wall -Wextra
done

# 5. Link the object files
# We grab all .o files found anywhere inside the build directory
echo "Linking BasicOS..."
i686-elf-gcc -T "$BASE_DIR/builder/linker.ld" \
    -o "$ISO_DIR/boot/basicos.bin" \
    -ffreestanding -O2 -nostdlib \
    $(find "$BUILD_DIR" -name "*.o") \
    -lgcc

# 6. Finalize ISO
cp "$BASE_DIR/builder/grub.cfg" "$ISO_DIR/boot/grub/grub.cfg"
grub-mkrescue -o "$BASE_DIR/BasicOS.iso" "$ISO_DIR"

echo "Build successful: BasicOS.iso created."