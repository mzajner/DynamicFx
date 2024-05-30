/* ------------------------------------------------------------
author: "Christophe Lebreton"
copyright: "SmartFaust - GRAME(c)2013-2018"
license: "BSD"
name: "sfTrashShift"
version: "1.1"
Code generated with Faust 2.70.3 (https://faust.grame.fr)
Compilation options: -lang cpp -rui -nvi -ct 1 -cn _MicroShifter -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___MicroShifter_H__
#define  ___MicroShifter_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _MicroShifter
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


class _MicroShifter final : public ::faust::dsp {
	
 public:
	
	FAUSTFLOAT fCheckbox0;
	float fRec0[2];
	FAUSTFLOAT fVslider0;
	float fRec1[2];
	int fSampleRate;
	float fConst2;
	float fConst3;
	FAUSTFLOAT fHslider0;
	float fVec0[2];
	float fRec2[2];
	int IOTA0;
	float fVec1[131072];
	FAUSTFLOAT fHslider1;
	float fVec2[2];
	float fRec3[2];
	FAUSTFLOAT fHslider2;
	float fConst4;
	float fRec5[2];
	FAUSTFLOAT fHslider3;
	float fRec6[2];
	float fRec4[2];
	float fConst5;
	float fRec7[2];
	float fVec3[131072];
	
 public:
	_MicroShifter() {}

	void metadata(Meta* m) { 
		m->declare("author", "Christophe Lebreton");
		m->declare("compile_options", "-lang cpp -rui -nvi -ct 1 -cn _MicroShifter -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("copyright", "SmartFaust - GRAME(c)2013-2018");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.1.0");
		m->declare("filename", "MicroShifter.dsp");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.3.0");
		m->declare("license", "BSD");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.7.0");
		m->declare("name", "sfTrashShift");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.5.0");
		m->declare("version", "1.1");
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
		float fConst1 = 1.0f / std::tan(3.1415927f / fConst0);
		fConst2 = 1.0f / (fConst1 + 1.0f);
		fConst3 = 1.0f - fConst1;
		fConst4 = 1.0f - 44.1f / fConst0;
		fConst5 = 22.05f / fConst0;
	}
	
	void instanceResetUserInterface() {
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fVslider0 = FAUSTFLOAT(1.0f);
		fHslider0 = FAUSTFLOAT(1.0f);
		fHslider1 = FAUSTFLOAT(1e+02f);
		fHslider2 = FAUSTFLOAT(75.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fVec0[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec2[l3] = 0.0f;
		}
		IOTA0 = 0;
		for (int l4 = 0; l4 < 131072; l4 = l4 + 1) {
			fVec1[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fVec2[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec3[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec5[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec6[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec4[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec7[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 131072; l11 = l11 + 1) {
			fVec3[l11] = 0.0f;
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
	
	_MicroShifter* clone() {
		return new _MicroShifter();
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("sfTrashShift");
		ui_interface->openHorizontalBox("sfTrashShift");
		ui_interface->addCheckButton("ON/OFF", &fCheckbox0);
		ui_interface->addVerticalSlider("Volume", &fVslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("sfTrashShift parameter(s)");
		ui_interface->declare(&fHslider1, "acc", "1 1 -10 0 10");
		ui_interface->declare(&fHslider1, "color", "255 255 0");
		ui_interface->declare(&fHslider1, "hidden", "1");
		ui_interface->addHorizontalSlider("dry_wet", &fHslider1, FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider0, "acc", "2 1 -10 0 10");
		ui_interface->declare(&fHslider0, "color", "255 255 0");
		ui_interface->declare(&fHslider0, "hidden", "1");
		ui_interface->addHorizontalSlider("gain", &fHslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider3, "acc", "0 1 -10 0 10");
		ui_interface->declare(&fHslider3, "color", "255 0 0");
		ui_interface->declare(&fHslider3, "hidden", "1");
		ui_interface->declare(&fHslider3, "units (cents)", "");
		ui_interface->addHorizontalSlider("shift", &fHslider3, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1e+02f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider2, "units (ms)", "");
		ui_interface->addHorizontalSlider("window", &fHslider2, FAUSTFLOAT(75.0f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = 0.002f * float(fCheckbox0);
		float fSlow1 = 0.002f * std::max<float>(0.0f, std::min<float>(2.0f, float(fVslider0)));
		float fSlow2 = std::max<float>(0.0f, std::min<float>(1.0f, float(fHslider0)));
		float fSlow3 = std::max<float>(0.0f, std::min<float>(1e+02f, float(fHslider1)));
		float fSlow4 = 0.0441f * std::max<float>(1e+01f, std::min<float>(1e+03f, float(fHslider2)));
		float fSlow5 = 2e-05f * std::max<float>(-1e+02f, std::min<float>(1e+02f, float(fHslider3)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = fSlow0 + 0.998f * fRec0[1];
			fRec1[0] = fSlow1 + 0.998f * fRec1[1];
			fVec0[0] = fSlow2;
			fRec2[0] = -(fConst2 * (fConst3 * fRec2[1] - (fSlow2 + fVec0[1])));
			float fTemp0 = fRec0[0] * std::min<float>(2.0f, std::max<float>(0.0f, fRec1[0])) * std::min<float>(1.0f, std::max<float>(0.0f, fRec2[0]));
			float fTemp1 = float(input0[i0]);
			fVec1[IOTA0 & 131071] = fTemp1;
			fVec2[0] = fSlow3;
			fRec3[0] = fConst2 * (0.01f * (fSlow3 + fVec2[1]) - fConst3 * fRec3[1]);
			float fTemp2 = std::min<float>(1.0f, std::max<float>(0.0f, fRec3[0]));
			float fTemp3 = 1.0f - fTemp2;
			fRec5[0] = fSlow4 + fConst4 * fRec5[1];
			fRec6[0] = fSlow5 + 0.998f * fRec6[1];
			fRec4[0] = std::fmod(fRec5[0] + fRec4[1] + (1.0f - std::pow(2.0f, 0.083333336f * fRec6[0])), fRec5[0]);
			fRec7[0] = fConst5 * fRec5[0] + fConst4 * fRec7[1];
			float fTemp4 = std::min<float>(fRec4[0] / fRec7[0], 1.0f);
			int iTemp5 = int(fRec4[0]);
			int iTemp6 = std::min<int>(65537, std::max<int>(0, iTemp5));
			float fTemp7 = std::floor(fRec4[0]);
			float fTemp8 = fTemp7 + (1.0f - fRec4[0]);
			float fTemp9 = fRec4[0] - fTemp7;
			int iTemp10 = std::min<int>(65537, std::max<int>(0, iTemp5 + 1));
			float fTemp11 = 1.0f - fTemp4;
			float fTemp12 = fRec5[0] + fRec4[0];
			int iTemp13 = int(fTemp12);
			int iTemp14 = std::min<int>(65537, std::max<int>(0, iTemp13));
			float fTemp15 = std::floor(fTemp12);
			float fTemp16 = fTemp15 + (1.0f - fTemp12);
			float fTemp17 = fTemp12 - fTemp15;
			int iTemp18 = std::min<int>(65537, std::max<int>(0, iTemp13 + 1));
			output0[i0] = FAUSTFLOAT(fTemp0 * (fTemp1 * fTemp3 + fTemp2 * (fTemp4 * (fVec1[(IOTA0 - iTemp6) & 131071] * fTemp8 + fTemp9 * fVec1[(IOTA0 - iTemp10) & 131071]) + fTemp11 * (fVec1[(IOTA0 - iTemp14) & 131071] * fTemp16 + fTemp17 * fVec1[(IOTA0 - iTemp18) & 131071]))));
			float fTemp19 = float(input1[i0]);
			fVec3[IOTA0 & 131071] = fTemp19;
			output1[i0] = FAUSTFLOAT(fTemp0 * (fTemp19 * fTemp3 + fTemp2 * (fTemp4 * (fVec3[(IOTA0 - iTemp6) & 131071] * fTemp8 + fTemp9 * fVec3[(IOTA0 - iTemp10) & 131071]) + fTemp11 * (fTemp16 * fVec3[(IOTA0 - iTemp14) & 131071] + fTemp17 * fVec3[(IOTA0 - iTemp18) & 131071]))));
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fVec0[1] = fVec0[0];
			fRec2[1] = fRec2[0];
			IOTA0 = IOTA0 + 1;
			fVec2[1] = fVec2[0];
			fRec3[1] = fRec3[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec4[1] = fRec4[0];
			fRec7[1] = fRec7[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "MicroShifter.dsp"
	#define FAUST_CLASS_NAME "_MicroShifter"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -rui -nvi -ct 1 -cn _MicroShifter -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 6
	#define FAUST_PASSIVES 0

	FAUST_ADDCHECKBOX("sfTrashShift/ON/OFF", fCheckbox0);
	FAUST_ADDVERTICALSLIDER("sfTrashShift/Volume", fVslider0, 1.0f, 0.0f, 2.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("sfTrashShift parameter(s)/dry_wet", fHslider1, 1e+02f, 0.0f, 1e+02f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("sfTrashShift parameter(s)/gain", fHslider0, 1.0f, 0.0f, 1.0f, 0.001f);
	FAUST_ADDHORIZONTALSLIDER("sfTrashShift parameter(s)/shift", fHslider3, 0.0f, -1e+02f, 1e+02f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("window", fHslider2, 75.0f, 1e+01f, 1e+03f, 1.0f);

	#define FAUST_LIST_ACTIVES(p) \
		p(CHECKBOX, ON/OFF, "sfTrashShift/ON/OFF", fCheckbox0, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(VERTICALSLIDER, Volume, "sfTrashShift/Volume", fVslider0, 1.0f, 0.0f, 2.0f, 0.001f) \
		p(HORIZONTALSLIDER, dry_wet, "sfTrashShift parameter(s)/dry_wet", fHslider1, 1e+02f, 0.0f, 1e+02f, 0.01f) \
		p(HORIZONTALSLIDER, gain, "sfTrashShift parameter(s)/gain", fHslider0, 1.0f, 0.0f, 1.0f, 0.001f) \
		p(HORIZONTALSLIDER, shift, "sfTrashShift parameter(s)/shift", fHslider3, 0.0f, -1e+02f, 1e+02f, 0.1f) \
		p(HORIZONTALSLIDER, window, "window", fHslider2, 75.0f, 1e+01f, 1e+03f, 1.0f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif
