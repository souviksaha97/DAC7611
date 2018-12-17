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

#ifndef DAC_H
#define DAC_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class DAC7611 {
  public:
    DAC7611(int CS = 2, int CLK = 3, int SDI = 4, int LD = 5, int CLR = 6);

    void sendDAC(int IPvalue);
    void begin(void);
    void reset(void);
    void clr(void);

  private:

    void advance_bit(int dataBit);
    void SSR(void);
    void formatData(int IPvalue);
    int sdata[12];
    int _CS;
    int _CLK;
    int _SDI;
    int _LD;
    int _CLR;
  
};

#endif
