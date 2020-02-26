from timeit import default_timer


def timer(func):
    def inner(*args, **kwargs):
        start = default_timer()
        print(func(*args, **kwargs))
        end = default_timer()
        print("Time elapsed: " + str(end - start))

    return inner


@timer
def timefib(n):
    def fib(n):
        if n == 0:
            return 0
        elif n == 1:
            return 1
        else:
            return fib(n - 1) + fib(n - 2)

    return fib(n)


timefib(int(input()))
