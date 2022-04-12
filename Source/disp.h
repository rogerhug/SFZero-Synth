
#include"SFZeroAudioProcessor.h"


class Para1 
{
public:
	Para1();
	~Para1();

	virtual void Setvalue(float mod) { vd = 1. + mod; }

	double getValue(double vl);
protected:


private:
	double vd;
	
	SFZeroAudioProcessor* ownerFilter;

};