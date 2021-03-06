EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:curlim-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "16 nov 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MOSFET_P Q2
U 1 1 526FE85F
P 5900 2050
F 0 "Q2" H 5900 2240 60  0000 R CNN
F 1 "irlml2244" H 5900 1870 60  0000 R CNN
F 2 "~" H 5900 2050 60  0000 C CNN
F 3 "~" H 5900 2050 60  0000 C CNN
	1    5900 2050
	0    1    -1   0   
$EndComp
$Comp
L R R4
U 1 1 526FE86E
P 4450 1950
F 0 "R4" V 4530 1950 40  0000 C CNN
F 1 "9" V 4457 1951 40  0000 C CNN
F 2 "~" V 4380 1950 30  0000 C CNN
F 3 "~" H 4450 1950 30  0000 C CNN
	1    4450 1950
	0    -1   -1   0   
$EndComp
$Comp
L PNP Q1
U 1 1 526FE87D
P 5150 2550
F 0 "Q1" H 5150 2400 60  0000 R CNN
F 1 "bc857" H 5150 2700 60  0000 R CNN
F 2 "~" H 5150 2550 60  0000 C CNN
F 3 "~" H 5150 2550 60  0000 C CNN
	1    5150 2550
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 1950 5700 1950
Wire Wire Line
	5150 2350 5150 1950
Connection ~ 5150 1950
$Comp
L R R3
U 1 1 526FE88D
P 4450 1750
F 0 "R3" V 4530 1750 40  0000 C CNN
F 1 "9" V 4457 1751 40  0000 C CNN
F 2 "~" V 4380 1750 30  0000 C CNN
F 3 "~" H 4450 1750 30  0000 C CNN
	1    4450 1750
	0    -1   -1   0   
$EndComp
$Comp
L R R5
U 1 1 526FE893
P 4450 2150
F 0 "R5" V 4530 2150 40  0000 C CNN
F 1 "9" V 4457 2151 40  0000 C CNN
F 2 "~" V 4380 2150 30  0000 C CNN
F 3 "~" H 4450 2150 30  0000 C CNN
	1    4450 2150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4800 1750 4800 2150
Wire Wire Line
	4800 1750 4700 1750
Connection ~ 4800 1950
Wire Wire Line
	4800 2150 4700 2150
Wire Wire Line
	3450 1950 4200 1950
Wire Wire Line
	4100 2150 4200 2150
Wire Wire Line
	4100 1750 4100 2150
Connection ~ 4100 1950
Wire Wire Line
	4200 1750 4100 1750
Wire Wire Line
	6100 1950 6900 1950
$Comp
L R R1
U 1 1 526FE943
P 4000 3350
F 0 "R1" V 4080 3350 40  0000 C CNN
F 1 "10" V 4007 3351 40  0000 C CNN
F 2 "~" V 3930 3350 30  0000 C CNN
F 3 "~" H 4000 3350 30  0000 C CNN
	1    4000 3350
	-1   0    0    1   
$EndComp
$Comp
L R R2
U 1 1 526FE950
P 4000 4050
F 0 "R2" V 4080 4050 40  0000 C CNN
F 1 "30" V 4007 4051 40  0000 C CNN
F 2 "~" V 3930 4050 30  0000 C CNN
F 3 "~" H 4000 4050 30  0000 C CNN
	1    4000 4050
	-1   0    0    1   
$EndComp
Wire Wire Line
	4000 3100 4000 1950
Connection ~ 4000 1950
Wire Wire Line
	4950 2650 4000 2650
Connection ~ 4000 2650
Wire Wire Line
	5900 2250 5900 3700
Wire Wire Line
	5900 2650 5350 2650
Wire Wire Line
	4000 3800 4000 3600
Wire Wire Line
	5900 3700 4000 3700
Connection ~ 5900 2650
Connection ~ 4000 3700
$Comp
L GND #PWR01
U 1 1 526FE9CC
P 4000 4550
F 0 "#PWR01" H 4000 4550 30  0001 C CNN
F 1 "GND" H 4000 4480 30  0001 C CNN
F 2 "" H 4000 4550 60  0000 C CNN
F 3 "" H 4000 4550 60  0000 C CNN
	1    4000 4550
	1    0    0    -1  
$EndComp
$Comp
L TST P1
U 1 1 526FE9DB
P 3450 1850
F 0 "P1" H 3450 2150 40  0000 C CNN
F 1 "TST" H 3450 2100 30  0000 C CNN
F 2 "~" H 3450 1850 60  0000 C CNN
F 3 "~" H 3450 1850 60  0000 C CNN
	1    3450 1850
	1    0    0    -1  
$EndComp
$Comp
L TST P2
U 1 1 526FE9E8
P 6900 1800
F 0 "P2" H 6900 2100 40  0000 C CNN
F 1 "TST" H 6900 2050 30  0000 C CNN
F 2 "~" H 6900 1800 60  0000 C CNN
F 3 "~" H 6900 1800 60  0000 C CNN
	1    6900 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 1950 6900 1800
Wire Wire Line
	3450 1950 3450 1850
Wire Wire Line
	4000 4550 4000 4300
$Comp
L PWR_FLAG #FLG02
U 1 1 526FEB4B
P 3650 4300
F 0 "#FLG02" H 3650 4395 30  0001 C CNN
F 1 "PWR_FLAG" H 3650 4480 30  0000 C CNN
F 2 "" H 3650 4300 60  0000 C CNN
F 3 "" H 3650 4300 60  0000 C CNN
	1    3650 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 4400 4350 4400
Wire Wire Line
	3650 4400 3650 4300
Connection ~ 4000 4400
$Comp
L TST P3
U 1 1 526FEC96
P 4350 4300
F 0 "P3" H 4350 4600 40  0000 C CNN
F 1 "TST" H 4350 4550 30  0000 C CNN
F 2 "~" H 4350 4300 60  0000 C CNN
F 3 "~" H 4350 4300 60  0000 C CNN
	1    4350 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 4400 4350 4300
Wire Notes Line
	3800 3350 2900 3750
Wire Notes Line
	3800 3350 3750 3350
Wire Notes Line
	3800 3350 3750 3400
Text Notes 2150 3750 0    60   ~ 0
No need in this \none. Without it \nthe board should \nwork well.
$EndSCHEMATC
