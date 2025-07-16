def num_paritybits(k: int) -> int:
    #k is the number of data bits
    #r is number of parity bits
    # (1 << r) means 2^r
    #so we check if 2^r < total bits + 1
    #example: we have 4 data bits
    # 1. 1 < 5, 2 < 6, 4 < 7, 8 < 8, so it stops at r = 3
    #Hamming's rule is 2^ r >= k + r + 1
    while (1 << r) < k + r + 1:
        r += 1
    return r
#compues 1 parity bit  for a certain index
#if xor result is 0, the group has an even number of 1's, if it's 1 the group has an odd number
#example [0, 1, 1, 0, 0, 1, 1]
#so for p = 0, mask = 001, indices kept is 1, 3, 5, 7
def parity(codeword: list[int], p: int) -> int:
    mask = 1 << p
    xor_sum = sum(bit
                  for i, bit in enumerate(codeword)
                  if i & mask) % 2
    return xor_sum

def encode(data: list[int]) -> list[int]:
    k = len(data) #number of data bits
    r = num_paritybits(k)
    n = k + r #total codeword length

    codeword = [0] * n #fills total with 0
    j = 0
    for i in range(n):
        if (i & (i + 1)) != 0: #checks if it is not a parity bit, and fills with data
            codeword[i] = data[j]
            j += 1
    #fills remaining bits with parity bits
    for p in range(r):
        codeword[(1 << p) - 1] = parity(codeword, p)

    return codeword

def decode(codeword: list[int]) -> tuple[list[int], bool]:
    codeword = codeword.copy() #copy of total encoded bits
    n = len(codeword)

    r = 0
    #number of parity bits
    while (1 << r) < n + 1:
        r += 1
    
    syndrome = 0
    #syndrome will become a binary num that represents bad bit
    #walks thru parity bits
    for p in range(r):
        #recalculate what parity should be
        expected = parity(codeword, p)
        #vs what it actually is
        received = codeword[(1 << p) - 1]
        if expected != received:
            syndrome |= 1 << p
    clean = syndrome == 0 #if parity not failed then true
    if syndrome and syndrome <= n:
        #flips bad bit
        codeword[syndrome - 1] ^= 1
        #helps keep track if we did correct smth
        clean = False
    #gets data, skips over all parity bits
    data = [
        bit for i, bit in enumerate(codeword) if (i & (i + 1)) != 0
        ]
    return data, clean
