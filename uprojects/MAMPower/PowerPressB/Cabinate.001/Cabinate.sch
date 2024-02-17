EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATmega:ATmega128A-AU U1
U 1 1 602FDFA5
P 5340 3440
F 0 "U1" H 5810 1500 50  0000 C CNN
F 1 "ATmega128A-AU" H 5700 1430 50  0000 C CNN
F 2 "HeatEx03:TQFP64.Break" H 5340 3440 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8151-8-bit-AVR-ATmega128A_Datasheet.pdf" H 5340 3440 50  0001 C CNN
	1    5340 3440
	1    0    0    -1  
$EndComp
$Comp
L HeatEx03-cache:ULN2003A U2
U 1 1 60300D6A
P 3800 5050
F 0 "U2" H 3800 5717 50  0000 C CNN
F 1 "ULN2003A" H 3800 5626 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_LongPads" H 3850 4500 50  0001 L CNN
F 3 "" H 3900 4850 50  0001 C CNN
	1    3800 5050
	-1   0    0    1   
$EndComp
$Comp
L power:VCC #PWR0101
U 1 1 60306555
P 5390 1240
F 0 "#PWR0101" H 5390 1090 50  0001 C CNN
F 1 "VCC" H 5405 1413 50  0000 C CNN
F 2 "" H 5390 1240 50  0001 C CNN
F 3 "" H 5390 1240 50  0001 C CNN
	1    5390 1240
	1    0    0    -1  
$EndComp
Wire Wire Line
	5340 1440 5390 1440
Wire Wire Line
	5390 1240 5390 1440
Connection ~ 5390 1440
Wire Wire Line
	5390 1440 5440 1440
Wire Wire Line
	3320 5450 3400 5450
$Comp
L power:GND #PWR0102
U 1 1 60308247
P 3800 4310
F 0 "#PWR0102" H 3800 4060 50  0001 C CNN
F 1 "GND" H 3805 4137 50  0000 C CNN
F 2 "" H 3800 4310 50  0001 C CNN
F 3 "" H 3800 4310 50  0001 C CNN
	1    3800 4310
	-1   0    0    1   
$EndComp
Wire Wire Line
	3800 4310 3800 4450
$Comp
L power:GND #PWR0103
U 1 1 60308C8C
P 5340 5590
F 0 "#PWR0103" H 5340 5340 50  0001 C CNN
F 1 "GND" H 5345 5417 50  0000 C CNN
F 2 "" H 5340 5590 50  0001 C CNN
F 3 "" H 5340 5590 50  0001 C CNN
	1    5340 5590
	1    0    0    -1  
$EndComp
Wire Wire Line
	5340 5590 5340 5440
$Comp
L power:+12V #PWR0104
U 1 1 6030B607
P 3320 5620
F 0 "#PWR0104" H 3320 5470 50  0001 C CNN
F 1 "+12V" H 3335 5793 50  0000 C CNN
F 2 "" H 3320 5620 50  0001 C CNN
F 3 "" H 3320 5620 50  0001 C CNN
	1    3320 5620
	-1   0    0    1   
$EndComp
Wire Wire Line
	3320 5620 3320 5450
$Comp
L Regulator_Switching:KA5L0265RTU U3
U 1 1 6030CB8E
P 4980 -2070
F 0 "U3" H 5410 -2024 50  0000 L CNN
F 1 "KA5L0265RTU" H 4690 -1710 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-4_Vertical" H 5430 -2020 50  0001 L CIN
F 3 "http://www.onsemi.com/pub/Collateral/KA5L0265R-D.PDF" H 5030 -2070 50  0001 C CNN
	1    4980 -2070
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Coils:TRANSFORMER_QUADFILIAR TX1
U 1 1 6030E6DB
P 6530 -1740
F 0 "TX1" H 6530 -764 45  0000 C CNN
F 1 "txfr" H 6530 -848 45  0000 C CNN
F 2 "PERSONAL2:-INDUCTOR_MEDIUM" H 6530 -890 20  0001 C CNN
F 3 "" H 6530 -1740 50  0001 C CNN
F 4 "XXX-00000" H 6530 -943 60  0000 C CNN "Field4"
	1    6530 -1740
	1    0    0    -1  
$EndComp
Wire Wire Line
	6280 -2470 6280 -2440
$Comp
L Device:D_Small D1
U 1 1 6031751E
P 6010 -2270
F 0 "D1" V 6056 -2340 50  0000 R CNN
F 1 "FR107" V 5965 -2340 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" V 6010 -2270 50  0001 C CNN
F 3 "~" V 6010 -2270 50  0001 C CNN
	1    6010 -2270
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6010 -2370 6010 -2470
Connection ~ 6010 -2470
Wire Wire Line
	6010 -2470 6280 -2470
$Comp
L Device:R_Small R1
U 1 1 60318C21
P 6010 -1900
F 0 "R1" H 6069 -1854 50  0000 L CNN
F 1 "33K1W" H 6069 -1945 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 6010 -1900 50  0001 C CNN
F 3 "~" H 6010 -1900 50  0001 C CNN
	1    6010 -1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6010 -2000 6010 -2090
Wire Wire Line
	6010 -1800 6010 -1740
Wire Wire Line
	6010 -1740 6110 -1740
$Comp
L Device:C_Small C1
U 1 1 6031AB5D
P 5830 -1890
F 0 "C1" H 5810 -1940 50  0000 R CNN
F 1 "103/1KV" H 6120 -1830 39  0000 R CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W5.0mm_P5.00mm" H 5830 -1890 50  0001 C CNN
F 3 "~" H 5830 -1890 50  0001 C CNN
	1    5830 -1890
	-1   0    0    1   
$EndComp
Wire Wire Line
	5830 -1990 5830 -2090
Wire Wire Line
	5830 -2090 6010 -2090
Connection ~ 6010 -2090
Wire Wire Line
	6010 -2090 6010 -2170
Wire Wire Line
	5830 -1790 5830 -1740
Wire Wire Line
	5830 -1740 6010 -1740
Connection ~ 6010 -1740
$Comp
L Connector_Generic:Conn_01x12 J2
U 1 1 6031CCC1
P 10520 1420
F 0 "J2" H 10438 595 50  0000 C CNN
F 1 "Conn_01x12" H 10438 686 50  0000 C CNN
F 2 "Connector_Phoenix_MC_HighVoltage:PhoenixContact_MC_1,5_12-G-5.08_1x12_P5.08mm_Horizontal" H 10520 1420 50  0001 C CNN
F 3 "~" H 10520 1420 50  0001 C CNN
	1    10520 1420
	1    0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x12 J1
U 1 1 6031DC57
P 10410 5860
F 0 "J1" H 10328 5035 50  0000 C CNN
F 1 "Conn_01x12" H 10328 5126 50  0000 C CNN
F 2 "Connector_Phoenix_MC_HighVoltage:PhoenixContact_MC_1,5_12-G-5.08_1x12_P5.08mm_Horizontal" H 10410 5860 50  0001 C CNN
F 3 "~" H 10410 5860 50  0001 C CNN
	1    10410 5860
	1    0    0    1   
$EndComp
Text GLabel 9580 6260 0    50   Input ~ 0
+48V
$Comp
L Relay:SANYOU_SRD_Form_C K5
U 1 1 6034BF33
P 8890 3890
F 0 "K5" H 9170 3870 50  0000 L CNN
F 1 "SANYOU_SRD_Form_C" V 9310 3740 20  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_SANYOU_SRD_Series_Form_C" H 9340 3840 50  0001 L CNN
F 3 "http://www.sanyourelay.ca/public/products/pdf/SRD.pdf" H 8890 3890 50  0001 C CNN
	1    8890 3890
	1    0    0    -1  
$EndComp
$Comp
L Relay:SANYOU_SRD_Form_C K6
U 1 1 6034E51D
P 8890 4650
F 0 "K6" H 9170 4630 50  0000 L CNN
F 1 "SANYOU_SRD_Form_C" V 9310 4500 20  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_SANYOU_SRD_Series_Form_C" H 9340 4600 50  0001 L CNN
F 3 "http://www.sanyourelay.ca/public/products/pdf/SRD.pdf" H 8890 4650 50  0001 C CNN
	1    8890 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R2
U 1 1 60356024
P 4370 -2070
F 0 "R2" H 4429 -2024 50  0000 L CNN
F 1 "1M" V 4370 -2150 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 4370 -2070 50  0001 C CNN
F 3 "~" H 4370 -2070 50  0001 C CNN
	1    4370 -2070
	1    0    0    -1  
$EndComp
Wire Wire Line
	4370 -2170 4370 -2270
Wire Wire Line
	4370 -2270 4480 -2270
Wire Wire Line
	4370 -1970 4370 -1870
Wire Wire Line
	4370 -1870 4480 -1870
$Comp
L power:GND #PWR02
U 1 1 60358E3D
P 5280 -1570
F 0 "#PWR02" H 5280 -1820 50  0001 C CNN
F 1 "GND" H 5285 -1743 50  0000 C CNN
F 2 "" H 5280 -1570 50  0001 C CNN
F 3 "" H 5280 -1570 50  0001 C CNN
	1    5280 -1570
	1    0    0    -1  
$EndComp
Wire Wire Line
	5280 -1570 5280 -1670
Wire Wire Line
	3990 -2270 4370 -2270
Connection ~ 4370 -2270
$Comp
L power:GND #PWR01
U 1 1 6035E023
P 3990 -1890
F 0 "#PWR01" H 3990 -2140 50  0001 C CNN
F 1 "GND" H 3995 -2063 50  0000 C CNN
F 2 "" H 3990 -1890 50  0001 C CNN
F 3 "" H 3990 -1890 50  0001 C CNN
	1    3990 -1890
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Capacitors:10UF-POLAR-RADIAL-2.5MM-25V-20% C2
U 1 1 60362D5E
P 3990 -2170
F 0 "C2" H 4118 -2157 45  0000 L CNN
F 1 "10UF" H 4118 -2241 45  0000 L CNN
F 2 "Capacitors:CPOL-RADIAL-2.5MM-5MM" H 3990 -1920 20  0001 C CNN
F 3 "" H 3990 -2170 50  0001 C CNN
F 4 "CAP-08440" H 4118 -2304 20  0000 L CNN "Field4"
	1    3990 -2170
	1    0    0    -1  
$EndComp
Wire Wire Line
	3990 -1890 3990 -1970
Text GLabel 3990 -3200 0    50   Input ~ 0
+48V
$Comp
L Device:R_Small R3
U 1 1 6036D5F6
P 4370 -2510
F 0 "R3" H 4429 -2464 50  0000 L CNN
F 1 "47K1W" V 4370 -2590 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" H 4370 -2510 50  0001 C CNN
F 3 "~" H 4370 -2510 50  0001 C CNN
	1    4370 -2510
	1    0    0    -1  
$EndComp
Wire Wire Line
	4370 -2410 4370 -2270
Wire Wire Line
	4370 -2610 4370 -3200
Wire Wire Line
	4370 -3200 3990 -3200
Wire Wire Line
	5280 -2470 6010 -2470
Text GLabel 6000 -1600 0    50   Input ~ 0
+48V
Wire Wire Line
	6000 -1600 6110 -1600
Wire Wire Line
	6110 -1600 6110 -1740
Connection ~ 6110 -1740
Wire Wire Line
	6110 -1740 6280 -1740
Text Notes 6280 -1680 0    197  ~ 0
.
Text Notes 6660 -1680 0    197  ~ 0
.
$Comp
L power:GND #PWR03
U 1 1 6037ADB1
P 6870 -1700
F 0 "#PWR03" H 6870 -1950 50  0001 C CNN
F 1 "GND" H 6875 -1873 50  0000 C CNN
F 2 "" H 6870 -1700 50  0001 C CNN
F 3 "" H 6870 -1700 50  0001 C CNN
	1    6870 -1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6780 -1740 6870 -1740
Wire Wire Line
	6870 -1740 6870 -1700
$Comp
L Device:D_Small D3
U 1 1 6037CC35
P 7000 -2440
F 0 "D3" V 7046 -2510 50  0000 R CNN
F 1 "FR107" V 6955 -2510 50  0000 R CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" V 7000 -2440 50  0001 C CNN
F 3 "~" V 7000 -2440 50  0001 C CNN
	1    7000 -2440
	-1   0    0    1   
$EndComp
Wire Wire Line
	6900 -2440 6780 -2440
Wire Wire Line
	7100 -2440 7140 -2440
Wire Wire Line
	7300 -2440 7300 -2350
Wire Wire Line
	7300 -2050 7300 -1740
Wire Wire Line
	7300 -1740 6870 -1740
Connection ~ 6870 -1740
$Comp
L power:+12V #PWR04
U 1 1 603840D8
P 7300 -2500
F 0 "#PWR04" H 7300 -2650 50  0001 C CNN
F 1 "+12V" H 7315 -2327 50  0000 C CNN
F 2 "" H 7300 -2500 50  0001 C CNN
F 3 "" H 7300 -2500 50  0001 C CNN
	1    7300 -2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 -2500 7300 -2440
Connection ~ 7300 -2440
$Comp
L Device:CP C3
U 1 1 6038E1C8
P 7300 -2200
F 0 "C3" H 7418 -2154 50  0000 L CNN
F 1 "100uF" H 7418 -2245 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.80mm" H 7338 -2350 50  0001 C CNN
F 3 "~" H 7300 -2200 50  0001 C CNN
	1    7300 -2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 603919A6
P 6160 -2140
F 0 "#PWR0105" H 6160 -2390 50  0001 C CNN
F 1 "GND" H 6160 -2260 50  0000 C CNN
F 2 "" H 6160 -2140 50  0001 C CNN
F 3 "" H 6160 -2140 50  0001 C CNN
	1    6160 -2140
	1    0    0    -1  
$EndComp
Wire Wire Line
	6280 -2140 6160 -2140
$Comp
L Device:R_POT RV1
U 1 1 60395BCF
P 4510 -1200
F 0 "RV1" V 4395 -1200 50  0000 C CNN
F 1 "10K" V 4304 -1200 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 4510 -1200 50  0001 C CNN
F 3 "~" H 4510 -1200 50  0001 C CNN
	1    4510 -1200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4510 -1350 4510 -1630
Wire Wire Line
	4510 -1630 4370 -1630
Wire Wire Line
	4370 -1630 4370 -1870
Connection ~ 4370 -1870
$Comp
L power:+12V #PWR06
U 1 1 60399A80
P 4840 -1360
F 0 "#PWR06" H 4840 -1510 50  0001 C CNN
F 1 "+12V" H 4855 -1187 50  0000 C CNN
F 2 "" H 4840 -1360 50  0001 C CNN
F 3 "" H 4840 -1360 50  0001 C CNN
	1    4840 -1360
	1    0    0    -1  
$EndComp
Wire Wire Line
	4660 -1200 4840 -1200
Wire Wire Line
	4840 -1200 4840 -1360
$Comp
L Device:R_Small R4
U 1 1 6039C34F
P 4170 -1200
F 0 "R4" H 4229 -1154 50  0000 L CNN
F 1 "2K2" V 4170 -1280 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 4170 -1200 50  0001 C CNN
F 3 "~" H 4170 -1200 50  0001 C CNN
	1    4170 -1200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4270 -1200 4360 -1200
$Comp
L power:GND #PWR05
U 1 1 6039F761
P 3960 -1160
F 0 "#PWR05" H 3960 -1410 50  0001 C CNN
F 1 "GND" H 3965 -1333 50  0000 C CNN
F 2 "" H 3960 -1160 50  0001 C CNN
F 3 "" H 3960 -1160 50  0001 C CNN
	1    3960 -1160
	1    0    0    -1  
$EndComp
Wire Wire Line
	4070 -1200 3960 -1200
Wire Wire Line
	3960 -1200 3960 -1160
Wire Wire Line
	6280 -2040 6280 -2090
Wire Wire Line
	6280 -2090 6780 -2090
Wire Wire Line
	6780 -2090 6780 -2040
Wire Wire Line
	6780 -2090 7140 -2090
Wire Wire Line
	7140 -2090 7140 -2440
Connection ~ 6780 -2090
Connection ~ 7140 -2440
Wire Wire Line
	7140 -2440 7300 -2440
Text GLabel 4440 3600 0    50   Input ~ 0
Q6
Text GLabel 6040 2640 2    50   Input ~ 0
10
Wire Wire Line
	6040 2640 5940 2640
Text GLabel 6040 2740 2    50   Input ~ 0
11
Wire Wire Line
	6040 2740 5940 2740
Text GLabel 4350 5150 2    50   Input ~ 0
12
Text GLabel 6040 2840 2    50   Input ~ 0
12
Wire Wire Line
	6040 2840 5940 2840
Wire Wire Line
	4740 4740 4590 4740
Wire Wire Line
	4590 4740 4590 4650
Wire Wire Line
	4590 4650 4500 4650
Wire Wire Line
	4740 4640 4660 4640
Wire Wire Line
	4660 4640 4660 4750
Wire Wire Line
	4660 4750 4390 4750
Wire Wire Line
	4740 4840 4630 4840
Wire Wire Line
	4300 4840 4300 4850
Wire Wire Line
	4300 4850 4200 4850
Wire Wire Line
	4740 5040 4680 5040
Wire Wire Line
	4580 5040 4580 4950
Wire Wire Line
	4580 4950 4200 4950
Text GLabel 4350 5050 2    50   Input ~ 0
10
Wire Wire Line
	4350 5050 4200 5050
Wire Wire Line
	4350 5150 4200 5150
Text GLabel 6040 2940 2    50   Input ~ 0
13
Wire Wire Line
	6040 2940 5940 2940
Text GLabel 4350 5250 2    50   Input ~ 0
13
Wire Wire Line
	4350 5250 4200 5250
$Comp
L SparkFun-Displays:LCD-16X2SILK LCD1
U 1 1 6041146B
P 2880 3110
F 0 "LCD1" H 2772 2050 45  0000 C CNN
F 1 "LCD-16X2SILK" H 2772 2134 45  0000 C CNN
F 2 "Displays:LCD-16X2" H 2880 4160 20  0001 C CNN
F 3 "" H 2880 3110 50  0001 C CNN
F 4 "LCD-00255" H 2772 2229 60  0000 C CNN "Field4"
	1    2880 3110
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 60327C6C
P 3450 4020
F 0 "#PWR0108" H 3450 3770 50  0001 C CNN
F 1 "GND" H 3455 3847 50  0000 C CNN
F 2 "" H 3450 4020 50  0001 C CNN
F 3 "" H 3450 4020 50  0001 C CNN
	1    3450 4020
	1    0    0    -1  
$EndComp
Wire Wire Line
	3280 3910 3450 3910
Wire Wire Line
	3450 3910 3450 4020
$Comp
L power:VCC #PWR0109
U 1 1 6032C71D
P 3430 3810
F 0 "#PWR0109" H 3430 3660 50  0001 C CNN
F 1 "VCC" H 3445 3983 50  0000 C CNN
F 2 "" H 3430 3810 50  0001 C CNN
F 3 "" H 3430 3810 50  0001 C CNN
	1    3430 3810
	0    1    1    0   
$EndComp
Wire Wire Line
	3430 3810 3280 3810
$Comp
L Device:R_Small R11
U 1 1 60331760
P 3710 3810
F 0 "R11" H 3769 3856 50  0000 L CNN
F 1 "3K3" V 3710 3730 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 3710 3810 50  0001 C CNN
F 3 "~" H 3710 3810 50  0001 C CNN
	1    3710 3810
	1    0    0    -1  
$EndComp
Wire Wire Line
	3710 3910 3510 3910
Connection ~ 3450 3910
Wire Wire Line
	3710 3710 3280 3710
Text GLabel 3590 3610 2    50   Input ~ 0
RS
Wire Wire Line
	3590 3610 3280 3610
$Comp
L power:GND #PWR0110
U 1 1 60340A31
P 4000 3520
F 0 "#PWR0110" H 4000 3270 50  0001 C CNN
F 1 "GND" H 4005 3347 50  0000 C CNN
F 2 "" H 4000 3520 50  0001 C CNN
F 3 "" H 4000 3520 50  0001 C CNN
	1    4000 3520
	1    0    0    -1  
$EndComp
Wire Wire Line
	3280 3510 4000 3510
Wire Wire Line
	4000 3510 4000 3520
Text GLabel 3590 3410 2    50   Input ~ 0
E
Wire Wire Line
	3590 3410 3280 3410
Text GLabel 3450 2910 2    50   Input ~ 0
D4
Wire Wire Line
	3450 2910 3280 2910
Text GLabel 3450 2810 2    50   Input ~ 0
D5
Wire Wire Line
	3450 2810 3280 2810
Text GLabel 3450 2710 2    50   Input ~ 0
D6
Wire Wire Line
	3450 2710 3280 2710
Text GLabel 3450 2610 2    50   Input ~ 0
D7
Wire Wire Line
	3450 2610 3280 2610
Text GLabel 3450 2410 2    50   Input ~ 0
LED-
Wire Wire Line
	3450 2410 3280 2410
Text GLabel 8240 4200 0    50   Input ~ 0
REL5
Wire Wire Line
	8240 4200 8690 4200
Wire Wire Line
	8690 4200 8690 4190
Text GLabel 8280 5000 0    50   Input ~ 0
REL6
Wire Wire Line
	8280 5000 8690 5000
Wire Wire Line
	8690 5000 8690 4950
Text GLabel 3250 4650 0    50   Input ~ 0
REL1
Wire Wire Line
	3250 4650 3400 4650
Text GLabel 6030 1940 2    50   Input ~ 0
RS
Text GLabel 6020 1740 2    50   Input ~ 0
E
Wire Wire Line
	6020 1740 5940 1740
Wire Wire Line
	6030 1940 5940 1940
Text GLabel 6080 2140 2    50   Input ~ 0
D4
Text GLabel 6080 2240 2    50   Input ~ 0
D5
Text GLabel 6080 2340 2    50   Input ~ 0
D6
Text GLabel 6080 2440 2    50   Input ~ 0
D7
Wire Wire Line
	6080 2140 5940 2140
Wire Wire Line
	6080 2240 5940 2240
Wire Wire Line
	6080 2340 5940 2340
Wire Wire Line
	6080 2440 5940 2440
Text GLabel 3250 4750 0    50   Input ~ 0
REL2
Wire Wire Line
	3250 4750 3400 4750
Text GLabel 3250 4850 0    50   Input ~ 0
REL3
Wire Wire Line
	3250 4850 3400 4850
Text GLabel 3250 4950 0    50   Input ~ 0
REL4
Wire Wire Line
	3250 4950 3400 4950
Text GLabel 3250 5050 0    50   Input ~ 0
REL5
Wire Wire Line
	3250 5050 3400 5050
Text GLabel 3250 5150 0    50   Input ~ 0
REL6
Wire Wire Line
	3250 5150 3400 5150
$Comp
L power:+12V #PWR0111
U 1 1 603FCACA
P 3990 -2550
F 0 "#PWR0111" H 3990 -2700 50  0001 C CNN
F 1 "+12V" H 4005 -2377 50  0000 C CNN
F 2 "" H 3990 -2550 50  0001 C CNN
F 3 "" H 3990 -2550 50  0001 C CNN
	1    3990 -2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3990 -2550 3990 -2270
Connection ~ 3990 -2270
$Comp
L SparkFun-Electromechanical:BUZZER-PTH LS1
U 1 1 60407E6C
P 1900 5060
F 0 "LS1" H 2153 5185 45  0000 L CNN
F 1 "BUZZER-PTH" H 2153 5101 45  0000 L CNN
F 2 "Electromechanical:BUZZER-12MM" H 1900 5360 20  0001 C CNN
F 3 "" H 1900 5060 50  0001 C CNN
F 4 "COMP-08253" H 2153 5006 60  0000 L CNN "Field4"
	1    1900 5060
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R12
U 1 1 60409252
P 2870 5250
F 0 "R12" H 2929 5296 50  0000 L CNN
F 1 "100E" V 2800 5170 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 2870 5250 50  0001 C CNN
F 3 "~" H 2870 5250 50  0001 C CNN
	1    2870 5250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2970 5250 3400 5250
Wire Wire Line
	2770 5250 2000 5250
Wire Wire Line
	2000 5250 2000 5160
$Comp
L power:+12V #PWR08
U 1 1 604191D1
P 1900 5220
F 0 "#PWR08" H 1900 5070 50  0001 C CNN
F 1 "+12V" H 1915 5393 50  0000 C CNN
F 2 "" H 1900 5220 50  0001 C CNN
F 3 "" H 1900 5220 50  0001 C CNN
	1    1900 5220
	-1   0    0    1   
$EndComp
Wire Wire Line
	1900 5220 1900 5160
$Comp
L Device:R_Small R13
U 1 1 604260D0
P 1170 4130
F 0 "R13" H 1229 4176 50  0000 L CNN
F 1 "3K3" V 1110 4060 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 1170 4130 50  0001 C CNN
F 3 "~" H 1170 4130 50  0001 C CNN
	1    1170 4130
	0    1    1    0   
$EndComp
$Comp
L Device:CP C4
U 1 1 60427640
P 1410 4290
F 0 "C4" H 1528 4336 50  0000 L CNN
F 1 "CP" H 1528 4245 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P2.00mm" H 1448 4140 50  0001 C CNN
F 3 "~" H 1410 4290 50  0001 C CNN
	1    1410 4290
	1    0    0    -1  
$EndComp
Wire Wire Line
	1270 4130 1410 4130
Wire Wire Line
	1410 4130 1410 4140
$Comp
L power:GND #PWR09
U 1 1 60432349
P 1410 4550
F 0 "#PWR09" H 1410 4300 50  0001 C CNN
F 1 "GND" H 1415 4377 50  0000 C CNN
F 2 "" H 1410 4550 50  0001 C CNN
F 3 "" H 1410 4550 50  0001 C CNN
	1    1410 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1410 4550 1410 4440
Text GLabel 1720 4130 2    50   Input ~ 0
ADC7
Wire Wire Line
	1720 4130 1410 4130
Connection ~ 1410 4130
Text GLabel 4570 4240 0    50   Input ~ 0
ADC7
Wire Wire Line
	4570 4240 4740 4240
Text GLabel 4570 4040 0    50   Input ~ 0
ADC5
Text GLabel 960  4130 0    50   Input ~ 0
S1
Wire Wire Line
	960  4130 1070 4130
Wire Wire Line
	4570 4040 4740 4040
$Comp
L Device:R_Small R19
U 1 1 6058E0F0
P 1180 3360
F 0 "R19" H 1239 3406 50  0000 L CNN
F 1 "3K3" V 1120 3290 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 1180 3360 50  0001 C CNN
F 3 "~" H 1180 3360 50  0001 C CNN
	1    1180 3360
	0    1    1    0   
$EndComp
$Comp
L Device:CP C5
U 1 1 6058E0F6
P 1420 3520
F 0 "C5" H 1538 3566 50  0000 L CNN
F 1 "CP" H 1538 3475 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P2.00mm" H 1458 3370 50  0001 C CNN
F 3 "~" H 1420 3520 50  0001 C CNN
	1    1420 3520
	1    0    0    -1  
$EndComp
Wire Wire Line
	1280 3360 1420 3360
Wire Wire Line
	1420 3360 1420 3370
$Comp
L power:GND #PWR014
U 1 1 6058E0FE
P 1420 3780
F 0 "#PWR014" H 1420 3530 50  0001 C CNN
F 1 "GND" H 1425 3607 50  0000 C CNN
F 2 "" H 1420 3780 50  0001 C CNN
F 3 "" H 1420 3780 50  0001 C CNN
	1    1420 3780
	1    0    0    -1  
$EndComp
Wire Wire Line
	1420 3780 1420 3670
Text GLabel 1730 3360 2    50   Input ~ 0
ADC5
Wire Wire Line
	1730 3360 1420 3360
Connection ~ 1420 3360
Text GLabel 970  3360 0    50   Input ~ 0
S2
Wire Wire Line
	970  3360 1080 3360
Text GLabel 4570 3840 0    50   Input ~ 0
Q7
Wire Wire Line
	4570 3840 4740 3840
Wire Wire Line
	4440 3740 4740 3740
Text GLabel 4440 3740 0    50   Input ~ 0
Q5
Wire Wire Line
	4440 3600 4570 3600
Wire Wire Line
	4570 3600 4570 3640
Wire Wire Line
	4570 3640 4740 3640
Text GLabel 4580 3940 0    50   Input ~ 0
DOORT
Wire Wire Line
	4580 3940 4740 3940
Text GLabel 4550 4140 0    50   Input ~ 0
WATERT
Wire Wire Line
	4550 4140 4740 4140
$Comp
L Regulator_Linear:LM7805_TO220 U6
U 1 1 603D55EE
P 1380 2240
F 0 "U6" H 1380 2482 50  0000 C CNN
F 1 "LM7805_TO220" H 1380 2391 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 1380 2465 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM7805.pdf" H 1380 2190 50  0001 C CNN
	1    1380 2240
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C6
U 1 1 603D9CB9
P 990 2390
F 0 "C6" H 1082 2436 50  0000 L CNN
F 1 "C_Small" H 1082 2345 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W5.0mm_P5.00mm" H 990 2390 50  0001 C CNN
F 3 "~" H 990 2390 50  0001 C CNN
	1    990  2390
	1    0    0    -1  
$EndComp
Wire Wire Line
	990  2290 990  2240
Wire Wire Line
	990  2240 1080 2240
$Comp
L Device:C_Small C7
U 1 1 603EA1E9
P 1760 2370
F 0 "C7" H 1852 2416 50  0000 L CNN
F 1 "C_Small" H 1852 2325 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W5.0mm_P5.00mm" H 1760 2370 50  0001 C CNN
F 3 "~" H 1760 2370 50  0001 C CNN
	1    1760 2370
	1    0    0    -1  
$EndComp
Wire Wire Line
	1760 2270 1760 2240
Wire Wire Line
	1760 2240 1680 2240
Wire Wire Line
	990  2490 990  2540
Wire Wire Line
	990  2540 1380 2540
Wire Wire Line
	1760 2470 1760 2540
Wire Wire Line
	1760 2540 1380 2540
Connection ~ 1380 2540
$Comp
L power:GND #PWR016
U 1 1 6041BE7E
P 1380 2540
F 0 "#PWR016" H 1380 2290 50  0001 C CNN
F 1 "GND" H 1385 2367 50  0000 C CNN
F 2 "" H 1380 2540 50  0001 C CNN
F 3 "" H 1380 2540 50  0001 C CNN
	1    1380 2540
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR015
U 1 1 6041C656
P 880 2240
F 0 "#PWR015" H 880 2090 50  0001 C CNN
F 1 "+12V" H 895 2413 50  0000 C CNN
F 2 "" H 880 2240 50  0001 C CNN
F 3 "" H 880 2240 50  0001 C CNN
	1    880  2240
	0    -1   -1   0   
$EndComp
Wire Wire Line
	880  2240 990  2240
Connection ~ 990  2240
$Comp
L power:VCC #PWR017
U 1 1 6042E3CB
P 1960 2240
F 0 "#PWR017" H 1960 2090 50  0001 C CNN
F 1 "VCC" H 1975 2413 50  0000 C CNN
F 2 "" H 1960 2240 50  0001 C CNN
F 3 "" H 1960 2240 50  0001 C CNN
	1    1960 2240
	0    1    1    0   
$EndComp
Wire Wire Line
	1960 2240 1760 2240
Connection ~ 1760 2240
Text GLabel 4420 3480 0    50   Input ~ 0
Q4
Wire Wire Line
	4420 3480 4740 3480
Wire Wire Line
	4740 3480 4740 3540
$Comp
L Transistor_BJT:PN2222A Q5
U 1 1 604F1D6D
P 3090 1420
F 0 "Q5" H 3280 1466 50  0000 L CNN
F 1 "PN2222A" H 3280 1375 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92L_Inline_Wide" H 3290 1345 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/PN/PN2222A.pdf" H 3090 1420 50  0001 L CNN
	1    3090 1420
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR019
U 1 1 604F3157
P 3570 2510
F 0 "#PWR019" H 3570 2360 50  0001 C CNN
F 1 "VCC" H 3585 2683 50  0000 C CNN
F 2 "" H 3570 2510 50  0001 C CNN
F 3 "" H 3570 2510 50  0001 C CNN
	1    3570 2510
	0    1    1    0   
$EndComp
Wire Wire Line
	3280 2510 3570 2510
$Comp
L Device:R_Small R21
U 1 1 60506600
P 3360 1180
F 0 "R21" H 3419 1226 50  0000 L CNN
F 1 "1k" V 3300 1110 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 3360 1180 50  0001 C CNN
F 3 "~" H 3360 1180 50  0001 C CNN
	1    3360 1180
	0    1    1    0   
$EndComp
Wire Wire Line
	3260 1180 3190 1180
Wire Wire Line
	3190 1180 3190 1220
Text GLabel 3730 1180 2    50   Input ~ 0
LED-
$Comp
L power:GND #PWR018
U 1 1 6052D564
P 3190 1680
F 0 "#PWR018" H 3190 1430 50  0001 C CNN
F 1 "GND" H 3195 1507 50  0000 C CNN
F 2 "" H 3190 1680 50  0001 C CNN
F 3 "" H 3190 1680 50  0001 C CNN
	1    3190 1680
	1    0    0    -1  
$EndComp
Wire Wire Line
	3190 1680 3190 1650
$Comp
L Device:R_Small R22
U 1 1 605411E2
P 3670 1500
F 0 "R22" H 3729 1546 50  0000 L CNN
F 1 "3K3" V 3610 1430 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 3670 1500 50  0001 C CNN
F 3 "~" H 3670 1500 50  0001 C CNN
	1    3670 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3670 1400 3670 1180
Wire Wire Line
	3460 1180 3670 1180
Wire Wire Line
	3730 1180 3670 1180
Wire Wire Line
	3670 1180 3670 1190
Connection ~ 3670 1180
Wire Wire Line
	3670 1600 3670 1650
Wire Wire Line
	3670 1650 3190 1650
Connection ~ 3190 1650
Wire Wire Line
	3190 1650 3190 1620
$Comp
L Device:R_Small R20
U 1 1 6057DFE5
P 2750 1420
F 0 "R20" H 2809 1466 50  0000 L CNN
F 1 "3K3" V 2690 1350 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 2750 1420 50  0001 C CNN
F 3 "~" H 2750 1420 50  0001 C CNN
	1    2750 1420
	0    1    1    0   
$EndComp
Wire Wire Line
	2850 1420 2890 1420
Text GLabel 2580 1420 0    50   Input ~ 0
BKLED
Wire Wire Line
	2580 1420 2650 1420
Text GLabel 6830 -2260 2    50   Input ~ 0
+48V
Wire Wire Line
	6780 -2260 6830 -2260
Wire Wire Line
	6780 -2140 6780 -2260
Wire Wire Line
	9190 3590 9570 3590
Wire Wire Line
	9570 3590 9570 1120
Wire Wire Line
	9570 1120 10320 1120
Wire Wire Line
	9090 4190 9620 4190
Wire Wire Line
	9620 4190 9620 1020
Wire Wire Line
	9620 1020 10320 1020
Wire Wire Line
	9190 4350 9700 4350
Wire Wire Line
	9700 4350 9700 920 
Wire Wire Line
	9700 920  10320 920 
Wire Wire Line
	9090 4950 9780 4950
Wire Wire Line
	9780 4950 9780 820 
Wire Wire Line
	9780 820  10320 820 
$Comp
L power:+12V #PWR0112
U 1 1 603F27E9
P 8690 4350
F 0 "#PWR0112" H 8690 4200 50  0001 C CNN
F 1 "+12V" H 8705 4523 50  0000 C CNN
F 2 "" H 8690 4350 50  0001 C CNN
F 3 "" H 8690 4350 50  0001 C CNN
	1    8690 4350
	0    -1   -1   0   
$EndComp
$Comp
L power:+12V #PWR0113
U 1 1 603F3B6D
P 8690 3590
F 0 "#PWR0113" H 8690 3440 50  0001 C CNN
F 1 "+12V" H 8705 3763 50  0000 C CNN
F 2 "" H 8690 3590 50  0001 C CNN
F 3 "" H 8690 3590 50  0001 C CNN
	1    8690 3590
	0    -1   -1   0   
$EndComp
Text GLabel 6050 4040 2    50   Input ~ 0
BKLED
Wire Wire Line
	6050 4040 5940 4040
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 604357AC
P 9510 6620
F 0 "J3" V 9382 6700 50  0000 L CNN
F 1 "Conn_01x02" V 9473 6700 50  0000 L CNN
F 2 "Connector_Phoenix_MC_HighVoltage:PhoenixContact_MC_1,5_2-G-5.08_1x02_P5.08mm_Horizontal" H 9510 6620 50  0001 C CNN
F 3 "~" H 9510 6620 50  0001 C CNN
	1    9510 6620
	0    1    1    0   
$EndComp
Wire Wire Line
	9510 6420 10210 6420
Wire Wire Line
	10210 6420 10210 6360
Text GLabel 6040 3040 2    50   Input ~ 0
ENC1
Text GLabel 6040 3140 2    50   Input ~ 0
ENC2
Text GLabel 6040 3240 2    50   Input ~ 0
ENC3
Wire Wire Line
	6040 3040 5940 3040
Wire Wire Line
	6040 3140 5940 3140
Wire Wire Line
	6040 3240 5940 3240
Text GLabel 6040 3340 2    50   Input ~ 0
ENC4
Wire Wire Line
	6040 3340 5940 3340
$Comp
L Connector_Generic:Conn_01x07 J4
U 1 1 6068D6D7
P 7840 5220
F 0 "J4" H 7920 5262 50  0000 L CNN
F 1 "Conn_01x07" H 7920 5171 50  0000 L CNN
F 2 "Connector_JST:JST_XH_B7B-XH-A_1x07_P2.50mm_Vertical" H 7840 5220 50  0001 C CNN
F 3 "~" H 7840 5220 50  0001 C CNN
	1    7840 5220
	1    0    0    -1  
$EndComp
Text GLabel 7530 5120 0    50   Input ~ 0
10
Wire Wire Line
	7530 5120 7640 5120
Text GLabel 7530 5020 0    50   Input ~ 0
12
Wire Wire Line
	7530 5020 7640 5020
Text GLabel 4680 5550 3    50   Input ~ 0
8
Wire Wire Line
	4680 5550 4680 5040
Connection ~ 4680 5040
Wire Wire Line
	4680 5040 4580 5040
Text GLabel 4580 5610 3    50   Input ~ 0
6
Wire Wire Line
	4580 5610 4580 5120
Wire Wire Line
	4580 5120 4630 5120
Wire Wire Line
	4630 5120 4630 4840
Connection ~ 4630 4840
Wire Wire Line
	4630 4840 4300 4840
Text GLabel 4390 4550 1    50   Input ~ 0
4
Wire Wire Line
	4390 4550 4390 4750
Connection ~ 4390 4750
Wire Wire Line
	4390 4750 4200 4750
Text GLabel 4500 4550 1    50   Input ~ 0
5
Wire Wire Line
	4500 4550 4500 4650
Connection ~ 4500 4650
Wire Wire Line
	4500 4650 4200 4650
Text GLabel 7480 5220 0    50   Input ~ 0
8
Wire Wire Line
	7480 5220 7640 5220
Text GLabel 7480 5320 0    50   Input ~ 0
6
Wire Wire Line
	7480 5320 7640 5320
Text GLabel 7480 5420 0    50   Input ~ 0
4
Wire Wire Line
	7480 5420 7640 5420
Text GLabel 7480 5520 0    50   Input ~ 0
5
Wire Wire Line
	7480 5520 7640 5520
$Comp
L power:GND #PWR0119
U 1 1 607BEE34
P 7260 4980
F 0 "#PWR0119" H 7260 4730 50  0001 C CNN
F 1 "GND" H 7265 4807 50  0000 C CNN
F 2 "" H 7260 4980 50  0001 C CNN
F 3 "" H 7260 4980 50  0001 C CNN
	1    7260 4980
	1    0    0    -1  
$EndComp
Wire Wire Line
	7260 4980 7260 4920
Wire Wire Line
	7260 4920 7640 4920
$Comp
L Connector_Generic:Conn_01x05 J5
U 1 1 607DF0EB
P 7850 4470
F 0 "J5" H 7930 4512 50  0000 L CNN
F 1 "Conn_01x05" H 7930 4421 50  0000 L CNN
F 2 "Connector_JST:JST_XH_B5B-XH-A_1x05_P2.50mm_Vertical" H 7850 4470 50  0001 C CNN
F 3 "~" H 7850 4470 50  0001 C CNN
	1    7850 4470
	1    0    0    -1  
$EndComp
Text GLabel 7540 4570 0    50   Input ~ 0
ENC1
Wire Wire Line
	7540 4270 7650 4270
Text GLabel 7540 4370 0    50   Input ~ 0
ENC2
Wire Wire Line
	7540 4370 7650 4370
Text GLabel 7540 4470 0    50   Input ~ 0
ENC3
Wire Wire Line
	7540 4470 7650 4470
Text GLabel 7540 4270 0    50   Input ~ 0
ENC4
Wire Wire Line
	7540 4570 7650 4570
$Comp
L power:GND #PWR0120
U 1 1 6085212D
P 7480 4680
F 0 "#PWR0120" H 7480 4430 50  0001 C CNN
F 1 "GND" H 7485 4507 50  0000 C CNN
F 2 "" H 7480 4680 50  0001 C CNN
F 3 "" H 7480 4680 50  0001 C CNN
	1    7480 4680
	1    0    0    -1  
$EndComp
Wire Wire Line
	7480 4680 7480 4670
Wire Wire Line
	7480 4670 7650 4670
Text GLabel 4740 4940 0    24   Input ~ 0
DLS
$Comp
L power:GND #PWR0121
U 1 1 60A1DC05
P 10140 1960
F 0 "#PWR0121" H 10140 1710 50  0001 C CNN
F 1 "GND" H 10145 1787 50  0000 C CNN
F 2 "" H 10140 1960 50  0001 C CNN
F 3 "" H 10140 1960 50  0001 C CNN
	1    10140 1960
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R25
U 1 1 60A48838
P 3950 3940
F 0 "R25" H 4009 3986 50  0000 L CNN
F 1 "3K3" V 3950 3860 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P15.24mm_Horizontal" H 3950 3940 50  0001 C CNN
F 3 "~" H 3950 3940 50  0001 C CNN
	1    3950 3940
	1    0    0    -1  
$EndComp
Text GLabel 3990 3800 2    50   Input ~ 0
E
Wire Wire Line
	3990 3800 3950 3800
Wire Wire Line
	3950 3800 3950 3840
Wire Wire Line
	3950 4040 3510 4040
Wire Wire Line
	3510 4040 3510 3910
Connection ~ 3510 3910
Wire Wire Line
	3510 3910 3450 3910
$Comp
L Device:D_Small D2
U 1 1 6032A636
P 10040 6260
F 0 "D2" H 9930 6290 50  0000 C CNN
F 1 "D_Small" H 9830 6230 50  0000 C CNN
F 2 "Diode_THT:D_DO-27_P15.24mm_Horizontal" V 10040 6260 50  0001 C CNN
F 3 "~" V 10040 6260 50  0001 C CNN
	1    10040 6260
	1    0    0    -1  
$EndComp
Wire Wire Line
	9580 6260 9940 6260
$Comp
L Isolator:PC817 U4
U 1 1 6047B3C9
P 7940 1310
F 0 "U4" H 7940 1635 50  0000 C CNN
F 1 "PC817" H 7940 1544 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 7740 1110 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 7940 1310 50  0001 L CNN
	1    7940 1310
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small R5
U 1 1 6047D2E4
P 8410 1410
F 0 "R5" H 8469 1456 50  0000 L CNN
F 1 "3K3" V 8410 1330 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 8410 1410 50  0001 C CNN
F 3 "~" H 8410 1410 50  0001 C CNN
	1    8410 1410
	0    1    1    0   
$EndComp
Wire Wire Line
	8310 1410 8240 1410
Wire Wire Line
	8320 1210 8240 1210
Text GLabel 8900 1410 2    50   Input ~ 0
A1
$Comp
L power:GND #PWR0107
U 1 1 604B2CD5
P 7550 1450
F 0 "#PWR0107" H 7550 1200 50  0001 C CNN
F 1 "GND" H 7555 1277 50  0000 C CNN
F 2 "" H 7550 1450 50  0001 C CNN
F 3 "" H 7550 1450 50  0001 C CNN
	1    7550 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7640 1410 7550 1410
Wire Wire Line
	7550 1410 7550 1450
$Comp
L Connector_Generic:Conn_01x05 J6
U 1 1 604C2FAC
P 6510 1410
F 0 "J6" H 6590 1452 50  0000 L CNN
F 1 "Conn_01x05" H 6590 1361 50  0000 L CNN
F 2 "Connector_JST:JST_XH_B5B-XH-A_1x05_P2.50mm_Vertical" H 6510 1410 50  0001 C CNN
F 3 "~" H 6510 1410 50  0001 C CNN
	1    6510 1410
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 604D447E
P 6780 1690
F 0 "#PWR0114" H 6780 1440 50  0001 C CNN
F 1 "GND" H 6785 1517 50  0000 C CNN
F 2 "" H 6780 1690 50  0001 C CNN
F 3 "" H 6780 1690 50  0001 C CNN
	1    6780 1690
	1    0    0    -1  
$EndComp
Wire Wire Line
	6710 1610 6780 1610
Wire Wire Line
	6780 1610 6780 1690
Wire Wire Line
	6710 1210 7640 1210
Wire Wire Line
	10140 1960 10140 1920
Wire Wire Line
	10140 1920 10320 1920
Text GLabel 10190 1220 0    50   Input ~ 0
A1
Wire Wire Line
	10190 1220 10320 1220
$Comp
L power:+24V #PWR0106
U 1 1 60523349
P 10250 1820
F 0 "#PWR0106" H 10250 1670 50  0001 C CNN
F 1 "+24V" V 10265 1948 50  0000 L CNN
F 2 "" H 10250 1820 50  0001 C CNN
F 3 "" H 10250 1820 50  0001 C CNN
	1    10250 1820
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10250 1820 10320 1820
$Comp
L power:+24V #PWR0115
U 1 1 605339C4
P 8320 1210
F 0 "#PWR0115" H 8320 1060 50  0001 C CNN
F 1 "+24V" V 8335 1338 50  0000 L CNN
F 2 "" H 8320 1210 50  0001 C CNN
F 3 "" H 8320 1210 50  0001 C CNN
	1    8320 1210
	0    1    1    0   
$EndComp
$Comp
L Isolator:PC817 U5
U 1 1 6053F098
P 7940 1840
F 0 "U5" H 7940 2165 50  0000 C CNN
F 1 "PC817" H 7940 2074 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 7740 1640 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 7940 1840 50  0001 L CNN
	1    7940 1840
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small R6
U 1 1 6053F09E
P 8410 1940
F 0 "R6" H 8469 1986 50  0000 L CNN
F 1 "3K3" V 8410 1860 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 8410 1940 50  0001 C CNN
F 3 "~" H 8410 1940 50  0001 C CNN
	1    8410 1940
	0    1    1    0   
$EndComp
Wire Wire Line
	8310 1940 8240 1940
Wire Wire Line
	8320 1740 8240 1740
Text GLabel 8910 1940 2    50   Input ~ 0
B1
$Comp
L power:GND #PWR0116
U 1 1 6053F0A8
P 7550 1980
F 0 "#PWR0116" H 7550 1730 50  0001 C CNN
F 1 "GND" H 7555 1807 50  0000 C CNN
F 2 "" H 7550 1980 50  0001 C CNN
F 3 "" H 7550 1980 50  0001 C CNN
	1    7550 1980
	1    0    0    -1  
$EndComp
Wire Wire Line
	7640 1940 7550 1940
Wire Wire Line
	7550 1940 7550 1980
$Comp
L power:+24V #PWR0117
U 1 1 6053F0B1
P 8320 1740
F 0 "#PWR0117" H 8320 1590 50  0001 C CNN
F 1 "+24V" V 8335 1868 50  0000 L CNN
F 2 "" H 8320 1740 50  0001 C CNN
F 3 "" H 8320 1740 50  0001 C CNN
	1    8320 1740
	0    1    1    0   
$EndComp
Wire Wire Line
	7640 1740 7360 1740
Wire Wire Line
	7360 1740 7360 1310
Wire Wire Line
	7360 1310 6710 1310
$Comp
L Isolator:PC817 U7
U 1 1 6056225F
P 7950 2350
F 0 "U7" H 7950 2675 50  0000 C CNN
F 1 "PC817" H 7950 2584 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 7750 2150 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 7950 2350 50  0001 L CNN
	1    7950 2350
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small R7
U 1 1 60562265
P 8420 2450
F 0 "R7" H 8479 2496 50  0000 L CNN
F 1 "3K3" V 8420 2370 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 8420 2450 50  0001 C CNN
F 3 "~" H 8420 2450 50  0001 C CNN
	1    8420 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	8320 2450 8250 2450
Wire Wire Line
	8330 2250 8250 2250
Text GLabel 8930 2450 2    50   Input ~ 0
A2
$Comp
L power:GND #PWR0118
U 1 1 6056226F
P 7560 2490
F 0 "#PWR0118" H 7560 2240 50  0001 C CNN
F 1 "GND" H 7565 2317 50  0000 C CNN
F 2 "" H 7560 2490 50  0001 C CNN
F 3 "" H 7560 2490 50  0001 C CNN
	1    7560 2490
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 2450 7560 2450
Wire Wire Line
	7560 2450 7560 2490
$Comp
L power:+24V #PWR0122
U 1 1 60562278
P 8330 2250
F 0 "#PWR0122" H 8330 2100 50  0001 C CNN
F 1 "+24V" V 8345 2378 50  0000 L CNN
F 2 "" H 8330 2250 50  0001 C CNN
F 3 "" H 8330 2250 50  0001 C CNN
	1    8330 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	7650 2250 7300 2250
Wire Wire Line
	7300 2250 7300 1410
Wire Wire Line
	7300 1410 6710 1410
Text GLabel 10190 1320 0    50   Input ~ 0
B1
Wire Wire Line
	10190 1320 10320 1320
Text GLabel 10180 1420 0    50   Input ~ 0
A2
Wire Wire Line
	10180 1420 10320 1420
$Comp
L Isolator:PC817 U8
U 1 1 605B4D10
P 7950 2880
F 0 "U8" H 7950 3205 50  0000 C CNN
F 1 "PC817" H 7950 3114 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 7750 2680 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 7950 2880 50  0001 L CNN
	1    7950 2880
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small R8
U 1 1 605B4D16
P 8420 2980
F 0 "R8" H 8479 3026 50  0000 L CNN
F 1 "3K3" V 8420 2900 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 8420 2980 50  0001 C CNN
F 3 "~" H 8420 2980 50  0001 C CNN
	1    8420 2980
	0    1    1    0   
$EndComp
Wire Wire Line
	8320 2980 8250 2980
Wire Wire Line
	8330 2780 8250 2780
Text GLabel 8950 2980 2    50   Input ~ 0
B2
$Comp
L power:GND #PWR0123
U 1 1 605B4D20
P 7560 3020
F 0 "#PWR0123" H 7560 2770 50  0001 C CNN
F 1 "GND" H 7565 2847 50  0000 C CNN
F 2 "" H 7560 3020 50  0001 C CNN
F 3 "" H 7560 3020 50  0001 C CNN
	1    7560 3020
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 2980 7560 2980
Wire Wire Line
	7560 2980 7560 3020
$Comp
L power:+24V #PWR0124
U 1 1 605B4D29
P 8330 2780
F 0 "#PWR0124" H 8330 2630 50  0001 C CNN
F 1 "+24V" V 8345 2908 50  0000 L CNN
F 2 "" H 8330 2780 50  0001 C CNN
F 3 "" H 8330 2780 50  0001 C CNN
	1    8330 2780
	0    1    1    0   
$EndComp
Wire Wire Line
	7650 2780 7060 2780
Wire Wire Line
	7060 2780 7060 1510
Wire Wire Line
	7060 1510 6710 1510
Text GLabel 10180 1520 0    50   Input ~ 0
B2
Wire Wire Line
	10180 1520 10320 1520
$Comp
L Device:LED_Small D5
U 1 1 605FCEF3
P 8750 1410
F 0 "D5" H 8750 1203 50  0000 C CNN
F 1 "LED_Small" H 8750 1294 50  0000 C CNN
F 2 "LED_THT:LED_Rectangular_W5.0mm_H2.0mm" V 8750 1410 50  0001 C CNN
F 3 "~" V 8750 1410 50  0001 C CNN
	1    8750 1410
	-1   0    0    1   
$EndComp
Wire Wire Line
	8510 1410 8650 1410
Wire Wire Line
	8850 1410 8900 1410
$Comp
L Device:LED_Small D6
U 1 1 60634565
P 8770 1940
F 0 "D6" H 8770 1733 50  0000 C CNN
F 1 "LED_Small" H 8770 1824 50  0000 C CNN
F 2 "LED_THT:LED_Rectangular_W5.0mm_H2.0mm" V 8770 1940 50  0001 C CNN
F 3 "~" V 8770 1940 50  0001 C CNN
	1    8770 1940
	-1   0    0    1   
$EndComp
Wire Wire Line
	8510 1940 8670 1940
Wire Wire Line
	8870 1940 8910 1940
$Comp
L Device:LED_Small D7
U 1 1 6065BEF1
P 8780 2450
F 0 "D7" H 8780 2243 50  0000 C CNN
F 1 "LED_Small" H 8780 2334 50  0000 C CNN
F 2 "LED_THT:LED_Rectangular_W5.0mm_H2.0mm" V 8780 2450 50  0001 C CNN
F 3 "~" V 8780 2450 50  0001 C CNN
	1    8780 2450
	-1   0    0    1   
$EndComp
Wire Wire Line
	8520 2450 8680 2450
Wire Wire Line
	8880 2450 8930 2450
$Comp
L Device:LED_Small D8
U 1 1 60683C11
P 8790 2980
F 0 "D8" H 8790 2773 50  0000 C CNN
F 1 "LED_Small" H 8790 2864 50  0000 C CNN
F 2 "LED_THT:LED_Rectangular_W5.0mm_H2.0mm" V 8790 2980 50  0001 C CNN
F 3 "~" V 8790 2980 50  0001 C CNN
	1    8790 2980
	-1   0    0    1   
$EndComp
Wire Wire Line
	8890 2980 8950 2980
Wire Wire Line
	8520 2980 8690 2980
$Comp
L power:GND #PWR0125
U 1 1 606C3F98
P 9080 6280
F 0 "#PWR0125" H 9080 6030 50  0001 C CNN
F 1 "GND" H 9085 6107 50  0000 C CNN
F 2 "" H 9080 6280 50  0001 C CNN
F 3 "" H 9080 6280 50  0001 C CNN
	1    9080 6280
	1    0    0    -1  
$EndComp
Wire Wire Line
	9080 6280 9410 6280
Wire Wire Line
	9410 6280 9410 6420
$Comp
L Connector_Generic:Conn_01x05 J7
U 1 1 606EC8DD
P 6720 4760
F 0 "J7" H 6800 4802 50  0000 L CNN
F 1 "Conn_01x05" H 6800 4711 50  0000 L CNN
F 2 "Connector_JST:JST_XH_B5B-XH-A_1x05_P2.50mm_Vertical" H 6720 4760 50  0001 C CNN
F 3 "~" H 6720 4760 50  0001 C CNN
	1    6720 4760
	1    0    0    -1  
$EndComp
Wire Wire Line
	5940 4540 6520 4540
Wire Wire Line
	6520 4540 6520 4560
Wire Wire Line
	5940 4740 6050 4740
Wire Wire Line
	6050 4740 6050 4660
Wire Wire Line
	6050 4660 6520 4660
Wire Wire Line
	5940 4940 6130 4940
Wire Wire Line
	6130 4940 6130 4760
Wire Wire Line
	6130 4760 6520 4760
Wire Wire Line
	5940 5140 6230 5140
Wire Wire Line
	6230 5140 6230 4860
Wire Wire Line
	6230 4860 6520 4860
$Comp
L power:GND #PWR07
U 1 1 60759858
P 6410 5040
F 0 "#PWR07" H 6410 4790 50  0001 C CNN
F 1 "GND" H 6415 4867 50  0000 C CNN
F 2 "" H 6410 5040 50  0001 C CNN
F 3 "" H 6410 5040 50  0001 C CNN
	1    6410 5040
	1    0    0    -1  
$EndComp
Wire Wire Line
	6410 5040 6410 4960
Wire Wire Line
	6410 4960 6520 4960
$Comp
L Isolator:PC817 U9
U 1 1 6077F1DD
P 7250 3540
F 0 "U9" H 7250 3865 50  0000 C CNN
F 1 "PC817" H 7250 3774 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 7050 3340 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 7250 3540 50  0001 L CNN
	1    7250 3540
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small R9
U 1 1 607803B4
P 7690 3640
F 0 "R9" H 7749 3686 50  0000 L CNN
F 1 "3K3" V 7690 3560 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 7690 3640 50  0001 C CNN
F 3 "~" H 7690 3640 50  0001 C CNN
	1    7690 3640
	0    1    1    0   
$EndComp
Wire Wire Line
	7590 3640 7550 3640
$Comp
L Device:LED_Small D9
U 1 1 60796D2F
P 7950 3640
F 0 "D9" H 7950 3433 50  0000 C CNN
F 1 "LED_Small" H 7950 3524 50  0000 C CNN
F 2 "LED_THT:LED_Rectangular_W5.0mm_H2.0mm" V 7950 3640 50  0001 C CNN
F 3 "~" V 7950 3640 50  0001 C CNN
	1    7950 3640
	-1   0    0    1   
$EndComp
Wire Wire Line
	7850 3640 7790 3640
Text GLabel 8090 3640 2    50   Input ~ 0
SW1
Wire Wire Line
	8090 3640 8050 3640
$Comp
L power:+24V #PWR0126
U 1 1 607C499D
P 7630 3440
F 0 "#PWR0126" H 7630 3290 50  0001 C CNN
F 1 "+24V" V 7560 3380 50  0000 L CNN
F 2 "" H 7630 3440 50  0001 C CNN
F 3 "" H 7630 3440 50  0001 C CNN
	1    7630 3440
	0    1    1    0   
$EndComp
Wire Wire Line
	7630 3440 7550 3440
$Comp
L power:GND #PWR0127
U 1 1 607DBFE5
P 6830 3640
F 0 "#PWR0127" H 6830 3390 50  0001 C CNN
F 1 "GND" H 6835 3467 50  0000 C CNN
F 2 "" H 6830 3640 50  0001 C CNN
F 3 "" H 6830 3640 50  0001 C CNN
	1    6830 3640
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 3640 6830 3640
Wire Wire Line
	10140 6260 10210 6260
Text GLabel 10200 1620 0    50   Input ~ 0
SW1
Wire Wire Line
	10200 1620 10320 1620
$Comp
L HeatEx03-cache:TIP122 Q1
U 1 1 60838CC7
P 5140 10480
F 0 "Q1" H 5347 10526 50  0000 L CNN
F 1 "TIP122" H 5347 10435 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5340 10405 50  0001 L CIN
F 3 "" H 5140 10480 50  0001 L CNN
	1    5140 10480
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0128
U 1 1 60851292
P 5240 10780
F 0 "#PWR0128" H 5240 10530 50  0001 C CNN
F 1 "GND" H 5245 10607 50  0000 C CNN
F 2 "" H 5240 10780 50  0001 C CNN
F 3 "" H 5240 10780 50  0001 C CNN
	1    5240 10780
	1    0    0    -1  
$EndComp
Wire Wire Line
	5240 10780 5240 10750
Text GLabel 5540 10280 2    50   Input ~ 0
SOL1
Wire Wire Line
	5540 10280 5240 10280
Text GLabel 10010 6160 0    50   Input ~ 0
SOL1
Wire Wire Line
	10010 6160 10210 6160
$Comp
L HeatEx03-cache:TIP122 Q3
U 1 1 608B6814
P 3930 10450
F 0 "Q3" H 4137 10496 50  0000 L CNN
F 1 "TIP122" H 4137 10405 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 4130 10375 50  0001 L CIN
F 3 "" H 3930 10450 50  0001 L CNN
	1    3930 10450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0129
U 1 1 608B681A
P 4030 10750
F 0 "#PWR0129" H 4030 10500 50  0001 C CNN
F 1 "GND" H 4035 10577 50  0000 C CNN
F 2 "" H 4030 10750 50  0001 C CNN
F 3 "" H 4030 10750 50  0001 C CNN
	1    4030 10750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4030 10750 4030 10730
Text GLabel 4330 10250 2    50   Input ~ 0
SOL2
Wire Wire Line
	4330 10250 4030 10250
Text GLabel 10010 6060 0    50   Input ~ 0
SOL2
Wire Wire Line
	10010 6060 10210 6060
$Comp
L HeatEx03-cache:TIP122 Q2
U 1 1 608E4489
P 2890 10430
F 0 "Q2" H 3097 10476 50  0000 L CNN
F 1 "TIP122" H 3097 10385 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 3090 10355 50  0001 L CIN
F 3 "" H 2890 10430 50  0001 L CNN
	1    2890 10430
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0130
U 1 1 608E448F
P 2990 10730
F 0 "#PWR0130" H 2990 10480 50  0001 C CNN
F 1 "GND" H 2995 10557 50  0000 C CNN
F 2 "" H 2990 10730 50  0001 C CNN
F 3 "" H 2990 10730 50  0001 C CNN
	1    2990 10730
	1    0    0    -1  
$EndComp
Wire Wire Line
	2990 10730 2990 10690
Text GLabel 3290 10230 2    50   Input ~ 0
SOL3
Wire Wire Line
	3290 10230 2990 10230
Text GLabel 10010 5960 0    50   Input ~ 0
SOL3
Wire Wire Line
	10010 5960 10210 5960
$Comp
L HeatEx03-cache:TIP122 Q4
U 1 1 6091B0D7
P 1800 10290
F 0 "Q4" H 2007 10336 50  0000 L CNN
F 1 "TIP122" H 2007 10245 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 2000 10215 50  0001 L CIN
F 3 "" H 1800 10290 50  0001 L CNN
	1    1800 10290
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0131
U 1 1 6091B0DD
P 1900 10590
F 0 "#PWR0131" H 1900 10340 50  0001 C CNN
F 1 "GND" H 1905 10417 50  0000 C CNN
F 2 "" H 1900 10590 50  0001 C CNN
F 3 "" H 1900 10590 50  0001 C CNN
	1    1900 10590
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 10590 1900 10560
Text GLabel 2200 10090 2    50   Input ~ 0
SOL4
Wire Wire Line
	2200 10090 1900 10090
$Comp
L Isolator:PC817 U10
U 1 1 60931895
P 1490 9710
F 0 "U10" H 1490 10035 50  0000 C CNN
F 1 "PC817" H 1490 9944 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 1290 9510 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 1490 9710 50  0001 L CNN
	1    1490 9710
	0    1    1    0   
$EndComp
Wire Wire Line
	1390 10010 1390 10290
Wire Wire Line
	1390 10290 1600 10290
Text GLabel 10010 5860 0    50   Input ~ 0
SOL4
Wire Wire Line
	10010 5860 10210 5860
$Comp
L Device:R_Small R14
U 1 1 6096B018
P 1730 10010
F 0 "R14" H 1789 10056 50  0000 L CNN
F 1 "270E" V 1660 9930 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 1730 10010 50  0001 C CNN
F 3 "~" H 1730 10010 50  0001 C CNN
	1    1730 10010
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1630 10010 1590 10010
$Comp
L power:VCC #PWR0132
U 1 1 609834DF
P 1910 9990
F 0 "#PWR0132" H 1910 9840 50  0001 C CNN
F 1 "VCC" H 1925 10163 50  0000 C CNN
F 2 "" H 1910 9990 50  0001 C CNN
F 3 "" H 1910 9990 50  0001 C CNN
	1    1910 9990
	1    0    0    -1  
$EndComp
Wire Wire Line
	1910 9990 1910 10010
Wire Wire Line
	1910 10010 1830 10010
$Comp
L Device:R_Small R10
U 1 1 6099C515
P 1590 9280
F 0 "R10" H 1649 9326 50  0000 L CNN
F 1 "270E" V 1520 9200 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 1590 9280 50  0001 C CNN
F 3 "~" H 1590 9280 50  0001 C CNN
	1    1590 9280
	1    0    0    -1  
$EndComp
Wire Wire Line
	1590 9380 1590 9410
$Comp
L power:GND #PWR0133
U 1 1 609B5172
P 1390 9320
F 0 "#PWR0133" H 1390 9070 50  0001 C CNN
F 1 "GND" H 1395 9147 50  0000 C CNN
F 2 "" H 1390 9320 50  0001 C CNN
F 3 "" H 1390 9320 50  0001 C CNN
	1    1390 9320
	-1   0    0    1   
$EndComp
Wire Wire Line
	1390 9320 1390 9410
Text GLabel 5140 9100 1    50   Input ~ 0
Q4
Wire Wire Line
	1590 9120 1590 9180
$Comp
L Isolator:PC817 U11
U 1 1 60A3454F
P 2790 9670
F 0 "U11" H 2790 9995 50  0000 C CNN
F 1 "PC817" H 2790 9904 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 2590 9470 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 2790 9670 50  0001 L CNN
	1    2790 9670
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R16
U 1 1 60A34556
P 3030 9970
F 0 "R16" H 3089 10016 50  0000 L CNN
F 1 "270E" V 2960 9890 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 3030 9970 50  0001 C CNN
F 3 "~" H 3030 9970 50  0001 C CNN
	1    3030 9970
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2930 9970 2890 9970
$Comp
L power:VCC #PWR0134
U 1 1 60A3455D
P 3210 9950
F 0 "#PWR0134" H 3210 9800 50  0001 C CNN
F 1 "VCC" H 3225 10123 50  0000 C CNN
F 2 "" H 3210 9950 50  0001 C CNN
F 3 "" H 3210 9950 50  0001 C CNN
	1    3210 9950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3210 9950 3210 9970
Wire Wire Line
	3210 9970 3130 9970
$Comp
L Device:R_Small R15
U 1 1 60A34565
P 2890 9240
F 0 "R15" H 2949 9286 50  0000 L CNN
F 1 "270E" V 2820 9160 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 2890 9240 50  0001 C CNN
F 3 "~" H 2890 9240 50  0001 C CNN
	1    2890 9240
	1    0    0    -1  
$EndComp
Wire Wire Line
	2890 9340 2890 9370
$Comp
L power:GND #PWR0135
U 1 1 60A3456C
P 2690 9280
F 0 "#PWR0135" H 2690 9030 50  0001 C CNN
F 1 "GND" H 2695 9107 50  0000 C CNN
F 2 "" H 2690 9280 50  0001 C CNN
F 3 "" H 2690 9280 50  0001 C CNN
	1    2690 9280
	-1   0    0    1   
$EndComp
Wire Wire Line
	2690 9280 2690 9370
Text GLabel 3920 9070 1    50   Input ~ 0
Q5
Wire Wire Line
	2890 9080 2890 9140
Wire Wire Line
	2690 9970 2690 10430
$Comp
L Isolator:PC817 U12
U 1 1 60A7108B
P 3820 9660
F 0 "U12" H 3820 9985 50  0000 C CNN
F 1 "PC817" H 3820 9894 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 3620 9460 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 3820 9660 50  0001 L CNN
	1    3820 9660
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R18
U 1 1 60A71092
P 4060 9960
F 0 "R18" H 4119 10006 50  0000 L CNN
F 1 "270E" V 3990 9880 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 4060 9960 50  0001 C CNN
F 3 "~" H 4060 9960 50  0001 C CNN
	1    4060 9960
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3960 9960 3920 9960
$Comp
L power:VCC #PWR0136
U 1 1 60A71099
P 4240 9940
F 0 "#PWR0136" H 4240 9790 50  0001 C CNN
F 1 "VCC" H 4255 10113 50  0000 C CNN
F 2 "" H 4240 9940 50  0001 C CNN
F 3 "" H 4240 9940 50  0001 C CNN
	1    4240 9940
	1    0    0    -1  
$EndComp
Wire Wire Line
	4240 9940 4240 9960
Wire Wire Line
	4240 9960 4160 9960
$Comp
L Device:R_Small R17
U 1 1 60A710A1
P 3920 9230
F 0 "R17" H 3979 9276 50  0000 L CNN
F 1 "270E" V 3850 9150 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 3920 9230 50  0001 C CNN
F 3 "~" H 3920 9230 50  0001 C CNN
	1    3920 9230
	1    0    0    -1  
$EndComp
Wire Wire Line
	3920 9330 3920 9360
$Comp
L power:GND #PWR0137
U 1 1 60A710A8
P 3720 9270
F 0 "#PWR0137" H 3720 9020 50  0001 C CNN
F 1 "GND" H 3725 9097 50  0000 C CNN
F 2 "" H 3720 9270 50  0001 C CNN
F 3 "" H 3720 9270 50  0001 C CNN
	1    3720 9270
	-1   0    0    1   
$EndComp
Wire Wire Line
	3720 9270 3720 9360
Text GLabel 2890 9080 1    50   Input ~ 0
Q6
Wire Wire Line
	3920 9070 3920 9130
Wire Wire Line
	3720 10450 3730 10450
Wire Wire Line
	3720 9960 3720 10450
$Comp
L Isolator:PC817 U13
U 1 1 603E7980
P 5040 9690
F 0 "U13" H 5040 10015 50  0000 C CNN
F 1 "PC817" H 5040 9924 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 4840 9490 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 5040 9690 50  0001 L CNN
	1    5040 9690
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R24
U 1 1 603E7986
P 5280 9990
F 0 "R24" H 5339 10036 50  0000 L CNN
F 1 "270E" V 5210 9910 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 5280 9990 50  0001 C CNN
F 3 "~" H 5280 9990 50  0001 C CNN
	1    5280 9990
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5180 9990 5140 9990
$Comp
L power:VCC #PWR0138
U 1 1 603E798D
P 5460 9970
F 0 "#PWR0138" H 5460 9820 50  0001 C CNN
F 1 "VCC" H 5475 10143 50  0000 C CNN
F 2 "" H 5460 9970 50  0001 C CNN
F 3 "" H 5460 9970 50  0001 C CNN
	1    5460 9970
	1    0    0    -1  
$EndComp
Wire Wire Line
	5460 9970 5460 9990
Wire Wire Line
	5460 9990 5380 9990
$Comp
L Device:R_Small R23
U 1 1 603E7995
P 5140 9260
F 0 "R23" H 5199 9306 50  0000 L CNN
F 1 "270E" V 5070 9180 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 5140 9260 50  0001 C CNN
F 3 "~" H 5140 9260 50  0001 C CNN
	1    5140 9260
	1    0    0    -1  
$EndComp
Wire Wire Line
	5140 9360 5140 9390
$Comp
L power:GND #PWR0139
U 1 1 603E799C
P 4940 9300
F 0 "#PWR0139" H 4940 9050 50  0001 C CNN
F 1 "GND" H 4945 9127 50  0000 C CNN
F 2 "" H 4940 9300 50  0001 C CNN
F 3 "" H 4940 9300 50  0001 C CNN
	1    4940 9300
	-1   0    0    1   
$EndComp
Wire Wire Line
	4940 9300 4940 9390
Text GLabel 1590 9120 1    50   Input ~ 0
Q7
Wire Wire Line
	5140 9100 5140 9160
Wire Wire Line
	4940 9990 4940 10480
$Comp
L Device:R_Small R26
U 1 1 60434960
P 1390 10390
F 0 "R26" H 1449 10436 50  0000 L CNN
F 1 "100K" V 1320 10310 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 1390 10390 50  0001 C CNN
F 3 "~" H 1390 10390 50  0001 C CNN
	1    1390 10390
	1    0    0    -1  
$EndComp
Connection ~ 1390 10290
Wire Wire Line
	1390 10490 1390 10560
Wire Wire Line
	1390 10560 1900 10560
Connection ~ 1900 10560
Wire Wire Line
	1900 10560 1900 10490
$Comp
L Device:R_Small R27
U 1 1 60458EA2
P 2550 10530
F 0 "R27" H 2609 10576 50  0000 L CNN
F 1 "100K" V 2480 10450 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 2550 10530 50  0001 C CNN
F 3 "~" H 2550 10530 50  0001 C CNN
	1    2550 10530
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 10430 2690 10430
Connection ~ 2690 10430
Wire Wire Line
	2550 10630 2550 10690
Wire Wire Line
	2550 10690 2990 10690
Connection ~ 2990 10690
Wire Wire Line
	2990 10690 2990 10630
$Comp
L Device:R_Small R28
U 1 1 604947F5
P 3560 10550
F 0 "R28" H 3619 10596 50  0000 L CNN
F 1 "100K" V 3490 10470 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 3560 10550 50  0001 C CNN
F 3 "~" H 3560 10550 50  0001 C CNN
	1    3560 10550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3560 10450 3720 10450
Connection ~ 3720 10450
Wire Wire Line
	3560 10650 3560 10730
Wire Wire Line
	3560 10730 4030 10730
Connection ~ 4030 10730
Wire Wire Line
	4030 10730 4030 10650
$Comp
L Device:R_Small R29
U 1 1 604D15C4
P 4750 10580
F 0 "R29" H 4809 10626 50  0000 L CNN
F 1 "100K" V 4680 10500 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 4750 10580 50  0001 C CNN
F 3 "~" H 4750 10580 50  0001 C CNN
	1    4750 10580
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 10480 4940 10480
Connection ~ 4940 10480
Wire Wire Line
	4750 10680 4750 10750
Wire Wire Line
	4750 10750 5240 10750
Connection ~ 5240 10750
Wire Wire Line
	5240 10750 5240 10680
$EndSCHEMATC
