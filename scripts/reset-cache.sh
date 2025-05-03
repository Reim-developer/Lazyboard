#!/bin/bash

cache_dir="$HOME/.cache/zclipboard"

remove_cache() {
    if [ ! -d "$cache_dir" ]; then
        echo "$cache_dir not found. Can't remove."
    else
        rm -rf "$cache_dir"
        echo "Removed $cache_dir."
    fi 
}

remove_cache