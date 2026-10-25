#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
version.py -- version string substitution utility.
"""

import argparse
import os
import re
import subprocess
import sys


def get_git_sha1(git_dir):
    try:
        result = subprocess.run(
            ['git', 'rev-parse', '--short', 'HEAD'],
            capture_output=True,
            text=True,
            cwd=git_dir,
            timeout=5,
            check=True
        )
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        print(f"Error: Failed to get git SHA-1: {e.stderr}")
        return None
    except Exception as e:
        print(f"Unexpected error: {e}")
        return None


def parse_version_info(content):
    ver_major = int(re.search(r'#define\s+VERSION_MAJOR\s+(\d+)', content).group(1))
    ver_minor = int(re.search(r'#define\s+VERSION_MINOR\s+(\d+)', content).group(1))
    ver_patch = int(re.search(r'#define\s+VERSION_PATCH\s+(\d+)', content).group(1))
    ver_build = int(re.search(r'#define\s+VERSION_BUILD\s+(\d+)', content).group(1))
    ver_source = re.search(r'#define\s+VERSION_SOURCE\s+(\S+)', content).group(1)
    ver_prerelease = re.search(r'#define\s+VERSION_PRERELEASE\s+(\S+)', content).group(1)
    return ver_major, ver_minor, ver_patch, ver_build, ver_source, ver_prerelease


def update_version_info(content, old_ver_build_line, new_ver_build_line, old_ver_source_line, new_ver_source_line):
    new_content = content.replace(old_ver_build_line, new_ver_build_line)
    new_content = new_content.replace(old_ver_source_line, new_ver_source_line)
    return new_content


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('header_path', help='version file path')
    args = parser.parse_args()

    with open(args.header_path, 'r', encoding='utf-8') as f:
        content = f.read()

    ver_major, ver_minor, ver_patch, ver_build, ver_source, ver_prerelease = parse_version_info(content)

    old_ver_build_line = f'#define VERSION_BUILD         {ver_build}'
    new_ver_build_line = f'#define VERSION_BUILD         {ver_build + 1}'

    old_ver_source_line = f'#define VERSION_SOURCE        {ver_source}'
    new_git_sha1 = get_git_sha1(os.path.dirname(args.header_path)) or "unknown"
    new_ver_source_line = f'#define VERSION_SOURCE        {new_git_sha1}'

    new_content = update_version_info(content, old_ver_build_line, new_ver_build_line, old_ver_source_line, new_ver_source_line)

    print(f'old version: {ver_major}.{ver_minor}.{ver_patch}.{ver_build} {ver_source} {ver_prerelease}')
    print(f'new version: {ver_major}.{ver_minor}.{ver_patch}.{ver_build + 1} {new_git_sha1} {ver_prerelease}')

    with open(args.header_path, 'w', encoding='utf-8') as f:
        f.write(new_content)


if __name__ == "__main__":
    main()