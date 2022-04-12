
#include "disp.h"

Para1::Para1() {};

Para1::~Para1() {}





double Para1::getValue(double vl)

{
vd = ownerFilter->getHighResolutionTicks()*0.001;
//	vd = ownerFilter->getMillisecondCounterHiRes();
	
	vl = vd;
	return vl;
}

