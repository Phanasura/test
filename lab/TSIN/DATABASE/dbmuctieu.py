glink = 'DATABASE/goals.json'
import json
from tabulate import tabulate

class GoalsDatabase:
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
                    if "(<(san)>)" in link_info:
                        name, link = link_info.split("(<(san)>)")
                    else:
                        name = link_info
                    row.append(name)
                else:
                    row.append("")
            rows.append(row)
        return tabulate(rows, headers=headers, tablefmt="fancy_grid")
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
            group_name = self.column_names[column_index]
            group_headers = ["ID", group_name, "Link"]
            group_rows = [[i + 1, link.split('(<(san)>)')[0], link.split('(<(san)>)')[1][:34]+"..."] for i, link in
                          enumerate(self.groups[group_name])]
            print(tabulate(group_rows, headers=group_headers, tablefmt="fancy_grid"))
            return True
        except Exception as e:
            print(e)
            return False
    def add_goal(self):
        if not self.column_names:
            print("No data.")
            return
        headers = ["ID", "Group"]
        rows = [[i + 1, column_name] for i, column_name in enumerate(self.column_names)]
        print(tabulate(rows, headers=headers, tablefmt="fancy_grid"))
        try:
            column_index = input("Choose your column ID to add (q=quit) >>>")
            if column_index == "q":
                return
            column_index = int(column_index) - 1
            if 0 <= column_index < len(self.column_names):
                group_name = self.column_names[column_index]
                group_headers = [group_name]
                group_rows = [[i + 1, link.replace("(<(san)>)", "  -  ")] for i, link in
                              enumerate(self.groups[group_name])]
                print(tabulate(group_rows, headers=group_headers, tablefmt="fancy_grid"))

                position = input("Enter the position to add the link (q=quit) >>>")
                try:
                    position = int(position)
                except ValueError:
                    print("Invalid position. Please enter an integer.")
                    return
                if position < 1 or position > len(self.groups[group_name]) + 1:
                    print("Invalid position. Position must be between 1 and the current number of links + 1.")
                    return
                name = input("Enter name (q=quit) >>>").strip()
                if name == "q":
                    return
                link = input("Enter note (q=quit) >>>").strip()
                if link == "q":
                    return
                link = f"{name}(<(san)>){link}"
                self.groups[group_name].insert(position - 1, link)
                for i, link_info in enumerate(self.groups[group_name]):
                    if "(<(san)>)" in link_info:
                        name, link = link_info.split("(<(san)>)")
                    else:
                        name = link_info
                    self.groups[group_name][i] = f"{name}(<(san)>)({link})"

                print(f"Link was added to position {position} in the group.")
                self.save_data()
            else:
                print("Invalid ID.")
        except ValueError:
            print("Please enter an integer.")
        next_option = input("Do you want to continue add? ( y | n ) >>>")
        if next_option == "y":
            try:
                self.add_goal()
            except:
                self.add_goal()
        else:
            return
    def add_goal_new(self, column_index, position, name, link):
        try:
            column_index = int(column_index) - 1
            if 0 <= column_index < len(self.column_names):
                group_name = self.column_names[column_index]
                try:
                    position = int(position)
                except ValueError:
                    print("Invalid position. Please enter an integer.")
                    return
                if position < 1 or position > len(self.groups[group_name]) + 1:
                    print("Invalid position. Position must be between 1 and the current number of links + 1.")
                    return
                link = f"{name}(<(san)>){link}"
                self.groups[group_name].insert(position - 1, link)
                for i, link_info in enumerate(self.groups[group_name]):
                    if "(<(san)>)" in link_info:
                        name, link = link_info.split("(<(san)>)")
                    else:
                        name = link_info
                    self.groups[group_name][i] = f"{name}(<(san)>)({link})"
                print("ADD GOAL SUCCESSFULLY !!!  👍 👌 🎊 ✅")
                self.save_data()
            else:
                print("Invalid ID.")
        except Exception as e:
            print(e)
            print(f"ADD GOAL UNSUCCESSFULLY !!! 😓 😩 😖 😰")
    def open_col(self,column_index):
        try:
            column_index = int(column_index) - 1
            if 0 <= column_index < len(self.column_names):
                group_name = self.column_names[column_index]
                #print(group_name)
                group_headers = ["ID", group_name, "Link"]
                #print(group_headers)
                #print(self.groups[group_name])
                group_rows = [[i + 1, link.split('(<(san)>)')[0], link.split('(<(san)>)')[1][:34]+"..."] for i, link in
                              enumerate(self.groups[group_name])]
                print(tabulate(group_rows, headers=group_headers, tablefmt="fancy_grid"))
            print("OPEN COLUMN SUCCESSFULLY !!!  👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print(f"OPEN COLUMN UNSUCCESSFULLY !!! 😓 😩 😖 😰")
    def delete_goal_new(self, column_index, link_indices):
        try:
            column_index = int(column_index) - 1
            if 0 <= column_index < len(self.column_names):
                group_name = self.column_names[column_index]
                links_in_group = self.groups.get(group_name, [])
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
                print("DELETE GOAL SUCCESSFULLY !!!  👍 👌 🎊 ✅")
            else:
                print("Invalid column ID.")
        except Exception as e:
            print(e)
            print(f"DELETE GOAL UNSUCCESSFULLY !!! 😓 😩 😖 😰")
    def delete_goal(self):
        if not self.column_names:
            print("No data.")
            return

        headers = ["ID", "Group"]
        rows = [[i + 1, column_name] for i, column_name in enumerate(self.column_names)]
        print(tabulate(rows, headers=headers, tablefmt="fancy_grid"))

        try:
            column_index = input("Choose your column ID your link in (q=quit) >>> ")
            if column_index == "q":
                return

            column_index = int(column_index) - 1
            if 0 <= column_index < len(self.column_names):
                group_name = self.column_names[column_index]
                group_headers = [group_name]
                group_rows = [[i + 1, link.replace("(<(san)>)", "  -  ")] for i, link in
                              enumerate(self.groups[group_name])]
                print(tabulate(group_rows, headers=group_headers, tablefmt="fancy_grid"))
                links_in_group = self.groups.get(group_name, [])

                if not links_in_group:
                    print("No links in this group.")
                    next_option = input("Do you want to continue? ( y | n ) >>>")
                    if next_option == "y":
                        try:
                            self.delete_goal()
                        except:
                            self.delete_goal()
                    else:
                        return
                link_indices = input("Choose the link IDs to delete (comma-separated) or 'q=quit' >>> ").strip()
                if link_indices.lower() == "q":
                    return

                link_indices = [int(idx.strip()) for idx in link_indices.split(",")]
                indices_to_delete = []

                for link_index in link_indices:
                    link_index -= 1  # Convert to 0-based index
                    if 0 <= link_index < len(links_in_group):
                        indices_to_delete.append(link_index)
                    else:
                        print(f"Invalid link ID: {link_index + 1}")

                # Delete links after iterating through the list
                for i in reversed(indices_to_delete):
                    deleted_link = links_in_group.pop(i)
                    print(f"Link {i + 1} has been deleted from the group.")

            else:
                print("Invalid column ID.")
        except ValueError:
            print("Please enter an integer.")

        self.save_data()
        next_option = input("Do you want to continue? ( y | n ) >>>")
        if next_option == "y":
            try:
                self.delete_goal()
            except:
                self.delete_goal()
        else:
            return
    def edit_goal(self):
        if not self.column_names:
            print("No data.")
            return
        headers = ["ID", "Group"]
        rows = [[i + 1, column_name] for i, column_name in enumerate(self.column_names)]
        print(tabulate(rows, headers=headers, tablefmt="fancy_grid"))
        try:
            column_index = input("Choose your column ID to edit the link in (q=quit) >>> ")
            if column_index == "q":
                return
            column_index = int(column_index) - 1
            if 0 <= column_index < len(self.column_names):
                group_name = self.column_names[column_index]
                group_headers = [group_name]
                group_rows = [[i + 1, link.replace("(<(san)>)", "  -  ")] for i, link in
                              enumerate(self.groups[group_name])]
                print(tabulate(group_rows, headers=group_headers, tablefmt="fancy_grid"))
                links_in_group = self.groups.get(group_name, [])
                if not links_in_group:
                    print("No links in this group.")
                    next_option = input("Do you want to continue? ( y | n ) >>>")
                    if next_option == "y":
                        try:
                            self.edit_goal()
                        except:
                            self.edit_goal()
                    else:
                        return
                    return

                link_index = input("Choose the link ID to edit (q=quit) >>> ")
                if link_index == "q":
                    return
                link_index = int(link_index) - 1
                if 0 <= link_index < len(links_in_group):
                    #print(links_in_group[link_index])
                    old_name = ""
                    if "(<(san)>)" in links_in_group[link_index]:
                        old_name, old_link = links_in_group[link_index].split("(<(san)>)")
                    else:
                        old_link = links_in_group[link_index]
                    new_name = input("Enter new name (Enter to keep old)>>>").strip()
                    if new_name == "q":
                        return
                    if new_name == "" or new_name == None:
                        new_name = old_name
                    new_link = input("Enter the new link (Enter to keep old)>>>").strip()
                    if new_link == "q":
                        return
                    if new_link == "" or new_link == None:
                        new_link = old_link
                    new_link = f"{new_name}(<(san)>){new_link}"
                    links_in_group[link_index] = new_link
                    print(f"Link has been edited in the group.")
                    self.save_data()
                else:
                    print("Invalid link ID.")
            else:
                print("Invalid column ID.")
        except ValueError:
            print("Please enter an integer.")
        next_option = input("Do you want to continue? ( y | n ) >>>")
        if next_option == "y":
            try:
                self.edit_goal()
            except:
                self.edit_goal()
        else:
            return
    def open_goal(self, column_index,link_index):
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
                    #print(links_in_group[link_index])
                    old_name = ""
                    if "(<(san)>)" in links_in_group[link_index]:
                        old_name, old_link = links_in_group[link_index].split("(<(san)>)")
                    else:
                        old_link = links_in_group[link_index]
                    #table = tabulate([[old_link]], tablefmt="fancy_grid", headers=[old_name])
                    #print(table)
                    print(f"\n\n\nCurrent Link Name Of {old_name} :>>>\n\n")
                    print(old_link)
                    print("\n\n\n")
                    self.save_data()
                    print("OPEN GOAL SUCCESSFULLY !!!  👍 👌 🎊 ✅")
                else:
                    print("Invalid link ID.")
            else:
                print("Invalid column ID.")
        except Exception as e:
            print(e)
            print(f"OPEN GOAL UNSUCCESSFULLY !!! 😓 😩 😖 😰")
    def edit_goal_new(self, column_index,link_index,new_name,new_link):
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
                    #print(links_in_group[link_index])
                    old_name = ""
                    if "(<(san)>)" in links_in_group[link_index]:
                        old_name, old_link = links_in_group[link_index].split("(<(san)>)")
                    else:
                        old_link = links_in_group[link_index]
                    if new_name == "none":
                        new_name = old_name
                    if new_link == "none":
                        new_link = old_link
                    new_link = f"{new_name}(<(san)>){new_link}"
                    links_in_group[link_index] = new_link
                    self.save_data()
                    print("EDIT GOAL SUCCESSFULLY !!!  👍 👌 🎊 ✅")
                else:
                    print("Invalid link ID.")
            else:
                print("Invalid column ID.")
        except Exception as e:
            print(e)
            print(f"EDIT GOAL UNSUCCESSFULLY !!! 😓 😩 😖 😰")
    def choose_processing(self):
        if not self.column_names:
            print("No data.")
            return
        headers = ["ID", "Group"]
        rows = [[i + 1, column_name] for i, column_name in enumerate(self.column_names)]
        print(tabulate(rows, headers=headers, tablefmt="fancy_grid"))
        try:
            column_index = input("Choose your group ID (q=quit) >>> ")
            if column_index == "q":
                return
            column_index = int(column_index) - 1
            if 0 <= column_index < len(self.column_names):
                group_name = self.column_names[column_index]
                group_headers = [group_name]
                group_rows = [[i + 1, link.replace("(<(san)>)", "  -  ")] for i, link in
                              enumerate(self.groups[group_name])]
                print(tabulate(group_rows, headers=group_headers, tablefmt="fancy_grid"))
                links_in_group = self.groups.get(group_name, [])
                if not links_in_group:
                    print("No links in this group.")
                    next_option = input("Do you want to continue? ( y | n ) >>>")
                    if next_option == "y":
                        try:
                            self.choose_processing()
                        except:
                            self.choose_processing()
                    else:
                        return
                    return

                link_index = input("Choose the link ID (q=quit) >>>")
                if link_index == "q":
                    return
                link_index = int(link_index) - 1
                if 0 <= link_index < len(links_in_group):
                    # print(links_in_group[link_index])
                    old_name = ""
                    if "(<(san)>)" in links_in_group[link_index]:
                        old_name, old_link = links_in_group[link_index].split("(<(san)>)")
                    else:
                        old_link = links_in_group[link_index]
                    new_name = "***"+old_name+"***"
                    new_link = old_link
                    new_link = f"{new_name}(<(san)>){new_link}"
                    links_in_group[link_index] = new_link
                    print(f"Link has been in the group.")
                    self.save_data()
                else:
                    print("Invalid link ID.")
            else:
                print("Invalid column ID.")
        except ValueError:
            print("Please enter an integer.")
    def choose_processing_new(self, column_index, link_index):
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
                    # print(links_in_group[link_index])
                    old_name = ""
                    if "(<(san)>)" in links_in_group[link_index]:
                        old_name, old_link = links_in_group[link_index].split("(<(san)>)")
                    else:
                        old_link = links_in_group[link_index]
                    new_name = "***"+old_name+"***"
                    new_link = old_link
                    new_link = f"{new_name}(<(san)>){new_link}"
                    links_in_group[link_index] = new_link
                    self.save_data()
                    print("CHOOSE GOAL PROCESSING SUCCESSFULLY !!!  👍 👌 🎊 ✅")
                else:
                    print("Invalid link ID.")
            else:
                print("Invalid column ID.")
        except Exception as e:
            print(e)
            print("CHOOSE GOAL PROCESSING UNSUCCESSFULLY !!! 😓 😩 😖 😰")
    def get_goal(self):
        executing_goals = []

        for group_name, links_in_group in self.groups.items():
            for i, link_info in enumerate(links_in_group):
                if "(<(san)>)" in link_info:
                    name, link = link_info.split("(<(san)>)")
                else:
                    name = link_info
                    link = ""
                if name.startswith("***") and name.endswith("***"):
                    executing_goals.append({
                        "Group": group_name,
                        "ID": i + 1,
                        "Name": name.strip('*'),
                        "Link": link
                    })

        if executing_goals:
            headers = [ "Group", "Name", "Link"]
            rows = [[goal["Group"], goal["Name"], goal["Link"]] for goal in executing_goals]
            return tabulate(rows, headers=headers, tablefmt="fancy_grid")
        else:
            return "Không có goal đang thực thi."



if __name__ == "__main__":
    db = GoalsDatabase("goals.json")
    while True:
        #print(db.get_goal())
        print(db.display_links_table())
        print(db.open_col(1))
        print("1. Add")
        print("2. Edit")
        print("3. Delete")
        print("0. Quit")
        choice = input("Enter your choice >>> ")
        if choice == '1':
            db.open_goal(1,1)
        elif choice == '2':
            db.edit_goal()
        elif choice == '3':
            db.delete_goal()
        elif choice == '4':
            db.choose_processing()
        elif choice == '5':
            print(db.get_goal())
        elif choice == '0':
            break
        else:
            print("Invalid choice. Please try again.")
    db.save_data()

