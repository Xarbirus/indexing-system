# indexing-system
Система для индексации текстовых файлов. Создана в рамках эксперимента. На данный момент система состоит из 2 частей:
- сервер на C++, строит обратный индекс из токена в файлы, где он встречается
- клиент на Python, способный запускать индексацию файлов на сервере, а также получать информацию о токенах

Клиент и сервер могут быть запущены как на Windows, так и на Linux.
____
#### Некоторые ограничения системы
- токеном считается непрерывная последовательность цифр, букв и символа_нижнего_подчеркивания (letters, digits and underscores)
- разделителями являются символы в кодах ascii: 0x00-0x1F, 0x20, 0x7F, а также
```\|/.,:;?!"()[]{}*#$%&'+-<=>@№^`~```
- поиск токена - регистрозависимый
- получение списка файлов - по полному вхождению слова, префикс для поиска не используется
- для индексации принимаются только полные пути к директориям или пути, начинающиеся с `~` (в таком случае ожидается, что в системе задана переменная среды `HOME` или `USERPROFILE`)
- индекс строится только по файлам, у которых есть расширение
____
#### Технические особенности реализации
- в качестве транспорта между клиентом и сервером выбран [`gRPC`](https://grpc.io/)
- для работы с индексом используется [`boost::symbols`](https://www.boost.org/doc/libs/1_80_0/libs/spirit/doc/html/spirit/qi/reference/string/symbols.html), где в качестве системы хранения выбрана [`boost::tst_map`](https://www.boost.org/doc/libs/1_80_0/boost/spirit/home/qi/string/tst_map.hpp)(за лучшую скорость поиска при большем расходе памяти)
- для хранения имен файлов директории используется [`boost::bimap`](https://www.boost.org/doc/libs/1_80_0/libs/bimap/doc/html/index.html)

## Сборка проекта
Для того, чтобы собрать проект на рабочей машине, Вам понадобятся:
- Python (для развертывания `conan`, `pyinstaller`, `grpcio`), все требования к нему находятся в `./requirements.txt`
- Cmake
- ninja, при сборке скриптами, или make/nmake
- компилятор с поддержкой c++20 (проверено на `g++11.3` и `msvc19.29.30147` из VS16.11)

Для сборки различных частей проекта можно воспользоваться подготовленными [скриптами](https://github.com/Xarbirus/indexing-system/tree/master/build):
- build-server - сборка серверой части проекта
- build-python-client - сборка клиентской части проекта
- generate-python-grpc - перегенерация транспорта для клиента

При сборке серверной части в скрипт потребуется передать 2 обязательных аргумента (имя профиля conan и тип билда) и один опциональный (запускать unit тесты или нет).
____
При сборке серверной части на Windows аргументы позиционные:

build-server.bat \[conan_profile\] \[build_type: debug, release, relwithdebinfo\] \[tests (optional): 0, 1\].

Например `build-server.bat release release 1`.

:heavy_exclamation_mark: **Важное**

Если нужно собрать проект компилятором от VS, то в cmd сначала нужно запустить `vcvarsall.bat` с указанием требующихся параметров (архитектура, платформа, прочее), а далее в рамках той же сессии - build-server.bat. Обычно этот скрипт находится по пути:

C:\\Program Files (x86)\\Microsoft Visual Studio\\**используемая_vs**\\VC\\Auxiliary\\Build\\
____
При сборке серверной части на Linux аргументы именованные и передаются по следующим ключам:

build-server.sh \[-t|--tests\] \[-c|--conan_profile arg\] \[-b|--build_type debug|release|relwithdebinfo\] \[-h|--help\].

Например `build-server.sh -t -c release -b release`.

## Использование системы
На данный клиентская и серверая части системы поддерживают различные наборы команд.

Для серверой части актуальны:
- help - список доступных команд иинформация о конкретной команде
- index - построение индекса для переданного корня
- roots - список всех проиндексированных корней
- remove - удаление указанного корня из системы
- clear - удаление всех корней
- quit - остановка сервера и выход

Для клиентской части актуальны:
- help - список доступных команд иинформация о конкретной команде
- index - построение на сервере индекса для переданного корня
- roots - список всех проиндексированных корней
- get - список всех файлов, в которых встречается переданное слово (дополнительно можно указать корень для поиска)
- remove - удаление указанного корня из системы
- clear - удаление всех корней на сервере
- quit - остановка клиента и выход

Для запуска и сервера и клиента требуется передать дополнительный аргумент. Для сервера это - ip и порт, к которому будут подключаться клиенты, для клиентов - ip и порт сервера. В качестве ip может также использоваться localhost.
