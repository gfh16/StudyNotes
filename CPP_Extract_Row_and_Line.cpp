#!/bin/bash
# Extract assigned rows of files

awk '{print $3}' SSD1_L1_E_X2.dat > newfile2.dat
awk '{print $3}' SSD1_L1_E_X4.dat > newfile4.dat
awk '{print $3}' SSD1_L1_E_X5.dat > newfile5.dat
awk '{print $3}' SSD1_L1_E_X10.dat > newfile10.dat
awk '{print $3}' SSD1_L1_E_X20.dat > newfile20.dat

#!/bin/bash
# Combine saveral files into one, by rows
paste  newfile2.dat newfile4.dat newfile5.dat  newfile10.dat newfile20.dat > result5.dat


