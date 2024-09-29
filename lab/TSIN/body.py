import threading
import time
import keyboard
import subprocess
import os
import sqlite3
from datetime import datetime, timedelta
from plyer import notification
from update import Update, ulink
from DATABASE.memory import brain_py_path, brain_exe_path, tolink, applink, notilink, mes, open_brain_key, st, en
notilink = 'notificate.db'
brain_py_path = "brain.py"
brain_exe_path = "brain.exe"
tolink = 'DATABASE/todolist.db'
applink = 'DATABASE/appointments.db'
class Body(threading.Thread):

    def __init__(self, interval=1):
        threading.Thread.__init__(self)
        self.daemon = False
        self.interval = interval
        self.task_list = []

    def openbot(self):
        if os.path.isfile(brain_exe_path):
            try:
                os.startfile(brain_exe_path)
            except Exception as e:
                print(f"OPEN BOT FILE:\n     Error: {e}")
        elif os.path.isfile(brain_py_path):
            try:
                subprocess.run(["python", brain_py_path])
            except Exception as e:
                print(f"OPEN BOT PYTHON FILE:\n   Error: {e}")
        else:
            print(f"Neither {brain_py_path} nor {brain_exe_path} found.")

    def update_todo(self):
        try:
            with sqlite3.connect(tolink) as conne:
                cursors = conne.cursor()
                query = "DELETE FROM tasks WHERE is_completed = '✓' AND habit != '✓'"
                cursors.execute(query)
                conne.commit()
                current_time = datetime.now().strftime("%I:%M %p")
                query = 'SELECT * FROM tasks WHERE is_completed != ? AND time >= ? ORDER BY time'
                cursors.execute(query, ("✓", current_time))
                self.task_list = cursors.fetchall()
                #print(self.task_list)
        except sqlite3.Error as e:
            print(f"UPDATE TODO NOTIFICATION:\n  SQLite error: {e}")
        finally:
            if conne:
                conne.close()

    def update_notification(self): #thêm các appointment vào notification database
        try:
            current_time = datetime.now()
            with sqlite3.connect(applink) as conn_appointments:
                cursor_appointments = conn_appointments.cursor()
                cursor_appointments.execute("SELECT category, name, strftime('%d/%m/%Y', date_time) FROM appointments")
                appointments = cursor_appointments.fetchall()
                with sqlite3.connect(notilink) as conn_notification:
                    cursor_notification = conn_notification.cursor()
                    for appointment in appointments:
                        category, name, formatted_date_time = appointment
                        formatted_date_time = datetime.strptime(formatted_date_time, '%d/%m/%Y')
                        #print(name)
                        #print(formatted_date_time)
                        #print(category)
                        if category == '✓':
                            if formatted_date_time.strftime("%d/%m") == current_time.strftime("%d/%m"):
                                #print("ok")
                                cursor_notification.execute(
                                    "INSERT INTO notificate (name, content, type) VALUES (?, ?, ?)",
                                    (name, "Xin chào SAN! Chúc anh một ngày tốt đẹp \n\n Hôm nay là ngày =>", "appointment"))
                                cursor_notification.execute(
                                    "INSERT INTO notificate (name, content, type) VALUES (?, ?, ?)",
                                    (name, "Xin chào SAN! Chúc anh một ngày tốt đẹp \n\n Hôm nay là ngày =>",
                                     "appointment"))
                                cursor_notification.execute(
                                    "INSERT INTO notificate (name, content, type) VALUES (?, ?, ?)",
                                    (name, "Xin chào SAN! Chúc anh một ngày tốt đẹp \n\n Hôm nay là ngày =>",
                                     "appointment"))
                                conn_notification.commit()
                        else:
                            if formatted_date_time.strftime("%d/%m/%Y") == current_time.strftime("%d/%m/%Y"):
                                #print("2")
                                cursor_notification.execute(
                                    "INSERT INTO notificate (name, content, type) VALUES (?, ?, ?)",
                                    (name, "Xin chào SAN! Chúc anh một ngày tốt đẹp \n\n Hôm nay là ngày =>", "appointment"))
                                cursor_notification.execute(
                                    "INSERT INTO notificate (name, content, type) VALUES (?, ?, ?)",
                                    (name, "Xin chào SAN! Chúc anh một ngày tốt đẹp \n\n Hôm nay là ngày =>",
                                     "appointment"))
                                cursor_notification.execute(
                                    "INSERT INTO notificate (name, content, type) VALUES (?, ?, ?)",
                                    (name, "Xin chào SAN! Chúc anh một ngày tốt đẹp \n\n Hôm nay là ngày =>",
                                     "appointment"))
                                conn_notification.commit()
        except sqlite3.Error as e:
            print(f"UPDATE NOTIFICATION APPOINTMENT:\n  SQLite error: {e}")

    def show_notification(self, name, icon, title, message, timeout):
        try:
            notification.notify(
                app_name=name,
                title=title,
                message=message,
                timeout=timeout,
                app_icon=icon,
                # cursor_notification.execute(
                #    "INSERT INTO notificate (name, content, type) VALUES (?, ?, ?)",
                #    (name, "", "appointment"))
                # conn_notification.commit()
            )
        except Exception as e:
            print(f"Show notification:  ERROR: {e}")

    def display_notifications(self):
        try:
            with sqlite3.connect(notilink) as conn_notification:
                cursor_notification = conn_notification.cursor()
                cursor_notification.execute("SELECT * FROM notificate")
                notifications = cursor_notification.fetchall()
                if notifications:
                    for notification_data in notifications:
                        name, message, category = notification_data
                        self.show_notification(category, None, f"{name}    -    {category}",
                                                message +"      |   " + name + "  |", 7)
                    cursor_notification.execute("DELETE FROM notificate")
                    conn_notification.commit()
                else:
                    return
        except sqlite3.Error as e:
            print(f"Display notification:   SQLite error: {e}")

    def update_start(self):
        try:
            up = Update(ulink)
            functions_data = up.get_all_functions()
            for function in functions_data:
                name, link, function_type = function[1], function[2], function[3]
                if function_type == "✓":
                    self.open_link(link)
            up.close_database()
        except Exception as e:
            print(f"UPDATE: upload start file error {e}")

    def open_link(self, path):
        try:
            os.startfile(path)
        except Exception as e:
            print(f"UPDATE: Error opening file or link: {e}")

    def addnoti(self,name, message, type):
        try:
            with sqlite3.connect(notilink) as conn_notification:
                cursor_notification = conn_notification.cursor()
                cursor_notification.execute(
                    "INSERT INTO notificate (name, content, type) VALUES (?, ?, ?)",
                    (name, message, type)
                )
                conn_notification.commit()
        except sqlite3.Error as e:
            print(f"ADD NOTIFICATION:   SQLite error: {e}")

    def run(self):
        is_update_done = False
        self.update_notification() #Appointment
        self.update_start() #mở các auto link UPDATE
        self.update_todo()  #delete các todolist đã qua
        while True:
            #print("Body is doing some work...")
            if keyboard.is_pressed(open_brain_key):
                background_thread = threading.Thread(target=self.openbot)
                background_thread.daemon = False
                background_thread.start()
            current_time = datetime.now()
            # Check if the current time matches any time in self.task_list
            matching_tasks = [task for task in self.task_list if task[5] == current_time.strftime("%I:%M %p")]
            for task in matching_tasks:
                task_name = task[2]
                #print(f"Sắp đến giờ rồi! Task: {task_name}")
                self.task_list.remove(task)
                for i in range(3):
                    self.addnoti(task_name,f"Xin chào SAN! Chúc anh một ngày tốt đẹp \n\n Sắp đến giờ! Chuần bị   =>   ", "to-do-tasks")
            if current_time.time().minute == 1 and not is_update_done:
                self.update_todo() #delete các todolist đã qua
                is_update_done = True
            if current_time.time().minute == 2 and is_update_done:
                is_update_done = False
            self.display_notifications()
            time.sleep(self.interval)

if __name__ == "__main__":
    body_thread = Body()
    body_thread.start()
    #print(body_thread.update_notification())
