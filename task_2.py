def rule(n, counter=0) -> int:
    try:
        if n <= 0:
            return 0
    except TypeError:
        return -1
    counter += 1
    return counter if n == 1 else rule(n=3 * n + 1 if n % 2 else n / 2, counter=counter)


def main() -> None:
    iterations = dict()
    for i in range(1, 1001):
        iterations.update({i: rule(i)})
    iterations = {key: value for key, value in sorted(iterations.items(), key=lambda item: item[1], reverse=True)}
    print(f'{list(iterations.keys())[0]} => {list(iterations.values())[0]}')


if __name__ == "__main__":
    main()
