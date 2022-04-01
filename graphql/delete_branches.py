"""Basic  script to batch delete branches on GitHub"""
import argparse
import json
import os
from pathlib import Path
from pprint import pprint
import requests
import sys

REST_API_ROOT = "https://api.github.com"
GH_ORG = "mantidproject"
GH_REPO = "mantid"


def delete_refs_on_github(refs: list):
    """Permanently delete all references on GitHub
    """
    for ref in refs:
        delete_ref_on_github(ref)


def delete_ref_on_github(refname: str):
    """Delete a branch on GitHub permanently

    :param refname: Name of the reference on GitHub
    :type refname: str
    """
    endpoint = f"{REST_API_ROOT}/repos/{GH_ORG}/{GH_REPO}/git/refs/heads/{refname}"
    headers = {"Authorization": f"bearer {os.environ['GITHUB_OAUTH_TOKEN']}"}
    print(f"Deleting branch from GitHub: {refname}")
    requests.delete(endpoint, headers=headers)


def parse_args(argv: list) -> argparse.Namespace:
    """Parse arguments supplied to the program

    :param argv: A string list of arguments where the first is the program name
    :type argv: list
    :return: A Namespace object containing the parsed values
    :rtype: argparse.Namespace
    """
    parser = argparse.ArgumentParser(
        description="Permanently delete branches from GitHub")
    parser.add_argument("refname",
                        nargs='?',
                        default=None,
                        help="The name of a Git reference")
    parser.add_argument(
        "--file",
        dest="filename",
        default=None,
        help=
        "A file containing multiple names to delete. The format is inferred from the extension. Supported types=[.json]"
    )

    return parser.parse_args(argv)


def read_refs_from_file(filename: Path) -> list:
    """Read a list of references from a file

    :return: A flat list of references
    :rtype: list
    """
    with open(filename, "r") as fp:
        payload = json.load(fp)

    return [record["0"] for record in payload]


def main() -> int:
    """Delete a branches from GitHub"""
    args = parse_args(sys.argv)

    if args.filename is not None:
        refs = read_refs_from_file(Path(args.filename))

    print(f"Found {len(refs)} references to delete:")
    pprint(refs, indent=4)

    user_input = input(
        "\nWould you like to delete them from GitHub?\n"
        "Type YES to confirm. Any other input continues without deletion.\n"
        ">")
    if user_input == "YES":
        delete_refs_on_github(refs)


if __name__ == "__main__":
    main()
