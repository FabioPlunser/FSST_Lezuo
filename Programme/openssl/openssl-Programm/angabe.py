import crypto
import sys
sys.modules['Crypto'] = crypto
from Crypto.Cipher import AES


# deciphers to "Schoene Crypto Welt" with IV=BBBBBBBBBBBBBBBB and key=BBBBBBBBBBBBBBBB aes128-cbc
key = b'BBBBBBBBBBBBBBBB'

IV =  b'BBBBBBBBBBBBBBBB'

plaintext="Schoene Crypto Welt"
aes = AES.new(key, AES.MODE_CBC, IV)
encd = aes.encrypt(plaintext)
print(encd)

cyphertext = 'AAE365272C81078AB6116B361831D0F6A5D3C8587E946B530B7957543107F15E'
aes = AES.new(key, AES.MODE_CBC, iv)
decd = aes.decrypt(cyphertext)
print(decd)


print(data)



