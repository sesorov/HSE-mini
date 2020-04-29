import this
from functools import reduce


def count_in_line(lst: list) -> list:
    result = []
    for line in lst:
        result.append(len(line))
    return result


def count_in_line_func(lst: list) -> list:
    return list(map(len, lst))


def count_in_line_lst_com(lst: list) -> list:
    return [len(line) for line in lst]


def count_total(lst: list) -> int:
    result = 0
    for line in lst:
        result += len(line)
    return result


def count_total_func(lst: list) -> int:
    return reduce(lambda a, line: a + len(line), lst, 0)


def count_percent(lst: list) -> list:
    result = []
    total = count_total(lst)
    for line_c in count_in_line(lst):
        result.append((line_c / total) * 100)
    return result


def count_percent_func(lst: list, total: int) -> list:
    return list(map(lambda line_c: (line_c / total) * 100, count_in_line(lst)))


def count_percent_list_com(lst: list, total: int) -> list:
    return [(line_c / total) * 100 for line_c in count_in_line(lst)]


def filter_gt(lst: list, percent: float) -> list:
    result = []
    for line_p in count_percent(lst):
        if line_p > percent:
            result.append(line_p)
    return result


def filter_gt_func(lst: list, percent: float) -> list:
    return list(filter(lambda line_p: line_p > percent, count_percent(lst)))


def filter_gt_list_com(lst: list, percent: float) -> list:
    return [line_p for line_p in count_percent(lst) if line_p > percent]


if __name__ == '__main__':
    zen = "".join([this.d.get(c, c) for c in this.s])
    print("#" * 20)
    zen = zen.split('\n')
    print(zen)

    print(count_in_line(zen))
    print(count_in_line_func(zen))
    print(count_in_line_lst_com(zen))

    print(count_total(zen))
    print(count_total_func(zen))

    print(count_percent(zen))
    print(count_percent_func(zen, count_total_func(zen)))
    print(count_percent_list_com(zen, count_total_func(zen)))

    print(filter_gt(zen, 6.6))
    print(filter_gt_func(zen, 6.6))
    print(filter_gt_list_com(zen, 6.6))
