import utils
import json
import os
import sys

def dynamic_progress_bar(target, i, bar_length=40):
    percent = i / target
    progress = int(percent * bar_length)
    bar = "█" * progress + "-" * (bar_length - progress)
    sys.stdout.write("\r[{}] {:.2%} Completed".format(bar, percent))
    sys.stdout.flush()


if __name__ == '__main__':
    to_extract = [os.path.splitext(file)[0] for file in os.listdir("dataset")]
    extracted = [os.path.splitext(file)[0] for file in os.listdir("extracted_data")]

    i = 0
    target = len(to_extract) - len(extracted)

    to_extract = [file for file in to_extract if file not in extracted]

    for file in to_extract:
        data = utils.extract_data(f'dataset/{file}.xml')

        with open(f'extracted_data/{file}.json', 'w') as json_file:
            json.dump(data, json_file, indent=4)

        i += 1
        dynamic_progress_bar(target, i)
