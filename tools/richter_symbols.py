# read out symbols from RICHTER.PRG

# usage:
# python3 ./tools/richter_symbols.py ./disks/saturn/RICHTER.PRG

import sys

if len(sys.argv) < 2:
    print("Please provide RICHTER.PRG as a command-line argument.")
    sys.exit(1)

filename = sys.argv[1]

start_address = 0x00028a00
end_address = 0x0002f000

# Read the binary file within the specified address range
with open(filename, 'rb') as file:
    file.seek(start_address)
    data = file.read(end_address - start_address)

lines = data.decode().split('\r\n')

# first and last lines are incomplete:
#                       60cb664 _parts_p_circle
# 060133cc  *ABS*      060133cc _conve

# fix line 0
lines[0] = "060cb664  *ABS*      060cb664 _parts_p_circle"

# Split the lines and store the data in a list
data = [line.strip().split() for line in lines]

# Sort the data based on the third column (converted to integers)
sorted_data = sorted(data, key=lambda x: int(x[2], 16))

# Print the sorted data
for row in sorted_data:
    print(" ".join(row))

# linker script format
for row in sorted_data:
    name = row[3]
    addr = row[2]
    print(f"{name} = 0x{addr};")
