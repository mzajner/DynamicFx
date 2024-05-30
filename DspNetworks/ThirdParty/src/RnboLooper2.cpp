/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#include "RNBO_Common.h"
#include "RNBO_AudioSignal.h"

namespace RNBO {


#define trunc(x) ((Int)(x))

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

class RnboLooper2 : public PatcherInterfaceImpl {
public:

RnboLooper2()
{
}

~RnboLooper2()
{
}

RnboLooper2* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
    getEngine()->flushClockEvents(this, 1646922831, false);
    getEngine()->flushClockEvents(this, 1114681293, false);
    getEngine()->flushClockEvents(this, -62043057, false);
    getEngine()->flushClockEvents(this, -1621164530, false);
}

template <typename T> void listquicksort(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template <typename T> Int listpartition(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template <typename T> void listswapelements(T& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

number samplerate() {
    return this->sr;
}

number minimum(number x, number y) {
    return (y < x ? y : x);
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

SampleIndex currentsampletime() {
    return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
}

number wrap(number x, number low, number high) {
    number lo;
    number hi;

    if (low == high)
        return low;

    if (low > high) {
        hi = low;
        lo = high;
    } else {
        lo = low;
        hi = high;
    }

    number range = hi - lo;

    if (x >= lo && x < hi)
        return x;

    if (range <= 0.000000001)
        return lo;

    long numWraps = (long)(trunc((x - lo) / range));
    numWraps = numWraps - ((x < lo ? 1 : 0));
    number result = x - range * numWraps;

    if (result >= hi)
        return result - range;
    else
        return result;
}

inline number safediv(number num, number denom) {
    return (denom == 0.0 ? 0.0 : num / denom);
}

number safepow(number base, number exponent) {
    return fixnan(rnbo_pow(base, exponent));
}

number scale(
    number x,
    number lowin,
    number hiin,
    number lowout,
    number highout,
    number pow
) {
    auto inscale = this->safediv(1., hiin - lowin);
    number outdiff = highout - lowout;
    number value = (x - lowin) * inscale;

    if (pow != 1) {
        if (value > 0)
            value = this->safepow(value, pow);
        else
            value = -this->safepow(-value, pow);
    }

    value = value * outdiff + lowout;
    return value;
}

Index vectorsize() {
    return this->vs;
}

ParameterValue fromnormalized(ParameterIndex index, ParameterValue normalizedValue) {
    return this->convertFromNormalizedParameterValue(index, normalizedValue);
}

MillisecondTime currenttime() {
    return this->_currentTime;
}

number tempo() {
    return this->getTopLevelPatcher()->globaltransport_getTempo(this->currenttime());
}

number mstobeats(number ms) {
    return ms * this->tempo() * 0.008 / (number)480;
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

Index getNumMidiInputPorts() const {
    return 1;
}

void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
    this->updateTime(time);
    this->ctlin_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_02_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_03_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_04_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
}

Index getNumMidiOutputPorts() const {
    return 0;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    SampleValue * out3 = (numOutputs >= 3 && outputs[2] ? outputs[2] : this->dummyBuffer);
    SampleValue * out4 = (numOutputs >= 4 && outputs[3] ? outputs[3] : this->dummyBuffer);
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);

    this->recordtilde_01_perform(
        this->recordtilde_01_record,
        this->recordtilde_01_begin,
        this->recordtilde_01_end,
        in1,
        in2,
        this->signals[0],
        n
    );

    this->snapshot_01_perform(this->signals[0], n);
    this->signalforwarder_01_perform(this->signals[0], out3, n);
    this->linetilde_01_perform(this->signals[0], n);
    this->linetilde_02_perform(this->signals[1], n);
    this->linetilde_03_perform(this->signals[2], n);

    this->groove_01_perform(
        this->signals[2],
        this->groove_01_begin,
        this->groove_01_end,
        this->signals[3],
        this->signals[4],
        this->signals[5],
        n
    );

    this->trapezoid_tilde_01_perform(
        this->signals[5],
        this->trapezoid_tilde_01_rampUp,
        this->trapezoid_tilde_01_rampDown,
        this->signals[2],
        n
    );

    this->dspexpr_08_perform(this->signals[4], this->signals[2], this->signals[6], n);
    this->dspexpr_07_perform(this->signals[6], this->signals[0], this->signals[4], n);
    this->dspexpr_06_perform(this->signals[4], this->signals[1], this->signals[6], n);
    this->dspexpr_02_perform(in2, this->signals[6], out2, n);
    this->dspexpr_05_perform(this->signals[3], this->signals[2], this->signals[6], n);
    this->dspexpr_04_perform(this->signals[6], this->signals[0], this->signals[2], n);
    this->dspexpr_03_perform(this->signals[2], this->signals[1], this->signals[0], n);
    this->dspexpr_01_perform(in1, this->signals[0], out1, n);
    this->signalforwarder_02_perform(this->signals[5], out4, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 7; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->groove_01_dspsetup(forceDSPSetup);
    this->data_01_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

void setProbingTarget(MessageTag id) {
    switch (id) {
    default:
        {
        this->setProbingIndex(-1);
        break;
        }
    }
}

void setProbingIndex(ProbingIndex ) {}

Index getProbingChannels(MessageTag outletId) const {
    RNBO_UNUSED(outletId);
    return 0;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->Looper);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 1;
}

void fillDataRef(DataRefIndex , DataRef& ) {}

void zeroDataRef(DataRef& ref) {
    ref->setZero();
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->updateTime(time);

    if (index == 0) {
        this->recordtilde_01_buffer = new Float64Buffer(this->Looper);
        this->groove_01_buffer = new Float64Buffer(this->Looper);
        this->data_01_buffer = new Float64Buffer(this->Looper);
        this->data_01_bufferUpdated();
    }
}

void initialize() {
    this->Looper = initDataRef("Looper", false, nullptr, "data");
    this->assign_defaults();
    this->setState();
    this->Looper->setIndex(0);
    this->recordtilde_01_buffer = new Float64Buffer(this->Looper);
    this->groove_01_buffer = new Float64Buffer(this->Looper);
    this->data_01_buffer = new Float64Buffer(this->Looper);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_01_getPresetValue(getSubState(preset, "BtnAutoRecord"));
    this->param_02_getPresetValue(getSubState(preset, "KnbRecordLength"));
    this->param_03_getPresetValue(getSubState(preset, "KnbVolume"));
    this->param_04_getPresetValue(getSubState(preset, "KnbTranspose"));
    this->param_05_getPresetValue(getSubState(preset, "BtnReverse"));
    this->param_06_getPresetValue(getSubState(preset, "KnbMode"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_01_setPresetValue(getSubState(preset, "BtnAutoRecord"));
    this->param_02_setPresetValue(getSubState(preset, "KnbRecordLength"));
    this->param_06_setPresetValue(getSubState(preset, "KnbMode"));
    this->param_04_setPresetValue(getSubState(preset, "KnbTranspose"));
    this->param_05_setPresetValue(getSubState(preset, "BtnReverse"));
    this->param_03_setPresetValue(getSubState(preset, "KnbVolume"));
}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false))
        {}
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time);

    if (this->globaltransport_setState(this->_currentTime, state, false))
        {}
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false))
        {}
}

void onSampleRateChanged(double ) {}

void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
    this->updateTime(time);

    if (this->globaltransport_setTimeSignature(this->_currentTime, numerator, denominator, false))
        {}
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time);

    switch (index) {
    case 0:
        {
        this->param_01_value_set(v);
        break;
        }
    case 1:
        {
        this->param_02_value_set(v);
        break;
        }
    case 2:
        {
        this->param_03_value_set(v);
        break;
        }
    case 3:
        {
        this->param_04_value_set(v);
        break;
        }
    case 4:
        {
        this->param_05_value_set(v);
        break;
        }
    case 5:
        {
        this->param_06_value_set(v);
        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->param_01_value;
        }
    case 1:
        {
        return this->param_02_value;
        }
    case 2:
        {
        return this->param_03_value;
        }
    case 3:
        {
        return this->param_04_value;
        }
    case 4:
        {
        return this->param_05_value;
        }
    case 5:
        {
        return this->param_06_value;
        }
    default:
        {
        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 6;
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "BtnAutoRecord";
        }
    case 1:
        {
        return "KnbRecordLength";
        }
    case 2:
        {
        return "KnbVolume";
        }
    case 3:
        {
        return "KnbTranspose";
        }
    case 4:
        {
        return "BtnReverse";
        }
    case 5:
        {
        return "KnbMode";
        }
    default:
        {
        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "BtnAutoRecord";
        }
    case 1:
        {
        return "KnbRecordLength";
        }
    case 2:
        {
        return "KnbVolume";
        }
    case 3:
        {
        return "KnbTranspose";
        }
    case 4:
        {
        return "BtnReverse";
        }
    case 5:
        {
        return "KnbMode";
        }
    default:
        {
        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 2;
            static const char * eVal0[] = {"On", "Off"};
            info->enumValues = eVal0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Auto Record";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1000;
            info->min = 0;
            info->max = 10000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -100;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Volume";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -24;
            info->max = 24;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Transp";
            info->unit = "st";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 4:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 2;
            static const char * eVal4[] = {"0", "1"};
            info->enumValues = eVal4;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Reverse";
            info->unit = "On/Off";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 2;
            info->min = 0;
            info->max = 2;
            info->exponent = 1;
            info->steps = 3;
            static const char * eVal5[] = {"Rec", "Play", "Stop"};
            info->enumValues = eVal5;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Mode";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
    case 4:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);

            {
                normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 2);
            }

            return normalizedValue;
        }
        }
    case 5:
        {
        {
            value = (value < 0 ? 0 : (value > 2 ? 2 : value));
            ParameterValue normalizedValue = (value - 0) / (2 - 0);

            {
                normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 3);
            }

            return normalizedValue;
        }
        }
    case 1:
        {
        {
            value = (value < 0 ? 0 : (value > 10000 ? 10000 : value));
            ParameterValue normalizedValue = (value - 0) / (10000 - 0);
            return normalizedValue;
        }
        }
    case 2:
        {
        {
            value = (value < -100 ? -100 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - -100) / (100 - -100);
            return normalizedValue;
        }
        }
    case 3:
        {
        {
            value = (value < -24 ? -24 : (value > 24 ? 24 : value));
            ParameterValue normalizedValue = (value - -24) / (24 - -24);
            return normalizedValue;
        }
        }
    default:
        {
        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 0:
    case 4:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                value = this->applyStepsToNormalizedParameterValue(value, 2);
            }

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 5:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                value = this->applyStepsToNormalizedParameterValue(value, 3);
            }

            {
                return 0 + value * (2 - 0);
            }
        }
        }
    case 1:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (10000 - 0);
            }
        }
        }
    case 2:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return -100 + value * (100 - -100);
            }
        }
        }
    case 3:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return -24 + value * (24 - -24);
            }
        }
        }
    default:
        {
        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_01_value_constrain(value);
        }
    case 1:
        {
        return this->param_02_value_constrain(value);
        }
    case 2:
        {
        return this->param_03_value_constrain(value);
        }
    case 3:
        {
        return this->param_04_value_constrain(value);
        }
    case 4:
        {
        return this->param_05_value_constrain(value);
        }
    case 5:
        {
        return this->param_06_value_constrain(value);
        }
    default:
        {
        return value;
        }
    }
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterChange(
            this->paramInitIndices[i],
            this->getParameterValue(this->paramInitIndices[i]),
            0
        );
    }
}

void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
    RNBO_UNUSED(hasValue);
    this->updateTime(time);

    switch (index) {
    case 1646922831:
        {
        this->snapshot_01_out_set(value);
        break;
        }
    case 1114681293:
        {
        this->linetilde_01_target_bang();
        break;
        }
    case -62043057:
        {
        this->linetilde_02_target_bang();
        break;
        }
    case -1621164530:
        {
        this->linetilde_03_target_bang();
        break;
        }
    }
}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time);
    this->processOutletAtCurrentTime(sender, index, value);
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    this->updateTime(time);

    switch (tag) {
    case TAG("valin"):
        {
        if (TAG("toggle_obj-86") == objectId)
            this->toggle_01_valin_set(payload);

        if (TAG("toggle_obj-33") == objectId)
            this->toggle_02_valin_set(payload);

        if (TAG("toggle_obj-144") == objectId)
            this->toggle_03_valin_set(payload);

        if (TAG("number_obj-119") == objectId)
            this->numberobj_01_valin_set(payload);

        if (TAG("number_obj-128") == objectId)
            this->numberobj_02_valin_set(payload);

        if (TAG("number_obj-126") == objectId)
            this->numberobj_03_valin_set(payload);

        if (TAG("number_obj-201") == objectId)
            this->numberobj_04_valin_set(payload);

        if (TAG("number_obj-203") == objectId)
            this->numberobj_05_valin_set(payload);

        if (TAG("number_obj-45") == objectId)
            this->numberobj_06_valin_set(payload);

        if (TAG("number_obj-78") == objectId)
            this->numberobj_07_valin_set(payload);

        if (TAG("number_obj-72") == objectId)
            this->numberobj_08_valin_set(payload);

        if (TAG("toggle_obj-81") == objectId)
            this->toggle_04_valin_set(payload);

        if (TAG("number_obj-77") == objectId)
            this->numberobj_09_valin_set(payload);

        if (TAG("toggle_obj-63") == objectId)
            this->toggle_05_valin_set(payload);

        if (TAG("number_obj-5") == objectId)
            this->numberobj_10_valin_set(payload);

        if (TAG("toggle_obj-73") == objectId)
            this->toggle_06_valin_set(payload);

        break;
        }
    case TAG("format"):
        {
        if (TAG("number_obj-119") == objectId)
            this->numberobj_01_format_set(payload);

        if (TAG("number_obj-128") == objectId)
            this->numberobj_02_format_set(payload);

        if (TAG("number_obj-126") == objectId)
            this->numberobj_03_format_set(payload);

        if (TAG("number_obj-201") == objectId)
            this->numberobj_04_format_set(payload);

        if (TAG("number_obj-203") == objectId)
            this->numberobj_05_format_set(payload);

        if (TAG("number_obj-45") == objectId)
            this->numberobj_06_format_set(payload);

        if (TAG("number_obj-78") == objectId)
            this->numberobj_07_format_set(payload);

        if (TAG("number_obj-72") == objectId)
            this->numberobj_08_format_set(payload);

        if (TAG("number_obj-77") == objectId)
            this->numberobj_09_format_set(payload);

        if (TAG("number_obj-5") == objectId)
            this->numberobj_10_format_set(payload);

        break;
        }
    }
}

void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    this->updateTime(time);

    switch (tag) {
    case TAG("bangin"):
        {
        if (TAG("button_obj-23") == objectId)
            this->button_01_bangin_bang();

        if (TAG("button_obj-64") == objectId)
            this->button_02_bangin_bang();

        if (TAG("button_obj-141") == objectId)
            this->button_03_bangin_bang();

        if (TAG("button_obj-26") == objectId)
            this->button_04_bangin_bang();

        if (TAG("button_obj-10") == objectId)
            this->button_05_bangin_bang();

        if (TAG("button_obj-71") == objectId)
            this->button_06_bangin_bang();

        if (TAG("button_obj-14") == objectId)
            this->button_07_bangin_bang();

        if (TAG("button_obj-15") == objectId)
            this->button_08_bangin_bang();

        if (TAG("button_obj-74") == objectId)
            this->button_09_bangin_bang();

        break;
        }
    }
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("valout"):
        {
        return "valout";
        }
    case TAG("toggle_obj-86"):
        {
        return "toggle_obj-86";
        }
    case TAG("bangout"):
        {
        return "bangout";
        }
    case TAG("button_obj-23"):
        {
        return "button_obj-23";
        }
    case TAG("button_obj-64"):
        {
        return "button_obj-64";
        }
    case TAG("toggle_obj-33"):
        {
        return "toggle_obj-33";
        }
    case TAG("toggle_obj-144"):
        {
        return "toggle_obj-144";
        }
    case TAG("number_obj-119"):
        {
        return "number_obj-119";
        }
    case TAG("setup"):
        {
        return "setup";
        }
    case TAG("button_obj-141"):
        {
        return "button_obj-141";
        }
    case TAG("number_obj-128"):
        {
        return "number_obj-128";
        }
    case TAG("number_obj-126"):
        {
        return "number_obj-126";
        }
    case TAG("number_obj-201"):
        {
        return "number_obj-201";
        }
    case TAG("number_obj-203"):
        {
        return "number_obj-203";
        }
    case TAG("number_obj-45"):
        {
        return "number_obj-45";
        }
    case TAG("number_obj-78"):
        {
        return "number_obj-78";
        }
    case TAG("number_obj-72"):
        {
        return "number_obj-72";
        }
    case TAG("toggle_obj-81"):
        {
        return "toggle_obj-81";
        }
    case TAG("number_obj-77"):
        {
        return "number_obj-77";
        }
    case TAG("toggle_obj-63"):
        {
        return "toggle_obj-63";
        }
    case TAG("button_obj-26"):
        {
        return "button_obj-26";
        }
    case TAG("button_obj-10"):
        {
        return "button_obj-10";
        }
    case TAG("number_obj-5"):
        {
        return "number_obj-5";
        }
    case TAG("button_obj-71"):
        {
        return "button_obj-71";
        }
    case TAG("button_obj-14"):
        {
        return "button_obj-14";
        }
    case TAG("button_obj-15"):
        {
        return "button_obj-15";
        }
    case TAG("toggle_obj-73"):
        {
        return "toggle_obj-73";
        }
    case TAG("button_obj-74"):
        {
        return "button_obj-74";
        }
    case TAG("valin"):
        {
        return "valin";
        }
    case TAG("bangin"):
        {
        return "bangin";
        }
    case TAG("format"):
        {
        return "format";
        }
    }

    return "";
}

MessageIndex getNumMessages() const {
    return 0;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {

    }

    return NullMessageInfo;
}

protected:

void param_01_value_set(number v) {
    v = this->param_01_value_constrain(v);
    this->param_01_value = v;
    this->sendParameter(0, false);

    if (this->param_01_value != this->param_01_lastValue) {
        this->getEngine()->presetTouched();
        this->param_01_lastValue = this->param_01_value;
    }

    this->toggle_02_value_number_set(v);
}

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(1, false);

    if (this->param_02_value != this->param_02_lastValue) {
        this->getEngine()->presetTouched();
        this->param_02_lastValue = this->param_02_value;
    }

    this->numberobj_03_value_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(2, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->numberobj_06_value_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(3, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->numberobj_08_value_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(4, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    this->toggle_04_value_number_set(v);
}

void param_06_value_set(number v) {
    v = this->param_06_value_constrain(v);
    this->param_06_value = v;
    this->sendParameter(5, false);

    if (this->param_06_value != this->param_06_lastValue) {
        this->getEngine()->presetTouched();
        this->param_06_lastValue = this->param_06_value;
    }

    this->numberobj_10_value_set(v);
}

void toggle_01_valin_set(number v) {
    this->toggle_01_value_number_set(v);
}

void button_01_bangin_bang() {
    this->button_01_bangval_bang();
}

void button_02_bangin_bang() {
    this->button_02_bangval_bang();
}

void snapshot_01_out_set(number v) {
    this->snapshot_01_out = v;
    this->select_01_input_number_set(v);
}

void toggle_02_valin_set(number v) {
    this->toggle_02_value_number_set(v);
}

void toggle_03_valin_set(number v) {
    this->toggle_03_value_number_set(v);
}

void numberobj_01_valin_set(number v) {
    this->numberobj_01_value_set(v);
}

void numberobj_01_format_set(number v) {
    this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void button_03_bangin_bang() {
    this->button_03_bangval_bang();
}

void numberobj_02_valin_set(number v) {
    this->numberobj_02_value_set(v);
}

void numberobj_02_format_set(number v) {
    this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_03_valin_set(number v) {
    this->numberobj_03_value_set(v);
}

void numberobj_03_format_set(number v) {
    this->numberobj_03_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_04_valin_set(number v) {
    this->numberobj_04_value_set(v);
}

void numberobj_04_format_set(number v) {
    this->numberobj_04_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_05_valin_set(number v) {
    this->numberobj_05_value_set(v);
}

void numberobj_05_format_set(number v) {
    this->numberobj_05_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_06_valin_set(number v) {
    this->numberobj_06_value_set(v);
}

void numberobj_06_format_set(number v) {
    this->numberobj_06_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_07_valin_set(number v) {
    this->numberobj_07_value_set(v);
}

void numberobj_07_format_set(number v) {
    this->numberobj_07_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_08_valin_set(number v) {
    this->numberobj_08_value_set(v);
}

void numberobj_08_format_set(number v) {
    this->numberobj_08_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void toggle_04_valin_set(number v) {
    this->toggle_04_value_number_set(v);
}

void numberobj_09_valin_set(number v) {
    this->numberobj_09_value_set(v);
}

void numberobj_09_format_set(number v) {
    this->numberobj_09_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void toggle_05_valin_set(number v) {
    this->toggle_05_value_number_set(v);
}

void button_04_bangin_bang() {
    this->button_04_bangval_bang();
}

void button_05_bangin_bang() {
    this->button_05_bangval_bang();
}

void numberobj_10_valin_set(number v) {
    this->numberobj_10_value_set(v);
}

void numberobj_10_format_set(number v) {
    this->numberobj_10_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void button_06_bangin_bang() {
    this->button_06_bangval_bang();
}

void button_07_bangin_bang() {
    this->button_07_bangval_bang();
}

void button_08_bangin_bang() {
    this->button_08_bangval_bang();
}

void toggle_06_valin_set(number v) {
    this->toggle_06_value_number_set(v);
}

void button_09_bangin_bang() {
    this->button_09_bangval_bang();
}

void linetilde_01_target_bang() {
    this->button_03_bangval_bang();
}

void linetilde_02_target_bang() {}

void linetilde_03_target_bang() {}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

Index getNumInputChannels() const {
    return 2;
}

Index getNumOutputChannels() const {
    return 4;
}

void allocateDataRefs() {
    this->data_01_buffer->requestSize(this->mstosamps(10000), 2);
    this->data_01_buffer->setSampleRate(this->sr);
    this->recordtilde_01_buffer = this->recordtilde_01_buffer->allocateIfNeeded();
    this->groove_01_buffer = this->groove_01_buffer->allocateIfNeeded();
    this->data_01_buffer = this->data_01_buffer->allocateIfNeeded();

    if (this->Looper->hasRequestedSize()) {
        if (this->Looper->wantsFill())
            this->zeroDataRef(this->Looper);

        this->getEngine()->sendDataRefUpdated(0);
    }
}

void initializeObjects() {
    this->numberobj_01_init();
    this->numberobj_02_init();
    this->numberobj_03_init();
    this->numberobj_04_init();
    this->numberobj_05_init();
    this->numberobj_06_init();
    this->numberobj_07_init();
    this->numberobj_08_init();
    this->data_01_init();
    this->numberobj_09_init();
    this->numberobj_10_init();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 4);
    }

    {
        this->scheduleParamInit(3, 2);
    }

    {
        this->scheduleParamInit(4, 3);
    }

    {
        this->scheduleParamInit(5, 1);
    }

    this->processParamInitEvents();
}

static number param_01_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)1 / (number)1;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep;
    }

    return v;
}

void switchobj_01_onoff_set(number v) {
    this->switchobj_01_onoff = v;
}

void expr_02_out1_set(number v) {
    this->expr_02_out1 = v;
    this->switchobj_01_onoff_set(this->expr_02_out1);
}

void expr_02_in1_set(number in1) {
    this->expr_02_in1 = in1;
    this->expr_02_out1_set(this->expr_02_in1 + this->expr_02_in2);//#map:+_obj-120:1
}

void trigger_01_out2_set(number v) {
    this->expr_02_in1_set(v);
}

void groove_01_end_set(number v) {
    this->groove_01_end = v;
}

void numberobj_01_output_set(number v) {
    this->groove_01_end_set(v);
}

void numberobj_01_value_set(number v) {
    this->numberobj_01_value_setter(v);
    v = this->numberobj_01_value;
    number localvalue = v;

    if (this->numberobj_01_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-119"), localvalue, this->_currentTime);
    this->numberobj_01_output_set(localvalue);
}

void switchobj_01_out_number_set(number v) {
    this->numberobj_01_value_set(v);
}

void switchobj_01_in2_number_set(number v) {
    if (this->switchobj_01_onoff == 2) {
        this->switchobj_01_out_number_set(v);
    }
}

void numberobj_03_output_set(number v) {
    this->switchobj_01_in2_number_set(v);
}

void numberobj_03_value_bang() {
    number v = this->numberobj_03_value;
    number localvalue = v;

    if (this->numberobj_03_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-126"), localvalue, this->_currentTime);
    this->numberobj_03_output_set(localvalue);
}

void switchobj_01_in1_number_set(number v) {
    if (this->switchobj_01_onoff == 1) {
        this->switchobj_01_out_number_set(v);
    }
}

void numberobj_02_output_set(number v) {
    this->switchobj_01_in1_number_set(v);
}

void numberobj_02_value_bang() {
    number v = this->numberobj_02_value;
    number localvalue = v;

    if (this->numberobj_02_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-128"), localvalue, this->_currentTime);
    this->numberobj_02_output_set(localvalue);
}

void trigger_01_out1_bang() {
    this->numberobj_03_value_bang();
    this->numberobj_02_value_bang();
}

void trigger_01_input_number_set(number v) {
    this->trigger_01_out2_set(trunc(v));
    this->trigger_01_out1_bang();
}

void recordtilde_01_record_set(number v) {
    this->recordtilde_01_record = v;
}

void toggle_01_output_set(number v) {
    this->recordtilde_01_record_set(v);
}

void toggle_01_value_number_set(number v) {
    this->toggle_01_value_number_setter(v);
    v = this->toggle_01_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-86"), v, this->_currentTime);
    this->toggle_01_output_set(v);
}

void expr_01_out1_set(number v) {
    this->expr_01_out1 = v;
    this->toggle_01_value_number_set(this->expr_01_out1);
}

void expr_01_in1_set(number in1) {
    this->expr_01_in1 = in1;
    this->expr_01_out1_set(this->expr_01_in1 == 0);//#map:not_obj-129:1
}

void toggle_02_output_set(number v) {
    this->trigger_01_input_number_set(v);
    this->expr_01_in1_set(v);
}

void toggle_02_value_number_set(number v) {
    this->toggle_02_value_number_setter(v);
    v = this->toggle_02_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-33"), v, this->_currentTime);
    this->toggle_02_output_set(v);
}

static number param_02_value_constrain(number v) {
    v = (v > 10000 ? 10000 : (v < 0 ? 0 : v));
    return v;
}

void numberobj_03_value_set(number v) {
    this->numberobj_03_value_setter(v);
    v = this->numberobj_03_value;
    number localvalue = v;

    if (this->numberobj_03_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-126"), localvalue, this->_currentTime);
    this->numberobj_03_output_set(localvalue);
}

static number param_03_value_constrain(number v) {
    v = (v > 100 ? 100 : (v < -100 ? -100 : v));
    return v;
}

void linetilde_02_time_set(number v) {
    this->linetilde_02_time = v;
}

void linetilde_02_segments_set(const list& v) {
    this->linetilde_02_segments = jsCreateListCopy(v);

    if ((bool)(v->length)) {
        if (v->length == 1 && this->linetilde_02_time == 0) {
            this->linetilde_02_activeRamps->length = 0;
            this->linetilde_02_currentValue = v[0];
        } else {
            auto currentTime = this->currentsampletime();
            number lastRampValue = this->linetilde_02_currentValue;
            number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;

            for (Index i = 0; i < this->linetilde_02_activeRamps->length; i += 3) {
                rampEnd = this->linetilde_02_activeRamps[(Index)(i + 2)];

                if (rampEnd > currentTime) {
                    this->linetilde_02_activeRamps[(Index)(i + 2)] = currentTime;
                    number diff = rampEnd - currentTime;
                    number valueDiff = diff * this->linetilde_02_activeRamps[(Index)(i + 1)];
                    lastRampValue = this->linetilde_02_activeRamps[(Index)i] - valueDiff;
                    this->linetilde_02_activeRamps[(Index)i] = lastRampValue;
                    this->linetilde_02_activeRamps->length = i + 3;
                    rampEnd = currentTime;
                } else {
                    lastRampValue = this->linetilde_02_activeRamps[(Index)i];
                }
            }

            if (rampEnd < currentTime) {
                this->linetilde_02_activeRamps->push(lastRampValue);
                this->linetilde_02_activeRamps->push(0);
                this->linetilde_02_activeRamps->push(currentTime);
            }

            number lastRampEnd = currentTime;

            for (Index i = 0; i < v->length; i += 2) {
                number destinationValue = v[(Index)i];
                number inc = 0;
                number rampTimeInSamples;

                if (v->length > i + 1) {
                    rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);

                    if ((bool)(this->linetilde_02_keepramp)) {
                        this->linetilde_02_time_set(v[(Index)(i + 1)]);
                    }
                } else {
                    rampTimeInSamples = this->mstosamps(this->linetilde_02_time);
                }

                if (rampTimeInSamples <= 0) {
                    rampTimeInSamples = 1;
                }

                inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                lastRampEnd += rampTimeInSamples;
                this->linetilde_02_activeRamps->push(destinationValue);
                this->linetilde_02_activeRamps->push(inc);
                this->linetilde_02_activeRamps->push(lastRampEnd);
                lastRampValue = destinationValue;
            }
        }
    }
}

void numberobj_04_output_set(number v) {
    {
        list converted = {v};
        this->linetilde_02_segments_set(converted);
    }
}

void numberobj_04_value_set(number v) {
    this->numberobj_04_value_setter(v);
    v = this->numberobj_04_value;
    number localvalue = v;

    if (this->numberobj_04_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-201"), localvalue, this->_currentTime);
    this->numberobj_04_output_set(localvalue);
}

void expr_03_out1_set(number v) {
    this->expr_03_out1 = v;
    this->numberobj_04_value_set(this->expr_03_out1);
}

void expr_03_in1_set(number in1) {
    this->expr_03_in1 = in1;
    this->expr_03_out1_set(rnbo_pow(10, this->expr_03_in1 * 0.05));//#map:dbtoa_obj-202:1
}

void numberobj_05_output_set(number v) {
    this->expr_03_in1_set(v);
}

void numberobj_05_value_set(number v) {
    this->numberobj_05_value_setter(v);
    v = this->numberobj_05_value;
    number localvalue = v;

    if (this->numberobj_05_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-203"), localvalue, this->_currentTime);
    this->numberobj_05_output_set(localvalue);
}

void scale_01_out_set(const list& v) {
    this->scale_01_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_05_value_set(converted);
    }
}

void scale_01_input_set(const list& v) {
    this->scale_01_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_01_inlow,
            this->scale_01_inhigh,
            this->scale_01_outlow,
            this->scale_01_outhigh,
            this->scale_01_power
        ));
    }

    this->scale_01_out_set(tmp);
}

void numberobj_06_output_set(number v) {
    {
        list converted = {v};
        this->scale_01_input_set(converted);
    }
}

void numberobj_06_value_set(number v) {
    this->numberobj_06_value_setter(v);
    v = this->numberobj_06_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < -100) {
        localvalue = -100;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_06_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-45"), localvalue, this->_currentTime);
    this->numberobj_06_output_set(localvalue);
}

static number param_04_value_constrain(number v) {
    v = (v > 24 ? 24 : (v < -24 ? -24 : v));
    return v;
}

void linetilde_03_time_set(number v) {
    this->linetilde_03_time = v;
}

void linetilde_03_segments_set(const list& v) {
    this->linetilde_03_segments = jsCreateListCopy(v);

    if ((bool)(v->length)) {
        if (v->length == 1 && this->linetilde_03_time == 0) {
            this->linetilde_03_activeRamps->length = 0;
            this->linetilde_03_currentValue = v[0];
        } else {
            auto currentTime = this->currentsampletime();
            number lastRampValue = this->linetilde_03_currentValue;
            number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;

            for (Index i = 0; i < this->linetilde_03_activeRamps->length; i += 3) {
                rampEnd = this->linetilde_03_activeRamps[(Index)(i + 2)];

                if (rampEnd > currentTime) {
                    this->linetilde_03_activeRamps[(Index)(i + 2)] = currentTime;
                    number diff = rampEnd - currentTime;
                    number valueDiff = diff * this->linetilde_03_activeRamps[(Index)(i + 1)];
                    lastRampValue = this->linetilde_03_activeRamps[(Index)i] - valueDiff;
                    this->linetilde_03_activeRamps[(Index)i] = lastRampValue;
                    this->linetilde_03_activeRamps->length = i + 3;
                    rampEnd = currentTime;
                } else {
                    lastRampValue = this->linetilde_03_activeRamps[(Index)i];
                }
            }

            if (rampEnd < currentTime) {
                this->linetilde_03_activeRamps->push(lastRampValue);
                this->linetilde_03_activeRamps->push(0);
                this->linetilde_03_activeRamps->push(currentTime);
            }

            number lastRampEnd = currentTime;

            for (Index i = 0; i < v->length; i += 2) {
                number destinationValue = v[(Index)i];
                number inc = 0;
                number rampTimeInSamples;

                if (v->length > i + 1) {
                    rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);

                    if ((bool)(this->linetilde_03_keepramp)) {
                        this->linetilde_03_time_set(v[(Index)(i + 1)]);
                    }
                } else {
                    rampTimeInSamples = this->mstosamps(this->linetilde_03_time);
                }

                if (rampTimeInSamples <= 0) {
                    rampTimeInSamples = 1;
                }

                inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                lastRampEnd += rampTimeInSamples;
                this->linetilde_03_activeRamps->push(destinationValue);
                this->linetilde_03_activeRamps->push(inc);
                this->linetilde_03_activeRamps->push(lastRampEnd);
                lastRampValue = destinationValue;
            }
        }
    }
}

void numberobj_07_output_set(number v) {
    {
        list converted = {v};
        this->linetilde_03_segments_set(converted);
    }
}

void numberobj_07_value_set(number v) {
    this->numberobj_07_value_setter(v);
    v = this->numberobj_07_value;
    number localvalue = v;

    if (this->numberobj_07_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-78"), localvalue, this->_currentTime);
    this->numberobj_07_output_set(localvalue);
}

void expr_06_out1_set(number v) {
    this->expr_06_out1 = v;
    this->numberobj_07_value_set(this->expr_06_out1);
}

void expr_06_in1_set(number in1) {
    this->expr_06_in1 = in1;
    this->expr_06_out1_set(this->expr_06_in1 * this->expr_06_in2);//#map:*_obj-75:1
}

void expr_07_out1_set(number v) {
    this->expr_07_out1 = v;
    this->expr_06_in1_set(this->expr_07_out1);
}

void expr_07_in1_set(number in1) {
    this->expr_07_in1 = in1;
    this->expr_07_out1_set(fixnan(rnbo_pow(2, this->expr_07_in1 / (number)12)));//#map:expr_obj-76:1
}

void numberobj_08_output_set(number v) {
    this->expr_07_in1_set(v);
}

void numberobj_08_value_set(number v) {
    this->numberobj_08_value_setter(v);
    v = this->numberobj_08_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < -24) {
        localvalue = -24;
    }

    if ((bool)(true) && localvalue > 24) {
        localvalue = 24;
    }

    if (this->numberobj_08_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-72"), localvalue, this->_currentTime);
    this->numberobj_08_output_set(localvalue);
}

static number param_05_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)1 / (number)1;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep;
    }

    return v;
}

void expr_06_in2_set(number v) {
    this->expr_06_in2 = v;
    this->expr_06_in1_set(this->expr_06_in1);
}

void numberobj_09_output_set(number v) {
    this->expr_06_in2_set(v);
}

void numberobj_09_value_set(number v) {
    this->numberobj_09_value_setter(v);
    v = this->numberobj_09_value;
    number localvalue = v;

    if (this->numberobj_09_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-77"), localvalue, this->_currentTime);
    this->numberobj_09_output_set(localvalue);
}

void listlookup_01_out_set(const list& v) {
    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_09_value_set(converted);
    }
}

void listlookup_01_input_set(const list& v) {
    this->listlookup_01_input = jsCreateListCopy(v);
    list tmp = list();

    for (Index i = 0; i < v->length; i++) {
        long j = (long)(rnbo_fround(v[(Index)i] * 1 / (number)1) * 1);

        if (j >= 0 && (Index)(j) < this->listlookup_01_lookup->length)
            tmp->push(this->listlookup_01_lookup[(Index)j]);
    }

    if ((bool)(tmp->length))
        this->listlookup_01_out_set(tmp);
}

void toggle_04_output_set(number v) {
    {
        list converted = {v};
        this->listlookup_01_input_set(converted);
    }
}

void toggle_04_value_number_set(number v) {
    this->toggle_04_value_number_setter(v);
    v = this->toggle_04_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-81"), v, this->_currentTime);
    this->toggle_04_output_set(v);
}

static number param_06_value_constrain(number v) {
    v = (v > 2 ? 2 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)2 / (number)2;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep;
    }

    return v;
}

void onebang_01_reset_bang() {
    this->onebang_01_allow = true;
}

void trigger_03_out2_bang() {
    this->onebang_01_reset_bang();
}

void linetilde_01_time_set(number v) {
    this->linetilde_01_time = v;
}

void linetilde_01_segments_set(const list& v) {
    this->linetilde_01_segments = jsCreateListCopy(v);

    if ((bool)(v->length)) {
        if (v->length == 1 && this->linetilde_01_time == 0) {
            this->linetilde_01_activeRamps->length = 0;
            this->linetilde_01_currentValue = v[0];
        } else {
            auto currentTime = this->currentsampletime();
            number lastRampValue = this->linetilde_01_currentValue;
            number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;

            for (Index i = 0; i < this->linetilde_01_activeRamps->length; i += 3) {
                rampEnd = this->linetilde_01_activeRamps[(Index)(i + 2)];

                if (rampEnd > currentTime) {
                    this->linetilde_01_activeRamps[(Index)(i + 2)] = currentTime;
                    number diff = rampEnd - currentTime;
                    number valueDiff = diff * this->linetilde_01_activeRamps[(Index)(i + 1)];
                    lastRampValue = this->linetilde_01_activeRamps[(Index)i] - valueDiff;
                    this->linetilde_01_activeRamps[(Index)i] = lastRampValue;
                    this->linetilde_01_activeRamps->length = i + 3;
                    rampEnd = currentTime;
                } else {
                    lastRampValue = this->linetilde_01_activeRamps[(Index)i];
                }
            }

            if (rampEnd < currentTime) {
                this->linetilde_01_activeRamps->push(lastRampValue);
                this->linetilde_01_activeRamps->push(0);
                this->linetilde_01_activeRamps->push(currentTime);
            }

            number lastRampEnd = currentTime;

            for (Index i = 0; i < v->length; i += 2) {
                number destinationValue = v[(Index)i];
                number inc = 0;
                number rampTimeInSamples;

                if (v->length > i + 1) {
                    rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);

                    if ((bool)(this->linetilde_01_keepramp)) {
                        this->linetilde_01_time_set(v[(Index)(i + 1)]);
                    }
                } else {
                    rampTimeInSamples = this->mstosamps(this->linetilde_01_time);
                }

                if (rampTimeInSamples <= 0) {
                    rampTimeInSamples = 1;
                }

                inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                lastRampEnd += rampTimeInSamples;
                this->linetilde_01_activeRamps->push(destinationValue);
                this->linetilde_01_activeRamps->push(inc);
                this->linetilde_01_activeRamps->push(lastRampEnd);
                lastRampValue = destinationValue;
            }
        }
    }
}

void toggle_03_output_set(number v) {
    {
        list converted = {v};
        this->linetilde_01_segments_set(converted);
    }
}

void toggle_03_value_number_set(number v) {
    this->toggle_03_value_number_setter(v);
    v = this->toggle_03_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-144"), v, this->_currentTime);
    this->toggle_03_output_set(v);
}

void receive_04_output_number_set(number v) {
    this->receive_04_output_number = v;
    this->toggle_03_value_number_set(v);
}

void send_04_input_number_set(number v) {
    this->send_04_input_number = v;
    this->receive_04_output_number_set(v);
}

void toggle_06_output_set(number v) {
    this->send_04_input_number_set(v);
}

void toggle_06_value_number_set(number v) {
    this->toggle_06_value_number_setter(v);
    v = this->toggle_06_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-73"), v, this->_currentTime);
    this->toggle_06_output_set(v);
}

void trigger_03_out1_set(number v) {
    this->toggle_06_value_number_set(v);
}

void trigger_03_input_bang_bang() {
    this->trigger_03_out2_bang();
    this->trigger_03_out1_set(0);
}

void button_05_output_bang() {
    this->trigger_03_input_bang_bang();
}

void button_05_bangval_bang() {
    this->getEngine()->sendBangMessage(TAG("bangout"), TAG("button_obj-10"), this->_currentTime);;
    this->button_05_output_bang();
}

void select_02_match1_bang() {
    this->button_05_bangval_bang();
}

void receive_02_output_number_set(number v) {
    this->receive_02_output_number = v;
    this->toggle_01_value_number_set(v);
}

void send_02_input_number_set(number v) {
    this->send_02_input_number = v;
    this->receive_02_output_number_set(v);
}

void toggle_05_output_set(number v) {
    this->send_02_input_number_set(v);
}

void toggle_05_value_number_set(number v) {
    this->toggle_05_value_number_setter(v);
    v = this->toggle_05_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-63"), v, this->_currentTime);
    this->toggle_05_output_set(v);
}

void trigger_05_out3_set(number v) {
    this->toggle_05_value_number_set(v);
}

void onebang_02_reset_bang() {
    this->onebang_02_allow = true;
}

void trigger_05_out2_bang() {
    this->onebang_02_reset_bang();
}

void trigger_05_out1_set(number v) {
    this->toggle_06_value_number_set(v);
}

void trigger_05_input_bang_bang() {
    this->trigger_05_out3_set(0);
    this->trigger_05_out2_bang();
    this->trigger_05_out1_set(0);
}

void button_07_output_bang() {
    this->trigger_05_input_bang_bang();
}

void button_07_bangval_bang() {
    this->getEngine()->sendBangMessage(TAG("bangout"), TAG("button_obj-14"), this->_currentTime);;
    this->button_07_output_bang();
}

void select_02_match2_bang() {
    this->button_07_bangval_bang();
}

void trigger_06_out3_set(number v) {
    this->toggle_05_value_number_set(v);
}

void onebang_03_reset_bang() {
    this->onebang_03_allow = true;
}

void trigger_06_out2_bang() {
    this->onebang_03_reset_bang();
}

void trigger_06_out1_set(number v) {
    this->toggle_06_value_number_set(v);
}

void trigger_06_input_bang_bang() {
    this->trigger_06_out3_set(0);
    this->trigger_06_out2_bang();
    this->trigger_06_out1_set(0);
}

void button_08_output_bang() {
    this->trigger_06_input_bang_bang();
}

void button_08_bangval_bang() {
    this->getEngine()->sendBangMessage(TAG("bangout"), TAG("button_obj-15"), this->_currentTime);;
    this->button_08_output_bang();
}

void select_02_match3_bang() {
    this->button_08_bangval_bang();
}

void select_02_nomatch_number_set(number ) {}

void select_02_input_number_set(number v) {
    if (v == this->select_02_test1)
        this->select_02_match1_bang();
    else if (v == this->select_02_test2)
        this->select_02_match2_bang();
    else if (v == this->select_02_test3)
        this->select_02_match3_bang();
    else
        this->select_02_nomatch_number_set(v);
}

void numberobj_10_output_set(number v) {
    this->select_02_input_number_set(v);
}

void numberobj_10_value_set(number v) {
    this->numberobj_10_value_setter(v);
    v = this->numberobj_10_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 2) {
        localvalue = 2;
    }

    if (this->numberobj_10_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-5"), localvalue, this->_currentTime);
    this->numberobj_10_output_set(localvalue);
}

void groove_01_rate_bang_bang() {
    this->groove_01_changeIncomingInSamples = this->sampleOffsetIntoNextAudioBuffer + 1;
    this->groove_01_incomingChange = 1;
}

void button_01_output_bang() {
    this->groove_01_rate_bang_bang();
}

void button_01_bangval_bang() {
    this->getEngine()->sendBangMessage(TAG("bangout"), TAG("button_obj-23"), this->_currentTime);;
    this->button_01_output_bang();
}

void groove_01_stop_bang() {
    this->groove_01_changeIncomingInSamples = this->sampleOffsetIntoNextAudioBuffer + 1;
    this->groove_01_incomingChange = 0;
}

void button_02_output_bang() {
    this->groove_01_stop_bang();
}

void button_02_bangval_bang() {
    this->getEngine()->sendBangMessage(TAG("bangout"), TAG("button_obj-64"), this->_currentTime);;
    this->button_02_output_bang();
}

void select_01_match1_bang() {}

void numberobj_02_value_set(number v) {
    this->numberobj_02_value_setter(v);
    v = this->numberobj_02_value;
    number localvalue = v;

    if (this->numberobj_02_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-128"), localvalue, this->_currentTime);
    this->numberobj_02_output_set(localvalue);
}

void select_01_nomatch_number_set(number v) {
    this->numberobj_02_value_set(v);
}

void select_01_input_number_set(number v) {
    if (v == this->select_01_test1)
        this->select_01_match1_bang();
    else
        this->select_01_nomatch_number_set(v);
}

void receive_03_output_bang_bang() {
    this->button_02_bangval_bang();
}

void send_05_input_bang_bang() {
    this->receive_03_output_bang_bang();
}

void button_09_output_bang() {
    this->send_05_input_bang_bang();
}

void button_09_bangval_bang() {
    this->getEngine()->sendBangMessage(TAG("bangout"), TAG("button_obj-74"), this->_currentTime);;
    this->button_09_output_bang();
}

void onebang_03_out1_bang() {
    this->button_09_bangval_bang();
}

void onebang_03_out2_bang() {}

void onebang_03_input_bang() {
    if ((bool)(this->onebang_03_allow)) {
        this->onebang_03_out1_bang();
        this->onebang_03_allow = false;
    } else
        this->onebang_03_out2_bang();
}

void receive_01_output_bang_bang() {
    this->button_01_bangval_bang();
}

void send_03_input_bang_bang() {
    this->receive_01_output_bang_bang();
}

void button_06_output_bang() {
    this->send_03_input_bang_bang();
}

void button_06_bangval_bang() {
    this->getEngine()->sendBangMessage(TAG("bangout"), TAG("button_obj-71"), this->_currentTime);;
    this->button_06_output_bang();
}

void trigger_04_out2_set(number v) {
    RNBO_UNUSED(v);
    this->button_06_bangval_bang();
}

void trigger_04_out1_set(number v) {
    this->toggle_06_value_number_set(v);
}

void trigger_04_input_bang_bang() {
    this->trigger_04_out2_set(1);
    this->trigger_04_out1_set(1);
}

void onebang_02_out1_bang() {
    this->trigger_04_input_bang_bang();
}

void onebang_02_out2_bang() {}

void onebang_02_input_bang() {
    if ((bool)(this->onebang_02_allow)) {
        this->onebang_02_out1_bang();
        this->onebang_02_allow = false;
    } else
        this->onebang_02_out2_bang();
}

void trigger_02_out2_bang() {
    this->button_09_bangval_bang();
}

void trigger_02_out1_set(number v) {
    this->toggle_05_value_number_set(v);
}

void trigger_02_input_bang_bang() {
    this->trigger_02_out2_bang();
    this->trigger_02_out1_set(1);
}

void onebang_01_out1_bang() {
    this->trigger_02_input_bang_bang();
}

void onebang_01_out2_bang() {}

void onebang_01_input_bang() {
    if ((bool)(this->onebang_01_allow)) {
        this->onebang_01_out1_bang();
        this->onebang_01_allow = false;
    } else
        this->onebang_01_out2_bang();
}

void button_04_output_bang() {
    this->onebang_03_input_bang();
    this->onebang_02_input_bang();
    this->onebang_01_input_bang();
}

void button_04_bangval_bang() {
    this->getEngine()->sendBangMessage(TAG("bangout"), TAG("button_obj-26"), this->_currentTime);;
    this->button_04_output_bang();
}

void receive_05_output_bang_bang() {
    this->button_04_bangval_bang();
}

void send_01_input_bang_bang() {
    this->receive_05_output_bang_bang();
}

void button_03_output_bang() {
    this->send_01_input_bang_bang();
}

void button_03_bangval_bang() {
    this->getEngine()->sendBangMessage(TAG("bangout"), TAG("button_obj-141"), this->_currentTime);;
    this->button_03_output_bang();
}

void ctlin_01_outchannel_set(number ) {}

void ctlin_01_outcontroller_set(number ) {}

void fromnormalized_01_output_set(number v) {
    this->param_03_value_set(v);
}

void fromnormalized_01_input_set(number v) {
    this->fromnormalized_01_output_set(this->fromnormalized(2, v));
}

void expr_04_out1_set(number v) {
    this->expr_04_out1 = v;
    this->fromnormalized_01_input_set(this->expr_04_out1);
}

void expr_04_in1_set(number in1) {
    this->expr_04_in1 = in1;
    this->expr_04_out1_set(this->expr_04_in1 * this->expr_04_in2);//#map:expr_04:1
}

void ctlin_01_value_set(number v) {
    this->expr_04_in1_set(v);
}

void ctlin_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_01_channel || this->ctlin_01_channel == -1) && (data[1] == this->ctlin_01_controller || this->ctlin_01_controller == -1)) {
        this->ctlin_01_outchannel_set(channel);
        this->ctlin_01_outcontroller_set(data[1]);
        this->ctlin_01_value_set(data[2]);
        this->ctlin_01_status = 0;
    }
}

void ctlin_02_outchannel_set(number ) {}

void ctlin_02_outcontroller_set(number ) {}

void fromnormalized_02_output_set(number v) {
    this->param_04_value_set(v);
}

void fromnormalized_02_input_set(number v) {
    this->fromnormalized_02_output_set(this->fromnormalized(3, v));
}

void expr_05_out1_set(number v) {
    this->expr_05_out1 = v;
    this->fromnormalized_02_input_set(this->expr_05_out1);
}

void expr_05_in1_set(number in1) {
    this->expr_05_in1 = in1;
    this->expr_05_out1_set(this->expr_05_in1 * this->expr_05_in2);//#map:expr_05:1
}

void ctlin_02_value_set(number v) {
    this->expr_05_in1_set(v);
}

void ctlin_02_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_02_channel || this->ctlin_02_channel == -1) && (data[1] == this->ctlin_02_controller || this->ctlin_02_controller == -1)) {
        this->ctlin_02_outchannel_set(channel);
        this->ctlin_02_outcontroller_set(data[1]);
        this->ctlin_02_value_set(data[2]);
        this->ctlin_02_status = 0;
    }
}

void ctlin_03_outchannel_set(number ) {}

void ctlin_03_outcontroller_set(number ) {}

void fromnormalized_03_output_set(number v) {
    this->param_05_value_set(v);
}

void fromnormalized_03_input_set(number v) {
    this->fromnormalized_03_output_set(this->fromnormalized(4, v));
}

void expr_08_out1_set(number v) {
    this->expr_08_out1 = v;
    this->fromnormalized_03_input_set(this->expr_08_out1);
}

void expr_08_in1_set(number in1) {
    this->expr_08_in1 = in1;
    this->expr_08_out1_set(this->expr_08_in1 * this->expr_08_in2);//#map:expr_08:1
}

void ctlin_03_value_set(number v) {
    this->expr_08_in1_set(v);
}

void ctlin_03_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_03_channel || this->ctlin_03_channel == -1) && (data[1] == this->ctlin_03_controller || this->ctlin_03_controller == -1)) {
        this->ctlin_03_outchannel_set(channel);
        this->ctlin_03_outcontroller_set(data[1]);
        this->ctlin_03_value_set(data[2]);
        this->ctlin_03_status = 0;
    }
}

void ctlin_04_outchannel_set(number ) {}

void ctlin_04_outcontroller_set(number ) {}

void fromnormalized_04_output_set(number v) {
    this->param_06_value_set(v);
}

void fromnormalized_04_input_set(number v) {
    this->fromnormalized_04_output_set(this->fromnormalized(5, v));
}

void expr_09_out1_set(number v) {
    this->expr_09_out1 = v;
    this->fromnormalized_04_input_set(this->expr_09_out1);
}

void expr_09_in1_set(number in1) {
    this->expr_09_in1 = in1;
    this->expr_09_out1_set(this->expr_09_in1 * this->expr_09_in2);//#map:expr_09:1
}

void ctlin_04_value_set(number v) {
    this->expr_09_in1_set(v);
}

void ctlin_04_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_04_channel || this->ctlin_04_channel == -1) && (data[1] == this->ctlin_04_controller || this->ctlin_04_controller == -1)) {
        this->ctlin_04_outchannel_set(channel);
        this->ctlin_04_outcontroller_set(data[1]);
        this->ctlin_04_value_set(data[2]);
        this->ctlin_04_status = 0;
    }
}

void recordtilde_01_perform(
    number record,
    number begin,
    number end,
    const SampleValue * input1,
    const SampleValue * input2,
    SampleValue * sync,
    Index n
) {
    RNBO_UNUSED(input2);
    RNBO_UNUSED(input1);
    RNBO_UNUSED(end);
    RNBO_UNUSED(begin);
    auto __recordtilde_01_loop = this->recordtilde_01_loop;
    auto __recordtilde_01_wIndex = this->recordtilde_01_wIndex;
    auto __recordtilde_01_lastRecord = this->recordtilde_01_lastRecord;
    auto __recordtilde_01_buffer = this->recordtilde_01_buffer;
    ConstSampleArray<2> input = {input1, input2};
    number bufferSize = __recordtilde_01_buffer->getSize();
    number srInv = (number)1 / this->samplerate();

    if (bufferSize > 0) {
        number maxChannel = __recordtilde_01_buffer->getChannels();
        number touched = false;

        for (Index i = 0; i < n; i++) {
            number loopBegin = 0;
            number loopEnd = bufferSize;

            if (loopEnd > loopBegin) {
                {
                    if ((bool)(record) && __recordtilde_01_lastRecord != record) {
                        __recordtilde_01_wIndex = loopBegin;
                    }
                }

                if (record != 0 && __recordtilde_01_wIndex < loopEnd) {
                    for (number channel = 0; channel < 2; channel++) {
                        number effectiveChannel = channel + 0;

                        if (effectiveChannel < maxChannel) {
                            __recordtilde_01_buffer->setSample(channel, __recordtilde_01_wIndex, input[(Index)channel][(Index)i]);
                            touched = true;
                        } else
                            break;
                    }

                    __recordtilde_01_wIndex++;

                    if ((bool)(__recordtilde_01_loop) && __recordtilde_01_wIndex >= loopEnd) {
                        __recordtilde_01_wIndex = loopBegin;
                    }

                    {
                        sync[(Index)i] = this->recordtilde_01_calcSync(__recordtilde_01_wIndex, loopBegin, loopEnd - loopBegin, bufferSize, srInv);
                    }
                } else {
                    sync[(Index)i] = 0;
                }

                {
                    __recordtilde_01_lastRecord = record;
                }
            }
        }

        if ((bool)(touched)) {
            __recordtilde_01_buffer->setTouched(true);
            __recordtilde_01_buffer->setSampleRate(this->samplerate());
        }
    }

    this->recordtilde_01_lastRecord = __recordtilde_01_lastRecord;
    this->recordtilde_01_wIndex = __recordtilde_01_wIndex;
}

void snapshot_01_perform(const SampleValue * input_signal, Index n) {
    auto __snapshot_01_lastValue = this->snapshot_01_lastValue;
    auto __snapshot_01_calc = this->snapshot_01_calc;
    auto __snapshot_01_count = this->snapshot_01_count;
    auto __snapshot_01_nextTime = this->snapshot_01_nextTime;
    auto __snapshot_01_interval = this->snapshot_01_interval;
    number timeInSamples = this->msToSamps(__snapshot_01_interval, this->sr);

    if (__snapshot_01_interval > 0) {
        for (Index i = 0; i < n; i++) {
            if (__snapshot_01_nextTime <= __snapshot_01_count + (SampleIndex)(i)) {
                {
                    __snapshot_01_calc = input_signal[(Index)i];
                }

                this->getEngine()->scheduleClockEventWithValue(
                    this,
                    1646922831,
                    this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                    __snapshot_01_calc
                );;

                __snapshot_01_calc = 0;
                __snapshot_01_nextTime += timeInSamples;
            }
        }

        __snapshot_01_count += this->vs;
    }

    __snapshot_01_lastValue = input_signal[(Index)(n - 1)];
    this->snapshot_01_nextTime = __snapshot_01_nextTime;
    this->snapshot_01_count = __snapshot_01_count;
    this->snapshot_01_calc = __snapshot_01_calc;
    this->snapshot_01_lastValue = __snapshot_01_lastValue;
}

void signalforwarder_01_perform(const SampleValue * input, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input[(Index)i];
    }
}

void linetilde_01_perform(SampleValue * out, Index n) {
    auto __linetilde_01_time = this->linetilde_01_time;
    auto __linetilde_01_keepramp = this->linetilde_01_keepramp;
    auto __linetilde_01_currentValue = this->linetilde_01_currentValue;
    Index i = 0;

    if ((bool)(this->linetilde_01_activeRamps->length)) {
        while ((bool)(this->linetilde_01_activeRamps->length) && i < n) {
            number destinationValue = this->linetilde_01_activeRamps[0];
            number inc = this->linetilde_01_activeRamps[1];
            number rampTimeInSamples = this->linetilde_01_activeRamps[2] - this->audioProcessSampleCount - i;
            number val = __linetilde_01_currentValue;

            while (rampTimeInSamples > 0 && i < n) {
                out[(Index)i] = val;
                val += inc;
                i++;
                rampTimeInSamples--;
            }

            if (rampTimeInSamples <= 0) {
                val = destinationValue;
                this->linetilde_01_activeRamps->splice(0, 3);

                if ((bool)(!(bool)(this->linetilde_01_activeRamps->length))) {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        1114681293,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;

                    if ((bool)(!(bool)(__linetilde_01_keepramp))) {
                        __linetilde_01_time = 0;
                    }
                }
            }

            __linetilde_01_currentValue = val;
        }
    }

    while (i < n) {
        out[(Index)i] = __linetilde_01_currentValue;
        i++;
    }

    this->linetilde_01_currentValue = __linetilde_01_currentValue;
    this->linetilde_01_time = __linetilde_01_time;
}

void linetilde_02_perform(SampleValue * out, Index n) {
    auto __linetilde_02_time = this->linetilde_02_time;
    auto __linetilde_02_keepramp = this->linetilde_02_keepramp;
    auto __linetilde_02_currentValue = this->linetilde_02_currentValue;
    Index i = 0;

    if ((bool)(this->linetilde_02_activeRamps->length)) {
        while ((bool)(this->linetilde_02_activeRamps->length) && i < n) {
            number destinationValue = this->linetilde_02_activeRamps[0];
            number inc = this->linetilde_02_activeRamps[1];
            number rampTimeInSamples = this->linetilde_02_activeRamps[2] - this->audioProcessSampleCount - i;
            number val = __linetilde_02_currentValue;

            while (rampTimeInSamples > 0 && i < n) {
                out[(Index)i] = val;
                val += inc;
                i++;
                rampTimeInSamples--;
            }

            if (rampTimeInSamples <= 0) {
                val = destinationValue;
                this->linetilde_02_activeRamps->splice(0, 3);

                if ((bool)(!(bool)(this->linetilde_02_activeRamps->length))) {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        -62043057,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;

                    if ((bool)(!(bool)(__linetilde_02_keepramp))) {
                        __linetilde_02_time = 0;
                    }
                }
            }

            __linetilde_02_currentValue = val;
        }
    }

    while (i < n) {
        out[(Index)i] = __linetilde_02_currentValue;
        i++;
    }

    this->linetilde_02_currentValue = __linetilde_02_currentValue;
    this->linetilde_02_time = __linetilde_02_time;
}

void linetilde_03_perform(SampleValue * out, Index n) {
    auto __linetilde_03_time = this->linetilde_03_time;
    auto __linetilde_03_keepramp = this->linetilde_03_keepramp;
    auto __linetilde_03_currentValue = this->linetilde_03_currentValue;
    Index i = 0;

    if ((bool)(this->linetilde_03_activeRamps->length)) {
        while ((bool)(this->linetilde_03_activeRamps->length) && i < n) {
            number destinationValue = this->linetilde_03_activeRamps[0];
            number inc = this->linetilde_03_activeRamps[1];
            number rampTimeInSamples = this->linetilde_03_activeRamps[2] - this->audioProcessSampleCount - i;
            number val = __linetilde_03_currentValue;

            while (rampTimeInSamples > 0 && i < n) {
                out[(Index)i] = val;
                val += inc;
                i++;
                rampTimeInSamples--;
            }

            if (rampTimeInSamples <= 0) {
                val = destinationValue;
                this->linetilde_03_activeRamps->splice(0, 3);

                if ((bool)(!(bool)(this->linetilde_03_activeRamps->length))) {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        -1621164530,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;

                    if ((bool)(!(bool)(__linetilde_03_keepramp))) {
                        __linetilde_03_time = 0;
                    }
                }
            }

            __linetilde_03_currentValue = val;
        }
    }

    while (i < n) {
        out[(Index)i] = __linetilde_03_currentValue;
        i++;
    }

    this->linetilde_03_currentValue = __linetilde_03_currentValue;
    this->linetilde_03_time = __linetilde_03_time;
}

void groove_01_perform(
    const Sample * rate_auto,
    number begin,
    number end,
    SampleValue * out1,
    SampleValue * out2,
    SampleValue * sync,
    Index n
) {
    RNBO_UNUSED(out2);
    RNBO_UNUSED(out1);
    RNBO_UNUSED(begin);
    auto __groove_01_crossfade = this->groove_01_crossfade;
    auto __groove_01_loop = this->groove_01_loop;
    auto __groove_01_playStatus = this->groove_01_playStatus;
    auto __groove_01_readIndex = this->groove_01_readIndex;
    auto __groove_01_incomingChange = this->groove_01_incomingChange;
    auto __groove_01_changeIncomingInSamples = this->groove_01_changeIncomingInSamples;
    auto __groove_01_buffer = this->groove_01_buffer;
    SampleArray<2> out = {out1, out2};
    SampleIndex bufferLength = (SampleIndex)(__groove_01_buffer->getSize());
    Index i = 0;

    if (bufferLength > 1) {
        auto effectiveChannels = this->minimum(__groove_01_buffer->getChannels(), 2);
        number srMult = 0.001 * __groove_01_buffer->getSampleRate();
        number srInv = (number)1 / this->samplerate();
        number rateMult = __groove_01_buffer->getSampleRate() * srInv;

        for (; i < n; i++) {
            Index channel = 0;
            number offset = 0;
            number loopMin = 0 * srMult;
            loopMin = (loopMin > bufferLength - 1 ? bufferLength - 1 : (loopMin < 0 ? 0 : loopMin));
            number loopMax = (end < 0 ? bufferLength : end * srMult);
            loopMax = (loopMax > bufferLength ? bufferLength : (loopMax < 0 ? 0 : loopMax));

            if (loopMin >= loopMax) {
                offset = loopMax;
                loopMax = bufferLength;
                loopMin -= offset;
            }

            number loopLength = loopMax - loopMin;
            number currentRate = rate_auto[(Index)i] * rateMult;
            number currentSync = 0;

            if (__groove_01_changeIncomingInSamples > 0) {
                __groove_01_changeIncomingInSamples--;

                if (__groove_01_changeIncomingInSamples <= 0) {
                    if (__groove_01_incomingChange == 1) {
                        if (currentRate < 0) {
                            __groove_01_readIndex = loopMax - 1;
                        } else {
                            __groove_01_readIndex = loopMin;
                        }

                        __groove_01_playStatus = 1;
                    } else if (__groove_01_incomingChange == 0) {
                        __groove_01_playStatus = 0;
                    }

                    __groove_01_incomingChange = 2;
                }
            }

            if (loopLength > 0) {
                if (currentRate != 0) {
                    if (__groove_01_playStatus == 1) {
                        if ((bool)(__groove_01_loop)) {
                            while (__groove_01_readIndex < loopMin) {
                                __groove_01_readIndex += loopLength;
                            }

                            while (__groove_01_readIndex >= loopMax) {
                                __groove_01_readIndex -= loopLength;
                            }
                        } else if (__groove_01_readIndex >= loopMax || __groove_01_readIndex < loopMin) {
                            __groove_01_playStatus = 0;
                            break;
                        }

                        for (; channel < effectiveChannels; channel++) {
                            number outSample = (currentRate == 1 ? this->groove_01_getSample((Index)(channel), trunc(__groove_01_readIndex), offset, bufferLength) : this->groove_01_interpolatedSample(
                                (Index)(channel),
                                __groove_01_readIndex,
                                loopMax,
                                loopLength,
                                offset,
                                bufferLength
                            ));

                            if (__groove_01_crossfade > 0) {
                                out[(Index)channel][(Index)i] = this->groove_01_crossfadedSample(
                                    outSample,
                                    __groove_01_readIndex,
                                    (Index)(channel),
                                    currentRate,
                                    loopMin,
                                    loopMax,
                                    loopLength,
                                    offset,
                                    bufferLength
                                );
                            } else {
                                out[(Index)channel][(Index)i] = outSample;
                            }
                        }

                        {
                            currentSync = this->groove_01_calcSync(__groove_01_readIndex, offset, loopMin, loopLength, bufferLength, srInv);
                        }

                        __groove_01_readIndex += currentRate;
                    }
                } else {
                    if (__groove_01_playStatus == 1) {
                        currentSync = this->groove_01_calcSync(__groove_01_readIndex, offset, loopMin, loopLength, bufferLength, srInv);
                    }
                }
            }

            {
                sync[(Index)i] = currentSync;
            }

            for (; channel < 2; channel++) {
                if (__groove_01_playStatus <= 0)
                    sync[(Index)i] = 0;

                out[(Index)channel][(Index)i] = 0;
            }
        }
    }

    for (; i < n; i++) {
        if (__groove_01_playStatus <= 0)
            sync[(Index)i] = 0;

        for (number channel = 0; channel < 2; channel++) {
            out[(Index)channel][(Index)i] = 0;
        }
    }

    this->groove_01_changeIncomingInSamples = __groove_01_changeIncomingInSamples;
    this->groove_01_incomingChange = __groove_01_incomingChange;
    this->groove_01_readIndex = __groove_01_readIndex;
    this->groove_01_playStatus = __groove_01_playStatus;
}

void trapezoid_tilde_01_perform(
    const Sample * phase,
    number rampUp,
    number rampDown,
    SampleValue * out1,
    Index n
) {
    RNBO_UNUSED(rampDown);
    RNBO_UNUSED(rampUp);
    Index i;

    for (i = 0; i < n; i++) {
        number __rampDown = 0.99;
        number __rampUp = 0.01;
        number __phase = phase[(Index)i];
        number tmp = 0.0;
        __phase = this->wrap(__phase, 0., 1.);
        __rampUp = (__rampUp > 1. ? 1. : (__rampUp < 0. ? 0. : __rampUp));
        __rampDown = (__rampDown > 1. ? 1. : (__rampDown < 0. ? 0. : __rampDown));

        if (__rampDown < __rampUp)
            __rampDown = __rampUp;

        if (__phase < __rampUp) {
            tmp = this->safediv(__phase, __rampUp);
        } else if (__phase > __rampDown) {
            tmp = 1. - this->safediv(__phase - __rampDown, 1. - __rampDown);
        } else {
            tmp = 1.;
        }

        out1[(Index)i] = tmp;
    }
}

void dspexpr_08_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_07_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_06_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_02_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_05_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_04_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_03_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void signalforwarder_02_perform(const SampleValue * input, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input[(Index)i];
    }
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void data_01_srout_set(number ) {}

void data_01_chanout_set(number ) {}

void data_01_sizeout_set(number v) {
    this->data_01_sizeout = v;
}

void toggle_01_value_number_setter(number v) {
    this->toggle_01_value_number = (v != 0 ? 1 : 0);
}

void toggle_02_value_number_setter(number v) {
    this->toggle_02_value_number = (v != 0 ? 1 : 0);
}

void toggle_03_value_number_setter(number v) {
    this->toggle_03_value_number = (v != 0 ? 1 : 0);
}

void numberobj_01_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_01_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_01_value = localvalue;
}

void numberobj_02_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_02_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_02_value = localvalue;
}

void numberobj_03_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_03_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_03_value = localvalue;
}

void numberobj_04_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_04_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_04_value = localvalue;
}

void numberobj_05_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_05_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_05_value = localvalue;
}

void numberobj_06_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < -100) {
        localvalue = -100;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_06_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_06_value = localvalue;
}

void numberobj_07_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_07_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_07_value = localvalue;
}

void numberobj_08_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < -24) {
        localvalue = -24;
    }

    if ((bool)(true) && localvalue > 24) {
        localvalue = 24;
    }

    if (this->numberobj_08_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_08_value = localvalue;
}

void toggle_04_value_number_setter(number v) {
    this->toggle_04_value_number = (v != 0 ? 1 : 0);
}

void numberobj_09_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_09_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_09_value = localvalue;
}

void toggle_05_value_number_setter(number v) {
    this->toggle_05_value_number = (v != 0 ? 1 : 0);
}

void onebang_01_initial_setter(number v) {
    if (v > 0)
        this->onebang_01_allow = true;
    else
        this->onebang_01_allow = false;
}

void numberobj_10_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 2) {
        localvalue = 2;
    }

    if (this->numberobj_10_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_10_value = localvalue;
}

void onebang_02_initial_setter(number v) {
    if (v > 0)
        this->onebang_02_allow = true;
    else
        this->onebang_02_allow = false;
}

void toggle_06_value_number_setter(number v) {
    this->toggle_06_value_number = (v != 0 ? 1 : 0);
}

void onebang_03_initial_setter(number v) {
    if (v > 0)
        this->onebang_03_allow = true;
    else
        this->onebang_03_allow = false;
}

void toggle_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_01_value_number;
}

void toggle_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_01_value_number_set(preset["value"]);
}

number recordtilde_01_calcSync(
    number writeIndex,
    number loopMin,
    number loopLength,
    SampleIndex bufferLength,
    number srInv
) {
    RNBO_UNUSED(bufferLength);
    RNBO_UNUSED(loopLength);

    {
        {
            {
                {
                    {
                        return (writeIndex - loopMin) * srInv * 1000;
                    }
                }
            }
        }
    }
}

number groove_01_getSample(
    Index channel,
    SampleIndex index,
    SampleIndex offset,
    SampleIndex bufferLength
) {
    if (offset > 0) {
        index += offset;

        if (index >= bufferLength)
            index -= bufferLength;
    }

    return this->groove_01_buffer->getSample(channel, index);
}

number groove_01_interpolatedSample(
    Index channel,
    number index,
    SampleIndex end,
    SampleIndex length,
    SampleIndex offset,
    SampleIndex bufferLength
) {
    SampleIndex index1 = (SampleIndex)(trunc(index));
    number i_x = index - index1;
    number i_1px = 1. + i_x;
    number i_1mx = 1. - i_x;
    number i_2mx = 2. - i_x;
    number i_a = i_1mx * i_2mx;
    number i_b = i_1px * i_x;
    number i_p1 = -.1666667 * i_a * i_x;
    number i_p2 = .5 * i_1px * i_a;
    number i_p3 = .5 * i_b * i_2mx;
    number i_p4 = -.1666667 * i_b * i_1mx;
    SampleIndex index2 = (SampleIndex)(index1 + 1);

    if (index2 >= end)
        index2 -= length;

    SampleIndex index3 = (SampleIndex)(index1 + 2);

    if (index3 >= end)
        index3 -= length;

    SampleIndex index4 = (SampleIndex)(index1 + 3);

    if (index4 >= end)
        index4 -= length;

    return this->groove_01_getSample(channel, index1, offset, bufferLength) * i_p1 + this->groove_01_getSample(channel, index2, offset, bufferLength) * i_p2 + this->groove_01_getSample(channel, index3, offset, bufferLength) * i_p3 + this->groove_01_getSample(channel, index4, offset, bufferLength) * i_p4;
}

number groove_01_crossfadedSample(
    SampleValue out,
    number readIndex,
    Index channel,
    number rate,
    number loopMin,
    number loopMax,
    number loopLength,
    number offset,
    number bufferLength
) {
    auto crossFadeStart1 = this->maximum(loopMin - this->groove_01_crossfadeInSamples, 0);
    auto crossFadeEnd1 = this->minimum(crossFadeStart1 + this->groove_01_crossfadeInSamples, bufferLength);
    number crossFadeStart2 = crossFadeStart1 + loopLength;
    auto crossFadeEnd2 = this->minimum(crossFadeEnd1 + loopLength, bufferLength);
    number crossFadeLength = crossFadeEnd2 - crossFadeStart2;

    if (crossFadeLength > 0) {
        crossFadeEnd1 = crossFadeStart1 + crossFadeLength;
        number diff = -1;
        number addFactor = 0;

        if (readIndex >= crossFadeStart2) {
            diff = readIndex - crossFadeStart2;
            addFactor = -1;
        } else if (readIndex < crossFadeEnd1) {
            diff = crossFadeEnd1 - readIndex + loopMax - crossFadeStart2;
            addFactor = 1;
        }

        if (diff >= 0) {
            number out2ReadIndex = readIndex + loopLength * addFactor;
            number out2 = (rate == 1 ? this->groove_01_getSample(channel, trunc(out2ReadIndex), offset, bufferLength) : this->groove_01_interpolatedSample(channel, out2ReadIndex, loopMax, loopLength, offset, bufferLength));
            number out2Factor = diff / crossFadeLength;
            number out1Factor = 1 - out2Factor;
            return out * out1Factor + out2 * out2Factor;
        }
    }

    return out;
}

number groove_01_calcSync(
    number readIndex,
    number offset,
    number loopMin,
    number loopLength,
    SampleIndex bufferLength,
    number srInv
) {
    RNBO_UNUSED(srInv);
    RNBO_UNUSED(bufferLength);
    RNBO_UNUSED(offset);

    {
        {
            return (readIndex - loopMin) / loopLength;
        }
    }
}

void groove_01_dspsetup(bool force) {
    if ((bool)(this->groove_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->groove_01_crossfadeInSamples = this->mstosamps(this->groove_01_crossfade);
    this->groove_01_setupDone = true;
}

void toggle_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_02_value_number;
}

void toggle_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_02_value_number_set(preset["value"]);
}

void param_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_01_value;
}

void param_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_01_value_set(preset["value"]);
}

void toggle_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_03_value_number;
}

void toggle_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_03_value_number_set(preset["value"]);
}

void numberobj_01_init() {
    this->numberobj_01_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-119"), 1, this->_currentTime);
}

void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_01_value;
}

void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_01_value_set(preset["value"]);
}

void numberobj_02_init() {
    this->numberobj_02_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-128"), 1, this->_currentTime);
}

void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_02_value;
}

void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_02_value_set(preset["value"]);
}

void numberobj_03_init() {
    this->numberobj_03_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-126"), 1, this->_currentTime);
}

void numberobj_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_03_value;
}

void numberobj_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_03_value_set(preset["value"]);
}

void param_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_02_value;
}

void param_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_02_value_set(preset["value"]);
}

void numberobj_04_init() {
    this->numberobj_04_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-201"), 1, this->_currentTime);
}

void numberobj_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_04_value;
}

void numberobj_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_04_value_set(preset["value"]);
}

void numberobj_05_init() {
    this->numberobj_05_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-203"), 1, this->_currentTime);
}

void numberobj_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_05_value;
}

void numberobj_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_05_value_set(preset["value"]);
}

void numberobj_06_init() {
    this->numberobj_06_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-45"), 1, this->_currentTime);
}

void numberobj_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_06_value;
}

void numberobj_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_06_value_set(preset["value"]);
}

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
}

void param_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_04_value;
}

void param_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_04_value_set(preset["value"]);
}

void numberobj_07_init() {
    this->numberobj_07_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-78"), 1, this->_currentTime);
}

void numberobj_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_07_value;
}

void numberobj_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_07_value_set(preset["value"]);
}

void numberobj_08_init() {
    this->numberobj_08_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-72"), 1, this->_currentTime);
}

void numberobj_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_08_value;
}

void numberobj_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_08_value_set(preset["value"]);
}

void data_01_init() {
    this->data_01_buffer->setWantsFill(true);
}

Index data_01_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    number size = 0;
    return (Index)(size);
}

void data_01_dspsetup(bool force) {
    if ((bool)(this->data_01_setupDone) && (bool)(!(bool)(force)))
        return;

    if (this->data_01_sizemode == 2) {
        this->data_01_buffer = this->data_01_buffer->setSize((Index)(this->mstosamps(this->data_01_sizems)));
        updateDataRef(this, this->data_01_buffer);
    } else if (this->data_01_sizemode == 3) {
        this->data_01_buffer = this->data_01_buffer->setSize(this->data_01_evaluateSizeExpr(this->samplerate(), this->vectorsize()));
        updateDataRef(this, this->data_01_buffer);
    }

    this->data_01_setupDone = true;
}

void data_01_bufferUpdated() {
    this->data_01_report();
}

void data_01_report() {
    this->data_01_srout_set(this->data_01_buffer->getSampleRate());
    this->data_01_chanout_set(this->data_01_buffer->getChannels());
    this->data_01_sizeout_set(this->data_01_buffer->getSize());
}

void param_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_05_value;
}

void param_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_05_value_set(preset["value"]);
}

void toggle_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_04_value_number;
}

void toggle_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_04_value_number_set(preset["value"]);
}

void numberobj_09_init() {
    this->numberobj_09_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-77"), 1, this->_currentTime);
}

void numberobj_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_09_value;
}

void numberobj_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_09_value_set(preset["value"]);
}

void toggle_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_05_value_number;
}

void toggle_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_05_value_number_set(preset["value"]);
}

void param_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_06_value;
}

void param_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_06_value_set(preset["value"]);
}

void numberobj_10_init() {
    this->numberobj_10_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-5"), 1, this->_currentTime);
}

void numberobj_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_10_value;
}

void numberobj_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_10_value_set(preset["value"]);
}

void toggle_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_06_value_number;
}

void toggle_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_06_value_number_set(preset["value"]);
}

Index globaltransport_getSampleOffset(MillisecondTime time) {
    return this->mstosamps(this->maximum(0, time - this->getEngine()->getCurrentTime()));
}

number globaltransport_getTempoAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < this->vs ? this->globaltransport_tempo[(Index)sampleOffset] : this->globaltransport_lastTempo);
}

number globaltransport_getStateAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < this->vs ? this->globaltransport_state[(Index)sampleOffset] : this->globaltransport_lastState);
}

number globaltransport_getState(MillisecondTime time) {
    return this->globaltransport_getStateAtSample(this->globaltransport_getSampleOffset(time));
}

number globaltransport_getBeatTime(MillisecondTime time) {
    number i = 2;

    while (i < this->globaltransport_beatTimeChanges->length && this->globaltransport_beatTimeChanges[(Index)(i + 1)] <= time) {
        i += 2;
    }

    i -= 2;
    number beatTimeBase = this->globaltransport_beatTimeChanges[(Index)i];

    if (this->globaltransport_getState(time) == 0)
        return beatTimeBase;

    number beatTimeBaseMsTime = this->globaltransport_beatTimeChanges[(Index)(i + 1)];
    number diff = time - beatTimeBaseMsTime;
    return beatTimeBase + this->mstobeats(diff);
}

bool globaltransport_setTempo(MillisecondTime time, number tempo, bool notify) {
    if ((bool)(notify)) {
        this->processTempoEvent(time, tempo);
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getTempoAtSample(offset) != tempo) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
            this->globaltransport_beatTimeChanges->push(time);
            fillSignal(this->globaltransport_tempo, this->vs, tempo, offset);
            this->globaltransport_lastTempo = tempo;
            this->globaltransport_tempoNeedsReset = true;
            return true;
        }
    }

    return false;
}

number globaltransport_getTempo(MillisecondTime time) {
    return this->globaltransport_getTempoAtSample(this->globaltransport_getSampleOffset(time));
}

bool globaltransport_setState(MillisecondTime time, number state, bool notify) {
    if ((bool)(notify)) {
        this->processTransportEvent(time, TransportState(state));
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getStateAtSample(offset) != state) {
            fillSignal(this->globaltransport_state, this->vs, state, offset);
            this->globaltransport_lastState = TransportState(state);
            this->globaltransport_stateNeedsReset = true;

            if (state == 0) {
                this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
                this->globaltransport_beatTimeChanges->push(time);
            }

            return true;
        }
    }

    return false;
}

bool globaltransport_setBeatTime(MillisecondTime time, number beattime, bool notify) {
    if ((bool)(notify)) {
        this->processBeatTimeEvent(time, beattime);
        this->globaltransport_notify = true;
        return false;
    } else {
        bool beatTimeHasChanged = false;
        float oldBeatTime = (float)(this->globaltransport_getBeatTime(time));
        float newBeatTime = (float)(beattime);

        if (oldBeatTime != newBeatTime) {
            beatTimeHasChanged = true;
        }

        this->globaltransport_beatTimeChanges->push(beattime);
        this->globaltransport_beatTimeChanges->push(time);
        return beatTimeHasChanged;
    }
}

number globaltransport_getBeatTimeAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBeatTime(this->getEngine()->getCurrentTime() + msOffset);
}

array<number, 2> globaltransport_getTimeSignature(MillisecondTime time) {
    number i = 3;

    while (i < this->globaltransport_timeSignatureChanges->length && this->globaltransport_timeSignatureChanges[(Index)(i + 2)] <= time) {
        i += 3;
    }

    i -= 3;

    return {
        this->globaltransport_timeSignatureChanges[(Index)i],
        this->globaltransport_timeSignatureChanges[(Index)(i + 1)]
    };
}

array<number, 2> globaltransport_getTimeSignatureAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getTimeSignature(this->getEngine()->getCurrentTime() + msOffset);
}

bool globaltransport_setTimeSignature(MillisecondTime time, number numerator, number denominator, bool notify) {
    if ((bool)(notify)) {
        this->processTimeSignatureEvent(time, (int)(numerator), (int)(denominator));
        this->globaltransport_notify = true;
    } else {
        array<number, 2> currentSig = this->globaltransport_getTimeSignature(time);

        if (currentSig[0] != numerator || currentSig[1] != denominator) {
            this->globaltransport_timeSignatureChanges->push(numerator);
            this->globaltransport_timeSignatureChanges->push(denominator);
            this->globaltransport_timeSignatureChanges->push(time);
            return true;
        }
    }

    return false;
}

void globaltransport_advance() {
    if ((bool)(this->globaltransport_tempoNeedsReset)) {
        fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
        this->globaltransport_tempoNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTempoEvent(this->globaltransport_lastTempo);
        }
    }

    if ((bool)(this->globaltransport_stateNeedsReset)) {
        fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
        this->globaltransport_stateNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTransportEvent(TransportState(this->globaltransport_lastState));
        }
    }

    if (this->globaltransport_beatTimeChanges->length > 2) {
        this->globaltransport_beatTimeChanges[0] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 2)];
        this->globaltransport_beatTimeChanges[1] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 1)];
        this->globaltransport_beatTimeChanges->length = 2;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendBeatTimeEvent(this->globaltransport_beatTimeChanges[0]);
        }
    }

    if (this->globaltransport_timeSignatureChanges->length > 3) {
        this->globaltransport_timeSignatureChanges[0] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 3)];
        this->globaltransport_timeSignatureChanges[1] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 2)];
        this->globaltransport_timeSignatureChanges[2] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 1)];
        this->globaltransport_timeSignatureChanges->length = 3;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTimeSignatureEvent(
                (int)(this->globaltransport_timeSignatureChanges[0]),
                (int)(this->globaltransport_timeSignatureChanges[1])
            );
        }
    }

    this->globaltransport_notify = false;
}

void globaltransport_dspsetup(bool force) {
    if ((bool)(this->globaltransport_setupDone) && (bool)(!(bool)(force)))
        return;

    fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
    this->globaltransport_tempoNeedsReset = false;
    fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
    this->globaltransport_stateNeedsReset = false;
    this->globaltransport_setupDone = true;
}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

void updateTime(MillisecondTime time) {
    this->_currentTime = time;
    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));

    if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;

    if (this->sampleOffsetIntoNextAudioBuffer < 0)
        this->sampleOffsetIntoNextAudioBuffer = 0;
}

void assign_defaults()
{
    dspexpr_01_in1 = 0;
    dspexpr_01_in2 = 0;
    dspexpr_02_in1 = 0;
    dspexpr_02_in2 = 0;
    dspexpr_03_in1 = 0;
    dspexpr_03_in2 = 0;
    receive_01_output_number = 0;
    receive_02_output_number = 0;
    dspexpr_04_in1 = 0;
    dspexpr_04_in2 = 0;
    toggle_01_value_number = 0;
    toggle_01_value_number_setter(toggle_01_value_number);
    recordtilde_01_record = 0;
    recordtilde_01_begin = 0;
    recordtilde_01_end = -1;
    recordtilde_01_loop = 0;
    dspexpr_05_in1 = 0;
    dspexpr_05_in2 = 0;
    groove_01_rate_auto = 1;
    groove_01_begin = 0;
    groove_01_end = -1;
    groove_01_loop = 1;
    groove_01_crossfade = 0;
    expr_01_in1 = 0;
    expr_01_out1 = 0;
    receive_03_output_number = 0;
    dspexpr_06_in1 = 0;
    dspexpr_06_in2 = 0;
    dspexpr_07_in1 = 0;
    dspexpr_07_in2 = 0;
    dspexpr_08_in1 = 0;
    dspexpr_08_in2 = 0;
    select_01_test1 = 0;
    snapshot_01_interval = 1;
    snapshot_01_out = 0;
    toggle_02_value_number = 0;
    toggle_02_value_number_setter(toggle_02_value_number);
    param_01_value = 0;
    receive_04_output_number = 0;
    toggle_03_value_number = 0;
    toggle_03_value_number_setter(toggle_03_value_number);
    linetilde_01_time = 10;
    linetilde_01_keepramp = 1;
    trapezoid_tilde_01_phase = 0;
    trapezoid_tilde_01_rampUp = 0.01;
    trapezoid_tilde_01_rampDown = 0.99;
    expr_02_in1 = 0;
    expr_02_in2 = 1;
    expr_02_out1 = 0;
    numberobj_01_value = 0;
    numberobj_01_value_setter(numberobj_01_value);
    switchobj_01_onoff = 1;
    send_01_input_number = 0;
    numberobj_02_value = 0;
    numberobj_02_value_setter(numberobj_02_value);
    numberobj_03_value = 0;
    numberobj_03_value_setter(numberobj_03_value);
    param_02_value = 1000;
    linetilde_02_time = 10;
    linetilde_02_keepramp = 1;
    numberobj_04_value = 0;
    numberobj_04_value_setter(numberobj_04_value);
    expr_03_in1 = 0;
    expr_03_out1 = 0;
    numberobj_05_value = 0;
    numberobj_05_value_setter(numberobj_05_value);
    scale_01_inlow = -100;
    scale_01_inhigh = 100;
    scale_01_outlow = -18;
    scale_01_outhigh = 18;
    scale_01_power = 1;
    numberobj_06_value = 0;
    numberobj_06_value_setter(numberobj_06_value);
    param_03_value = 0;
    param_04_value = 0;
    linetilde_03_time = 50;
    linetilde_03_keepramp = 1;
    numberobj_07_value = 0;
    numberobj_07_value_setter(numberobj_07_value);
    expr_06_in1 = 0;
    expr_06_in2 = 0;
    expr_06_out1 = 0;
    expr_07_in1 = 0;
    expr_07_out1 = 0;
    numberobj_08_value = 0;
    numberobj_08_value_setter(numberobj_08_value);
    data_01_sizeout = 0;
    data_01_size = 0;
    data_01_sizems = 10000;
    data_01_normalize = 0.995;
    data_01_channels = 2;
    param_05_value = 0;
    toggle_04_value_number = 0;
    toggle_04_value_number_setter(toggle_04_value_number);
    listlookup_01_lookup = { 1, -1 };
    numberobj_09_value = 0;
    numberobj_09_value_setter(numberobj_09_value);
    receive_05_output_number = 0;
    toggle_05_value_number = 0;
    toggle_05_value_number_setter(toggle_05_value_number);
    send_02_input_number = 0;
    onebang_01_initial = 0;
    onebang_01_initial_setter(onebang_01_initial);
    param_06_value = 2;
    select_02_test1 = 0;
    select_02_test2 = 1;
    select_02_test3 = 2;
    numberobj_10_value = 0;
    numberobj_10_value_setter(numberobj_10_value);
    onebang_02_initial = 0;
    onebang_02_initial_setter(onebang_02_initial);
    send_03_input_number = 0;
    toggle_06_value_number = 0;
    toggle_06_value_number_setter(toggle_06_value_number);
    send_04_input_number = 0;
    send_05_input_number = 0;
    onebang_03_initial = 0;
    onebang_03_initial_setter(onebang_03_initial);
    ctlin_01_input = 0;
    ctlin_01_controller = 4;
    ctlin_01_channel = -1;
    expr_04_in1 = 0;
    expr_04_in2 = 0.007874015748;
    expr_04_out1 = 0;
    ctlin_02_input = 0;
    ctlin_02_controller = 2;
    ctlin_02_channel = -1;
    expr_05_in1 = 0;
    expr_05_in2 = 0.007874015748;
    expr_05_out1 = 0;
    ctlin_03_input = 0;
    ctlin_03_controller = 3;
    ctlin_03_channel = -1;
    expr_08_in1 = 0;
    expr_08_in2 = 0.007874015748;
    expr_08_out1 = 0;
    ctlin_04_input = 0;
    ctlin_04_controller = 1;
    ctlin_04_channel = -1;
    expr_09_in1 = 0;
    expr_09_in2 = 0.007874015748;
    expr_09_out1 = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    signals[2] = nullptr;
    signals[3] = nullptr;
    signals[4] = nullptr;
    signals[5] = nullptr;
    signals[6] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    toggle_01_lastValue = 0;
    recordtilde_01_wIndex = 0;
    recordtilde_01_lastRecord = 0;
    groove_01_readIndex = 0;
    groove_01_playStatus = 0;
    groove_01_changeIncomingInSamples = 0;
    groove_01_incomingChange = 2;
    groove_01_crossfadeInSamples = 0;
    groove_01_setupDone = false;
    snapshot_01_calc = 0;
    snapshot_01_nextTime = 0;
    snapshot_01_count = 0;
    snapshot_01_lastValue = 0;
    toggle_02_lastValue = 0;
    param_01_lastValue = 0;
    toggle_03_lastValue = 0;
    linetilde_01_currentValue = 0;
    numberobj_01_currentFormat = 6;
    numberobj_01_lastValue = 0;
    numberobj_02_currentFormat = 6;
    numberobj_02_lastValue = 0;
    numberobj_03_currentFormat = 6;
    numberobj_03_lastValue = 0;
    param_02_lastValue = 0;
    linetilde_02_currentValue = 0;
    numberobj_04_currentFormat = 6;
    numberobj_04_lastValue = 0;
    numberobj_05_currentFormat = 6;
    numberobj_05_lastValue = 0;
    numberobj_06_currentFormat = 6;
    numberobj_06_lastValue = 0;
    param_03_lastValue = 0;
    param_04_lastValue = 0;
    linetilde_03_currentValue = 1;
    numberobj_07_currentFormat = 6;
    numberobj_07_lastValue = 0;
    numberobj_08_currentFormat = 6;
    numberobj_08_lastValue = 0;
    data_01_sizemode = 2;
    data_01_setupDone = false;
    param_05_lastValue = 0;
    toggle_04_lastValue = 0;
    numberobj_09_currentFormat = 6;
    numberobj_09_lastValue = 0;
    toggle_05_lastValue = 0;
    param_06_lastValue = 0;
    numberobj_10_currentFormat = 6;
    numberobj_10_lastValue = 0;
    toggle_06_lastValue = 0;
    ctlin_01_status = 0;
    ctlin_01_byte1 = -1;
    ctlin_01_inchan = 0;
    ctlin_02_status = 0;
    ctlin_02_byte1 = -1;
    ctlin_02_inchan = 0;
    ctlin_03_status = 0;
    ctlin_03_byte1 = -1;
    ctlin_03_inchan = 0;
    ctlin_04_status = 0;
    ctlin_04_byte1 = -1;
    ctlin_04_inchan = 0;
    globaltransport_tempo = nullptr;
    globaltransport_tempoNeedsReset = false;
    globaltransport_lastTempo = 120;
    globaltransport_state = nullptr;
    globaltransport_stateNeedsReset = false;
    globaltransport_lastState = 0;
    globaltransport_beatTimeChanges = { 0, 0 };
    globaltransport_timeSignatureChanges = { 4, 4, 0 };
    globaltransport_notify = false;
    globaltransport_setupDone = false;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number dspexpr_01_in1;
    number dspexpr_01_in2;
    number dspexpr_02_in1;
    number dspexpr_02_in2;
    number dspexpr_03_in1;
    number dspexpr_03_in2;
    number receive_01_output_number;
    list receive_01_output_list;
    number receive_02_output_number;
    list receive_02_output_list;
    number dspexpr_04_in1;
    number dspexpr_04_in2;
    number toggle_01_value_number;
    number recordtilde_01_record;
    number recordtilde_01_begin;
    number recordtilde_01_end;
    number recordtilde_01_loop;
    number dspexpr_05_in1;
    number dspexpr_05_in2;
    number groove_01_rate_auto;
    number groove_01_begin;
    number groove_01_end;
    number groove_01_loop;
    number groove_01_crossfade;
    number expr_01_in1;
    number expr_01_out1;
    number receive_03_output_number;
    list receive_03_output_list;
    number dspexpr_06_in1;
    number dspexpr_06_in2;
    number dspexpr_07_in1;
    number dspexpr_07_in2;
    number dspexpr_08_in1;
    number dspexpr_08_in2;
    number select_01_test1;
    number snapshot_01_interval;
    number snapshot_01_out;
    number toggle_02_value_number;
    number param_01_value;
    number receive_04_output_number;
    list receive_04_output_list;
    number toggle_03_value_number;
    list linetilde_01_segments;
    number linetilde_01_time;
    number linetilde_01_keepramp;
    number trapezoid_tilde_01_phase;
    number trapezoid_tilde_01_rampUp;
    number trapezoid_tilde_01_rampDown;
    number expr_02_in1;
    number expr_02_in2;
    number expr_02_out1;
    number numberobj_01_value;
    number switchobj_01_onoff;
    number send_01_input_number;
    list send_01_input_list;
    number numberobj_02_value;
    number numberobj_03_value;
    number param_02_value;
    list linetilde_02_segments;
    number linetilde_02_time;
    number linetilde_02_keepramp;
    number numberobj_04_value;
    number expr_03_in1;
    number expr_03_out1;
    number numberobj_05_value;
    list scale_01_input;
    number scale_01_inlow;
    number scale_01_inhigh;
    number scale_01_outlow;
    number scale_01_outhigh;
    number scale_01_power;
    list scale_01_out;
    number numberobj_06_value;
    number param_03_value;
    number param_04_value;
    list linetilde_03_segments;
    number linetilde_03_time;
    number linetilde_03_keepramp;
    number numberobj_07_value;
    number expr_06_in1;
    number expr_06_in2;
    number expr_06_out1;
    number expr_07_in1;
    number expr_07_out1;
    number numberobj_08_value;
    number data_01_sizeout;
    number data_01_size;
    number data_01_sizems;
    number data_01_normalize;
    number data_01_channels;
    number param_05_value;
    number toggle_04_value_number;
    list listlookup_01_input;
    list listlookup_01_lookup;
    number numberobj_09_value;
    number receive_05_output_number;
    list receive_05_output_list;
    number toggle_05_value_number;
    number send_02_input_number;
    list send_02_input_list;
    number onebang_01_initial;
    number param_06_value;
    number select_02_test1;
    number select_02_test2;
    number select_02_test3;
    number numberobj_10_value;
    number onebang_02_initial;
    number send_03_input_number;
    list send_03_input_list;
    number toggle_06_value_number;
    number send_04_input_number;
    list send_04_input_list;
    number send_05_input_number;
    list send_05_input_list;
    number onebang_03_initial;
    number ctlin_01_input;
    number ctlin_01_controller;
    number ctlin_01_channel;
    number expr_04_in1;
    number expr_04_in2;
    number expr_04_out1;
    number ctlin_02_input;
    number ctlin_02_controller;
    number ctlin_02_channel;
    number expr_05_in1;
    number expr_05_in2;
    number expr_05_out1;
    number ctlin_03_input;
    number ctlin_03_controller;
    number ctlin_03_channel;
    number expr_08_in1;
    number expr_08_in2;
    number expr_08_out1;
    number ctlin_04_input;
    number ctlin_04_controller;
    number ctlin_04_channel;
    number expr_09_in1;
    number expr_09_in2;
    number expr_09_out1;
    MillisecondTime _currentTime;
    SampleIndex audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[7];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number toggle_01_lastValue;
    Float64BufferRef recordtilde_01_buffer;
    SampleIndex recordtilde_01_wIndex;
    number recordtilde_01_lastRecord;
    Float64BufferRef groove_01_buffer;
    number groove_01_readIndex;
    Index groove_01_playStatus;
    SampleIndex groove_01_changeIncomingInSamples;
    Int groove_01_incomingChange;
    SampleIndex groove_01_crossfadeInSamples;
    bool groove_01_setupDone;
    number snapshot_01_calc;
    number snapshot_01_nextTime;
    SampleIndex snapshot_01_count;
    number snapshot_01_lastValue;
    number toggle_02_lastValue;
    number param_01_lastValue;
    number toggle_03_lastValue;
    list linetilde_01_activeRamps;
    number linetilde_01_currentValue;
    Int numberobj_01_currentFormat;
    number numberobj_01_lastValue;
    Int numberobj_02_currentFormat;
    number numberobj_02_lastValue;
    Int numberobj_03_currentFormat;
    number numberobj_03_lastValue;
    number param_02_lastValue;
    list linetilde_02_activeRamps;
    number linetilde_02_currentValue;
    Int numberobj_04_currentFormat;
    number numberobj_04_lastValue;
    Int numberobj_05_currentFormat;
    number numberobj_05_lastValue;
    Int numberobj_06_currentFormat;
    number numberobj_06_lastValue;
    number param_03_lastValue;
    number param_04_lastValue;
    list linetilde_03_activeRamps;
    number linetilde_03_currentValue;
    Int numberobj_07_currentFormat;
    number numberobj_07_lastValue;
    Int numberobj_08_currentFormat;
    number numberobj_08_lastValue;
    Float64BufferRef data_01_buffer;
    Int data_01_sizemode;
    bool data_01_setupDone;
    number param_05_lastValue;
    number toggle_04_lastValue;
    Int numberobj_09_currentFormat;
    number numberobj_09_lastValue;
    number toggle_05_lastValue;
    bool onebang_01_allow;
    number param_06_lastValue;
    Int numberobj_10_currentFormat;
    number numberobj_10_lastValue;
    bool onebang_02_allow;
    number toggle_06_lastValue;
    bool onebang_03_allow;
    int ctlin_01_status;
    int ctlin_01_byte1;
    int ctlin_01_inchan;
    int ctlin_02_status;
    int ctlin_02_byte1;
    int ctlin_02_inchan;
    int ctlin_03_status;
    int ctlin_03_byte1;
    int ctlin_03_inchan;
    int ctlin_04_status;
    int ctlin_04_byte1;
    int ctlin_04_inchan;
    signal globaltransport_tempo;
    bool globaltransport_tempoNeedsReset;
    number globaltransport_lastTempo;
    signal globaltransport_state;
    bool globaltransport_stateNeedsReset;
    number globaltransport_lastState;
    list globaltransport_beatTimeChanges;
    list globaltransport_timeSignatureChanges;
    bool globaltransport_notify;
    bool globaltransport_setupDone;
    number stackprotect_count;
    DataRef Looper;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;

};

PatcherInterface* createRnboLooper2()
{
    return new RnboLooper2();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr RnboLooper2FactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return createRnboLooper2;
}

} // end RNBO namespace

