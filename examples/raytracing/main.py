import argparse
import time
from multiprocessing import Pool
import json
import os
import sfs
import boto3

lambda_client = boto3.client('lambda')

def lambda_test(x, y, x_slices, y_slices, exec_name, output_file, seg):
    input_event = {
        "exec_name": exec_name,
        "output_file": output_file,
        "segment": seg,
    }
    
    invoke_response = lambda_client.invoke(
        FunctionName="testFunc",
        InvocationType='RequestResponse',
        Payload=json.dumps(input_event)
    )

    response = json.loads(invoke_response['Payload'].read().decode("utf-8"))
    return response


def lambda_raytracing(x, y, x_slices, y_slices, exec_name, output_file, seg):
    input_event = {
        "exec_name": exec_name,
        "output_file": output_file,
        "x_res": x,
        "y_res": y,
        "num_ver_slices": x_slices,
        "num_hor_slices": y_slices,
        "segment": seg,
    }

    invoke_response = lambda_client.invoke(
                FunctionName="sfs-raytracing",
                InvocationType='RequestResponse',
                Payload=json.dumps(input_event)
            )
    
    response = json.loads(invoke_response['Payload'].read().decode("utf-8"))

    return response


def lambda_stitch(x, y, x_slices, y_slices, exec_name, output_file):
    input_event = {
        "exec_name": exec_name,
        "output_file": output_file,
        "x_res": x,
        "y_res": y,
        "num_ver_slices": x_slices,
        "num_hor_slices": y_slices,
    }
    invoke_response = lambda_client.invoke(
                FunctionName="sfs-stitch",
                InvocationType='RequestResponse',
                Payload=json.dumps(input_event)
            )
    response = json.loads(invoke_response['Payload'].read().decode("utf-8"))
    
    return response

def lambda_args(args):
    num_seg = args.x * args.y
    return zip([args.x_res]*num_seg, [args.y_res]*num_seg, [args.x]*num_seg, [args.y]*num_seg, 
                [args.exec_raytracing]*num_seg, [args.output]*num_seg, range(num_seg))

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog='main.py', description='Example of Raytracing using SFS.')
    parser.add_argument("x_res", type=int, help="number of pixels in width")
    parser.add_argument("y_res", type=int, help="number of pixels in height")
    parser.add_argument("x", type=int, help="number of slices vertically")
    parser.add_argument("y", type=int, help="number of slices horizontally")
    parser.add_argument("exec_raytracing", help="executable filename for distributed raytracing")
    parser.add_argument("exec_stitch", help="executable filename for stitching images together")
    parser.add_argument("output", help="output filename")
    
    args = parser.parse_args()

    if args.x_res % args.x != 0 or args.y_res % args.y != 0:
        parser.error(message="number of pixels must be divisible by the number of slices")
    
    start = time.time()
    num_seg = args.x * args.y

    with Pool(num_seg) as p:
        argvs = lambda_args(args)
        result = p.starmap(lambda_raytracing, argvs)
    print(result)

    if num_seg > 1:
        result = lambda_stitch(args.x_res, args.y_res, args.x, args.y, args.exec_stitch, args.output)
        print(result)     
    
    end = time.time()
    print(end-start)
