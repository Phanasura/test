document.addEventListener("DOMContentLoaded", function () {
    const taskInput = document.getElementById("taskInput");
    const addTaskBtn = document.getElementById("addTaskBtn");
    const taskList = document.getElementById("taskList");
  
    addTaskBtn.addEventListener("click", function () {
      const taskText = taskInput.value.trim();
      if (taskText !== "") {
        const li = document.createElement("li");
        li.innerHTML = `
          <span>${taskText}</span>
          <span class="delete-btn">Delete</span>
        `;
        taskList.appendChild(li);
        taskInput.value = "";
      }
    });
  
    taskList.addEventListener("click", function (event) {
      if (event.target.classList.contains("delete-btn")) {
        event.target.parentElement.remove();
      }
    });
  });
  