tolink = "DATABASE/todolist.db"
import sqlite3
from tabulate import tabulate
from datetime import datetime
from tkinter import Tk, StringVar, Button, Label, Spinbox
class TodoListManager:
    def __init__(self, db_name):
        self.db_name = db_name
        self.conn = sqlite3.connect(db_name)
        self.cursor = self.conn.cursor()
        self.check = ""
        self.create_table()
    def create_table(self):
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS tasks (
                id INTEGER PRIMARY KEY,
                is_completed TEXT,
                task_name TEXT NOT NULL,
                note TEXT,
                habit TEXT,
                time TEXT
            )
        ''')
        self.conn.commit()
    def get_task_by_id(self, task_id):
        self.cursor.execute('SELECT is_completed, task_name, note, habit, time  FROM tasks WHERE id = ?', (task_id,))
        row = self.cursor.fetchone()
        if row:
            return row
        return None, None, None, None, None
    def add_task(self):
        done = " "
        task_name = input("Enter Task Name ('q' = quit)>>>")
        if task_name.lower() == "q":
            return
        print("Enter note ('q' = quit || 'stop' = break)>>>")
        content_lines = []
        while True:
            line = input()
            if line.lower() == "stop":
                break
            content_lines.append(line)
        note = "\n".join(content_lines)
        if note.lower() == "q":
            return
        habit = input("Is it habit? (y | n)>>>")
        if habit.lower() == "quit":
            return
        if habit.strip() == 'y':
            habit = "✓"
        else:
            habit = " "
        self.cursor.execute('''
            INSERT INTO tasks (is_completed, task_name, note, habit)
            VALUES (?, ?, ?, ?)
        ''', (done, task_name, note, habit))
        self.conn.commit()
        #print(self.print_task_table())

    def get_time(self):
        global meridian_var  # Declare meridian_var as a global variable
        root = Tk()
        time_var = StringVar()
        meridian_var = StringVar()

        hour_spinbox = Spinbox(root, from_=1, to=12, width=16)
        minute_spinbox = Spinbox(root, from_=0, to=59, width=16)

        meridian_spinbox = Spinbox(root, values=("AM", "PM"), width=16)

        def set_selected_time():
            time_str = f"{hour_spinbox.get().zfill(2)}:{minute_spinbox.get().zfill(2)} {meridian_spinbox.get()}".strip()
            time_var.set(time_str)
            root.destroy()

        hour_label = Label(root, text="Giờ:")
        hour_label.grid(row=0, column=0, padx=10, pady=10)

        hour_spinbox.grid(row=0, column=1, padx=10, pady=10)

        minute_label = Label(root, text="Phút:")
        minute_label.grid(row=1, column=0, padx=10, pady=10)

        minute_spinbox.grid(row=1, column=1, padx=10, pady=10)

        meridian_label = Label(root, text="AM/PM:")
        meridian_label.grid(row=2, column=0, padx=10, pady=10)

        meridian_spinbox.grid(row=2, column=1, padx=10, pady=10)

        select_time_button = Button(root, text="Ok", command=set_selected_time)
        select_time_button.grid(row=3, column=0, columnspan=2, pady=10)

        root.mainloop()
        #print()
        return datetime.strptime(time_var.get(), "%I:%M %p").strftime("%I:%M %p")

    def add_task_new(self,task_name, note, habit,dtime):
        try:
            done = ""
            if habit.strip() == 'y':
                habit = "✓"
            else:
                habit = ""
            self.cursor.execute('''
                        INSERT INTO tasks (is_completed, task_name, note, habit, time)
                        VALUES (?, ?, ?, ?, ?)
                    ''', (done, task_name, note, habit, dtime))
            self.conn.commit()
            print("ADD TASK SUCCESSFULLY !!!  👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print(f"ADD TASK UNSUCCESSFULLY !!! 😓 😩 😖 😰")
    def get_tasks(self):
        self.cursor.execute('SELECT * FROM tasks ORDER BY time')
        tasks = self.cursor.fetchall()
        return tasks
    def doned(self):
        try:
            task_id = input("Enter Task ID you are done >>>")
            if task_id.lower() == "quit":
                return
        except ValueError:
            print("You must enter a valid ID number")
            return
        current_status, current_name, cur_note, cur_type = self.get_task_by_id(task_id)
        if current_status == "✓":
            new_status = " "
        else:
            new_status = "✓"
        self.cursor.execute('''
            UPDATE tasks
            SET is_completed = ?
            WHERE id = ?
        ''', (new_status, task_id))
        self.conn.commit()
        #print(self.print_task_table())
    def doned_new(self, task_id):
        try:
            task_id = int(task_id)
            current_status, current_name, cur_note, cur_type, ctime = self.get_task_by_id(task_id)
            if current_status == "✓":
                new_status = " "
            else:
                new_status = "✓"
            self.cursor.execute('''
                UPDATE tasks
                SET is_completed = ?
                WHERE id = ?
            ''', (new_status, task_id))
            self.conn.commit()
            print("MARK DONE TASK SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("MARK DONE TASK UNSUCCESSFULLY ! 😓 😩 😖 😰")

    def clear_all(self):
        self.cursor.execute('DELETE FROM tasks')
        self.conn.commit()
        #print("All notes have been deleted.")
        #print(self.get_notes_as_table())
    def delete_task(self):
        try:
            task_id = input("Enter Task ID to delete >>>")
            if task_id.lower() == "quit":
                return
        except ValueError:
            print("You must enter a valid ID number")
            return
        self.cursor.execute('''
            DELETE FROM tasks
            WHERE id = ?
        ''', (task_id,))
        self.conn.commit()
        #print(self.print_task_table())
    def delete_task_new(self, task_id):
        try:
            task_id = int(task_id)
            self.cursor.execute('''
                DELETE FROM tasks
                WHERE id = ?
            ''', (task_id,))
            self.conn.commit()
            # print(self.print_task_table())
            print("DELETE TASK SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("DELETE TASK UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def edit_task(self):
        try:
            task_id = int(input("Enter Task ID to edit ('q' = quit)>>>"))
            current_task = self.get_task_by_id(task_id)
        except ValueError:
            print("You must enter a valid ID number")
            return
        if current_task:
            current_done, current_name, cur_note, cur_type = current_task
            new_name = input(f"Enter New Task Name (or press Enter to keep old) ('q' = quit)>>> ")
            if new_name.lower() == "q":
                return
            print(f"Enter New Note ('stop' = break)>>> ")
            content_lines = []
            while True:
                line = input()
                if line.lower() == "stop":
                    break
                content_lines.append(line)
            new_note = "\n".join(content_lines)
            new_type = input("Is it habit? (y | n)>>>")
            if new_type.strip() == 'y':
                new_type = "✓"
            else:
                new_type = " "
            if not new_note.strip():
                new_note = cur_note
            if not new_name.strip():
                new_name = current_name

            self.cursor.execute('''
                    UPDATE tasks
                    SET is_completed = ?, task_name = ?, note=? ,habit=?
                    WHERE id = ?
                ''', (current_done, new_name,new_note,new_type,  task_id))
            self.conn.commit()
            print(f"Task with ID '{task_id}' has been edited.")
        else:
            print(f"No task found with ID '{task_id}'.")
        #print(self.print_task_table())
    def edit_task_new(self, task_id, new_name, new_note, new_type, dtime):
        try:
            task_id = int(task_id)
            current_task = self.get_task_by_id(task_id)
            if current_task:
                current_done, current_name, cur_note, cur_type, cdtime = current_task
                if new_name.lower().strip() == "none":
                    new_name = current_name
                elif new_note.lower().strip() == "none":
                    new_note = cur_note
                if dtime.strip() == 'y':
                    dtime = self.get_time()
                else:
                    dtime = cdtime
                self.cursor.execute('''
                                UPDATE tasks
                                SET is_completed = ?, task_name = ?, note=? ,habit=?, time=?
                                WHERE id = ?
                            ''', (current_done, new_name, new_note, new_type, dtime, task_id))
                self.conn.commit()
                print("EDIT TASK SUCCESSFULLY ! 👍 👌 🎊 ✅")
            else:
                print(f"No task found with ID '{task_id}'.")
                print("EDIT TASK UNSUCCESSFULLY ! 😓 😩 😖 😰")
            # print(self.print_task_table())
        except Exception as e:
            print(e)
            print("EDIT TASK UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def print_task_table(self):
        tasks = self.get_tasks()
        habit_data = []
        non_habit_data = []

        for task in tasks:
            task_data = (task[0], task[1], task[2][:25]+"...", task[3][:25]+"...", task[4], task[5])
            if task[4].strip() == '✓':
                habit_data.append(task_data)
            else:
                non_habit_data.append(task_data)
        non_habit_data.reverse()
        combined_data = non_habit_data + habit_data
        table = tabulate(combined_data,
                         headers=["Done?", "Task Name", "Note", "Habit?","Time"],
                         tablefmt="fancy_grid")
        return table
    def show_remain_tasks(self):
        current_time = datetime.now().strftime("%I:%M %p")
        #query = 'SELECT * FROM tasks WHERE is_completed != ? AND time > ? ORDER BY time'
        #self.cursor.execute(query, ("✓", current_time))
        #tasks = self.cursor.fetchall()
        tasks = self.get_tasks()
        if not tasks:
            return "No tasks to show."
        else:
            task_data = [(task[1], task[2][:25]+"...", task[3][:25]+"...", task[4], task[5]) for task in tasks]
            table = tabulate(task_data, headers=["Done?", "Task Name", "Note", "Habit?", "Time"], tablefmt="fancy_grid")
            return table
    def open_task(self, note_id):
        try:
            note_id = int(note_id)
            current_task = self.get_task_by_id(note_id)
            if current_task:
                current_status, current_name, cur_note, cur_type, ctime = current_task
                print("\nCurrent task name: >>>")
                print(current_name)
                print("\n\n\nCurrent task note: >>>")
                print(cur_note)
                print("\n\n\nOPEN TASK SUCCESSFULLY !!!  👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print(f"OPEN TASK UNSUCCESSFULLY !!! 😓 😩 😖 😰")

    def close(self):
        self.conn.close()

if __name__ == "__main__":
    todo_manager = TodoListManager('todolist.db')
    while True:
        #print(todo_manager.print_task_table())
        print(todo_manager.show_remain_tasks())
        print("1. Add Task")
        print("2. Mark")
        print("3. Edit Task")
        print("4. Delete Task")
        print("5. Quit")
        choice = input("Enter your choice >>> ")
        if choice == '1':
            print(todo_manager.get_time())
        elif choice == '2':
            todo_manager.doned()
        elif choice == '3':
            todo_manager.edit_task()
        elif choice == '4':
            todo_manager.delete_task()
        elif choice == '0':
            print(todo_manager.print_task_table())
        elif choice == '6':
            todo_manager.show_remain_tasks()  # Thêm lựa chọn này
        elif choice == '5':
            break
        else:
            print("Invalid choice. Please try again.")
    todo_manager.close()

