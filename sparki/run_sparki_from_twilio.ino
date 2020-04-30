/*******************************************
 Drawing some text
 
 http://arcbotics.com/products/sparki/parts/lcd/
********************************************/
#include <Sparki.h>  // include the sparki library

#define BUFFER_SIZE 32

char buffer[BUFFER_SIZE];
int offset;
int millisOfLastChar;

void makeMove();
void displayCommands();
void processCommands();

void setup()
{
  memset(buffer, 0, BUFFER_SIZE);
  offset = 0;
  millisOfLastChar = 0;
  
  Serial1.begin(9600);

  sparki.clearLCD();
  sparki.println("Waiting for commands....");
  sparki.updateLCD();
}

void loop()
{
  if(Serial1.available())
  {
    int val = Serial1.read();
    char x = (char)val;
    millisOfLastChar = millis();
    if(x != '\n')  // end of command marker
    {
      if(offset < BUFFER_SIZE-1)
      {
        buffer[offset] = x;
        offset++;
      }
    }
    else
    {
      processCommands();
    }
  }

  // handle in case we didn't see the end of command marker (\n)
  if((offset > 0) && ((millis() - millisOfLastChar) > 2000))
  {
    processCommands();
  }
  
  sparki.updateLCD(); // put the drawings on the screen
}

void displayCommands()
{
    sparki.clearLCD();
    sparki.println("Commands received:");
    for(int i = 0; i < offset; i++)
    {
      if(buffer[i] == 'f')
      {
        sparki.println("  forward");
      }
      else if(buffer[i] == 'l')
      {
        sparki.println("  turn left");
      }
      else if(buffer[i] == 'r')
      {
        sparki.println("  turn right");
      }
      else if(buffer[i] == 'd')
      {
        sparki.println("  dance!");
      }
      else if(buffer[i] == 'n')
      {
        sparki.println("  simple dance");
      }
    }
    sparki.updateLCD();  
}

void makeMove()
{
  for(int i=0; i < offset; i++)
  {
    // ignore space
    if(buffer[i] == 'f' || buffer[i] == 'F')
    {
      sparki.moveForward();
      delay(1000); 
      sparki.moveStop();
    }
    else if(buffer[i] == 'b')
    {
      sparki.beep();
      sparki.moveBackward();
      delay(1000);
      sparki.moveStop();
    }
    else if (buffer[i] == 'r' || buffer[i] == 'R')
    {
      sparki.moveRight(90);
    }
    else if (buffer[i] == 'l' || buffer[i] == 'L')
    {
      sparki.moveLeft(90);
    }
    else if (buffer[i] == 's' || buffer[i] == 'S')
    {
      sparki.moveStop();
      delay(1000);
    }
    else if (buffer[i] == 'n')
    {
      // nerd dance!
      for(int i = 0; i < 4; i++)
      {
        sparki.moveForward();
        delay(300);
        sparki.beep();
        sparki.moveBackward();
        delay(300);
      }
      sparki.moveStop();
    }
    else if (buffer[i] == 'd' || buffer[i] == 'D')
    {
      // dance!  - spin right, spin left, weave back and forth
      sparki.moveRight(360);
      sparki.moveLeft(360);
      for(int i = 0; i < 4; i++)
      {
        sparki.motorRotate(MOTOR_LEFT, DIR_CCW, 100);
        sparki.motorRotate(MOTOR_RIGHT, DIR_CW, 50);
        delay(300);
        sparki.motorRotate(MOTOR_LEFT, DIR_CW, 50);
        sparki.motorRotate(MOTOR_RIGHT, DIR_CCW, 100);
      }
      sparki.moveStop();
    }
    else if (buffer[i] == 32)
    {
      // just skip this
    }
    else //in case it's a character sparki doesn't understand
    {
      //Serial1.print("I'm sorry, I didn't understand the command- ");
      //Serial1.println(buffer[i]); //send the character back
    }
  } 
}

void processCommands()
{
    // make sure buffer is null terminated so we can treat it like a string
    buffer[offset] = 0;
    displayCommands();
    makeMove();
    // reset ourselves so ready for next command string
    memset(buffer, 0, BUFFER_SIZE);
    offset = 0;  
}
