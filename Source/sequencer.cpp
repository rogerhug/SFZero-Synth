#include "sequencer.h"
#include <time.h>
#include <chrono>

#include <ctime>
using namespace std;





Sequencer::Sequencer() {};

Sequencer::~Sequencer() {}

	


double Sequencer::Time(double Time)

{
	
	

	

	//t1 = 12;
	
	
	//cout << count << endl;
	clock_t initS;
	
	
	int countT = 0;
	initS = clock();
	//const int init2 = (int)Time::getMillisecondCounter();
	int init2 = initS;
	int tc33 = 0;
	// init = 1+initT ;
	
	 int  Tdur = 33;
	 int Tsh = 1;
 int vt = 0;
 int tx,tx1,tx2,tx3,tx4;


 countT = init2 / 1000 % 4 + 1;
 

	 if (countT == 1 && initS % 1000<Tdur) {

		 	 vt = 1;
			 }

	 if (countT == 1 && initS % 1000+ Tsh > Tdur) {
		 vt -= 0;
	 }
	 if (countT == 2 && initS % 1000<Tdur) {

		 vt = 1;
	 }

	 if (countT ==2 && initS  % 1000+ Tsh > Tdur) {
		 vt = 0;
	 }

	 if (countT == 3 && initS % 1000<Tdur) {

		 vt = 1;
	 }

	 if (countT == 3 && initS  % 1000+ Tsh > Tdur) {
		 vt = 0;
	 }
	 if (countT == 4 && initS % 1000<Tdur) {

		 vt = 1;
	 }

	 if (countT == 4 && initS  % 1000+ Tsh > Tdur) {
		 vt = 0;
	 }
		 

	 
	
 Time =vt ;	
xtm = countT;
	
	return Time;

}

double Sequencer::Timer(double sec)
{
	const int initT = (int)Time::getMillisecondCounter()/1000%4+1;
	
	double x;
	 
	sec =x;
		return sec;
	
}
double Sequencer::TimerHost(int TimeHost)
{

	int count = mCount;

	int mod = (mPos) % (mSampel * 2);

	count = mod / (mSampel / 4);

     TimeHost = count+1;
	

	
	
	
	return TimeHost;
}

double Sequencer::TimerHostOut(int TimeHostout)
{
	int count = mCount;
	int countT = 0;
	int mod = (mPos) % (mSampel * 8);

	count = mod / (mSampel / 8);

	for (int i = 0; i < count; ++i)
	{
		if (++countT > 1)
			countT = 0;
		TimeHostout = countT;
	}





	return TimeHostout;
}


bool Sequencer::triggerDef(bool tr1Def)
{


	int tt1 = Time(0);


	int duration = 2;
	
	if (tt1 == 1 && trigger1 == true   || tt1 == 2 && trigger2 == true  || tt1 == 3 && trigger3 == true  || tt1 == 4 && trigger4 == true  || tt1 == 5 && trigger5 == true || tt1 == 6 && trigger6 == true || tt1 == 7 && trigger7 == true  || tt1 == 8 && trigger8 == true )
	{
		tr1Def = 1;
	}
	else
		tr1Def = 0;
	

	return tr1Def;
}

bool Sequencer::triggerHost(bool tr1Def)
{
	
	int tt1 = TimerHost(0);
	int tt2 = TimerHostOut(0);

	if (tt1 == 1 && trigger1 == true || tt1 == 2 && trigger2 == true || tt1 == 3 && trigger3 == true || tt1 == 4 && trigger4 == true || tt1 == 5 && trigger5 == true || tt1 == 6 && trigger6 == true || tt1 == 7 && trigger7 == true || tt1 == 8 && trigger8 == true)
	{
		tr1Def = true;
	}

	if (tt2 == 1 && hold1 == 1)
	{
		tr1Def = false;
	}

	return tr1Def;
}


;