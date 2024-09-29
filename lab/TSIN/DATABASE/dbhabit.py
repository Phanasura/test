halink = "DATABASE/habit.db"
import sqlite3
from datetime import datetime, timedelta
from tabulate import tabulate
from tkinter import Tk, Button, StringVar
from tkcalendar import Calendar
from datetime import timedelta
class HabitManager:
    def __init__(self, db_name):
        self.db_name = db_name
        self.conn = sqlite3.connect(db_name)
        self.cursor = self.conn.cursor()
        self.level = ["New kid","Firm beliver","Master","GrandMaster","Saint"]
        self.create_table()
    def create_table(self):
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS habits (
                id INTEGER PRIMARY KEY,
                name TEXT NOT NULL,
                days_passed INTEGER NOT NULL,
                days_remaining INTEGER NOT NULL,
                start_date DATE NOT NULL,
                end_date DATE NOT NULL,
                level TEXT
            )
        ''')
        self.conn.commit()
    def add_habit(self):
        try:
            current_date = datetime.now().date()
            start_date = current_date.strftime('%Y-%m-%d')
            name = input("Enter habit name: ")
            days_remaining = int(input("Enter the number of days for the habit: "))
            end_date = (current_date + timedelta(days=days_remaining)).strftime('%Y-%m-%d')
            level = "New kid"
            days_passed = 0
            self.cursor.execute('''
                        INSERT INTO habits (name, days_passed, days_remaining, start_date, end_date, level)
                        VALUES (?, ?, ?, ?, ?, ?)
                    ''', (name, days_passed, days_remaining, start_date, end_date, level))
            self.conn.commit()
            with sqlite3.connect('appointments.db') as conne:
                cursors = conne.cursor()
                cursors.execute('''
                                    INSERT INTO appointments (name, date_time, category)
                                    VALUES (?, ?, ?)
                                ''', (name, f"{end_date} 00:00:00", "habit"))
                conne.commit()
                print("Cuộc hẹn đã được thêm thành công.")
        except:
            return
    def add_habit_new(self, name, days_remaining):
        try:
            days_remaining = int(days_remaining)
            current_date = datetime.now().date()
            start_date = current_date.strftime('%Y-%m-%d')
            end_date = (current_date + timedelta(days=days_remaining)).strftime('%Y-%m-%d')
            level = "New kid"
            days_passed = 0
            self.cursor.execute('''
                        INSERT INTO habits (name, days_passed, days_remaining, start_date, end_date, level)
                        VALUES (?, ?, ?, ?, ?, ?)
                    ''', (name, days_passed, days_remaining, start_date, end_date, level))
            self.conn.commit()
            with sqlite3.connect('appointments.db') as conne:
                cursors = conne.cursor()
                cursors.execute('''
                                    INSERT INTO appointments (name, date_time, category)
                                    VALUES (?, ?, ?)
                                ''', (name, f"{end_date} 00:00:00", "habit"))
                conne.commit()
            print("ADD HABIT SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("ADD HABIT UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def delete_habit(self):
        try:
            self.display_habits()
            habit_id = input("Enter the ID of the habit you want to delete: ")
            habit_id = int(habit_id)
            self.cursor.execute('DELETE FROM habits WHERE id = ?', (habit_id,))
            self.conn.commit()
            print("Habit deleted successfully.")
        except:
            return
    def delete_habit_new(self,habit_id):
        try:
            #self.display_habits()
            habit_id = int(habit_id)
            self.cursor.execute('DELETE FROM habits WHERE id = ?', (habit_id,))
            self.conn.commit()
            print("DELETE HABIT SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("DELETE HABIT UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def get_calendar(self):
        root = Tk()
        date_var = StringVar()

        def set_selected_date():
            date_var.set(cal.get_date())
            root.destroy()

        cal = Calendar(root, selectmode="day", year=datetime.now().year, month=datetime.now().month,
                       day=datetime.now().day)
        cal.pack(padx=10, pady=10)
        select_date_button = Button(root, text="Chọn ngày", command=set_selected_date)
        select_date_button.pack(pady=10)
        root.mainloop()
        return datetime.strptime(date_var.get(), "%m/%d/%y")
    def edit_habit(self):
        try:
            self.display_habits()
            habit_id = int(input("Enter the ID of the habit you want to edit: "))
            self.cursor.execute('SELECT * FROM habits WHERE id = ?', (habit_id,))
            existing_habit = self.cursor.fetchone()
            print(existing_habit)
            if existing_habit:
                headers = ["ID", "Name", "Days Passed", "Days Remaining", "Start Date", "End Date", "Level"]
                habit_table = [headers, list(existing_habit)]
                print("Current Habit Information:")
                print(tabulate(habit_table, tablefmt="grid"))
                name = input("Enter new habit name (press Enter to keep the current name): ") or existing_habit[1]
                days_len = input("Enter the number of days for the habit (press Enter to keep the current days remaining): ") or (existing_habit[2]+existing_habit[3])
                #print(days_len)
                start_date = input("Enter new start date (YYYY-MM-DD) (press Enter to keep the current start date): ") or existing_habit[4]
                level = existing_habit[6]
                end_date = (datetime.strptime(start_date, '%Y-%m-%d') + timedelta(days=int(days_len))).strftime('%Y-%m-%d')
                self.cursor.execute('''
                    UPDATE habits
                    SET name = ?, days_remaining = ?, start_date = ?, end_date = ?, level = ?
                    WHERE id = ?
                ''', (name, existing_habit[3], start_date, end_date, level, habit_id))
                self.conn.commit()
                print("Habit updated successfully.")
            else:
                print(f"No habit found with ID {habit_id}.")
        except ValueError:
            print("Invalid habit ID. Please enter a valid integer.")
    def edit_habit_new(self, habit_id, name, days_len, start_date):
        try:
            habit_id = int(habit_id)
            self.cursor.execute('SELECT * FROM habits WHERE id = ?', (habit_id,))
            existing_habit = self.cursor.fetchone()
            if existing_habit:
                if name.strip() == 'none':
                    name = existing_habit[1]
                if days_len.strip() == 'none':
                    days_len = (existing_habit[2]+existing_habit[3])
                if start_date.strip() == 'y':
                    start_date = self.get_calendar()
                    if not start_date:
                        print("EDIT HABIT UNSUCCESSFULLY ! 😓 😩 😖 😰")
                        return
                    else:
                        start_date = start_date.strftime("%Y-%m-%d")
                else:
                    start_date = existing_habit[4]
                level = existing_habit[6]
                end_date = (datetime.strptime(start_date, '%Y-%m-%d') + timedelta(days=int(days_len))).strftime('%Y-%m-%d')
                self.cursor.execute('''
                    UPDATE habits
                    SET name = ?, days_remaining = ?, start_date = ?, end_date = ?, level = ?
                    WHERE id = ?
                ''', (name, existing_habit[3], start_date, end_date, level, habit_id))
                self.conn.commit()
                print("EDIT HABIT SUCCESSFULLY ! 👍 👌 🎊 ✅")
            else:
                print(f"No habit found with ID {habit_id}.")
        except Exception as e:
            print(e)
            print("EDIT HABIT UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def update_habit_dates(self):
        current_date = datetime.now().date()
        self.cursor.execute('SELECT id, start_date, end_date, days_remaining FROM habits')
        habits = self.cursor.fetchall()
        for habit in habits:
            habit_id, start_date, end_date, days_remaining = habit
            days_passed = (current_date - datetime.strptime(start_date, '%Y-%m-%d').date()).days
            days_remaining = (datetime.strptime(end_date, '%Y-%m-%d').date() - current_date).days
            if days_passed + days_remaining == 0:
                percent_completed = 0
            else:
                percent_completed = (days_passed / (days_passed + days_remaining)) * 100
            if percent_completed < 10:
                level = self.level[0]
            elif 10 <= percent_completed < 30:
                level = self.level[1]
            elif 30 <= percent_completed < 50:
                level = self.level[2]
            elif 50 <= percent_completed < 70:
                level = self.level[3]
            else:
                level = self.level[4]
            self.cursor.execute('''
                UPDATE habits
                SET days_passed = ?, days_remaining = ?, level = ?
                WHERE id = ?
            ''', (days_passed, days_remaining, level, habit_id))
            self.conn.commit()
    def display_habits(self):
        self.update_habit_dates()

        self.cursor.execute('SELECT * FROM habits')
        habits = self.cursor.fetchall()

        headers = ["ID", "Name", "Days Passed", "Days Remaining", "Start Date", "End Date", "Level"]
        habit_table = []

        for habit in habits:
            habit_id, name, days_passed, days_remaining, start_date, end_date, level = habit
            start_date_formatted = datetime.strptime(start_date, '%Y-%m-%d').strftime('%d-%m-%Y')
            end_date_formatted = datetime.strptime(end_date, '%Y-%m-%d').strftime('%d-%m-%Y')
            habit_table.append([habit_id, name, days_passed, days_remaining, start_date_formatted, end_date_formatted, level])

        return tabulate([headers] + habit_table, tablefmt="fancy_grid")

    def display(self):
        self.update_habit_dates()

        self.cursor.execute('SELECT * FROM habits ORDER BY days_passed ASC')
        habits = self.cursor.fetchall()

        headers = ["Name", "Days Passed", "Days Remaining", "Level"]
        habit_table = []

        for habit in habits:
            habit_id, name, days_passed, days_remaining, start_date, end_date, level = habit
            habit_table.append(
                [name, days_passed, days_remaining, level])

        return tabulate([headers] + habit_table, tablefmt="fancy_grid")
    '''
    def performance(self):
        self.cursor.execute('SELECT level, name, days_passed, days_remaining FROM habits ORDER BY level')
        habits = self.cursor.fetchall()

        header_line = "+------------------------------------+"
        row_line = "+------------------------------------+"
        separator_line = "+------------------------------------+"

        result = ""

        for habit in habits:
            level, name, days_passed, days_remaining = habit
            result += (
                f"{header_line}\n"
                f"| {level:<34} |\n"
                f"{row_line}\n"
                f"| {name:<34} |\n"
                f"{row_line}\n"
                f"| {days_passed:^15} | {days_remaining:^15} |\n"
                f"{separator_line}\n\n"
            )

        return result
    '''

    def close_connection(self):
        self.conn.close()
if __name__ == "__main__":
    db = HabitManager("habit.db")
    while True:
        print(db.display())
        print("1. Add")
        print("2. Edit")
        print("3. Delete")
        print("0. Quit")
        choice = input("Enter your choice >>> ")
        if choice == '1':
            db.add_habit()
        elif choice == '2':
            db.edit_habit()
        elif choice == '3':
            db.delete_habit()
        elif choice == '4':
            db.display_habits()
        elif choice == '0':
            break
        else:
            print("Invalid choice. Please try again.")
    db.close_connection()

