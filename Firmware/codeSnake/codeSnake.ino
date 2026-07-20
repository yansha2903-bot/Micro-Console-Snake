#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Настройки экрана
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 // Пин сброса (не используется на 4-пин экранах)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Назначение пинов для кнопок из твоей схемы
const int PIN_UP = 0; // SW1 -> D0
const int PIN_DOWN = 1; // SW2 -> D1
const int PIN_LEFT = 2; // SW3 -> D2
const int PIN_RIGHT = 3; // SW4 -> D3

// Константы игры
#define SNAKE_PIECE_SIZE 4 // Размер одного сегмента змейки в пикселях
#define MAX_SNAKE_LENGTH 100

// Направления движения
enum Direction { UP, DOWN, LEFT, RIGHT };
Direction currentDir = RIGHT;

// Структура для координат
struct Point {
int x;
int y;
};

Point snake[MAX_SNAKE_LENGTH];
int snakeLength = 3;
Point food;
int score = 0;
bool gameOver = false;

void setup() {
// Инициализация кнопок с встроенной подтяжкой INPUT_PULLUP
pinMode(PIN_UP, INPUT_PULLUP);
pinMode(PIN_DOWN, INPUT_PULLUP);
pinMode(PIN_LEFT, INPUT_PULLUP);
pinMode(PIN_RIGHT, INPUT_PULLUP);

// Инициализация дисплея по адресу I2C (обычно 0x3C)
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
for(;;); // Если экран не найден, стопорим процесс
}

display.clearDisplay();
resetGame();
}

void loop() {
if (gameOver) {
checkRestart();
} else {
readInput();
updateLogic();
drawGame();
delay(150); // Скорость игры (чем меньше задержка, тем быстрее змейка)
}
}

// Считывание кнопок (учитываем, что при нажатии на пине будет LOW)
void readInput() {
if (digitalRead(PIN_UP) == LOW && currentDir != DOWN) currentDir = UP;
if (digitalRead(PIN_DOWN) == LOW && currentDir != UP) currentDir = DOWN;
if (digitalRead(PIN_LEFT) == LOW && currentDir != RIGHT) currentDir = LEFT;
if (digitalRead(PIN_RIGHT) == LOW && currentDir != LEFT) currentDir = RIGHT;
}

// Логика игры
void updateLogic() {
// Сдвигаем хвост змейки
for (int i = snakeLength - 1; i > 0; i--) {
snake[i] = snake[i - 1];
}

// Двигаем голову в зависимости от направления
switch (currentDir) {
case UP: snake[0].y -= SNAKE_PIECE_SIZE; break;
case DOWN: snake[0].y += SNAKE_PIECE_SIZE; break;
case LEFT: snake[0].x -= SNAKE_PIECE_SIZE; break;
case RIGHT: snake[0].x += SNAKE_PIECE_SIZE; break;
}

// Проверка коллизии со стенами
if (snake[0].x < 0 || snake[0].x >= SCREEN_WIDTH || snake[0].y < 0 || snake[0].y >= SCREEN_HEIGHT) {
gameOver = true;
}

// Проверка коллизии с самим собой
for (int i = 1; i < snakeLength; i++) {
if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
gameOver = true;
}
}

// Проверка: съела ли змейка еду
if (snake[0].x == food.x && snake[0].y == food.y) {
score++;
if (snakeLength < MAX_SNAKE_LENGTH) {
snakeLength++;
}
spawnFood();
}
}

// Отрисовка кадра
void drawGame() {
display.clearDisplay();

// Рисуем рамку игрового поля
display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);

// Рисуем змейку
for (int i = 0; i < snakeLength; i++) {
display.fillRect(snake[i].x, snake[i].y, SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, SSD1306_WHITE);
}

// Рисуем еду
display.fillRect(food.x, food.y, SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, SSD1306_WHITE);

display.display();
}

// Спавн еды в случайном месте, выровненном по сетке змейки
void spawnFood() {
int cols = SCREEN_WIDTH / SNAKE_PIECE_SIZE;
int rows = SCREEN_HEIGHT / SNAKE_PIECE_SIZE;

// Оставляем отступы от краев, чтобы еда не спавнилась прямо в рамке
food.x = random(1, cols - 1) * SNAKE_PIECE_SIZE;
food.y = random(1, rows - 1) * SNAKE_PIECE_SIZE;
}

// Экран Game Over и перезапуск
void checkRestart() {
display.clearDisplay();
display.setTextSize(2);
display.setTextColor(SSD1306_WHITE);
display.setCursor(10, 15);
display.print("GAME OVER");

display.setTextSize(1);
display.setCursor(25, 45);
display.print("Press ANY button");
display.display();

// Если нажата любая кнопка — перезапускаем игру
if (digitalRead(PIN_UP) == LOW || digitalRead(PIN_DOWN) == LOW ||
digitalRead(PIN_LEFT) == LOW || digitalRead(PIN_RIGHT) == LOW) {
resetGame();
delay(300); // Защита от дребезга при перезапуске
}
}

// Сброс параметров до начальных
void resetGame() {
snakeLength = 3;
score = 0;
gameOver = false;
currentDir = RIGHT;

// Стартовая позиция змейки по центру экрана
int startX = (SCREEN_WIDTH / 2) / SNAKE_PIECE_SIZE * SNAKE_PIECE_SIZE;
int startY = (SCREEN_HEIGHT / 2) / SNAKE_PIECE_SIZE * SNAKE_PIECE_SIZE;

for (int i = 0; i < snakeLength; i++) {
snake[i].x = startX - (i * SNAKE_PIECE_SIZE);
snake[i].y = startY;
}

spawnFood();
}void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
