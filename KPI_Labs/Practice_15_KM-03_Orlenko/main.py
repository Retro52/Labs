from logarithm.logarithm import *
from exp_root.exponentiation import *
from exp_root.root import *
from factorial.factorial import *


def str_to_num(question):
    while True:
        num = input(question)
        try:
            num = float(num)
            break
        except ValueError:
            print(f"{num} is not a number")
    return num


def main_check(num, st):
    while True:
        ans = input(num)
        if num in range(st + 1):
            break
        else:
            print('error')
    return int(ans)


def logs():
    print()
    while True:
        try:
            func_num_local = int(input('Select function from list:\n 1 - Logarithm of x to the given base'
                                       '\n 2 - Natural logarithm'
                                       '\n 3 - Logarithm of x to the base 10\n' 
                                       'Enter option here: '))
            if func_num_local in range(4):
                break
            else:
                print()
                print('There is only 3 functions')
                print()
        except ValueError:
            print()
            print('You only can enter number from 1 to 3')
            print()
    if func_num_local == 1:
        a = str_to_num('Enter argument a (a > 0): ')
        while a <= 0:
            print('Check instructions and try again')
            a = str_to_num('Enter argument a (a > 0): ')
        b = str_to_num('Enter base b (b > 0, b != 1): ')
        while b <= 0 or b == 1:
            print('Check instructions and try again')
            b = str_to_num('Enter base b (b > 0, b != 1): ')
        print(f'log_{b}({a})', log(a, b))
    elif func_num_local == 2:
        a = str_to_num('Enter argument a (a > 0): ')
        while a <= 0:
            print('Check instructions and try again')
            a = str_to_num('Enter argument a (a > 0): ')
        print(f'ln{a}', ln(a))
    elif func_num_local == 3:
        a = str_to_num('Enter argument a (a > 0): ')
        while a <= 0:
            print('Check instructions and try again')
            a = str_to_num('Enter argument a (a > 0): ')
        print(f'lg({a})', lg(a))


def factorial():
    a = str_to_num('Enter number to find his factorial (n >= 0): ')
    while a < 0:
        print('Check instructions and try again')
        a = str_to_num('Enter number to find his factorial (n >= 0): ')
    print(f'{a}! =', fact(a))


def exps():
    print()
    while True:
        try:
            func_num_local = int(input('Select function from list:\n 1 - Exponentiation (square)'
                                       '\n 2 - Exponentiation (cube)'
                                       '\n 3 - *- Advanced - Exponentiation (n)\n' 
                                       'Enter option here: '))
            if func_num_local in range(4):
                break
            else:
                print()
                print('There is only 3 functions')
                print()
        except ValueError:
            print()
            print('You only can enter number from 1 to 3')
            print()
    if func_num_local == 1:
        a = str_to_num('Enter x (exponential number): ')
        print(f'{a}^2 =', exp2(a))
    elif func_num_local == 2:
        a = str_to_num('Enter x (exponential number): ')
        print(f'{a}^3 =', exp3(a))
    elif func_num_local == 3:
        a = str_to_num('Enter x (exponential number): ')
        b = str_to_num('Enter n: ')
        print(f'{a}^{b} =', expn(a, b))


def roots():
    print()
    while True:
        try:
            func_num_local = int(input('Select function from list:\n 1 - Root (square)'
                                       '\n 2 - Root (cube)'
                                       '\n 3 - *- Advanced - Root (n)\n' 
                                       'Enter option here: '))
            if func_num_local in range(4):
                break
            else:
                print()
                print('There is only 3 functions')
                print()
        except ValueError:
            print()
            print('You only can enter number from 1 to 3')
            print()
    if func_num_local == 1:
        a = str_to_num('Enter number to find it`s square root (n >= 0): ')
        while a < 0:
            print('Check instructions and try again')
            a = str_to_num('Enter number to find it`s square root (n >= 0): ')
        print(f'√{a} =', root2(a))
    elif func_num_local == 2:
        a = str_to_num('Enter number to find it`s cube root: ')
        print(f'Cube √{a} =', root3(a))
    elif func_num_local == 2:
        a = str_to_num('Enter number to find it`s cube root: ')
        print(f'Cube √{a} =', root3(a))
    elif func_num_local == 3:
        n = str_to_num('Enter the degree of the root (n > 0): ')
        while n <= 0:
            print('Check instructions and try again')
            n = str_to_num('Enter the degree of the root (n > 0): ')
        a = str_to_num('Enter number to find it`s nth root: ')
        while a < 0 and n % 2 == 0:
            print('Check instructions and try again')
            a = str_to_num('Enter number to find it`s nth root: ')
        print(f'{n}th √{a} =', rootn(a, n))


def main():
    while True:
        try:
            func_num = int(input('Select function from list:\n 1 - factorial function\n 2 - exponential functions'
                                 '\n 3 - root functions\n 4 - logarithmic functions\n'
                                 'Enter option here: '))
            if func_num in range(5):
                break
            else:
                print()
                print('There is only 4 functions')
                print()
        except ValueError:
            print()
            print('You only can enter number from 1 to 4')
            print()
            pass
    if func_num == 1:
        factorial()
    elif func_num == 2:
        exps()
    elif func_num == 3:
        roots()
    elif func_num == 4:
        logs()


def lobby():
    while True:
        main()
        ans = input('Open.Check.Mistake.Repeat? (y/n)')
        if ans.lower() != 'y':
            break


if __name__ == '__main__':
    lobby()
