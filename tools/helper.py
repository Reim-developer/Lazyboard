#!/usr/bin/python3

import argparse
import os
import sys 

RED = "\033[1;31m"
WHITE = "\033[0m"
GREEN = "\033[0;32m"

stderr = sys.stderr.write
abort = sys.exit

parser = argparse.ArgumentParser(description = "Helper Tools For Lazyboard Project")
sub_parsers = parser.add_subparsers(dest = "command")

def gen_to_hex(data: bytes) -> str:
	return ", ".join(f"0x{b:02x}" for b in data)

def file_name(file_str: str) -> str:
	return os.path.basename(file_str)

def file_extension(file: str) -> str:
	_, extension = os.path.splitext(file)

	return extension

def gen_res(args: argparse.Namespace) -> None:
	file_path = args.path
	cxx_output = args.output

	if not os.path.exists(file_path):
		stderr(f"{RED}error:{WHITE} Resource file path {file_path} not found\n")
		abort(1)

	if not file_extension(cxx_output) == ".cxx":
		cxx_output += ".hxx"

	try:
		with open(file = file_path, mode = "rb") as image_file:
			read_bytes = gen_to_hex(image_file.read())

		with open(file = cxx_output, mode = "w", encoding = "utf-8") as output:
			header_name = file_name(cxx_output).upper().replace(".", "_")

			output.write(f"#ifndef {header_name}\n")
			output.write(f"#define {header_name}\n\n")
			output.write(f"#include <stdint.h>\n\n")
			output.write("#include <initializer_list>\n\n")
			output.write("using std::initializer_list;\n\n")
			output.write(f"const initializer_list<uint8_t> image_bytes = {{\n")
			output.write(f"    " + read_bytes + "\n")
			output.write("};\n")

			output.write(f"#endif // {header_name}")

		print(f"{GREEN}ok:{WHITE} Generated successfully, can found header file at: {cxx_output}")

	except Exception as error:
		stderr(f"{RED}error:{WHITE} Exception error: {error}")

def gen_resources_command() -> None:
	gen_res_cmd = sub_parsers.add_parser("gen-res", help = "Gen resource to C++ header")
	gen_res_cmd.add_argument("--path", help = "Resource file path")
	gen_res_cmd.add_argument("--output", help = "C++ source output")
	gen_res_cmd.set_defaults(func = gen_res)

def main() -> None:
	gen_resources_command()
	arguments = parser.parse_args()

	if hasattr(arguments, "func"):
		arguments.func(arguments)

	else:
		parser.print_help()

main()