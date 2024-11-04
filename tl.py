import random
import tkinter as tk
import sqlite3
from datetime import datetime, timedelta
from plyer import notification
from tkinter import ttk, messagebox

class TodoListApp:
    def __init__(self, root):
        try:
            self.root = root
            self.topic = []
            # Thiết lập các thuộc tính của cửa sổ
            self.root.title("TASKS LIST SYSTEM")
            self.root.attributes('-topmost', True)
            self.root.configure(bg="#222121")
            self.root.geometry("430x610")
            # Sự kiện FocusIn và FocusOut
            self.root.bind('<FocusIn>', self.on_focus_in)
            self.root.bind('<FocusOut>', self.on_focus_out)
            # Kết nối với cơ sở dữ liệu SQLite
            self.conn = sqlite3.connect('todolist.db')
            self.cursor = self.conn.cursor()
            self.create_table()
            # Ô nhập liệu để thêm task
            self.entry_frame = tk.Frame(self.root, bg="#222121")
            self.entry_frame.pack(fill=tk.X, padx=10, pady=5)
            # Entry đầu tiên ở bên trái
            self.entry = tk.Entry(self.entry_frame, width=16, font=("Helvetica", 16, 'bold'), bg="#444444",
                                  fg="#ffffff",
                                  insertbackground="#ffffff")
            self.entry.pack(side=tk.LEFT, padx=5, pady=5, fill=tk.X, expand=True)
            # Entry thứ hai ở bên phải
            self.combobox = ttk.Combobox(self.entry_frame, width=10, font=("Helvetica", 16, 'bold'), state="readonly")
            self.combobox.pack(side=tk.RIGHT, padx=5, pady=5, fill=tk.X, expand=True)
            self.combobox.set("none")
            # Gán sự kiện nhấn Enter cho ô nhập liệu và Combobox
            self.entry.bind('<Return>', self.add_task_event)
            # Frame để chứa các nút ở trên Listbox
            self.buttons_frame = tk.Frame(self.root, bg="#222121")
            self.buttons_frame.pack(fill=tk.X, padx=10, pady=5)
            # Nút Add Task
            self.add_button = tk.Button(self.buttons_frame, text="Add", command=self.add_task, width=9, bg="#333333",
                                        fg="#ffffff")
            self.add_button.pack(side=tk.LEFT, padx=5)

            self.open_button = tk.Button(self.buttons_frame, text="Note", command=self.open_note, width=9, bg="#333333",
                                         fg="#ffffff")
            self.open_button.pack(side=tk.LEFT, padx=5)

            self.delete_button = tk.Button(self.buttons_frame, text="Delete", command=self.delete_task, width=9,
                                           bg="#333333", fg="#ffffff")
            self.delete_button.pack(side=tk.RIGHT, padx=5)
            self.edit_button = tk.Button(self.buttons_frame, text="Edit", command=self.edit, width=9, bg="#333333",
                                         fg="#ffffff")
            self.edit_button.pack(side=tk.RIGHT, padx=5)
            self.main_button = tk.Button(self.buttons_frame, text="Main", command=self.choose_main, width=9,
                                         bg="#333333", fg="#ffffff")
            self.main_button.pack(side=tk.RIGHT, padx=5)
            style = ttk.Style()
            style.theme_use("clam")
            style.configure("Treeview",
                            background="#444444",
                            foreground="#ffffff",
                            fieldbackground="#444444",
                            bordercolor="#222121", )
            style.configure("Treeview.Heading",
                            background="#333333",
                            foreground="#ffffff",
                            relief="flat")
            style.map('mystyle.Treeview',
                      background=[('selected', '#222121')],
                      foreground=[('selected', '#ffffff')])
            # Frame chứa Treeview
            self.tree_frame = tk.Frame(self.root, bg="#222121")
            self.tree_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

            # Tạo Treeview với style tùy chỉnh
            self.tree = ttk.Treeview(self.tree_frame, columns=("Task", "Reward"), show="headings", height=8,
                                     style="mystyle.Treeview")

            # Đặt các tiêu đề cho cột
            self.tree.heading("Task", text="Task Name")
            self.tree.heading("Reward", text="Reward")

            # Đặt độ rộng cho các cột
            self.tree.column("Task", width=160, anchor='center')
            self.tree.column("Reward", width=70, anchor='center')

            # Scrollbar cho Treeview
            self.scrollbar = ttk.Scrollbar(self.tree_frame, orient=tk.VERTICAL, command=self.tree.yview)
            self.tree.configure(yscrollcommand=self.scrollbar.set)
            self.scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

            # Hiển thị Treeview
            self.tree.pack(fill=tk.BOTH, expand=True)

            self.dragged_item_index = None

            # Load tasks from database
            self.load_tasks()
            self.progress_frame = tk.Frame(self.root, bg="#222121")
            self.progress_frame.pack(fill=tk.X, padx=10, pady=5)

            # Thêm pro_label vào progress_frame
            self.pro_label = tk.Label(self.progress_frame, text=f"Lv :", font=("Helvetica", 12),
                                      bg="#222121", fg="#ffffff")
            self.pro_label.pack(side=tk.LEFT, padx=5)

            # Thêm progress vào progress_frame, ngang hàng với pro_label
            self.progress = ttk.Progressbar(self.progress_frame, length=250, mode="determinate")
            self.progress.pack(side=tk.LEFT, padx=5)
            self.get_cur_level()

            self.Done_button = tk.Button(self.progress_frame, text="Done", command=self.done, width=5, bg="#333333",
                                         fg="#ffffff")
            self.Done_button.pack(side=tk.LEFT, padx=5)

            self.set_button = tk.Button(self.progress_frame, text="Set", command=self.set, width=5, bg="#333333",
                                        fg="#ffffff")
            self.set_button.pack(side=tk.LEFT, padx=5)
            # Frame chứa Label "Min:", Entry, nút OK, và label đếm ngược thời gian
            self.timer_frame = tk.Frame(self.root, bg="#222121")
            self.timer_frame.pack(fill=tk.X, padx=10, pady=10)
            self.min_label = tk.Label(self.timer_frame, text="Min:", font=("Helvetica", 12), bg="#222121", fg="#ffffff")
            self.min_label.pack(side=tk.LEFT, padx=5)

            self.minutes_entry = tk.Entry(self.timer_frame, width=5, font=("Helvetica", 12), bg="#444444", fg="#ffffff")
            self.minutes_entry.pack(side=tk.LEFT, padx=5)

            self.ok_button = tk.Button(self.timer_frame, text="Ok", command=self.start_timer, width=5, bg="#333333",
                                       fg="#ffffff")
            self.ok_button.pack(side=tk.LEFT, padx=5)

            # Label đếm ngược thời gian đặt ngang hàng

            self.hour_entry = tk.Entry(self.timer_frame, width=5, font=("Helvetica", 12), bg="#444444", fg="#ffffff")
            self.hour_entry.pack(side=tk.LEFT, padx=5)

            self.min_entry = tk.Entry(self.timer_frame, width=5, font=("Helvetica", 12), bg="#444444", fg="#ffffff")
            self.min_entry.pack(side=tk.LEFT, padx=5)

            self.countdown_label = tk.Label(self.timer_frame, font=("Helvetica", 16, 'bold'), bg="#222121",
                                            fg="#ffffff")
            self.countdown_label.pack(side=tk.LEFT, padx=10)

            # Biến để lưu trữ ID của hàm after
            self.after_id = None

            # Label hiển thị thời gian kết thúc đếm ngược
            self.end_time_label = tk.Label(self.root, font=("Helvetica", 14), bg="#222121", fg="#ffffff")
            self.end_time_label.pack(padx=10, pady=10)
            self.open_task()
            self.print_todo()
            return
        except:
            messagebox.showerror("Error", f" GUI INIT !!!")
            return

    def load_tasks(self):
        try:
            # Xóa tất cả các dòng hiện có trong Treeview
            for item in self.tree.get_children():
                self.tree.delete(item)
            self.topic = []
            # Load tasks từ cơ sở dữ liệu và hiển thị trong Listbox
            self.cursor.execute('SELECT main, task, reward, topic FROM tasks WHERE task!=? ORDER  BY topic',
                                ('original task name',))
            tasks = self.cursor.fetchall()
            print(tasks)
            cur_topic = 'nonádasdasde'
            # Đăng ký thẻ với màu nền vàng
            self.tree.tag_configure('black', background='black')
            for main, task, reward, topic in tasks:
                if topic != cur_topic:
                    self.topic.append(topic)
                    self.tree.insert("", "end", values=("----------------TOPIC----------------", topic),
                                     tags=('black',))
                    cur_topic = topic
                if not main:
                    self.tree.insert("", "end", values=(f"{task}", reward))
                else:
                    self.tree.insert("", "end", values=(f"[X]{task}", reward))
            self.combobox['values'] = self.topic
            return
        except:
            messagebox.showerror("Error", f"LOAD TASK !!!")
            return
    def start_timer(self):
        try:
            minutes = self.minutes_entry.get()
            hours = self.hour_entry.get()
            mins = self.min_entry.get()
            if minutes.isdigit() and int(minutes) > 0:
                total_seconds = int(minutes) * 60
            elif hours.isdigit() and mins.isdigit() and int(hours) >= 0 and int(mins) >= 0:
                now = datetime.now()
                target_time = now.replace(hour=int(hours), minute=int(mins), second=0, microsecond=0)
                if target_time < now:
                    target_time += timedelta(days=1)
                total_seconds = int((target_time - now).total_seconds())
            else:
                messagebox.showwarning("Warning", "Vui lòng nhập thời gian hợp lệ!")
                return
            if self.after_id is not None:
                self.root.after_cancel(self.after_id)
            end_time = datetime.now() + timedelta(seconds=total_seconds)
            end_time_str = end_time.strftime('%I:%M %p')
            self.end_time_label.config(text=f"End Time: {end_time_str}")
            total_minutes, seconds = divmod(total_seconds, 60)
            popup = tk.Toplevel(self.root)
            PopUpTimer(popup, total_minutes,  seconds)
            self.countdown(total_seconds)
        except Exception:
            messagebox.showerror("Error", f"Counter TIMER decrease ")
            return
    def get_cur_level(self):
        try:
            conn = sqlite3.connect('setting.db')
            cursor = conn.cursor()

            # Fetch current times and history
            cursor.execute('SELECT times, history FROM setting')
            result = cursor.fetchone()

            if result:
                current_times, current_history = result
                print("Current times:", current_times)
                print("Current history:", current_history)
                new_history = current_history
                # Update times (increment by 1) and history (with new_history)
                updated_times = current_times
                self.cur_lev = updated_times // 3
                self.pro_label['text'] = f"Lv {self.cur_lev}:"
                self.update_progress(updated_times % 3, 3 + self.cur_lev)
            conn.close()
            return
        except:
            messagebox.showerror("Error", f" get_cur_level !!!")
            return
    def get_history(self):
        try:
            conn = sqlite3.connect('setting.db')
            cursor = conn.cursor()

            # Fetch current times and history
            cursor.execute('SELECT times, history FROM setting')
            result = cursor.fetchone()
            conn.close()
            if result:
                current_times, current_history = result
                return current_history
        except:
            messagebox.showerror("Error", f" get_history !!!")
            return
    def update_progress(self, current_value, target_value):
        try:
            """Cập nhật giá trị cho ProgressBar dựa trên giá trị hiện tại và mục tiêu"""
            percentage = (current_value / target_value) * 100  # Tính phần trăm tiến trình
            self.progress['value'] = percentage  # Cập nhật giá trị thanh tiến trình
            self.root.update_idletasks()  # Cập nhật giao diện ngay lập tức
        except:
            messagebox.showerror("Error", f" update_progress !!!")
            return

    def set(self):
        try:
            quick_edit_window = tk.Toplevel(self.root)
            quick_edit_window.title("EDIT")
            quick_edit_window.geometry("300x390")
            quick_edit_window.configure(bg="#222121")
            quick_edit_window.attributes('-topmost', True)
            group_label = tk.Label(quick_edit_window, text="Add Group:", fg="#ffffff", bg="#222121")
            group_label.pack(padx=10, pady=5)
            group_entry = tk.Entry(quick_edit_window)
            group_entry.pack(padx=10, pady=5)
            old_word_label = tk.Label(quick_edit_window, text="Current Reward:", fg="#ffffff", bg="#222121")
            old_word_label.pack(padx=10, pady=5)
            old_word_entry = tk.Entry(quick_edit_window)
            old_word_entry.pack(padx=10, pady=5)
            old_word_entry.insert(0, self.get_reward())
            text_area = tk.Text(quick_edit_window, height=9, width=43, font=("Helvetica", 14), fg="#ffffff",
                                bg="#222121", insertbackground="white")
            text_area.pack(padx=10, pady=5)
            def comfirm_word_mean():
                if group_entry.get().strip():
                    self.topic.append(group_entry.get())
                    self.combobox['values'] = self.topic
                self.minutes_entry.delete(0, tk.END)
                new_reward = old_word_entry.get().rstrip(',')
                self.cursor.execute('UPDATE tasks SET reward = ? WHERE task = ?', (new_reward,'original task name',))
                self.conn.commit()
                content = text_area.get("1.0", tk.END).strip()
                conn = sqlite3.connect('setting.db')
                cursor = conn.cursor()
                cursor.execute('UPDATE setting SET history = ?',
                               (content,))
                conn.commit()
                conn.close()
                quick_edit_window.destroy()
                return
            text_area.insert(tk.END, self.get_history())
            ok_button = tk.Button(quick_edit_window, text="OK", command=comfirm_word_mean, font=("Helvetica", 14))
            ok_button.pack(padx=10, pady=5)
            self.clear_selection()
            return
        except:
            messagebox.showerror("Error", f" set !!!")
            return
    def done(self):
        try:
            selected_item = self.tree.selection()
            if selected_item:
                task_name = self.tree.item(selected_item, 'values')[0]
                if task_name.startswith("[X]"):
                    task_name = task_name[3:]
                elif task_name=="----------------TOPIC----------------":
                    return
                print(task_name)
                reward = self.tree.item(selected_item, 'values')[1]
                self.cursor.execute('DELETE FROM tasks WHERE task = ?', (task_name,))
                self.conn.commit()
                self.load_tasks()
                # thêm vào history times+1 update progress bar
                conn = sqlite3.connect('setting.db')
                cursor = conn.cursor()

                # Fetch current times and history
                cursor.execute('SELECT times, history FROM setting')
                result = cursor.fetchone()

                if result:
                    current_times, current_history = result
                    print("Current times:", current_times)
                    print("Current history:", current_history)
                    new_history = current_history + '\n' + f"{task_name} - {reward}"
                    # Update times (increment by 1) and history (with new_history)
                    updated_times = current_times + 1
                    cursor.execute('''
                                        UPDATE setting
                                        SET times = ?, history = ?
                                    ''', (updated_times, new_history,))

                    # Commit changes
                    conn.commit()
                    print("Update successful. New times:", updated_times, new_history)
                    self.pro_label['text'] = f"Lv {updated_times // 3}:"
                    self.update_progress(updated_times % 3, 3)
                else:
                    print("No data found in the setting table.")
                conn.close()
            return
        except:
            messagebox.showerror("Error", f" done !!!")
            return
    def get_reward(self):
        try:
            self.cursor.execute('SELECT reward FROM tasks WHERE task = ?', ('original task name',))
            reward = self.cursor.fetchall()[0][0]
            if reward:
                return reward
            else:
                return ''
        except:
            messagebox.showerror("Error", f" get_reward !!!")
            return
    def open_note(self):
        try:
            selected_item = self.tree.selection()
            if selected_item:
                task_name = self.tree.item(selected_item, 'values')[0]
                if task_name.startswith("[X]"):
                    task_name = task_name[3:]
                elif task_name == "----------------TOPIC----------------":
                    return
                self.cursor.execute('SELECT note FROM tasks WHERE task = ?', (task_name,))
                notes = self.cursor.fetchall()[0]
                print(notes)
                quick_note_window = tk.Toplevel(self.root)
                quick_note_window.title("Note")
                quick_note_window.geometry("400x250")
                quick_note_window.configure(bg="#222121")  # , fg="#ffffff", bg="#222121"
                quick_note_window.attributes('-topmost', True)
                text_area = tk.Text(quick_note_window, height=8, width=43, font=("Helvetica", 14), fg="#ffffff",
                                    bg="#222121", insertbackground="white")
                text_area.pack(padx=10, pady=5)

                def save():
                    content = text_area.get("1.0", tk.END).strip()
                    print(content)
                    self.cursor.execute('UPDATE tasks SET note = ? WHERE task = ?', (content, task_name,))
                    self.conn.commit()
                    quick_note_window.destroy()
                    return

                text_area.insert(tk.END, notes)
                ok_button = tk.Button(quick_note_window, text="Save", command=save, font=("Helvetica", 10))
                ok_button.pack(padx=10, pady=5)
            else:
                self.cursor.execute('SELECT note FROM tasks WHERE task = ?', ('original task name',))
                notes = self.cursor.fetchall()[0]
                print(notes)
                quick_note_window = tk.Toplevel(self.root)
                quick_note_window.title("Note")
                quick_note_window.geometry("400x250")
                quick_note_window.configure(bg="#222121")  # , fg="#ffffff", bg="#222121"
                quick_note_window.attributes('-topmost', True)
                text_area = tk.Text(quick_note_window, height=8, width=43, font=("Helvetica", 14), fg="#ffffff",
                                    bg="#222121", insertbackground="white")
                text_area.pack(padx=10, pady=5)


                def save():
                    content = text_area.get("1.0", tk.END).strip()

                    self.cursor.execute('UPDATE tasks SET note = ? WHERE task = ?',
                                        (content, 'original task name',))
                    self.conn.commit()
                    quick_note_window.destroy()
                    return

                text_area.insert(tk.END, notes)
                ok_button = tk.Button(quick_note_window, text="Save", command=save, font=("Helvetica", 10))
                ok_button.pack(padx=10, pady=5)
            self.clear_selection()
            return
        except:
            messagebox.showerror("Error", f" NOTE !!!")
            return
    def clear_selection(self):
        # Bỏ chọn tất cả các mục trong Treeview
        self.tree.selection_remove(self.tree.selection())

    def edit(self):
        try:
            selected_item = self.tree.selection()
            if selected_item:
                task_name = self.tree.item(selected_item, 'values')[0]
                if task_name.startswith("[X]"):
                    task_name = task_name[3:]
                elif task_name == "----------------TOPIC----------------":
                    return
                print(task_name)
                reward = self.tree.item(selected_item, 'values')[1]
                quick_edit_window = tk.Toplevel(self.root)
                quick_edit_window.title("EDIT")
                quick_edit_window.geometry("300x150")
                quick_edit_window.configure(bg="#222121")
                quick_edit_window.attributes('-topmost', True)
                old_word_label = tk.Label(quick_edit_window, text="Old task:", fg="#ffffff", bg="#222121")
                old_word_label.pack(padx=10, pady=5)
                old_word_entry = tk.Entry(quick_edit_window)
                old_word_entry.pack(padx=10, pady=5)
                old_mean_label = tk.Label(quick_edit_window, text="Old reward:", fg="#ffffff", bg="#222121")
                old_mean_label.pack(padx=10, pady=5)
                old_mean_entry = tk.Entry(quick_edit_window)
                old_mean_entry.pack(padx=10, pady=5)
                old_word_entry.insert(0, task_name)
                old_mean_entry.insert(0, reward)


                def comfirm_word_mean():
                    new_word = old_word_entry.get()
                    new_mean = old_mean_entry.get()
                    self.cursor.execute('UPDATE tasks SET task = ?, reward = ? WHERE task = ?',
                                        (new_word, new_mean, task_name))
                    self.conn.commit()
                    self.load_tasks()
                    quick_edit_window.destroy()

                ok_button = tk.Button(quick_edit_window, text="OK", command=comfirm_word_mean, font=("Helvetica", 14))
                ok_button.pack(padx=10, pady=5)
            self.clear_selection()
            return
        except:
            messagebox.showerror("Error", f" EDIT !!!")
            return
    def print_todo(self):
        try:
            self.cursor.execute('SELECT task, reward FROM tasks WHERE main = 1')
            task = self.cursor.fetchall()
            if task:
                main_task = task[0][0]
                reward = task[0][1]
                notification.notify(
                    title=f"{main_task} - {reward}",
                    message=self.get_random_motivational_quote(),
                    timeout=3,
                )
                # Lặp lại hàm này sau 7 phút (7*60*1000 milliseconds = 420000 ms)
            self.root.after(420000, self.print_todo)
        except:
            messagebox.showerror("Error", f" NOTIFY Main task !!!")
            return
    def get_random_motivational_quote(self):
        try:
            connn = sqlite3.connect('Database/sentences.db')
            cursorn = connn.cursor()
            cursorn.execute('SELECT sentence FROM sentences')
            quotes = cursorn.fetchall()

            if quotes:
                # Chọn ngẫu nhiên một câu nói từ database
                random_quote = random.choice(quotes)
                return random_quote[0]  # Trả về chỉ câu nói (sentence)
            else:
                return " 😭🦾😫😥😢😨😢😫🦾"
        except:
            messagebox.showerror("Error", f" get sentences !!!")
            return
    def create_table(self):
        # Tạo bảng task nếu nó chưa tồn tại
        self.cursor.execute('''
                                CREATE TABLE IF NOT EXISTS tasks (
                                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                                    task TEXT NOT NULL,
                                    main INTEGER DEFAULT 0,
                                    note TEXT DEFAULT '',
                                    reward TEXT DEFAULT '',
                                    topic TEXT DEFAULT 'none'
                                )
                            ''')
        self.cursor.execute('SELECT COUNT(*) FROM tasks')
        task_count = self.cursor.fetchone()[0]

        if task_count == 0:
            # Thêm task với giá trị mặc định
            self.cursor.execute('''
                            INSERT INTO tasks (task, main, note, reward)
                            VALUES (?, ?, ?, ?)
                        ''', ('original task name', 0, '', ''))
        self.conn.commit()
        try:
            return
        except:
            messagebox.showerror("Error", f" create table db !!!")
            return
    def add_task(self):
        try:
            task = self.entry.get()
            topic = self.combobox.get()
            print(task, topic)
            if task:
                reward = random.choice(self.get_reward().split(','))
                print("task:", task, "reward:", reward, "topic:", topic)
                self.cursor.execute('INSERT INTO tasks (task, reward, topic) VALUES (?, ?, ?)', (task, reward, topic))
                self.conn.commit()
                self.tree.insert("", "end", values=(task, reward))
                self.entry.delete(0, tk.END)
                self.combobox.set("none")
                self.load_tasks()
            self.clear_selection()
            return
        except:
            messagebox.showerror("Error", f"ADD TASK !!!")
            return
    def add_task_event(self, event):
        self.add_task()
    def open_task(self):
        try:
            cup = tk.Toplevel(self.root)
            CountTimer(cup)
        except:
            messagebox.showerror("Error", f"OPEN init timer !!!")
            return
    def choose_main(self):
        try:
            selected_item = self.tree.selection()
            if selected_item:
                task_name = self.tree.item(selected_item, 'values')[0]
                self.cursor.execute('UPDATE tasks SET main = 0')
                self.cursor.execute('UPDATE tasks SET main = 1 WHERE task = ?', (task_name,))
                self.conn.commit()
                self.load_tasks()
            else:
                popup = tk.Toplevel(self.root)
                CountTimer(popup)
            return
        except:
            messagebox.showerror("Error", f" Main Task !!!")
            return
    def delete_task(self):
        try:
            # self.get_selected_task()
            selected_item = self.tree.selection()
            if selected_item:
                for item in selected_item:
                    task_name = self.tree.item(item, 'values')[0]
                    print(task_name)
                    if task_name.startswith("[X]"):
                        task_name = task_name[3:]
                    elif task_name == "----------------TOPIC----------------":
                        return
                    self.cursor.execute('DELETE FROM tasks WHERE task = ?', (task_name,))
                    self.conn.commit()
                    self.tree.delete(item)
                self.load_tasks()
        except:
            messagebox.showerror("Error", f" Delete !!!")
            return
    def countdown(self, remaining_seconds):
        if remaining_seconds >= 0:
            minutes = remaining_seconds // 60
            seconds = remaining_seconds % 60
            self.countdown_label.config(text=f"{minutes:02d}:{seconds:02d}")
            # Lưu lại ID của hàm after
            self.after_id = self.root.after(1000, self.countdown, remaining_seconds - 1)
    def on_focus_in(self, event):
        # Khi focus vào ứng dụng, đặt màu nền bình thường và tắt trong suốt
        self.root.configure(bg="#222121")
        self.root.attributes('-alpha', 1.0)
        self.root.attributes('-transparentcolor', '')
    def on_focus_out(self, event):
        # Khi mất focus, đặt trong suốt
        self.root.configure(bg="#222121")
        self.root.attributes('-transparentcolor', '#222121')
        self.root.attributes('-alpha', 0.3)

    def __del__(self):
        # Đóng kết nối cơ sở dữ liệu khi ứng dụng kết thúc
        self.conn.close()


##OK Popup Counter decrease
class PopUpTimer:
    def __init__(self, root, minutes, seconds):
        print("PopUpTimer")
        self.root = root
        self.minutes = minutes
        self.seconds = seconds

        self.root.title("")
        self.root.overrideredirect(1)
        self.root.attributes('-topmost', True)
        self.root.configure(bg="#222121")
        screen_width = self.root.winfo_screenwidth()
        window_width = 300  # Thay đổi giá trị này thành chiều rộng thực tế của cửa sổ của bạn
        x_position = (screen_width // 2) - (window_width // 2)

        # Đặt cửa sổ ở trên cùng và giữa
        self.root.geometry(f"+{x_position + 160}+0")

        # Cho phép di chuyển cửa sổ
        self.root.bind("<B1-Motion>", self.move_window)

        # Nhãn hiển thị thời gian đếm ngược
        self.label = tk.Label(self.root, text=f"{self.minutes:02d}:{self.seconds:02d}", font=("Helvetica", 20),
                              bg="#222121", fg="#FF0000")
        self.label.pack()
        self.close_button = tk.Button(self.root, text="X", command=self.root.destroy, bg="#444444", fg="#ffffff", bd=0)
        self.close_button.pack(side=tk.TOP)
        # Nút để đóng cửa sổ

        # Đặt cửa sổ trong suốt và trên cùng
        self.root.attributes('-transparentcolor', '#222121')
        self.root.attributes('-alpha', 0.7)

        # Bắt đầu đếm ngược
        self.update_timer()

    def update_timer(self):
        if self.minutes > 0 or self.seconds > 0:
            if self.seconds == 0:
                self.minutes -= 1
                self.seconds = 59
            else:
                self.seconds -= 1

            self.label.config(text=f"{self.minutes:02d}:{self.seconds:02d}")

            # Cập nhật mỗi giây
            self.root.after(1000, self.update_timer)
        else:
            self.timer_finished()
            notification.notify(
                title="Time's Up!",
                message="Đă Hết Thời gian Đếm ngược !!!!!!!",
                timeout=7,
            )

    def timer_finished(self):
        self.label.config(text="Time's up!")
        self.root.attributes('-alpha', 1.0)  # Làm cửa sổ hoàn toàn hiện diện khi hết thời gian

    def move_window(self, event):
        self.root.geometry(f'+{event.x_root}+{event.y_root}')


#Open Popup Counter increase
class CountTimer:
    def __init__(self, root):
        print("CountTimer")
        self.root = root
        self.minutes = 0
        self.seconds = 0

        self.root.title("")
        self.root.overrideredirect(1)
        self.root.attributes('-topmost', True)
        self.root.configure(bg="#222121")
        screen_width = self.root.winfo_screenwidth()
        window_width = 300  # Thay đổi giá trị này thành chiều rộng thực tế của cửa sổ của bạn
        x_position = (screen_width // 2) - (window_width // 2)

        # Đặt cửa sổ ở trên cùng và giữa
        self.root.geometry(f"+{x_position}+0")

        # Cho phép di chuyển cửa sổ
        self.root.bind("<B1-Motion>", self.move_window)

        # Nhãn hiển thị thời gian
        self.label = tk.Label(self.root, text=f"{self.minutes:02d}:{self.seconds:02d}", font=("Helvetica", 20),
                              bg="#222121", fg="#FFFF33")
        self.label.pack()

        # Nút đóng cửa sổ
        self.close_button = tk.Button(self.root, text="X", command=self.root.destroy, bg="#444444", fg="#ffffff", bd=0)
        self.close_button.pack(side=tk.TOP)

        # Đặt cửa sổ trong suốt và trên cùng
        self.root.attributes('-transparentcolor', '#222121')
        self.root.attributes('-alpha', 0.7)

        # Bắt đầu đếm thời gian
        self.update_timer()

    def update_timer(self):
        # Tăng thời gian
        self.seconds += 1
        if self.seconds == 60:
            self.minutes += 1
            self.seconds = 0

        # Cập nhật nhãn
        self.label.config(text=f"{self.minutes:02d}:{self.seconds:02d}")

        # Cập nhật mỗi giây
        self.root.after(1000, self.update_timer)

    def move_window(self, event):
        self.root.geometry(f'+{event.x_root}+{event.y_root}')


if __name__ == "__main__":
    root = tk.Tk()
    app = TodoListApp(root)
    root.mainloop()
