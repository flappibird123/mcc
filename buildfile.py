import os
import subprocess
from pathlib import Path 

SRC_ROOT = Path(__file__).parent / "src"
BUILD_ROOT = Path(__file__).parent / "build"

def build_dir(src_dir):
    # load buildfile from this directory
    buildfile = src_dir / "buildfile.py"
    ns = {}
    with open(buildfile) as f:
        exec(f.read(), ns)

    c_files = ns.get("c_files", [])
    asm_files = ns.get("asm_files", [])
    subdirs = ns.get("subdirs", [])

    
    include_root = "include"
    include_dirs = []

    for root, dirs, files in os.walk(include_root):
        # add the current folder to the list
        include_dirs.append(root)

    # create a string like: "-Iinclude -Iinclude/foo -Iinclude/bar"
    include_flags = " ".join(f"-I{d}" for d in include_dirs)

    # build object c_files
    for c_file in c_files:
        src_path = src_dir / c_file
        build_path = BUILD_ROOT / src_path.relative_to(SRC_ROOT)
        build_path = build_path.with_suffix(".o")
        build_path.parent.mkdir(parents=True, exist_ok=True)
        cmd = f"clang -c {include_flags} -ffreestanding -nostdlib {src_path} -o {build_path}"
        print(cmd)
        subprocess.run(cmd, shell=True, check=True)

    for asm_file in asm_files:
        src_path = src_dir / asm_file
        build_path = BUILD_ROOT / src_path.relative_to(SRC_ROOT)
        build_path = build_path.with_suffix(".o")
        build_path.parent.mkdir(parents=True, exist_ok=True)
        cmd = f"nasm -f elf64 {src_path} -o {build_path}"
        print(cmd)
        subprocess.run(cmd, shell=True, check=True)

    for sub in subdirs:
        build_dir(src_dir / sub)


if __name__ == "__main__":
    build_dir(SRC_ROOT)

