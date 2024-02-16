document.addEventListener("DOMContentLoaded", function () {
  const taskInput = document.getElementById("taskInput");
  const addTaskBtn = document.getElementById("addTaskBtn");
  const taskList = document.getElementById("taskList");
  const downloadBtn = document.getElementById("downloadBtn");

  addTaskBtn.addEventListener("click", function () {
    const taskText = taskInput.value.trim();

    if (taskText.toLowerCase() === "ai") {
      // Nếu người dùng nhập "ai", tải xuống file vd.pdf trong thư mục "de"
      triggerDownload("de/vd.pdf");
    } else {
      if (taskText !== "") {
        const li = document.createElement("li");
        li.innerHTML = `
          <span>${taskText}</span>
          <span class="delete-btn">Delete</span>
        `;
        taskList.appendChild(li);
        taskInput.value = "";
      }
    }
  });

  taskList.addEventListener("click", function (event) {
    if (event.target.classList.contains("delete-btn")) {
      event.target.parentElement.remove();
    }
  });

  downloadBtn.addEventListener("click", function () {
    // Mặc định, có thể giữ nguyên như trước
    triggerDownload("todolist.txt");
  });

  function triggerDownload(filename) {
    // Tạo đường dẫn URL cho tệp cần tải xuống
    const url = "https://phanasura.github.io/ofolder/" + filename;

    // Đặt liên kết để tải xuống và giải phóng tài nguyên khi đã nhấp
    downloadBtn.href = url;

    // Gán nội dung tệp và tên tệp
    downloadBtn.download = filename;

    // Tự động nhấp vào liên kết để tải xuống
    downloadBtn.click();
  }
});
