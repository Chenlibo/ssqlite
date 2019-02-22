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
        print("bytes [0, 128)", f.read(128).decode('utf-8'))
        print("bytes [128, 256)", f.read(128).decode('utf-8'))
        f.seek(0)
        print("bytes [0, 64)", f.read(64).decode('utf-8'))
