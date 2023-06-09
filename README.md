# СИСТЕМА ПРОДАЖИ АВИАБИЛЕТОВ
Целью курсового проектирования является изучение структур данных и алгоритмов их обработки, а также получение практических навыков их использования при разработке программ.

Задача курсового проекта: разработка информационной системы для предметной области «Продажа авиабилетов», которая должна осуществлять ввод, хранение, обработку и вывод данных о пассажирах, авиарейсах и продаже, и возврате авиабилетов. 

Проект реализован на языке С++ в виде консольного приложения.

## Использовались следующие структуры и алгоритмы обработки данных:
* Хеш-таблица с закрытым хешированием с квадратичным опробованием
* Линейный двунаправленный список
* Быстрая сортировка
* АВЛ-дерево с обратным методом обхода
* Алгоритмом Боуера и Мура 

## Информационная система осуществляет следующие операции:
* регистрацию нового пассажира
* удаление данных о пассажире
* просмотр всех зарегистрированных пассажиров
* очистку данных о пассажирах
* поиск пассажира по «номеру паспорта». Результаты поиска – все сведения о найденном пассажире и номерах авиарейсов, на который он купил билет
* поиск пассажира по его ФИО. Результаты поиска – список найденных пассажиров с указанием номера паспорта и ФИО
* добавление нового авиарейса
* удаление сведений об авиарейсе
* просмотр всех авиарейсов
* очистку данных об авиарейсах
* поиск авиарейса по «номеру авиарейса». Результаты поиска – все сведения о найденном авиарейсе, а также ФИО и номера паспортов пассажиров, которые купили билет на этот авиарейс
* поиск авиарейса по фрагментам названия аэропорта прибытия *(используется алгоритм Боуера и Мура)*. Результаты поиска – список найденных авиарейсов с указанием номера авиарейса, аэропорта прибытия, даты отправления, времени отправления
* регистрацию продажи пассажиру авиабилета
* регистрацию возврата пассажиром авиабилета
