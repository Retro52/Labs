import random

import tkinter as tk

from tkinter import messagebox

import ctypes

user32 = ctypes.windll.user32

card_list = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]

a = int(random.uniform(1, len(card_list)))
a = card_list[a]
card_list.remove(a)

b = int(random.uniform(1, len(card_list)))
b = card_list[b]
card_list.remove(b)

c = int(random.uniform(1, len(card_list)))
c = card_list[c]
card_list.remove(c)

d = int(random.uniform(1, len(card_list)))
d = card_list[d]
card_list.remove(d)

f = 0

g = 0

h = 0

e = 0

r_n = 1

x = user32.GetSystemMetrics(0)
z = user32.GetSystemMetrics(1)


def passing():
    global a
    global b
    global c
    global d
    global e
    global f
    global g
    global h
    global player_score
    global AI_score
    global r_n
    if r_n == 1:
        if 6 > d and b + e < random.uniform(13, 18):
            f = int(random.uniform(1, len(card_list)))
            f = card_list[f]
            card_list.remove(f)
            AI_card_3.configure(text=str(f))
            points.configure(text=f'AI:\nx+{d + f + g}/21\n\n\n\n\n\n\n\n\n\n\n\n\n\nYOU:\n{a + b + e + g}/21')
        r_n = 2
    elif r_n == 2:
        if c + d + f <= random.uniform(13, 15):
            h = int(random.uniform(1, len(card_list)))
            h = card_list[h]
            card_list.remove(h)
            AI_card_4.configure(text=str(h))
            points.configure(text=f'AI:\nx+{d + f + g}/21\n\n\n\n\n\n\n\n\n\n\n\n\n\nYOU:\n{a + b + e + g}/21')
        player_sum = a + b + e + g
        ai_sum = c + d + f + h

        if player_sum > 21:
            if player_sum == ai_sum:
                result.configure(text='Draw', fg='purple')
            elif player_sum < ai_sum:
                result.configure(text='You won!', fg='green')
                player_score += 1
            elif player_sum > ai_sum:
                result.configure(text='You lost!', fg='red')
                AI_score += 1
        elif ai_sum > 21:
            result.configure(text='You win', fg='green')
            player_score += 1
        elif ai_sum > player_sum:
            result.configure(text='You lost', fg='red')
            AI_score += 1
        elif player_sum > ai_sum:
            player_score += 1
            result.configure(text='You won!', fg='green')
        elif player_sum == ai_sum:
            result.configure(text='Draw', fg='purple')

        score.configure(text=f'YOU:\n{player_score}\nAI:\n{AI_score}')
        points.configure(text=f'AI:\n{ai_sum}/21\n\n\n\n\n\n\n\n\n\n\n\n\n\nYOU:\n{player_sum}/21')
        AI_card_1.configure(text=str(c))
        r_n = 3
        if AI_score - player_score == 10:
            messagebox.showinfo(title='Achievement reached', message='Achievement reached: \nNo chances')
        elif AI_score - player_score == 5:
            messagebox.showinfo(title='Achievement reached', message='Achievement reached: \nJust not your lucky day')
        elif player_score - AI_score == 10:
            messagebox.showinfo(title='Achievement reached', message='Achievement reached: \nSkynet - destroyed')
        elif player_score - AI_score == 5:
            messagebox.showinfo(title='Achievement reached', message='Achievement reached: \nDungeon master')


def click():
    global a
    global b
    global c
    global d
    global e
    global f
    global g
    global h
    global player_score
    global AI_score
    global r_n
    if r_n == 1:
        e = int(random.uniform(1, len(card_list)))
        e = card_list[e]
        card_list.remove(e)
        my_card_3.configure(text=str(e))
        points.configure(text=f'AI:\nx+{d + f + g}/21\n\n\n\n\n\n\n\n\n\n\n\n\n\nYOU:\n{a + b + e + g}/21')
        if 6 > d and b + e < random.uniform(13, 18):
            f = int(random.uniform(1, len(card_list)))
            f = card_list[f]
            card_list.remove(f)
            AI_card_3.configure(text=str(f))
            points.configure(text=f'AI:\nx+{d + f + g}/21\n\n\n\n\n\n\n\n\n\n\n\n\n\nYOU:\n{a + b + e + g}/21')
        r_n = 2
    elif r_n == 2:
        g = int(random.uniform(1, len(card_list)))
        g = card_list[g]
        card_list.remove(g)
        my_card_4.configure(text=str(g))
        points.configure(text=f'AI:\nx+{d + f + g}/21\n\n\n\n\n\n\n\n\n\n\n\n\n\nYOU:\n{a + b + e + g}/21')
        if c + d + f <= random.uniform(11, 14):
            h = int(random.uniform(1, len(card_list)))
            h = card_list[h]
            card_list.remove(h)
            AI_card_4.configure(text=str(g))
            points.configure(text=f'AI:\nx+{d + f + h}/21\n\n\n\n\n\n\n\n\n\n\n\n\n\nYOU:\n{a + b + e + g}/21')
        player_sum = a + b + e + g
        ai_sum = c + d + f + h

        if player_sum > 21:
            if player_sum == ai_sum:
                result.configure(text='Draw', fg='purple')
            elif player_sum < ai_sum:

                result.configure(text='You won!', fg='green')
                player_score += 1
            elif player_sum > ai_sum:
                result.configure(text='You lost!', fg='red')
                AI_score += 1
        elif ai_sum > 21:
            result.configure(text='You win', fg='green')
            player_score += 1
        elif ai_sum > player_sum:
            result.configure(text='You lost', fg='red')
            AI_score += 1
        elif player_sum > ai_sum:
            player_score += 1
            result.configure(text='You won!', fg='green')
        elif player_sum == ai_sum:
            result.configure(text='Draw', fg='purple')
        score.configure(text=f'YOU:\n{player_score}\nAI:\n{AI_score}')
        points.configure(text=f'AI:\n{ai_sum}/21\n\n\n\n\n\n\n\n\n\n\n\n\n\nYOU:\n{player_sum}/21')
        AI_card_1.configure(text=str(c))
        r_n = 3
        if AI_score - player_score == 10:
            messagebox.showinfo(title='Achievement reached', message='Achievement reached: \nNo chances')
        elif AI_score - player_score == 5:
            messagebox.showinfo(title='Achievement reached', message='Achievement reached: \nJust not your lucky day')
        elif player_score - AI_score == 10:
            messagebox.showinfo(title='Achievement reached', message='Achievement reached: \nSkynet - destroyed')
        elif player_score - AI_score == 5:
            messagebox.showinfo(title='Achievement reached', message='Achievement reached: \nDungeon master')


def play_again():
    global card_list
    global a
    global b
    global c
    global d
    global e
    global f
    global g
    global h
    global player_score
    global AI_score
    global r_n
    if r_n == 3:
        r_n = 1
        card_list = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
        #
        a = int(random.uniform(1, len(card_list)))
        a = card_list[a]
        card_list.remove(a)
        #
        b = int(random.uniform(1, len(card_list)))
        b = card_list[b]
        card_list.remove(b)
        #
        c = int(random.uniform(1, len(card_list)))
        c = card_list[c]
        card_list.remove(c)
        #
        d = int(random.uniform(1, len(card_list)))
        d = card_list[d]
        card_list.remove(d)
        e = 0
        f = 0
        g = 0
        h = 0
        my_card_1.configure(text=str(a))
        my_card_2.configure(text=str(b))
        my_card_3.configure(text=str(e))
        my_card_4.configure(text=str(g))
        AI_card_1.configure(text='*')
        AI_card_2.configure(text=str(d))
        AI_card_3.configure(text=str(f))
        AI_card_4.configure(text=str(h))
        points.configure(text=f'AI:\nx+{d + f + g}/21\n\n\n\n\n\n\n\n\n\n\n\n\n\nYOU:\n{a + b + e + g}/21')
        result.configure(text='', fg='red')


player_score = 0
AI_score = 0

root = tk.Tk()
root.config()
root.geometry(f"{round(0.83333*x)}x{round(0.83333*z)}")
root.title('21 point')
root.minsize(width=round(0.83333*x), height=round(0.83333*z))

frame = tk.Frame(root, width=1280, height=720)
frame.pack()

score = tk.Message(frame, text=f'YOU:\n{player_score}\nAI:\n{AI_score}', font=24)
score.place(relx=0.05, rely=0.4)

my_card_1 = tk.Message(frame, text=str(a), font=40)
my_card_1.place(relx=0.2, rely=0.75)

my_card_2 = tk.Message(frame, text=str(b), font=40)
my_card_2.place(relx=0.4, rely=0.75)

my_card_3 = tk.Message(frame, text=str(e), font=40)
my_card_3.place(relx=0.6, rely=0.75)

my_card_4 = tk.Message(frame, text=str(g), font=40)
my_card_4.place(relx=0.8, rely=0.75)

AI_card_1 = tk.Message(frame, text='*', font=40)
AI_card_1.place(relx=0.2, rely=0.25)

AI_card_2 = tk.Message(frame, text=str(d), font=40)
AI_card_2.place(relx=0.4, rely=0.25)

AI_card_3 = tk.Message(frame, text=str(f), font=40)
AI_card_3.place(relx=0.6, rely=0.25)

AI_card_4 = tk.Message(frame, text=str(h), font=40)
AI_card_4.place(relx=0.8, rely=0.25)

btn_omc = tk.Button(command=click, text='Take one more card')
btn_omc.place(relx=0.8, rely=0.85)

btn_pass = tk.Button(text='Pass', command=passing)
btn_pass.place(relx=0.8, rely=0.89)

points = tk.Message(frame, text=f'AI:\nx+{d + f + g}/21\n\n\n\n\n\n\n\n\n\n\n\n\n\nYOU:\n{a + b + e + g}/21', font=24)
points.place(relx=0.92, rely=0.225)

result = tk.Message(frame, text='', font=30)
result.place(relx=0.45, rely=0.47)

btn_play_again = tk.Button(command=play_again, text='Play again')
btn_play_again.place(relx=0.8, rely=0.93)

btn_quit = tk.Button(text='QUIT', fg='red', bg='black', font=20, command=root.destroy)
btn_quit.place(relx=0.05, rely=0.92)

root.mainloop()
