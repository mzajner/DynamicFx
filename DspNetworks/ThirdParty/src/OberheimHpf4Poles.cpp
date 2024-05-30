/* ------------------------------------------------------------
author: "Christopher Arndt, Eric Tarr"
license: "MIT-style STK-4.3 license"
name: "Oberheim"
Code generated with Faust 2.70.3 (https://faust.grame.fr)
Compilation options: -lang cpp -rui -nvi -ct 1 -cn _OberheimHpf4Poles -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___OberheimHpf4Poles_H__
#define  ___OberheimHpf4Poles_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _OberheimHpf4Poles
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

static float _OberheimHpf4Poles_faustpower2_f(float value) {
	return value * value;
}

class _OberheimHpf4Poles final : public ::faust::dsp {
	
 public:
	
	int fSampleRate;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	float fRec5[2];
	float fConst3;
	FAUSTFLOAT fHslider1;
	float fRec6[2];
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fRec4[2];
	float fRec8[2];
	float fRec9[2];
	float fRec10[2];
	float fRec11[2];
	
 public:
	_OberheimHpf4Poles() {}

	void metadata(Meta* m) { 
		m->declare("author", "Christopher Arndt, Eric Tarr");
		m->declare("compile_options", "-lang cpp -rui -nvi -ct 1 -cn _OberheimHpf4Poles -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("description", "Oberheim multi-mode, state-variable filter");
		m->declare("filename", "OberheimHpf4Poles.dsp");
		m->declare("license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.7.0");
		m->declare("misceffects.lib/cubicnl:author", "Julius O. Smith III");
		m->declare("misceffects.lib/cubicnl:license", "STK-4.3");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.4.0");
		m->declare("name", "Oberheim");
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
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 3.1415927f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1.0f);
		fHslider1 = FAUSTFLOAT(2e+04f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec5[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec6[l1] = 0.0f;
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
			fRec4[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec8[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec9[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec10[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec11[l9] = 0.0f;
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
	
	_OberheimHpf4Poles* clone() {
		return new _OberheimHpf4Poles();
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Oberheim");
		ui_interface->declare(&fHslider1, "0", "");
		ui_interface->declare(&fHslider1, "abbrev", "cutoff");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "symbol", "cutoff");
		ui_interface->declare(&fHslider1, "unit", "hz");
		ui_interface->addHorizontalSlider("Cutoff frequency", &fHslider1, FAUSTFLOAT(2e+04f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "abbrev", "q");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "symbol", "q");
		ui_interface->addHorizontalSlider("Q", &fHslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.3f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = fConst1 * std::max<float>(0.3f, std::min<float>(1e+01f, float(fHslider0)));
		float fSlow1 = fConst1 * std::max<float>(2e+01f, std::min<float>(2e+04f, float(fHslider1)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = float(input0[i0]);
			fRec5[0] = fSlow0 + fConst2 * fRec5[1];
			fRec6[0] = fSlow1 + fConst2 * fRec6[1];
			float fTemp1 = std::tan(fConst3 * fRec6[0]);
			float fTemp2 = 1.0f / fRec5[0] + fTemp1;
			float fTemp3 = fTemp0 - (fRec3[1] + fRec4[1] * fTemp2);
			float fTemp4 = fTemp1 * fTemp2 + 1.0f;
			float fRec0 = fTemp3 / fTemp4;
			float fTemp5 = fTemp1 * (fTemp0 - (fRec1[1] + fTemp2 * fRec2[1])) / fTemp4;
			float fTemp6 = std::max<float>(-1.0f, std::min<float>(1.0f, fRec2[1] + fTemp5));
			float fTemp7 = 1.0f - 0.33333334f * _OberheimHpf4Poles_faustpower2_f(fTemp6);
			fRec1[0] = fRec1[1] + 2.0f * fTemp1 * fTemp6 * fTemp7;
			fRec2[0] = fTemp5 + fTemp6 * fTemp7;
			float fTemp8 = fTemp1 * fTemp3 / fTemp4;
			float fTemp9 = std::max<float>(-1.0f, std::min<float>(1.0f, fRec4[1] + fTemp8));
			float fTemp10 = 1.0f - 0.33333334f * _OberheimHpf4Poles_faustpower2_f(fTemp9);
			fRec3[0] = fRec3[1] + 2.0f * fTemp1 * fTemp9 * fTemp10;
			fRec4[0] = fTemp8 + fTemp9 * fTemp10;
			output0[i0] = FAUSTFLOAT(fRec0);
			float fTemp11 = float(input1[i0]);
			float fTemp12 = fTemp11 - (fRec10[1] + fTemp2 * fRec11[1]);
			float fRec7 = fTemp12 / fTemp4;
			float fTemp13 = fTemp1 * (fTemp11 - (fRec8[1] + fTemp2 * fRec9[1])) / fTemp4;
			float fTemp14 = std::max<float>(-1.0f, std::min<float>(1.0f, fRec9[1] + fTemp13));
			float fTemp15 = 1.0f - 0.33333334f * _OberheimHpf4Poles_faustpower2_f(fTemp14);
			fRec8[0] = fRec8[1] + 2.0f * fTemp1 * fTemp14 * fTemp15;
			fRec9[0] = fTemp13 + fTemp14 * fTemp15;
			float fTemp16 = fTemp1 * fTemp12 / fTemp4;
			float fTemp17 = std::max<float>(-1.0f, std::min<float>(1.0f, fRec11[1] + fTemp16));
			float fTemp18 = 1.0f - 0.33333334f * _OberheimHpf4Poles_faustpower2_f(fTemp17);
			fRec10[0] = fRec10[1] + 2.0f * fTemp1 * fTemp17 * fTemp18;
			fRec11[0] = fTemp16 + fTemp17 * fTemp18;
			output1[i0] = FAUSTFLOAT(fRec7);
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "OberheimHpf4Poles.dsp"
	#define FAUST_CLASS_NAME "_OberheimHpf4Poles"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -rui -nvi -ct 1 -cn _OberheimHpf4Poles -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("Cutoff frequency", fHslider1, 2e+04f, 2e+01f, 2e+04f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Q", fHslider0, 1.0f, 0.3f, 1e+01f, 0.01f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Cutoff_frequency, "Cutoff frequency", fHslider1, 2e+04f, 2e+01f, 2e+04f, 0.1f) \
		p(HORIZONTALSLIDER, Q, "Q", fHslider0, 1.0f, 0.3f, 1e+01f, 0.01f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif
