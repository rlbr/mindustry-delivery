from enum import IntEnum

length_vals = [0] * 4


class lengths(IntEnum):
    RESOURCE_INT = 0
    MODE = 1
    VAULT_ID = 2
    ID = 3


length_vals[lengths.RESOURCE_INT] = 4
length_vals[lengths.MODE] = 3
length_vals[lengths.VAULT_ID] = 10
length_vals[lengths.ID] = 8
# 0000 000 0 00000000
# rrrr mmm v iiiiiiii
end = sum(length_vals)
ends = []
for length in length_vals:
    end -= length
    ends.append(end)


def get_mask(length):
    return (1 << length) - 1


def read_flag(flag, index):
    val = flag >> ends[index]
    return val & get_mask(length_vals[index])


def modify_flag(flag, index, val):
    mask = get_mask(length_vals[index]) << ends[index]
    mask = ~mask
    breakpoint()
    flag = flag & mask
    val = val << ends[index]
    return flag | val


class IntBackedArray(list):
    def __init__(self, lengths):
        self.lengths = tuple(lengths)
        self.flag = 0

    def __getitem__(self, index):
        return read_flag(self.flag, index)

    def __setitem__(self, index, val):
        self.flag = modify_flag(self.flag, index, val)
