import random


def guess(is_bot: bool, n: int = random.randint(1, 1001),
          attempt: int = 1) -> bool:
    if not is_bot:
        num = random.randint(1, n)
        pre = 0
        print(f"The number is between 1 and {n}. Guess it!")
        while True:
            try:
                pre = int(input("Your suggestion: "))
                while pre != num:
                    print("No, try bigger..." if pre < num else "No, try fewer...")
                    attempt += 1
                    pre = int(input("Your suggestion: "))
            except ValueError:
                print("Sorry, only digits are allowed.")
            if pre == num:
                break
        print(f"Right! You guessed it on {attempt} attempt.")
    else:
        while True:
            try:
                n = int(input("OK, what's the range? Write it: "))
                break
            except ValueError:
                print("Jeez, i need digits. Only digits.")
        print("Now imagine the number. I'll try to guess it, write 'b' if it's too low and 'f' if it's too "
              "big. Write 'y' if i'm right.")
        pre = n // 2
        max_pre, min_pre = n, 1
        while min_pre < max_pre:
            usr_in = input(f"Is it {pre}? -> ")
            if usr_in == 'b':
                min_pre = pre + 1
                pre = (min_pre + max_pre) // 2
                attempt += 1
            elif usr_in == 'f':
                max_pre = pre - 1
                pre = (min_pre + max_pre) // 2
                attempt += 1
            elif usr_in == 'y':
                break
            else:
                print("Sorry, I can't understand. Can you repeat, please? -> ")
        print(f"Your number is {pre}! I guessed it on {attempt} attempt.")
    return pre, attempt


def main() -> None:
    guess(is_bot=True)


if __name__ == "__main__":
    main()
