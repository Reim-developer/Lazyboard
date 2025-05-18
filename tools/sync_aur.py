import hashlib
import logging
import shutil
import sys
import os

logging.basicConfig(
    level = logging.DEBUG,
    format = "[%(asctime)s] [%(levelname)s] %(message)s",
    datefmt = "%Y-%m-%d %H:%M:%S"
)

def get_sha512(file_path: str) -> str:
    hasher = hashlib.sha512()

    with open(file = file_path, mode = "rb") as file:
        while chunk := file.read(8192):
            hasher.update(chunk)

    return hasher.hexdigest()

def file_exists(file_path: str) -> bool:
    return os.path.exists(file_path)

def match_aur(github_file: str, aur_file: str, verbose: str) -> None:
    if not file_exists(github_file) or not file_exists(aur_file):
        logging.error(f"{github_file} or {aur_file} is not exists.")
        sys.exit(1)

    github_sha512: str = get_sha512(github_file)
    aur_sha512: str = get_sha512(aur_file)

    if github_sha512 != aur_sha512:
        logging.warning(f"{github_file} & {aur_file} is not matches. Sync now.")
        shutil.copy2(aur_file, github_file)

        logging.info("Successfully sync AUR PKGBUILD to GitHub PKGBUILD.")

        if verbose == "--verbose":
              logging.info(f"GitHub File SHA512: {github_sha512}")
              logging.info(f"AUR File SHA512: {aur_sha512}")

        sys.exit(0)
    
    logging.info("SHA512 Matches. Don't need sync")
    logging.info(f"GitHub File SHA512: {github_sha512}")
    logging.info(f"AUR File SHA512: {aur_sha512}")
    sys.exit(0)

match_aur(github_file = sys.argv[1], aur_file = sys.argv[2], verbose = sys.argv[3])