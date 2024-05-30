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

class RnboTubeTapeSaturation : public PatcherInterfaceImpl {
public:

class RNBOSubpatcher_43 : public PatcherInterfaceImpl {
    
    friend class RnboTubeTapeSaturation;
    
    public:
    
    RNBOSubpatcher_43()
    {
    }
    
    ~RNBOSubpatcher_43()
    {
    }
    
    virtual RnboTubeTapeSaturation* getPatcher() const {
        return static_cast<RnboTubeTapeSaturation *>(_parentPatcher);
    }
    
    RnboTubeTapeSaturation* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -62043057, false);
    }
    
    inline number safemod(number f, number m) {
        if (m != 0) {
            Int f_trunc = (Int)(trunc(f));
            Int m_trunc = (Int)(trunc(m));
    
            if (f == f_trunc && m == m_trunc) {
                f = f_trunc % m_trunc;
            } else {
                if (m < 0) {
                    m = -m;
                }
    
                if (f >= m) {
                    if (f >= m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f -= m;
                    }
                } else if (f <= -m) {
                    if (f <= -m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f += m;
                    }
                }
            }
        } else {
            f = 0.0;
        }
    
        return f;
    }
    
    inline number safesqrt(number num) {
        return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
    }
    
    SampleIndex currentsampletime() {
        return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
    }
    
    number mstosamps(MillisecondTime ms) {
        return ms * this->sr * 0.001;
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
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
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        const SampleValue * in3 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
        const SampleValue * in4 = (numInputs >= 4 && inputs[3] ? inputs[3] : this->zeroBuffer);
        this->linetilde_01_perform(this->signals[0], n);
        this->xfade_tilde_01_perform(this->signals[0], in1, in3, out1, n);
        this->xfade_tilde_02_perform(this->signals[0], in2, in4, out2, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 1; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
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
    
        RNBO_UNUSED(forceDSPSetup);
    
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
    
    void getPreset(PatcherStateInterface& ) {}
    
    void processTempoEvent(MillisecondTime , Tempo ) {}
    
    void processTransportEvent(MillisecondTime , TransportState ) {}
    
    void processBeatTimeEvent(MillisecondTime , BeatTime ) {}
    
    void onSampleRateChanged(double ) {}
    
    void processTimeSignatureEvent(MillisecondTime , int , int ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
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
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
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
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -62043057:
            {
            this->linetilde_01_target_bang();
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
            if (TAG("Mix~/number_obj-5") == objectId)
                this->numberobj_01_valin_set(payload);
    
            if (TAG("Mix~/number_obj-8") == objectId)
                this->numberobj_02_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("Mix~/number_obj-5") == objectId)
                this->numberobj_01_format_set(payload);
    
            if (TAG("Mix~/number_obj-8") == objectId)
                this->numberobj_02_format_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("Mix~/number_obj-5"):
            {
            return "Mix~/number_obj-5";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("Mix~/number_obj-8"):
            {
            return "Mix~/number_obj-8";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void numberobj_01_valin_set(number v) {
        this->numberobj_01_value_set(v);
    }
    
    void numberobj_01_format_set(number v) {
        this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_02_valin_set(number v) {
        this->numberobj_02_value_set(v);
    }
    
    void numberobj_02_format_set(number v) {
        this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void eventinlet_01_out1_bang_bang() {
        this->numberobj_02_value_bang();
    }
    
    void eventinlet_01_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_02_value_set(converted);
        }
    }
    
    void linetilde_01_target_bang() {}
    
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
        return 4;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->numberobj_01_init();
        this->numberobj_02_init();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {}
    
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
    
    void numberobj_01_output_set(number v) {
        {
            list converted = {v};
            this->linetilde_01_segments_set(converted);
        }
    }
    
    void numberobj_01_value_set(number v) {
        this->numberobj_01_value_setter(v);
        v = this->numberobj_01_value;
        number localvalue = v;
    
        if (this->numberobj_01_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("Mix~/number_obj-5"), localvalue, this->_currentTime);
        this->numberobj_01_output_set(localvalue);
    }
    
    void expr_01_out1_set(number v) {
        this->expr_01_out1 = v;
        this->numberobj_01_value_set(this->expr_01_out1);
    }
    
    void expr_01_in1_set(number in1) {
        this->expr_01_in1 = in1;
    
        this->expr_01_out1_set(
            (this->expr_01_in2 == 0 ? 0 : (this->expr_01_in2 == 0. ? 0. : this->expr_01_in1 / this->expr_01_in2))
        );//#map:Mix~//_obj-7:1
    }
    
    void numberobj_02_output_set(number v) {
        this->expr_01_in1_set(v);
    }
    
    void numberobj_02_value_set(number v) {
        this->numberobj_02_value_setter(v);
        v = this->numberobj_02_value;
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("Mix~/number_obj-8"), localvalue, this->_currentTime);
        this->numberobj_02_output_set(localvalue);
    }
    
    void eventinlet_01_out1_number_set(number v) {
        this->numberobj_02_value_set(v);
    }
    
    void numberobj_02_value_bang() {
        number v = this->numberobj_02_value;
        number localvalue = v;
    
        if (this->numberobj_02_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("Mix~/number_obj-8"), localvalue, this->_currentTime);
        this->numberobj_02_output_set(localvalue);
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
                            -62043057,
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
    
    void xfade_tilde_01_perform(
        const Sample * pos,
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] * this->xfade_tilde_01_func_next(pos[(Index)i], 0) + in2[(Index)i] * this->xfade_tilde_01_func_next(pos[(Index)i], 1);
        }
    }
    
    void xfade_tilde_02_perform(
        const Sample * pos,
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] * this->xfade_tilde_02_func_next(pos[(Index)i], 0) + in2[(Index)i] * this->xfade_tilde_02_func_next(pos[(Index)i], 1);
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
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
    
    number xfade_tilde_01_func_next(number pos, int channel) {
        {
            {
                number nchan_1 = 2 - 1;
    
                {
                    pos = pos * nchan_1;
                }
    
                {
                    if (pos > nchan_1)
                        pos = nchan_1;
                    else if (pos < 0)
                        pos = 0;
                }
    
                pos = pos - channel;
    
                if (pos > -1 && pos < 1) {
                    {
                        return rnbo_cos(1.57079632679489661923 * pos);
                    }
                } else {
                    return 0;
                }
            }
        }
    }
    
    void xfade_tilde_01_func_reset() {}
    
    number xfade_tilde_02_func_next(number pos, int channel) {
        {
            {
                number nchan_1 = 2 - 1;
    
                {
                    pos = pos * nchan_1;
                }
    
                {
                    if (pos > nchan_1)
                        pos = nchan_1;
                    else if (pos < 0)
                        pos = 0;
                }
    
                pos = pos - channel;
    
                if (pos > -1 && pos < 1) {
                    {
                        return rnbo_cos(1.57079632679489661923 * pos);
                    }
                } else {
                    return 0;
                }
            }
        }
    }
    
    void xfade_tilde_02_func_reset() {}
    
    void numberobj_01_init() {
        this->numberobj_01_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("Mix~/number_obj-5"), 1, this->_currentTime);
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
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("Mix~/number_obj-8"), 1, this->_currentTime);
    }
    
    void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_02_value;
    }
    
    void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_02_value_set(preset["value"]);
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
        xfade_tilde_01_pos = 0;
        xfade_tilde_02_pos = 0;
        numberobj_01_value = 0;
        numberobj_01_value_setter(numberobj_01_value);
        expr_01_in1 = 0;
        expr_01_in2 = 100;
        expr_01_out1 = 0;
        numberobj_02_value = 0;
        numberobj_02_value_setter(numberobj_02_value);
        linetilde_01_time = 10;
        linetilde_01_keepramp = 1;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        numberobj_01_currentFormat = 6;
        numberobj_01_lastValue = 0;
        numberobj_02_currentFormat = 6;
        numberobj_02_lastValue = 0;
        linetilde_01_currentValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number xfade_tilde_01_pos;
        number xfade_tilde_02_pos;
        number numberobj_01_value;
        number expr_01_in1;
        number expr_01_in2;
        number expr_01_out1;
        number numberobj_02_value;
        list linetilde_01_segments;
        number linetilde_01_time;
        number linetilde_01_keepramp;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[1];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        Int numberobj_01_currentFormat;
        number numberobj_01_lastValue;
        Int numberobj_02_currentFormat;
        number numberobj_02_lastValue;
        list linetilde_01_activeRamps;
        number linetilde_01_currentValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

RnboTubeTapeSaturation()
{
}

~RnboTubeTapeSaturation()
{
    delete this->p_01;
}

RnboTubeTapeSaturation* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
    getEngine()->flushClockEvents(this, -1214668403, false);
    getEngine()->flushClockEvents(this, 1964277200, false);
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

MillisecondTime currenttime() {
    return this->_currentTime;
}

number samplerate() {
    return this->sr;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
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

ParameterValue fromnormalized(ParameterIndex index, ParameterValue normalizedValue) {
    return this->convertFromNormalizedParameterValue(index, normalizedValue);
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
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
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);

    this->gen_01_perform(
        in1,
        this->gen_01_in2,
        this->gen_01_in3,
        this->gen_01_in4,
        this->gen_01_in5,
        this->signals[0],
        n
    );

    this->gen_02_perform(
        in2,
        this->gen_02_in2,
        this->gen_02_in3,
        this->gen_02_in4,
        this->gen_02_in5,
        this->signals[1],
        n
    );

    this->p_01_perform(in1, in2, this->signals[0], this->signals[1], out1, out2, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 2; i++) {
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

    this->gen_01_dspsetup(forceDSPSetup);
    this->gen_02_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);
    this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);

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
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 0;
}

void fillDataRef(DataRefIndex , DataRef& ) {}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->p_01->processDataViewUpdate(index, time);
}

void initialize() {
    this->assign_defaults();
    this->setState();
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

void setState() {
    this->p_01 = new RNBOSubpatcher_43();
    this->p_01->setEngineAndPatcher(this->getEngine(), this);
    this->p_01->initialize();
    this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_01_getPresetValue(getSubState(preset, "KnbDryWet"));
    this->param_02_getPresetValue(getSubState(preset, "KnbInput"));
    this->param_03_getPresetValue(getSubState(preset, "KnbDrive"));
    this->param_04_getPresetValue(getSubState(preset, "KnbBlend"));
    this->param_05_getPresetValue(getSubState(preset, "KnbOutput"));
    this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "Mix~"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_02_setPresetValue(getSubState(preset, "KnbInput"));
    this->param_03_setPresetValue(getSubState(preset, "KnbDrive"));
    this->param_04_setPresetValue(getSubState(preset, "KnbBlend"));
    this->param_05_setPresetValue(getSubState(preset, "KnbOutput"));
    this->param_01_setPresetValue(getSubState(preset, "KnbDryWet"));
}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false)) {
        this->p_01->processTempoEvent(time, tempo);
    }
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time);

    if (this->globaltransport_setState(this->_currentTime, state, false)) {
        this->p_01->processTransportEvent(time, state);
    }
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false)) {
        this->p_01->processBeatTimeEvent(time, beattime);
    }
}

void onSampleRateChanged(double ) {}

void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
    this->updateTime(time);

    if (this->globaltransport_setTimeSignature(this->_currentTime, numerator, denominator, false)) {
        this->p_01->processTimeSignatureEvent(time, numerator, denominator);
    }
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
    default:
        {
        index -= 5;

        if (index < this->p_01->getNumParameters())
            this->p_01->setParameterValue(index, v, time);

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
    default:
        {
        index -= 5;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterValue(index);

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
    return 5 + this->p_01->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "KnbDryWet";
        }
    case 1:
        {
        return "KnbInput";
        }
    case 2:
        {
        return "KnbDrive";
        }
    case 3:
        {
        return "KnbBlend";
        }
    case 4:
        {
        return "KnbOutput";
        }
    default:
        {
        index -= 5;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterName(index);

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "KnbDryWet";
        }
    case 1:
        {
        return "KnbInput";
        }
    case 2:
        {
        return "KnbDrive";
        }
    case 3:
        {
        return "KnbBlend";
        }
    case 4:
        {
        return "KnbOutput";
        }
    default:
        {
        index -= 5;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterId(index);

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
            info->initialValue = 50;
            info->min = 0;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Mix";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -48;
            info->max = 48;
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
            info->initialValue = 50;
            info->min = 0.1;
            info->max = 100;
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
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 50;
            info->min = 0;
            info->max = 100;
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
        case 4:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = -24;
            info->max = 12;
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
        default:
            {
            index -= 5;

            if (index < this->p_01->getNumParameters())
                this->p_01->getParameterInfo(index, info);

            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
    if (subpatcher == this->p_01)
        return 5;

    return 0;
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
    case 3:
        {
        {
            value = (value < 0 ? 0 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - 0) / (100 - 0);
            return normalizedValue;
        }
        }
    case 1:
        {
        {
            value = (value < -48 ? -48 : (value > 48 ? 48 : value));
            ParameterValue normalizedValue = (value - -48) / (48 - -48);
            return normalizedValue;
        }
        }
    case 2:
        {
        {
            value = (value < 0.1 ? 0.1 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - 0.1) / (100 - 0.1);
            return normalizedValue;
        }
        }
    case 4:
        {
        {
            value = (value < -24 ? -24 : (value > 12 ? 12 : value));
            ParameterValue normalizedValue = (value - -24) / (12 - -24);
            return normalizedValue;
        }
        }
    default:
        {
        index -= 5;

        if (index < this->p_01->getNumParameters())
            return this->p_01->convertToNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 0:
    case 3:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (100 - 0);
            }
        }
        }
    case 1:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return -48 + value * (48 - -48);
            }
        }
        }
    case 2:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0.1 + value * (100 - 0.1);
            }
        }
        }
    case 4:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return -24 + value * (12 - -24);
            }
        }
        }
    default:
        {
        index -= 5;

        if (index < this->p_01->getNumParameters())
            return this->p_01->convertFromNormalizedParameterValue(index, value);

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
    default:
        {
        index -= 5;

        if (index < this->p_01->getNumParameters())
            return this->p_01->constrainParameterValue(index, value);

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
    case -1214668403:
        {
        this->line_01_tick_set(value);
        break;
        }
    case 1964277200:
        {
        this->line_02_tick_set(value);
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
        if (TAG("number_obj-8") == objectId)
            this->numberobj_03_valin_set(payload);

        if (TAG("number_obj-9") == objectId)
            this->numberobj_04_valin_set(payload);

        if (TAG("number_obj-12") == objectId)
            this->numberobj_05_valin_set(payload);

        if (TAG("number_obj-15") == objectId)
            this->numberobj_06_valin_set(payload);

        if (TAG("number_obj-7") == objectId)
            this->numberobj_07_valin_set(payload);

        break;
        }
    case TAG("format"):
        {
        if (TAG("number_obj-8") == objectId)
            this->numberobj_03_format_set(payload);

        if (TAG("number_obj-9") == objectId)
            this->numberobj_04_format_set(payload);

        if (TAG("number_obj-12") == objectId)
            this->numberobj_05_format_set(payload);

        if (TAG("number_obj-15") == objectId)
            this->numberobj_06_format_set(payload);

        if (TAG("number_obj-7") == objectId)
            this->numberobj_07_format_set(payload);

        break;
        }
    }

    this->p_01->processNumMessage(tag, objectId, time, payload);
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_01->processListMessage(tag, objectId, time, payload);
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_01->processBangMessage(tag, objectId, time);
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("valout"):
        {
        return "valout";
        }
    case TAG("number_obj-8"):
        {
        return "number_obj-8";
        }
    case TAG("setup"):
        {
        return "setup";
        }
    case TAG("number_obj-9"):
        {
        return "number_obj-9";
        }
    case TAG("number_obj-12"):
        {
        return "number_obj-12";
        }
    case TAG("number_obj-15"):
        {
        return "number_obj-15";
        }
    case TAG("number_obj-7"):
        {
        return "number_obj-7";
        }
    case TAG("valin"):
        {
        return "valin";
        }
    case TAG("format"):
        {
        return "format";
        }
    }

    auto subpatchResult_0 = this->p_01->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

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

    this->numberobj_03_value_set(v);
}

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(1, false);

    if (this->param_02_value != this->param_02_lastValue) {
        this->getEngine()->presetTouched();
        this->param_02_lastValue = this->param_02_value;
    }

    this->numberobj_04_value_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(2, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->expr_03_in1_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(3, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    {
        list converted = {v};
        this->scale_01_input_set(converted);
    }
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(4, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    this->numberobj_07_value_set(v);
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

void line_01_tick_set(number v) {
    this->line_01_output_set(v);

    if ((bool)(this->line_01_isFinished(v))) {
        this->line_01_slope = 0;
        this->line_01_startValue = v;
        this->line_01_startPendingRamp();
    } else {
        this->line_01_scheduleNext();
    }
}

void numberobj_05_valin_set(number v) {
    this->numberobj_05_value_set(v);
}

void numberobj_05_format_set(number v) {
    this->numberobj_05_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void line_02_tick_set(number v) {
    this->line_02_output_set(v);

    if ((bool)(this->line_02_isFinished(v))) {
        this->line_02_slope = 0;
        this->line_02_startValue = v;
        this->line_02_startPendingRamp();
    } else {
        this->line_02_scheduleNext();
    }
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
    return 2;
}

void allocateDataRefs() {
    this->p_01->allocateDataRefs();
}

void initializeObjects() {
    this->numberobj_03_init();
    this->numberobj_04_init();
    this->numberobj_05_init();
    this->gen_01_prevout_init();
    this->gen_01_prevmed_init();
    this->gen_01_med_init();
    this->numberobj_06_init();
    this->gen_02_prevout_init();
    this->gen_02_prevmed_init();
    this->gen_02_med_init();
    this->numberobj_07_init();
    this->p_01->initializeObjects();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());
    this->p_01->startup();

    {
        this->scheduleParamInit(0, 10);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 0);
    }

    {
        this->scheduleParamInit(3, 0);
    }

    {
        this->scheduleParamInit(4, 0);
    }

    this->processParamInitEvents();
}

static number param_01_value_constrain(number v) {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void p_01_in5_number_set(number v) {
    this->p_01->updateTime(this->_currentTime);
    this->p_01->eventinlet_01_out1_number_set(v);
}

void numberobj_03_output_set(number v) {
    this->p_01_in5_number_set(v);
}

void numberobj_03_value_set(number v) {
    this->numberobj_03_value_setter(v);
    v = this->numberobj_03_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_03_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-8"), localvalue, this->_currentTime);
    this->numberobj_03_output_set(localvalue);
}

static number param_02_value_constrain(number v) {
    v = (v > 48 ? 48 : (v < -48 ? -48 : v));
    return v;
}

void gen_02_in2_set(number v) {
    this->gen_02_in2 = v;
}

void gen_01_in2_set(number v) {
    this->gen_01_in2 = v;
}

void numberobj_04_output_set(number v) {
    this->gen_02_in2_set(v);
    this->gen_01_in2_set(v);
}

void numberobj_04_value_set(number v) {
    this->numberobj_04_value_setter(v);
    v = this->numberobj_04_value;
    number localvalue = v;

    if (this->numberobj_04_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-9"), localvalue, this->_currentTime);
    this->numberobj_04_output_set(localvalue);
}

static number param_03_value_constrain(number v) {
    v = (v > 100 ? 100 : (v < 0.1 ? 0.1 : v));
    return v;
}

static number line_01_time_constrain(number v) {
    if (v < 0)
        v = 0;

    return v;
}

void line_01_time_set(number v) {
    v = this->line_01_time_constrain(v);
    this->line_01_time = v;
}

void gen_02_in3_set(number v) {
    this->gen_02_in3 = v;
}

void gen_01_in3_set(number v) {
    this->gen_01_in3 = v;
}

void numberobj_05_output_set(number v) {
    this->gen_02_in3_set(v);
    this->gen_01_in3_set(v);
}

void numberobj_05_value_set(number v) {
    this->numberobj_05_value_setter(v);
    v = this->numberobj_05_value;
    number localvalue = v;

    if (this->numberobj_05_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-12"), localvalue, this->_currentTime);
    this->numberobj_05_output_set(localvalue);
}

void line_01_output_set(number v) {
    this->line_01_output = v;
    this->numberobj_05_value_set(v);
}

void line_01_stop_bang() {
    this->getEngine()->flushClockEvents(this, -1214668403, false);;
    this->line_01_pendingRamps->length = 0;
    this->line_01_startValue = this->line_01_output;
    this->line_01_slope = 0;
    this->line_01__time = 0;
    this->line_01_time_set(0);
}

static number line_01_grain_constrain(number v) {
    if (v < 0)
        v = 0;

    return v;
}

void line_01_grain_set(number v) {
    v = this->line_01_grain_constrain(v);
    this->line_01_grain = v;

    if ((bool)(!(bool)(this->line_01_isFinished(this->line_01_startValue)))) {
        this->getEngine()->flushClockEvents(this, -1214668403, false);;
        this->line_01_scheduleNext();
    }
}

void line_01_end_bang() {}

void line_01_target_set(const list& v) {
    this->line_01_target = jsCreateListCopy(v);
    this->line_01_pendingRamps->length = 0;

    if (v->length == 1) {
        this->line_01__time = this->line_01_time;
        this->line_01_time_set(0);

        if ((bool)(this->line_01__time))
            this->line_01_startRamp(v[0], this->line_01__time);
        else {
            this->line_01_output_set(v[0]);
            this->line_01_startValue = v[0];
            this->line_01_stop_bang();
        }
    } else if (v->length == 2) {
        this->line_01_time_set(0);
        this->line_01__time = (v[1] < 0 ? 0 : v[1]);
        this->line_01_startRamp(v[0], this->line_01__time);
    } else if (v->length == 3) {
        this->line_01_time_set(0);
        this->line_01_grain_set(v[2]);
        this->line_01__time = (v[1] < 0 ? 0 : v[1]);
        this->line_01_startRamp(v[0], this->line_01__time);
    } else {
        this->line_01_time_set(0);
        this->line_01_pendingRamps = jsCreateListCopy(v);
        this->line_01_startPendingRamp();
    }
}

void expr_03_out1_set(number v) {
    this->expr_03_out1 = v;

    {
        list converted = {this->expr_03_out1};
        this->line_01_target_set(converted);
    }
}

void expr_03_in1_set(number in1) {
    this->expr_03_in1 = in1;

    this->expr_03_out1_set(
        (this->expr_03_in2 == 0 ? 0 : (this->expr_03_in2 == 0. ? 0. : this->expr_03_in1 / this->expr_03_in2))
    );//#map:/_obj-6:1
}

static number param_04_value_constrain(number v) {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

static number line_02_time_constrain(number v) {
    if (v < 0)
        v = 0;

    return v;
}

void line_02_time_set(number v) {
    v = this->line_02_time_constrain(v);
    this->line_02_time = v;
}

void gen_02_in4_set(number v) {
    this->gen_02_in4 = v;
}

void gen_01_in4_set(number v) {
    this->gen_01_in4 = v;
}

void line_02_output_set(number v) {
    this->line_02_output = v;
    this->gen_02_in4_set(v);
    this->gen_01_in4_set(v);
}

void line_02_stop_bang() {
    this->getEngine()->flushClockEvents(this, 1964277200, false);;
    this->line_02_pendingRamps->length = 0;
    this->line_02_startValue = this->line_02_output;
    this->line_02_slope = 0;
    this->line_02__time = 0;
    this->line_02_time_set(0);
}

static number line_02_grain_constrain(number v) {
    if (v < 0)
        v = 0;

    return v;
}

void line_02_grain_set(number v) {
    v = this->line_02_grain_constrain(v);
    this->line_02_grain = v;

    if ((bool)(!(bool)(this->line_02_isFinished(this->line_02_startValue)))) {
        this->getEngine()->flushClockEvents(this, 1964277200, false);;
        this->line_02_scheduleNext();
    }
}

void line_02_end_bang() {}

void line_02_target_set(const list& v) {
    this->line_02_target = jsCreateListCopy(v);
    this->line_02_pendingRamps->length = 0;

    if (v->length == 1) {
        this->line_02__time = this->line_02_time;
        this->line_02_time_set(0);

        if ((bool)(this->line_02__time))
            this->line_02_startRamp(v[0], this->line_02__time);
        else {
            this->line_02_output_set(v[0]);
            this->line_02_startValue = v[0];
            this->line_02_stop_bang();
        }
    } else if (v->length == 2) {
        this->line_02_time_set(0);
        this->line_02__time = (v[1] < 0 ? 0 : v[1]);
        this->line_02_startRamp(v[0], this->line_02__time);
    } else if (v->length == 3) {
        this->line_02_time_set(0);
        this->line_02_grain_set(v[2]);
        this->line_02__time = (v[1] < 0 ? 0 : v[1]);
        this->line_02_startRamp(v[0], this->line_02__time);
    } else {
        this->line_02_time_set(0);
        this->line_02_pendingRamps = jsCreateListCopy(v);
        this->line_02_startPendingRamp();
    }
}

void numberobj_06_output_set(number v) {
    {
        list converted = {v};
        this->line_02_target_set(converted);
    }
}

void numberobj_06_value_set(number v) {
    this->numberobj_06_value_setter(v);
    v = this->numberobj_06_value;
    number localvalue = v;

    if (this->numberobj_06_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-15"), localvalue, this->_currentTime);
    this->numberobj_06_output_set(localvalue);
}

void scale_01_out_set(const list& v) {
    this->scale_01_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_06_value_set(converted);
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

static number param_05_value_constrain(number v) {
    v = (v > 12 ? 12 : (v < -24 ? -24 : v));
    return v;
}

void gen_02_in5_set(number v) {
    this->gen_02_in5 = v;
}

void gen_01_in5_set(number v) {
    this->gen_01_in5 = v;
}

void numberobj_07_output_set(number v) {
    this->gen_02_in5_set(v);
    this->gen_01_in5_set(v);
}

void numberobj_07_value_set(number v) {
    this->numberobj_07_value_setter(v);
    v = this->numberobj_07_value;
    number localvalue = v;

    if (this->numberobj_07_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-7"), localvalue, this->_currentTime);
    this->numberobj_07_output_set(localvalue);
}

void ctlin_01_outchannel_set(number ) {}

void ctlin_01_outcontroller_set(number ) {}

void fromnormalized_01_output_set(number v) {
    this->param_01_value_set(v);
}

void fromnormalized_01_input_set(number v) {
    this->fromnormalized_01_output_set(this->fromnormalized(0, v));
}

void expr_02_out1_set(number v) {
    this->expr_02_out1 = v;
    this->fromnormalized_01_input_set(this->expr_02_out1);
}

void expr_02_in1_set(number in1) {
    this->expr_02_in1 = in1;
    this->expr_02_out1_set(this->expr_02_in1 * this->expr_02_in2);//#map:expr_02:1
}

void ctlin_01_value_set(number v) {
    this->expr_02_in1_set(v);
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

void gen_01_perform(
    const Sample * in1,
    number in2,
    number in3,
    number in4,
    number in5,
    SampleValue * out1,
    Index n
) {
    auto __gen_01_prevout_value = this->gen_01_prevout_value;
    auto __gen_01_prevmed_value = this->gen_01_prevmed_value;
    auto __gen_01_med_value = this->gen_01_med_value;
    number ingain_0 = rnbo_pow(10., ((in2 > 48 ? 48 : (in2 < -48 ? -48 : in2))) * 0.05);
    number outgain_1 = rnbo_pow(10., ((in5 > 12 ? 12 : (in5 < -24 ? -24 : in5))) * 0.05);
    number drive_2 = (in3 > 10 ? 10 : (in3 < 0.1 ? 0.1 : in3));
    number blend_3 = (in4 > 10 ? 10 : (in4 < -10 ? -10 : in4));
    number rdrive_4 = (drive_2 == 0. ? 0. : (number)12 / drive_2);
    number rbdr_6 = ((10.5 - blend_3 == 0. ? 0. : rdrive_4 / (10.5 - blend_3))) * 780 / (number)33;
    number rbdr2_7 = rbdr_6 * rbdr_6;
    number srct_31 = (0.1 * this->samplerate() + 1 == 0. ? 0. : 0.1 * this->samplerate() / (0.1 * this->samplerate() + 1));
    Index i;

    for (i = 0; i < n; i++) {
        number rdrive2_5 = rdrive_4 * rdrive_4;
        number D_8 = 0;

        {
            auto x_9 = 2 * rdrive2_5 - 1;
            number EPS_10 = 1e-9;
            number xgeps_11 = x_9 > EPS_10;
            number xleps_12 = x_9 < -EPS_10;
            number geps_13 = ((bool)(xgeps_11) ? (x_9 <= 0 ? 0 : rnbo_sqrt(x_9)) : 0);
            D_8 = ((bool)(xleps_12) ? (-x_9 <= 0 ? 0 : rnbo_sqrt(-x_9)) : geps_13);
        }

        number kpa_14 = D_8 + 1;
        number kpb_15 = (2 - kpa_14) / (number)2;
        number ap_16 = (rdrive2_5 - kpa_14 + 1) / (number)2;
        number D_17 = 0;

        {
            number D_19 = 0;

            {
                auto x_20 = 2 * rdrive2_5 - 1;
                number EPS_21 = 1e-9;
                number xgeps_22 = x_20 > EPS_21;
                number xleps_23 = x_20 < -EPS_21;
                number geps_24 = ((bool)(xgeps_22) ? (x_20 <= 0 ? 0 : rnbo_sqrt(x_20)) : 0);
                D_19 = ((bool)(xleps_23) ? (-x_20 <= 0 ? 0 : rnbo_sqrt(-x_20)) : geps_24);
            }

            auto x_18 = 2 * D_19 - 2 * rdrive2_5;
            number EPS_25 = 1e-9;
            number xgeps_26 = x_18 > EPS_25;
            number xleps_27 = x_18 < -EPS_25;
            number geps_28 = ((bool)(xgeps_26) ? (x_18 <= 0 ? 0 : rnbo_sqrt(x_18)) : 0);
            D_17 = ((bool)(xleps_27) ? (-x_18 <= 0 ? 0 : rnbo_sqrt(-x_18)) : geps_28);
        }

        number kc_29 = (D_17 == 0. ? 0. : kpa_14 / D_17);
        number kc2_30 = kc_29 * kc_29;
        number sq_32 = kc2_30 + 1;
        number D_33 = 0;

        {
            auto x_34 = sq_32;
            number EPS_35 = 1e-9;
            number xgeps_36 = x_34 > EPS_35;
            number xleps_37 = x_34 < -EPS_35;
            number geps_38 = ((bool)(xgeps_36) ? (x_34 <= 0 ? 0 : rnbo_sqrt(x_34)) : 0);
            D_33 = ((bool)(xleps_37) ? (-x_34 <= 0 ? 0 : rnbo_sqrt(-x_34)) : geps_38);
        }

        number knb_39 = (D_33 == 0. ? 0. : -1 * rbdr_6 / D_33);
        number D_40 = 0;

        {
            auto x_41 = sq_32;
            number EPS_42 = 1e-9;
            number xgeps_43 = x_41 > EPS_42;
            number xleps_44 = x_41 < -EPS_42;
            number geps_45 = ((bool)(xgeps_43) ? (x_41 <= 0 ? 0 : rnbo_sqrt(x_41)) : 0);
            D_40 = ((bool)(xleps_44) ? (-x_41 <= 0 ? 0 : rnbo_sqrt(-x_41)) : geps_45);
        }

        number kna_46 = (D_40 == 0. ? 0. : 2 * kc_29 * rbdr_6 / D_40);
        number an_47 = (sq_32 == 0. ? 0. : rbdr2_7 / sq_32);
        number D_48 = 0;

        {
            auto x_49 = 2 * kna_46 + 4 * an_47 - 1;
            number EPS_50 = 1e-9;
            number xgeps_51 = x_49 > EPS_50;
            number xleps_52 = x_49 < -EPS_50;
            number geps_53 = ((bool)(xgeps_51) ? (x_49 <= 0 ? 0 : rnbo_sqrt(x_49)) : 0);
            D_48 = ((bool)(xleps_52) ? (-x_49 <= 0 ? 0 : rnbo_sqrt(-x_49)) : geps_53);
        }

        number imr_54 = 2 * knb_39 + D_48;
        number pwrq_55 = (imr_54 + 1 == 0. ? 0. : (number)2 / (imr_54 + 1));
        number xin_56 = in1[(Index)i] * ingain_0;
        number ifmed_57 = xin_56 >= 0;
        number D_58 = 0;

        {
            auto x_59 = ap_16 + xin_56 * (kpa_14 - xin_56);
            number EPS_60 = 1e-9;
            number xgeps_61 = x_59 > EPS_60;
            number xleps_62 = x_59 < -EPS_60;
            number geps_63 = ((bool)(xgeps_61) ? (x_59 <= 0 ? 0 : rnbo_sqrt(x_59)) : 0);
            D_58 = ((bool)(xleps_62) ? (-x_59 <= 0 ? 0 : rnbo_sqrt(-x_59)) : geps_63);
        }

        number med1_64 = (D_58 + kpb_15) * pwrq_55;
        number D_65 = 0;

        {
            auto x_66 = an_47 - xin_56 * (kna_46 + xin_56);
            number EPS_67 = 1e-9;
            number xgeps_68 = x_66 > EPS_67;
            number xleps_69 = x_66 < -EPS_67;
            number geps_70 = ((bool)(xgeps_68) ? (x_66 <= 0 ? 0 : rnbo_sqrt(x_66)) : 0);
            D_65 = ((bool)(xleps_69) ? (-x_66 <= 0 ? 0 : rnbo_sqrt(-x_66)) : geps_70);
        }

        number med2_71 = (D_65 + knb_39) * pwrq_55 * -1;
        __gen_01_med_value = ((bool)(ifmed_57) ? med1_64 : med2_71);

        auto y_72 = this->maximum(
            srct_31 * (__gen_01_med_value - __gen_01_prevmed_value + __gen_01_prevout_value),
            -1
        );

        number M_73 = 0;

        {
            auto x_74 = __gen_01_med_value;
            number EPS_75 = 1e-9;
            number xgeps_76 = x_74 > EPS_75;
            number xleps_77 = x_74 < -EPS_75;
            number glps_78 = (xgeps_76 + xleps_77 > 1 ? 1 : (xgeps_76 + xleps_77 < 0 ? 0 : xgeps_76 + xleps_77));
            M_73 = ((bool)(glps_78) ? x_74 : 0);
        }

        __gen_01_prevmed_value = M_73;
        number M_79 = 0;

        {
            auto x_80 = y_72;
            number EPS_81 = 1e-9;
            number xgeps_82 = x_80 > EPS_81;
            number xleps_83 = x_80 < -EPS_81;
            number glps_84 = (xgeps_82 + xleps_83 > 1 ? 1 : (xgeps_82 + xleps_83 < 0 ? 0 : xgeps_82 + xleps_83));
            M_79 = ((bool)(glps_84) ? x_80 : 0);
        }

        __gen_01_prevout_value = M_79;
        number expr_1_86 = this->gen_01_dcblock_85_next(y_72 * outgain_1, 0.9997);
        out1[(Index)i] = expr_1_86;
    }

    this->gen_01_med_value = __gen_01_med_value;
    this->gen_01_prevmed_value = __gen_01_prevmed_value;
    this->gen_01_prevout_value = __gen_01_prevout_value;
}

void gen_02_perform(
    const Sample * in1,
    number in2,
    number in3,
    number in4,
    number in5,
    SampleValue * out1,
    Index n
) {
    auto __gen_02_prevout_value = this->gen_02_prevout_value;
    auto __gen_02_prevmed_value = this->gen_02_prevmed_value;
    auto __gen_02_med_value = this->gen_02_med_value;
    number ingain_0 = rnbo_pow(10., ((in2 > 48 ? 48 : (in2 < -48 ? -48 : in2))) * 0.05);
    number outgain_1 = rnbo_pow(10., ((in5 > 12 ? 12 : (in5 < -24 ? -24 : in5))) * 0.05);
    number drive_2 = (in3 > 10 ? 10 : (in3 < 0.1 ? 0.1 : in3));
    number blend_3 = (in4 > 10 ? 10 : (in4 < -10 ? -10 : in4));
    number rdrive_4 = (drive_2 == 0. ? 0. : (number)12 / drive_2);
    number rbdr_6 = ((10.5 - blend_3 == 0. ? 0. : rdrive_4 / (10.5 - blend_3))) * 780 / (number)33;
    number rbdr2_7 = rbdr_6 * rbdr_6;
    number srct_31 = (0.1 * this->samplerate() + 1 == 0. ? 0. : 0.1 * this->samplerate() / (0.1 * this->samplerate() + 1));
    Index i;

    for (i = 0; i < n; i++) {
        number rdrive2_5 = rdrive_4 * rdrive_4;
        number D_8 = 0;

        {
            auto x_9 = 2 * rdrive2_5 - 1;
            number EPS_10 = 1e-9;
            number xgeps_11 = x_9 > EPS_10;
            number xleps_12 = x_9 < -EPS_10;
            number geps_13 = ((bool)(xgeps_11) ? (x_9 <= 0 ? 0 : rnbo_sqrt(x_9)) : 0);
            D_8 = ((bool)(xleps_12) ? (-x_9 <= 0 ? 0 : rnbo_sqrt(-x_9)) : geps_13);
        }

        number kpa_14 = D_8 + 1;
        number kpb_15 = (2 - kpa_14) / (number)2;
        number ap_16 = (rdrive2_5 - kpa_14 + 1) / (number)2;
        number D_17 = 0;

        {
            number D_19 = 0;

            {
                auto x_20 = 2 * rdrive2_5 - 1;
                number EPS_21 = 1e-9;
                number xgeps_22 = x_20 > EPS_21;
                number xleps_23 = x_20 < -EPS_21;
                number geps_24 = ((bool)(xgeps_22) ? (x_20 <= 0 ? 0 : rnbo_sqrt(x_20)) : 0);
                D_19 = ((bool)(xleps_23) ? (-x_20 <= 0 ? 0 : rnbo_sqrt(-x_20)) : geps_24);
            }

            auto x_18 = 2 * D_19 - 2 * rdrive2_5;
            number EPS_25 = 1e-9;
            number xgeps_26 = x_18 > EPS_25;
            number xleps_27 = x_18 < -EPS_25;
            number geps_28 = ((bool)(xgeps_26) ? (x_18 <= 0 ? 0 : rnbo_sqrt(x_18)) : 0);
            D_17 = ((bool)(xleps_27) ? (-x_18 <= 0 ? 0 : rnbo_sqrt(-x_18)) : geps_28);
        }

        number kc_29 = (D_17 == 0. ? 0. : kpa_14 / D_17);
        number kc2_30 = kc_29 * kc_29;
        number sq_32 = kc2_30 + 1;
        number D_33 = 0;

        {
            auto x_34 = sq_32;
            number EPS_35 = 1e-9;
            number xgeps_36 = x_34 > EPS_35;
            number xleps_37 = x_34 < -EPS_35;
            number geps_38 = ((bool)(xgeps_36) ? (x_34 <= 0 ? 0 : rnbo_sqrt(x_34)) : 0);
            D_33 = ((bool)(xleps_37) ? (-x_34 <= 0 ? 0 : rnbo_sqrt(-x_34)) : geps_38);
        }

        number knb_39 = (D_33 == 0. ? 0. : -1 * rbdr_6 / D_33);
        number D_40 = 0;

        {
            auto x_41 = sq_32;
            number EPS_42 = 1e-9;
            number xgeps_43 = x_41 > EPS_42;
            number xleps_44 = x_41 < -EPS_42;
            number geps_45 = ((bool)(xgeps_43) ? (x_41 <= 0 ? 0 : rnbo_sqrt(x_41)) : 0);
            D_40 = ((bool)(xleps_44) ? (-x_41 <= 0 ? 0 : rnbo_sqrt(-x_41)) : geps_45);
        }

        number kna_46 = (D_40 == 0. ? 0. : 2 * kc_29 * rbdr_6 / D_40);
        number an_47 = (sq_32 == 0. ? 0. : rbdr2_7 / sq_32);
        number D_48 = 0;

        {
            auto x_49 = 2 * kna_46 + 4 * an_47 - 1;
            number EPS_50 = 1e-9;
            number xgeps_51 = x_49 > EPS_50;
            number xleps_52 = x_49 < -EPS_50;
            number geps_53 = ((bool)(xgeps_51) ? (x_49 <= 0 ? 0 : rnbo_sqrt(x_49)) : 0);
            D_48 = ((bool)(xleps_52) ? (-x_49 <= 0 ? 0 : rnbo_sqrt(-x_49)) : geps_53);
        }

        number imr_54 = 2 * knb_39 + D_48;
        number pwrq_55 = (imr_54 + 1 == 0. ? 0. : (number)2 / (imr_54 + 1));
        number xin_56 = in1[(Index)i] * ingain_0;
        number ifmed_57 = xin_56 >= 0;
        number D_58 = 0;

        {
            auto x_59 = ap_16 + xin_56 * (kpa_14 - xin_56);
            number EPS_60 = 1e-9;
            number xgeps_61 = x_59 > EPS_60;
            number xleps_62 = x_59 < -EPS_60;
            number geps_63 = ((bool)(xgeps_61) ? (x_59 <= 0 ? 0 : rnbo_sqrt(x_59)) : 0);
            D_58 = ((bool)(xleps_62) ? (-x_59 <= 0 ? 0 : rnbo_sqrt(-x_59)) : geps_63);
        }

        number med1_64 = (D_58 + kpb_15) * pwrq_55;
        number D_65 = 0;

        {
            auto x_66 = an_47 - xin_56 * (kna_46 + xin_56);
            number EPS_67 = 1e-9;
            number xgeps_68 = x_66 > EPS_67;
            number xleps_69 = x_66 < -EPS_67;
            number geps_70 = ((bool)(xgeps_68) ? (x_66 <= 0 ? 0 : rnbo_sqrt(x_66)) : 0);
            D_65 = ((bool)(xleps_69) ? (-x_66 <= 0 ? 0 : rnbo_sqrt(-x_66)) : geps_70);
        }

        number med2_71 = (D_65 + knb_39) * pwrq_55 * -1;
        __gen_02_med_value = ((bool)(ifmed_57) ? med1_64 : med2_71);

        auto y_72 = this->maximum(
            srct_31 * (__gen_02_med_value - __gen_02_prevmed_value + __gen_02_prevout_value),
            -1
        );

        number M_73 = 0;

        {
            auto x_74 = __gen_02_med_value;
            number EPS_75 = 1e-9;
            number xgeps_76 = x_74 > EPS_75;
            number xleps_77 = x_74 < -EPS_75;
            number glps_78 = (xgeps_76 + xleps_77 > 1 ? 1 : (xgeps_76 + xleps_77 < 0 ? 0 : xgeps_76 + xleps_77));
            M_73 = ((bool)(glps_78) ? x_74 : 0);
        }

        __gen_02_prevmed_value = M_73;
        number M_79 = 0;

        {
            auto x_80 = y_72;
            number EPS_81 = 1e-9;
            number xgeps_82 = x_80 > EPS_81;
            number xleps_83 = x_80 < -EPS_81;
            number glps_84 = (xgeps_82 + xleps_83 > 1 ? 1 : (xgeps_82 + xleps_83 < 0 ? 0 : xgeps_82 + xleps_83));
            M_79 = ((bool)(glps_84) ? x_80 : 0);
        }

        __gen_02_prevout_value = M_79;
        number expr_1_86 = this->gen_02_dcblock_85_next(y_72 * outgain_1, 0.9997);
        out1[(Index)i] = expr_1_86;
    }

    this->gen_02_med_value = __gen_02_med_value;
    this->gen_02_prevmed_value = __gen_02_prevmed_value;
    this->gen_02_prevout_value = __gen_02_prevout_value;
}

void p_01_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    const SampleValue * in4,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: Mix~
    ConstSampleArray<4> ins = {in1, in2, in3, in4};

    SampleArray<2> outs = {out1, out2};
    this->p_01->process(ins, 4, outs, 2, n);
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void numberobj_03_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

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

void numberobj_03_init() {
    this->numberobj_03_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-8"), 1, this->_currentTime);
}

void numberobj_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_03_value;
}

void numberobj_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_03_value_set(preset["value"]);
}

void param_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_01_value;
}

void param_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_01_value_set(preset["value"]);
}

void numberobj_04_init() {
    this->numberobj_04_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-9"), 1, this->_currentTime);
}

void numberobj_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_04_value;
}

void numberobj_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_04_value_set(preset["value"]);
}

void param_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_02_value;
}

void param_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_02_value_set(preset["value"]);
}

number line_01_valueAtTime(number time) {
    return this->line_01_startValue + this->line_01_slope * (time - this->line_01_startTime);
}

void line_01_scheduleNext() {
    auto currentTime = this->currenttime();
    number nextTime = currentTime + this->line_01_grain;
    number nextValue;

    if (nextTime - this->line_01_startTime >= this->line_01__time || this->line_01_grain == 0) {
        nextTime = this->line_01_startTime + this->line_01__time;
        nextValue = this->line_01_currentTarget;
    } else {
        nextValue = this->line_01_valueAtTime(nextTime);
    }

    this->getEngine()->scheduleClockEventWithValue(this, -1214668403, nextTime - currentTime + this->_currentTime, nextValue);;
}

void line_01_startRamp(number target, MillisecondTime time) {
    auto currentTime = this->currenttime();
    this->line_01_startValue = this->line_01_valueAtTime(currentTime);
    this->line_01_startTime = currentTime;
    this->line_01_currentTarget = target;
    this->getEngine()->flushClockEvents(this, -1214668403, false);;
    number rise = target - this->line_01_startValue;
    this->line_01_slope = rise / time;
    this->line_01_scheduleNext();
}

bool line_01_isFinished(number value) {
    return value == this->line_01_currentTarget && this->currenttime() - this->line_01_startTime >= this->line_01__time;
}

void line_01_startPendingRamp() {
    if (this->line_01_pendingRamps->length < 2) {
        this->line_01_pendingRamps->length = 0;
        this->line_01__time = 0;
        this->line_01_time_set(0);
        this->line_01_end_bang();
        return;
    }

    if (this->line_01_pendingRamps->length > 1) {
        number target = this->line_01_pendingRamps->shift();
        this->line_01__time = this->line_01_pendingRamps->shift();
        this->line_01__time = (this->line_01__time < 0 ? 0 : this->line_01__time);
        this->line_01_startRamp(target, this->line_01__time);
    }
}

void numberobj_05_init() {
    this->numberobj_05_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-12"), 1, this->_currentTime);
}

void numberobj_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_05_value;
}

void numberobj_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_05_value_set(preset["value"]);
}

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
}

number gen_01_prevout_getvalue() {
    return this->gen_01_prevout_value;
}

void gen_01_prevout_setvalue(number val) {
    this->gen_01_prevout_value = val;
}

void gen_01_prevout_reset() {
    this->gen_01_prevout_value = 0;
}

void gen_01_prevout_init() {
    this->gen_01_prevout_value = 0;
}

number gen_01_prevmed_getvalue() {
    return this->gen_01_prevmed_value;
}

void gen_01_prevmed_setvalue(number val) {
    this->gen_01_prevmed_value = val;
}

void gen_01_prevmed_reset() {
    this->gen_01_prevmed_value = 0;
}

void gen_01_prevmed_init() {
    this->gen_01_prevmed_value = 0;
}

number gen_01_med_getvalue() {
    return this->gen_01_med_value;
}

void gen_01_med_setvalue(number val) {
    this->gen_01_med_value = val;
}

void gen_01_med_reset() {
    this->gen_01_med_value = 0;
}

void gen_01_med_init() {
    this->gen_01_med_value = 0;
}

number gen_01_dcblock_85_next(number x, number gain) {
    RNBO_UNUSED(gain);
    number y = x - this->gen_01_dcblock_85_xm1 + this->gen_01_dcblock_85_ym1 * 0.9997;
    this->gen_01_dcblock_85_xm1 = x;
    this->gen_01_dcblock_85_ym1 = y;
    return y;
}

void gen_01_dcblock_85_reset() {
    this->gen_01_dcblock_85_xm1 = 0;
    this->gen_01_dcblock_85_ym1 = 0;
}

void gen_01_dcblock_85_dspsetup() {
    this->gen_01_dcblock_85_reset();
}

void gen_01_dspsetup(bool force) {
    if ((bool)(this->gen_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gen_01_setupDone = true;
    this->gen_01_dcblock_85_dspsetup();
}

number line_02_valueAtTime(number time) {
    return this->line_02_startValue + this->line_02_slope * (time - this->line_02_startTime);
}

void line_02_scheduleNext() {
    auto currentTime = this->currenttime();
    number nextTime = currentTime + this->line_02_grain;
    number nextValue;

    if (nextTime - this->line_02_startTime >= this->line_02__time || this->line_02_grain == 0) {
        nextTime = this->line_02_startTime + this->line_02__time;
        nextValue = this->line_02_currentTarget;
    } else {
        nextValue = this->line_02_valueAtTime(nextTime);
    }

    this->getEngine()->scheduleClockEventWithValue(this, 1964277200, nextTime - currentTime + this->_currentTime, nextValue);;
}

void line_02_startRamp(number target, MillisecondTime time) {
    auto currentTime = this->currenttime();
    this->line_02_startValue = this->line_02_valueAtTime(currentTime);
    this->line_02_startTime = currentTime;
    this->line_02_currentTarget = target;
    this->getEngine()->flushClockEvents(this, 1964277200, false);;
    number rise = target - this->line_02_startValue;
    this->line_02_slope = rise / time;
    this->line_02_scheduleNext();
}

bool line_02_isFinished(number value) {
    return value == this->line_02_currentTarget && this->currenttime() - this->line_02_startTime >= this->line_02__time;
}

void line_02_startPendingRamp() {
    if (this->line_02_pendingRamps->length < 2) {
        this->line_02_pendingRamps->length = 0;
        this->line_02__time = 0;
        this->line_02_time_set(0);
        this->line_02_end_bang();
        return;
    }

    if (this->line_02_pendingRamps->length > 1) {
        number target = this->line_02_pendingRamps->shift();
        this->line_02__time = this->line_02_pendingRamps->shift();
        this->line_02__time = (this->line_02__time < 0 ? 0 : this->line_02__time);
        this->line_02_startRamp(target, this->line_02__time);
    }
}

void numberobj_06_init() {
    this->numberobj_06_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-15"), 1, this->_currentTime);
}

void numberobj_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_06_value;
}

void numberobj_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_06_value_set(preset["value"]);
}

void param_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_04_value;
}

void param_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_04_value_set(preset["value"]);
}

number gen_02_prevout_getvalue() {
    return this->gen_02_prevout_value;
}

void gen_02_prevout_setvalue(number val) {
    this->gen_02_prevout_value = val;
}

void gen_02_prevout_reset() {
    this->gen_02_prevout_value = 0;
}

void gen_02_prevout_init() {
    this->gen_02_prevout_value = 0;
}

number gen_02_prevmed_getvalue() {
    return this->gen_02_prevmed_value;
}

void gen_02_prevmed_setvalue(number val) {
    this->gen_02_prevmed_value = val;
}

void gen_02_prevmed_reset() {
    this->gen_02_prevmed_value = 0;
}

void gen_02_prevmed_init() {
    this->gen_02_prevmed_value = 0;
}

number gen_02_med_getvalue() {
    return this->gen_02_med_value;
}

void gen_02_med_setvalue(number val) {
    this->gen_02_med_value = val;
}

void gen_02_med_reset() {
    this->gen_02_med_value = 0;
}

void gen_02_med_init() {
    this->gen_02_med_value = 0;
}

number gen_02_dcblock_85_next(number x, number gain) {
    RNBO_UNUSED(gain);
    number y = x - this->gen_02_dcblock_85_xm1 + this->gen_02_dcblock_85_ym1 * 0.9997;
    this->gen_02_dcblock_85_xm1 = x;
    this->gen_02_dcblock_85_ym1 = y;
    return y;
}

void gen_02_dcblock_85_reset() {
    this->gen_02_dcblock_85_xm1 = 0;
    this->gen_02_dcblock_85_ym1 = 0;
}

void gen_02_dcblock_85_dspsetup() {
    this->gen_02_dcblock_85_reset();
}

void gen_02_dspsetup(bool force) {
    if ((bool)(this->gen_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gen_02_setupDone = true;
    this->gen_02_dcblock_85_dspsetup();
}

void numberobj_07_init() {
    this->numberobj_07_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-7"), 1, this->_currentTime);
}

void numberobj_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_07_value;
}

void numberobj_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_07_value_set(preset["value"]);
}

void param_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_05_value;
}

void param_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_05_value_set(preset["value"]);
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
    numberobj_03_value = 0;
    numberobj_03_value_setter(numberobj_03_value);
    param_01_value = 50;
    numberobj_04_value = 0;
    numberobj_04_value_setter(numberobj_04_value);
    param_02_value = 0;
    p_01_target = 0;
    line_01_time = 0;
    line_01_grain = 50;
    line_01_output = 0;
    expr_03_in1 = 0;
    expr_03_in2 = 10;
    expr_03_out1 = 0;
    numberobj_05_value = 0;
    numberobj_05_value_setter(numberobj_05_value);
    param_03_value = 50;
    gen_01_in1 = 0;
    gen_01_in2 = 0;
    gen_01_in3 = 0;
    gen_01_in4 = 0;
    gen_01_in5 = 0;
    scale_01_inlow = 0;
    scale_01_inhigh = 100;
    scale_01_outlow = -10;
    scale_01_outhigh = 10;
    scale_01_power = 1;
    line_02_time = 0;
    line_02_grain = 20;
    line_02_output = 0;
    numberobj_06_value = 0;
    numberobj_06_value_setter(numberobj_06_value);
    param_04_value = 50;
    gen_02_in1 = 0;
    gen_02_in2 = 0;
    gen_02_in3 = 0;
    gen_02_in4 = 0;
    gen_02_in5 = 0;
    numberobj_07_value = 0;
    numberobj_07_value_setter(numberobj_07_value);
    param_05_value = 0;
    ctlin_01_input = 0;
    ctlin_01_controller = 10;
    ctlin_01_channel = -1;
    expr_02_in1 = 0;
    expr_02_in2 = 0.007874015748;
    expr_02_out1 = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    numberobj_03_currentFormat = 6;
    numberobj_03_lastValue = 0;
    param_01_lastValue = 0;
    numberobj_04_currentFormat = 6;
    numberobj_04_lastValue = 0;
    param_02_lastValue = 0;
    line_01_startTime = 0;
    line_01_startValue = 0.2;
    line_01_currentTarget = 0;
    line_01_slope = 0;
    line_01__time = 0;
    numberobj_05_currentFormat = 6;
    numberobj_05_lastValue = 0;
    param_03_lastValue = 0;
    gen_01_prevout_value = 0;
    gen_01_prevmed_value = 0;
    gen_01_med_value = 0;
    gen_01_dcblock_85_xm1 = 0;
    gen_01_dcblock_85_ym1 = 0;
    gen_01_setupDone = false;
    line_02_startTime = 0;
    line_02_startValue = 100;
    line_02_currentTarget = 0;
    line_02_slope = 0;
    line_02__time = 0;
    numberobj_06_currentFormat = 6;
    numberobj_06_lastValue = 0;
    param_04_lastValue = 0;
    gen_02_prevout_value = 0;
    gen_02_prevmed_value = 0;
    gen_02_med_value = 0;
    gen_02_dcblock_85_xm1 = 0;
    gen_02_dcblock_85_ym1 = 0;
    gen_02_setupDone = false;
    numberobj_07_currentFormat = 6;
    numberobj_07_lastValue = 0;
    param_05_lastValue = 0;
    ctlin_01_status = 0;
    ctlin_01_byte1 = -1;
    ctlin_01_inchan = 0;
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

    number numberobj_03_value;
    number param_01_value;
    number numberobj_04_value;
    number param_02_value;
    number p_01_target;
    list line_01_target;
    number line_01_time;
    number line_01_grain;
    number line_01_output;
    number expr_03_in1;
    number expr_03_in2;
    number expr_03_out1;
    number numberobj_05_value;
    number param_03_value;
    number gen_01_in1;
    number gen_01_in2;
    number gen_01_in3;
    number gen_01_in4;
    number gen_01_in5;
    list scale_01_input;
    number scale_01_inlow;
    number scale_01_inhigh;
    number scale_01_outlow;
    number scale_01_outhigh;
    number scale_01_power;
    list scale_01_out;
    list line_02_target;
    number line_02_time;
    number line_02_grain;
    number line_02_output;
    number numberobj_06_value;
    number param_04_value;
    number gen_02_in1;
    number gen_02_in2;
    number gen_02_in3;
    number gen_02_in4;
    number gen_02_in5;
    number numberobj_07_value;
    number param_05_value;
    number ctlin_01_input;
    number ctlin_01_controller;
    number ctlin_01_channel;
    number expr_02_in1;
    number expr_02_in2;
    number expr_02_out1;
    MillisecondTime _currentTime;
    SampleIndex audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[2];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    Int numberobj_03_currentFormat;
    number numberobj_03_lastValue;
    number param_01_lastValue;
    Int numberobj_04_currentFormat;
    number numberobj_04_lastValue;
    number param_02_lastValue;
    number line_01_startTime;
    number line_01_startValue;
    number line_01_currentTarget;
    number line_01_slope;
    number line_01__time;
    list line_01_pendingRamps;
    Int numberobj_05_currentFormat;
    number numberobj_05_lastValue;
    number param_03_lastValue;
    number gen_01_prevout_value;
    number gen_01_prevmed_value;
    number gen_01_med_value;
    number gen_01_dcblock_85_xm1;
    number gen_01_dcblock_85_ym1;
    bool gen_01_setupDone;
    number line_02_startTime;
    number line_02_startValue;
    number line_02_currentTarget;
    number line_02_slope;
    number line_02__time;
    list line_02_pendingRamps;
    Int numberobj_06_currentFormat;
    number numberobj_06_lastValue;
    number param_04_lastValue;
    number gen_02_prevout_value;
    number gen_02_prevmed_value;
    number gen_02_med_value;
    number gen_02_dcblock_85_xm1;
    number gen_02_dcblock_85_ym1;
    bool gen_02_setupDone;
    Int numberobj_07_currentFormat;
    number numberobj_07_lastValue;
    number param_05_lastValue;
    int ctlin_01_status;
    int ctlin_01_byte1;
    int ctlin_01_inchan;
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
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_43* p_01;

};

PatcherInterface* createRnboTubeTapeSaturation()
{
    return new RnboTubeTapeSaturation();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr RnboTubeTapeSaturationFactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return createRnboTubeTapeSaturation;
}

} // end RNBO namespace

