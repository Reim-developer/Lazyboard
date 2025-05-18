#!/bin/bash

config() {
    local trans_file="config.hpp"
    local trans_script="generate.py"
    local gen_path="../src/zUtils/include"
    local xml_path="./xml/config.xml"
    local key_tag="property"
    local header_name="CONFIG_HPP"
    local type_name="char"

    cd "../.." || exit
    cd "tools" || exit

    python "$trans_script" "$xml_path" "$trans_file" "$key_tag" "$header_name" "$type_name"
    cp "$trans_file" "$gen_path"
    rm -rf "$trans_file"
}

config