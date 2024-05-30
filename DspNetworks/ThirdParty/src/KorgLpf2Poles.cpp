/* ------------------------------------------------------------
author: "Your Name"
license: "MIT-style STK-4.3 license"
name: "Korg35Filter"
Code generated with Faust 2.70.3 (https://faust.grame.fr)
Compilation options: -lang cpp -rui -nvi -ct 1 -cn _KorgLpf2Poles -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___KorgLpf2Poles_H__
#define  ___KorgLpf2Poles_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _KorgLpf2Poles
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif


class _KorgLpf2Poles final : public ::faust::dsp {
	
 public:
	
	int fSampleRate;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	float fConst3;
	float fRec4[2];
	FAUSTFLOAT fHslider1;
	float fRec5[2];
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fRec7[2];
	float fRec8[2];
	float fRec9[2];
	
 public:
	_KorgLpf2Poles() {}

	void metadata(Meta* m) { 
		m->declare("author", "Your Name");
		m->declare("compile_options", "-lang cpp -rui -nvi -ct 1 -cn _KorgLpf2Poles -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("description", "FAUST Korg 35 Band-Pass Filter");
		m->declare("filename", "KorgLpf2Poles.dsp");
		m->declare("license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.7.0");
		m->declare("name", "Korg35Filter");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.5.0");
	}

	static constexpr int getStaticNumInputs() {
		return 2;
	}
	static constexpr int getStaticNumOutputs() {
		return 2;
	}
	int getNumInputs() {
		return 2;
	}
	int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 3.1415927f / fConst0;
		fConst2 = 44.1f / fConst0;
		fConst3 = 1.0f - fConst2;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(2e+04f);
		fHslider1 = FAUSTFLOAT(1.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec4[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec5[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec2[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec3[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec7[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec8[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec9[l7] = 0.0f;
		}
	}
	
	void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	_KorgLpf2Poles* clone() {
		return new _KorgLpf2Poles();
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Korg35Filter");
		ui_interface->declare(&fHslider0, "0", "");
		ui_interface->declare(&fHslider0, "abbrev", "cutoff");
		ui_interface->declare(&fHslider0, "scale", "log");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "symbol", "cutoff");
		ui_interface->declare(&fHslider0, "unit", "hz");
		ui_interface->addHorizontalSlider("Cutoff frequency", &fHslider0, FAUSTFLOAT(2e+04f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "abbrev", "q");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "symbol", "q");
		ui_interface->addHorizontalSlider("Q", &fHslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.5f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst2 * std::max<float>(2e+01f, std::min<float>(2e+04f, float(fHslider0)));
		float fSlow1 = fConst2 * std::max<float>(0.5f, std::min<float>(1e+01f, float(fHslider1)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec4[0] = fSlow0 + fConst3 * fRec4[1];
			float fTemp0 = std::tan(fConst1 * fRec4[0]);
			float fTemp1 = float(input0[i0]);
			float fTemp2 = (fTemp1 - fRec3[1]) * fTemp0;
			fRec5[0] = fSlow1 + fConst3 * fRec5[1];
			float fTemp3 = fRec5[0] + -0.707f;
			float fTemp4 = fTemp0 + 1.0f;
			float fTemp5 = fTemp0 / fTemp4;
			float fTemp6 = fTemp5 + -1.0f;
			float fTemp7 = 0.21521576f * fRec1[1] * fTemp3 * fTemp6;
			float fTemp8 = 1.0f - 0.21521576f * (fTemp0 * fTemp3 * (1.0f - fTemp5) / fTemp4);
			float fTemp9 = fTemp0 * ((fRec3[1] + (fTemp2 - fTemp7 - fRec2[1]) / fTemp4) / fTemp8 - fRec1[1]) / fTemp4;
			float fTemp10 = fRec1[1] + fTemp9;
			float fRec0 = fTemp10;
			fRec1[0] = fRec1[1] + 2.0f * fTemp9;
			fRec2[0] = fRec2[1] + 2.0f * (fTemp0 * (0.21521576f * fTemp3 * fTemp10 - fRec2[1]) / fTemp4);
			fRec3[0] = fRec3[1] + 2.0f * (fTemp2 / fTemp4);
			output0[i0] = FAUSTFLOAT(fRec0);
			float fTemp11 = float(input1[i0]);
			float fTemp12 = fTemp0 * (fTemp11 - fRec9[1]);
			float fTemp13 = 0.21521576f * fTemp3 * fTemp6 * fRec7[1];
			float fTemp14 = fTemp0 * ((fRec9[1] + (fTemp12 - fTemp13 - fRec8[1]) / fTemp4) / fTemp8 - fRec7[1]) / fTemp4;
			float fTemp15 = fRec7[1] + fTemp14;
			float fRec6 = fTemp15;
			fRec7[0] = fRec7[1] + 2.0f * fTemp14;
			fRec8[0] = fRec8[1] + 2.0f * (fTemp0 * (0.21521576f * fTemp3 * fTemp15 - fRec8[1]) / fTemp4);
			fRec9[0] = fRec9[1] + 2.0f * (fTemp12 / fTemp4);
			output1[i0] = FAUSTFLOAT(fRec6);
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "KorgLpf2Poles.dsp"
	#define FAUST_CLASS_NAME "_KorgLpf2Poles"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -rui -nvi -ct 1 -cn _KorgLpf2Poles -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Cutoff frequency", fHslider0, 2e+04f, 2e+01f, 2e+04f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Q", fHslider1, 1.0f, 0.5f, 1e+01f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Cutoff_frequency, "Cutoff frequency", fHslider0, 2e+04f, 2e+01f, 2e+04f, 0.1f) \
		p(HORIZONTALSLIDER, Q, "Q", fHslider1, 1.0f, 0.5f, 1e+01f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif
