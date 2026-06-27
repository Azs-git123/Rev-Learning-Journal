import struct

value = 0xDEADBEEF

print("Little Endian :", struct.pack("<I", value).hex())
print("Big Endian    :", struct.pack(">I", value).hex())
