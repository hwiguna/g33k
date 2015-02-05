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
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "28 jan 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L BUZ11 Q1
U 1 1 54C85213
P 3500 3850
F 0 "Q1" H 3500 3702 40  0000 R CNN
F 1 "BUZ11" H 3500 4000 40  0000 R CNN
F 2 "TO220" H 3400 3950 25  0000 C CIN
F 3 "~" H 3500 3850 60  0000 C CNN
	1    3500 3850
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 54C85263
P 3600 2900
F 0 "#PWR?" H 3600 2860 30  0001 C CNN
F 1 "+3.3V" H 3600 3010 30  0000 C CNN
F 2 "" H 3600 2900 60  0000 C CNN
F 3 "" H 3600 2900 60  0000 C CNN
	1    3600 2900
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 54C85274
P 3600 3300
F 0 "D1" H 3600 3400 50  0000 C CNN
F 1 "LED" H 3600 3200 50  0000 C CNN
F 2 "~" H 3600 3300 60  0000 C CNN
F 3 "~" H 3600 3300 60  0000 C CNN
	1    3600 3300
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 54C85297
P 3600 4300
F 0 "#PWR?" H 3600 4300 30  0001 C CNN
F 1 "GND" H 3600 4230 30  0001 C CNN
F 2 "" H 3600 4300 60  0000 C CNN
F 3 "" H 3600 4300 60  0000 C CNN
	1    3600 4300
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 54C852A6
P 2900 3900
F 0 "R1" V 2980 3900 40  0000 C CNN
F 1 "1K" V 2907 3901 40  0000 C CNN
F 2 "~" V 2830 3900 30  0000 C CNN
F 3 "~" H 2900 3900 30  0000 C CNN
	1    2900 3900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3600 3100 3600 2900
Wire Wire Line
	2650 3100 3600 3100
Wire Wire Line
	3600 4050 3600 4300
Wire Wire Line
	3600 3500 3600 3650
Wire Wire Line
	2650 3100 2650 3900
Wire Wire Line
	3150 3900 3300 3900
$EndSCHEMATC
