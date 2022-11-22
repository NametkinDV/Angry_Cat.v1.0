#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const float fSizeWidthField  = 1366.0F;   // Размер окна игры по ширине
const float fSizeHeigthField = 768.0F;  // Размер окна игры по высоте
const float gravity = 9.8F / 100; // Сила притяжения (в миллисикундах)

enum Direction {LEFT = 0, STANDL = 1, STANDR = 2, RIGHT = 3, JUMPL = 4, JUMPR};


class TimeGame final
{
private:
  double timeStartGame;
  double microSec;

public:

  TimeGame()
  {
    timeStartGame = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count(); // Фиксация времени при запуске
  }
  
  double timeHasPassed() // Подсчёт времени (в миллисекундах) / Ритм игры
  {
    microSec = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count(); //Получение времени(микросекунды)
    microSec -= timeStartGame;

    return microSec;
  }

  void resetTime()
  {
    timeStartGame = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
  }
};


class Cat final
{
private:
  Texture catBodyTexture;                            // Путь к текстурам тела кота
  Sprite catBody;                                    // Присвоение спрайту текстуры тела кота

  unsigned int nSizeCatX;                            // Размер текстуры тела кота по ширине
  unsigned int nSizeCatY;                            // Размер текстуры тела кота по высоте
  float fHalfSizeCatX;                               // Центр текстуры тела кота по ширине
  float fHalfSizeCatY;                               // Центр текстуры тела кота по высоте
  float fCatBodyPositionX;                           // Позиция кота по ширине
  float fCatBodyPositionY;                           // Позиция кота по высоте
  float fSpeedCatBody;                               // Скорость передвижения кота
  float fJumpCatBody;                                // Скорость прыжка кота
bool x = true;
  double dCurrentFrame = 1.5;
  short int snDirectionBodyCat;                      // Направление тела кота
  unsigned int snTextureDirectionBodyCat[6][2] // Координаты отрисовки текстуры тела кота
  {
    {76, 100}, // Бежит влево
    {0, 100}, // Стоит влево
    {0, 0}, // Стоит вправо
    {76, 0}, // Бежит вправо
    {},
    {}
  };
  
public:
  explicit Cat()
  {
    catBodyTexture.loadFromFile("./Textures.v0.0/Moves.png");
    catBody.setTexture(catBodyTexture);

    nSizeCatX = 76;
    nSizeCatY = 100;
    catBody.setTextureRect(IntRect(snTextureDirectionBodyCat[STANDR][0], snTextureDirectionBodyCat[STANDR][1], nSizeCatX, nSizeCatY));
    fHalfSizeCatX = (float)nSizeCatX / 2;
    fHalfSizeCatY = (float)nSizeCatY / 2;
    catBody.setOrigin(fHalfSizeCatX, fHalfSizeCatY);

    fCatBodyPositionX = 50;
    fCatBodyPositionY = (fSizeHeigthField - fHalfSizeCatY - 115 - 1000); // +115 от низа с учётом меню иконок
    catBody.setPosition(fCatBodyPositionX, fCatBodyPositionY);
    fSpeedCatBody = 0.05F;
    fJumpCatBody = 0.0F;
    snDirectionBodyCat = RIGHT;

    cout << "Cat's body created" << endl;
  }

  
  Sprite getCatBody()
  {
    return catBody;
  }

  
  void controlCatBody(double &t)
  {
    
    if (Keyboard::isKeyPressed(Keyboard::Left)) // Движение влево
      {
	if (x == true) { if (dCurrentFrame >= 2.5) {x = false;} dCurrentFrame += 0.0005 * t;}
	if (x == false){ if (dCurrentFrame <= 0.5) {x = true;} dCurrentFrame -= 0.0005 * t;} // Смена кадра
	cout << dCurrentFrame << endl;
	
	//if (snDirectionBodyCat != LEFT) // Текстура движения влево
	catBody.setTextureRect(IntRect((snTextureDirectionBodyCat[LEFT][0] + (nSizeCatX * (int)dCurrentFrame)), snTextureDirectionBodyCat[LEFT][1], nSizeCatX, nSizeCatY));
	snDirectionBodyCat = LEFT;
	
	if (fCatBodyPositionX - fHalfSizeCatX >= fSizeWidthField - fSizeWidthField) fCatBodyPositionX -= fSpeedCatBody * t; // Движение
	catBody.setPosition(fCatBodyPositionX, fCatBodyPositionY);
      }
    
    else if (Keyboard::isKeyPressed(Keyboard::Right)) // Движение вправо
      {
	if (x == true) { if (dCurrentFrame >= 2.5) {x = false;} dCurrentFrame += 0.0005 * t;}
	if (x == false){ if (dCurrentFrame <= 0.5) {x = true;} dCurrentFrame -= 0.0005 * t;} // Смена кадра
	cout << dCurrentFrame << endl;
	
	//if (snDirectionBodyCat != RIGHT) // Текстура движения вправо
	catBody.setTextureRect(IntRect((snTextureDirectionBodyCat[RIGHT][0] + (nSizeCatX * (int)dCurrentFrame)), snTextureDirectionBodyCat[RIGHT][1], nSizeCatX, nSizeCatY));
	snDirectionBodyCat = RIGHT;
	
	if (fCatBodyPositionX + fHalfSizeCatX <= fSizeWidthField) fCatBodyPositionX += fSpeedCatBody * t; // Движение
	catBody.setPosition(fCatBodyPositionX, fCatBodyPositionY);
      }
    
    else // Положение персонажа стоя на месте
      {
	dCurrentFrame = 1.5;
	
	if (snDirectionBodyCat == LEFT)
	  {
	    catBody.setTextureRect(IntRect(snTextureDirectionBodyCat[STANDL][0], snTextureDirectionBodyCat[STANDL][1], nSizeCatX, nSizeCatY));
	    snDirectionBodyCat = STANDL;
	  }
	if (snDirectionBodyCat == RIGHT)
	  {
	    catBody.setTextureRect(IntRect(snTextureDirectionBodyCat[STANDR][0], snTextureDirectionBodyCat[STANDR][1], nSizeCatX, nSizeCatY));
	    snDirectionBodyCat = STANDR;
	  }
      }
    
    if (Keyboard::isKeyPressed(Keyboard::Up) && fCatBodyPositionY == (fSizeHeigthField - fHalfSizeCatY - 115)) // Прыжок
      {
	if (snDirectionBodyCat == LEFT || snDirectionBodyCat == STANDL) {snDirectionBodyCat = JUMPL; }
	else if (snDirectionBodyCat == RIGHT || snDirectionBodyCat == STANDR) { snDirectionBodyCat = JUMPR; }
	fJumpCatBody = 7.7F;
      }      
  }


  void jumpAndGravity(double &t)
  {   
    if (fJumpCatBody > 0.0F)
      {
	fCatBodyPositionY -= fJumpCatBody * (t / 45);
	fJumpCatBody -= gravity * (t / 45);
	cout << "Прыгаем" << fJumpCatBody << "-";
      }
    
    else if (fJumpCatBody <= 0.0F && fCatBodyPositionY < (fSizeHeigthField - fHalfSizeCatY - 115))
      {
	fCatBodyPositionY -= fJumpCatBody * (t / 45);
	fJumpCatBody -= gravity * (t / 45);
	cout << "Тянет вниз";
      }

    else
      {
      fJumpCatBody = 0.0F;
      fCatBodyPositionY = (fSizeHeigthField - fHalfSizeCatY - 115);
      }
    
    catBody.setPosition(fCatBodyPositionX, fCatBodyPositionY);
  }
};


int main()
{
  // Объекты игры
  Event event;
  TimeGame classTime;
  double time;
  Cat CatBody;
 
  RenderWindow window(VideoMode(fSizeWidthField, fSizeHeigthField), "Angry Cat!");

  // Управление
  while (window.isOpen())
    {
      while (window.pollEvent(event))
	{
	  if (event.type == Event::Closed) { window.close(); }
	}
      
      time = classTime.timeHasPassed();
      classTime.resetTime();
      time /= 80;

      CatBody.controlCatBody(time);
      CatBody.jumpAndGravity(time);
	
	  //Отрисовка
      window.clear(Color::White);
      window.draw(CatBody.getCatBody());
      window.display();
    }

  return 0;
}
