import requests
import os
userData = requests.get('https://api.github.com/user', auth=(os.environ["GITHUB_LOGIN"], os.environ["GITHUB_PASSWORD"])).json()["avatar_url"]
pic = requests.get(userData)
with open("ava.jpeg", "wb") as handle:
    handle.write(pic.content)
