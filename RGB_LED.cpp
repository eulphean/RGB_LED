/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   
  Code by Amanda Yamasaki
  for Jan Tichy's Public Light and Space
  https://github.com/amandayamasaki
  
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Arduino.h"
#include "RGB_LED.h"

/* * *  This is for the RGB Led * * */
RGB_LED::RGB_LED(int pin1, int pin2, int pin3){
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);

  _pins[0] = pin1; 
  _pins[1] = pin2;
  _pins[2] = pin3; 
}

void RGB_LED::setColor(int red, int green, int blue) {
  analogWrite(_pins[0], red); 
  analogWrite(_pins[1], green);
  analogWrite(_pins[2], blue);
}





