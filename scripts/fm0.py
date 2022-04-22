#!/usr/bin/env python3

import sys

MAP = {
    "00": "1",
    "11": "1",
    "01": "0",
    "10": "0",
}


def split(s, n):
    return [s[i : i + n] for i in range(0, len(s), n)]


def decode(s):
    a = split(s, 2)
    b = "".join(map(lambda x: MAP[x], a))
    c = split(b, 8)
    d = map(lambda x: int(x, 2), c)
    return list(d)


print(decode(sys.argv[1]))
