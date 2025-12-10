# MTD-Utils Build Summary for Radxa Rock (ARM)

## Build Information
- **Date**: December 10, 2025
- **Architecture**: ARM EABI5 (arm-linux-gnueabihf)
- **Linking Type**: Static (standalone binaries)
- **Install Location**: `/home/jibon/radxa/mtd-utils-install/`
- **Total Binaries**: 49 tools

## Features Included
✅ **JFFS2 Support** - Complete JFFS2 filesystem tools  
✅ **UBIFS Support** - Complete UBIFS filesystem tools  
✅ **NAND Flash Support** - NAND read/write/test utilities  
✅ **UBI Layer** - UBI volume management  
✅ **Static Linking** - No external library dependencies required on target

## Key Tools

### UBIFS Tools (16 tools)
- `mkfs.ubifs` (2.9MB) - Create UBIFS filesystems
- `mount.ubifs` - Mount helper for UBIFS
- `ubiformat` (96K) - Format UBI devices
- `ubiattach`, `ubidetach` - Attach/detach UBI devices
- `ubimkvol`, `ubirmvol` - Create/remove UBI volumes
- `ubinfo` - Display UBI device information
- `ubinize` (45K) - Create UBI images from configuration
- `ubiupdatevol` - Update UBI volume contents
- `ubiscan` - Scan and analyze UBI devices
- `ubiblock`, `ubicrc32`, `ubihealthd`, `ubirename`, `ubirsvol`

### JFFS2 Tools (3 tools)
- `mkfs.jffs2` (107K) - Create JFFS2 filesystem images
- `jffs2dump` (35K) - Dump JFFS2 filesystem info
- `jffs2reader` (46K) - Read JFFS2 filesystems

### NAND Tools (6 tools)
- `nanddump` (51K) - Dump NAND flash contents
- `nandwrite` (55K) - Write to NAND flash
- `nandtest` (18K) - Test NAND flash
- `nandflipbits` (46K) - Flip bits in NAND pages
- `nftldump`, `nftl_format` - NFTL layer utilities

### Flash Management (14 tools)
- `flash_erase` (51K) - Erase flash sectors
- `flashcp` (23K) - Copy to flash with verification
- `flash_lock`, `flash_unlock` - Lock/unlock flash sectors
- `flash_otp_*` - OTP (One-Time Programmable) area tools
- `lsmtd` (76K) - List MTD devices
- `mtdinfo` (60K) - Display MTD device information
- `mtd_debug` (18K) - MTD debugging utility
- `mtdpart` (14K) - MTD partition management

### Other Tools
- `ftl_format`, `ftl_check` - Flash Translation Layer tools
- `doc_loadbios`, `docfdisk` - DiskOnChip tools
- `serve_image`, `recv_image` - Network flash tools
- `fectest` - Forward Error Correction test
- `rfddump`, `rfdformat` - Resident Flash Disk tools

## Dependencies Built (Static ARM Libraries)
Located in `/home/jibon/radxa/arm-static-libs/install/lib/`

| Library | Size | Purpose |
|---------|------|---------|
| libcrypto.a | 5.1MB | OpenSSL crypto (for UBIFS authentication/encryption) |
| libssl.a | 672K | OpenSSL SSL/TLS |
| libuuid.a | 32K | UUID generation (for mkfs.ubifs) |
| libz.a | 75K | zlib compression (JFFS2/UBIFS) |
| liblzo2.a | 138K | LZO compression (JFFS2/UBIFS) |
| libzstd.a | 464K | Zstandard compression (UBIFS) |

## Usage Examples

### Creating UBIFS Image
```bash
# Create UBIFS filesystem from directory
./mkfs.ubifs -r /path/to/rootfs -m 2048 -e 124KiB -c 1024 -o ubifs.img

# Format MTD device as UBI
./ubiformat /dev/mtd0

# Attach UBI device
./ubiattach -p /dev/mtd0

# Create UBI volume
./ubimkvol /dev/ubi0 -N rootfs -s 100MiB

# Write UBIFS image to volume
./ubiupdatevol /dev/ubi0_0 ubifs.img
```

### Creating JFFS2 Image
```bash
# Create JFFS2 filesystem from directory
./mkfs.jffs2 -r /path/to/rootfs -o jffs2.img -e 128KiB -n -p

# Write to NAND flash
./flash_erase /dev/mtd1 0 0
./nandwrite -p /dev/mtd1 jffs2.img
```

### NAND Operations
```bash
# Dump NAND flash
./nanddump -f nand_backup.bin /dev/mtd2

# Write to NAND
./nandwrite /dev/mtd2 image.bin

# Test NAND flash
./nandtest /dev/mtd2
```

## Device Tree Configuration
NAND controller enabled in kernel with:
```dts
&nandc {
    status = "okay";
    nand@0 {
        nand-skip-bbtscan;  // Skip bad block table scan
    };
};
```

## Kernel Configuration
MTD subsystem enabled with:
- `CONFIG_MTD=y`
- `CONFIG_MTD_NAND_ROCKCHIP=y`
- `CONFIG_MTD_UBI=y`
- `CONFIG_UBIFS_FS=y`
- `CONFIG_JFFS2_FS=y`
- `CONFIG_MTD_BLOCK=y`
- And 80+ additional MTD-related options

## Build Process
1. Built static ARM libraries: zlib, lzo, zstd, uuid, openssl
2. Configured mtd-utils with cross-compilation for ARM
3. Linked statically against custom-built libraries
4. All binaries are standalone (no dynamic library dependencies)

## Transfer to Target
```bash
# Copy entire toolset to target device
scp -r /home/jibon/radxa/mtd-utils-install/sbin/* root@radxa:/usr/sbin/

# Or create tarball
tar czf mtd-utils-arm-static.tar.gz -C /home/jibon/radxa/mtd-utils-install/sbin .
```

## Verification
All binaries verified with:
- `file` command: Shows ARM EABI5 executable
- `ldd` command: Returns "not a dynamic executable" (static linking confirmed)
- Cross-compiled with: `arm-linux-gnueabihf-gcc`

## Notes
- All binaries are statically linked - no library dependencies required on target
- Can run directly on ARM device without installing additional packages
- UBIFS tools support authentication and encryption (via OpenSSL)
- JFFS2 tools support compression (zlib, lzo)
- Compatible with Linux kernel 5.15.196 MTD subsystem
- Built for Rockchip RK3188 NAND controller

## Related Files
- Kernel: `/home/jibon/radxa/linux-5.15.196/arch/arm/boot/zImage`
- Device Trees: `/home/jibon/radxa/linux-5.15.196/arch/arm/boot/dts/rk3188-radxarock.dtb`
- BusyBox: `/home/jibon/radxa/tiny-rootfx/` (embedded in kernel)
- Build scripts: `/home/jibon/radxa/arm-static-libs/build-all-deps.sh`
