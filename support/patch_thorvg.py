print("======== PATCH THORVG SCRIPT TRIGGERED ========")

Import("env")
import subprocess
import os

def patch_already_applied(source_file):
    if not os.path.exists(source_file):
        return False
    with open(source_file, "r", encoding="utf-8") as f:
        for line in f:
            if "ColorStop()" in line and "value" in line:
                return True
    return False

def apply_patch(source_dir, patch_file):
    print("======== APPLY PATCH LOG ========")

    if not os.path.exists(source_dir):
        print(f"Source directory {source_dir} does not exist. Skipping.")
        return

    header = os.path.join(source_dir, "src/libs/thorvg/tvgLottieProperty.h")
    if patch_already_applied(header):
        print("Patch already applied. Skipping.")
        return

    print(f"Trying to patch: {patch_file} into {source_dir}")
    try:
        result = subprocess.run(
            ["patch", "-p1", "-N", "--input=" + patch_file],
            cwd=source_dir,
            check=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )
        print("Patch applied successfully.")
        print("stdout:", result.stdout.decode())
        print("stderr:", result.stderr.decode())
    except subprocess.CalledProcessError as e:
        print("Patch failed:\n" + e.stderr.decode())
        raise e

patch_path = os.path.join(env["PROJECT_DIR"], "support/LVGL_ThorVG_Lottie.patch")
target_dir = ".pio/libdeps/board_M5CoreS3/lvgl"

apply_patch(target_dir, patch_path)
