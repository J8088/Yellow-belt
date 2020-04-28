#include <iostream>
#include <map>
#include <tuple>
#include <vector>

using namespace std;



//Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;



class TeamTasks {
private:
    map<string, TasksInfo> tasks;
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const
  {
      return tasks.at(person);
  }

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person) {
      tasks[person][TaskStatus::NEW]++;
  }


    bool Check_count(int& count)
    {
        return (count == 0);
    }

    void Updating_actions(const TaskStatus& type, TasksInfo& updated_tasks,
                          TasksInfo& untouched_tasks, int& task_count, const int& type_count)
    {
        updated_tasks[TaskStatus (int(type) + 1)]++;
        untouched_tasks[type]--;
        if (untouched_tasks[type] == 0)
            untouched_tasks.erase(type);
        task_count--;
    }

    //Как итерировать по enum?????
    TasksInfo Update_all_tasks(TasksInfo updated_tasks, TasksInfo untouched_tasks) {
        TasksInfo result;
        for(int i=0; i< 4; i++)
        {
            TaskStatus eCurrent = (TaskStatus) i;
            result[eCurrent] = updated_tasks[eCurrent] + untouched_tasks[eCurrent];
            if (result[eCurrent] == 0)
                result.erase(eCurrent);
        }
        return result;
    }

  // Обновить статусы по данному количеству задач конкретного разработчика,
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count){
      bool flag = 0; // контролируем количество обновляемых задач
      // собираю информацию об изменениях сюда, и только потом применяю к исходному словарю
      TasksInfo updated_tasks, untouched_tasks = tasks[person];

      for (const auto& item : tasks[person])
      {
          TaskStatus type = item.first;
          int type_count = item.second;
          for (int i = 0; i < type_count; ++i) {
              flag = Check_count(task_count);
              if (flag)
                  break;
              switch (type) {
                  case TaskStatus::NEW:
                      Updating_actions(type, updated_tasks, untouched_tasks, task_count, type_count);
                      break;
                  case TaskStatus::IN_PROGRESS:
                      Updating_actions(type, updated_tasks, untouched_tasks, task_count, type_count);
                      break;
                  case TaskStatus::TESTING:
                      Updating_actions(type, updated_tasks, untouched_tasks, task_count, type_count);
                      break;
                  case TaskStatus::DONE:
                      break;
              }
          }
      }
      tasks[person] = Update_all_tasks(updated_tasks, untouched_tasks);
      untouched_tasks.erase(TaskStatus::DONE);
      return make_tuple(updated_tasks, untouched_tasks);
  };
};


// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}


int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}

/*int main()
{
    TeamTasks tasks;
    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    cout << "Alice's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Alice", 5);
    cout << "Alice's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Alice", 1);
    cout << "Alice's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    cout << "Alice's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Alice", 2);
    cout << "Alice's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Alice", 10);
    cout << "Alice's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Alice", 7);
    cout << "Alice's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    return 0;
}*/
