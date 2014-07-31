import os
import time

RELEASE_WORKING_DIRECTORY = ""
RELEASE_BRANCH_NAME = ""


def set_working_dir(working_dir):
    global RELEASE_WORKING_DIRECTORY
    RELEASE_WORKING_DIRECTORY = working_dir


def set_branch_name(branch_name):
    global RELEASE_BRANCH_NAME
    RELEASE_BRANCH_NAME = branch_name


def get_working_dir():
    if not RELEASE_WORKING_DIRECTORY:
        exit("Empty working directory")
    return RELEASE_WORKING_DIRECTORY


def get_source_dir():
    return get_working_dir()+"/"+"BornAgain"


def get_build_dir():
    return get_working_dir()+"/"+"build"


def get_upload_dir():
    return get_working_dir()+"/"+"upload"


def get_install_dir():
    return get_working_dir()+"/"+"installed"


def get_branch_name():
    if not RELEASE_BRANCH_NAME:
        exit("Empty branch name")
    return RELEASE_BRANCH_NAME


def get_version():
    name, version = get_branch_name().split("-")
    #version_major, version_minor, version_patch = version.split(".")
    return version


def get_checkrelease_dir():
    return get_working_dir()+"/"+"checkrelease"


def get_checkmaster_dir():
    return get_checkrelease_dir()+"/"+"checkmaster"


def get_checktarball_dir():
    return get_checkrelease_dir()+"/"+"checktarball"


def get_manual_name():
    cmake_file = get_source_dir() + "/Doc/UserManual/CMakeLists.txt"
    numbers = []
    with open(cmake_file, "r") as fin:
        for line in fin:
            if "UM_VERSION" in line:
                str = line.replace("(", "").replace(")", "")
                numbers.append([int(s) for s in str.split() if s.isdigit()][0])
    return "UserManual-%s.%s.%s.pdf" % (numbers[0], numbers[1], numbers[2])


def run_command(cmd):
    print ">>>", cmd
    returncode = os.system(cmd)
    time.sleep(1)
    if returncode:
        exit("Error while running command '"+cmd+"'")

