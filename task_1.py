import re

BOLD = '\033[1m'
END = '\033[0m'
GREEN = '\033[92m'

words = dict()
with open("text.txt", mode='r') as handle:
    counter = 0
    reversed_text = ""
    for line in handle.readlines():
        for word in line.split():
            reversed_text = word + " " + reversed_text
            word = re.sub('[.,!:?]', '', word).lower()
            counter += 1
            if word in words:
                words[word] += 1
            else:
                words.update({word: 1})
    words = {key: value for key, value in sorted(words.items(), key=lambda item: item[0], reverse=False)}
    words = {key: value for key, value in sorted(words.items(), key=lambda item: item[1], reverse=True)}
    print(GREEN + BOLD + 'Words count: ' + END + f'{counter}')
    print(GREEN + BOLD + 'Top 10 most used words (sorted by alphabet):' + END)
    for i in range(0, 10):
        print(f'{list(words.keys())[i]}: {list(words.values())[i]}')
    print(GREEN + BOLD + 'Reversed text:' + END + f'\n{reversed_text}')
