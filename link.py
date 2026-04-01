from pathlib import Path 
import subprocess

BUILD_ROOT = Path(__file__).parent / "build"

all_objs = list(BUILD_ROOT.rglob("*.o"))


start_obj = [p for p in all_objs if p.name == "start.o"]
other_obj = [p for p in all_objs if p.name != "start.o"]

link_order = start_obj + other_obj 


link_order_str = " ".join(str(p) for p in link_order)

ld_cmd = f"ld -o program {link_order_str}"

print(ld_cmd)

subprocess.run(ld_cmd, shell=True, check=True)
