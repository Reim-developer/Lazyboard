import xml.etree.ElementTree as et
import sys

def utf8_to_hex(string: str) -> str:
    return "".join(f'\\x{b:02x}' for b in string.encode("utf-8"))

def gen_hpp(xml_file: str, output_file: str, key: str, header_name: str, typeName: str) -> None:
    tree = et.parse(xml_file)
    root = tree.getroot()

    with open(output_file, mode = 'w', encoding = "utf-8") as xml:
        xml.write(f"#ifndef {header_name} \n")
        xml.write(f"#define {header_name} \n")
        xml.write("// Generate by zClipboard Toolchain.\n")
        xml.write("// For more information. Please see tools/xml.\n\n")

        for entry in root.findall(key):
            key_atrr = entry.get("key")

            if key_atrr is None:
                continue

            key_upper = key_atrr.upper()

            value = entry.text or ""

            hex_value = utf8_to_hex(value)
            xml.write(f"// Expands to: {value}.\n")
            xml.write(f'inline constexpr const {typeName} {key_upper}[] = "{hex_value}";\n')

        xml.write("\n")
        xml.write("#endif")
        print(f"Successfully generate: {output_file}")

gen_hpp(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5])