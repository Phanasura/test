applink = 'DATABASE/appointments.db'
import sqlite3
from datetime import datetime
from tabulate import tabulate
from tkinter import Tk, Button, StringVar
from tkcalendar import Calendar
from datetime import timedelta

class AppointmentManager:
    def __init__(self, db_path):
        self.conn = sqlite3.connect(db_path)
        self.cursor = self.conn.cursor()
        self.create_table()
        self.delete_past_appointments()
    def create_table(self):
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS appointments (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                date_time DATE NOT NULL, 
                category TEXT
            )
        ''')
        self.conn.commit()
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
    def add_app(self):
        name = input("Nhập tên cuộc hẹn(q): ")
        if name.strip() == 'q':
            return
        date_time = self.get_calendar()
        print(f"Ngày: {date_time}")
        category = input("Đây có phải sự kiện không?(q | y | n)>>>")
        if category.strip() == 'q':
            return
        elif category.strip() == 'y':
            category = '✓'
        else:
            category = ""
        self.add_appointment(name,date_time,category)
        return
    def add_app_new(self, name, category):
        try:
            date_time = self.get_calendar()
            if not date_time:
                print("ADD UNSUCCESSFULLY ! 😓 😩 😖 😰")
                return
            print(f"Ngày: {date_time}")
            if category.strip() == 'y':
                category = '✓'
            else:
                category = ""
            self.cursor.execute('''
                        INSERT INTO appointments (name, date_time, category)
                        VALUES (?, ?, ?)
                    ''', (name, date_time, category))
            self.conn.commit()
            print("ADD SUCCESSFULLY ! 👍 👌 🎊 ✅")
            return
        except Exception as e:
            print(e)
            print("ADD UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def add_appointment(self,name,date_time,category):
        self.cursor.execute('''
            INSERT INTO appointments (name, date_time, category)
            VALUES (?, ?, ?)
        ''', (name, date_time, category))
        self.conn.commit()
        print("Cuộc hẹn đã được thêm thành công.")
    def delete_appointment(self):
        appointment_id = input("Nhập ID của cuộc hẹn cần xóa: ")
        self.cursor.execute('''
            DELETE FROM appointments
            WHERE id = ?
        ''', (appointment_id,))
        self.conn.commit()
        print("Cuộc hẹn đã được xóa thành công.")
    def delete_appointment_new(self,appointment_id):
        try:
            appointment_id = int(appointment_id)
            self.cursor.execute('''
                        DELETE FROM appointments
                        WHERE id = ?
                    ''', (appointment_id,))
            self.conn.commit()
            print("DELETE SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("DELETE UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def edit_appointment(self):
        appointment_id = input("Nhập ID của cuộc hẹn cần chỉnh sửa (q):")
        self.cursor.execute('''
                SELECT * FROM appointments
                WHERE id = ?
            ''', (appointment_id,))
        existing_appointment = self.cursor.fetchone()
        if existing_appointment:
            if appointment_id.strip() == 'q':
                return
            name = input("Nhập tên mới của cuộc hẹn (q):") or existing_appointment[1]
            if name.strip() == 'q':
                return
            opt = input("Bạn có muốn đổi ngày không? (y | n)>>>")
            if opt.strip() == 'y':
                date_time = self.get_calendar()
            else:
                date_time = existing_appointment[2]
            print(f"Ngày: {date_time}")
            category = input("Đây có phải sự kiện không?(q | y | n)>>>") or existing_appointment[3]
            if category.strip() == 'q':
                return
            elif category.strip() == 'y':
                category = '✓'
            else:
                category = ""
            self.cursor.execute('''
                UPDATE appointments
                SET name = ?, date_time = ?, category = ?
                WHERE id = ?
            ''', (name, date_time, category, appointment_id))
            self.conn.commit()
            print("Cuộc hẹn đã được chỉnh sửa thành công.")
        else:
            print(f"Không tìm thấy cuộc hẹn với ID {appointment_id}")
    def edit_appointment_new(self, appointment_id, name,category,opt):
        try:
            appointment_id = int(appointment_id)
            self.cursor.execute('''
                            SELECT * FROM appointments
                            WHERE id = ?
                        ''', (appointment_id,))
            existing_appointment = self.cursor.fetchone()
            if existing_appointment:
                if name.strip() == "none":
                    name = existing_appointment[1]
                if category.strip() == 'y':
                    category = '✓'
                else:
                    category = ""
                if opt.strip() == 'y':
                    date_time = self.get_calendar()
                    if not date_time:
                        print("EDIT UNSUCCESSFULLY ! 😓 😩 😖 😰")
                        return
                else:
                    date_time = existing_appointment[2]
                print(f"Ngày: {date_time}")
                self.cursor.execute('''
                            UPDATE appointments
                            SET name = ?, date_time = ?, category = ?
                            WHERE id = ?
                        ''', (name, date_time, category, appointment_id))
                self.conn.commit()
                print("EDIT SUCCESSFULLY ! 👍 👌 🎊 ✅")
            else:
                print(f"Không tìm thấy cuộc hẹn với ID")
        except Exception as e:
            print(e)
            print("EDIT UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def display_appointments(self):
        self.cursor.execute('''
            SELECT * FROM appointments
            ORDER BY date_time ASC
        ''')
        appointments = self.cursor.fetchall()
        if not appointments:
            print("Không có cuộc hẹn nào.")
        else:
            headers = ["ID", "Tên", "Thời điểm", "Sự kiện"]
            formatted_appointments = []
            for appointment in appointments:
                formatted_appointment = list(appointment)
                # Chuyển đổi date_time thành định dạng "dd-mm-yyyy"
                if formatted_appointment[3] == '✓':
                    #print(formatted_appointment[3])
                    formatted_appointment[2] = datetime.strptime(str(appointment[2]), "%Y-%m-%d %H:%M:%S").strftime(
                        "%d-%m")
                else:
                    #print(formatted_appointment[3])
                    formatted_appointment[2] = datetime.strptime(str(appointment[2]), "%Y-%m-%d %H:%M:%S").strftime(
                        "%d-%m-%Y")
                formatted_appointments.append(formatted_appointment)
            table = tabulate(formatted_appointments, headers=headers, tablefmt="grid")
            print(table)
    def close_connection(self):
        self.conn.close()
    def upcoming_appointments(self):
        try:
            current_date = datetime.now()
            end_date = current_date + timedelta(days=30)
            self.cursor.execute('''
                        SELECT * FROM appointments
                    ''')
            upcoming_appointments = self.cursor.fetchall()
            if not upcoming_appointments:
                return "Không có cuộc hẹn trong 30 ngày tiếp theo."
            else:
                headers = ["Tên", "Thời điểm", "Thể loại"]
                formatted_appointments = []
                for appointment in upcoming_appointments:
                    formatted_appointment = list(appointment)
                    appointment_date = datetime.strptime(formatted_appointment[2], "%Y-%m-%d %H:%M:%S")
                    if formatted_appointment[3] == '✓':
                        current_date_formatted = datetime.strptime(current_date.strftime("%d-%m"), "%d-%m")
                        appointment_date_formatted = datetime.strptime(appointment_date.strftime("%d-%m"), "%d-%m")
                        end_date_formatted = datetime.strptime(end_date.strftime("%d-%m"), "%d-%m")
                        if current_date_formatted <= appointment_date_formatted <= end_date_formatted:
                            formatted_appointment[2] = appointment_date.strftime("%d-%m")
                            formatted_appointments.append(formatted_appointment[1:])
                    else:
                        if appointment_date.strftime("%Y-%m-%d") <= end_date.strftime("%Y-%m-%d"):
                            formatted_appointment[2] = appointment_date.strftime("%d-%m-%Y")
                            formatted_appointments.append(formatted_appointment[1:])
                table = tabulate(formatted_appointments, headers=headers, tablefmt="fancy_grid")
                return table
        except Exception as e:
            print(e)
            return "Can't Find Upcoming Appointments !!!"
    def delete_past_appointments(self):
        current_date = datetime.now().replace(hour=0, minute=0, second=0, microsecond=0)
        self.cursor.execute('''
            DELETE FROM appointments
            WHERE date_time < ? AND (category IS NULL OR category = '')
        ''', (current_date,))
        self.conn.commit()
        #print("Các cuộc hẹn đã qua thời gian hiện tại và có habit rỗng đã được xóa thành công.")

if __name__ == "__main__":
    manager = AppointmentManager('appointments.db')

    while True:
        manager.delete_past_appointments()
        print("\n===== Quản lý Cuộc hẹn =====")
        manager.display_appointments()
        #print(manager.upcoming_appointments())
        print("1. Thêm cuộc hẹn")
        print("2. Xóa cuộc hẹn")
        print("3. Chỉnh sửa cuộc hẹn")
        print("4. Hiển thị danh sách cuộc hẹn")
        print("5. Cuộc hẹn trong 30 ngày tới")
        print("0. Thoát")

        choice = input("Nhập lựa chọn của bạn: ")

        if choice == '1':
            manager.add_app()
        elif choice == '2':
            manager.delete_appointment()
        elif choice == '3':
            manager.edit_appointment()
        elif choice == '4':
            manager.display_appointments()
        elif choice == '5':
            print(manager.upcoming_appointments())
        elif choice == '0':
            manager.close_connection()
            break
        else:
            print("Lựa chọn không hợp lệ. Vui lòng thử lại.")
