#!/bin/bash
set -e 

: ${LAMBDA_FUNCTION_NAME_1?"Must set LAMBDA_FUNCTION_NAME"}
: ${LAMBDA_FUNCTION_NAME_2?"Must set LAMBDA_FUNCTION_NAME"}
: ${LAMBDA_CODE_S3_BUCKET?"Must set LAMBDA_CODE_BUCKET"}
: ${AWS_DEFAULT_REGION?"Must set AWS_DEFAULT_REGION"}

zip -r sfs-raytracing.zip lambda_raytracing_s3.py sfs 
aws s3 cp sfs-raytracing.zip s3://$LAMBDA_CODE_S3_BUCKET/sfs-raytracing.zip
aws s3 cp raytracing s3://$LAMBDA_CODE_S3_BUCKET/raytracing

zip -r sfs-stitch.zip lambda_stitch_s3.py sfs
aws s3 cp sfs-stitch.zip s3://$LAMBDA_CODE_S3_BUCKET/sfs-stitch.zip
aws s3 cp stitch s3://$LAMBDA_CODE_S3_BUCKET/stitch

aws lambda update-function-code \
        --function-name $LAMBDA_FUNCTION_NAME_1 \
        --s3-bucket "$LAMBDA_CODE_S3_BUCKET" \
        --s3-key "sfs-raytracing.zip"

aws lambda update-function-code \
        --function-name $LAMBDA_FUNCTION_NAME_2 \
        --s3-bucket "$LAMBDA_CODE_S3_BUCKET" \
        --s3-key "sfs-stitch.zip" 

rm sfs-raytracing.zip
rm sfs-stitch.zip
