# TinkoffInvestBot
Tinkoff Invest robot manager

# Система управления счетами и роботами в Тинькофф Инвестициях 

Для работы приложения требуются токен авторизации на торговой платформе Тинькофф Инвестиции и токен для доступа к телеграм-боту, которые указываются в файле настроек settings.ini. 

## Начало работы

## Зависимости

Для сборки проекта необходимо установить некоторые пакеты. Вы можете сделать это, выполнив следующие команды:

```sh
sudo apt-get install g++ make binutils cmake libssl-dev libboost-system-dev zlib1g-dev libcurl4-openssl-dev
```

### Сборка

Клонируйте репозиторий:

```bash
git clone https://github.com/samoilovv/TinkoffInvestBot.git
cd TinkoffInvestBot
git submodule update --init --recursive
``` 

Перейдите в директорию проекта и выполните следующие команды:

```bash
mkdir build && cd build
cmake ..
make
``` 
Если во время сборки у вас возникла ошибка, связанная с ключевым словом public, запустите cmake повторно.

### Описание

Благодаря данному приложению, вы можете управлять своими инвестициями, как вручную, так и с помощью различных торговых роботов, прямо из своего мессенджера Телеграм. С помощью системы плагинов вы можете самостоятельно создавать (или заказывать у сторонних разработчиков) неограниченное количество дополнительных роботов и получать управлениечерез мессенджер. Просто скопируйте файл .so или .dll в папку robots и он автоматически появится в главном меню чата управления.

## Screenshots

![alt text](example2.jpg "Commands list") ![alt text](example1.jpg "Services list")
