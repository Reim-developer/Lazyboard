#!/bin/bash

trans() {
    local trans_file="language.hpp"
    local trans_script="generate.py"
    local gen_path="../src/language/include"
    local xml_path="./xml/language.xml"
    local key_tag="entry"
    local header_name="TRANSLATOR_HPP"
    local type_name="char"

    cd "../.." || exit
    cd "tools" || exit

    python "$trans_script" "$xml_path" "$trans_file" "$key_tag" "$header_name" "$type_name"
    cp "$trans_file" "$gen_path"
    rm -rf "$trans_file"
}

trans