#!/bin/bash

gen_embed_icon() {
    local embed_img_file="embed_img.py"
    local icon_path="../../assets/icon.png"
    local tmp_script_path="../../tools"
    local header_path="embed_icon.hpp"
    local header_name="core_embed_icon"
    local var_name="ICON_EMBED"

    cp "$icon_path"  "$tmp_script_path" || exit 1

    tmp_icon_path="icon.png"

    cd ../.. || exit 1
    cd tools || exit 1
    python "$embed_img_file" "$tmp_icon_path" "$header_path" "$header_name" "$var_name"

    cp "$header_path" "../src/core/include"

    rm -f "$tmp_icon_path"
    rm -f "$header_path"
}

gen_embed_icon