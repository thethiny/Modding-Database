# KHUxPNG2PNG.py
# Reworked version: outputs PNG instead of BMP.
# Keeps the same per-pixel shuffle logic as the C++: (R,G,B,A in .dat) -> (B,G,R,A) written out.
# Uses the same width/height extraction logic from the Input\<name> file as the C++.

import os
import sys

from PIL import Image


def read_u8(f):
    b = f.read(1)
    return None if not b else b[0]


def get_dims_from_input(input_path: str):
    # C++ logic:
    # - skip 0x1E bytes
    # - read 2 bytes -> width (little-endian, high 2 bytes assumed 0)
    # - read 2 bytes -> height as size[1] (low), size[0] (high)
    with open(input_path, "rb") as f:
        f.read(0x1E)
        w0 = read_u8(f)
        w1 = read_u8(f)
        if w0 is None or w1 is None:
            return None, None
        width = w0 | (w1 << 8)

        h_low = read_u8(f)  # size[1]
        h_high = read_u8(f)  # size[0]
        if h_low is None or h_high is None:
            return None, None
        height = h_low | (h_high << 8)

    return width, height


def replace_ext(path: str, new_ext: str):
    base, _ = os.path.splitext(path)
    return base + new_ext


def convert_one(name: str):
    in_path = os.path.join("Input", name)
    dat_path = os.path.join("DATS", name + ".dat")

    if not os.path.isfile(in_path):
        return
    if not os.path.isfile(dat_path):
        return

    width, height = get_dims_from_input(in_path)
    if not width or not height:
        return

    out_path = os.path.join("pngImages", replace_ext(name, ".png"))
    os.makedirs(os.path.dirname(out_path) or ".", exist_ok=True)

    need = width * height * 4

    with open(dat_path, "rb") as f:
        raw = f.read(need)

    if len(raw) < need:
        # Not enough pixel data; match the "skip/continue" spirit.
        return

    # Keep the SAME shuffle logic as the C++:
    # input pixel bytes are read as: R, (G), B, A
    # output bytes are written as:  B, G, R, A
    out = bytearray(need)
    for i in range(0, need, 4):
        r = raw[i + 0]
        g = raw[i + 1]
        b = raw[i + 2]
        a = raw[i + 3]
        out[i + 0] = r
        out[i + 1] = g
        out[i + 2] = b
        out[i + 3] = a

    img = Image.frombytes("RGBA", (width, height), bytes(out))
    img.save(out_path, "PNG")


def main():
    # Usage:
    #   python KHUxPNG2PNG.py           -> reads pngList.txt
    #   python KHUxPNG2PNG.py file1 ... -> converts the given names
    if len(sys.argv) > 1:
        for name in sys.argv[1:]:
            print(f"Converting {name}...")
            convert_one(name)
        return

    if not os.path.isfile("pngList.txt"):
        return

    with open("pngList.txt", "r", encoding="utf-8", errors="ignore") as lst:
        for line in lst:
            name = line.rstrip("\r\n")
            if not name:
                continue
            print(f"Converting {name}...")
            convert_one(name)


if __name__ == "__main__":
    main()
