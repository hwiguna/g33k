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
Date "4 jan 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L +5V #PWR01
U 1 1 54A8DA2F
P 3100 3650
F 0 "#PWR01" H 3100 3740 20  0001 C CNN
F 1 "+5V" H 3100 3740 30  0000 C CNN
F 2 "" H 3100 3650 60  0000 C CNN
F 3 "" H 3100 3650 60  0000 C CNN
	1    3100 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 54A8DA3E
P 3100 4000
F 0 "#PWR02" H 3100 4000 30  0001 C CNN
F 1 "GND" H 3100 3930 30  0001 C CNN
F 2 "" H 3100 4000 60  0000 C CNN
F 3 "" H 3100 4000 60  0000 C CNN
	1    3100 4000
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 54A8DA4D
P 4250 3550
F 0 "R1" V 4330 3550 40  0000 C CNN
F 1 "R" V 4257 3551 40  0000 C CNN
F 2 "~" V 4180 3550 30  0000 C CNN
F 3 "~" H 4250 3550 30  0000 C CNN
	1    4250 3550
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 54A8DA5C
P 4250 4000
F 0 "D1" H 4250 4100 50  0000 C CNN
F 1 "LED" H 4250 3900 50  0000 C CNN
F 2 "~" H 4250 4000 60  0000 C CNN
F 3 "~" H 4250 4000 60  0000 C CNN
	1    4250 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	4250 3300 3100 3300
Wire Wire Line
	3100 3300 3100 3650
Wire Wire Line
	4250 4200 3100 4200
Wire Wire Line
	3100 4200 3100 4000
$EndSCHEMATC
