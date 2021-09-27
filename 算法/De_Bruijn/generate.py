from typing import Iterable, Union, Any
def de_bruijn(k: Union[Iterable[Any], int], n: int) -> str:
    """de Bruijn sequence for alphabet k
    and subsequences of length n.
    """
    # Two kinds of alphabet input: an integer expands
    # to a list of integers as the alphabet..
    if isinstance(k, int):
        alphabet = list(map(str, range(k)))
    else:
        # While any sort of list becomes used as it is
        alphabet = k
        k = len(k)

    a = [0] * k * n
    sequence = []

    def db(t, p):
        if t > n:
            if n % p == 0:
                sequence.extend(a[1 : p + 1])
        else:
            a[t] = a[t - p]
            db(t + 1, p)
            for j in range(a[t - p] + 1, k):
                a[t] = j
                db(t + 1, t)

    db(1, 1)
    return "".join(alphabet[i] for i in sequence)


print(de_bruijn(2, 3))
print(de_bruijn(2, 4))
print(de_bruijn(2, 5))
print(de_bruijn(2, 6))
# 00010111 
# 00010111
# 0000100110101111 
# 0000100110101111
# 00000100011001010011101011011111 
# 00000100011001010011101011011111
# 
# 0000001000011000101000111001001011001101001111010101110110111111
print(de_bruijn("abcd", 2))