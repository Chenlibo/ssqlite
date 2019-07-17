import subprocess
import json
import time
import os
import  boto3
import logging

def setup_logging():
    """Setup logging that outputs to Cloudwatch."""
    root = logging.getLogger()
    if root.handlers:
        for handler in root.handlers:
            root.removeHandler(handler)

    logging.basicConfig(
            level=os.environ.get("LOGLEVEL", "DEBUG"),
            format="%(asctime)s\t%(levelname)s\t%(filename)s:%(lineno)d:%(funcName)s\t%(message)s")
    logging.info("starting")

def raytracing_handler(event, context):
    
    start = time.time()
    
    # extract arguments
    exec_name = event['exec_name']
    output_file = event["output_file"]
    tnx = str(event["x_res"])
    tny = str(event["y_res"])
    x = str(event["num_ver_slices"])
    y = str(event["num_hor_slices"])
    seg = str(event["segment"])
    
    # copy raytracing binary from s3 to /tmp
    tmpfs_path = "/tmp/"
    exec_tmpfs_path = tmpfs_path+exec_name
    logging.info("Start copy raytracing binary from s3 to /tmp")
    with open(exec_tmpfs_path, "w+b") as f_exec:
        f_exec.write(client.get_object(Bucket=S3_BUCKET, Key=exec_name)["Body"].read())
    
    os.chmod(exec_tmpfs_path, 0o777)
    logging.info("segment #"+seg+": First part finished")
    
    # run raytracing exectuable from /tmp
    logging.info("Starting the second part")
    full_output_filepath = tmpfs_path+output_file+str(seg)+".ppm"
    args = [exec_tmpfs_path, tnx, tny, x, y, full_output_filepath, seg]
    process = subprocess.Popen(args, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    #process.communicate()
    logging.info(process.communicate()[1])
    logging.info("Second part finished")
    
    # copy the ppm file in /tmp to s3
    with open(full_output_filepath, "r") as f_out:
        #client.upload_file(full_output_filepath, S3_BUCKET, f"{output_file}{seg}.ppm")
        client.put_object(Bucket=S3_BUCKET, Body=f_out.read().encode("utf-8"), Key=f"{output_file}{seg}.ppm")
    logging.info("Third part finished")
    
    end = time.time()
    
    return {
        'statusCode': 200,
        'segment': seg,
        'elapsed_time': end-start
    }

AWS_KEY = os.environ["AWS_KEY"]
AWS_SECRET = os.environ["AWS_SECRET"]
S3_BUCKET = os.environ["S3_BUCKET"]
client = boto3.client('s3', aws_access_key_id=AWS_KEY, aws_secret_access_key=AWS_SECRET) 
setup_logging()