import re
import os
import shutil
import logging
import requests
import subprocess
from pathlib import Path

class MikotoTest:
    """
    Copyright (c) 2025 Reim-developer
    
    This project is licensed under the GNU GPL-3.0.
    """
    def __init__(self) -> None:
        self.__STATUS_OK__: int = 200

    def __write(self, path: str, raw_content: str) -> None:
        try:
            with open(file = path, mode = "w", encoding = "utf-8") as File:
                File.write(raw_content)

        except FileNotFoundError:
            raise ValueError(f"Could not write to {path} because this path not found.")

    def getRawCodeFromGitHub(self, raw_url: str) -> str | None:
        """
        Get the raw code from GitHub user content.\n
        Return:\n
        Source code raw if exists. Otherwise, return None.\n
        Raise:\n
        [x] Send requests failed (Empty URL, URL not found),
        like: httwrong://github.com
        """

        if len(raw_url) == 0:
            raise ValueError("Could not send requests to empty URL.")
        
        if not re.findall(r'https?://[^\s]+', raw_url):
            raise ValueError("Only support valid URL, like start with: https:// or http://")

        response = requests.get(raw_url)

        # If response status code is not equal to
        # 200, it will return None.
        if response.status_code != self.__STATUS_OK__:
            return None
        
        # Return response text
        return response.text
    
    def getFileNameFromURL(self, url: str) -> str:
        """
        Get file name from URL.\n
        Return:\n
        `basename` File basename, (e.g: http://myFile.txt) => will return `myFile.txt`
        """
        return os.path.basename(url)
    
    def getCwd(self) -> str:
        """
        Get the current directory, as in the Python script run.\n
        Return:\n
        `cwd` The current directory, as in the Python script run.
        """
        return os.getcwd()

    def mkdirProject(self, path: str) -> str:
        """
        Create directory/project if is not exists.\n
        Otherwise, if this exists, return `path`.

        Return:\n
        `path` Directory path generate.\n
        """
        if os.path.exists(path):
            return path
        
        os.mkdir(path = path)
        return path

    def writeRawCodeTo(self, path: str,  raw_content: str, 
                       make_ifnot_exists: bool = False, override: bool = False,
                       throw: bool = False) -> None:
        """
        Write raw code to target file path directory.

        # Parameters:
        `path` File path directory. Required.\n
        `raw_content` Raw code/content you want write. Required.\n
        `make_ifnot_exists` Make file, if is not exists. Default is `False`.\n
        `override` Override file, if is exists. Default is `False`.
        `throw` Throw traceback in ALL flow logic. Default is `False`
        """
        if not os.path.exists(path = path) and not make_ifnot_exists:
            if throw:
                raise ValueError(f"Could not write to {path} because this path is doesn't exists. If you wish create path if not exists, use 'make_ifnot_exists = True' parameter")
        
        if not os.path.exists(path = path) and make_ifnot_exists:
            self.__write(path = path, raw_content = raw_content)
            return

        if os.path.exists(path = path):
            _path_ = Path(path)

            if _path_.is_dir():
                raise ValueError("Could not write to directory.")
            
        if os.path.exists(path = path) and not override:
            if throw:
                raise ValueError(f"Could not write to {path} because this path exists, but the parameter `override` is not provided to True.")
        
        if os.path.exists(path = path) and override:
            self.__write(path = path, raw_content = raw_content)

        self.__write(path = path, raw_content = raw_content)

    def hasTool(self, tool_name: str) -> bool:
        """
        Check tool is exists.\n
        Return:\n
        True if exists. Otherwise, will return False.
        """
        tool = shutil.which(tool_name)

        return False if tool is None else True
    
    def run_program(self, args: list[str] | str, cwd: str, verbose: bool = False) -> None:
        if not verbose:
            subprocess.run(args = args, cwd = cwd)

            return
        
        details = subprocess.run(args = args, cwd = cwd)
        logging.basicConfig(
            level = logging.INFO,
            format = "[%(asctime)s] [%(levelname)s] %(message)s",
            datefmt = "%Y-%m-%d %H:%M:%S"
        )

        logging.info(f"Command: {details.args}")
        logging.info(f"Exit Code: {details.returncode}")
