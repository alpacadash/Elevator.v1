#include "Elevator.h"
#include "Panel.h"
#include "Building.h"

#include <iostream>
#include <vector>
using namespace std;

#include <cstdlib>

Elevator::Elevator(unsigned int capacity, int speed, int start)
: speed(speed), CAPACITY(capacity)
{
  location = Building::floors[start];
  direction = IDLE;
  timer = 0;
  atFloorIndex = -1;

  for(int i = 0; i < Building::FLOORS; i++)
  {
    panel.addButton(Building::floors[i].label);
  }
}

void Elevator::openDoorTo(int floorindex)
{
  this->panel.clear(Building::floors[floorindex].label);
  this->atFloorIndex = floorindex;
  this->resetTimer();
}

void Elevator::board(const Rider& rider)
{
  this->riders.push_back(rider);
  this->panel.press(Building::floors[rider.to].label);
  if(rider.goingUp) this->direction = UP;
  else if(rider.goingDown) this->direction = DOWN;

  this->resetTimer();
}

ostream& operator<<(ostream& out, const Elevator& e){
  out << "Elevator at";
  out.width(6);
  out << e.location;

  out.width(13);
  if(e.direction == e.UP)
  {
    out << " going UP ";
  }
  else if(e.direction == e.DOWN)
  {
    out << " going DOWN ";
  }
  else
  {
    out << " IDLE ";
  }

  out.width(4);
  out << e.riders.size() << " " << "riders";

  if (e.atFloorIndex != -1)
  {
    out << " door is OPEN|" << e.timer << " ";
  }

  out << e.panel;

  return out;
}
