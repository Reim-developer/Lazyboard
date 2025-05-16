import xml.etree.ElementTree as et

def utf8_to_hex(string: str) -> str:
    return "".join(f'\\x{b:02x}' for b in string.encode("utf-8"))

def gen_hpp(xml_file: str, output_file: str) -> None:
    tree = et.parse(xml_file)
    root = tree.getroot()

    with open(output_file, mode = 'w', encoding = "utf-8") as xml:
        xml.write("#ifndef TRANSLATE_HPP\n")
        xml.write("#define TRANSLATE_HPP\n")
        xml.write("/*\n")
        xml.write("Generate by zClipboard Translate Tools.\n")
        xml.write("*/\n\n")
        xml.write("namespace zclipboard::language {\n")

        for entry in root.findall("entry"):
            key = entry.get("key")

            if key is None:
                continue
            key = key.upper()

            value = entry.text or ""

            hex_value = utf8_to_hex(value)
            xml.write(f'inline constexpr const char* {key} = "{hex_value}";\n')

        xml.write("}\n")
        xml.write("\n")
        xml.write("#endif")
        print("Successfully generate language file.")

gen_hpp("./xml/language.xml", "language.hpp")