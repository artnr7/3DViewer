Привет. В Qt есть довольно устоявшиеся соглашения.

**Сигналы** обычно называют:

* как **событие, которое уже произошло**
* без префиксов `sig_`, `signal_` и без `on_`

Примеры:

* `clicked()`
* `textChanged(const QString &text)`
* `valueChanged(int value)`
* `connectionLost()`

То есть сигнал обычно звучит как факт: **“значение изменилось”**, **“кнопка нажата”**.

**Слоты** обычно называют:

* как **действие**, которое нужно выполнить
* глаголом
* без специальных префиксов вроде `slot_`

Примеры:

* `setText(const QString &text)`
* `updateStatus()`
* `loadFile()`
* `resetCounter()`

То есть слот — это обычно команда: **“обновить”**, **“загрузить”**, **“установить”**.

Есть еще частый шаблон для **приватных слотов, связанных с UI-событиями**:

* `on_<objectName>_<signalName>()`

Пример:

* `on_pushButton_clicked()`
* `on_lineEdit_textChanged()`

Но это не общее правило именования всех слотов, а именно стиль, который долго использовался с Designer и автоподключением (`connectSlotsByName`).

Итого:

* **сигнал**: имя-событие → `dataReady()`, `finished()`, `errorOccurred()`
* **слот**: имя-действие → `startProcessing()`, `handleError()`, `setValue()`

Практически полезное правило:

* если функция **сообщает, что что-то случилось** → это стиль сигнала
* если функция **что-то делает в ответ** → это стиль слота

Неплохо также придерживаться таких мелочей:

* использовать **camelCase**
* для булевых состояний в сигналах удобно: `enabledChanged(bool enabled)`
* для “изменилось” почти стандартный паттерн: `<property>Changed(...)`

Примеры хороших имен:

* `nameChanged(const QString &name)`
* `downloadFinished()`
* `downloadFailed(const QString &reason)`
* `startDownload()`
* `cancelDownload()`
* `handleNetworkError(QNetworkReply::NetworkError error)`

Примеры неудачных:

* `sigNameChanged()`
* `slotButtonPressed()`
* `doWhenClicked()`
* `someSignal1()`

Если хочешь, могу сразу показать **небольшой пример класса Qt с правильно названными сигналами и слотами**.

