HUR-BOOT> update sd
switch to partitions #0, OK
mmc0 is current device
reading UpdateFlag
489 bytes read in 4 ms (119.1 KiB/s)
Update IMG : ALL
reading SHUR_v018.bin
16977041 bytes read in 735 ms (22 MiB/s)

Sanion HUR Update Start...
Compress Data Size: 16977041
Header Reading..

============== Update Binary Information ================
Version            : V 0.18
Compress Data Size : 0x1030C91
Partitions Count   : 7
Binary CRC         : 0x15F
Update IMG         : ALL
===========================================================
switch to partitions #0, OK
mmc1(part 0) is current device
Writing GPT: success!
ti_spi_set_speed: hz: 76800000, clock divider 0
__ti_qspi_set_mode: SPI flash mode=0x2000, SPI_RX_QUAD=0x2000
SF: Detected s25fl256s_64k with page size 256 Bytes, erase size 64 KiB, total 32 MiB, mapped at 5c000000
ti_spi_set_speed: hz: 76800000, clock divider 0
__ti_qspi_set_mode: SPI flash mode=0x2000, SPI_RX_QUAD=0x2000

Header Count  : 7, Current Count: 1
File System     : BIN
Partition name  : SPL
Partition addr  : 0x00000000
Buffer addr     : 0x82000040
Data Size       : 0x00019a06
SF: 131072 bytes @ 0x0 Erased: OK
device 0 offset 0x0, size 0x19a06
SF: 104966 bytes @ 0x0 Written: OK

Header Count  : 7, Current Count: 2
File System     : BIN
Partition name  : BOOT
Partition addr  : 0x00020000
Buffer addr     : 0x82019a6a
Data Size       : 0x000e14d4
SF: 1048576 bytes @ 0x20000 Erased: OK
device 0 offset 0x20000, size 0xe14d4
SF: 922836 bytes @ 0x20000 Written: OK

Header Count  : 7, Current Count: 3
File System     : BIN
Partition name  : LOGO
Partition addr  : 0x00120000
Buffer addr     : 0x820faf62
Data Size       : 0x000172bd
SF: 2097152 bytes @ 0x120000 Erased: OK
device 0 offset 0x120000, size 0x172bd
SF: 94909 bytes @ 0x120000 Written: OK
ti_spi_set_speed: hz: 76800000, clock divider 0
__ti_qspi_set_mode: SPI flash mode=0x2000, SPI_RX_QUAD=0x2000
SF: Detected s25fl256s_64k with page size 256 Bytes, erase size 64 KiB, total 32 MiB, mapped at 5c000000
ti_spi_set_speed: hz: 76800000, clock divider 0
__ti_qspi_set_mode: SPI flash mode=0x2000, SPI_RX_QUAD=0x2000

Header Count  : 7, Current Count: 4
File System     : BIN
Partition name  : DTB
Partition addr  : 0x00320000
Buffer addr     : 0x82112243
Data Size       : 0x000177c6
SF: 131072 bytes @ 0x320000 Erased: OK
device 0 offset 0x320000, size 0x177c6
SF: 96198 bytes @ 0x320000 Written: OK

Header Count  : 7, Current Count: 5
File System     : BIN
Partition name  : KL
Partition addr  : 0x00340000
Buffer addr     : 0x82129a2d
Data Size       : 0x003c2200
SF: 4194304 bytes @ 0x340000 Erased: OK
device 0 offset 0x340000, size 0x3c2200
SF: 3940864 bytes @ 0x340000 Written: OK
ti_spi_set_speed: hz: 76800000, clock divider 0
__ti_qspi_set_mode: SPI flash mode=0x2000, SPI_RX_QUAD=0x2000
SF: Detected s25fl256s_64k with page size 256 Bytes, erase size 64 KiB, total 32 MiB, mapped at 5c000000
ti_spi_set_speed: hz: 76800000, clock divider 0
__ti_qspi_set_mode: SPI flash mode=0x2000, SPI_RX_QUAD=0x2000

Header Count  : 7, Current Count: 6
File System     : JFFS2
Partition name  : APP
Partition addr  : 0x00740000
Buffer addr     : 0x824ebc51
Data Size       : 0x00890000
SF: 21757952 bytes @ 0x740000 Erased: OK
device 0 offset 0x740000, size 0x890000
SF: 8978432 bytes @ 0x740000 Written: OK
gpio: pin 167 (gpio 167) value is 0
ti_spi_set_speed: hz: 38400000, clock divider 1
__ti_qspi_set_mode: SPI flash mode=0x2000, SPI_RX_QUAD=0x2000
SF: Detected s25fl256s_64k with page size 256 Bytes, erase size 64 KiB, total 32 MiB, mapped at 5c000000
ti_spi_set_speed: hz: 38400000, clock divider 1
__ti_qspi_set_mode: SPI flash mode=0x2000, SPI_RX_QUAD=0x2000

Header Count  : 7, Current Count: 7
File System     : BIN
Partition name  : FPGA
Partition addr  : 0x00000000
Buff addr       : 0x82d7bc75
Data Size       : 0x002b501c
SF: 33554432 bytes @ 0x0 Erased: OK
device 0 offset 0x0, size 0x2b501c
SF: 2838556 bytes @ 0x0 Written: OK
gpio: pin 167 (gpio 167) value is 1

Sanion UR Update Complete!!!
switch to partitions #0, OK
mmc1(part 0) is current device

MMC erase: dev # 1, block # 2129920, count 2097152 ... 2097152 blocks erased: OK
Writing GPT: success!

Sanion UR Update Complete!!!
resetting ...