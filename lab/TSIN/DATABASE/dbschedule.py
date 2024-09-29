schelink = "DATABASE/schedule.json"
import json
from tabulate import tabulate
from datetime import datetime, timedelta

class ScheduleReader:
    def __init__(self, file_path):
        self.file_path = file_path
        self.schedules = self._load_schedules()
    def _load_schedules(self):
        with open(self.file_path, 'r') as file:
            data = json.load(file)
        return list(data.keys())
    def _save_schedules(self, new_schedule):
        with open(self.file_path, 'r') as file:
            data = json.load(file)
        data[new_schedule] = {}
        with open(self.file_path, 'w') as file:
            json.dump(data, file, indent=2)
    def _delete_schedule(self, index_to_delete):
        with open(self.file_path, 'r') as file:
            data = json.load(file)

        schedule_names = list(data.keys())

        # Kiểm tra xem số thứ tự có hợp lệ không
        if 1 <= index_to_delete <= len(schedule_names):
            schedule_to_delete = schedule_names[index_to_delete - 1]
            del data[schedule_to_delete]
            with open(self.file_path, 'w') as file:
                json.dump(data, file, indent=2)
            print(f"Đã xóa schedule: {schedule_to_delete}")
        else:
            print("Số thứ tự không hợp lệ.")
    def get_all_schedules(self):
        with open(self.file_path, 'r') as file:
            data = json.load(file)
        schedule_names = list(data.keys())
        # print(schedule_names)
        for i in range(len(schedule_names)):
            print(tabulate([], headers=[schedule_names[i]], tablefmt="fancy_grid"), end="\n")
    def add_schedule(self):
        new_schedule = input("Enter new schedule (or enter 'stop')>>>")
        self._save_schedules(new_schedule)
        self.schedules = self._load_schedules()
        option = input("Do you want to continue? (y | n)>>>")
        if option.strip() == "y":
            try:
                self.add_schedule()
            except:
                self.add_schedule()
        else:
            return
    def add_schedule_new(self, new_schedule):
        try:
            self._save_schedules(new_schedule)
            self.schedules = self._load_schedules()
            print("ADD SCHEDULE SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("ADD SCHEDULE UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def delete_schedule(self):
        self.get_list_schedules()
        index_to_delete = int(input("Nhập số thứ tự của schedule cần xóa: "))
        self._delete_schedule(index_to_delete)
        self.schedules = self._load_schedules()
        option = input("Do you want to continue? (y | n)>>>")
        if option.strip() == "y":
            try:
                self.delete_schedule()
            except:
                self.delete_schedule()
        else:
            return
    def delete_schedule_new(self, index_to_delete):
        try:
            index_to_delete = int(index_to_delete)
            self._delete_schedule(index_to_delete)
            self.schedules = self._load_schedules()
            print("DELETE SCHEDULE SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("DELETE SCHEDULE UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def get_list_schedules(self):
        with open(self.file_path, 'r') as file:
            data = json.load(file)
        schedule_names = list(data.keys())
        schedule_table = [(i + 1, schedule_name) for i, schedule_name in enumerate(schedule_names)]
        print(tabulate(schedule_table, headers=["ID", "Schedules"], tablefmt="fancy_grid"))
    def _edit_schedule_name(self, index_to_edit, new_schedule_name):
        with open(self.file_path, 'r') as file:
            data = json.load(file)
        schedule_names = list(data.keys())
        if 1 <= index_to_edit <= len(schedule_names):
            schedule_to_edit = schedule_names[index_to_edit - 1]
            data[new_schedule_name] = data.pop(schedule_to_edit)
            with open(self.file_path, 'w') as file:
                json.dump(data, file, indent=2)
            print(f"Đã sửa tên schedule từ {schedule_to_edit} thành {new_schedule_name}")
        else:
            print("Số thứ tự không hợp lệ.")
    def edit_schedule_name_new(self, index_to_edit, new_schedule_name):
        try:
            index_to_edit = int(index_to_edit)
            with open(self.file_path, 'r') as file:
                data = json.load(file)
            schedule_names = list(data.keys())
            if new_schedule_name in schedule_names:
                print("New schedule name has existed!  😓 😩 😖 😰")
                return
            if 1 <= index_to_edit <= len(schedule_names):
                schedule_to_edit = schedule_names[index_to_edit - 1]
                data[new_schedule_name] = data.pop(schedule_to_edit)
                with open(self.file_path, 'w') as file:
                    json.dump(data, file, indent=2)
                self.schedules = self._load_schedules()
                print("EDIT SCHEDULE SUCCESSFULLY ! 👍 👌 🎊 ✅")
            else:
                print("ID NOT FOUND!")
        except Exception as e:
            print(e)
            print("EDIT SCHEDULE UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def edit_schedule_name(self):
        self.get_list_schedules()
        index_to_edit = int(input("Nhập số thứ tự của schedule cần sửa tên: "))
        if 1 <= index_to_edit <= len(self.schedules):
            new_name = input("Nhập tên mới: ")
            self._edit_schedule_name(index_to_edit, new_name)
            self.schedules = self._load_schedules()  # Cập nhật danh sách các schedule
        else:
            print("Số thứ tự không hợp lệ.")
        option = input("Do you want to continue? (y | n)>>>")
        if option.strip() == "y":
            try:
                self.edit_schedule_name()
            except:
                self.edit_schedule_name()
        else:
            return
    def open_schedule(self):
        self.get_list_schedules()
        index = int(input("Nhập số thứ tự của schedule để mở: "))
        with open(self.file_path, 'r') as file:
            data = json.load(file)
        schedule_names = list(data.keys())
        if 1 <= index <= len(schedule_names):
            schedule_to_edit = schedule_names[index - 1]
            print(self.file_path)
            print(f"{schedule_to_edit}")
            schedule_reader = TimetableGenerator("schedule.json",f"{schedule_to_edit}")
            schedule_reader.run()
        else:
            print("Số thứ tự không hợp lệ.")
    def open_schedule_new(self, index):
        try:
            index = int(index)
            with open(self.file_path, 'r') as file:
                data = json.load(file)
            schedule_names = list(data.keys())
            if 1 <= index <= len(schedule_names):
                schedule_to_edit = schedule_names[index - 1]
                #print(self.file_path)
                #print(f"{schedule_to_edit}")
                print("OPEN SCHEDULE SUCCESSFULLY ! 👍 👌 🎊 ✅")
                return self.file_path, f"{schedule_to_edit}"
                #schedule_reader = TimetableGenerator(self.file_path, f"{schedule_to_edit}")
                #schedule_reader.run()
            else:
                print("Invalid ID")
        except Exception as e:
            print(e)
            print("OPEN SCHEDULE UNSUCCESSFULLY ! 😓 😩 😖 😰")
            return None, None
    def display_combined_schedule(self):
        try:
            with open(self.file_path, 'r') as file:
                data = json.load(file)
            all_schedules = {day: {time: "" for time in ["Morning", "Afternoon", "Evening"]} for day in data["Study"]}
            for schedule_name, schedule_data in data.items():
                for day, day_data in schedule_data.items():
                    for time, tasks in day_data.items():
                        all_schedules[day][time] += f"{schedule_name}: {', '.join(tasks)}\n" if tasks else ""
            table = []
            for time in ["Morning", "Afternoon", "Evening"]:
                row = [time] + [all_schedules[day][time] for day in data["Study"]]
                table.append(row)
            print(tabulate(table, headers=[""] + list(data["Study"].keys()), tablefmt="fancy_grid"))
            print("OPEN COMBINED SCHEDULE SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("OPEN COMBINED SCHEDULE UNSUCCESSFULLY ! 😓 😩 😖 😰")
    '''
    def get_current_schedule_tasks(self):
        current_day = datetime.now().strftime("%A")
        current_time = self._get_current_time()
        all_tasks = {}
        with open(self.file_path, 'r') as file:
            data = json.load(file)
        for schedule_name, schedule_data in data.items():
            schedule_tasks = schedule_data.get(current_day, {}).get(current_time, [])
            print(schedule_data.get(current_day, {}))
            all_tasks[schedule_name] = schedule_tasks
        #print(all_tasks)
        #print(f"Current tasks for {current_time}, {current_day}:")
        content = ""
        for schedule_name, tasks in all_tasks.items():
            if tasks:
                content = content + f"{schedule_name}: {', '.join(tasks)}\n"
            else:
                content = content + f"{schedule_name}: No tasks\n"
        #print(content)
        headers = ["", current_day]
        table = [
            [current_time, content]
        ]
        print(tabulate(table, headers=headers, tablefmt="fancy_grid"))
    '''
    def _get_current_time(self):
        current_hour = datetime.now().hour
        if 6 <= current_hour < 12:
            return "Morning"
        elif 12 <= current_hour < 18:
            return "Afternoon"
        else:
            return "Evening"
    def current_day_tasks(self):
        try:
            current_day = datetime.now().strftime("%A")
            with open(self.file_path, 'r') as file:
                data = json.load(file)
            headers = ["", current_day]
            table = []
            for time_of_day in ["Morning", "Afternoon", "Evening"]:
                row = [time_of_day]
                rew = ""
                for schedule_name, schedule_data in data.items():
                    schedule_tasks = schedule_data.get(current_day, {}).get(time_of_day, [])
                    if schedule_tasks:
                        rew += f"{schedule_name}: {', '.join(schedule_tasks)}\n"
                    else:
                        rew += f"{schedule_name}: No tasks\n"
                row.append(rew)
                table.append(row)
            print("OPEN CURRENT SCHEDULE DAY SUCCESSFULLY ! 👍 👌 🎊 ✅")
            return tabulate(table, headers=headers, tablefmt="fancy_grid")
        except Exception as e:
            print(e)
            print("OPEN CURRENT SCHEDULE DAY UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def next_day_tasks(self):
        try:
            current_day = (datetime.now() + timedelta(days=1)).strftime("%A")
            with open(self.file_path, 'r') as file:
                data = json.load(file)

            headers = ["", current_day]
            table = []

            for time_of_day in ["Morning", "Afternoon", "Evening"]:
                row = [time_of_day]
                rew = ""
                for schedule_name, schedule_data in data.items():
                    schedule_tasks = schedule_data.get(current_day, {}).get(time_of_day, [])
                    if schedule_tasks:
                        rew += f"{schedule_name}: {', '.join(schedule_tasks)}\n"
                    else:
                        rew += f"{schedule_name}: No tasks\n"
                row.append(rew)
                table.append(row)
            print("OPEN NEXT SCHEDULE DAY SUCCESSFULLY ! 👍 👌 🎊 ✅")
            return tabulate(table, headers=headers, tablefmt="fancy_grid")
        except Exception as e:
            print(e)
            print("OPEN NEXT SCHEDULE DAY UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def run(self):
        self.get_list_schedules()
        print("0. Quit")
        print("1. Add")
        print("2. Delete")
        print("3. Edit")
        print("4. Open")
        print("5. Synthesize Schedule")
        print("6. Get tasks in current day")
        print("7. Get tasks in next day")
        choice = input("Enter your choice >>> ")
        if choice == '0':
            return
        elif choice == '1':
            self.add_schedule()
        elif choice == '2':
            self.delete_schedule()
        elif choice == "3":
            self.edit_schedule_name_new()
        elif choice == "4":
            self.open_schedule()
        elif choice == "5":
            self.display_combined_schedule()
        elif choice == "6":
            print(self.current_day_tasks())
        elif choice == "7":
            print(self.next_day_tasks())
        else:
            print("Invalid choice. Please try again.")
        try:
            self.run()

        except:
            self.run()
class TimetableGenerator:
    def __init__(self, file_path, schedule_name):
        self.file_path = file_path
        self.schedule_name = schedule_name
        self.days_of_week = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]
        self.time_of_day = ["Morning", "Afternoon", "Evening"]
        self.schedule_data = self.load_schedule_data()
    def load_schedule_data(self):
        with open(self.file_path, 'r') as file:
            return json.load(file)
    def save_schedule_data(self):
        with open(self.file_path, 'w') as file:
            json.dump(self.schedule_data, file, indent=2)
    def generate_timetable(self):
        timetable = {time: {day: "" for day in self.days_of_week} for time in self.time_of_day}

        for day in self.days_of_week:
            for time in self.time_of_day:
                classes = self.schedule_data.get(self.schedule_name, {}).get(day, {}).get(time, [])
                timetable[time][day] = "\n".join(classes)

        return timetable
    def display_timetable(self):
        timetable = self.generate_timetable()
        table = []
        for time in self.time_of_day:
            row = [time] + [timetable[time][day] for day in self.days_of_week]
            table.append(row)

        print(tabulate(table, headers=[""] + self.days_of_week, tablefmt="fancy_grid"))
    def display_choices(self, choices, header):
        print(tabulate(enumerate(choices, start=1), headers=["Number", header], tablefmt="fancy_grid"))
    def add_work(self):
        self.display_timetable()
        print("Days of the week:")
        self.display_choices(self.days_of_week, "Day")
        try:
            day_index = int(input("Enter the number corresponding to the day: "))
        except ValueError:
            print("Invalid input. Please enter valid numbers.")
            return

        self.display_timetable()
        print("\nTime of day:")
        self.display_choices(self.time_of_day, "Time")
        try:
            time_index = int(input("Enter the number corresponding to the time of day: "))
        except ValueError:
            print("Invalid input. Please enter valid numbers.")
            return

        if 1 <= day_index <= len(self.days_of_week) and 1 <= time_index <= len(self.time_of_day):
            day = self.days_of_week[day_index - 1]
            time = self.time_of_day[time_index - 1]
            print("Enter the name of the work: (or enter 'stop')>>>")
            content_lines = []
            while True:
                line = input()
                if line.lower() == "stop":
                    break
                content_lines.append(line)
            work = "\n".join(content_lines)
            self.schedule_data.setdefault(f"{self.schedule_name}", {}).setdefault(day, {}).setdefault(time, []).append(work)
            self.save_schedule_data()
            print(f"Work '{work}' added to {day} {time}.")
        else:
            print("Invalid number. Please enter a valid number for day and time.")

        option = input("Do you want to continue? (y | n)>>>")
        if option.strip() == "y":
            try:
                self.add_work()
            except:
                self.add_work()
        else:
            return
    def add_work_new(self, day_index, time_index, work):
        try:
            day_index = int(day_index)
            time_index = int(time_index)
            day = self.days_of_week[day_index - 1]
            time = self.time_of_day[time_index - 1]
            self.schedule_data.setdefault(f"{self.schedule_name}", {}).setdefault(day, {}).setdefault(time, []).append(
                work)
            self.save_schedule_data()
            print("ADD SCHEDULE WORK SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("ADD SCHEDULE WORK UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def delete_work(self):
        self.display_timetable()
        print("Days of the week:")
        self.display_choices(self.days_of_week, "Day")
        try:
            day_input = input("Enter the number ('all')>>>")
            if day_input.lower() == 'all':
                self.delete_all_works_for_day()
                return
            else:
                day_index = int(day_input)
        except ValueError:
            print("Invalid input. Please enter valid numbers or 'all'.")
            return

        self.display_timetable()
        print("\nTime of day:")
        self.display_choices(self.time_of_day, "Time")
        try:
            time_index = int(input("Enter the number corresponding to the time of day: "))
        except ValueError:
            print("Invalid input. Please enter valid numbers.")
            return

        if 1 <= day_index <= len(self.days_of_week) and 1 <= time_index <= len(self.time_of_day):
            day = self.days_of_week[day_index - 1]
            time = self.time_of_day[time_index - 1]
            works = self.schedule_data.get(f"{self.schedule_name}", {}).get(day, {}).get(time, [])
            print(f"\nWorks in {day} {time}:")
            self.display_choices(works, "Work")
            try:
                work_index = input("Enter the number ('all')>>>")
                if work_index.lower().strip() == 'all':
                    self.delete_all_works_in_slot(day, time)
                    return
                else:
                    work_index = int(work_index)
            except ValueError:
                print("Invalid input. Please enter a valid number or 'all'.")
                return

            if 1 <= work_index <= len(works):
                work_to_delete = works[work_index - 1]
                works.remove(work_to_delete)
                self.save_schedule_data()
                print(f"Work '{work_to_delete}' deleted from {day} {time}.")
            else:
                print("Invalid number. Please enter a valid number for the work.")
        else:
            print("Invalid number. Please enter a valid number for day and time.")

        option = input("Do you want to continue? (y | n)>>>")
        if option.strip() == "y":
            try:
                self.delete_work()
            except:
                self.delete_work()
        else:
            return
    def delete_work_new(self):
        self.display_timetable()
        print("Days of the week:")
        self.display_choices(self.days_of_week, "Day")
        try:
            day_input = input("Enter the number ('all')>>>")
            if day_input.lower() == 'all':
                self.delete_all_works_for_day()
                return
            else:
                day_index = int(day_input)
        except ValueError:
            print("Invalid input. Please enter valid numbers or 'all'.")
            return

        self.display_timetable()
        print("\nTime of day:")
        self.display_choices(self.time_of_day, "Time")
        try:
            time_index = int(input("Enter the number corresponding to the time of day: "))
        except ValueError:
            print("Invalid input. Please enter valid numbers.")
            return

        if 1 <= day_index <= len(self.days_of_week) and 1 <= time_index <= len(self.time_of_day):
            day = self.days_of_week[day_index - 1]
            time = self.time_of_day[time_index - 1]
            works = self.schedule_data.get(f"{self.schedule_name}", {}).get(day, {}).get(time, [])
            print(f"\nWorks in {day} {time}:")
            self.display_choices(works, "Work")
            try:
                work_index = input("Enter the number ('all')>>>")
                if work_index.lower().strip() == 'all':
                    self.delete_all_works_in_slot(day, time)
                    return
                else:
                    work_index = int(work_index)
            except ValueError:
                print("Invalid input. Please enter a valid number or 'all'.")
                return

            if 1 <= work_index <= len(works):
                work_to_delete = works[work_index - 1]
                works.remove(work_to_delete)
                self.save_schedule_data()
                print(f"Work '{work_to_delete}' deleted from {day} {time}.")
            else:
                print("Invalid number. Please enter a valid number for the work.")
        else:
            print("Invalid number. Please enter a valid number for day and time.")

        option = input("Do you want to continue? (y | n)>>>")
        if option.strip() == "y":
            try:
                self.delete_work()
            except:
                self.delete_work()
        else:
            return
    def delete_all_works_in_slot(self, day, time):
        try:
            works = self.schedule_data.get(f"{self.schedule_name}", {}).get(day, {}).get(time, [])
            if works:
                self.schedule_data[f"{self.schedule_name}"][day][time] = []
                self.save_schedule_data()
                print(f"DELETE ALL WORKS IN {day}:{time} SUCCESSFULLY ! 👍 👌 🎊 ✅")
            else:
                print(f"No works to delete in {day} {time}.")
                print(f"DELETE ALL WORKS IN {day}:{time} UNSUCCESSFULLY ! 😓 😩 😖 😰")
        except Exception as e:
            print(e)
            print(f"DELETE ALL WORKS IN {day}:{time} UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def delete_all_works_in_week(self):
        try:
            for day in self.days_of_week:
                for time in self.time_of_day:
                    self.delete_all_works_in_slot(day, time)
            print("DELETE ALL WORKS IN WEEK SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("DELETE ALL WORKS IN WEEK UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def delete_all_works_for_aday(self,day):
        try:
            for time in self.time_of_day:
                self.delete_all_works_in_slot(day, time)
            print("DELETE ALL WORKS IN DAY SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("DELETE ALL WORKS IN DAY UNSUCCESSFULLY ! 😓 😩 😖 😰")
    def delete_all_works_for_day(self):
        try:
            day_index = input("Enter the Day ID ('all')>>>")
            if day_index.strip() == 'all':
                self.delete_all_works_in_week()
                return
            else:
                day_index = int(day_index)
        except ValueError:
            print("Invalid input. Please enter valid numbers.")
            return

        if 1 <= day_index <= len(self.days_of_week):
            day = self.days_of_week[day_index - 1]
            for time in self.time_of_day:
                works = self.schedule_data.get(f"{self.schedule_name}", {}).get(day, {}).get(time, [])
                works.clear()
            self.save_schedule_data()
            print(f"All works deleted from {day}.")
        else:
            print("Invalid number. Please enter a valid number for the day.")
    def edit_work(self):
        self.display_timetable()
        print("Days of the week:")
        self.display_choices(self.days_of_week, "Day")
        try:
            day_index = int(input("Enter the number corresponding to the day: "))
        except ValueError:
            print("Invalid input. Please enter valid numbers.")
            return

        self.display_timetable()
        print("\nTime of day:")
        self.display_choices(self.time_of_day, "Time")
        try:
            time_index = int(input("Enter the number corresponding to the time of day: "))
        except ValueError:
            print("Invalid input. Please enter valid numbers.")
            return

        if 1 <= day_index <= len(self.days_of_week) and 1 <= time_index <= len(self.time_of_day):
            day = self.days_of_week[day_index - 1]
            time = self.time_of_day[time_index - 1]
            works = self.schedule_data.get(f"{self.schedule_name}", {}).get(day, {}).get(time, [])
            print(f"\nWorks in {day} {time}:")
            self.display_choices(works, "Work")
            try:
                work_index = int(input("Enter the number corresponding to the work to edit: "))
            except ValueError:
                print("Invalid input. Please enter a valid number.")
                return
            if 1 <= work_index <= len(works):
                work_to_edit = works[work_index - 1]
                new_work = input(f"Enter the new name for the work '{work_to_edit}': ")
                works[work_index - 1] = new_work
                self.save_schedule_data()
                print(f"Work '{work_to_edit}' edited to '{new_work}' in {day} {time}.")
            else:
                print("Invalid number. Please enter a valid number for the work.")
        else:
            print("Invalid number. Please enter a valid number for day and time.")

        option = input("Do you want to continue? (y | n)>>>")
        if option.strip() == "y":
            try:
                self.edit_work()
            except:
                self.edit_work()
        else:
            return
    def edit_work_new(self, work_index, works, new_work):
        try:
            works[work_index - 1] = new_work
            self.save_schedule_data()
            print("EDIT SCHEDULE WORK SUCCESSFULLY ! 👍 👌 🎊 ✅")
        except Exception as e:
            print(e)
            print("EDIT SCHEDULE WORK UNSUCCESSFULLY ! 😓 😩 😖 😰")

    def run(self):
        self.display_timetable()
        print("0. Quit")
        print("1. Add")
        print("2. Delete")
        print("3. Edit")
        choice = input("Enter your choice >>> ")
        if choice == '0':
            return
        elif choice == '1':
            self.add_work()
        elif choice == '2':
            self.delete_work()
        elif choice == "3":
            self.edit_work()
        else:
            print("Invalid choice. Please try again.")
        try:
            self.run()
        except:
            self.run()
if __name__ == "__main__":
    #TimetableGenerator('schedule.json')
    schedule_reader = ScheduleReader("schedule.json")
    #schedule_reader.run()
    #schedule_reader = TimetableGenerator("schedule.json", f"Study")
    schedule_reader.run()


