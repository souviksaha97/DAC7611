//Release Date: 15-12-2018
//souvikssaha@gmail.com

/*===========================================================================
DAC7611 device library code is placed under the MIT license
Copyright (c) 2018 Souvik Saha

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
===========================================================================*/

//The DAC7611 is a 12-bit digital-to-analog converter
//(DAC) with guaranteed 12-bit monotonicity performance over the industrial temperature range. 
//It requires a single +5V supply and contains an input shift
//register, latch, 2.435V reference, DAC, and high speed
//rail-to-rail output amplifier. 


#include "DAC7611.h"
#include "Arduino.h"

DAC7611::DAC7611(int CS, int CLK, int SDI, int LD, int CLR){
  _CS = CS;
  _CLK = CLK;
  _SDI = SDI;
  _LD = LD;
  _CLR = CLR;
}

void DAC7611::begin(void)
{
  pinMode(_CS,OUTPUT);
  pinMode(_CLK,OUTPUT);  
  pinMode(_SDI,OUTPUT);  
  pinMode(_LD,OUTPUT);  
  pinMode(_CLR,OUTPUT);

  digitalWrite(_CLR, HIGH);
  digitalWrite(_CS, HIGH);
  digitalWrite(_CLK,HIGH);
  digitalWrite(_LD,LOW);
  digitalWrite(_SDI,LOW);
}

void DAC7611::sendDAC(int IPvalue)
{
  IPvalue = constrain(IPvalue, 0, 4095);
  formatData(IPvalue);
  digitalWrite(_LD,HIGH);
  delayMicroseconds(1);
  digitalWrite(_CS,LOW);
  delayMicroseconds(1); 
  for(int i=11;i>=0;i--)
  {
   advance_bit(sdata[i]);
  }
  SSR();
  clr();          
}
 
void DAC7611::reset(void)
{
  digitalWrite(_CLR, HIGH);
  delayMicroseconds(10);
  digitalWrite(_CLR, LOW);
  delayMicroseconds(10);
  digitalWrite(_CLR, HIGH);
}

void DAC7611::advance_bit(int dataBit)
{
    digitalWrite(_CLK,LOW);
    digitalWrite(_SDI,dataBit);
    digitalWrite(_CLK,HIGH);
    delayMicroseconds(1);    
}

void DAC7611::SSR(void)
{
    digitalWrite(_CS,HIGH);
    delayMicroseconds(1);
    digitalWrite(_LD,LOW);
    delayMicroseconds(1);
    digitalWrite(_LD,HIGH);
}

void DAC7611::formatData(int IPvalue)
{
    //int sdata[12];
      int i = 0;
      int tmp = IPvalue;
      while(tmp != 0)
      {
        sdata[i] = tmp%2;
        tmp/=2;
        i++;
      }
     //Serial.println(input);   
}

void DAC7611::clr(void)
{
    for (int i = 0; i < 12; i++)
    {
      sdata[i] = 0;
    }
}
