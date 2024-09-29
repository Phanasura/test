ulink = "functions.db"
import os
import sqlite3
from tabulate import tabulate

class Update:
    def __init__(self, db_path):
        self.db_path = db_path
        self.connection = sqlite3.connect(self.db_path)
        self.cursor = self.connection.cursor()
        self._create_table()
    def _create_table(self):
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS functions (
                id INTEGER PRIMARY KEY,
                name TEXT,
                link TEXT,
                type TEXT
            )
        ''')
        self.connection.commit()
    def add_function(self):
        name = input().strip()
        link = input("Enter function link >>>").strip()
        f_type = input("Is it a startup file? ( y | n )>>>").strip()
        if f_type == 'y':
            f_type = "✓"
        else:
            f_type = ""
        if os.path.exists(link):
            pass
        elif os.path.exists(os.path.join("UPDATE", link)):
            link = os.path.join("UPDATE", link)
        else:
            option = input("Is it a web link? (y | n)>>>").strip()
            if option == 'y':
                pass
            else:
                return
        self.cursor.execute("INSERT INTO functions (name, link, type) VALUES (?, ?, ?)", (name, link, f_type))
        self.connection.commit()
        print("ADDED NEW FUNCTION SUCCESSFULLY")
    def add_function_new(self, name, link, f_type):
        try:
            if f_type == 'y':
                f_type = "✓"
            else:
                f_type = ""
            #if os.path.exists(link):
            #    pass
            #elif os.path.exists(os.path.join("UPDATE", link)):
            #    link = os.path.join("UPDATE", link)
            #else:
            #    return
            self.cursor.execute("INSERT INTO functions (name, link, type) VALUES (?, ?, ?)", (name, link, f_type))
            self.connection.commit()
            print("ADD SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("ADD UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def edit_function(self):
        try:
            function_id = int(input("Enter ID to edit >>> "))
        except ValueError:
            print("You must enter an ID number")
            return

        current_function = self.get_function_by_id(function_id)
        if current_function:
            current_name, current_link, current_type = current_function
            print(f"Current name: {current_name}")
            name = input("Enter new name (or press Enter to keep old name) >>> ").strip()
            print(f"Current link: {current_link}")
            link = input("Enter new link (or press Enter to keep old link) >>> ").strip()
            f_type = input("Is it a startup file? ( y | n )>>>").strip()
            if f_type == 'y':
                f_type = "✓"
            else:
                f_type = ""
            if not self._file_exists(link):
                print(f"File not found: {link}. Please make sure the file exists.")
                return

            if name == "":
                name = current_name
            if link == "":
                link = current_link

            self.cursor.execute("UPDATE functions SET name = ?, link = ?, type = ? WHERE id = ?",
                                (name, link, f_type, function_id))
            self.connection.commit()
        else:
            print(f"No function found with ID {function_id}")
    def edit_function_new(self, function_id, name, link, f_type):
        try:
            function_id = int(function_id)
            current_function = self.get_function_by_id(function_id)
            if current_function:
                current_name, current_link, current_type = current_function
                if name.strip() == 'none':
                    name = current_name
                elif link.strip() == 'none':
                    link = current_link
                if f_type == 'y':
                    f_type = "✓"
                else:
                    f_type = ""
                #if not self._file_exists(link):
                #    print(f"File not found: {link}. Please make sure the file exists.")
                #    return
                self.cursor.execute("UPDATE functions SET name = ?, link = ?, type = ? WHERE id = ?",
                                    (name, link, f_type, function_id))
                self.connection.commit()
                print("EDIT SUCCESSFULLY ! 👍 👌 🎊 ✅")
            else:
                print(f"No function found with ID {function_id}")
        except Exception as e:
            print(e)
            print("EDIT UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def delete_function(self):
        try:
            function_id = int(input("Enter ID to delete >>> "))
        except ValueError:
            print("You must enter an ID number")
            return

        self.cursor.execute("DELETE FROM functions WHERE id = ?", (function_id,))
        self.connection.commit()
        print(f"Function with ID {function_id} has been deleted.")
    def delete_function_new(self, function_id):
        try:
            function_id = int(function_id)
            self.cursor.execute("DELETE FROM functions WHERE id = ?", (function_id,))
            self.connection.commit()
            print("DELETE SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("DELETE UNSUCCESSFULLY ! 😓 😩 😖 😰")

    def display(self):
        self.cursor.execute('SELECT * FROM functions')
        data = self.cursor.fetchall()
        table = tabulate(data, headers=["ID", "Name", "Link", "Startup File"], tablefmt="fancy_grid")
        print(table)
    def get_function_by_id(self, function_id):
        self.cursor.execute('SELECT name, link, type FROM functions WHERE id = ?', (function_id,))
        row = self.cursor.fetchone()
        if row:
            return row
        return None
    def get_all_functions(self):
        self.cursor.execute('SELECT * FROM functions')
        data = self.cursor.fetchall()
        return data
    def close_database(self):
        self.connection.close()
    def _file_exists(self, file_path):
        if os.path.exists(file_path):
            return True
        else:
            return os.path.exists(os.path.join("UPDATE/", file_path))
    def open_link(self):
        try:
            function_id = int(input("Enter ID>>> "))
        except ValueError:
            print("You must enter an ID number")
            return
        current_function = self.get_function_by_id(function_id)
        if current_function:
            current_name, path, type = current_function
        try:
            os.startfile(path)
        except Exception as e:
            print(f"Error opening file: {e}")
    def open_link_new(self, function_id):
        try:
            function_id = int(function_id)
            current_function = self.get_function_by_id(function_id)
            if current_function:
                current_name, path, type = current_function
            try:
                os.startfile(path)
            except Exception as e:
                print(f"Error opening file: {e}")
            print("OPEN SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("OPEN UNSUCCESSFULLY ! 😓 😩 😖 😰")

if __name__ == "__main__":
    db = Update("functions.db")
    while True:
        db.display()
        print("1. Add Function")
        print("2. Edit Function")
        print("3. Delete Function")
        print("4. Display All Functions")
        print("5. Quit")
        choice = input("Enter your choice >>> ")
        if choice == '1':
            db.add_function()
        elif choice == '2':
            db.edit_function()
        elif choice == '3':
            db.delete_function()
        elif choice == '4':
            db.get_all_functions()
        elif choice == '5':
            db.close_database()
            break
        elif choice == '6':
            db.open_link()
            break
        else:
            print("Invalid choice. Please try again.")
