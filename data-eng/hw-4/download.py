import ast
import subprocess
from concurrent.futures import ThreadPoolExecutor

file_path = 'pmcid_101976_118972.txt'
# Destination local path for XML files
local_path = 'dataset'
# URL base for the S3 object
s3_base_url = 's3://pmc-oa-opendata/oa_comm/xml/all/'
# AWS S3 command
aws_command = 'aws s3 cp {} {} --no-sign-request'
num_threads = 6

def download_file(item):
    s3_url = s3_base_url + f'{item}.xml'
    command = aws_command.format(s3_url, local_path)
    subprocess.run(command, shell=True)
    print(f'File downloaded: {item}')

def download_dataset():
    file_list = []

    # convert the file content to a list
    with open(file_path, 'r') as file:
        content = file.read()
        try:
            file_list = ast.literal_eval(content)
        except (SyntaxError, ValueError) as e:
            print(f'Error during file content conversion: {e}')

    # Use ThreadPoolExecutor to parallelize the file download
    with ThreadPoolExecutor(max_workers=num_threads) as executor:
        executor.map(download_file, file_list)
