mlink = 'DATABASE/music.db'
import sqlite3
from tabulate import tabulate
from tkinter import filedialog
import webbrowser
import os

class MusicDatabase:
    def __init__(self, db_path):
        self.db_path = db_path
        self.connection = sqlite3.connect(self.db_path)
        self.cursor = self.connection.cursor()
        self._create_table()
    def _create_table(self):
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS playlist (
                id INTEGER PRIMARY KEY,
                name TEXT,
                path TEXT
            )
        ''')
        self.connection.commit()
    def add_playlist(self,name, path):
        try:
            if path == "open":
                path = filedialog.askopenfilename(title="Chọn file")
            self.cursor.execute("INSERT INTO playlist (name, path) VALUES (?, ?)", (name, path))
            self.connection.commit()
            print("ADD SONG SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("ADD SONG UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def edit_playlist(self,playlist_id, name, path):
        try:
            playlist_id = int(playlist_id)
            current_song = self.get_current_topic_and_content(playlist_id)
            if current_song:
                current_topic, current_content = current_song
                if path == "open":
                    path = filedialog.askopenfilename(title="Chọn file")
                if name.strip() == "none":
                    name = current_topic
                if path.strip() == "none":
                    path = current_content
                self.cursor.execute("UPDATE playlist SET name = ?, path = ? WHERE id = ?", (name, path, playlist_id))
                self.connection.commit()
                print("EDIT SONG SUCCESSFULLY ! 👍 👌 🎊 ✅")
            else:
                print(f"No found with ID.")
        except Exception as e:
            print(e)
            print("EDIT SONG UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def delete_playlist(self,playlist_id):
        try:
            playlist_id = int(playlist_id)
            self.cursor.execute("DELETE FROM playlist WHERE id = ?", (playlist_id,))
            self.connection.commit()
            print("DELETE SONG SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("DELETE SONG UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def get_as_table(self):
        self.cursor.execute('SELECT * FROM playlist')
        data = self.cursor.fetchall()
        table = tabulate(data, headers=["ID", "NAME", "POSITION"], tablefmt="fancy_grid")
        return table
    def get_current_topic_and_content(self, note_id):
        self.cursor.execute('SELECT name, path FROM playlist WHERE id = ?', (note_id,))
        row = self.cursor.fetchone()
        if row:
            return row
        return None, None
    def open_path(self,playlist_id):
        try:
            playlist_id = int(playlist_id)
            current_song = self.get_current_topic_and_content(playlist_id)
            if current_song:
                current_topic, path = current_song
            try:
                if os.path.exists(path):
                    os.startfile(path)
                    print(f"Opening {path}")
                else:
                    webbrowser.open(path)
                    print(f"Opening web link: {path}")
            except Exception as e:
                print(f"Error opening path: {e}")
            print("OPEN SONG SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("OPEN SONG UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def close_database(self):
        self.connection.close()

if __name__ == "__main__":
    db = MusicDatabase("music.db")
    while True:
        print(db.get_as_table())
        print("1. Open")
        print("2. Add")
        print("3. Edit")
        print("4. Delete")
        print("5. Quit")
        choice = input("Enter your choice >>> ")
        if choice == '1':
            db.open_path()
        elif choice == '2':
            db.add_playlist()
        elif choice == '3':
            db.edit_playlist()
        elif choice == '4':
            db.delete_playlist()
        elif choice == '5':
            break
        else:
            print("Invalid choice. Please try again.")
    db.close_database()
