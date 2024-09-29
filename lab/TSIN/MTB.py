#from Database.memory import name, gglink, ytblink, flink, ttlink, etclink, ailogo, introlink, spe
import google.generativeai as palm
from translate import Translator
import webbrowser
import pyttsx3
from datetime import datetime
import time
from customtkinter import *
import queue
import ctypes
import win32gui
import win32console
from colorama import Fore, Style, Back
import openai
import threading
from tkinter import filedialog

class SearchBar:

    def __init__(self, root):
        self.master = root
        try:
            from ctypes import windll, byref, sizeof, c_int
            HWND = windll.user32.GetParent(self.master.winfo_id())
            self.master.iconbitmap("Database/bar_icon.ico")
            title_bar_color = 0x00242424
            title_text_color = 0x00FFFFFF
            windll.dwmapi.DwmSetWindowAttribute(
                HWND,
                35,
                byref(c_int(title_bar_color)),
                sizeof(c_int))
            windll.dwmapi.DwmSetWindowAttribute(
                HWND,
                36,
                byref(c_int(title_text_color)),
                sizeof(c_int))
        except:
            pass
        self.master.title("")
        self.master.overrideredirect(7)
        self.flag = True
        self.master.geometry(f"470x50+{self.master.winfo_screenwidth() // 2}+0")
        self.master.configure(bg="#222121")
        self.master.attributes('-alpha', 0.7)
        self.master.attributes('-toolwindow', True)
        self.master.attributes('-topmost', True)
        self.master.attributes('-transparentcolor', '#222121')
        self.master.wm_attributes("-topmost", True)
        self.master.wm_attributes("-transparentcolor", "#222121")
        self.master.bind("<B1-Motion>", self.move_window)
        self.master.bind("<Control-t>", self.change_position)
        self.text_input = CTkTextbox(self.master, width=340, height=1, font=("Helvetica", 25, 'bold'),
                                     corner_radius=7)
        self.text_input.grid(column=1, row=1, padx=2, pady=3, sticky="nsew")
        self.text_input.bind("<Return>", self.on_search)
        self.text_input.bind("<Shift-Return>", self.on_shift_enter)
        self.search_button = CTkButton(self.master, text="➤➤➤", font=('Times New Roman', 16, 'bold'),
                                       fg_color="transparent", hover_color="#333030", text_color="yellow", width=16,
                                       height=4, corner_radius=25, command=self.on_search)
        self.search_button.grid(column=2, row=1, padx=1, pady=3, sticky="nsew")
        self.size_button = CTkButton(self.master, text="-", font=('Times New Roman', 34, 'bold'),
                                     fg_color="transparent", hover_color="#333030", text_color="yellow", width=43,
                                     height=10, corner_radius=25, command=self.resizebar)
        self.size_button.grid(column=0, row=1, padx=3, pady=3, sticky="nsew")
        for i in range(5):
            self.master.grid_rowconfigure(i, weight=2)
        for i in range(5):
            self.master.grid_columnconfigure(i, weight=2)
        self.master.protocol("WM_DELETE_WINDOW", self.closing)
    def move_window(self,event):
        self.master.geometry('+{0}+{1}'.format(event.x_root, event.y_root))
        self.flag = True
        self.resizebar()
    def change_position(self, event):
        x, y = self.master.winfo_pointerxy()
        self.master.geometry(f"+{x}+{y}")
    def resizebar(self):
        self.flag = not self.flag
        if self.flag:
            self.text_input = CTkTextbox(self.master, width=340, height=1, font=("Helvetica", 25, 'bold'),
                                         corner_radius=7)
            self.text_input.grid(column=1, row=1, padx=2, pady=3, sticky="nsew")
            self.search_button = CTkButton(self.master, text="➤➤➤", font=('Times New Roman', 16, 'bold'),
                                           fg_color="transparent", hover_color="#333030", text_color="yellow", width=16,
                                           height=4, corner_radius=25, command=self.on_search)
            self.search_button.grid(column=2, row=1, padx=1, pady=3, sticky="nsew")
            self.text_input.bind("<Return>", self.on_search)
            self.text_input.bind("<Shift-Return>", self.on_shift_enter)
            self.size_button.configure(text='-', width=43, height=10)
            self.master.geometry(f"500x50")
        else:
            self.text_input.destroy()
            self.search_button.destroy()
            self.size_button.configure(text='+', width=110, height=40)
            self.master.geometry(f"60x50")
    def on_shift_enter(self, event=None):
        current_cursor_position = self.text_input.index(END)
        self.text_input.insert(current_cursor_position, "")
    def on_search(self, event=None):
        query = self.text_input.get("1.0", END).strip()
        self.text_input.delete("1.0", END)
        if query == '\\':
            self.resizebar()
        elif query == 'ok':
            self.master.withdraw()
            self.master.iconify()
        return
    def clear_all_widgets(self,root):
        for widget in root.winfo_children():
            widget.destroy()
    def closing(self):
        self.clear_all_widgets(self.master)
        self.master.destroy()

if __name__ == "__main__":
    search_bar = CTk()
    SB = SearchBar(search_bar)
    search_bar.mainloop()