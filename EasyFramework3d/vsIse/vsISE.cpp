/*
  Name: vsIse.cpp
  Copyright: vs
  Author: Rolf
  Date: 04.05.05 22:41
  Description: Implementation der Methoden und Konstruktoren ... der vsIse Klasse
*/

#include <string>
#include <math.h>
#include <assert.h>
#include <iostream>
#include "vsIse.h"
#include "konstanten.h"

vsIse::vsIse()
{
    vz = false;
    ziffer = 0;  
    for (int i=0; i<VS_ISE_STUFENANZAHL; i++)
    {
        ziffern[i] = 0;
    }                
}

vsIse::vsIse(double newZiffer)
:ziffer(fabs(newZiffer))
{
    if (newZiffer >= 0)
        vz = false;
    else vz = true;
    
    for (int i=0; i<VS_ISE_STUFENANZAHL; i++)
    {
        ziffern[i] = 0;
    }       
}

vsIse::vsIse(bool vz, double newZiffer, int *newZiffern)
{
    this->vz = vz;
    assert(newZiffer >= 0);     // wenn false, wird fehler hier angegeben!!
    ziffer = newZiffer;
    for (int i=0; i<VS_ISE_STUFENANZAHL; i++)
    {
        this->ziffern[i] = newZiffern[i];
    }
}

vsIse::~vsIse()
{

}
	
vsIse::vsIse(const vsIse& iseOP2)		// Kopierkonstruktor
{
    vz = iseOP2.vz;
    ziffer = iseOP2.ziffer;
    for (int i=0; i<VS_ISE_STUFENANZAHL; i++)
    {
        ziffern[i] = iseOP2.ziffern[i];
    }
}

vsIse vsIse::operator+(const vsIse &iseOP2)
{
    vsIse temp(vz, ziffer, ziffern);
    
    temp += iseOP2;
    
    return temp;
}

vsIse vsIse::operator-(const vsIse &iseOP2)
{
    vsIse temp(vz, ziffer, ziffern);
    
    temp -= iseOP2;
    
    return temp;
}

vsIse &vsIse::operator=(const vsIse &iseOP2)
{
    if (this != &iseOP2)
    {
        vz = iseOP2.vz;
        ziffer = iseOP2.ziffer;
        for (int i=0; i<VS_ISE_STUFENANZAHL; i++)
        {
            ziffern[i] = iseOP2.ziffern[i];
        }
    }
    return *this;
}

vsIse &vsIse::operator+=(const vsIse &iseOP2)
{
    if (vz == iseOP2.vz)
        carryPlus(iseOP2);
    else
        carryMinus(iseOP2);
        
    return *this; 
}

vsIse &vsIse::operator-=(const vsIse &iseOP2)
{
    if (vz != iseOP2.vz)
        carryPlus(iseOP2);
    else
        carryMinus(iseOP2);
        
    return *this;   
}

vsIse &vsIse::operator=(const double &OP2)
{
        ziffer = fabs(OP2);
        if (OP2 >= 0)
            vz = false;
        else vz = true;
        
        for (int i=0; i<VS_ISE_STUFENANZAHL; i++)
        {
            ziffern[i] = 0;
        }
    return *this;
}
	
vsIse vsIse::operator+(const double &zifferAdd)
{
    vsIse temp(vz, ziffer, ziffern);
    temp += zifferAdd;
    return temp;
}

vsIse vsIse::operator-(const double &zifferSub)
{
    
    vsIse temp(vz, ziffer, ziffern);
    temp -= zifferSub;
    return temp;
}

vsIse &vsIse::operator+=(const double &zifferAdd)
{
    if (!vz)
        ziffer += zifferAdd;
    else
        ziffer -= zifferAdd;
        
    carry();
        
    return *this; 
}

vsIse &vsIse::operator-=(const double &zifferSub)
{
    if (!vz)
        ziffer -= zifferSub;
    else
        ziffer += zifferSub;
    
    carry();
    
    return *this;       
}

vsIse& vsIse::operator*=(const vsIse &iseOP2)
{
    ziffer*=iseOP2.ziffer;

    if (ziffer > VS_ISE_BASIS)
    {
        *this += ziffer;                      // der überlauf geht mit += in höhere wertigkeiten
        ziffer = modf (ziffer, VS_ISE_BASIS); // splittet die zahl auf und nimmt die hintere hälfte
    }
    
    int carry = 0;
    
    for (int OPthis=2; OPthis < VS_ISE_STUFENANZAHL/2+1; OPthis++)
    {
        for (int OP2=0; OP2 < VS_ISE_STUFENANZAHL/2; OP2++)
        {
            ziffern[OPthis] = modf(ziffern[OPthis] * ziffern[OP2], VS_ISE_BASIS) + carry;
            carry = (ziffern[OPthis] * iseOP2.ziffern[OP2]) / VS_ISE_BASIS;       
                 
        }
        
    }
    
    
    return *this;   
}

double vsIse::getLJahr()	    	// rechnet in Lichtjahre um
{
           
}

double vsIse::getLStunde()		//            Lichtstunde
{
       
}

double vsIse::getLMinute()		// blabla
{
       
}

double vsIse::getLSekunde()  	// blublublu
{
              
}

std::string vsIse::strGetString()  	// in Lichtjahre umgerechnet mit einheitenbezeichnungen usw.
{
       
}

void vsIse::getCout() const
{
    if (vz) printf("-");
    else printf("+");
    for (int i=VS_ISE_STUFENANZAHL-2; i>=0; i--)
    {
        printf("%04u ",ziffern[i]);
    }
    printf("%04.3f\n",fabs(ziffer));    
}

double vsIse::getZiffer()              // ISE double holen. 1.Stufe : 0 - 1 000 000
{
    return ziffer;   
}

void vsIse::setIse(double zifferSet, int *ziffernSet)      // ISE setzten
{
    ziffer = zifferSet;
    for (int i=0; i<VS_ISE_STUFENANZAHL-1; i++)
    {
        ziffern[i] = getZiffer(i);
    }     
}

void vsIse::carry()
{
    if (ziffer < VS_ISE_BASIS && ziffer >= 0) return;
    
    if (ziffer >= VS_ISE_BASIS)
    {
        while (ziffer >= 2*VS_ISE_BASIS)
        {
            ziffer -= VS_ISE_BASIS;
            ziffern[0]++;
        }
        ziffer -= VS_ISE_BASIS;
            
        for (int i=0; i<VS_ISE_STUFENANZAHL-1; i++)
        {
            ziffern[i]++;
            if (ziffern[i] < VS_ISE_BASIS) return;
            
            ziffern[i] = 0;
        }
    }
    else
    {
        // vorzeichenwechsel
        bool allNull = true;
        for (int i=0; i<VS_ISE_STUFENANZAHL-1; i++)
        {
            if (ziffern[i] != 0)
            {
                allNull = false;
                break;
            }
        }
        if (allNull)
        {
            ziffer = -ziffer;
            vz = !vz;
            return;
        }
        
        while (ziffer < -VS_ISE_BASIS)
        {
            ziffer += VS_ISE_BASIS;
            ziffern[0]--;
        }
        ziffer += VS_ISE_BASIS;
        
        for (int i=0; i<VS_ISE_STUFENANZAHL-1; i++)
        {
            ziffern[i]--;
            if (ziffern[i] >= 0) return;
            
            ziffern[i] = VS_ISE_BASIS-1;
        }
    }
}

void vsIse::carryPlus(const vsIse &op)
{
    ziffer += op.ziffer;
    
    if (ziffer >= VS_ISE_BASIS)
    {
        ziffer -= VS_ISE_BASIS;
        ziffern[0]++;
    }
        
    for (int i=0; i<VS_ISE_STUFENANZAHL-2; i++)
    {
        ziffern[i] += op.ziffern[i];
        
        if (ziffern[i] >= VS_ISE_BASIS)
        {
            ziffern[i+1]++;
            ziffern[i] -= VS_ISE_BASIS;
        }
    }
    ziffern[VS_ISE_STUFENANZAHL-2] += op.ziffern[VS_ISE_STUFENANZAHL-2];
}

void vsIse::carryMinus(const vsIse &op)
{
    // op is smaller than this obj
    if (!absLess(op))
    {
        ziffer -= op.ziffer;
    
        if (ziffer < 0)
        {
            ziffer += VS_ISE_BASIS;
            ziffern[0]--;
        }
        
        for (int i=0; i<VS_ISE_STUFENANZAHL-2; i++)
        {
            ziffern[i] -= op.ziffern[i];
            
            if (ziffern[i] < 0)
            {
                ziffern[i+1]--;
                ziffern[i] += VS_ISE_BASIS;
            }
        }
        ziffern[VS_ISE_STUFENANZAHL-2] -= op.ziffern[VS_ISE_STUFENANZAHL-2];
    }
    else
    // op is greater than this obj => all differences the other way round
    {
        ziffer -= op.ziffer;
        ziffer = -ziffer;

        if (ziffer < 0)
        {
            ziffer += VS_ISE_BASIS;
            ziffern[0]++;
        }
        
        for (int i=0; i<VS_ISE_STUFENANZAHL-2; i++)
        {
            ziffern[i] -= op.ziffern[i];
            ziffern[i] = -ziffern[i];
            
            if (ziffern[i] < 0)
            {
                ziffern[i+1]++;
                ziffern[i] += VS_ISE_BASIS;
            }
        }
        ziffern[VS_ISE_STUFENANZAHL-2] -= op.ziffern[VS_ISE_STUFENANZAHL-2];
        ziffern[VS_ISE_STUFENANZAHL-2] = -ziffern[VS_ISE_STUFENANZAHL-2];
    }
}

bool vsIse::operator<=(const vsIse &iseOP2)
{
    if  (vz && !iseOP2.vz)
        return true;
        
    if (*this == iseOP2)
        return true;
    
    if (!vz && iseOP2.vz)
        return false;
    
    return absLess(iseOP2);
}

bool vsIse::operator<(const vsIse &iseOP2)
{
    return (*this < iseOP2) && (*this != iseOP2);
}

bool vsIse::operator>(const vsIse &iseOP2)
{
    return !(*this <= iseOP2);
}

bool vsIse::operator>=(const vsIse &iseOP2)
{
    return !(*this < iseOP2);
}

bool vsIse::operator!=(const vsIse &iseOP2)
{
    return !(*this == iseOP2);
}

bool vsIse::operator==(const vsIse &iseOP2)
{
    if (vz != iseOP2.vz)
    {
        for (int i = 0; i < VS_ISE_STUFENANZAHL-1; i++)
        {
            if (!(ziffern[i] == iseOP2.ziffern[i] && ziffern[i] == 0))
                return false;
        }
        if (ziffer == iseOP2.ziffer && ziffer == 0.0)
            return true; 
    }
    
    for (int i = 0; i < VS_ISE_STUFENANZAHL-1; i++)
    {
        if (ziffern[i] != iseOP2.ziffern[i])
            return false;
    }
    return (ziffer == iseOP2.ziffer);
}

bool vsIse::absLess(const vsIse &iseOP2)
{
    for (int i = VS_ISE_STUFENANZAHL-2; i >= 0; i--)
    {
        if (ziffern[i] > iseOP2.ziffern[i])
        {
            return false;
        }
        if (ziffern[i] < iseOP2.ziffern[i])
        {
            return true;
        }
    }
    
    return (ziffer < iseOP2.ziffer);
}
