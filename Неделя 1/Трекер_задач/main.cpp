#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;



// Перечислимый тип для статуса задачи
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
    map<string, TasksInfo> data;
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const
  {
      return data.at(person);
  }

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person)
  {
      data[person][TaskStatus ::NEW]++;
  }

    TasksInfo person_update, updated_tasks, untouched_tasks;
  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo&, TasksInfo&> PerformPersonTasks(
      const string& person, int task_count)
  {
      person_update = data.at(person);
      updated_tasks = {};
      untouched_tasks = {};
      int i = 0;
      bool fl = 0;
      for (auto j : data.at(person)) {
          fl = (i == task_count);
          if (fl)
              break;
          int cur = j.second;
          for (int k = 0; k < cur; ++k) {
              switch (j.first)
              {
                  case TaskStatus ::NEW:
                  {
                      person_update[TaskStatus::NEW]--;//если ноль, я храню в словаре :(
                      Check_Zero(person_update);
                      person_update[TaskStatus::IN_PROGRESS]++;
                      updated_tasks[TaskStatus::IN_PROGRESS]++;
                      untouched_tasks[TaskStatus::NEW] = data.at(person)[TaskStatus ::NEW] - updated_tasks[TaskStatus::IN_PROGRESS];
                      i++;
                      fl = (i == task_count);
                      break;
                  }
                  case TaskStatus ::IN_PROGRESS:
                  {
                      person_update[TaskStatus::IN_PROGRESS]--;//если ноль, я храню в словаре :(
                      Check_Zero(person_update);
                      person_update[TaskStatus::TESTING]++;
                      i++;
                      updated_tasks[TaskStatus::TESTING]++;
                      untouched_tasks[TaskStatus::IN_PROGRESS] = data.at(person)[TaskStatus ::IN_PROGRESS] - updated_tasks[TaskStatus::TESTING];
                      fl = (i == task_count);
                      break;
                  }
                  case TaskStatus ::TESTING:
                  {
                      person_update[TaskStatus::TESTING]--;//если ноль, я храню в словаре :(
                      Check_Zero(person_update);
                      person_update[TaskStatus::DONE]++;
                      i++;
                      updated_tasks[TaskStatus::DONE]++;
                      untouched_tasks[TaskStatus::TESTING] = data.at(person)[TaskStatus ::TESTING] - updated_tasks[TaskStatus::DONE];
                      fl = (i == task_count);
                      break;
                  }
                  case TaskStatus ::DONE:
                  {
                      fl = 1;
                      break;
                  }
              }
              if (fl)
                  break;
          }
      }
      data.at(person) = person_update;
      return tie(updated_tasks,untouched_tasks);
  };

    // чтобы не хранить в словаре 0 заданий!
    void Check_Zero(TasksInfo& inf)
    {
        for (auto& i : inf)
        {
            if (i.second == 0)
                inf.erase(i.first);
        }
    }
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



/*
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
*/

/*
    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    TasksInfo updated_tasks, untouched_tasks;
    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Alice", 5);
    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Alice", 5);
    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Alice", 1);
    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Alice", 2);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Alice", 4);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));


    return 0;
}
*/


int main()
{
    TeamTasks tasks;
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ilia");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ilia", 3);

    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    return 0;
}