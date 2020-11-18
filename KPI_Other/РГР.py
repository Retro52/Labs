import tkinter as tk

from tkinter import messagebox

import ctypes

# import matplotlib.pyplot as plt

user32 = ctypes.windll.user32


def diff2_table(mx, my):
    n = len(my)
    h = mx[1] - mx[0]

    result = [(my[2] - 2 * my[1] + my[0]) / (h * h)]

    for idx in range(1, n - 1):
        result.append((my[idx + 1] - 2 * my[idx] + my[idx - 1]) / (h ** 2))
    result.append((my[-1] - 2 * my[-2] + my[-3]) / (h * h))

    return result


arrayX = []
arrayY = []
i = 0
y = ''

x = user32.GetSystemMetrics(0)
z = user32.GetSystemMetrics(1)


def click():
    x0 = x_input.get()
    step = h_input.get()
    all_ok = True

    try:
        step = float(step)
        if step <= 0:
            tk.messagebox.showerror(title="Error", message='Not correct input - h is below zero')
            all_ok = False
    except ValueError:
        tk.messagebox.showerror(title="Error", message='Not correct input - h')
        all_ok = False

    try:
        x0 = float(x0)
    except ValueError:
        tk.messagebox.showerror(title="Error", message='Not correct input - x0')
        all_ok = False

    if len(arrayY) < 3:
        all_ok = False
        tk.messagebox.showerror(title="Error", message='List of y must be longer')

    if all_ok:
        array_length = len(arrayY)
        for element in range(0, array_length):
            arrayX.append(x0 + element * step)
        diff_lv2 = diff2_table(arrayX, arrayY)
        calculations_result.configure(
            text='\n'.join('y[' + str(idx) + ']=' + format(number, "0.2f") for idx, number in enumerate(diff_lv2)))


def add_y():
    y_0 = y_value_input.get()
    try:
        y_0 = float(y_0)
        arrayY.append(y_0)
        y_value_input.delete(0, 'end')
        display_y.configure(text='\n'.join([str(word) for word in arrayY]))
    except ValueError:
        y_value_input.delete(0, 'end')
        tk.messagebox.showerror(title="Error", message='Not correct input - y')


def clear_y():
    arrayY.clear()
    display_y.configure(text='\n'.join([str(word) for word in arrayY]))


def clear_all():
    arrayY.clear()
    display_y.configure(text='\n'.join([str(word) for word in arrayY]))
    x_input.delete(0, 'end')
    h_input.delete(0, 'end')
    calculations_result.configure(text='')


root = tk.Tk()
root.config(bg='grey')
root.minsize(round(x * 0.8463541666666667), round(z * 0.7407407407407407))
root.geometry(f"{x}x{z}")
root.title('Second derivative calculator')

tk.messagebox.showinfo(title='Welcome', message='                                          Вітаю.                   \n '
                                                'Ця програма підраховує другу похідну для рівновіддалених точок.'
                                                'Перш за все введіть дані у спеціально для цього призначені поля. '
                                                'Щоб увести у спочатку запишіть його у поле, а потім натисніть'
                                                'на кнопку + поруч. Повторіть, поки не наберете хоча б'
                                                ' 3 (!) значення. Щоб очистити значення у натисніть clear all y.'
                                                'Щоб виконати підрахунок натисніть Calculate. Щоб очистити усі поля'
                                                '(у тому числі і результат) натисніть clear all. Щоб вийти з програми'
                                                'натисніть Quit. Бажаю приємної роботи) ')

canvas = tk.Canvas(root, width=x, height=z)
canvas.pack()

frame = tk.Frame(canvas, bg='white')
frame.place(relx=0, rely=0, relwidth=1, relheight=1)

title = tk.Label(frame, text='Enter x0', bg='white', font=12)
title.place(rely=0, relx=0.01)

x_input = tk.Entry(frame, bg='#fafafa', font=20)
x_input.place(rely=0.05, relx=0.01)

title = tk.Label(frame, text='Enter h', bg='white', font=12)
title.place(rely=0, relx=0.4)

h_input = tk.Entry(frame, bg='#fafafa', font=20)
h_input.place(rely=0.05, relx=0.4)

btn = tk.Button(frame, text='Calculate', bg='white', command=click, font=25)
btn.configure(height=1, width=11)
btn.place(rely=0.9, relx=0.45)

title_y = tk.Label(frame, text='Enter multiple y', bg='white', font=12)
title_y.place(rely=0, relx=0.797)

frame_for_y = tk.Frame(frame, bg='white', width=x * 0.2, height=z * 0.8)
frame_for_y.place(relx=0.8, rely=0.05)

y_value_input = tk.Entry(frame_for_y, bg='#fafafa', width=round(x * 0.01135), font=20)
y_value_input.pack()

display_y = tk.Message(frame_for_y, text="", bg='white', font=12)
display_y.config(width=x * 0.2)
display_y.pack()

btn_add_y = tk.Button(frame_for_y, text='+', bg='#fafafa', command=add_y)
btn_add_y.configure(width=2, height=1)
btn_add_y.place(relx=0.87, rely=0)

btn_clear_all_y = tk.Button(frame, text='Clear all y', bg='pink', font=20, command=clear_y)
btn_clear_all_y.place(rely=0.9, relx=0.825)

btn_clear_all = tk.Button(frame, text='Clear all', bg='pink', font=10, command=clear_all)
btn_clear_all.place(relx=0.45, rely=0.105)

text_for_result = tk.Label(frame, text="Second derivative:", font=12, bg='white')
text_for_result.place(relx=0.01, rely=0.105)

calculations_result = tk.Message(frame, text='', bg='white', font=12)
calculations_result.place(relx=0.01, rely=0.14)

quit_button = tk.Button(frame, text='Quit', fg='red', bg='black', command=root.destroy, font=20)
quit_button.configure(width=15)
quit_button.place(rely=0.9, relx=0.01)

root.mainloop()
