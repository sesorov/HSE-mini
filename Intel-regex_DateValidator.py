import re

text = input("Please, type date and time (dd-mm-yy tt:tt):")
strings = ['^[0-3][0-9]-[0|1][0-9]-\d{2}', '\s([0-2][0-9]:[0-5][0-9])$']
output = []

for string in strings:
    regex = re.compile(string)
    match = re.findall(regex, text)
    if match:
        output.append(match[0])
    else:
        if string == strings[0]:
            print('Unsupported date format')
        else:
            print('Unsupported time format')
if output.__len__() == 2:
    print(f"date: {output[0]}")
    print(f"time: {output[1]}")
