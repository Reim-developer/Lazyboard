import sys
# import os
import logging

logging.basicConfig(
    level = logging.DEBUG,
    format = "[%(asctime)s] [%(levelname)s] %(message)s",
    datefmt = "%Y-%m-%d %H:%M:%S"
)


def gen_to_hex(data: bytes) -> str:
    return ', '.join(f'0x{b:02x}' for b in data )

def gen_embed_hpp(resouce_path: str, header_path: str, header_name: str, var_name: str) -> None:    
    with open(file = resouce_path, mode = "rb") as resouce:
        data = resouce.read()

    with open(file = header_path, mode = "w", encoding = "utf-8") as header:
        header.write(f"#ifndef {header_name}\n")
        header.write(f"#define {header_name}\n\n")
        header.write("// Auto generate by zClipboard Toolchain.\n\n")
        header.write("#include <stdint.h>\n")
        header.write(f'static const uint8_t {var_name.upper()}[] = {{\n')
        header.write("    " + gen_to_hex(data = data) + "\n")
        header.write("};\n")
        header.write(f'static const size_t {var_name.upper()}_LEN = {len(data)};\n')
        header.write(f"#endif // {header_name}")

gen_embed_hpp(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])
