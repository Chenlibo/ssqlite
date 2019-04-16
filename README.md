Serverless SQLite Demo Code
===========================

## Environment setup

```
export AWS_DEFAULT_REGION=us-west-2
```

Please note that EFS is not supported in all regions. Check the [Region Table](https://aws.amazon.com/about-aws/global-infrastructure/regional-product-services/) for service availability.
The CloudFormation template used here presently supports the `us-west-2` and `us-east-1` regions.

Optionally set an environment variable for access credentials
```
export AWS_DEFAULT_PROFILE={ MY PROFILE }
```
replacing `{ MY PROFILE }` with the name of a profile in your `~/.aws/credentials` file.


```
export EC2_KEY_PAIR={ MY EC2 KEY }
```

replacing `{ MY EC2 KEY }` with the name of an EC2 key used for ssh access. See [EC2 Key Pair documentation](http://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-key-pairs.html).
This should be a `KeyName` as returned by `aws ec2 describe-key-pairs`.

Select a location for your code on S3

```
export SSQL_CODE_BUCKET= { MY BUCKET NAME }
```

replacing `{ MY BUCKET NAME }` with the name of your choice, e.g., `myusername.ssql.code`.

Set a name for the CloudFormation stack

```
export SSQL_STACK_NAME={ MY STACK NAME }
```

replacing `{ MY STACK NAME }` with a chosen name, e.g., `ssqlite-test`.

## Create the S3 bucket

```
aws s3 mb s3://$SSQL_CODE_BUCKET
```


## Deploy using CloudFormation

Copy the the configuration json file to S3:

```
aws s3 cp lambda-efs.json s3://$SSQL_CODE_BUCKET/lambda-efs.json
```


Build and package the code, upload it to S3:
```
./tools/lambdadeploy.sh --s3-only
```


Create the stack

```
aws cloudformation create-stack \
    --stack-name $SSQL_STACK_NAME \
    --parameters "ParameterKey=KeyName,ParameterValue=$EC2_KEY_PAIR" \
                 "ParameterKey=S3CodeBucket,ParameterValue=$SSQL_CODE_BUCKET"\
    --capabilities CAPABILITY_IAM \
    --template-url https://s3.amazonaws.com/$SSQL_CODE_BUCKET/lambda-efs.json
```

Check the status of stack creation

```
aws cloudformation describe-stacks \
    --stack-name $SSQL_STACK_NAME
```


Later, when ready for cleanup, remove the stack

```
aws cloudformation delete-stack \
    --stack-name { MY_STACK_NAME }
```

replacing `{ MY STACK NAME }` with the name of your stack, e.g., `$SSQL_STACK_NAME`.

## Invoke the Lambda function

```
aws lambda invoke \
    --invocation-type RequestResponse \
    --function-name SQLiteDemo-$SSQL_STACK_NAME \
    --payload '{}' \
    out.txt \
```

view the output
```
cat out.txt
```


## Mount the EFS on the control server

Ssh to the instance
```
ssh -i ~/.ssh/$EC2_KEY_PAIR.pem ec2-user@{ EC2 INSTANCE IP }
```

replacing `{ EC2 INSTANCE IP }` with the public IP address of the instance, as found in the control panel (TODO: improve this).

```
sudo mkdir /efs
sudo chown ec2-user.ec2-user /efs
```

TODO: Need to get the name of the EFS onto the EC2 instance, for now need to
look it up in the AWS console

```
sudo mount -t nfs -o nfsvers=4.1,rsize=1048576,wsize=1048576,hard,timeo=600,retrans=2 \
    { EFS NAME }.efs.$AWS_DEFAULT_REGION.amazonaws.com:/ /efs
```

replacing `{ EFS NAME }` with the file system ID of the EFS volume as found in the AWS console (it should look something like `fs-d795b69e`).

Building SQLite and Python
==========================

This repository includes a binary version of the SQLite library for Python (`dist/_sqlite3.so`) that encompasses SQLite as opposed to loading it from a shared library.
To build it yourself follow these [instructions](build_sqlite_python.md).

Building and Running NFSv4 Benchmark
====================================

## Build the Benchmark

1. In `/nfsv4`, run `make` to build `libnfs4.so`, then `export LD_LIBRARY_PATH=$PWD` to include `libnfs4.so`

2. In `/test`, run `make nfsv4_read_write_test`

3. Set the nfs server with `export NFS4_SERVER=$SSQL_EFS_NAME.efs.$AWS_DEFAULT_REGION.amazonaws.com`

## Run the Benchmark

`./nfsv4_read_write_test write /some_file_name` to run write benchmark

`./nfsv4_read_write_test read /some_file_name` to run read benchmark

Ensure you have Python 3.x installed for instructions below

## Run the Python Benchmarks

`python3 python_simply_demo.py --mount-point=${NFS_SERVER} --test-file=/some_file_name`

`python3 benchmark.py --mount-point=${NFS_SERVER} --test-file=/some_file_name`

## Run the SFS Python Tests

`sudo python3 sfs_test.py ${NFS4_SERVER}`

## Using setup.py to create a local installation, test and clean 
### local installation
`python3 setup.py install`
### test
`python3 setup.py test --ip=${NFS4_SERVER_IP}`
### clean
`python3 setup.py clean`


## Uploading to (Test) PyPI instruction
Reference: https://packaging.python.org/tutorials/packaging-projects/

### Generating distribution archives
Make sure you have the latest versions of setuptools and wheel installed:

`python3 -m pip install --user --upgrade setuptools wheel`

Now run this command from the same directory where setup.py is located (ssqlite/):

`python3 setup.py sdist bdist_wheel`

Once completed should generate two files in the dist directory:

```
dist/
    sfs-0.0.1-py3-none-any.whl
    sfs-0.0.1.tar.gz`
```

### Uploading the distribution archives¶
The first thing you’ll need to do is register an account on Test PyPI and PyPI (two different accounts).

Now that you are registered, you can use twine to upload the distribution packages. You’ll need to install Twine:

`python3 -m pip install --user --upgrade twine`

Once installed, run Twine to upload all of the archives under dist:
#### Upload to Test PyPI
`python3 -m twine upload --repository-url https://test.pypi.org/legacy/ dist/*`

#### Upload to PyPI
`twine upload dist/*`

### Installing your newly uploaded package
#### If you uploaded to Test PyPI
`python3 -m pip install --index-url https://test.pypi.org/simple/ --no-deps sfs`

#### If you uploaded to PyPI
`pip install sfs`