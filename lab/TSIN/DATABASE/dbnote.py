nlink = 'DATABASE/notes.db'
import sqlite3
from tabulate import tabulate

class NoteDatabase:
    def __init__(self, db_name):
        self.conn = sqlite3.connect(db_name)
        self.cursor = self.conn.cursor()
        self.create_table()
    def create_table(self):
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS notes (
                id INTEGER PRIMARY KEY,
                topic TEXT,
                content TEXT
            )
        ''')
        self.conn.commit()
    def add_note(self):
        topic = input("Enter note name >>>")
        print("Enter note content(Type 'stop' on a line to finish) >>>")
        content_lines = []
        while True:
            line = input()
            if line.lower() == "stop":
                break
            content_lines.append(line)
        content = "\n".join(content_lines)
        self.cursor.execute('INSERT INTO notes (topic, content) VALUES (?, ?)', (topic, content))
        self.conn.commit()
        print(f"Note '{topic}' has been added to the database.")
        #print(self.get_notes_as_table())
    def add_note_new(self, note_name, content):
        try:
            self.cursor.execute('INSERT INTO notes (topic, content) VALUES (?, ?)', (note_name, content))
            self.conn.commit()
            print("ADD NOTE SUCCESSFULLY !!!  👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print(f"ADD NOTE UNSUCCESSFULLY !!! 😓 😩 😖 😰")
    def get_notes_as_table(self):
        self.cursor.execute('SELECT * FROM notes')
        notes = self.cursor.fetchall()
        for i, note in enumerate(notes):
            notes[i] = (note[0], note[1][:25]+"...", note[2][:25]+"...")
        table = tabulate(notes, headers=["ID", "NAME", "CONTENT"], tablefmt="fancy_grid")
        return table

    def get_notes(self):
        self.cursor.execute('SELECT * FROM notes')
        notes = self.cursor.fetchall()
        return notes
    def delete_note(self):
        try:
            note_id = int(input("Enter the ID you want to delete('all' or 'q')>>>"))
        except:
            print("You must enter an ID number")
            return
        if note_id == "q":
            return
        self.cursor.execute('DELETE FROM notes WHERE id = ?', (note_id,))
        self.conn.commit()
        print(f"Note with ID has been deleted.")
        #print(self.get_notes_as_table())
    def delete_note_new(self,note_id):
        try:
            note_id = int(note_id)
            self.cursor.execute('DELETE FROM notes WHERE id = ?', (note_id,))
            self.conn.commit()
            print("DELETE NOTE SUCCESSFULLY !!!  👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print(f"DELETE NOTE UNSUCCESSFULLY !!! 😓 😩 😖 😰")
    def edit_note(self):
        try:
            note_id = int(input("Enter the ID you want to edit >>>"))
        except:
            print("You must enter an ID number")
            return
        current_note = self.get_current_topic_and_content(note_id)
        if current_note:
            current_topic, current_content = current_note
            print(f"Current name: {current_topic}")
            new_topic = input("Enter new name (or enter to keep old name) >>>")
            print(f"Current content: {current_content}")
            print("Enter new content (or enter stop) >>>")
            content_lines = []
            while True:
                line = input()
                if line.lower() == "stop":
                    break
                content_lines.append(line)
            new_content = "\n".join(content_lines)
            #print(current_topic)
            #print(current_content)
            #print(new_topic)
            #print(new_content)
            if new_topic.strip() == "":
                new_topic = current_topic
            if new_content.strip() == "":
                new_content = current_content

            self.cursor.execute('UPDATE notes SET topic = ?, content = ? WHERE id = ?',
                                (new_topic, new_content, note_id))
            self.conn.commit()
            print(f"Note with ID '{note_id}' has been edited.")
        else:
            print(f"No task found with ID.")
        #print(self.get_notes_as_table())
    def edit_note_new(self, note_id, new_topic, new_content):
        try:
            note_id=int(note_id)
            current_note = self.get_current_topic_and_content(note_id)
            if current_note:
                current_topic, current_content = current_note
                if new_topic.strip() == "none":
                    new_topic = current_topic
                if new_content.strip() == "none":
                    new_content = current_content
                self.cursor.execute('UPDATE notes SET topic = ?, content = ? WHERE id = ?',
                                    (new_topic, new_content, note_id))
                self.conn.commit()
                print("EDIT NOTE SUCCESSFULLY !!!  👍 👌 🎊 ✅")
            else:
                print(f"No task found with ID.")
            # print(self.get_notes_as_table())
        except Exception as e:
            print(e)
            print(f"EDIT NOTE UNSUCCESSFULLY !!! 😓 😩 😖 😰")
    def get_current_topic_and_content(self, note_id):
        self.cursor.execute('SELECT topic, content FROM notes WHERE id = ?', (note_id,))
        row = self.cursor.fetchone()
        if row:
            return row
        return None, None
    def open_note(self,note_id):
        try:
            note_id = int(note_id)
            current_note = self.get_current_topic_and_content(note_id)
            if current_note:
                current_topic, current_content = current_note
                print("\n\n\nCurrent name: >>>")
                print(current_topic)
                print("\n\n\nCurrent Note: >>>")
                print(current_content)
                print("\n\n\nOPEN NOTE SUCCESSFULLY !!!  👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print(f"OPEN NOTE UNSUCCESSFULLY !!! 😓 😩 😖 😰")
    def close_database(self):
        self.conn.close()

if __name__ == "__main__":
    db = NoteDatabase('notes.db')
    while True:
        print(db.get_notes_as_table())
        print("1. Add")
        print("2. Edit")
        print("3. Delete")
        print("4. Open")
        print("5. Quit")
        choice = input("Enter your choice >>> ")
        if choice == '1':
            db.add_note()
        elif choice == '4':
            db.open_note()
        elif choice == '2':
            db.edit_note()
        elif choice == '3':
            db.delete_note()
        elif choice == '0':
            print(db.get_notes_as_table())
        elif choice == '5':
            break
        else:
            print("Invalid choice. Please try again.")
    db.close_database()
