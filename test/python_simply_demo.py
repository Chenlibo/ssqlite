import argparse

from sfs import *

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Demonstrate of SFS read with Python')
    parser.add_argument('--mount-point', type=str, required=True,
        help='Hostname or IP address of EFS mount point')
    parser.add_argument('--test-file', type=str, required=True,
        help='File name of test file to read')
    args = parser.parse_args()

    if not args.test_file.startswith('/'):
        raise ValueError('test-file should start with \'/\'')

    mount(args.mount_point)
    with open(args.test_file) as f:
        f.read(128)
