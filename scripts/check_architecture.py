Import("env")

from pathlib import Path
import re
import sys

PROJECT_DIR = Path(env["PROJECT_DIR"])
SRC_DIR = PROJECT_DIR / "src"

RULES = {
    "core": ["drivers", "web"],
    "app": [],
    "drivers": [],
    "web": []
}

include_pattern = re.compile(r'^\s*#\s*include\s*"([^"]+)"')

def get_module(path: Path) -> str | None:
    parts = path.parts
    if "src" in parts:
        idx = parts.index("src")
        if idx + 1 < len(parts):
            return parts[idx + 1]
    return None

def main():
    errors = []

    for file_path in SRC_DIR.rglob("*"):
        if file_path.suffix not in [".cpp", ".h", ".hpp"]:
            continue

        current_module = get_module(file_path)
        if current_module is None:
            continue

        forbidden = RULES.get(current_module, [])

        try:
            content = file_path.read_text(encoding="utf-8")
        except Exception as exc:
            errors.append(f"Erro ao ler {file_path}: {exc}")
            continue

        for line_no, line in enumerate(content.splitlines(), start=1):
            match = include_pattern.match(line)
            if not match:
                continue

            included = match.group(1)

            for forbidden_module in forbidden:
                if included.startswith(forbidden_module + "/"):
                    errors.append(
                        f"[ARCH] {file_path.relative_to(PROJECT_DIR)}:{line_no} "
                        f"nao pode incluir '{included}'"
                    )

    if errors:
        print("\n".join(errors))
        env.Exit(1)

main()