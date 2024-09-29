from DATABASE.memory import name, gglink, ytblink, flink, ttlink, etclink, ailogo, introlink, spe
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

from update import Update, ulink

from DATABASE.dbnote import NoteDatabase, nlink

from DATABASE.dbtodo import TodoListManager, tolink

from DATABASE.dbmuctieu import GoalsDatabase, glink

from DATABASE.dbghichu import NotesManager, nslink

from DATABASE.dbautopen import WebLinkManager, alink

from DATABASE.dbmusic import MusicDatabase, mlink

from DATABASE.dbschedule import ScheduleReader, schelink, TimetableGenerator

from DATABASE.dbappointment import AppointmentManager, applink

from DATABASE.dbhabit import HabitManager, halink

from DATABASE.dbapi import APIManager, apilink

import threading

from tkinter import filedialog

palm.configure(api_key='AIzaSyBAYU3roNE4Du-kv9-gnCqRp34sqSg7EkQ')
def add_word_mean_to_file(word, mean, file_path="C:\\Program Files (x86)\\TSAN\\MEMRAP\\datastorage\\tempv.txt"):
    try:
        # Mở tệp với chế độ ghi
        with open(file_path, 'a') as file:
            # Ghi từ và nghĩa vào tệp theo định dạng word:mean
            file.write(f"{word}:{mean}\n")
        print(f"Đã thêm từ '{word}' với nghĩa '{mean}' vào '{file_path}' thành công.")
    except Exception as e:
        print(f"Có lỗi xảy ra khi thêm từ vào tệp: {e}")
class Tsin:

    def __init__(self):
        try:
            self.translator = Translator(to_lang='en', from_lang='vi')
            self.response = "👍👍✅"
            self.last_intro_date = self.load_last_intro_date()
            self.application = {
                "read:": self.read_text,
                "bw:": self.block_website,
                "gg:": self.google_search,
                "ytb:": self.youtube_search,
                "tt:": self.tiktok_search,
                "fb:": self.facebook_search,
                "trans:": self.translate_text,
                "note:": self.note_manager,
                "music:": self.music_song_manager,
                "link:": self.autopen_link_manager,
                "gc:": self.ghi_chu_tien_trinh,
                "goal:": self.goals_manager,
                "todo:": self.to_do_list,
                "habit:": self.habit_challange_manager,
                "tkb:": self.schedule_manager,
                "app:": self.appointment_manager,
                "update:": self.update_body_brain,
                "review:": self.synthesize,
                "sb:": self.init_search_bar,
                "?:": self.guide,
                "cc:": self.changecolor,
                "open:": self.open_link,
                "api:": self.manage_api_key,
                "mod:": self.change_model,
                "napi:": self.editapi
            }
            self.other_applications = {}
            self.Fcolor = {
                "GREEN": Fore.GREEN,
                "RED": Fore.RED,
                "YELLOW": Fore.YELLOW,
                "BLUE": Fore.BLUE,
                "MAGENTA": Fore.MAGENTA,
                "CYAN": Fore.CYAN,
                "WHITE": Fore.WHITE,
            }
            self.Bcolor = {
                "GREEN": Back.GREEN,
                "RED": Back.RED,
                "YELLOW": Back.YELLOW,
                "BLUE": Back.BLUE,
                "MAGENTA": Back.MAGENTA,
                "CYAN": Back.CYAN,
                "WHITE": Back.WHITE,
                "BLACK": Back.BLACK,
            }
            self.Stylecolor = {
                "NORMAL": Style.NORMAL,
                "BRIGHT": Style.BRIGHT,
                "DIM": Style.DIM,
            }
            self.update_application()
            self.SB = None
            self.user_input_queue = queue.Queue()
            self.bar = True
            self.readmode = False
            self.messs = []
            self.cur_Fcolor = Fore.GREEN
            self.cur_Bcolor = Back.BLACK
            self.cur_Style = Style.BRIGHT
            self.cur_model = 0 #bard
            self.model_list = ["bard","chatgpt-3.5"]
        except Exception as e:
            print(e)
            print("ERROR =>  !      INIT CHATBOT     ! 😡 🤬 😡")
    def editapi(self,query):
        query = query.strip()
        print(f"Do you sure to change api={query}? (y | n)")
        op = self.get_input("Enter >>>")
        if op == 'y':
            if self.cur_model == 0:
                palm.configure(query)
            elif self.cur_model == 1:
                openai.api_key = query
        else:
            return
    def change_model(self, query):
        print(f">>> Current Model {self.model_list[self.cur_model]}")
        for i,model in enumerate(self.model_list, start=0):
            print(f"{i}  {model}")
        print()
        try:
            new_model = self.get_input("Enter you new model pos (q)>>>")
            if new_model.strip() == 'q':
                return
            new_model = int(new_model)
        except Exception as e:
            print(e)
            print("ERROR =>  !      MODEL POS     ! 😡 🤬 😡")
            self.change_model("")
        self.messs = []
        self.cur_model = new_model
        if new_model == 1:
            openai.api_key = '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'
            system_msg = self.get_input("What type of chatbot would you like to create? (q)")
            if system_msg.strip() == 'q':
                return
            self.messs.append({"role": "system", "content": system_msg})
    def run_chatbot(self):
        try:
            self.intro()
            sb_thread = threading.Thread(target=self.create_sb)
            sb_thread.start()
            ghi_chu = NotesManager(nslink)
            introhere = f"{self.cur_Fcolor}{self.cur_Bcolor}{self.cur_Style}\nSearch Bar is opening !\n\n\n<<< Đây là ghi chú và tiến trình hiện tại >>>\n\n{ghi_chu.display_notes()} \n\n\nDo you want to synthesize? ( y | n ) >>>\n"
            self.generate_chat(introhere)
            ghi_chu.close_connection()
            option = self.get_input("Bạn >>>")
            if option == 'y':
                self.synthesize("")
            else:
                pass
            print(f"\nChat Bot Has Been Initialized\n")
            while True:
                msg = self.get_input(f"{self.cur_Fcolor}{self.cur_Bcolor}{self.cur_Style}Bạn >>>")
                if not msg.strip():
                    continue
                print()
                ans = self.reply(msg.lower())
                if ans == "break":
                    print("\nPlease Close The Search Bar To Quit ! 👌👍✅")
                    return
                if self.readmode:
                    self.read_text("")
        except Exception as e:
            print(e)
            print("RUN CHATBOT UNSUCCESSFULLY ! 😓 😩 😖 😰")
            print("ERROR =>  !      RUN CHATBOT     ! 😡 🤬 😡")
            self.run_chatbot()
            return
    def inp(self, text="Enter"):
        print(text + "       ('send' = stop)")
        content_lines = []
        while True:
            line = input()
            if line.lower().strip() == "send":
                break
            content_lines.append(line)
        content = "\n".join(content_lines)
        return content.strip()
    def get_input(self, text):
        try:
            if self.bar:
                msg_from_searchbar = ""
                print(text)
                while msg_from_searchbar == "":
                    if self.bar:
                        try:
                            msg_from_searchbar = self.user_input_queue.get(timeout=0.1)
                        except queue.Empty:
                            msg_from_searchbar = ""
                    else:
                        break
                if msg_from_searchbar != "":
                    print(msg_from_searchbar)
                    return msg_from_searchbar
                else:
                    msg = self.inp(text)
                    return msg
            else:
                msg = self.inp(text)
                return msg
        except Exception as e:
            print(e)
            print("ERROR =>  !      GET INPUT     ! 😡 🤬 😡")
            self.get_input("")
            return
    def reply(self, msg):
        try:
            if msg.strip() == 'quit' or msg.strip() == 'bye':
                return "break"
            handled = False
            for keyword, handler in self.application.items():
                if keyword in msg.lower():
                    handler_params = msg.split(keyword)[1].strip()
                    handler(handler_params)
                    handled = True
                    break
            else:
                for keyword, path in self.other_applications.items():
                    if keyword in msg.lower():
                        self.open_link(path)
                        handled = True
                        break
                else:
                    if self.cur_model == 0:
                        self.response = palm.chat(messages=f"{msg.lower().strip()}").last
                        if self.response is None:
                            self.response = "Sorry, I don't understand what you mean.  😓 😩 😖 😰"
                    elif self.cur_model == 1:
                        self.messs.append({"role": "user", "content": f"{msg.lower().strip()}"})
                        respon = openai.ChatCompletion.create(
                            model="gpt-3.5-turbo",
                            messages=self.messs)
                        self.response = respon["choices"][0]["message"]["content"]
                        self.messs.append({"role": "assistant", "content": self.response})
                    print(f"Bot >>> {self.response}\n")
            return self.response
        except Exception as e:
            print(e)
            print("ERROR =>  !     REPLY     ! 😡 🤬 😡")
    def manage_api_key(self, query):
        try:
            api_k = APIManager(apilink)
            print("+---------------------------------------------+")
            print("|            API    KEY   MANAGER             |")
            print("+---------------------------------------------+")
            print(api_k.display_apis())
            print("Do you want to edit a new ? ( y | n ) >>>")
            option = self.get_input("Choose your option >>>").strip().lower()
            if "y" in option:
                new_api = self.get_input("Enter new API ('q') >>>")
                if new_api.strip() == 'q':
                    self.manage_api_key("")
                    return
                api_k.edit_apis_new(new_api)
            else:
                return
            api_k.close_connection()
        except Exception as e:
            print(e)
            print("ERROR =>  !      API     ! 😡 🤬 😡")
        try:
            self.manage_api_key("")
        except:
            self.manage_api_key("")
        return
    def changecolor(self, query):
        try:
            print("Change color")
            print("Foreground color:")
            self.display_color_table(self.Fcolor)
            fcolor_choice = self.get_input(
                f"{self.cur_Fcolor}{self.cur_Bcolor}{self.cur_Style}Enter Foreground color ID (q)>>>")
            if fcolor_choice.strip() == 'q':
                return
            self.cur_Fcolor = self.get_color_code(fcolor_choice, self.Fcolor)

            print(f"{self.cur_Fcolor}{self.cur_Bcolor}{self.cur_Style}Background color:")
            self.display_color_table(self.Bcolor)
            bcolor_choice = self.get_input(
                f"{self.cur_Fcolor}{self.cur_Bcolor}{self.cur_Style}Enter Background color ID (q)>>>")
            if bcolor_choice.strip() == 'q':
                return
            self.cur_Bcolor = self.get_color_code(bcolor_choice, self.Bcolor)

            print(f"{self.cur_Fcolor}{self.cur_Bcolor}{self.cur_Style}Style text:")
            self.display_color_table(self.Stylecolor)
            style_choice = self.get_input(
                f"{self.cur_Fcolor}{self.cur_Bcolor}{self.cur_Style}Enter Style text ID (q)>>>")
            if style_choice.strip() == 'q':
                return
            self.cur_Style = self.get_color_code(style_choice, self.Stylecolor)
            return
        except Exception as e:
            print(e)
            print("ERROR =>  !      CHANGE COLOR     ! 😡 🤬 😡")
            self.changecolor("")
            return
    def display_color_table(self, color_dict):
        for i, (color_name, color_code) in enumerate(color_dict.items(), start=1):
            print(f"{color_code} {i}. {color_name}: {color_code} ")
    def get_color_code(self, choice, color_dict):
        if choice.isdigit() and 1 <= int(choice) <= len(color_dict):
            return list(color_dict.values())[int(choice) - 1]
        elif choice in color_dict:
            return color_dict[choice]
        else:
            print("Lựa chọn không hợp lệ, sử dụng mặc định.")
            return list(color_dict.values())[0]
    def receive_user_input(self, user_input):
        self.user_input_queue.put(user_input)
    def receive_off(self, state):
        self.bar = state
    def give_topmost(self):
        self.hid()
        ctypes.windll.user32.ShowWindow(ctypes.windll.kernel32.GetConsoleWindow(), 1)
    def give_top(self):
        ctypes.windll.user32.ShowWindow(ctypes.windll.kernel32.GetConsoleWindow(), 1)
    def hid(self):
        window = win32console.GetConsoleWindow()
        win32gui.ShowWindow(window, 0)
    def update_application(self):
        try:
            up = Update(ulink)
            functions_data = up.get_all_functions()

            for function in functions_data:
                name, link, function_type = function[1], function[2], function[3]
                if function_type != "✓":
                    self.other_applications[name + ":"] = link

            up.close_database()
        except Exception as e:
            print(e)
        #print(self.other_applications)
    def open_link(self, path):
        try:
            os.startfile(path)
        except Exception as e:
            print(f"Error opening file or link: {e}")
            print("ERROR =>  !      OPEN LINK     ! 😡 🤬 😡")
            return
    def load_last_intro_date(self):
        try:
            with open(introlink, "r") as file:
                return file.read()
        except FileNotFoundError:
            return None
        except Exception as e:
            print(f"Error loading last intro date: {e}")
            return None
    def save_last_intro_date(self, intro_date):
        try:
            with open(introlink, "w") as file:
                file.write(intro_date)
        except Exception as e:
            print(f"Error saving last intro date: {e}")
    def generate_chat(self, text, speed=spe):
        try:
            for char in text:
                print(char, end="")
                time.sleep(speed)
            return
        except Exception as e:
            print(e)
            print("ERROR =>  !      GENERATE CHAT     ! 😡 🤬 😡")
            return
    def create_sb(self):
        try:
            self.bar = True
            search_bar = CTk()
            self.SB = SearchBar(search_bar, self.user_input_queue, self.receive_user_input, self.receive_off,
                                self.give_topmost, self.hid, self.give_top)
            search_bar.mainloop()
            return
        except Exception as e:
            print(e)
            print("ERROR =>  !      CREATE SEARCHBAR     ! 😡 🤬 😡")
    def init_search_bar(self, query):
        try:
            if not self.bar:
                sb_thread = threading.Thread(target=self.create_sb)
                sb_thread.start()
            else:
                print("Search Bar is running ! 👌👍✅")
        except Exception as e:
            print(e)
            print("ERROR =>  !      INIT SEARCHBAR     ! 😡 🤬 😡")
    def intro(self):
        try:
            if self.last_intro_date is not None and self.last_intro_date == datetime.now().strftime("%d/%m/%Y"):
                # print("Hàm intro đã được thực hiện trong ngày hôm nay.")
                return
            self.generate_chat(f"{self.cur_Fcolor}{self.cur_Bcolor}{self.cur_Style}{ailogo}")
            self.last_intro_date = datetime.now().strftime("%d/%m/%Y")
            self.save_last_intro_date(self.last_intro_date)
            return
        except Exception as e:
            print(e)
            print("ERROR =>  !      INTRO     ! 😡 🤬 😡")
    def guide(self, query):
        try:
            print("+----------------------------+")
            print("|         APPLICATIONS       |")
            print("+------------------+---------+")
            print("|     Command      |   Call  |")
            print("+------------------+---------+")
            for key, value in self.application.items():
                function_name = value.__name__ if callable(value) else str(value)
                print(f"|  {key}  |   {function_name}   |")
            for key, value in self.other_applications.items():
                print(f"|  {key}  |   {value}   |")
            print("+------------------+---------+")
            return
        except Exception as e:
            print(e)
            print("ERROR =>  !      GUIDE     ! 😡 🤬 😡")
    def synthesize(self, query):
        try:
            ghi_chu = NotesManager(nslink)
            ghichu = ghi_chu.display_notes()
            ghi_chu.close_connection()

            appointments = AppointmentManager(applink)
            app = appointments.upcoming_appointments()
            appointments.close_connection()

            todo = TodoListManager(tolink)
            to=todo.show_remain_tasks()
            todo.close()

            goal = GoalsDatabase(glink)
            goa=goal.get_goal()
            goal.save_data()

            schedule_reader = ScheduleReader(schelink)
            sche=schedule_reader.current_day_tasks()

            habit = HabitManager(halink)
            ha=habit.display()
            habit.close_connection()

            review = "\n>>>Đây là ghi chú và tiến trình hiện tại:\n" + ghichu + '\n' + "\n>>>Đây là các sự kiện sắp tới:\n" + app + '\n' + "\n>>>Đây là thời khóa biểu cho ngày hôm nay:\n" + sche + '\n' + "\n>>>Đây là các thói quen hiện tại:\n" + ha + '\n' + "\n>>>Đây là các công việc còn lại:\n" + to + '\n' + "\n>>>Đây là mục tiêu hiện tại:\n" + goa + '\n\n'

            self.generate_chat(review)

            return
        except Exception as e:
            print(e)
            print("ERROR =>  !     SYNTHESIZE     ! 😡 🤬 😡")
    def read_text(self, query):
        try:
            if query.strip() == 'on':
                self.readmode = True
                return
            elif query.strip() == 'off':
                self.readmode = False
                return
            engine = pyttsx3.init()
            engine.setProperty('rate', 133)
            engine.setProperty('volume', 3)
            engine.say(self.response)
            engine.runAndWait()
            return
        except Exception as e:
            print(e)
    def block_website(self, query):
        try:
            if query.strip():
                query = query.replace("https://", "")
                option = self.get_input(f"{name}>>>Do you sure to block web:{query} ? (y | n)>>>")
                if option.strip() == 'y':
                    data_block_link = etclink
                    with open(data_block_link, "r", encoding="utf-8") as file:
                        datas = file.readlines()
                    raw_data = [data for data in datas if data.strip()]
                    if query.strip():
                        block_web = "127.0.0.1 " + query.strip() + '\n'
                        raw_data.append(block_web)
                        with open(data_block_link, "w", encoding="utf-8") as file:
                            file.writelines(raw_data)
                        print(f"Block web: {query}")
                        return
                    else:
                        return
                else:
                    return
                # print(raw_data)
                # print(block_web)
            else:
                print("Block web is EMPTY !!! I can find web link !")
        except Exception as e:
            print(e)
            print("ERROR =>  !      BLOCK WEB     ! 😡 🤬 😡")
    def translate_text(self, query):
        try:
            response = self.translator.translate(query)
            print(f"{name} >>> MEAN (Eng): {response}\n")
            return
        except Exception as e:
            print(e)
            print("ERROR =>  !      TRANSLATE     ! 😡 🤬 😡")
    def google_search(self, query):
        try:
            # print(f"Handling 'gg: {query}'")
            temp = query.replace(' ', '+')
            g_url = f"{gglink}"
            webbrowser.open(g_url + temp)
            print(f"{name} >>> I am searching for google about: {query}\n")
            return
        except Exception as e:
            print(e)
            print("ERROR =>  !      GOOGLE SEARCH     ! 😡 🤬 😡")
    def youtube_search(self, query):
        try:
            temp = query.replace(' ', '+')
            y_url = f"{ytblink}"
            webbrowser.open(y_url + temp)
            print(f"{name} >>> I am searching for youtube about: {query}\n")
            return
        except Exception as e:
            print(e)
            print("ERROR =>  !      YOUTUBE     ! 😡 🤬 😡")
    def tiktok_search(self, query):
        try:
            temp = query.replace(' ', '+')
            t_url = f"{ttlink}"
            webbrowser.open(t_url + temp)
            print(f"{name} >>> I am searching for tiktok about: {query}\n")
            return
        except Exception as e:
            print(e)
            print("ERROR =>  !      TIKTOK     ! 😡 🤬 😡")
    def facebook_search(self, query):
        try:
            temp = query.replace(' ', '+')
            t_url = f"{flink}"
            webbrowser.open(t_url + temp)
            print(f"{name} >>> I am searching for facebook about: {query}\n")
            return
        except Exception as e:
            print(e)
            print("ERROR =>  !      FACEBOOK     ! 😡 🤬 😡")
    def to_do_list(self, query):
        try:
            todo = TodoListManager(tolink)
            print("+-------------------------+")
            print("|        TO-DO-LIST       |")
            print("+-------------------------+")
            print(todo.print_task_table())
            print("+------------+---------------+------------+------------+")
            print("|     New    |     Delete    |    Edit    |     Quit   |")
            print("+------------+---------------+------------+------------+")
            print("|   Remain   |     Done(do)  |    Open    |")
            print("+------------+---------------+------------+")
            option = self.get_input("Choose your option >>> ")
            if option.lower() == "n":
                task_name = self.get_input("Enter Task Name ('q')>>>")
                if task_name.strip() == 'q':
                    self.to_do_list("")
                    return
                note = self.get_input("Enter Task Note ('q')>>>")
                if note.strip() == 'q':
                    self.to_do_list("")
                    return
                habit = self.get_input("Is this a Habit ? ( y | n | q)>>>")
                if habit.strip() == 'q':
                    self.to_do_list("")
                    return
                print("Choose Time>>>")
                dtime = todo.get_time()
                print(f"Time >>> {dtime}")
                todo.add_task_new(task_name, note, habit, dtime)
                pass
            elif option.lower() == "do":
                task_id = self.get_input("Enter Done Task ID ('q')>>>")
                if task_id.strip() == 'q':
                    self.to_do_list("")
                    return
                todo.doned_new(task_id)
                pass
            elif option.lower() == "re":
                print(todo.show_remain_tasks())
                pass
            elif option.lower() == "d":
                task_id = self.get_input("Enter Delete Task ID ('q')>>>")
                if task_id.strip() == 'q':
                    self.to_do_list("")
                    return
                todo.delete_task_new(task_id)
                pass
            elif option.lower() == "e":
                task_id = self.get_input("Enter Edit Task ID (q)>>>")
                if task_id.strip() == 'q':
                    self.to_do_list("")
                    return
                task_name = self.get_input("Enter New Task Name ( q | none )>>>")
                if task_name.strip() == 'q':
                    self.to_do_list("")
                    return
                note = self.get_input("Enter New Task Note ( q | none )>>>")
                if note.strip() == 'q':
                    self.to_do_list("")
                    return
                habit = self.get_input("Is this a Habit ? ( y | n | q)>>>")
                if habit.strip() == 'q':
                    self.to_do_list("")
                    return
                elif habit.strip() == 'y':
                    habit = "✓"
                else:
                    habit = " "
                dtime = self.get_input("Do you want to change time? (y | n | q)>>>")
                if dtime.strip() == 'q':
                    self.to_do_list("")
                    return
                todo.edit_task_new(task_id, task_name, note, habit, dtime)
                pass
            elif option.lower() == "op":
                task_id = self.get_input("Enter Open Task ID ('q')>>>")
                if task_id.strip() == 'q':
                    self.to_do_list("")
                    return
                todo.open_task(task_id)
            elif option.lower() == "q":
                todo.close()
                return
            else:
                print("Invalid option. Please choose one of the provided options.")
            todo.close()
        except Exception as e:
            print(e)
            print("ERROR =>  !      TO-DO-LIST     ! 😡 🤬 😡")
        try:
            self.to_do_list("")
        except:
            self.to_do_list("")
        return
    def note_manager(self,query):
        try:
            notes = NoteDatabase(nlink)
            table = notes.get_notes_as_table()
            print("+-------------------+")
            print("|        NOTE       |")
            print("+-------------------+")
            print(table)
            print("+------------+---------------+------------+------------+------------+")
            print("|     New    |     Delete    |     Edit   |    Open    |     Quit   |")
            print("+------------+---------------+------------+------------+------------+")
            option = self.get_input("Choose your option >>>")
            if option.lower() == "n":
                note_name = self.get_input("Enter note name (q)>>>")
                if note_name.strip() == 'q':
                    self.note_manager("")
                    return
                content = self.get_input("Enter note content (q)>>>")
                if content.strip() == 'q':
                    self.note_manager("")
                    return
                notes.add_note_new(note_name, content)
                pass
            elif option.lower() == "d":
                note_id = self.get_input("Enter delete note ID (q)>>>")
                if note_id.strip() == 'q':
                    self.note_manager("")
                    return
                notes.delete_note_new(note_id)
                pass
            elif option.lower() == "e":
                note_id = self.get_input("Enter edit note ID (q)>>>")
                if note_id.strip() == 'q':
                    self.note_manager("")
                    return
                note_name = self.get_input("Enter new note name (q | none)>>>")
                if note_name.strip() == 'q':
                    self.note_manager("")
                    return
                content = self.get_input("Enter new note content (q | none)>>>")
                if content.strip() == 'q':
                    self.note_manager("")
                    return
                notes.edit_note_new(note_id, note_name, content)
                pass
            elif option.lower() == "op":
                note_id = self.get_input("Enter open note ID (q)>>>")
                if note_id.strip() == 'q':
                    self.note_manager("")
                    return
                notes.open_note(note_id)
                pass
            elif option.lower() == "q":
                notes.close_database()
                return
            else:
                print("Invalid option. Please choose one of the provided options.")
            notes.close_database()
        except Exception as e:
            print(e)
            print("ERROR =>  !      NOTE     ! 😡 🤬 😡")
        try:
            self.note_manager("")
        except:
            self.note_manager("")
        return
    def goals_manager(self, query):
        try:
            goal = GoalsDatabase(glink)
            print("+-------------------+")
            print("|        GOAL       |")
            print("+-------------------+")
            print(goal.display_links_table())
            print("+------------+---------------+------------+------------+")
            print("|     New    |     Delete    |     Edit   |     Quit   |")
            print("+------------+---------------+------------+------------+")
            print("|    Open    |     Choose    |")
            print("+------------+---------------+")
            option = self.get_input("Choose your option >>>")
            if option.lower() == "n":
                goal.print_group()
                column_index = self.get_input("Enter column ID (q)>>>")
                if column_index.strip() == 'q':
                    self.goals_manager("")
                    return
                if not goal.print_link(column_index):
                    self.goals_manager("")
                    return
                position = self.get_input("Enter goal position ID (q)>>>")
                if position.strip() == 'q':
                    self.goals_manager("")
                    return
                name = self.get_input("Enter name (q)>>>")
                if name.strip() == 'q':
                    self.goals_manager("")
                    return
                link = self.get_input("Enter note (q)>>>")
                if link.strip() == 'q':
                    self.goals_manager("")
                    return
                goal.add_goal_new(column_index, position, name, link)
                pass
            elif option.lower() == "d":
                goal.print_group()
                column_index = self.get_input("Enter column ID (q)>>>")
                if column_index.strip() == 'q':
                    self.goals_manager("")
                    return
                if not goal.print_link(column_index):
                    self.goals_manager("")
                    return
                position = self.get_input("Enter goal position ID (q)>>>")
                if position.strip() == 'q':
                    self.goals_manager("")
                    return
                goal.delete_goal_new(column_index, position)
                pass
            elif option.lower() == "e":
                goal.print_group()
                column_index = self.get_input("Enter column ID (q)>>>")
                if column_index.strip() == 'q':
                    self.goals_manager("")
                    return
                if not goal.print_link(column_index):
                    self.goals_manager("")
                    return
                position = self.get_input("Enter goal position ID (q)>>>")
                if position.strip() == 'q':
                    self.goals_manager("")
                    return
                name = self.get_input("Enter name (q | none)>>>")
                if name.strip() == 'q':
                    self.goals_manager("")
                    return
                link = self.get_input("Enter note (q | none)>>>")
                if link.strip() == 'q':
                    self.goals_manager("")
                    return
                goal.edit_goal_new(column_index, position, name, link)
                pass
            elif option.lower() == "ch":
                goal.print_group()
                column_index = self.get_input("Enter column ID (q)>>>")
                if column_index.strip() == 'q':
                    self.goals_manager("")
                    return
                if not goal.print_link(column_index):
                    self.goals_manager("")
                    return
                position = self.get_input("Enter goal ID (q)>>>")
                if position.strip() == 'q':
                    self.goals_manager("")
                    return
                goal.choose_processing_new(column_index, position)
                pass
            elif option.lower() == "op":
                print("WHAT DO YOU WANT TO OPEN? ( column | goal )")
                option = self.get_input("(c | g) >>>")
                if option.strip() == 'c':
                    goal.print_group()
                    column_index = self.get_input("Enter column ID (q)>>>")
                    if column_index.strip() == 'q':
                        self.goals_manager("")
                        return
                    goal.open_col(column_index)
                elif option.strip() == 'g':
                    goal.print_group()
                    column_index = self.get_input("Enter column ID (q)>>>")
                    if column_index.strip() == 'q':
                        self.goals_manager("")
                        return
                    if not goal.print_link(column_index):
                        self.goals_manager("")
                        return
                    position = self.get_input("Enter goal ID (q)>>>")
                    if position.strip() == 'q':
                        self.goals_manager("")
                        return
                    goal.open_goal(column_index, position)
                pass
            elif option.lower() == "q":
                goal.save_data()
                return
            else:
                print("Invalid option. Please choose one of the provided options.")
            goal.save_data()
        except Exception as e:
            print(e)
            print("ERROR =>  !      GOAL     ! 😡 🤬 😡")
        try:
            self.goals_manager("")
        except:
            self.goals_manager("")
        return
    def ghi_chu_tien_trinh(self, query):
        try:
            ghi_chu = NotesManager(nslink)
            print("+---------------------------------------------+")
            print("|         TEMPORARY NOTE AND PROCESSING       |")
            print("+---------------------------------------------+")
            print(ghi_chu.display_notes())
            print("Do you want to edit a new ? ( y | n | op)")
            option = self.get_input("Choose your option >>>").strip().lower()
            if "y" in option:
                no = ghi_chu.get_np()
                print(f"\n\n\nTemporary Note:\n\n\n{no[1]}\n\n\n")
                new_note = self.get_input("Enter new note ('q' | 'none')>>>")
                if new_note.strip() == 'q':
                    self.ghi_chu_tien_trinh("")
                    return
                print(f"\n\n\nTemporary Processing:\n\n\n{no[2]}\n\n\n")
                new_process = self.get_input("Enter new process ('q' | 'none')>>>")
                if new_process.strip() == 'q':
                    self.ghi_chu_tien_trinh("")
                    return
                ghi_chu.edit_note_new(new_note, new_process)
            elif option == 'op':
                ghi_chu.opengc()
            else:
                return
            ghi_chu.close_connection()
        except Exception as e:
            print(e)
            print("ERROR =>  !      GHI CHU     ! 😡 🤬 😡")
        try:
            self.ghi_chu_tien_trinh("")
        except:
            self.ghi_chu_tien_trinh("")
        return
    def autopen_link_manager(self, query):
        try:
            auto = WebLinkManager(alink)
            print("+----------------------+")
            print("|        AUTOPEN       |")
            print("+----------------------+")
            auto.display_links_table()
            print("+------------+---------------+------------+------------+------------+")
            print("|     New    |     Delete    |     Edit   |    Open    |     Quit   |")
            print("+------------+---------------+------------+------------+------------+")
            option = self.get_input("Choose your option >>>")
            if option.lower() == "n":
                print("+-------------+-------------+")
                print("|    group    |     link    |")
                print("+-------------+-------------+")
                choice = self.get_input("Choose your option (q)>>>")
                if choice.strip() == "q":
                    self.autopen_link_manager("")
                    return
                if choice == 'g':
                    gname = self.get_input("Enter group name (q)>>>")
                    if gname.strip() == "q":
                        self.autopen_link_manager("")
                        return
                    auto.create_group_new(gname)
                elif choice == 'l':
                    auto.print_group()
                    column_index = self.get_input("Choose add group ID (q)>>>")
                    if column_index.strip() == "q":
                        self.autopen_link_manager("")
                        return
                    name = self.get_input("Enter name (q)>>>")
                    if name.strip() == "q":
                        self.autopen_link_manager("")
                        return
                    link = self.get_input("Enter link (q | open)>>>")
                    if link.strip() == "q":
                        self.autopen_link_manager("")
                        return
                    elif link.strip() == 'open':
                        link = filedialog.askopenfilename(title="Chọn file")
                    auto.add_link_to_group_new(column_index, name, link)
                else:
                    print("Invalid selection.")
                pass
            elif option.lower() == "d":
                print("+-------------+-------------+")
                print("|    group    |     link    |")
                print("+-------------+-------------+")
                choice = self.get_input("Choose your option (q)>>>")
                if choice.strip() == "q":
                    self.autopen_link_manager("")
                    return
                if choice == 'g':
                    auto.print_group()
                    columns_to_delete = self.get_input("Choose delete group ID (',' | 'all' | 'q')>>>")
                    if columns_to_delete.strip() == "q":
                        self.autopen_link_manager("")
                        return
                    auto.delete_group(columns_to_delete)
                elif choice == 'l':
                    auto.print_group()
                    column_index = self.get_input("Choose group ID (q)>>>")
                    if column_index.strip() == "q":
                        self.autopen_link_manager("")
                        return
                    if not auto.print_link(column_index):
                        self.autopen_link_manager("")
                        return
                    link_indices = self.get_input("Choose delete link ID (',' | 'q')>>>")
                    if link_indices.strip() == "q":
                        self.autopen_link_manager("")
                        return
                    auto.delete_link(column_index, link_indices)
                else:
                    print("Invalid selection.")
                pass
            elif option.lower() == "e":
                print("+-------------+-------------+")
                print("|    group    |     link    |")
                print("+-------------+-------------+")
                choice = self.get_input("Choose your option (q)>>>")
                if choice.strip() == "q":
                    self.autopen_link_manager("")
                    return
                if choice == 'g':
                    auto.print_group()
                    column_index = self.get_input("Choose edit group ID (q)>>>")
                    if column_index.strip() == "q":
                        self.autopen_link_manager("")
                        return
                    new_group_name = self.get_input("Enter new name (q | none)>>>")
                    if new_group_name.strip() == "q":
                        self.autopen_link_manager("")
                        return
                    auto.edit_group(column_index, new_group_name)
                elif choice == 'l':
                    auto.print_group()
                    column_index = self.get_input("Choose group ID (q)>>>")
                    if column_index.strip() == "q":
                        self.autopen_link_manager("")
                        return
                    if not auto.print_link(column_index):
                        self.autopen_link_manager("")
                        return
                    link_index = self.get_input("Choose edit link ID (q)>>>")
                    if link_index.strip() == "q":
                        self.autopen_link_manager("")
                        return
                    new_name = self.get_input("Enter new name (q | none)>>>")
                    if new_name.strip() == "q":
                        self.autopen_link_manager("")
                        return
                    new_link = self.get_input("Enter the new link (q | open | none)>>>")
                    if new_link.strip() == "q":
                        self.autopen_link_manager("")
                        return
                    elif new_link.strip() == 'open':
                        new_link = filedialog.askopenfilename(title="Chọn file")
                    auto.edit_link(column_index, link_index, new_name, new_link)
                else:
                    print("Invalid selection.")
                pass
            elif option.lower() == "op":
                auto.print_group()
                column_index = self.get_input("Enter column ID ('q')>>>")
                if column_index.strip() == 'q':
                    self.autopen_link_manager("")
                    return
                if not auto.print_link(column_index):
                    self.autopen_link_manager("")
                    return
                paths_to_open = self.get_input("Enter open path ID (',' | all | 'q')>>>")
                if paths_to_open.strip() == 'q':
                    self.autopen_link_manager("")
                    return
                auto.open_path(column_index, paths_to_open)
                pass
            elif option.lower() == "q":
                return
            else:
                print("Invalid option. Please choose one of the provided options.")
        except Exception as e:
            print(e)
            print("ERROR =>  !      AUTOPEN - LINK     ! 😡 🤬 😡")
        try:
            self.autopen_link_manager("")
        except:
            self.autopen_link_manager("")
        return
    def music_song_manager(self, query):
        try:
            musician = MusicDatabase(mlink)
            print("+--------------------+")
            print("|        MUSIC       |")
            print("+--------------------+")
            print(musician.get_as_table())
            print("+------------+---------------+------------+------------+------------+")
            print("|     New    |     Delete    |     Edit   |    Open    |     Quit   |")
            print("+------------+---------------+------------+------------+------------+")
            option = self.get_input("Choose your option >>>")
            if option.lower() == "n":
                name = self.get_input("Enter name (q) >>>")
                if name.strip() == 'q':
                    self.music_song_manager("")
                    return
                path = self.get_input("Enter path ('open' | q)>>>")
                if path.strip() == 'q':
                    self.music_song_manager("")
                    return
                musician.add_playlist(name, path)
                pass
            elif option.lower() == "d":
                dsongID = self.get_input("Enter delete song ID (q)>>>")
                if dsongID.strip() == 'q':
                    self.music_song_manager("")
                    return
                musician.delete_playlist(dsongID)
                pass
            elif option.lower() == "e":
                esongID = self.get_input("Enter edit song ID (q)>>>")
                if esongID.strip() == 'q':
                    self.music_song_manager("")
                    return
                ename = self.get_input("Enter new name (q)>>>")
                if ename.strip() == 'q':
                    self.music_song_manager("")
                    return
                epath = self.get_input("Enter new path ('open' | q)>>>")
                if epath.strip() == 'q':
                    self.music_song_manager("")
                    return
                musician.edit_playlist(esongID, ename, epath)
                pass
            elif option.lower() == "op":
                osongID = self.get_input("Enter open song ID (q)>>>")
                if osongID.strip() == 'q':
                    self.music_song_manager("")
                    return
                musician.open_path(osongID)
                pass
            elif option.lower() == "q":
                musician.close_database()
                return
            else:
                print("Invalid option. Please choose one of the provided options.")
            musician.close_database()
        except Exception as e:
            print(e)
            print("ERROR =>  !      MUSIC     ! 😡 🤬 😡")
        try:
            self.music_song_manager("")
        except:
            self.music_song_manager("")
        return
    def appointment_manager(self, query):
        try:
            appointments = AppointmentManager(applink)
            print("+--------------------------+")
            print("|        APPOINTMENT       |")
            print("+--------------------------+")
            appointments.display_appointments()
            print("+--------+------------+----------+------------+---------+")
            print("|   New  |   Delete   |   Edit   |  Upcoming  |   Quit  |")
            print("+--------+------------+----------+------------+---------+")
            option = self.get_input("Choose your option >>>")
            if option.lower() == "n":
                name = self.get_input("Enter name('q')>>>")
                if name.strip() == 'q':
                    self.appointment_manager("")
                    return
                type = self.get_input("Is it a event? (y | n | q)>>>")
                if type.strip() == 'q':
                    self.appointment_manager("")
                    return
                appointments.add_app_new(name, type)
                pass
            elif option.lower() == "d":
                app_id = self.get_input("Enter delete ID('q')>>>")
                if app_id.strip() == 'q':
                    self.appointment_manager("")
                    return
                appointments.delete_appointment_new(app_id)
                pass
            elif option.lower() == "e":
                app_id = self.get_input("Enter edit ID('q')>>>")
                if app_id.strip() == 'q':
                    self.appointment_manager("")
                    return
                name = self.get_input("Enter name('q' | none)>>>")
                if name.strip() == 'q':
                    self.appointment_manager("")
                    return
                type = self.get_input("Is it a event? (y | n | q)>>>")
                if type.strip() == 'q':
                    self.appointment_manager("")
                    return
                opt = self.get_input("Do you want to change datetime? (y | n | q)>>>")
                if opt.strip() == 'q':
                    self.appointment_manager("")
                    return
                appointments.edit_appointment_new(app_id, name, type, opt)
                pass
            elif option.lower() == "up":
                print(appointments.upcoming_appointments())
                pass
            elif option.lower() == "q":
                appointments.close_connection()
                return
            else:
                print("Invalid option. Please choose one of the provided options.")
            appointments.close_connection()
        except Exception as e:
            print(e)
            print("ERROR =>  !     APPOINTMENT     ! 😡 🤬 😡")
        try:
            self.appointment_manager("")
        except:
            self.appointment_manager("")
        return
    def habit_challange_manager(self, query):
        try:
            habit = HabitManager(halink)
            print("+--------------------------+")
            print("|           HABIT          |")
            print("+--------------------------+")
            print(habit.display_habits())
            print("+--------+---------+----------+---------+")
            print("|   New  |   Del   |   Edit   |   Quit  |")
            print("+--------+---------+----------+---------+")
            option = self.get_input("Choose your option >>> ")
            if option.lower() == "n":
                name = self.get_input("Enter habit name (q)>>>")
                if name.strip() == 'q':
                    self.habit_challange_manager("")
                    return
                days_remain = self.get_input("Enter habit days (q)>>>")
                if days_remain.strip() == 'q':
                    self.habit_challange_manager("")
                    return
                habit.add_habit_new(name, days_remain)
                pass
            elif option.lower() == "d":
                h_id = self.get_input("Enter habit ID (q)>>>")
                if h_id.strip() == 'q':
                    self.habit_challange_manager("")
                    return
                habit.delete_habit_new(h_id)
                pass
            elif option.lower() == "e":
                habit.display_habits()
                h_id = self.get_input("Enter habit ID (q)>>>")
                if h_id.strip() == 'q':
                    self.habit_challange_manager("")
                    return
                name = self.get_input("Enter habit name (q | none)>>>")
                if name.strip() == 'q':
                    self.habit_challange_manager("")
                    return
                days_remain = self.get_input("Enter habit days (q | none)>>>")
                if days_remain.strip() == 'q':
                    self.habit_challange_manager("")
                    return
                start_day = self.get_input("Do you want to change start day? (y | n | q)>>>")
                if start_day.strip() == 'q':
                    self.habit_challange_manager("")
                    return
                habit.edit_habit_new(h_id, name, days_remain, start_day)
                pass
            elif option.lower() == "q":
                habit.close_connection()
                return
            else:
                print("Invalid option. Please choose one of the provided options.")
            habit.close_connection()
        except Exception as e:
            print(e)
            print("ERROR =>  !     HABIT     ! 😡 🤬 😡")
        try:
            self.habit_challange_manager("")
        except:
            self.habit_challange_manager("")
        return
    def update_body_brain(self, query):
        try:
            up = Update(ulink)
            print("+--------------------+")
            print("|       UPDATE       |")
            print("+--------------------+")
            up.display()
            print("+------------+------------+------------+------------+------------+")
            print("|     New    |     Del    |     Edit   |     Open   |     Quit   |")
            print("+------------+------------+------------+------------+------------+")
            option = self.get_input("Choose your option >>>")
            if option.lower() == "n":
                name = self.get_input("Enter function name (q)>>>")
                if name.strip() == 'q':
                    self.update_body_brain("")
                    return
                link = self.get_input("Enter function link (q | open)>>>")
                if link.strip() == 'q':
                    self.update_body_brain("")
                    return
                elif link.strip() == 'open':
                    link = filedialog.askopenfilename(title="Chọn file")
                f_type = self.get_input("Is it a BODY startup file? ( y | n | q)>>>")
                if f_type.strip() == 'q':
                    self.update_body_brain("")
                    return
                up.add_function_new(name, link, f_type)
                pass
            elif option.lower() == "d":
                fID = self.get_input("Enter delete function ID (q)>>>")
                if fID.strip() == 'q':
                    self.update_body_brain("")
                    return
                up.delete_function_new(fID)
                pass
            elif option.lower() == "e":
                fID = self.get_input("Enter edit function ID (q)>>>")
                if fID.strip() == 'q':
                    self.update_body_brain("")
                    return
                name = self.get_input("Enter function name (q | none)>>>")
                if name.strip() == 'q':
                    self.update_body_brain("")
                    return
                link = self.get_input("Enter function link (q | none | open)>>>")
                if link.strip() == 'q':
                    self.update_body_brain("")
                    return
                elif link.strip() == 'open':
                    link = filedialog.askopenfilename(title="Chọn file")
                f_type = self.get_input("Is it a BODY startup file? ( y | n | q)>>>")
                if f_type.strip() == 'q':
                    self.update_body_brain("")
                    return
                up.edit_function_new(fID, name, link, f_type)
                pass
            elif option.lower() == "op":
                fID = self.get_input("Enter open function ID (q)>>>")
                if fID.strip() == 'q':
                    self.update_body_brain("")
                    return
                up.open_link_new(fID)
                pass
            elif option.lower() == "q":
                up.close_database()
                self.update_application()
                return
            else:
                print("Invalid option. Please choose one of the provided options.")
            up.close_database()
        except Exception as e:
            print(e)
            print("ERROR =>  !      UPDATE     ! 😡 🤬 😡")
        try:
            self.update_body_brain("")
        except:
            self.update_body_brain("")
        return
    def schedule_manager(self, query):
        try:
            # schedule_reader.run()
            schedule_reader = ScheduleReader(schelink)
            print("+------------------------+")
            print("|    SCHEDULE MANAGER    |")
            print("+------------------------+")
            schedule_reader.get_list_schedules()
            print("+------------+----------------+------------+-------------+")
            print("|     New    |     Delete     |     Edit   |     Quit    |")
            print("+------------+----------------+------------+-------------+")
            print("|     Open   |   AllSchedule  |   CurDay   |   NextDay   |")
            print("+------------+----------------+------------+-------------+")
            option = self.get_input("Choose your option >>>")
            if option.lower() == "n":
                new_schedule = self.get_input("Enter new schedule('q')>>>")
                if new_schedule.strip() == 'q':
                    self.schedule_manager("")
                    return
                schedule_reader.add_schedule_new(new_schedule)
                pass
            elif option.lower() == "d":
                sid = self.get_input("Enter delete schedule ID('q')>>>")
                if sid.strip() == 'q':
                    self.schedule_manager("")
                    return
                schedule_reader.delete_schedule_new(sid)
                pass
            elif option.lower() == "e":
                sid = self.get_input("Enter edit schedule ID('q')>>>")
                if sid.strip() == 'q':
                    self.schedule_manager("")
                    return
                new_schedule = self.get_input("Enter new schedule name('q')>>>")
                if new_schedule.strip() == 'q':
                    self.schedule_manager("")
                    return
                schedule_reader.edit_schedule_name_new(sid, new_schedule)
                pass
            elif option.lower() == "op":
                sid = self.get_input("Enter Open schedule ID('q')>>>")
                if sid.strip() == 'q':
                    self.schedule_manager("")
                    return
                fpath, schedule_name = schedule_reader.open_schedule_new(sid)
                if not fpath and not schedule_name:
                    self.schedule_manager("")
                    return
                self.open_schedule_manager(fpath, schedule_name)
                pass
            elif option.lower() == "al":
                schedule_reader.display_combined_schedule()
                pass
            elif option.lower() == "cu":
                print(schedule_reader.current_day_tasks())
                pass
            elif option.lower() == "ne":
                print(schedule_reader.next_day_tasks())
                pass
            elif option.lower() == "q":
                return
            else:
                print("Invalid option. Please choose one of the provided options.")
        except Exception as e:
            print(e)
            print("ERROR =>  !      ALL SCHEDULE     ! 😡 🤬 😡")
        try:
            self.schedule_manager("")
        except:
            self.schedule_manager("")
        return
    def open_schedule_manager(self, fpath, schedule_name):
        try:
            schedule_open = TimetableGenerator(fpath, schedule_name)
            print("+------------- --------+")
            print(f"|    {schedule_name}    |")
            print("+-------------- -------+")
            schedule_open.display_timetable()
            print("+------------+----------------+------------+-------------+")
            print("|     New    |     Delete     |     Edit   |     Quit    |")
            print("+------------+----------------+------------+-------------+")
            option = self.get_input("Choose your option >>>")
            if option.lower() == "n":
                print("Days of the week:")
                schedule_open.display_choices(schedule_open.days_of_week, "Day")
                day_index = self.get_input("Enter day of week ID>>>")
                if day_index.strip() == 'q':
                    self.open_schedule_manager(fpath, schedule_name)
                    return
                print("\nTime of day:")
                schedule_open.display_choices(schedule_open.time_of_day, "Time")
                time_index = self.get_input("Enter time ID>>>")
                if time_index.strip() == 'q':
                    self.open_schedule_manager(fpath, schedule_name)
                    return
                if 1 <= int(day_index) <= len(schedule_open.days_of_week) and 1 <= int(time_index) <= len(
                        schedule_open.time_of_day):
                    work = self.get_input("Enter work name >>>")
                    schedule_open.add_work_new(day_index, time_index, work)
                else:
                    print("Invalid number.")
                    pass
            elif option.lower() == "d":
                print("Days of the week:")
                schedule_open.display_choices(schedule_open.days_of_week, "Day")
                try:
                    day_input = self.get_input("Enter day of week ID ('all' | 'q')>>>")
                    if day_input.strip().lower() == 'all':
                        schedule_open.delete_all_works_in_week()
                        self.open_schedule_manager(fpath, schedule_name)
                        return
                    elif day_input.strip().lower() == 'q':
                        self.open_schedule_manager(fpath, schedule_name)
                        return
                    else:
                        day_index = int(day_input)
                except Exception as e:
                    print(e)
                    print("DELETE WORKS UNSUCCESSFULLY ! 😓 😩 😖 😰")
                    self.open_schedule_manager(fpath, schedule_name)
                    return
                print("\nTime of day:")
                schedule_open.display_choices(schedule_open.time_of_day, "Time")
                try:
                    time_index = self.get_input("Enter the ID time of day ('all' | 'q')>>>")
                    if time_index.strip() == 'all':
                        schedule_open.delete_all_works_for_aday(schedule_open.days_of_week[day_index - 1])
                        self.open_schedule_manager(fpath, schedule_name)
                        return
                    elif time_index.strip().lower() == 'q':
                        self.open_schedule_manager(fpath, schedule_name)
                        return
                    else:
                        time_index = int(time_index)
                except Exception as e:
                    print(e)
                    print("DELETE WORKS UNSUCCESSFULLY ! 😓 😩 😖 😰")
                    self.open_schedule_manager(fpath, schedule_name)
                    return
                if 1 <= day_index <= len(schedule_open.days_of_week) and 1 <= time_index <= len(
                        schedule_open.time_of_day):
                    day = schedule_open.days_of_week[day_index - 1]
                    time = schedule_open.time_of_day[time_index - 1]
                    works = schedule_open.schedule_data.get(f"{schedule_open.schedule_name}", {}).get(day, {}).get(time,
                                                                                                                   [])
                    print(f"\nWorks in {day} {time}:")
                    schedule_open.display_choices(works, "Work")
                    try:
                        work_index = self.get_input("Enter the number ('all' | 'q')>>>")
                        if work_index.lower().strip() == 'all':
                            schedule_open.delete_all_works_in_slot(day, time)
                            self.open_schedule_manager(fpath, schedule_name)
                            return
                        elif work_index.strip().lower() == 'q':
                            self.open_schedule_manager(fpath, schedule_name)
                            return
                        else:
                            work_index = int(work_index)
                    except Exception as e:
                        print(e)
                        print("DELETE WORKS UNSUCCESSFULLY ! 😓 😩 😖 😰")
                        self.open_schedule_manager(fpath, schedule_name)
                        return
                    if 1 <= work_index <= len(works):
                        work_to_delete = works[work_index - 1]
                        works.remove(work_to_delete)
                        schedule_open.save_schedule_data()
                        print("DELETE WORKS SUCCESSFULLY ! 👍 👌 🎊 ✅")
                    else:
                        print("Invalid number.")
                        print("DELETE WORKS UNSUCCESSFULLY ! 😓 😩 😖 😰")
                else:
                    print("Invalid number.")
                    print("DELETE WORKS UNSUCCESSFULLY ! 😓 😩 😖 😰")
                pass
            elif option.lower() == "e":
                print("Days of the week:")
                schedule_open.display_choices(schedule_open.days_of_week, "Day")
                day_index = self.get_input("Enter day of week ID ('q')>>>")
                if day_index.strip() == 'q':
                    self.open_schedule_manager(fpath, schedule_name)
                    return
                else:
                    try:
                        day_index = int(day_index)
                    except Exception as e:
                        print(e)
                        print("EDIT SCHEDULE WORK UNSUCCESSFULLY ! 😓 😩 😖 😰")
                        self.open_schedule_manager(fpath, schedule_name)
                        return
                print("\nTime of day:")
                schedule_open.display_choices(schedule_open.time_of_day, "Time")
                time_index = self.get_input("Enter time ID ('q')>>>")
                if time_index.strip() == 'q':
                    self.open_schedule_manager(fpath, schedule_name)
                    return
                else:
                    try:
                        time_index = int(time_index)
                    except Exception as e:
                        print(e)
                        print("EDIT SCHEDULE WORK UNSUCCESSFULLY ! 😓 😩 😖 😰")
                        self.open_schedule_manager(fpath, schedule_name)
                        return
                if 1 <= day_index <= len(schedule_open.days_of_week) and 1 <= time_index <= len(
                        schedule_open.time_of_day):
                    day = schedule_open.days_of_week[day_index - 1]
                    time = schedule_open.time_of_day[time_index - 1]
                    works = schedule_open.schedule_data.get(f"{schedule_open.schedule_name}", {}).get(day, {}).get(time,
                                                                                                                   [])
                    print(f"\nWorks in {day}:{time} :")
                    schedule_open.display_choices(works, "Work")
                    work_index = self.get_input("Enter work ID ('q')>>>")
                    if work_index.strip() == 'q':
                        self.open_schedule_manager(fpath, schedule_name)
                        return
                    else:
                        try:
                            work_index = int(work_index)
                        except Exception as e:
                            print(e)
                            print("EDIT SCHEDULE WORK UNSUCCESSFULLY ! 😓 😩 😖 😰")
                            self.open_schedule_manager(fpath, schedule_name)
                            return
                    if 1 <= work_index <= len(works):
                        work_to_edit = works[work_index - 1]
                        print(f"Current work name: {work_to_edit}")
                        new_work = self.get_input(f"Enter the new name ('q')>>>")
                        if new_work.strip() == 'q':
                            self.open_schedule_manager(fpath, schedule_name)
                            return
                        schedule_open.edit_work_new(work_index, works, new_work)
                    else:
                        print("EDIT SCHEDULE WORK UNSUCCESSFULLY ! 😓 😩 😖 😰")
                else:
                    print("EDIT SCHEDULE WORK UNSUCCESSFULLY ! 😓 😩 😖 😰")
                pass
            elif option.lower() == "q":
                return
            else:
                print("Invalid option. Please choose one of the provided options.")
        except Exception as e:
            print(e)
            print("ERROR =>  !      ONE SCHEDULE     ! 😡 🤬 😡")
        try:
            self.open_schedule_manager(fpath, schedule_name)
        except:
            self.open_schedule_manager(fpath, schedule_name)
        return



class SearchBar:
    def __init__(self, master, message_queue, callback, call_off, topmo, hid, gitop):
        try:
            self.master = master
            self.master.overrideredirect(1)
            self.user_input_queue = message_queue
            self.callback = callback
            self.call_off = call_off
            self.topmot = topmo
            self.hid = hid
            self.gitop = gitop
            set_appearance_mode("Dark")
            set_default_color_theme("blue")
            try:
                from ctypes import windll, byref, sizeof, c_int
                HWND = windll.user32.GetParent(self.master.winfo_id())
                self.master.iconbitmap("DATABASE/icon.ico")
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
            self.master.bind('<B1-Motion>', self.move_window)
            self.flag = True
            self.master.geometry(f"460x34+{self.master.winfo_screenwidth() // 2}+0")
            self.master.configure(bg="#222121")
            self.text_input = CTkTextbox(self.master, width=340, height=1, font=("Helvetica", 16, 'bold'),
                                         corner_radius=3)
            self.text_input.grid(column=1, row=1, padx=3, pady=3, sticky="nsew")
            self.search_button = CTkButton(self.master, text="➤➤➤", font=('Times New Roman', 16, 'bold'),
                                           fg_color="transparent", hover_color="#333030", text_color="yellow", width=12,
                                           height=4, corner_radius=16, command=self.on_search)
            self.search_button.grid(column=2, row=1, padx=3, pady=3, sticky="nsew")
            self.size_button = CTkButton(self.master, text="-", font=('Times New Roman', 16, 'bold'),
                                         fg_color="transparent", hover_color="#333030", text_color="yellow", width=7,
                                         height=7, corner_radius=16, command=self.resizebar)
            self.size_button.grid(column=0, row=1, padx=3, pady=3, sticky="nsew")
            self.master.attributes('-topmost', True)
            # self.master.overrideredirect(1)
            self.text_input.bind("<Return>", self.on_search)
            self.text_input.bind("<Shift-Return>", self.on_shift_enter)
            for i in range(5):
                self.master.grid_rowconfigure(i, weight=2)
            for i in range(5):
                self.master.grid_columnconfigure(i, weight=2)
            self.master.protocol("WM_DELETE_WINDOW", self.breakbar)
        except Exception as e:
            print(e)
            print("ERORR INIT SEARCH BAR")
    def move_window(self,event):
        self.master.geometry('+{0}+{1}'.format(event.x_root, event.y_root))
    def resizebar(self):
        try:
            self.flag = not self.flag
            if self.flag:
                self.text_input = CTkTextbox(self.master, width=340, height=1, font=("Helvetica", 16, 'bold'),
                                             corner_radius=3)
                self.text_input.grid(column=1, row=1, padx=3, pady=3, sticky="nsew")
                self.search_button = CTkButton(self.master, text="➤➤➤", font=('Times New Roman', 16, 'bold'),
                                               fg_color="transparent", hover_color="#333030", text_color="yellow",
                                               width=12,
                                               height=4, corner_radius=16, command=self.on_search)
                self.search_button.grid(column=2, row=1, padx=3, pady=3, sticky="nsew")
                self.text_input.bind("<Return>", self.on_search)
                self.text_input.bind("<Shift-Return>", self.on_shift_enter)
                self.size_button.configure(text='-', width=10, height=7)
                self.master.geometry(f"460x34")
                self.text_input.bind()
            else:
                self.text_input.destroy()
                self.search_button.destroy()
                self.size_button.configure(text='+', width=110, height=7)
                self.master.geometry(f"10x34")
        except Exception as e:
            print(e)
            print("ERORR RESIZE SEARCH BAR")
    def on_shift_enter(self, event=None):
        current_cursor_position = self.text_input.index(END)
        self.text_input.insert(current_cursor_position, "")
    def on_search(self, event=None):
        try:
            query = self.text_input.get("1.0", END).strip()
            self.text_input.delete("1.0", END)
            if query.strip() == '/':
                self.resizebar()
                self.hid()
                pass
            elif query.strip() == (','):
                self.hid()
                pass
            elif query.strip() == ('.'):
                self.topmot()
                pass
            else:
                self.gitop()
                self.callback(query)
                pass
            return
        except Exception as e:
            print(e)
            print("ERORR ON SEARCH")
    def breakbar(self):
        self.call_off(False)
        try:
            self.master.destroy()
        except:
            pass



#RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN RUN
if __name__ == "__main__":
    #AI = Tsin()
    #AI.run_chatbot()
    search_bar = CTk()
    SB = SearchBar(search_bar, 1,1,1,1,1,1)
    search_bar.mainloop()





'''
    def focus_processing(self,object):
        print("+-------------------+")
        print("|       FOCUS       |")
        print("+-------------------+")
        object.print_table()
        print("+-----------+----------+----------+")
        print("|    NEW    |  DELETE  |   EDIT   |")
        print("+-----------+----------+----------+")
        option = self.get_input("Choose your option (q = quit)>>>")
        if option.lower() == "n":
            time = self.get_input("Enter WORK time (min)>>>")
            rest = self.get_input("Enter REST time (min)>>>")
            music = self.get_input("Enter MUSIC link >>>")
            block = self.get_input("Enter BLOCK WEBS >>>")
            object.insert_data_new(time, rest, music, block)
            pass
        elif option.lower() == "d":
            delete_id = self.get_input("Enter delete ID>>>")
            object.delete_data_new(delete_id)
            pass
        elif option.lower() == "e":
            edit_id = self.get_input("Enter edit ID >>>")
            time = self.get_input("Enter new WORK time (min)>>>")
            rest = self.get_input("Enter new REST time (min)>>>")
            music = self.get_input("Enter new MUSIC link >>>")
            block = self.get_input("Enter new BLOCK WEBS >>>")
            object.edit_data_new(edit_id, time, rest, music, block)
            pass
        elif option.lower() == "q":
            object.close_connection()
            return
        else:
            print("Invalid option. Please choose one of the provided options.")
        try:
            self.focus_processing(object)
        except:
            self.focus_processing(object)
        return
    def focus_mode(self,query):
        focusing = FocusDatabase(folink)
        print("+-----------+----------+")
        print("|   START   |   EDIT   |")
        print("+-----------+----------+")

        ask = self.get_input("What do you choose? >>>")
        if ask == 'st':
            focusing.print_table()
            focus_id = self.get_input("Enter ID to focus on >>>")
            round = self.get_input("ENTER YOUR POMODORO ROUND >>>")
            print("STARTING GAME ...............")
            try:
                cid, ctime, crest, cmusic, cblock = focusing.start_game(int(focus_id), int(round))
                game_thread = threading.Thread(target=focusing.start_game_in_thread,
                                               args=(round, ctime, crest, cmusic, cblock,))
                game_thread.start()
            except:
                pass
            return
        elif ask == 'e':
            self.focus_processing(focusing)
        again = self.get_input("Do you want to continue? ( y | n ) >>>")
        if 'y' in again:
            self.focus_mode("")
        else:
            return
            '''





