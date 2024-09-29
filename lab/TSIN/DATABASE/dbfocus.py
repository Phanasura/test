folink = 'DATABASE/notes_database.db'
import sqlite3
from tabulate import tabulate
import webbrowser
import threading
import time
from customtkinter import *
import pygame
from plyer import notification
import random
set_appearance_mode("Dark")
set_default_color_theme("blue")

class FocusProgram:
    def __init__(self, master, num_pomodoros, tdo, tres):
        self.master = master
        self.master.title("Focus Program")
        #self.master.geometry("200x335+0+0")
        try:
            from ctypes import windll, byref, sizeof, c_int
            HWND = windll.user32.GetParent(self.master.winfo_id())
            # self.root.iconbitmap("images/icon1.ico")
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
        self.work_time = tdo
        self.break_time = tres
        self.var = IntVar()
        self.secon = False
        self.numcircle = num_pomodoros
        self.status = ["Work","Rest","Continue?"]
        self.status_color = ["red","blue","yellow"]
        self.emo = [
            "(^_^)",
            "ヽ(＾Д＾)ﾉ",
            "ヾ(＾-＾)ノ",
            "ヽ(´▽`)/",
            "＼(＾▽＾)／",
            "(^o^)丿",
            "ヾ(＾ω＾)ﾉ",
            "＼(≧▽≦)／",
            "(^o^)/",
            "ヽ(＾Д＾)ﾉ",
            "(＾◡＾)",
            "＼(＾▽＾)／",
            "ヾ(＾-＾)ノ",
            "(*^▽^*)",
            "ヽ(°▽°)ノ",
            "ヾ(＠＾▽＾＠)ﾉ",
            "(*≧ω≦)",
            "ヾ(≧▽≦*)o",
            "(≧∇≦)/",
            "(⌒‿⌒)",
            "(*^ω^*)",
            "ヽ(＾ω＾)ﾉ",
            "＼(＾▽＾)／",
            "(*^_^*)",
            "ヽ(*・ω・)ﾉ",
            "(≧ω≦)",
            "(^▽^)/",
            "ヾ(≧▽≦*)",
            "ヾ(＾∇＾)",
            "(*≧▽≦)",
            "＼(＾▽＾)／",
            "(＾◡＾)",
            "(￣▽￣)/",
            "ヾ(≧▽≦)ﾉ",
            "(^◡^ )",
            "(^_^)v",
            "＼(^o^)／",
            "(≧ω≦)/",
            "ヽ(*⌒∇⌒*)ﾉ",
            "(*≧ω≦)",
            "ヾ(＾ω＾)ﾉ",
            "(^▽^)/",
            "(ﾉ´▽｀)ﾉ♪",
            "(*≧▽≦)",
            "(✯◡✯)",
            "ヽ(✿◕‿◕)ﾉ",
            "(ノ◕ヮ◕)ノ*:・゚✧",
            "(^_^)v",
            "ヾ(＾∇＾)",
            "(*≧▽≦)",
            "＼(＾▽＾)／",
            "(＾◡＾)",
            "(￣▽￣)/",
            "ヾ(≧▽≦)ﾉ",
            "(^◡^ )",
            "(^_^)v",
            "＼(^o^)／",
            "(≧ω≦)/",
            "ヽ(*⌒∇⌒*)ﾉ",
            "(*≧ω≦)",
            "ヾ(＾ω＾)ﾉ",
            "(^▽^)/",
            "(ﾉ´▽｀)ﾉ♪",
            "(*≧▽≦)",
            "(✯◡✯)",
            "ヽ(✿◕‿◕)ﾉ",
            "(°ロ°)☝",
            "(¬‿¬)",
            "(≧◡≦)",
            "(ᵔᴥᵔ)",
            "(¬‿¬)",
            "＼(≧▽≦)／",
            "ʘ‿ʘ"
        ]
        self.icocheer = [
            "👏", "👍", "🙌", "🎉", "👌", "😄", "😊", "🌟", "💪", "👊",
            "👋", "🌈", "✨", "🥳", "😎", "🤗", "🥇", "🏆", "🎊", "🔥",
            "💯", "🚀", "😃", "🤩", "😇", "👑", "💖", "🌺", "❤️", "🌈🚀",
            "🎈", "🎆", "🎇", "🎁", "💥", "🌠", "💃", "🕺", "🎵", "🔝",
            "🎀", "🏅", "🏵️", "🎖️", "🌞", "🌍", "🌠", "🚴‍♂️", "🚵‍♀️", "🤹‍♂️",
            "🎮", "🎤", "🎸", "🎺", "🎷", "🎭", "🎪", "🎬", "🎥", "📣"
        ]
        #print(len(self.emo))
        self.master.geometry("123x85+0+0")
        self.start_button = CTkButton(self.master, text="START", width=20, height=20, command=self.create_ui, corner_radius=32, fg_color="#4158D0", hover_color="#C850C0", border_color="#FFCC70", border_width=2)
        self.start_button.place(x=95, y=50, anchor=SE)
        self.flag = False
        self.timer_running = False
        self.master.attributes('-topmost', True)
        self.master.protocol("WM_DELETE_WINDOW", self.on_closing)
    def create_ui(self):
        self.status_label = CTkLabel(self.master, text=f"{self.status[0]}", text_color=f"{self.status_color[0]}",
                                     width=10, height=10,
                                     font=("Helvetica", 17))
        self.status_label.place(x=85, y=25, anchor=SE)
        self.label = CTkLabel(self.master, text=f"{self.work_time:02d}:{self.break_time:02d}", width=10, height=10,
                              font=("Helvetica", 25))
        self.label.place(x=95, y=55, anchor=SE)
        self.swap_button = CTkButton(self.master, text="⇌", width=20, height=20, command=self.swap, corner_radius=32,
                                     fg_color="#4158D0", hover_color="#C850C0", border_color="#FFCC70", border_width=2)
        self.swap_button.place(x=115, y=80, anchor=SE)
        self.button = CTkButton(self.master, text="↕", width=20, height=20, command=self.toggle_timer, corner_radius=32,
                                fg_color="#4158D0", hover_color="#C850C0", border_color="#FFCC70", border_width=2)
        self.button.place(x=40, y=80, anchor=SE)
        self.textbox = CTkTextbox(self.master, width=185, height=200, text_color="#149414", corner_radius=7,
                                  border_spacing=3)
        self.textbox.place(x=193, y=290, anchor=SE)
        self.textbox.configure(state=DISABLED)
        self.mess = CTkEntry(self.master, placeholder_text="Note here >>>", width=150, height=20, corner_radius=16)
        self.mess.place(x=158, y=325, anchor=SE)

        self.send_button = CTkButton(self.master, text="➤", width=20, height=25, command=self.send, corner_radius=16,
                                     fg_color="#4158D0", hover_color="#C850C0", border_color="#FFCC70", border_width=1)
        self.send_button.place(x=197, y=325, anchor=SE)
        self.mess.bind("<Return>", lambda event: self.send())
        self.start_button.destroy()
        threading.Thread(target=self.pomodoro_study, args=(self.numcircle, self.work_time, self.break_time,)).start()
    def on_closing(self):
        self.unlock_web()
        sys.exit()
    def send(self):
        self.var.set(1)
        text = self.mess.get().lower().strip()
        if not text:
            return
        elif text.strip().lower() == "again":
            self.again()
        msg = f">>>{text}\n-----------------------------------\n"
        self.textbox.configure(state=NORMAL)
        self.textbox.insert(END, msg)
        self.textbox.configure(state=DISABLED)
        self.textbox.see(END)
    def ask(self):
        self.master.geometry("200x335")
        self.swap_button.place(x=190, y=80, anchor=SE)
        self.label.place(x=130, y=55, anchor=SE)
        self.status_label.place(x=120, y=25, anchor=SE)
        self.flag = True
        self.textbox.configure(state=NORMAL)
        msg = "TSIN: DO YOU WANT TO CONTINUE ? ( y | n )\n"
        self.textbox.insert(END, msg)
        self.textbox.see(END)
        self.send_button.wait_variable(self.var)
        self.textbox.configure(state=DISABLED)
        text = self.mess.get().lower().strip()
        if 'y' in text:
            self.mess.delete(0, END)
            msg = "TSIN: How many rounds do you want to continue with ?\n"
            self.textbox.configure(state=NORMAL)
            self.textbox.insert(END, msg)
            self.textbox.see(END)
            self.send_button.wait_variable(self.var)
            self.textbox.configure(state=DISABLED)
            text = self.mess.get().lower().strip()
            self.mess.delete(0, END)
            self.textbox.see(END)
            try:
                text = int(text)
                return text
            except ValueError:
                return 0
        else:
            self.textbox.configure(state=NORMAL)
            self.textbox.insert(END, "Enter 'again' to play again!\n")
            self.textbox.configure(state=DISABLED)
            self.textbox.see(END)
            self.mess.delete(0, END)
            return 0

    def again(self):
        self.flag = True
        self.master.geometry("200x335")
        self.swap_button.place(x=190, y=80, anchor=SE)
        self.label.place(x=130, y=55, anchor=SE)
        self.status_label.place(x=120, y=25, anchor=SE)
        self.label.configure(text=f"{self.work_time:02d}:{self.break_time:02d}")
        self.textbox.configure(state=NORMAL)
        msg = "TSIN: Chat something to start again?('q' to quit) \n"
        self.textbox.insert(END, msg)
        self.textbox.see(END)
        self.send_button.wait_variable(self.var)
        self.textbox.configure(state=DISABLED)
        text = self.mess.get().lower().strip()
        self.textbox.see(END)
        if text.strip() and text.strip() != "q":
            self.mess.delete(0, END)
            threading.Thread(target=self.pomodoro_study,
                             args=(self.numcircle, self.work_time, self.break_time,)).start()
        elif text.strip() == 'q':
            self.label.configure(text="00:00")
            self.mess.delete(0, END)
            return
    def show_notification(self,name, icon, title, message, timeout):
        notification.notify(
            app_name=name,
            title=title,
            message=message,
            timeout=timeout,
            app_icon=icon,
        )
    def countdown(self, seconds, cur, next):
        self.play_music()
        while seconds > 0:
            mins, secs = divmod(seconds, 60)
            timeformat = '{:02d}:{:02d}'.format(mins, secs)
            #print(f"\rThời gian còn lại: {timeformat}", end="")
            if not self.secon:
                self.label.configure(text=timeformat)
            else:
                self.label.configure(text=f"{seconds}s")
            remaining_percentage = seconds / (self.work_time * 60) * 100
            #print(remaining_percentage)
            if remaining_percentage == 50:
                message = f"Bạn còn khoảng 50% thời gian {cur}."
                self.show_notification("TSIN",
                                       'DATABASE/icon1.ico',
                                       'Focus Program',
                                       f"{message}\n{random.choice(self.emo)}  {random.choice(self.icocheer)}\n CỤ THỂ LÀ CÒN:    {seconds} giây.\n{random.choice(self.emo)}  {random.choice(self.icocheer)}",
                                       5)
                #print(message)
            elif remaining_percentage == 15:
                message = f"Bạn còn khoảng 15% thời gian {cur}."
                self.show_notification("TSIN",
                                       'DATABASE/icon1.ico',
                                       'Focus Program',
                                       f"{message}\n{random.choice(self.emo)}  {random.choice(self.icocheer)}\n CỤ THỂ LÀ CÒN:    {seconds} giây.\n{random.choice(self.emo)}  {random.choice(self.icocheer)}",
                                       5)
                #print(message)
            elif seconds <= 3:
                message = (f"Thời gian {cur} đã HẾT.{random.choice(self.emo)}  {random.choice(self.icocheer)} "
                           f"\n ------------------------"
                           f"\n |        {next} Time       |"
                           f"\n ------------------------")
                self.show_notification("TSIN",
                                       'DATABASE/icon1.ico',
                                       'Focus Program',
                                       f"{message}",
                                       5)
                #print(message)
            time.sleep(1)
            seconds -= 1
    def play_music(self):
        pygame.mixer.init()
        sound = pygame.mixer.Sound("DATABASE/321.MP3")
        sound.play()
    def unlock_web(self):
        data_block_link = "C:/Windows/System32/drivers/etc/hosts"
        database_link = "DATABASE/block_data"

        with open(data_block_link, "r", encoding="utf-8") as file1:
            blocked_datas = file1.readlines()

        with open(database_link, "r", encoding="utf-8") as file:
            raw_datas = file.readlines()

        with open(data_block_link, "w", encoding="utf-8") as file:
            file.writelines(raw_datas)

        with open(database_link, "w", encoding="utf-8") as file:
            file.writelines(blocked_datas)
        return
    def pomodoro_study(self, num_pomodoros, work_time, break_time):
        for pomodoro in range(num_pomodoros):
            #print(f"\nBắt đầu Pomodoro {pomodoro + 1}: Thời gian làm việc {work_time} phút.")
            self.status_label.configure(text="Work", text_color="red")
            self.countdown(work_time * 60, "Work","Rest")
            #print("\nThời gian làm việc kết thúc. Chúc mừng bạn đã hoàn thành một Pomodoro!")
            if pomodoro < num_pomodoros - 1:
                #print(f"\nNghỉ {break_time} phút.")
                self.status_label.configure(text="Rest", text_color="blue")
                self.unlock_web()
                self.countdown(break_time * 60,"Rest", "Work")
                self.unlock_web()
                #print("\nKết thúc thời gian nghỉ. Bắt đầu Pomodoro tiếp theo.")
        self.status_label.configure(text="Continue?", text_color="yellow")
        round = self.ask()
        if round:
            #print(f"\nNghỉ {break_time} phút.")
            self.status_label.configure(text="Rest", text_color="blue")
            self.unlock_web()
            self.countdown(break_time * 60,"Rest","Work")
            self.unlock_web()
            #print("\nKết thúc thời gian nghỉ. Bắt đầu Pomodoro tiếp theo.")
            self.pomodoro_study(round, work_time, break_time)
        else:
            self.textbox.configure(state=NORMAL)
            self.textbox.insert(END, "Enter 'again' to play again!\n")
            self.textbox.configure(state=DISABLED)
            self.textbox.see(END)
            return
    def toggle_timer(self):
        self.flag = not self.flag
        if self.flag:
            self.master.geometry("200x335")
            self.swap_button.place(x=190, y=80, anchor=SE)
            self.label.place(x=130, y=55, anchor=SE)
            self.status_label.place(x=120, y=25, anchor=SE)
        else:
            self.master.geometry("123x85")
            self.swap_button.place(x=115, y=80, anchor=SE)
            self.label.place(x=95, y=55, anchor=SE)
            self.status_label.place(x=85, y=25, anchor=SE)
    def swap(self):
        self.secon = not self.secon
        return

class FocusDatabase:
    def __init__(self, db_name):
        self.db_name = db_name
        self.connection = sqlite3.connect(self.db_name)
        self.cursor = self.connection.cursor()
        self.create_table()
    def create_table(self):
        create_table_sql = '''
            CREATE TABLE IF NOT EXISTS focus_data (
                id INTEGER PRIMARY KEY,
                time INTEGER,
                rest INTEGER,
                music TEXT,
                block TEXT
            );
        '''
        self.cursor.execute(create_table_sql)
        self.connection.commit()
    def insert_data(self):
        time = int(input("Enter WORK time >>>"))
        rest = int(input("Enter REST time >>>"))
        music = input("Enter MUSIC link >>>")
        print("Enter BLOCK WEBS (enter stop)>>>")
        content_lines = []
        while True:
            line = input()
            if line.lower() == "stop":
                break
            content_lines.append(line)
        block = "\n".join(content_lines)
        insert_data_sql = '''
            INSERT INTO focus_data (time, rest, music, block)
            VALUES (?, ?, ?, ?);
        '''
        data = (time, rest, music, block)
        self.cursor.execute(insert_data_sql, data)
        self.connection.commit()
    def insert_data_new(self, time, rest, music, block):
        try:
            if time.strip() == "q":
                return
            if rest.strip() == 'q':
                return
            if music.strip() == 'q':
                return
            elif music.strip() == 'none':
                music = ""
            if block.strip() == 'q':
                return
            elif block.strip() == 'none':
                block = ""
            insert_data_sql = '''
                        INSERT INTO focus_data (time, rest, music, block)
                        VALUES (?, ?, ?, ?);
                    '''
            data = (time, rest, music, block)
            self.cursor.execute(insert_data_sql, data)
            self.connection.commit()
            print("INSERT DATA SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except:
            print("INSERT DATA UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def edit_data(self):
        edit_id = int(input("Enter ID to edit >>> "))
        select_one_sql = 'SELECT * FROM focus_data WHERE id = ?;'
        self.cursor.execute(select_one_sql, (edit_id,))
        record = self.cursor.fetchone()
        if record:
            print(f"Current record with ID {edit_id}: {record}")
            cid, ctime, crest, cmusic, cblock = record
            # Chỉnh sửa thông tin dựa trên ID
            time = input("Enter WORK time >>>")
            rest = input("Enter REST time >>>")
            music = input("Enter MUSIC link >>>")
            print("Enter BLOCK WEBS (enter stop)>>>")
            content_lines = []
            while True:
                line = input()
                if line.lower() == "stop":
                    break
                content_lines.append(line)
            block = "\n".join(content_lines)
            if time.strip() == "":
                time = ctime
            if rest.strip() == "":
                rest = crest
            if music.strip() == "":
                music = cmusic
            if block.strip() == "":
                block = cblock
            # Cập nhật thông tin vào cơ sở dữ liệu
            update_data_sql = '''
                UPDATE focus_data
                SET time = ?, rest = ?, music = ?, block = ?
                WHERE id = ?;
            '''
            data = (time, rest, music, block, edit_id)
            self.cursor.execute(update_data_sql, data)
            self.connection.commit()
            print(f"Record with ID {edit_id} has been updated.")
        else:
            print(f"No record found with ID {edit_id}.")
    def edit_data_new(self,edit_id,time,rest,music,block):
        try:
            select_one_sql = 'SELECT * FROM focus_data WHERE id = ?;'
            self.cursor.execute(select_one_sql, (edit_id,))
            record = self.cursor.fetchone()
            if record:
                cid, ctime, crest, cmusic, cblock = record
                if time.strip() == "none":
                    time = ctime
                elif time.strip() == 'q':
                    return
                if rest.strip() == "none":
                    rest = crest
                elif rest.strip() == 'q':
                    return
                if music.strip() == "none":
                    music = cmusic
                elif music.strip() == 'q':
                    return
                if block.strip() == "none":
                    block = cblock
                elif block.strip() == 'q':
                    return
                update_data_sql = '''
                            UPDATE focus_data
                            SET time = ?, rest = ?, music = ?, block = ?
                            WHERE id = ?;
                        '''
                data = (time, rest, music, block, edit_id)
                self.cursor.execute(update_data_sql, data)
                self.connection.commit()
                print("EDIT DATA SUCCESSFULLY ! 👍 👌 🎊 ✅")
            else:
                print(f"No record found with ID {edit_id}.")
        except:
            print("EDIT DATA UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def print_table(self):
        all_data = self.fetch_all_data()
        if all_data:
            headers = ["ID", "Time", "Rest", "Music", "Block"]
            table = [(record[0], record[1], record[2], record[3], record[4]) for record in all_data]
            print(tabulate(table, headers, tablefmt="fancy_grid"))
        else:
            print("No data in the database.")
    def fetch_all_data(self):
        select_all_sql = 'SELECT * FROM focus_data;'
        self.cursor.execute(select_all_sql)
        return self.cursor.fetchall()
    def delete_data(self):
        try:
            delete_id = int(input("Enter ID to delete >>> "))
            delete_data_sql = 'DELETE FROM focus_data WHERE id = ?;'
            self.cursor.execute(delete_data_sql, (delete_id,))
            self.connection.commit()
            print(f"Record with ID {delete_id} has been deleted.")
        except:
            print("No record found with ID .")
    def delete_data_new(self, delete_id):
        try:
            if delete_id.strip() == 'q':
                return
            delete_data_sql = 'DELETE FROM focus_data WHERE id = ?;'
            self.cursor.execute(delete_data_sql, (delete_id,))
            self.connection.commit()
            print("DELETE DATA SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except:
            print("DELETE DATA UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def close_connection(self):
        self.connection.close()

    def game(self, round, ctime, crest):
        root = CTk()
        app = FocusProgram(root, round, ctime, crest)
        root.mainloop()
        return
    def start_game_in_thread(self,round,ctime,crest,cmusic,cblock):
        try:
            if cmusic.strip():
                self.open_path(cmusic)
            if cblock.strip():
                self.block_web(cblock)
            game_thread = threading.Thread(target=self.game,
                                           args=(round, ctime, crest))
            game_thread.start()
        except:
            pass
    def start_game(self, focus_id, round):
        try:
            select_one_sql = 'SELECT * FROM focus_data WHERE id = ?;'
            self.cursor.execute(select_one_sql, (focus_id,))
            record = self.cursor.fetchone()
            if record:
                cid, ctime, crest, cmusic, cblock = record
                return cid, ctime, crest, cmusic, cblock
        except:
            print("No record found with ID .")

    def unlock_web(self):
        data_block_link = "C:/Windows/System32/drivers/etc/hosts"
        database_link = "DATABASE/block_data"

        with open(data_block_link, "r", encoding="utf-8") as file1:
            blocked_datas = file1.readlines()

        with open(database_link, "r", encoding="utf-8") as file:
            datas = file.readlines()

        with open(data_block_link, "w", encoding="utf-8") as file:
            file.writelines(datas)

        with open(database_link, "w", encoding="utf-8") as file:
            file.writelines(blocked_datas)
        return
    def block_web(self,block_web):
        data_block_link = "C:/Windows/System32/drivers/etc/hosts"
        database_link = "DATABASE/block_data"

        with open(data_block_link, "r", encoding="utf-8") as file:
            datas = file.readlines()
        raw_data = [data for data in datas if data.strip()]

        with open(database_link, "w", encoding="utf-8") as file:
            file.writelines(raw_data)
        with open("temp", "w", encoding="utf-8") as file:
            file.writelines(raw_data)

        block_list = block_web.split("\n")
        block_list = [data for data in block_list if data.strip()]
        for i in range(len(block_list)):
            block_list[i] = "127.0.0.1 " + block_list[i] + '\n'

        blocked_data = raw_data+block_list
        blocked_data = [data for data in blocked_data if data.strip()]

        with open(data_block_link, "w", encoding="utf-8") as file:
            file.writelines(blocked_data)
        return
    def open_path(self, path):
        try:
            if os.path.exists(path):
                os.startfile(path)
            else:
                webbrowser.open(path)
            return
        except Exception as e:
            print(f"Error opening path: {e}")


if __name__ == "__main__":
    db = FocusDatabase('focus_data.db')
    while True:
        db.print_table()
        print("1. Add Task")
        print("2. Start")
        print("3. Edit Task")
        print("4. Delete Task")
        print("5. Quit")
        choice = input("Enter your choice >>> ")
        if choice == '1':
            db.insert_data()
        elif choice == '2':
            db.print_table()
            db.start_game()
        elif choice == '3':
            db.edit_data()
        elif choice == '4':
            db.delete_data()
        elif choice == '5':
            break
        else:
            print("Invalid choice. Please try again.")
    db.close_connection()
