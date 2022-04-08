#include"Panel.h"

#include<iostream>
#include<vector>
using namespace std;

int Panel::Button::count = 0;

void Panel::addButton(string label)
{
  Button b;
  b.label = label;
  b.lit = false;
  buttons.push_back(b);
}

void Panel::press(string label)
{
  for(unsigned int i = 0; i < buttons.size(); i++)
  {
    if(buttons[i].label == label)
    {
      Button::count++;
      buttons[i].lit = true;
      buttons[i].sequence = Button::count;
    }
  }
}

void Panel::clear(string label)
{
  for(unsigned int i = 0; i < buttons.size(); i++)
  {
    if(buttons[i].label == label)
    {
      if(buttons[i].lit == true)
      {
        buttons[i].lit = false;
        for(unsigned int j = 0; j < buttons.size(); j++)
        {
          if(buttons[j].sequence > buttons[i].sequence)
          buttons[j].sequence--;
        }
        buttons[i].sequence = 0;
        Button::count--;
      }
    }
  }
}

string Panel::getFirstLit() const
{
  for(unsigned int i = 0; i < buttons.size(); i++)
  {
    if(buttons[i].lit == true)
    {
      if(buttons[i].sequence == 1)
      {
        return buttons[i].label;
      }
    }
  }
  return "";
}

bool Panel::isLit(string label) const
{
  for(unsigned int i = 0; i < buttons.size(); i++)
  {
    if(buttons[i].label == label)
    {
      return buttons[i].lit;
    }
  }
  return false;
}

bool Panel::areAnyLit() const
{
  for(unsigned int i = 0; i < buttons.size(); i++)
  {
    if(buttons[i].lit == true)
    {
      return true;
    }
  }
  return false;
}

ostream& operator<<(ostream& out, const Panel& panel)
{
  for(unsigned int i = 0; i < panel.buttons.size(); i++)
    {
      if(panel.isLit(panel.buttons[i].label))
      out << "[" << panel.buttons[i].label << "]";
    }
  return out;
}
