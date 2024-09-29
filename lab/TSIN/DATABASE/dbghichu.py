nslink = 'DATABASE/notes_database.db'
import sqlite3
from tabulate import tabulate

class NotesManager:
    def __init__(self, db_name):
        self.conn = sqlite3.connect(db_name)
        self.cursor = self.conn.cursor()
        self.initialize_database()

    def initialize_database(self):
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS notes (
                id INTEGER PRIMARY KEY,
                note TEXT,
                process TEXT
            )
        ''')

        self.cursor.execute('SELECT COUNT(*) FROM notes')
        record_count = self.cursor.fetchone()[0]

        if record_count == 0:
            self.cursor.execute('INSERT INTO notes (note, process) VALUES (?, ?)', ('NONE', 'NONE'))
            self.conn.commit()

    def get_inp(self):
        content_lines = []
        while True:
            line = input()
            if line.lower() == "stop":
                break
            content_lines.append(line)
        new_content = "\n".join(content_lines)
        return new_content

    def display_notes(self):
        self.cursor.execute('SELECT note, process FROM notes')
        notes = self.cursor.fetchall()
        notes[0] = (notes[0][0][:34]+"...", notes[0][1][:34]+"...")
        headers = ["Ghi chú", "Tiến trình"]
        table = tabulate(notes, headers, tablefmt="fancy_grid")
        return table

    def edit_note(self):
        self.cursor.execute('SELECT * FROM notes')
        note = self.cursor.fetchone()

        if note:
            print(f"Ghi chú: {note[1]}")
            print(f"Tiến trình: {note[2]}")
            print("Nhập ghi chú mới ('stop' để kết thúc) >>> ")
            new_note = self.get_inp()
            print("Nhập tiến trình mới ('stop' để kết thúc) >>> ")
            new_process = self.get_inp()
            if new_note.strip() == "":
                new_note = note[1]
            if new_process.strip() == "":
                new_process = note[2]
            self.cursor.execute('UPDATE notes SET note = ?, process = ? WHERE id = ?', (new_note, new_process, note[0]))
            self.conn.commit()
            print("Bản ghi đã được chỉnh sửa thành công!")
        else:
            print("Không có bản ghi nào để chỉnh sửa.")

    def get_np(self):
        self.cursor.execute('SELECT * FROM notes')
        note = self.cursor.fetchone()
        if note:
            return note

    def opengc(self):
        self.cursor.execute('SELECT * FROM notes')
        note = self.cursor.fetchone()
        if note:
            print(f"\n\n\n################Temporary Note################ >>>>>>>> \n\n\n{note[1]}\n\n\n######################################################################################################################################")
            print(f"\n\n\n################Temporary Processing################ >>>>>>>>>> \n\n\n{note[2]}\n\n\n")


    def edit_note_new(self, new_note, new_process):
        try:
            self.cursor.execute('SELECT * FROM notes')
            note = self.cursor.fetchone()
            if note:
                if new_note.strip() == "none":
                    new_note = note[1]
                if new_process.strip() == "none":
                    new_process = note[2]
                self.cursor.execute('UPDATE notes SET note = ?, process = ? WHERE id = ?',
                                    (new_note, new_process, note[0]))
                self.conn.commit()
                print("EDIT SUCCESSFULLY ! 👍 👌 🎊 ✅")
            else:
                print("DATA NOT FOUND !")
        except:
            print("EDIT UNSUCCESSFULLY ! 😓 😩 😖 😰")

    def close_connection(self):
        self.conn.close()

    def run(self):
        while True:
            print("\n===== Quản lý Ghi chú và Tiến trình =====")
            print(self.display_notes())
            print(self.opengc())
            print("2. Chỉnh sửa Ghi chú")
            print("3. Thoát")
            choice = input("Nhập lựa chọn của bạn: ")
            if choice == '2':
                self.edit_note()
            elif choice == '3':
                print("Tạm biệt!")
                break
            else:
                print("Lựa chọn không hợp lệ. Vui lòng chọn lại.")
        self.close_connection()

if __name__ == "__main__":
    notes_manager = NotesManager('notes_database.db')
    notes_manager.run()
