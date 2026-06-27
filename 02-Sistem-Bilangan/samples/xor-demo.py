message = b"ReverseEngineering"
key = 0x42

encrypted = bytes([b ^ key for b in message])
decrypted = bytes([b ^ key for b in encrypted])

print("Encrypted:", encrypted.hex())
print("Decrypted:", decrypted.decode())
