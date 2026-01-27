
# Архитектура программы 3DViewer

В данном файле представлен состав модулей программы и их взаимодействие

### Модули программы:
```mermaid
%%{init: {'theme': 'dark', 'class': {'hideEmptyMembersBox': true}}}%%
classDiagram

 namespace View {
  class MenuWidget
  class ObjectViewWidget
 }

 Controller --> ObjectViewWidget
 Controller <-- MenuWidget
 Model <--> Controller

```

### Процесс работы программы

```mermaid
%%{init: {'theme': 'dark', 'class': {'hideEmptyMembersBox': true}}}%%
sequenceDiagram
  participant U as Пользователь
  participant V as View (UI)
  participant C as Controller
  participant M as Model

  U->>V: Нажимает "Open File"
  V->>V: Открывает QFileDialog
  V->>C: Сигнал (Открытие файла, название фала)

  C->>M: Перессылка сигнала
  M-->>M: Парсинг .obj
  M-->>C: Возврат данных (вершины, ребра)

  C->>V: Возврат данных
  V->>V: Отображение модели
  V->U: Видит модель
```
