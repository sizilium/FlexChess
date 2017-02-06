/*
  Name: vsIse.h
  Copyright: vs
  Author: Rolf
  Date: 04.05.05 22:41
  Description: ISE Klasse. Interstellare Einheit, zum speichern von 
  			   sehr großen Zahlen!
*/

#include <string>
#include "konstanten.h"

#ifndef vsIse_H
#define vsIse_H

class vsIse {
public:
	vsIse();
	vsIse(double newZiffer);
	vsIse(bool vz, double newZiffer, int *newZiffern);

	~vsIse();
	
	vsIse (const vsIse &vsIse);		// Kopierkonstruktor

	vsIse &operator=(const vsIse &iseOP2);
	vsIse operator+(const vsIse &iseOP2);
	vsIse operator-(const vsIse &iseOP2);
	vsIse &operator+=(const vsIse &iseOP2);
	vsIse &operator-=(const vsIse &iseOP2);
	
	vsIse &operator=(const double &OP2);
	vsIse operator+(const double &zifferAdd);
	vsIse operator-(const double &zifferSub);
	vsIse &operator+=(const double &zifferAdd);
	vsIse &operator-=(const double &zifferSub);
	
	vsIse& operator*=(const vsIse &iseOP2); // nur die ersten 3 "ziffern" multipliziert !!!!!
	                                        // die restlichen 3 dienen zum überlauf...
	
	bool operator==(const vsIse &iseOP2);
	bool operator!=(const vsIse &iseOP2);

	bool operator<=(const vsIse &iseOP2);
	bool operator>=(const vsIse &iseOP2);
	bool operator<(const vsIse &iseOP2);
	bool operator>(const vsIse &iseOP2);
		// TODO: wuzrel von ise ziehen !!!!!! 

	double getLJahr();	    	// rechnet in Lichtjahre um
	double getLStunde();		//            Lichtstunde
	double getLMinute();	
	double getLSekunde();  	

	std::string strGetString();  // in Lichtjahre umgerechnet mit einheitenbezeichnungen usw.
    void getCout() const;
    
	void setIse(double zifferSet, int *ziffernSet);      // ISE setzten
	void setZiffer(double zifferSet) { ziffer = zifferSet; }  // ISE double setzten. 1. Stufe
	double getZiffer();   // ISE double holen. 1.Stufe : 0 - 1 000 000
	double setArrayZiffer(int i) { ziffern[i] = i; }
    int getZiffer(int i) { return ziffern[i]; }           
    	
protected:
    bool vz;
    
	int ziffern[VS_ISE_STUFENANZAHL-1];	// dieses Array ergibt die Interstellare Einheit (ISE)
										    // ise in meter = dZiffer + iaZiffer[1]*1 000 000 + ...
    double ziffer;                      // speziell: Stufe 1 ist double, mehr genauigkeit	
    
    void carry();
    void carryPlus(const vsIse&);
    void carryMinus(const vsIse&);
    
    bool absLess(const vsIse &iseOP2);
};

#endif
