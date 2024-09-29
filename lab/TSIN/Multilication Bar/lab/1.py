import tkinter as tk

class PopUpTimer:
    def __init__(self, root):
        self.root = root
        self.minutes = 0
        self.seconds = 0

        self.root.title("")
        self.root.overrideredirect(1)
        self.root.attributes('-topmost', True)
        self.root.configure(bg="#222121")
        screen_width = self.root.winfo_screenwidth()
        window_width = 300  # Thay đổi giá trị này thành chiều rộng thực tế của cửa sổ của bạn
        x_position = (screen_width // 2) - (window_width // 2)

        # Đặt cửa sổ ở trên cùng và giữa
        self.root.geometry(f"+{x_position}+0")

        # Cho phép di chuyển cửa sổ
        self.root.bind("<B1-Motion>", self.move_window)

        # Nhãn hiển thị thời gian
        self.label = tk.Label(self.root, text=f"{self.minutes:02d}:{self.seconds:02d}", font=("Helvetica", 20), bg="#222121", fg="#FFFF33")
        self.label.pack(side=tk.RIGHT)

        # Nút đóng cửa sổ
        self.close_button = tk.Button(self.root, text="X", command=self.root.destroy, bg="#444444", fg="#ffffff", bd=0)
        self.close_button.pack(side=tk.LEFT)

        # Đặt cửa sổ trong suốt và trên cùng
        self.root.attributes('-transparentcolor', '#222121')
        self.root.attributes('-alpha', 0.7)

        # Bắt đầu đếm thời gian
        self.update_timer()

    def update_timer(self):
        # Tăng thời gian
        self.seconds += 1
        if self.seconds == 60:
            self.minutes += 1
            self.seconds = 0

        # Cập nhật nhãn
        self.label.config(text=f"{self.minutes:02d}:{self.seconds:02d}")

        # Cập nhật mỗi giây
        self.root.after(1000, self.update_timer)

    def move_window(self, event):
        self.root.geometry(f'+{event.x_root}+{event.y_root}')

if __name__ == "__main__":
    root = tk.Tk()
    app = PopUpTimer(root)
    root.mainloop()
