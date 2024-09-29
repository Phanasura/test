alink = "DATABASE/web_links.json"
import json
from tabulate import tabulate
import webbrowser
import os
from tkinter import filedialog
#path = filedialog.askopenfilename(title="Chọn file")
class WebLinkManager:
    def __init__(self, filename):
        self.filename = filename
        self.groups = self.load_data()
        self.column_names = list(self.groups.keys())
    def load_data(self):
        try:
            with open(self.filename, "r", encoding="utf-8") as file:
                data = json.load(file)
                #self.groups = data
                return data
        except FileNotFoundError:
            return {}
    def save_data(self):
        with open(self.filename, "w") as file:
            json.dump(self.groups, file, indent=2)
        self.column_names = list(self.groups.keys())
    def display_links_table(self):
        headers = list(self.groups.keys())
        if not headers:
            print("Không có dữ liệu để hiển thị.")
            return

        rows = []
        max_row_count = max(len(group) for group in self.groups.values())

        for i in range(max_row_count):
            row = []
            for group in headers:
                if i < len(self.groups[group]):
                    link_info = self.groups[group][i]
                    # Tách name và link bằng "(<(san)>)"
                    if "(<(san)>)" in link_info:
                        name, link = link_info.split("(<(san)>)")
                    else:
                        name = link_info
                    row.append(name)
                else:
                    row.append("")
            rows.append(row)
        print(tabulate(rows, headers=headers, tablefmt="fancy_grid"))
    def create_or_add_link(self):
        print("+-------------+-------------+")
        print("|    group    |     link    |")
        print("+-------------+-------------+")
        choice = input("Choose your option (q=quit)>>> ").lower().strip()
        if choice == "q":
            return
        if choice == 'g':
            self.create_group()
        elif choice == 'l':
            self.add_link_to_group()
        else:
            print("Invalid selection.")
        try:
            self.create_or_add_link()
        except:
            self.create_or_add_link()
    def create_group(self):
        group_name = input("Enter group name >>>")
        if group_name not in self.groups:
            self.groups[group_name] = []
            self.save_data()
            print("New group has been created successfully.")
        else:
            print("This group already exists.")
        next_option = input("Do you want to continue? ( y | n ) >>>")
        if next_option == "y":
            try:
                self.create_group()
            except:
                self.create_group()
        else:
            return
    def create_group_new(self, group_name):
        try:
            if group_name not in self.groups:
                self.groups[group_name] = []
                self.save_data()
                print("CREATE GROUP SUCCESSFULLY ! 👍 👌 🎊 ✅")
            else:
                print("This group already exists.")
        except Exception as e:
            print(e)
            print("CREATE GROUP UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def add_link_to_group(self):
        if not self.column_names:
            print("No data.")
            return
        headers = ["ID", "Group"]
        rows = [[i + 1, column_name] for i, column_name in enumerate(self.column_names)]
        print(tabulate(rows, headers=headers, tablefmt="grid"))
        try:
            column_index = input("Choose your column ID to add (q=quit) >>> ")
            if column_index == "q":
                return
            column_index = int(column_index) - 1
            if 0 <= column_index < len(self.column_names):
                group_name = self.column_names[column_index]
                name = input("Enter name (q=quit) >>>").strip()
                if name == "q":
                    return
                link = input("Enter link (q=quit) >>>").strip()
                if link == "q":
                    return
                link = f"{name}(<(san)>){link}"
                self.groups[group_name].append(link)
                print(f"Link was added to the group.")
                self.save_data()
            else:
                print("Invalid ID.")
        except ValueError:
            print("Please enter an integer.")
        next_option = input("Do you want to continue? ( y | n ) >>>")
        if next_option == "y":
            try:
                self.add_link_to_group()
            except:
                self.add_link_to_group()
        else:
            return
    def add_link_to_group_new(self,column_index, name, link):
        try:
            column_index = int(column_index) - 1
            if 0 <= column_index < len(self.column_names):
                group_name = self.column_names[column_index]
                link = f"{name}(<(san)>){link}"
                self.groups[group_name].append(link)
                self.save_data()
                print("CREATE LINK SUCCESSFULLY ! 👍 👌 🎊 ✅")
            else:
                print("Invalid ID.")
        except Exception as e:
            print(e)
            print("CREATE LINK UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def open_path(self,column_index, paths_to_open):
        try:
            if not self.column_names:
                print("NO DATA.")
                return
            column_index = int(column_index) - 1
            if 0 <= column_index < len(self.column_names):
                group_name = self.column_names[column_index]
                links_in_group = self.groups.get(group_name, [])
                link_open = []
                for j, link in enumerate(links_in_group, start=1):
                    if "(<(san)>)" in link:
                        name, link = link.split("(<(san)>)")
                    else:
                        name = ""
                    link_open.append(link)
                if paths_to_open.lower() == 'all':
                    for path in link_open:
                        try:
                            if os.path.exists(path):
                                os.startfile(path)
                                print(f"Opening {path}")
                            else:
                                webbrowser.open(path)
                                print(f"Opening web link: {path}")
                        except:
                            print(f"Error opening path. Please enter a valid ID.")
                else:
                    paths_to_open = paths_to_open.split(",")
                    for path_id in paths_to_open:
                        try:
                            path_id = int(path_id)
                            if 0 < path_id <= len(link_open):
                                path = link_open[path_id - 1]
                                if os.path.exists(path):
                                    os.startfile(path)
                                    print(f"Opening {path}")
                                else:
                                    webbrowser.open(path)
                                    print(f"Opening web link: {path}")
                            else:
                                print("Invalid ID.")
                        except ValueError:
                            print(f"Error opening path. Please enter a valid ID.")
                print("OPEN LINKS SUCCESSFULLY ! 👍 👌 🎊 ✅")
            else:
                print("Invalid ID.")
        except Exception as e:
            print(e)
            print("OPEN LINKS UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def delete_group_or_link(self):
        print("+-------------+-------------+")
        print("|    group    |     link    |")
        print("+-------------+-------------+")
        choice = input("Choose your option (q=quit)>>> ").lower().strip()
        if choice == "q":
            return
        if choice == 'g':
            self.delete_group()
        elif choice == 'l':
            self.delete_link()
        else:
            print("Invalid selection.")
        try:
            self.delete_group_or_link()
        except:
            self.delete_group_or_link()
    def delete_group(self, columns_to_delete):
        try:
            if columns_to_delete.lower() == "all":
                self.groups = {}
                print("All groups have been deleted.")
                self.save_data()
                return
            columns_to_delete = [int(idx.strip()) for idx in columns_to_delete.split(",")]
            for column_index in columns_to_delete:
                column_index -= 1
                if 0 <= column_index < len(self.column_names):
                    group_name = self.column_names[column_index]
                    del self.groups[group_name]
                else:
                    print(f"Invalid ID: {column_index + 1}")
            self.save_data()
            print("DELETE GROUP SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("DELETE GROUP UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def delete_link(self, column_index, link_indices):
        try:
            column_index = int(column_index) - 1
            if 0 <= column_index < len(self.column_names):
                group_name = self.column_names[column_index]
                links_in_group = self.groups.get(group_name, [])
                if not links_in_group:
                    print("No links in this group.")
                    return
                link_indices = [int(idx.strip()) for idx in link_indices.split(",")]
                indices_to_delete = []
                for link_index in link_indices:
                    link_index -= 1
                    if 0 <= link_index < len(links_in_group):
                        indices_to_delete.append(link_index)
                    else:
                        print(f"Invalid link ID: {link_index + 1}")
                for i in reversed(indices_to_delete):
                    deleted_link = links_in_group.pop(i)
                self.save_data()
                print("DELETE LINK SUCCESSFULLY ! 👍 👌 🎊 ✅")
            else:
                print("Invalid column ID.")
        except Exception as e:
            print(e)
            print("DELETE LINK UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def print_group(self):
        if not self.column_names:
            print("No data.")
            return
        headers = ["ID", "Group"]
        rows = [[i + 1, column_name] for i, column_name in enumerate(self.column_names)]
        print(tabulate(rows, headers=headers, tablefmt="fancy_grid"))
    def print_link(self, column_index):
        try:
            column_index = int(column_index) - 1
            if 0 <= column_index < len(self.column_names):
                group_name = self.column_names[column_index]
                links_in_group = self.groups.get(group_name, [])
                if not links_in_group:
                    print("No links in this group.")
                    return
                print(f"\nLink List in '{group_name}':")
                link_table = []
                for j, link in enumerate(links_in_group, start=1):
                    if "(<(san)>)" in link:
                        name, link = link.split("(<(san)>)")
                    else:
                        name = ""
                    link_table.append([j, name, link])
                headers = ["ID", "Name", "Link"]
                table = tabulate(link_table, headers=headers, tablefmt="fancy_grid")
                print(table)
                return True
        except Exception as e:
            print(e)
            return False
    def edit_group_or_link(self):

        choice = input("Choose your option (q=quit)>>> ").lower().strip()
        if choice == "q":
            return
        if choice == 'g':
            self.edit_group()
        elif choice == 'l':
            self.edit_link()
        else:
            print("Invalid selection.")
        try:
            self.edit_group_or_link()
        except:
            self.edit_group_or_link()
    def edit_group(self, column_index, new_group_name):
        try:
            column_index = int(column_index) - 1
            if 0 <= column_index < len(self.column_names):
                old_group_name = self.column_names[column_index]
                if new_group_name not in self.groups:
                    self.groups[new_group_name] = self.groups.pop(old_group_name)
                    self.column_names[column_index] = new_group_name
                    self.save_data()
                    print("EDIT GROUP SUCCESSFULLY ! 👍 👌 🎊 ✅")
                else:
                    print(f"Group '{new_group_name}' already exists.")
            else:
                print("Invalid ID.")
        except Exception as e:
            print(e)
            print("EDIT GROUP UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def edit_link(self, column_index, link_index, new_name, new_link):
        try:
            column_index = int(column_index) - 1
            if 0 <= column_index < len(self.column_names):
                group_name = self.column_names[column_index]
                links_in_group = self.groups.get(group_name, [])
                if not links_in_group:
                    print("No links in this group.")
                    return
                link_index = int(link_index) - 1
                if 0 <= link_index < len(links_in_group):
                    old_name = ""
                    if "(<(san)>)" in links_in_group[link_index]:
                        old_name, old_link = links_in_group[link_index].split("(<(san)>)")
                    else:
                        old_link = links_in_group[link_index]
                    if new_name.strip() == "none":
                        new_name = old_name
                    if new_link.strip() == "none":
                        new_link = old_link
                    new_link = f"{new_name}(<(san)>){new_link}"
                    links_in_group[link_index] = new_link
                    self.save_data()
                    print("EDIT LINK SUCCESSFULLY ! 👍 👌 🎊 ✅")
                else:
                    print("Invalid link ID.")
            else:
                print("Invalid column ID.")
        except Exception as e:
            print(e)
            print("EDIT LINK UNSUCCESSFULLY ! 😓 😩 😖 😰")

if __name__ == "__main__":
    web_link_manager = WebLinkManager("web_links.json")
    while True:
        web_link_manager.display_links_table()
        web_link_manager.print_group()
        web_link_manager.print_link(1)
        print("0. Quit")
        print("1. ADD")
        print("3. Delete")
        print("4. Display links table")
        print("5. Edit")
        print("6. Open path")
        choice = input("Enter your choice >>> ")
        if choice == '1':
            web_link_manager.create_or_add_link()
        #elif choice == '2':
        #    web_link_manager.add_link_to_group()
        elif choice == '3':
            web_link_manager.delete_group_or_link()
        elif choice == '4':
            web_link_manager.display_links_table()
        elif choice == '0':
            break
        elif choice == '6':
            web_link_manager.open_path()
        elif choice == '5':
            web_link_manager.edit_group_or_link()
        else:
            print("Invalid choice. Please try again.")
