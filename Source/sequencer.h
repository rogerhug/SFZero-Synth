
#include "../JuceLibraryCode/JuceHeader.h"
#include "SFZeroAudioProcessor.h"


	class Sequencer 
	{
	public:
		Sequencer();
		~Sequencer();
	
		double Time(double Time);
		double Timer(double sec);
		double TimerHost(int TimeHost);
		double TimerHostOut(int TimeHostout);

		virtual void SetPosition(int mod) { mPos = 1. + mod; }
		virtual void SetSampel(int mod) { mSampel = 1. + mod; }

		bool triggerDef(bool tr1Def);
		bool triggerHost(bool tr1Def);

		virtual void SetTime(int mod) { mTime = 1. + mod; }
		virtual void SetTr1(bool mod) { trigger1 = 0 + mod; }
		virtual void SetTr2(bool mod) { trigger2 = 0 + mod; }
		virtual void SetTr3(bool mod) { trigger3 = 0 + mod; }
		virtual void SetTr4(bool mod) { trigger4 = 0 + mod; }
		virtual void SetTr5(bool mod) { trigger5 = 0 + mod; }
		virtual void SetTr6(bool mod) { trigger6 = 0 + mod; }
		virtual void SetTr7(bool mod) { trigger7 = 0 + mod; }
		virtual void SetTr8(bool mod) { trigger8 = 0 + mod; }
		virtual void SetHold1(bool mod) { hold1 = 0 + mod; }



	protected:


	private:
		SFZeroAudioProcessor pc1;
	
		int initT;	int xtm;
		int mTime, mCount, mPreviusCount, mPos, mSampel;
		int trigger1, trigger2, trigger3, trigger4, trigger5, trigger6, trigger7, trigger8, hold1;
		float mili;

	};




