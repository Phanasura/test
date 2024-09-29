apilink = 'DATABASE/aiapikey.db'
import sqlite3
from tabulate import tabulate

def get_api():
    try:
        with sqlite3.connect(apilink) as conn_api:
            cursor_api = conn_api.cursor()
            cursor_api.execute(
                'SELECT * FROM apikey'
            )
            api = cursor_api.fetchone()[1]
            if api:
                return api
            else:
                print("API NOT FOUND !")
            conn_api.commit()
    except sqlite3.Error as e:
        print(f"API KEY:   SQLite error: {e}")

class APIManager:
    def __init__(self, db_name):
        self.conn = sqlite3.connect(db_name)
        self.cursor = self.conn.cursor()
        self.initialize_database()

    def initialize_database(self):
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS apikey (
                id INTEGER PRIMARY KEY,
                api TEXT
            )
        ''')

        self.cursor.execute('SELECT COUNT(*) FROM apikey')
        record_count = self.cursor.fetchone()[0]
        if record_count == 0:
            self.cursor.execute('INSERT INTO apikey (api) VALUES (?)', ('AIzaSyBAYU3roNE4Du-kv9-gnCqRp34sqSg7EkQ',))
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

    def display_apis(self):
        self.cursor.execute('SELECT api FROM apikey')
        notes = self.cursor.fetchall()

        headers = ["API KEY"]
        table = tabulate(notes, headers, tablefmt="fancy_grid")
        return table

    def edit_note(self):
        self.cursor.execute('SELECT * FROM apikey')
        note = self.cursor.fetchone()

        if note:
            print(f"API KEY HIỆN TẠI >>>{note[1]}")
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
    def edit_apis_new(self, new_api):
        try:
            self.cursor.execute('SELECT * FROM apikey')
            api = self.cursor.fetchone()
            if api:
                print(f"Temporary API KEY >>>\n{api[1]}")
                if new_api.strip() == "none":
                    new_api = api
                self.cursor.execute('UPDATE apikey SET api = ? WHERE id = ?',
                                    (new_api, api[0]))
                self.conn.commit()
                print("EDIT SUCCESSFULLY ! 👍 👌 🎊 ✅")
            else:
                print("DATA NOT FOUND !")
                print("EDIT UNSUCCESSFULLY ! 😓 😩 😖 😰")
        except Exception as e:
            print(e)
            print("EDIT UNSUCCESSFULLY ! 😓 😩 😖 😰")

    def close_connection(self):
        self.conn.close()

    def run(self):
        print(get_api())
        while True:
            print("\n===== Quản lý API =====")
            print(self.display_apis())
            print("2. Chỉnh sửa Ghi chú")
            print("3. Thoát")
            choice = input("Nhập lựa chọn của bạn: ")
            if choice == '2':
                choices = input("Nhập : ")
                self.edit_apis_new(choices)
            elif choice == '3':
                print("Tạm biệt!")
                break
            else:
                print("Lựa chọn không hợp lệ. Vui lòng chọn lại.")
        self.close_connection()

if __name__ == "__main__":
    notes_manager = APIManager('aiapikey.db')
    notes_manager.run()
