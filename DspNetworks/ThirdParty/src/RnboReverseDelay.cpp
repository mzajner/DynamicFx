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

class RnboReverseDelay : public PatcherInterfaceImpl {
public:

class RNBOSubpatcher_855 : public PatcherInterfaceImpl {
    
    friend class RnboReverseDelay;
    
    public:
    
    RNBOSubpatcher_855()
    {
    }
    
    ~RNBOSubpatcher_855()
    {
    }
    
    virtual RnboReverseDelay* getPatcher() const {
        return static_cast<RnboReverseDelay *>(_parentPatcher);
    }
    
    RnboReverseDelay* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
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
        const SampleValue * in5 = (numInputs >= 5 && inputs[4] ? inputs[4] : this->zeroBuffer);
        this->xfade_tilde_01_perform(in5, in1, in3, out1, n);
        this->xfade_tilde_02_perform(in5, in2, in4, out2, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
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
    
    void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
    
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
    
    void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
    
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
        return 5;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {}
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {}
    
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
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number xfade_tilde_01_pos;
        number xfade_tilde_02_pos;
        MillisecondTime _currentTime;
        SampleIndex audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

class RNBOSubpatcher_856 : public PatcherInterfaceImpl {
    
    friend class RnboReverseDelay;
    
    public:
    
    RNBOSubpatcher_856()
    {
    }
    
    ~RNBOSubpatcher_856()
    {
    }
    
    virtual RnboReverseDelay* getPatcher() const {
        return static_cast<RnboReverseDelay *>(_parentPatcher);
    }
    
    RnboReverseDelay* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
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
        SampleValue * out3 = (numOutputs >= 3 && outputs[2] ? outputs[2] : this->dummyBuffer);
        SampleValue * out4 = (numOutputs >= 4 && outputs[3] ? outputs[3] : this->dummyBuffer);
        const SampleValue * in2 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in3 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        const SampleValue * in4 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
        const SampleValue * in5 = (numInputs >= 4 && inputs[3] ? inputs[3] : this->zeroBuffer);
        const SampleValue * in6 = (numInputs >= 5 && inputs[4] ? inputs[4] : this->zeroBuffer);
        const SampleValue * in8 = (numInputs >= 6 && inputs[5] ? inputs[5] : this->zeroBuffer);
        const SampleValue * in9 = (numInputs >= 7 && inputs[6] ? inputs[6] : this->zeroBuffer);
        const SampleValue * in10 = (numInputs >= 8 && inputs[7] ? inputs[7] : this->zeroBuffer);
        const SampleValue * in11 = (numInputs >= 9 && inputs[8] ? inputs[8] : this->zeroBuffer);
        const SampleValue * in12 = (numInputs >= 10 && inputs[9] ? inputs[9] : this->zeroBuffer);
        const SampleValue * in13 = (numInputs >= 11 && inputs[10] ? inputs[10] : this->zeroBuffer);
        this->selector_02_perform(this->selector_02_onoff, in2, in3, in4, in5, this->signals[0], n);
        this->xfade_tilde_03_perform(in8, in2, in3, in4, in5, this->signals[1], n);
        this->selector_01_perform(this->selector_01_onoff, this->signals[0], this->signals[1], out4, n);
        this->dspexpr_01_perform(in6, out4, out1, n);
        this->selector_04_perform(this->selector_04_onoff, in10, in11, in12, in13, this->signals[1], n);
        this->xfade_tilde_04_perform(in8, in10, in11, in12, in13, this->signals[0], n);
        this->selector_03_perform(this->selector_03_onoff, this->signals[1], this->signals[0], out3, n);
        this->dspexpr_02_perform(in9, out3, out2, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 2; i++) {
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
    
    void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}
    
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
    
    void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag , MessageTag , MillisecondTime ) {}
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
    
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
    
    void eventinlet_01_out1_bang_bang() {}
    
    void eventinlet_01_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->selector_03_onoff_set(converted);
        }
    
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->selector_01_onoff_set(converted);
        }
    }
    
    void eventinlet_02_out1_bang_bang() {}
    
    void eventinlet_02_out1_list_set(const list& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->selector_04_onoff_set(converted);
        }
    
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->selector_02_onoff_set(converted);
        }
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
        return 11;
    }
    
    Index getNumOutputChannels() const {
        return 4;
    }
    
    void initializeObjects() {}
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void allocateDataRefs() {}
    
    void selector_04_onoff_set(number v) {
        this->selector_04_onoff = v;
    }
    
    void selector_02_onoff_set(number v) {
        this->selector_02_onoff = v;
    }
    
    void eventinlet_02_out1_number_set(number v) {
        this->selector_04_onoff_set(v);
        this->selector_02_onoff_set(v);
    }
    
    void selector_03_onoff_set(number v) {
        this->selector_03_onoff = v;
    }
    
    void selector_01_onoff_set(number v) {
        this->selector_01_onoff = v;
    }
    
    void eventinlet_01_out1_number_set(number v) {
        this->selector_03_onoff_set(v);
        this->selector_01_onoff_set(v);
    }
    
    void selector_02_perform(
        number onoff,
        const SampleValue * in1,
        const SampleValue * in2,
        const SampleValue * in3,
        const SampleValue * in4,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            if (onoff >= 1 && onoff < 2)
                out[(Index)i] = in1[(Index)i];
            else if (onoff >= 2 && onoff < 3)
                out[(Index)i] = in2[(Index)i];
            else if (onoff >= 3 && onoff < 4)
                out[(Index)i] = in3[(Index)i];
            else if (onoff >= 4 && onoff < 5)
                out[(Index)i] = in4[(Index)i];
            else
                out[(Index)i] = 0;
        }
    }
    
    void xfade_tilde_03_perform(
        const Sample * pos,
        const SampleValue * in1,
        const SampleValue * in2,
        const SampleValue * in3,
        const SampleValue * in4,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] * this->xfade_tilde_03_func_next(pos[(Index)i], 0) + in2[(Index)i] * this->xfade_tilde_03_func_next(pos[(Index)i], 1) + in3[(Index)i] * this->xfade_tilde_03_func_next(pos[(Index)i], 2) + in4[(Index)i] * this->xfade_tilde_03_func_next(pos[(Index)i], 3);
        }
    }
    
    void selector_01_perform(
        number onoff,
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            if (onoff >= 1 && onoff < 2)
                out[(Index)i] = in1[(Index)i];
            else if (onoff >= 2 && onoff < 3)
                out[(Index)i] = in2[(Index)i];
            else
                out[(Index)i] = 0;
        }
    }
    
    void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void selector_04_perform(
        number onoff,
        const SampleValue * in1,
        const SampleValue * in2,
        const SampleValue * in3,
        const SampleValue * in4,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            if (onoff >= 1 && onoff < 2)
                out[(Index)i] = in1[(Index)i];
            else if (onoff >= 2 && onoff < 3)
                out[(Index)i] = in2[(Index)i];
            else if (onoff >= 3 && onoff < 4)
                out[(Index)i] = in3[(Index)i];
            else if (onoff >= 4 && onoff < 5)
                out[(Index)i] = in4[(Index)i];
            else
                out[(Index)i] = 0;
        }
    }
    
    void xfade_tilde_04_perform(
        const Sample * pos,
        const SampleValue * in1,
        const SampleValue * in2,
        const SampleValue * in3,
        const SampleValue * in4,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] * this->xfade_tilde_04_func_next(pos[(Index)i], 0) + in2[(Index)i] * this->xfade_tilde_04_func_next(pos[(Index)i], 1) + in3[(Index)i] * this->xfade_tilde_04_func_next(pos[(Index)i], 2) + in4[(Index)i] * this->xfade_tilde_04_func_next(pos[(Index)i], 3);
        }
    }
    
    void selector_03_perform(
        number onoff,
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            if (onoff >= 1 && onoff < 2)
                out[(Index)i] = in1[(Index)i];
            else if (onoff >= 2 && onoff < 3)
                out[(Index)i] = in2[(Index)i];
            else
                out[(Index)i] = 0;
        }
    }
    
    void dspexpr_02_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    number xfade_tilde_03_func_next(number pos, int channel) {
        {
            {
                number nchan_1 = 4 - 1;
    
                {
                    if (pos > nchan_1)
                        pos = nchan_1;
                    else if (pos < 0)
                        pos = 0;
                }
    
                pos = pos - channel;
    
                if (pos > -1 && pos < 1) {
                    {
                        {
                            return 1.0 - rnbo_abs(pos);
                        }
                    }
                } else {
                    return 0;
                }
            }
        }
    }
    
    void xfade_tilde_03_func_reset() {}
    
    number xfade_tilde_04_func_next(number pos, int channel) {
        {
            {
                number nchan_1 = 4 - 1;
    
                {
                    if (pos > nchan_1)
                        pos = nchan_1;
                    else if (pos < 0)
                        pos = 0;
                }
    
                pos = pos - channel;
    
                if (pos > -1 && pos < 1) {
                    {
                        {
                            return 1.0 - rnbo_abs(pos);
                        }
                    }
                } else {
                    return 0;
                }
            }
        }
    }
    
    void xfade_tilde_04_func_reset() {}
    
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
        selector_01_onoff = 1;
        selector_02_onoff = 1;
        xfade_tilde_03_pos = 0;
        dspexpr_02_in1 = 0;
        dspexpr_02_in2 = 0;
        selector_03_onoff = 1;
        selector_04_onoff = 1;
        xfade_tilde_04_pos = 0;
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
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number dspexpr_01_in1;
        number dspexpr_01_in2;
        number selector_01_onoff;
        number selector_02_onoff;
        number xfade_tilde_03_pos;
        number dspexpr_02_in1;
        number dspexpr_02_in2;
        number selector_03_onoff;
        number selector_04_onoff;
        number xfade_tilde_04_pos;
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
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
    
};

RnboReverseDelay()
{
}

~RnboReverseDelay()
{
    delete this->p_01;
    delete this->p_02;
}

RnboReverseDelay* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
    getEngine()->flushClockEvents(this, -62043057, false);
    getEngine()->flushClockEvents(this, 1114681293, false);
    getEngine()->flushClockEvents(this, -2003561653, false);
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

number maximum(number x, number y) {
    return (x < y ? y : x);
}

number samplerate() {
    return this->sr;
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

template <typename T> inline number dim(T& buffer) {
    return buffer->getSize();
}

template <typename T> inline number channels(T& buffer) {
    return buffer->getChannels();
}

inline number intnum(const number value) {
    return trunc(value);
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

template <typename T> inline void poke_default(
    T& buffer,
    SampleValue value,
    SampleValue sampleIndex,
    int channel,
    number overdub
) {
    number bufferSize = buffer->getSize();
    const Index bufferChannels = (const Index)(buffer->getChannels());

    if (bufferSize > 0 && (5 != 5 || (sampleIndex >= 0 && sampleIndex < bufferSize)) && (5 != 5 || (channel >= 0 && channel < bufferChannels))) {
        if (overdub != 0) {
            number currentValue = buffer->getSample(channel, sampleIndex);

            {
                value = value * (1. - overdub) + currentValue * overdub;
            }
        }

        buffer->setSample(channel, sampleIndex, value);
        buffer->setTouched(true);
    }
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
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

number triangle(number phase, number duty) {
    number p1 = duty;
    auto wrappedPhase = this->wrap(phase, 0., 1.);
    p1 = (p1 > 1. ? 1. : (p1 < 0. ? 0. : p1));

    if (wrappedPhase < p1)
        return wrappedPhase / p1;
    else
        return (p1 == 1. ? wrappedPhase : 1. - (wrappedPhase - p1) / (1. - p1));
}

inline number linearinterp(number frac, number x, number y) {
    return x + (y - x) * frac;
}

inline number cubicinterp(number a, number w, number x, number y, number z) {
    number a2 = a * a;
    number f0 = z - y - w + x;
    number f1 = w - x - f0;
    number f2 = y - w;
    number f3 = x;
    return f0 * a * a2 + f1 * a2 + f2 * a + f3;
}

inline number splineinterp(number a, number w, number x, number y, number z) {
    number a2 = a * a;
    number f0 = -0.5 * w + 1.5 * x - 1.5 * y + 0.5 * z;
    number f1 = w - 2.5 * x + 2 * y - 0.5 * z;
    number f2 = -0.5 * w + 0.5 * y;
    return f0 * a * a2 + f1 * a2 + f2 * a + x;
}

inline number cosT8(number r) {
    number t84 = 56.0;
    number t83 = 1680.0;
    number t82 = 20160.0;
    number t81 = 2.4801587302e-05;
    number t73 = 42.0;
    number t72 = 840.0;
    number t71 = 1.9841269841e-04;

    if (r < 0.785398163397448309615660845819875721 && r > -0.785398163397448309615660845819875721) {
        number rr = r * r;
        return 1.0 - rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
    } else if (r > 0.0) {
        r -= 1.57079632679489661923132169163975144;
        number rr = r * r;
        return -r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
    } else {
        r += 1.57079632679489661923132169163975144;
        number rr = r * r;
        return r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
    }
}

inline number cosineinterp(number frac, number x, number y) {
    number a2 = (1.0 - this->cosT8(frac * 3.14159265358979323846)) / (number)2.0;
    return x * (1.0 - a2) + y * a2;
}

template <typename T> inline array<SampleValue, 1 + 1> peek_boundmode_wrap_interp_cubic(T& buffer, SampleValue sampleIndex, Index channelOffset) {
    number bufferSize = buffer->getSize();
    const Index bufferChannels = (const Index)(buffer->getChannels());
    constexpr int ___N2 = 1 + 1;
    array<SampleValue, ___N2> out = FIXEDSIZEARRAYINIT(1 + 1);

    if (bufferSize == 0 || (3 == 5 && (sampleIndex < 0 || sampleIndex >= bufferSize))) {
        return out;
    } else {
        {
            SampleIndex bufferbindindex_result;

            {
                {
                    {
                        bufferbindindex_result = this->wrap(sampleIndex, 0, bufferSize);
                    }
                }
            }

            sampleIndex = bufferbindindex_result;
        }

        for (Index channel = 0; channel < 1; channel++) {
            Index channelIndex = (Index)(channel + channelOffset);

            {
                if (channelIndex >= bufferChannels || channelIndex < 0) {
                    out[(Index)channel] = 0;
                    continue;
                }
            }

            SampleValue bufferreadsample_result;

            {
                auto& __buffer = buffer;

                if (sampleIndex < 0.0) {
                    bufferreadsample_result = 0.0;
                }

                SampleIndex index1 = (SampleIndex)(trunc(sampleIndex));

                {
                    {
                        number frac = sampleIndex - index1;
                        number wrap = bufferSize - 1;
                        SampleIndex index2 = (SampleIndex)(index1 + 1);

                        if (index2 > wrap)
                            index2 = 0;

                        SampleIndex index3 = (SampleIndex)(index2 + 1);

                        if (index3 > wrap)
                            index3 = 0;

                        SampleIndex index4 = (SampleIndex)(index3 + 1);

                        if (index4 > wrap)
                            index4 = 0;

                        bufferreadsample_result = this->cubicinterp(
                            frac,
                            __buffer->getSample(channelIndex, index1),
                            __buffer->getSample(channelIndex, index2),
                            __buffer->getSample(channelIndex, index3),
                            __buffer->getSample(channelIndex, index4)
                        );
                    }
                }
            }

            out[(Index)channel] = bufferreadsample_result;
        }

        out[1] = sampleIndex;
        return out;
    }
}

inline number safesqrt(number num) {
    return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
}

SampleIndex currentsampletime() {
    return this->audioProcessSampleCount + this->sampleOffsetIntoNextAudioBuffer;
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
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
    this->linetilde_01_perform(this->signals[0], n);
    this->linetilde_02_perform(this->signals[1], n);
    this->linetilde_03_perform(this->signals[2], n);
    this->linetilde_04_perform(this->signals[3], n);
    this->scopetilde_03_perform(this->zeroBuffer, this->zeroBuffer, n);
    this->feedbackreader_01_perform(this->signals[4], n);
    this->feedbackreader_02_perform(this->signals[5], n);
    this->xfade_tilde_05_perform(this->signals[3], this->signals[4], this->signals[5], this->signals[6], n);
    this->dspexpr_04_perform(this->signals[6], this->signals[3], this->signals[7], n);
    this->dspexpr_03_perform(this->signals[7], this->signals[6], n);
    this->signaladder_01_perform(this->signals[6], in1, this->signals[6], n);

    this->gen_01_perform(
        this->signals[6],
        this->gen_01_in2,
        this->gen_01_KnbWindowCoefficient,
        this->gen_01_KnbDelayTimeLeft,
        this->gen_01_KnbSmooth,
        this->gen_01_KnbDuty,
        this->gen_01_KnbSmoothWindow,
        this->signals[7],
        this->signals[8],
        this->signals[9],
        this->signals[10],
        this->signals[11],
        n
    );

    this->dspexpr_05_perform(this->signals[7], this->signals[0], this->signals[12], n);
    this->feedbackwriter_01_perform(this->signals[12], n);
    this->xfade_tilde_06_perform(this->signals[3], this->signals[5], this->signals[4], this->signals[12], n);
    this->dspexpr_07_perform(this->signals[12], this->signals[3], this->signals[4], n);
    this->dspexpr_06_perform(this->signals[4], this->signals[3], n);
    this->signaladder_02_perform(this->signals[3], in2, this->signals[3], n);

    this->gen_02_perform(
        this->signals[3],
        this->gen_02_in2,
        this->gen_02_KnbSmoothWindow,
        this->gen_02_KnbSmooth,
        this->gen_02_KnbDelayTimeRight,
        this->gen_02_KnbDuty,
        this->gen_02_KnbWindowCoefficient,
        this->signals[4],
        this->signals[12],
        this->signals[5],
        this->signals[13],
        this->signals[14],
        n
    );

    this->p_02_perform(
        this->signals[8],
        this->signals[9],
        this->signals[10],
        this->signals[11],
        this->signals[7],
        this->signals[2],
        this->signals[4],
        this->signals[12],
        this->signals[5],
        this->signals[13],
        this->signals[14],
        this->signals[15],
        this->signals[16],
        this->signals[17],
        this->signals[18],
        n
    );

    this->p_01_perform(
        in1,
        in2,
        this->signals[15],
        this->signals[16],
        this->signals[1],
        out1,
        out2,
        n
    );

    this->scopetilde_02_perform(this->signals[17], this->zeroBuffer, n);
    this->scopetilde_01_perform(this->signals[18], this->zeroBuffer, n);
    this->dspexpr_08_perform(this->signals[4], this->signals[0], this->signals[18], n);
    this->feedbackwriter_02_perform(this->signals[18], n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 19; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->feedbacktilde_01_feedbackbuffer = resizeSignal(this->feedbacktilde_01_feedbackbuffer, this->maxvs, maxBlockSize);
        this->feedbacktilde_02_feedbackbuffer = resizeSignal(this->feedbacktilde_02_feedbackbuffer, this->maxvs, maxBlockSize);
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

    this->data_01_dspsetup(forceDSPSetup);
    this->data_02_dspsetup(forceDSPSetup);
    this->scopetilde_03_dspsetup(forceDSPSetup);
    this->gen_01_dspsetup(forceDSPSetup);
    this->gen_02_dspsetup(forceDSPSetup);
    this->scopetilde_02_dspsetup(forceDSPSetup);
    this->scopetilde_01_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);
    this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);
    this->p_02->prepareToProcess(sampleRate, maxBlockSize, force);

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
        return addressOf(this->revdel);
        break;
        }
    case 1:
        {
        return addressOf(this->revdelright);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 2;
}

void fillDataRef(DataRefIndex , DataRef& ) {}

void zeroDataRef(DataRef& ref) {
    ref->setZero();
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->updateTime(time);

    if (index == 0) {
        this->gen_01_revdel = new Float32Buffer(this->revdel);
        this->data_02_buffer = new Float32Buffer(this->revdel);
        this->data_02_bufferUpdated();
    }

    if (index == 1) {
        this->gen_02_revdelright = new Float32Buffer(this->revdelright);
        this->data_01_buffer = new Float32Buffer(this->revdelright);
        this->data_01_bufferUpdated();
    }

    this->p_01->processDataViewUpdate(index, time);
    this->p_02->processDataViewUpdate(index, time);
}

void initialize() {
    this->revdel = initDataRef("revdel", false, nullptr, "buffer~");
    this->revdelright = initDataRef("revdelright", false, nullptr, "buffer~");
    this->assign_defaults();
    this->setState();
    this->revdel->setIndex(0);
    this->gen_01_revdel = new Float32Buffer(this->revdel);
    this->data_02_buffer = new Float32Buffer(this->revdel);
    this->revdelright->setIndex(1);
    this->gen_02_revdelright = new Float32Buffer(this->revdelright);
    this->data_01_buffer = new Float32Buffer(this->revdelright);
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
    this->p_01 = new RNBOSubpatcher_855();
    this->p_01->setEngineAndPatcher(this->getEngine(), this);
    this->p_01->initialize();
    this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
    this->p_02 = new RNBOSubpatcher_856();
    this->p_02->setEngineAndPatcher(this->getEngine(), this);
    this->p_02->initialize();
    this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_01_getPresetValue(getSubState(preset, "KnbDelayTimeLeft"));
    this->param_02_getPresetValue(getSubState(preset, "KnbDelayTimeRight"));
    this->param_03_getPresetValue(getSubState(preset, "KnbFeedback"));
    this->param_04_getPresetValue(getSubState(preset, "KnbWindowCoefficient"));
    this->param_05_getPresetValue(getSubState(preset, "KnbCrossFeedback"));
    this->param_06_getPresetValue(getSubState(preset, "KnbWaveshapeMorph"));
    this->param_07_getPresetValue(getSubState(preset, "KnbWaveshapeFixed"));
    this->param_08_getPresetValue(getSubState(preset, "BtnWaveShapeMorph"));
    this->param_09_getPresetValue(getSubState(preset, "KnbDuty"));
    this->param_10_getPresetValue(getSubState(preset, "BtnEnable"));
    this->param_11_getPresetValue(getSubState(preset, "KnbSmooth"));
    this->param_12_getPresetValue(getSubState(preset, "KnbSmoothWindow"));
    this->param_13_getPresetValue(getSubState(preset, "KnbMix"));
    this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "Mix~"));
    this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "Mixer"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_01_setPresetValue(getSubState(preset, "KnbDelayTimeLeft"));
    this->param_02_setPresetValue(getSubState(preset, "KnbDelayTimeRight"));
    this->param_04_setPresetValue(getSubState(preset, "KnbWindowCoefficient"));
    this->param_06_setPresetValue(getSubState(preset, "KnbWaveshapeMorph"));
    this->param_07_setPresetValue(getSubState(preset, "KnbWaveshapeFixed"));
    this->param_08_setPresetValue(getSubState(preset, "BtnWaveShapeMorph"));
    this->param_09_setPresetValue(getSubState(preset, "KnbDuty"));
    this->param_11_setPresetValue(getSubState(preset, "KnbSmooth"));
    this->param_12_setPresetValue(getSubState(preset, "KnbSmoothWindow"));
    this->param_10_setPresetValue(getSubState(preset, "BtnEnable"));
    this->param_03_setPresetValue(getSubState(preset, "KnbFeedback"));
    this->param_05_setPresetValue(getSubState(preset, "KnbCrossFeedback"));
    this->param_13_setPresetValue(getSubState(preset, "KnbMix"));
}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false)) {
        this->p_01->processTempoEvent(time, tempo);
        this->p_02->processTempoEvent(time, tempo);
    }
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time);

    if (this->globaltransport_setState(this->_currentTime, state, false)) {
        this->p_01->processTransportEvent(time, state);
        this->p_02->processTransportEvent(time, state);
    }
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false)) {
        this->p_01->processBeatTimeEvent(time, beattime);
        this->p_02->processBeatTimeEvent(time, beattime);
    }
}

void onSampleRateChanged(double ) {}

void processTimeSignatureEvent(MillisecondTime time, int numerator, int denominator) {
    this->updateTime(time);

    if (this->globaltransport_setTimeSignature(this->_currentTime, numerator, denominator, false)) {
        this->p_01->processTimeSignatureEvent(time, numerator, denominator);
        this->p_02->processTimeSignatureEvent(time, numerator, denominator);
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
    case 5:
        {
        this->param_06_value_set(v);
        break;
        }
    case 6:
        {
        this->param_07_value_set(v);
        break;
        }
    case 7:
        {
        this->param_08_value_set(v);
        break;
        }
    case 8:
        {
        this->param_09_value_set(v);
        break;
        }
    case 9:
        {
        this->param_10_value_set(v);
        break;
        }
    case 10:
        {
        this->param_11_value_set(v);
        break;
        }
    case 11:
        {
        this->param_12_value_set(v);
        break;
        }
    case 12:
        {
        this->param_13_value_set(v);
        break;
        }
    default:
        {
        index -= 13;

        if (index < this->p_01->getNumParameters())
            this->p_01->setParameterValue(index, v, time);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            this->p_02->setParameterValue(index, v, time);

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
    case 6:
        {
        return this->param_07_value;
        }
    case 7:
        {
        return this->param_08_value;
        }
    case 8:
        {
        return this->param_09_value;
        }
    case 9:
        {
        return this->param_10_value;
        }
    case 10:
        {
        return this->param_11_value;
        }
    case 11:
        {
        return this->param_12_value;
        }
    case 12:
        {
        return this->param_13_value;
        }
    default:
        {
        index -= 13;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterValue(index);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->getParameterValue(index);

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
    return 13 + this->p_01->getNumParameters() + this->p_02->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "KnbDelayTimeLeft";
        }
    case 1:
        {
        return "KnbDelayTimeRight";
        }
    case 2:
        {
        return "KnbFeedback";
        }
    case 3:
        {
        return "KnbWindowCoefficient";
        }
    case 4:
        {
        return "KnbCrossFeedback";
        }
    case 5:
        {
        return "KnbWaveshapeMorph";
        }
    case 6:
        {
        return "KnbWaveshapeFixed";
        }
    case 7:
        {
        return "BtnWaveShapeMorph";
        }
    case 8:
        {
        return "KnbDuty";
        }
    case 9:
        {
        return "BtnEnable";
        }
    case 10:
        {
        return "KnbSmooth";
        }
    case 11:
        {
        return "KnbSmoothWindow";
        }
    case 12:
        {
        return "KnbMix";
        }
    default:
        {
        index -= 13;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterName(index);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->getParameterName(index);

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "KnbDelayTimeLeft";
        }
    case 1:
        {
        return "KnbDelayTimeRight";
        }
    case 2:
        {
        return "KnbFeedback";
        }
    case 3:
        {
        return "KnbWindowCoefficient";
        }
    case 4:
        {
        return "KnbCrossFeedback";
        }
    case 5:
        {
        return "KnbWaveshapeMorph";
        }
    case 6:
        {
        return "KnbWaveshapeFixed";
        }
    case 7:
        {
        return "BtnWaveShapeMorph";
        }
    case 8:
        {
        return "KnbDuty";
        }
    case 9:
        {
        return "BtnEnable";
        }
    case 10:
        {
        return "KnbSmooth";
        }
    case 11:
        {
        return "KnbSmoothWindow";
        }
    case 12:
        {
        return "KnbMix";
        }
    default:
        {
        index -= 13;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterId(index);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->getParameterId(index);

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
            info->initialValue = 300;
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
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 300;
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
            info->displayName = "Regen";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 1;
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
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
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
        case 6:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 3;
            info->exponent = 1;
            info->steps = 4;
            static const char * eVal6[] = {"1", "2", "3", "4"};
            info->enumValues = eVal6;
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
        case 7:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 2;
            static const char * eVal7[] = {"0", "1"};
            info->enumValues = eVal7;
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
        case 8:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
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
        case 9:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 2;
            static const char * eVal9[] = {"0", "1"};
            info->enumValues = eVal9;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Frezze";
            info->unit = "On/Off";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 10:
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
        case 11:
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
        case 12:
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
        default:
            {
            index -= 13;

            if (index < this->p_01->getNumParameters())
                this->p_01->getParameterInfo(index, info);

            index -= this->p_01->getNumParameters();

            if (index < this->p_02->getNumParameters())
                this->p_02->getParameterInfo(index, info);

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
        return 13;

    if (subpatcher == this->p_02)
        return 13 + this->p_01->getNumParameters();

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
    case 3:
    case 8:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 7:
    case 9:
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
    case 6:
        {
        {
            value = (value < 0 ? 0 : (value > 3 ? 3 : value));
            ParameterValue normalizedValue = (value - 0) / (3 - 0);

            {
                normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 4);
            }

            return normalizedValue;
        }
        }
    case 2:
    case 4:
    case 5:
    case 10:
    case 11:
    case 12:
        {
        {
            value = (value < 0 ? 0 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - 0) / (100 - 0);
            return normalizedValue;
        }
        }
    case 0:
    case 1:
        {
        {
            value = (value < 0 ? 0 : (value > 10000 ? 10000 : value));
            ParameterValue normalizedValue = (value - 0) / (10000 - 0);
            return normalizedValue;
        }
        }
    default:
        {
        index -= 13;

        if (index < this->p_01->getNumParameters())
            return this->p_01->convertToNormalizedParameterValue(index, value);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->convertToNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 3:
    case 8:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 7:
    case 9:
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
    case 6:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                value = this->applyStepsToNormalizedParameterValue(value, 4);
            }

            {
                return 0 + value * (3 - 0);
            }
        }
        }
    case 2:
    case 4:
    case 5:
    case 10:
    case 11:
    case 12:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (100 - 0);
            }
        }
        }
    case 0:
    case 1:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));

            {
                return 0 + value * (10000 - 0);
            }
        }
        }
    default:
        {
        index -= 13;

        if (index < this->p_01->getNumParameters())
            return this->p_01->convertFromNormalizedParameterValue(index, value);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->convertFromNormalizedParameterValue(index, value);

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
    case 6:
        {
        return this->param_07_value_constrain(value);
        }
    case 7:
        {
        return this->param_08_value_constrain(value);
        }
    case 8:
        {
        return this->param_09_value_constrain(value);
        }
    case 9:
        {
        return this->param_10_value_constrain(value);
        }
    case 10:
        {
        return this->param_11_value_constrain(value);
        }
    case 11:
        {
        return this->param_12_value_constrain(value);
        }
    case 12:
        {
        return this->param_13_value_constrain(value);
        }
    default:
        {
        index -= 13;

        if (index < this->p_01->getNumParameters())
            return this->p_01->constrainParameterValue(index, value);

        index -= this->p_01->getNumParameters();

        if (index < this->p_02->getNumParameters())
            return this->p_02->constrainParameterValue(index, value);

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
    RNBO_UNUSED(value);
    RNBO_UNUSED(hasValue);
    this->updateTime(time);

    switch (index) {
    case -62043057:
        {
        this->linetilde_01_target_bang();
        break;
        }
    case 1114681293:
        {
        this->linetilde_02_target_bang();
        break;
        }
    case -2003561653:
        {
        this->linetilde_03_target_bang();
        break;
        }
    case -1621164530:
        {
        this->linetilde_04_target_bang();
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
        if (TAG("number_obj-55") == objectId)
            this->numberobj_01_valin_set(payload);

        if (TAG("toggle_obj-76") == objectId)
            this->toggle_01_valin_set(payload);

        if (TAG("number_obj-104") == objectId)
            this->numberobj_02_valin_set(payload);

        if (TAG("number_obj-80") == objectId)
            this->numberobj_03_valin_set(payload);

        if (TAG("number_obj-82") == objectId)
            this->numberobj_04_valin_set(payload);

        if (TAG("number_obj-119") == objectId)
            this->numberobj_05_valin_set(payload);

        if (TAG("number_obj-17") == objectId)
            this->numberobj_06_valin_set(payload);

        if (TAG("number_obj-99") == objectId)
            this->numberobj_07_valin_set(payload);

        if (TAG("number_obj-67") == objectId)
            this->numberobj_08_valin_set(payload);

        if (TAG("number_obj-70") == objectId)
            this->numberobj_09_valin_set(payload);

        if (TAG("number_obj-41") == objectId)
            this->numberobj_10_valin_set(payload);

        if (TAG("number_obj-44") == objectId)
            this->numberobj_11_valin_set(payload);

        break;
        }
    case TAG("format"):
        {
        if (TAG("number_obj-55") == objectId)
            this->numberobj_01_format_set(payload);

        if (TAG("number_obj-104") == objectId)
            this->numberobj_02_format_set(payload);

        if (TAG("number_obj-80") == objectId)
            this->numberobj_03_format_set(payload);

        if (TAG("number_obj-82") == objectId)
            this->numberobj_04_format_set(payload);

        if (TAG("number_obj-119") == objectId)
            this->numberobj_05_format_set(payload);

        if (TAG("number_obj-17") == objectId)
            this->numberobj_06_format_set(payload);

        if (TAG("number_obj-99") == objectId)
            this->numberobj_07_format_set(payload);

        if (TAG("number_obj-67") == objectId)
            this->numberobj_08_format_set(payload);

        if (TAG("number_obj-70") == objectId)
            this->numberobj_09_format_set(payload);

        if (TAG("number_obj-41") == objectId)
            this->numberobj_10_format_set(payload);

        if (TAG("number_obj-44") == objectId)
            this->numberobj_11_format_set(payload);

        break;
        }
    }

    this->p_01->processNumMessage(tag, objectId, time, payload);
    this->p_02->processNumMessage(tag, objectId, time, payload);
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
    this->p_02->processListMessage(tag, objectId, time, payload);
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);
    this->p_01->processBangMessage(tag, objectId, time);
    this->p_02->processBangMessage(tag, objectId, time);
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("setup"):
        {
        return "setup";
        }
    case TAG("scope~_obj-138"):
        {
        return "scope~_obj-138";
        }
    case TAG("monitor"):
        {
        return "monitor";
        }
    case TAG("valout"):
        {
        return "valout";
        }
    case TAG("number_obj-55"):
        {
        return "number_obj-55";
        }
    case TAG("toggle_obj-76"):
        {
        return "toggle_obj-76";
        }
    case TAG("number_obj-104"):
        {
        return "number_obj-104";
        }
    case TAG("number_obj-80"):
        {
        return "number_obj-80";
        }
    case TAG("number_obj-82"):
        {
        return "number_obj-82";
        }
    case TAG("number_obj-119"):
        {
        return "number_obj-119";
        }
    case TAG("number_obj-17"):
        {
        return "number_obj-17";
        }
    case TAG("number_obj-99"):
        {
        return "number_obj-99";
        }
    case TAG("number_obj-67"):
        {
        return "number_obj-67";
        }
    case TAG("number_obj-70"):
        {
        return "number_obj-70";
        }
    case TAG("scope~_obj-78"):
        {
        return "scope~_obj-78";
        }
    case TAG("number_obj-41"):
        {
        return "number_obj-41";
        }
    case TAG("number_obj-44"):
        {
        return "number_obj-44";
        }
    case TAG("scope~_obj-28"):
        {
        return "scope~_obj-28";
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

    auto subpatchResult_1 = this->p_02->resolveTag(tag);

    if (subpatchResult_1)
        return subpatchResult_1;

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

    this->gen_01_KnbDelayTimeLeft_set(v);
}

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(1, false);

    if (this->param_02_value != this->param_02_lastValue) {
        this->getEngine()->presetTouched();
        this->param_02_lastValue = this->param_02_value;
    }

    this->gen_02_KnbDelayTimeRight_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(2, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->numberobj_03_value_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(3, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->gen_02_KnbWindowCoefficient_set(v);
    this->gen_01_KnbWindowCoefficient_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(4, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    this->numberobj_11_value_set(v);
}

void param_06_value_set(number v) {
    v = this->param_06_value_constrain(v);
    this->param_06_value = v;
    this->sendParameter(5, false);

    if (this->param_06_value != this->param_06_lastValue) {
        this->getEngine()->presetTouched();
        this->param_06_lastValue = this->param_06_value;
    }

    this->numberobj_09_value_set(v);
}

void param_07_value_set(number v) {
    v = this->param_07_value_constrain(v);
    this->param_07_value = v;
    this->sendParameter(6, false);

    if (this->param_07_value != this->param_07_lastValue) {
        this->getEngine()->presetTouched();
        this->param_07_lastValue = this->param_07_value;
    }

    this->expr_04_in1_set(v);
}

void param_08_value_set(number v) {
    v = this->param_08_value_constrain(v);
    this->param_08_value = v;
    this->sendParameter(7, false);

    if (this->param_08_value != this->param_08_lastValue) {
        this->getEngine()->presetTouched();
        this->param_08_lastValue = this->param_08_value;
    }

    this->numberobj_07_value_set(v);
}

void param_09_value_set(number v) {
    v = this->param_09_value_constrain(v);
    this->param_09_value = v;
    this->sendParameter(8, false);

    if (this->param_09_value != this->param_09_lastValue) {
        this->getEngine()->presetTouched();
        this->param_09_lastValue = this->param_09_value;
    }

    this->numberobj_01_value_set(v);
}

void param_10_value_set(number v) {
    v = this->param_10_value_constrain(v);
    this->param_10_value = v;
    this->sendParameter(9, false);

    if (this->param_10_value != this->param_10_lastValue) {
        this->getEngine()->presetTouched();
        this->param_10_lastValue = this->param_10_value;
    }

    this->toggle_01_value_number_set(v);
}

void param_11_value_set(number v) {
    v = this->param_11_value_constrain(v);
    this->param_11_value = v;
    this->sendParameter(10, false);

    if (this->param_11_value != this->param_11_lastValue) {
        this->getEngine()->presetTouched();
        this->param_11_lastValue = this->param_11_value;
    }

    this->gen_02_KnbSmooth_set(v);
    this->gen_01_KnbSmooth_set(v);
}

void param_12_value_set(number v) {
    v = this->param_12_value_constrain(v);
    this->param_12_value = v;
    this->sendParameter(11, false);

    if (this->param_12_value != this->param_12_lastValue) {
        this->getEngine()->presetTouched();
        this->param_12_lastValue = this->param_12_value;
    }

    this->gen_02_KnbSmoothWindow_set(v);
    this->gen_01_KnbSmoothWindow_set(v);
}

void param_13_value_set(number v) {
    v = this->param_13_value_constrain(v);
    this->param_13_value = v;
    this->sendParameter(12, false);

    if (this->param_13_value != this->param_13_lastValue) {
        this->getEngine()->presetTouched();
        this->param_13_lastValue = this->param_13_value;
    }

    this->numberobj_06_value_set(v);
}

void numberobj_01_valin_set(number v) {
    this->numberobj_01_value_set(v);
}

void numberobj_01_format_set(number v) {
    this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void toggle_01_valin_set(number v) {
    this->toggle_01_value_number_set(v);
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

void numberobj_09_valin_set(number v) {
    this->numberobj_09_value_set(v);
}

void numberobj_09_format_set(number v) {
    this->numberobj_09_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_10_valin_set(number v) {
    this->numberobj_10_value_set(v);
}

void numberobj_10_format_set(number v) {
    this->numberobj_10_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_11_valin_set(number v) {
    this->numberobj_11_value_set(v);
}

void numberobj_11_format_set(number v) {
    this->numberobj_11_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void linetilde_01_target_bang() {}

void linetilde_02_target_bang() {}

void linetilde_03_target_bang() {}

void linetilde_04_target_bang() {}

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
    this->p_02->allocateDataRefs();
    this->data_02_buffer->requestSize(this->mstosamps(10000), 1);
    this->data_02_buffer->setSampleRate(this->sr);
    this->data_01_buffer->requestSize(this->mstosamps(10000), 1);
    this->data_01_buffer->setSampleRate(this->sr);
    this->gen_01_revdel = this->gen_01_revdel->allocateIfNeeded();
    this->data_02_buffer = this->data_02_buffer->allocateIfNeeded();

    if (this->revdel->hasRequestedSize()) {
        if (this->revdel->wantsFill())
            this->zeroDataRef(this->revdel);

        this->getEngine()->sendDataRefUpdated(0);
    }

    this->gen_02_revdelright = this->gen_02_revdelright->allocateIfNeeded();
    this->data_01_buffer = this->data_01_buffer->allocateIfNeeded();

    if (this->revdelright->hasRequestedSize()) {
        if (this->revdelright->wantsFill())
            this->zeroDataRef(this->revdelright);

        this->getEngine()->sendDataRefUpdated(1);
    }
}

void initializeObjects() {
    this->numberobj_01_init();
    this->numberobj_02_init();
    this->gen_01_history_2_init();
    this->gen_01_history_1_init();
    this->gen_01_change_3_init();
    this->gen_01_counter_20_init();
    this->gen_01_change_23_init();
    this->gen_01_counter_40_init();
    this->numberobj_03_init();
    this->numberobj_04_init();
    this->numberobj_05_init();
    this->numberobj_06_init();
    this->numberobj_07_init();
    this->gen_02_history_2_init();
    this->gen_02_history_1_init();
    this->gen_02_change_2_init();
    this->gen_02_counter_20_init();
    this->gen_02_change_23_init();
    this->gen_02_counter_40_init();
    this->numberobj_08_init();
    this->numberobj_09_init();
    this->numberobj_10_init();
    this->numberobj_11_init();
    this->data_01_init();
    this->data_02_init();
    this->p_01->initializeObjects();
    this->p_02->initializeObjects();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());
    this->p_01->startup();
    this->p_02->startup();

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 5);
    }

    {
        this->scheduleParamInit(3, 0);
    }

    {
        this->scheduleParamInit(4, 6);
    }

    {
        this->scheduleParamInit(5, 0);
    }

    {
        this->scheduleParamInit(6, 0);
    }

    {
        this->scheduleParamInit(7, 0);
    }

    {
        this->scheduleParamInit(8, 0);
    }

    {
        this->scheduleParamInit(9, 1);
    }

    {
        this->scheduleParamInit(10, 0);
    }

    {
        this->scheduleParamInit(11, 0);
    }

    {
        this->scheduleParamInit(12, 6);
    }

    this->processParamInitEvents();
}

static number param_01_value_constrain(number v) {
    v = (v > 10000 ? 10000 : (v < 0 ? 0 : v));
    return v;
}

void gen_01_KnbDelayTimeLeft_set(number v) {
    this->gen_01_KnbDelayTimeLeft = v;
}

static number param_02_value_constrain(number v) {
    v = (v > 10000 ? 10000 : (v < 0 ? 0 : v));
    return v;
}

void gen_02_KnbDelayTimeRight_set(number v) {
    this->gen_02_KnbDelayTimeRight = v;
}

static number param_03_value_constrain(number v) {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
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

void numberobj_04_output_set(number v) {
    {
        list converted = {v};
        this->linetilde_01_segments_set(converted);
    }
}

void numberobj_04_value_set(number v) {
    this->numberobj_04_value_setter(v);
    v = this->numberobj_04_value;
    number localvalue = v;

    if (this->numberobj_04_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-82"), localvalue, this->_currentTime);
    this->numberobj_04_output_set(localvalue);
}

void scale_01_out_set(const list& v) {
    this->scale_01_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_04_value_set(converted);
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

void numberobj_03_output_set(number v) {
    {
        list converted = {v};
        this->scale_01_input_set(converted);
    }
}

void numberobj_03_value_set(number v) {
    this->numberobj_03_value_setter(v);
    v = this->numberobj_03_value;
    number localvalue = v;

    if (this->numberobj_03_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-80"), localvalue, this->_currentTime);
    this->numberobj_03_output_set(localvalue);
}

static number param_04_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void gen_02_KnbWindowCoefficient_set(number v) {
    this->gen_02_KnbWindowCoefficient = v;
}

void gen_01_KnbWindowCoefficient_set(number v) {
    this->gen_01_KnbWindowCoefficient = v;
}

static number param_05_value_constrain(number v) {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void linetilde_04_time_set(number v) {
    this->linetilde_04_time = v;
}

void linetilde_04_segments_set(const list& v) {
    this->linetilde_04_segments = jsCreateListCopy(v);

    if ((bool)(v->length)) {
        if (v->length == 1 && this->linetilde_04_time == 0) {
            this->linetilde_04_activeRamps->length = 0;
            this->linetilde_04_currentValue = v[0];
        } else {
            auto currentTime = this->currentsampletime();
            number lastRampValue = this->linetilde_04_currentValue;
            number rampEnd = currentTime - this->sampleOffsetIntoNextAudioBuffer;

            for (Index i = 0; i < this->linetilde_04_activeRamps->length; i += 3) {
                rampEnd = this->linetilde_04_activeRamps[(Index)(i + 2)];

                if (rampEnd > currentTime) {
                    this->linetilde_04_activeRamps[(Index)(i + 2)] = currentTime;
                    number diff = rampEnd - currentTime;
                    number valueDiff = diff * this->linetilde_04_activeRamps[(Index)(i + 1)];
                    lastRampValue = this->linetilde_04_activeRamps[(Index)i] - valueDiff;
                    this->linetilde_04_activeRamps[(Index)i] = lastRampValue;
                    this->linetilde_04_activeRamps->length = i + 3;
                    rampEnd = currentTime;
                } else {
                    lastRampValue = this->linetilde_04_activeRamps[(Index)i];
                }
            }

            if (rampEnd < currentTime) {
                this->linetilde_04_activeRamps->push(lastRampValue);
                this->linetilde_04_activeRamps->push(0);
                this->linetilde_04_activeRamps->push(currentTime);
            }

            number lastRampEnd = currentTime;

            for (Index i = 0; i < v->length; i += 2) {
                number destinationValue = v[(Index)i];
                number inc = 0;
                number rampTimeInSamples;

                if (v->length > i + 1) {
                    rampTimeInSamples = this->mstosamps(v[(Index)(i + 1)]);

                    if ((bool)(this->linetilde_04_keepramp)) {
                        this->linetilde_04_time_set(v[(Index)(i + 1)]);
                    }
                } else {
                    rampTimeInSamples = this->mstosamps(this->linetilde_04_time);
                }

                if (rampTimeInSamples <= 0) {
                    rampTimeInSamples = 1;
                }

                inc = (destinationValue - lastRampValue) / rampTimeInSamples;
                lastRampEnd += rampTimeInSamples;
                this->linetilde_04_activeRamps->push(destinationValue);
                this->linetilde_04_activeRamps->push(inc);
                this->linetilde_04_activeRamps->push(lastRampEnd);
                lastRampValue = destinationValue;
            }
        }
    }
}

void numberobj_10_output_set(number v) {
    {
        list converted = {v};
        this->linetilde_04_segments_set(converted);
    }
}

void numberobj_10_value_set(number v) {
    this->numberobj_10_value_setter(v);
    v = this->numberobj_10_value;
    number localvalue = v;

    if (this->numberobj_10_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-41"), localvalue, this->_currentTime);
    this->numberobj_10_output_set(localvalue);
}

void expr_09_out1_set(number v) {
    this->expr_09_out1 = v;
    this->numberobj_10_value_set(this->expr_09_out1);
}

void expr_09_in1_set(number in1) {
    this->expr_09_in1 = in1;

    this->expr_09_out1_set(
        (this->expr_09_in2 == 0 ? 0 : (this->expr_09_in2 == 0. ? 0. : this->expr_09_in1 / this->expr_09_in2))
    );//#map:/_obj-42:1
}

void numberobj_11_output_set(number v) {
    this->expr_09_in1_set(v);
}

void numberobj_11_value_set(number v) {
    this->numberobj_11_value_setter(v);
    v = this->numberobj_11_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_11_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-44"), localvalue, this->_currentTime);
    this->numberobj_11_output_set(localvalue);
}

static number param_06_value_constrain(number v) {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
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

void numberobj_08_output_set(number v) {
    {
        list converted = {v};
        this->linetilde_03_segments_set(converted);
    }
}

void numberobj_08_value_set(number v) {
    this->numberobj_08_value_setter(v);
    v = this->numberobj_08_value;
    number localvalue = v;

    if (this->numberobj_08_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-67"), localvalue, this->_currentTime);
    this->numberobj_08_output_set(localvalue);
}

void expr_08_out1_set(number v) {
    this->expr_08_out1 = v;
    this->numberobj_08_value_set(this->expr_08_out1);
}

void expr_08_in1_set(number in1) {
    this->expr_08_in1 = in1;

    this->expr_08_out1_set(
        (this->expr_08_in2 == 0 ? 0 : (this->expr_08_in2 == 0. ? 0. : this->expr_08_in1 / this->expr_08_in2))
    );//#map:/_obj-68:1
}

void numberobj_09_output_set(number v) {
    this->expr_08_in1_set(v);
}

void numberobj_09_value_set(number v) {
    this->numberobj_09_value_setter(v);
    v = this->numberobj_09_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_09_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-70"), localvalue, this->_currentTime);
    this->numberobj_09_output_set(localvalue);
}

static number param_07_value_constrain(number v) {
    v = (v > 3 ? 3 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)3 / (number)3;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep;
    }

    return v;
}

void p_02_in1_number_set(number v) {
    this->p_02->updateTime(this->_currentTime);
    this->p_02->eventinlet_02_out1_number_set(v);
}

void numberobj_02_output_set(number v) {
    this->p_02_in1_number_set(v);
}

void numberobj_02_value_set(number v) {
    this->numberobj_02_value_setter(v);
    v = this->numberobj_02_value;
    number localvalue = v;

    if (this->numberobj_02_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-104"), localvalue, this->_currentTime);
    this->numberobj_02_output_set(localvalue);
}

void expr_04_out1_set(number v) {
    this->expr_04_out1 = v;
    this->numberobj_02_value_set(this->expr_04_out1);
}

void expr_04_in1_set(number in1) {
    this->expr_04_in1 = in1;
    this->expr_04_out1_set(this->expr_04_in1 + this->expr_04_in2);//#map:+_obj-140:1
}

static number param_08_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)1 / (number)1;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep;
    }

    return v;
}

void p_02_in7_number_set(number v) {
    this->p_02->updateTime(this->_currentTime);
    this->p_02->eventinlet_01_out1_number_set(v);
}

void expr_07_out1_set(number v) {
    this->expr_07_out1 = v;
    this->p_02_in7_number_set(this->expr_07_out1);
}

void expr_07_in1_set(number in1) {
    this->expr_07_in1 = in1;
    this->expr_07_out1_set(this->expr_07_in1 + this->expr_07_in2);//#map:+_obj-139:1
}

void numberobj_07_output_set(number v) {
    this->expr_07_in1_set(v);
}

void numberobj_07_value_set(number v) {
    this->numberobj_07_value_setter(v);
    v = this->numberobj_07_value;
    number localvalue = v;

    if (this->numberobj_07_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-99"), localvalue, this->_currentTime);
    this->numberobj_07_output_set(localvalue);
}

static number param_09_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

static number gen_02_KnbDuty_constrain(number v) {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_02_KnbDuty_set(number v) {
    v = this->gen_02_KnbDuty_constrain(v);
    this->gen_02_KnbDuty = v;
}

static number gen_01_KnbDuty_constrain(number v) {
    if (v < 0)
        v = 0;

    if (v > 1)
        v = 1;

    return v;
}

void gen_01_KnbDuty_set(number v) {
    v = this->gen_01_KnbDuty_constrain(v);
    this->gen_01_KnbDuty = v;
}

void numberobj_01_output_set(number v) {
    this->gen_02_KnbDuty_set(v);
    this->gen_01_KnbDuty_set(v);
}

void numberobj_01_value_set(number v) {
    this->numberobj_01_value_setter(v);
    v = this->numberobj_01_value;
    number localvalue = v;

    if (this->numberobj_01_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-55"), localvalue, this->_currentTime);
    this->numberobj_01_output_set(localvalue);
}

static number param_10_value_constrain(number v) {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)1 / (number)1;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround(v * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep;
    }

    return v;
}

void gen_02_in2_set(number v) {
    this->gen_02_in2 = v;
}

void gen_01_in2_set(number v) {
    this->gen_01_in2 = v;
}

void toggle_01_output_set(number v) {
    this->gen_02_in2_set(v);
    this->gen_01_in2_set(v);
}

void toggle_01_value_number_set(number v) {
    this->toggle_01_value_number_setter(v);
    v = this->toggle_01_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-76"), v, this->_currentTime);
    this->toggle_01_output_set(v);
}

static number param_11_value_constrain(number v) {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

static number gen_02_KnbSmooth_constrain(number v) {
    if (v < 0)
        v = 0;

    return v;
}

void gen_02_KnbSmooth_set(number v) {
    v = this->gen_02_KnbSmooth_constrain(v);
    this->gen_02_KnbSmooth = v;
}

static number gen_01_KnbSmooth_constrain(number v) {
    if (v < 0)
        v = 0;

    return v;
}

void gen_01_KnbSmooth_set(number v) {
    v = this->gen_01_KnbSmooth_constrain(v);
    this->gen_01_KnbSmooth = v;
}

static number param_12_value_constrain(number v) {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

static number gen_02_KnbSmoothWindow_constrain(number v) {
    if (v < 0)
        v = 0;

    return v;
}

void gen_02_KnbSmoothWindow_set(number v) {
    v = this->gen_02_KnbSmoothWindow_constrain(v);
    this->gen_02_KnbSmoothWindow = v;
}

static number gen_01_KnbSmoothWindow_constrain(number v) {
    if (v < 0)
        v = 0;

    return v;
}

void gen_01_KnbSmoothWindow_set(number v) {
    v = this->gen_01_KnbSmoothWindow_constrain(v);
    this->gen_01_KnbSmoothWindow = v;
}

static number param_13_value_constrain(number v) {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
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

void numberobj_05_output_set(number v) {
    {
        list converted = {v};
        this->linetilde_02_segments_set(converted);
    }
}

void numberobj_05_value_set(number v) {
    this->numberobj_05_value_setter(v);
    v = this->numberobj_05_value;
    number localvalue = v;

    if (this->numberobj_05_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-119"), localvalue, this->_currentTime);
    this->numberobj_05_output_set(localvalue);
}

void expr_05_out1_set(number v) {
    this->expr_05_out1 = v;
    this->numberobj_05_value_set(this->expr_05_out1);
}

void expr_05_in1_set(number in1) {
    this->expr_05_in1 = in1;

    this->expr_05_out1_set(
        (this->expr_05_in2 == 0 ? 0 : (this->expr_05_in2 == 0. ? 0. : this->expr_05_in1 / this->expr_05_in2))
    );//#map:/_obj-120:1
}

void numberobj_06_output_set(number v) {
    this->expr_05_in1_set(v);
}

void numberobj_06_value_set(number v) {
    this->numberobj_06_value_setter(v);
    v = this->numberobj_06_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_06_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-17"), localvalue, this->_currentTime);
    this->numberobj_06_output_set(localvalue);
}

void ctlin_01_outchannel_set(number ) {}

void ctlin_01_outcontroller_set(number ) {}

void fromnormalized_01_output_set(number v) {
    this->param_03_value_set(v);
}

void fromnormalized_01_input_set(number v) {
    this->fromnormalized_01_output_set(this->fromnormalized(2, v));
}

void expr_01_out1_set(number v) {
    this->expr_01_out1 = v;
    this->fromnormalized_01_input_set(this->expr_01_out1);
}

void expr_01_in1_set(number in1) {
    this->expr_01_in1 = in1;
    this->expr_01_out1_set(this->expr_01_in1 * this->expr_01_in2);//#map:expr_01:1
}

void ctlin_01_value_set(number v) {
    this->expr_01_in1_set(v);
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
    this->param_05_value_set(v);
}

void fromnormalized_02_input_set(number v) {
    this->fromnormalized_02_output_set(this->fromnormalized(4, v));
}

void expr_02_out1_set(number v) {
    this->expr_02_out1 = v;
    this->fromnormalized_02_input_set(this->expr_02_out1);
}

void expr_02_in1_set(number in1) {
    this->expr_02_in1 = in1;
    this->expr_02_out1_set(this->expr_02_in1 * this->expr_02_in2);//#map:expr_02:1
}

void ctlin_02_value_set(number v) {
    this->expr_02_in1_set(v);
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
    this->param_10_value_set(v);
}

void fromnormalized_03_input_set(number v) {
    this->fromnormalized_03_output_set(this->fromnormalized(9, v));
}

void expr_03_out1_set(number v) {
    this->expr_03_out1 = v;
    this->fromnormalized_03_input_set(this->expr_03_out1);
}

void expr_03_in1_set(number in1) {
    this->expr_03_in1 = in1;
    this->expr_03_out1_set(this->expr_03_in1 * this->expr_03_in2);//#map:expr_03:1
}

void ctlin_03_value_set(number v) {
    this->expr_03_in1_set(v);
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
    this->param_13_value_set(v);
}

void fromnormalized_04_input_set(number v) {
    this->fromnormalized_04_output_set(this->fromnormalized(12, v));
}

void expr_06_out1_set(number v) {
    this->expr_06_out1 = v;
    this->fromnormalized_04_input_set(this->expr_06_out1);
}

void expr_06_in1_set(number in1) {
    this->expr_06_in1 = in1;
    this->expr_06_out1_set(this->expr_06_in1 * this->expr_06_in2);//#map:expr_06:1
}

void ctlin_04_value_set(number v) {
    this->expr_06_in1_set(v);
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
                        1114681293,
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
                        -2003561653,
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

void linetilde_04_perform(SampleValue * out, Index n) {
    auto __linetilde_04_time = this->linetilde_04_time;
    auto __linetilde_04_keepramp = this->linetilde_04_keepramp;
    auto __linetilde_04_currentValue = this->linetilde_04_currentValue;
    Index i = 0;

    if ((bool)(this->linetilde_04_activeRamps->length)) {
        while ((bool)(this->linetilde_04_activeRamps->length) && i < n) {
            number destinationValue = this->linetilde_04_activeRamps[0];
            number inc = this->linetilde_04_activeRamps[1];
            number rampTimeInSamples = this->linetilde_04_activeRamps[2] - this->audioProcessSampleCount - i;
            number val = __linetilde_04_currentValue;

            while (rampTimeInSamples > 0 && i < n) {
                out[(Index)i] = val;
                val += inc;
                i++;
                rampTimeInSamples--;
            }

            if (rampTimeInSamples <= 0) {
                val = destinationValue;
                this->linetilde_04_activeRamps->splice(0, 3);

                if ((bool)(!(bool)(this->linetilde_04_activeRamps->length))) {
                    this->getEngine()->scheduleClockEventWithValue(
                        this,
                        -1621164530,
                        this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                        0
                    );;

                    if ((bool)(!(bool)(__linetilde_04_keepramp))) {
                        __linetilde_04_time = 0;
                    }
                }
            }

            __linetilde_04_currentValue = val;
        }
    }

    while (i < n) {
        out[(Index)i] = __linetilde_04_currentValue;
        i++;
    }

    this->linetilde_04_currentValue = __linetilde_04_currentValue;
    this->linetilde_04_time = __linetilde_04_time;
}

void scopetilde_03_perform(const SampleValue * x, const SampleValue * y, Index n) {
    auto __scopetilde_03_ysign = this->scopetilde_03_ysign;
    auto __scopetilde_03_ymonitorvalue = this->scopetilde_03_ymonitorvalue;
    auto __scopetilde_03_xsign = this->scopetilde_03_xsign;
    auto __scopetilde_03_xmonitorvalue = this->scopetilde_03_xmonitorvalue;
    auto __scopetilde_03_mode = this->scopetilde_03_mode;

    for (Index i = 0; i < n; i++) {
        number xval = x[(Index)i];
        number yval = y[(Index)i];

        if (__scopetilde_03_mode == 1) {
            number xabsval = rnbo_abs(xval);

            if (xabsval > __scopetilde_03_xmonitorvalue) {
                __scopetilde_03_xmonitorvalue = xabsval;
                __scopetilde_03_xsign = (xval < 0 ? -1 : 1);
            }

            number yabsval = rnbo_abs(yval);

            if (yabsval > __scopetilde_03_ymonitorvalue) {
                __scopetilde_03_ymonitorvalue = yabsval;
                __scopetilde_03_ysign = (yval < 0 ? -1 : 1);
            }
        } else {
            __scopetilde_03_xmonitorvalue = xval;
            __scopetilde_03_xsign = 1;
            __scopetilde_03_ymonitorvalue = yval;
            __scopetilde_03_ysign = 1;
        }

        this->scopetilde_03_effectiveCount--;

        if (this->scopetilde_03_effectiveCount <= 0) {
            this->scopetilde_03_updateEffectiveCount();
            this->scopetilde_03_monitorbuffer->push(__scopetilde_03_xmonitorvalue * __scopetilde_03_xsign);

            if (__scopetilde_03_mode == 1)
                __scopetilde_03_xmonitorvalue = 0;

            if (this->scopetilde_03_monitorbuffer->length >= 128 * (0 + 0)) {
                this->getEngine()->sendListMessage(
                    TAG("monitor"),
                    TAG("scope~_obj-28"),
                    this->scopetilde_03_monitorbuffer,
                    this->_currentTime
                );;

                this->scopetilde_03_monitorbuffer->length = 0;
            }
        }
    }

    this->scopetilde_03_xmonitorvalue = __scopetilde_03_xmonitorvalue;
    this->scopetilde_03_xsign = __scopetilde_03_xsign;
    this->scopetilde_03_ymonitorvalue = __scopetilde_03_ymonitorvalue;
    this->scopetilde_03_ysign = __scopetilde_03_ysign;
}

void feedbackreader_01_perform(SampleValue * output, Index n) {
    auto& buffer = this->feedbacktilde_01_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = buffer[(Index)i];
    }
}

void feedbackreader_02_perform(SampleValue * output, Index n) {
    auto& buffer = this->feedbacktilde_02_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = buffer[(Index)i];
    }
}

void xfade_tilde_05_perform(
    const Sample * pos,
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out[(Index)i] = in1[(Index)i] * this->xfade_tilde_05_func_next(pos[(Index)i], 0) + in2[(Index)i] * this->xfade_tilde_05_func_next(pos[(Index)i], 1);
    }
}

void dspexpr_04_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_03_perform(const Sample * in1, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = rnbo_atan(in1[(Index)i]);//#map:_###_obj_###_:1
    }
}

void signaladder_01_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out[(Index)i] = in1[(Index)i] + in2[(Index)i];
    }
}

void gen_01_perform(
    const Sample * in1,
    number in2,
    number KnbWindowCoefficient,
    number KnbDelayTimeLeft,
    number KnbSmooth,
    number KnbDuty,
    number KnbSmoothWindow,
    SampleValue * out1,
    SampleValue * out2,
    SampleValue * out3,
    SampleValue * out4,
    SampleValue * out5,
    Index n
) {
    auto __gen_01_history_2_value = this->gen_01_history_2_value;
    auto __gen_01_history_1_value = this->gen_01_history_1_value;
    auto int_5_2 = this->intnum(1);
    auto min_9_11 = this->maximum(KnbSmoothWindow, 0.01);
    number rdiv_10_12 = (min_9_11 == 0. ? 0. : ((this->samplerate() == 0. ? 0. : (number)1000 / this->samplerate())) / min_9_11);
    number eq_16_19 = in2 == 0;
    auto int_20_22 = this->intnum(0);
    auto min_24_29 = this->maximum(KnbSmooth, 0.01);
    number rdiv_25_30 = (min_24_29 == 0. ? 0. : ((this->samplerate() == 0. ? 0. : (number)1000 / this->samplerate())) / min_24_29);
    auto int_33_39 = this->intnum(1);
    number clamp_43_48 = (KnbDuty > 1 ? 1 : (KnbDuty < 0 ? 0 : KnbDuty));
    number rsub_44_49 = 1 - clamp_43_48;
    auto power_58 = this->maximum(1, 1);
    number floor_53_59 = rnbo_floor(power_58);
    number mul_54_60 = floor_53_59 * 2;
    Index i;

    for (i = 0; i < n; i++) {
        auto revdel_dim_3_0 = this->dim(this->gen_01_revdel);
        auto revdel_chans_4_1 = this->channels(this->gen_01_revdel);
        number change_6_4 = this->gen_01_change_3_next(KnbWindowCoefficient);
        number latch_7_6 = this->gen_01_latch_5_next(__gen_01_history_1_value, change_6_4);
        number latch_8_10 = this->gen_01_latch_9_next(KnbWindowCoefficient, change_6_4);
        number plusequals_11_14 = this->gen_01_plusequals_13_next(rdiv_10_12, change_6_4);
        number clamp_12_15 = (plusequals_11_14 > 1 ? 1 : (plusequals_11_14 < 0 ? 0 : plusequals_11_14));
        number mix_13_16 = latch_7_6 + clamp_12_15 * (latch_8_10 - latch_7_6);
        number gen_14_17 = mix_13_16;
        number history_1_next_15_18 = fixdenorm(mix_13_16);
        number counter_17 = 0;
        number counter_18 = 0;
        number counter_19 = 0;
        array<number, 3> result_21 = this->gen_01_counter_20_next(int_5_2, eq_16_19, revdel_dim_3_0);
        counter_19 = result_21[2];
        counter_18 = result_21[1];
        counter_17 = result_21[0];
        this->poke_default(this->gen_01_revdel, in1[(Index)i], counter_17, 0, 0);
        number change_21_24 = this->gen_01_change_23_next(KnbDelayTimeLeft);
        number latch_22_26 = this->gen_01_latch_25_next(__gen_01_history_2_value, change_21_24);
        number latch_23_28 = this->gen_01_latch_27_next(KnbDelayTimeLeft, change_21_24);
        number plusequals_26_32 = this->gen_01_plusequals_31_next(rdiv_25_30, change_21_24);
        number clamp_27_33 = (plusequals_26_32 > 1 ? 1 : (plusequals_26_32 < 0 ? 0 : plusequals_26_32));
        number mix_28_34 = latch_22_26 + clamp_27_33 * (latch_23_28 - latch_22_26);
        number gen_29_35 = mix_28_34;
        number history_1_next_30_36 = fixdenorm(mix_28_34);
        auto mstosamps_31_37 = this->mstosamps(gen_29_35);
        number abs_32_38 = rnbo_abs(mstosamps_31_37);
        number counter_34 = 0;
        number counter_35 = 0;
        number counter_36 = 0;
        array<number, 3> result_41 = this->gen_01_counter_40_next(int_33_39, eq_16_19, mstosamps_31_37);
        counter_36 = result_41[2];
        counter_35 = result_41[1];
        counter_34 = result_41[0];
        auto scale_37_42 = this->scale(counter_34, int_20_22, mstosamps_31_37, mstosamps_31_37, int_20_22, 1);
        number div_38_43 = (abs_32_38 == 0. ? 0. : counter_34 / abs_32_38);
        number clamp_39_44 = (div_38_43 > 1 ? 1 : (div_38_43 < 0 ? 0 : div_38_43));
        auto triangle_40_45 = this->triangle(clamp_39_44, 0.5);
        number clamp_41_46 = (gen_14_17 > 1 ? 1 : (gen_14_17 < 0 ? 0 : gen_14_17));
        number eq_42_47 = clamp_41_46 == 1;
        number sub_45_50 = triangle_40_45 - rsub_44_49;
        number gt_46_51 = sub_45_50 > 0;
        auto scale_47_52 = this->scale(clamp_41_46, 1, 0, 0, 1, -1);
        number mul_48_53 = sub_45_50 * scale_47_52;
        number add_49_54 = mul_48_53 + rsub_44_49;
        number clamp_50_55 = (add_49_54 > 1 ? 1 : (add_49_54 < 0 ? 0 : add_49_54));
        number switch_51_56 = ((bool)(eq_42_47) ? gt_46_51 : clamp_50_55);
        number gen_52_57 = switch_51_56;
        out2[(Index)i] = gen_52_57;
        number clamp_55_61 = (triangle_40_45 > 1 ? 1 : (triangle_40_45 < 0 ? 0 : triangle_40_45));
        number sub_56_62 = clamp_55_61 - 1;
        number clamp_57_63 = (gen_14_17 > 1 ? 1 : (gen_14_17 < 0.000001 ? 0.000001 : gen_14_17));
        number rdiv_58_64 = (clamp_57_63 == 0. ? 0. : (number)2 / clamp_57_63);
        number mul_59_65 = sub_56_62 * rdiv_58_64;
        number pow_60_66 = fixnan(rnbo_pow(mul_59_65, mul_54_60));
        number mul_61_67 = pow_60_66 * -0.5;
        number exp_62_68 = rnbo_exp(mul_61_67);
        number gen_63_69 = exp_62_68;
        out4[(Index)i] = gen_63_69;
        number clamp_64_70 = (triangle_40_45 > 1 ? 1 : (triangle_40_45 < 0 ? 0 : triangle_40_45));
        number rsub_65_71 = 1 - gen_14_17;
        number clamp_66_72 = (rsub_65_71 > 1 ? 1 : (rsub_65_71 < 0 ? 0 : rsub_65_71));
        number gte_67_73 = clamp_64_70 >= clamp_66_72;
        number mul_68_74 = clamp_64_70 * 3.14159265358979323846;
        number div_69_75 = (clamp_66_72 == 0. ? 0. : mul_68_74 / clamp_66_72);
        number cos_70_76 = rnbo_cos(div_69_75);
        number rsub_71_77 = 1 - cos_70_76;
        number mul_72_78 = rsub_71_77 * 0.5;
        number switch_73_79 = ((bool)(gte_67_73) ? 1 : mul_72_78);
        number gen_74_80 = switch_73_79;
        out3[(Index)i] = gen_74_80;
        auto scale_75_81 = this->scale(triangle_40_45, 0, 1, 3.14159265358979323846, 6.28318530717958647692, 1);
        number cos_76_82 = rnbo_cos(scale_75_81);
        number sub_77_83 = cos_76_82 - 1;
        number clamp_78_84 = (gen_14_17 > 1 ? 1 : (gen_14_17 < 0 ? 0 : gen_14_17));
        number rsub_79_85 = 1 - clamp_78_84;
        number mul_80_86 = rsub_79_85 * 1.57079632679489661923;
        number tan_81_87 = rnbo_tan(mul_80_86);
        number abs_82_88 = rnbo_abs(tan_81_87);
        number mul_83_89 = sub_77_83 * abs_82_88;
        number exp_84_90 = rnbo_exp(mul_83_89);
        number gen_85_91 = exp_84_90;
        out5[(Index)i] = gen_85_91;
        number eq_86_92 = counter_35 == 1;
        number sah_87_94 = this->gen_01_sah_93_next(counter_17, eq_86_92, 0);
        number sub_88_95 = sah_87_94 - mstosamps_31_37;
        number add_89_96 = sub_88_95 + scale_37_42;
        number sample_revdel_90 = 0;
        number index_revdel_91 = 0;
        auto result_97 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_revdel, add_89_96, 0);
        index_revdel_91 = result_97[1];
        sample_revdel_90 = result_97[0];
        out1[(Index)i] = sample_revdel_90;
        __gen_01_history_1_value = history_1_next_15_18;
        __gen_01_history_2_value = history_1_next_30_36;
    }

    this->gen_01_history_1_value = __gen_01_history_1_value;
    this->gen_01_history_2_value = __gen_01_history_2_value;
}

void dspexpr_05_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void feedbackwriter_01_perform(const SampleValue * input, Index n) {
    auto& buffer = this->feedbacktilde_01_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        buffer[(Index)i] = input[(Index)i];
    }
}

void xfade_tilde_06_perform(
    const Sample * pos,
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out[(Index)i] = in1[(Index)i] * this->xfade_tilde_06_func_next(pos[(Index)i], 0) + in2[(Index)i] * this->xfade_tilde_06_func_next(pos[(Index)i], 1);
    }
}

void dspexpr_07_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_06_perform(const Sample * in1, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = rnbo_atan(in1[(Index)i]);//#map:_###_obj_###_:1
    }
}

void signaladder_02_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < n; i++) {
        out[(Index)i] = in1[(Index)i] + in2[(Index)i];
    }
}

void gen_02_perform(
    const Sample * in1,
    number in2,
    number KnbSmoothWindow,
    number KnbSmooth,
    number KnbDelayTimeRight,
    number KnbDuty,
    number KnbWindowCoefficient,
    SampleValue * out1,
    SampleValue * out2,
    SampleValue * out3,
    SampleValue * out4,
    SampleValue * out5,
    Index n
) {
    auto __gen_02_history_2_value = this->gen_02_history_2_value;
    auto __gen_02_history_1_value = this->gen_02_history_1_value;
    auto min_8_10 = this->maximum(KnbSmoothWindow, 0.01);
    number rdiv_9_11 = (min_8_10 == 0. ? 0. : ((this->samplerate() == 0. ? 0. : (number)1000 / this->samplerate())) / min_8_10);
    auto int_15_18 = this->intnum(1);
    number eq_16_19 = in2 == 0;
    auto int_20_22 = this->intnum(0);
    auto min_24_29 = this->maximum(KnbSmooth, 0.01);
    number rdiv_25_30 = (min_24_29 == 0. ? 0. : ((this->samplerate() == 0. ? 0. : (number)1000 / this->samplerate())) / min_24_29);
    auto int_33_39 = this->intnum(1);
    auto power_46 = this->maximum(1, 1);
    number floor_41_47 = rnbo_floor(power_46);
    number mul_42_48 = floor_41_47 * 2;
    number clamp_65_71 = (KnbDuty > 1 ? 1 : (KnbDuty < 0 ? 0 : KnbDuty));
    number rsub_66_72 = 1 - clamp_65_71;
    Index i;

    for (i = 0; i < n; i++) {
        auto revdelright_dim_3_0 = this->dim(this->gen_02_revdelright);
        auto revdelright_chans_4_1 = this->channels(this->gen_02_revdelright);
        number change_5_3 = this->gen_02_change_2_next(KnbWindowCoefficient);
        number latch_6_5 = this->gen_02_latch_4_next(__gen_02_history_1_value, change_5_3);
        number latch_7_9 = this->gen_02_latch_8_next(KnbWindowCoefficient, change_5_3);
        number plusequals_10_13 = this->gen_02_plusequals_12_next(rdiv_9_11, change_5_3);
        number clamp_11_14 = (plusequals_10_13 > 1 ? 1 : (plusequals_10_13 < 0 ? 0 : plusequals_10_13));
        number mix_12_15 = latch_6_5 + clamp_11_14 * (latch_7_9 - latch_6_5);
        number gen_13_16 = mix_12_15;
        number history_1_next_14_17 = fixdenorm(mix_12_15);
        number counter_17 = 0;
        number counter_18 = 0;
        number counter_19 = 0;
        array<number, 3> result_21 = this->gen_02_counter_20_next(int_15_18, eq_16_19, revdelright_dim_3_0);
        counter_19 = result_21[2];
        counter_18 = result_21[1];
        counter_17 = result_21[0];
        this->poke_default(this->gen_02_revdelright, in1[(Index)i], counter_17, 0, 0);
        number change_21_24 = this->gen_02_change_23_next(KnbDelayTimeRight);
        number latch_22_26 = this->gen_02_latch_25_next(__gen_02_history_2_value, change_21_24);
        number latch_23_28 = this->gen_02_latch_27_next(KnbDelayTimeRight, change_21_24);
        number plusequals_26_32 = this->gen_02_plusequals_31_next(rdiv_25_30, change_21_24);
        number clamp_27_33 = (plusequals_26_32 > 1 ? 1 : (plusequals_26_32 < 0 ? 0 : plusequals_26_32));
        number mix_28_34 = latch_22_26 + clamp_27_33 * (latch_23_28 - latch_22_26);
        number gen_29_35 = mix_28_34;
        number history_1_next_30_36 = fixdenorm(mix_28_34);
        auto mstosamps_31_37 = this->mstosamps(gen_29_35);
        number abs_32_38 = rnbo_abs(mstosamps_31_37);
        number counter_34 = 0;
        number counter_35 = 0;
        number counter_36 = 0;
        array<number, 3> result_41 = this->gen_02_counter_40_next(int_33_39, eq_16_19, mstosamps_31_37);
        counter_36 = result_41[2];
        counter_35 = result_41[1];
        counter_34 = result_41[0];
        auto scale_37_42 = this->scale(counter_34, int_20_22, mstosamps_31_37, mstosamps_31_37, int_20_22, 1);
        number div_38_43 = (abs_32_38 == 0. ? 0. : counter_34 / abs_32_38);
        number clamp_39_44 = (div_38_43 > 1 ? 1 : (div_38_43 < 0 ? 0 : div_38_43));
        auto triangle_40_45 = this->triangle(clamp_39_44, 0.5);
        number clamp_43_49 = (triangle_40_45 > 1 ? 1 : (triangle_40_45 < 0 ? 0 : triangle_40_45));
        number sub_44_50 = clamp_43_49 - 1;
        number clamp_45_51 = (gen_13_16 > 1 ? 1 : (gen_13_16 < 0.000001 ? 0.000001 : gen_13_16));
        number rdiv_46_52 = (clamp_45_51 == 0. ? 0. : (number)2 / clamp_45_51);
        number mul_47_53 = sub_44_50 * rdiv_46_52;
        number pow_48_54 = fixnan(rnbo_pow(mul_47_53, mul_42_48));
        number mul_49_55 = pow_48_54 * -0.5;
        number exp_50_56 = rnbo_exp(mul_49_55);
        number gen_51_57 = exp_50_56;
        out4[(Index)i] = gen_51_57;
        auto scale_52_58 = this->scale(triangle_40_45, 0, 1, 3.14159265358979323846, 6.28318530717958647692, 1);
        number cos_53_59 = rnbo_cos(scale_52_58);
        number sub_54_60 = cos_53_59 - 1;
        number clamp_55_61 = (gen_13_16 > 1 ? 1 : (gen_13_16 < 0 ? 0 : gen_13_16));
        number rsub_56_62 = 1 - clamp_55_61;
        number mul_57_63 = rsub_56_62 * 1.57079632679489661923;
        number tan_58_64 = rnbo_tan(mul_57_63);
        number abs_59_65 = rnbo_abs(tan_58_64);
        number mul_60_66 = sub_54_60 * abs_59_65;
        number exp_61_67 = rnbo_exp(mul_60_66);
        number gen_62_68 = exp_61_67;
        out5[(Index)i] = gen_62_68;
        number clamp_63_69 = (gen_13_16 > 1 ? 1 : (gen_13_16 < 0 ? 0 : gen_13_16));
        number eq_64_70 = clamp_63_69 == 1;
        number sub_67_73 = triangle_40_45 - rsub_66_72;
        number gt_68_74 = sub_67_73 > 0;
        auto scale_69_75 = this->scale(clamp_63_69, 1, 0, 0, 1, -1);
        number mul_70_76 = sub_67_73 * scale_69_75;
        number add_71_77 = mul_70_76 + rsub_66_72;
        number clamp_72_78 = (add_71_77 > 1 ? 1 : (add_71_77 < 0 ? 0 : add_71_77));
        number switch_73_79 = ((bool)(eq_64_70) ? gt_68_74 : clamp_72_78);
        number gen_74_80 = switch_73_79;
        out2[(Index)i] = gen_74_80;
        number clamp_75_81 = (triangle_40_45 > 1 ? 1 : (triangle_40_45 < 0 ? 0 : triangle_40_45));
        number rsub_76_82 = 1 - gen_13_16;
        number clamp_77_83 = (rsub_76_82 > 1 ? 1 : (rsub_76_82 < 0 ? 0 : rsub_76_82));
        number gte_78_84 = clamp_75_81 >= clamp_77_83;
        number mul_79_85 = clamp_75_81 * 3.14159265358979323846;
        number div_80_86 = (clamp_77_83 == 0. ? 0. : mul_79_85 / clamp_77_83);
        number cos_81_87 = rnbo_cos(div_80_86);
        number rsub_82_88 = 1 - cos_81_87;
        number mul_83_89 = rsub_82_88 * 0.5;
        number switch_84_90 = ((bool)(gte_78_84) ? 1 : mul_83_89);
        number gen_85_91 = switch_84_90;
        out3[(Index)i] = gen_85_91;
        number eq_86_92 = counter_35 == 1;
        number sah_87_94 = this->gen_02_sah_93_next(counter_17, eq_86_92, 0);
        number sub_88_95 = sah_87_94 - mstosamps_31_37;
        number add_89_96 = sub_88_95 + scale_37_42;
        number sample_revdelright_90 = 0;
        number index_revdelright_91 = 0;
        auto result_97 = this->peek_boundmode_wrap_interp_cubic(this->gen_02_revdelright, add_89_96, 0);
        index_revdelright_91 = result_97[1];
        sample_revdelright_90 = result_97[0];
        out1[(Index)i] = sample_revdelright_90;
        __gen_02_history_1_value = history_1_next_14_17;
        __gen_02_history_2_value = history_1_next_30_36;
    }

    this->gen_02_history_1_value = __gen_02_history_1_value;
    this->gen_02_history_2_value = __gen_02_history_2_value;
}

void p_02_perform(
    const SampleValue * in2,
    const SampleValue * in3,
    const SampleValue * in4,
    const SampleValue * in5,
    const SampleValue * in6,
    const SampleValue * in8,
    const SampleValue * in9,
    const SampleValue * in10,
    const SampleValue * in11,
    const SampleValue * in12,
    const SampleValue * in13,
    SampleValue * out1,
    SampleValue * out2,
    SampleValue * out3,
    SampleValue * out4,
    Index n
) {
    // subpatcher: Mixer
    ConstSampleArray<11> ins = {in2, in3, in4, in5, in6, in8, in9, in10, in11, in12, in13};

    SampleArray<4> outs = {out1, out2, out3, out4};
    this->p_02->process(ins, 11, outs, 4, n);
}

void p_01_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    const SampleValue * in4,
    const SampleValue * in5,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    // subpatcher: Mix~
    ConstSampleArray<5> ins = {in1, in2, in3, in4, in5};

    SampleArray<2> outs = {out1, out2};
    this->p_01->process(ins, 5, outs, 2, n);
}

void scopetilde_02_perform(const SampleValue * x, const SampleValue * y, Index n) {
    auto __scopetilde_02_ysign = this->scopetilde_02_ysign;
    auto __scopetilde_02_ymonitorvalue = this->scopetilde_02_ymonitorvalue;
    auto __scopetilde_02_xsign = this->scopetilde_02_xsign;
    auto __scopetilde_02_xmonitorvalue = this->scopetilde_02_xmonitorvalue;
    auto __scopetilde_02_mode = this->scopetilde_02_mode;

    for (Index i = 0; i < n; i++) {
        number xval = x[(Index)i];
        number yval = y[(Index)i];

        if (__scopetilde_02_mode == 1) {
            number xabsval = rnbo_abs(xval);

            if (xabsval > __scopetilde_02_xmonitorvalue) {
                __scopetilde_02_xmonitorvalue = xabsval;
                __scopetilde_02_xsign = (xval < 0 ? -1 : 1);
            }

            number yabsval = rnbo_abs(yval);

            if (yabsval > __scopetilde_02_ymonitorvalue) {
                __scopetilde_02_ymonitorvalue = yabsval;
                __scopetilde_02_ysign = (yval < 0 ? -1 : 1);
            }
        } else {
            __scopetilde_02_xmonitorvalue = xval;
            __scopetilde_02_xsign = 1;
            __scopetilde_02_ymonitorvalue = yval;
            __scopetilde_02_ysign = 1;
        }

        this->scopetilde_02_effectiveCount--;

        if (this->scopetilde_02_effectiveCount <= 0) {
            this->scopetilde_02_updateEffectiveCount();
            this->scopetilde_02_monitorbuffer->push(__scopetilde_02_xmonitorvalue * __scopetilde_02_xsign);

            if (__scopetilde_02_mode == 1)
                __scopetilde_02_xmonitorvalue = 0;

            if (this->scopetilde_02_monitorbuffer->length >= 128 * (1 + 0)) {
                this->getEngine()->sendListMessage(
                    TAG("monitor"),
                    TAG("scope~_obj-78"),
                    this->scopetilde_02_monitorbuffer,
                    this->_currentTime
                );;

                this->scopetilde_02_monitorbuffer->length = 0;
            }
        }
    }

    this->scopetilde_02_xmonitorvalue = __scopetilde_02_xmonitorvalue;
    this->scopetilde_02_xsign = __scopetilde_02_xsign;
    this->scopetilde_02_ymonitorvalue = __scopetilde_02_ymonitorvalue;
    this->scopetilde_02_ysign = __scopetilde_02_ysign;
}

void scopetilde_01_perform(const SampleValue * x, const SampleValue * y, Index n) {
    auto __scopetilde_01_ysign = this->scopetilde_01_ysign;
    auto __scopetilde_01_ymonitorvalue = this->scopetilde_01_ymonitorvalue;
    auto __scopetilde_01_xsign = this->scopetilde_01_xsign;
    auto __scopetilde_01_xmonitorvalue = this->scopetilde_01_xmonitorvalue;
    auto __scopetilde_01_mode = this->scopetilde_01_mode;

    for (Index i = 0; i < n; i++) {
        number xval = x[(Index)i];
        number yval = y[(Index)i];

        if (__scopetilde_01_mode == 1) {
            number xabsval = rnbo_abs(xval);

            if (xabsval > __scopetilde_01_xmonitorvalue) {
                __scopetilde_01_xmonitorvalue = xabsval;
                __scopetilde_01_xsign = (xval < 0 ? -1 : 1);
            }

            number yabsval = rnbo_abs(yval);

            if (yabsval > __scopetilde_01_ymonitorvalue) {
                __scopetilde_01_ymonitorvalue = yabsval;
                __scopetilde_01_ysign = (yval < 0 ? -1 : 1);
            }
        } else {
            __scopetilde_01_xmonitorvalue = xval;
            __scopetilde_01_xsign = 1;
            __scopetilde_01_ymonitorvalue = yval;
            __scopetilde_01_ysign = 1;
        }

        this->scopetilde_01_effectiveCount--;

        if (this->scopetilde_01_effectiveCount <= 0) {
            this->scopetilde_01_updateEffectiveCount();
            this->scopetilde_01_monitorbuffer->push(__scopetilde_01_xmonitorvalue * __scopetilde_01_xsign);

            if (__scopetilde_01_mode == 1)
                __scopetilde_01_xmonitorvalue = 0;

            if (this->scopetilde_01_monitorbuffer->length >= 128 * (1 + 0)) {
                this->getEngine()->sendListMessage(
                    TAG("monitor"),
                    TAG("scope~_obj-138"),
                    this->scopetilde_01_monitorbuffer,
                    this->_currentTime
                );;

                this->scopetilde_01_monitorbuffer->length = 0;
            }
        }
    }

    this->scopetilde_01_xmonitorvalue = __scopetilde_01_xmonitorvalue;
    this->scopetilde_01_xsign = __scopetilde_01_xsign;
    this->scopetilde_01_ymonitorvalue = __scopetilde_01_ymonitorvalue;
    this->scopetilde_01_ysign = __scopetilde_01_ysign;
}

void dspexpr_08_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void feedbackwriter_02_perform(const SampleValue * input, Index n) {
    auto& buffer = this->feedbacktilde_02_feedbackbuffer;

    for (Index i = 0; i < n; i++) {
        buffer[(Index)i] = input[(Index)i];
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

void data_02_srout_set(number ) {}

void data_02_chanout_set(number ) {}

void data_02_sizeout_set(number v) {
    this->data_02_sizeout = v;
}

void numberobj_01_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_01_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_01_value = localvalue;
}

void toggle_01_value_number_setter(number v) {
    this->toggle_01_value_number = (v != 0 ? 1 : 0);
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

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
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

    if (this->numberobj_08_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_08_value = localvalue;
}

void numberobj_09_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_09_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_09_value = localvalue;
}

void numberobj_10_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_10_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_10_value = localvalue;
}

void numberobj_11_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 100) {
        localvalue = 100;
    }

    if (this->numberobj_11_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_11_value = localvalue;
}

void param_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_01_value;
}

void param_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_01_value_set(preset["value"]);
}

void param_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_02_value;
}

void param_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_02_value_set(preset["value"]);
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

void param_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_05_value;
}

void param_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_05_value_set(preset["value"]);
}

void param_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_06_value;
}

void param_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_06_value_set(preset["value"]);
}

void param_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_07_value;
}

void param_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_07_value_set(preset["value"]);
}

void scopetilde_01_updateEffectiveCount() {
    number effectiveCount = 256 * 1 + 256 * 0;
    this->scopetilde_01_effectiveCount = this->maximum(effectiveCount, 256);
}

void scopetilde_01_dspsetup(bool force) {
    if ((bool)(this->scopetilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    {
        this->scopetilde_01_mode = 1;
    }

    this->getEngine()->sendListMessage(
        TAG("setup"),
        TAG("scope~_obj-138"),
        {1, 1, this->samplerate(), 0, 1, 0, 0, 128, this->scopetilde_01_mode},
        this->_currentTime
    );;

    this->scopetilde_01_updateEffectiveCount();
    this->scopetilde_01_setupDone = true;
}

void param_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_08_value;
}

void param_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_08_value_set(preset["value"]);
}

void numberobj_01_init() {
    this->numberobj_01_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-55"), 1, this->_currentTime);
}

void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_01_value;
}

void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_01_value_set(preset["value"]);
}

void param_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_09_value;
}

void param_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_09_value_set(preset["value"]);
}

void toggle_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_01_value_number;
}

void toggle_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_01_value_number_set(preset["value"]);
}

void param_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_10_value;
}

void param_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_10_value_set(preset["value"]);
}

void numberobj_02_init() {
    this->numberobj_02_currentFormat = 0;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-104"), 1, this->_currentTime);
}

void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_02_value;
}

void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_02_value_set(preset["value"]);
}

number gen_01_history_2_getvalue() {
    return this->gen_01_history_2_value;
}

void gen_01_history_2_setvalue(number val) {
    this->gen_01_history_2_value = val;
}

void gen_01_history_2_reset() {
    this->gen_01_history_2_value = 0;
}

void gen_01_history_2_init() {
    this->gen_01_history_2_value = 0;
}

number gen_01_history_1_getvalue() {
    return this->gen_01_history_1_value;
}

void gen_01_history_1_setvalue(number val) {
    this->gen_01_history_1_value = val;
}

void gen_01_history_1_reset() {
    this->gen_01_history_1_value = 0;
}

void gen_01_history_1_init() {
    this->gen_01_history_1_value = 0;
}

number gen_01_change_3_next(number x) {
    number temp = x - this->gen_01_change_3_prev;
    this->gen_01_change_3_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_3_init() {
    this->gen_01_change_3_prev = 0;
}

void gen_01_change_3_reset() {
    this->gen_01_change_3_prev = 0;
}

number gen_01_latch_5_next(number x, number control) {
    if (control != 0.)
        this->gen_01_latch_5_value = x;

    return this->gen_01_latch_5_value;
}

void gen_01_latch_5_dspsetup() {
    this->gen_01_latch_5_reset();
}

void gen_01_latch_5_reset() {
    this->gen_01_latch_5_value = 0;
}

number gen_01_latch_9_next(number x, number control) {
    if (control != 0.)
        this->gen_01_latch_9_value = x;

    return this->gen_01_latch_9_value;
}

void gen_01_latch_9_dspsetup() {
    this->gen_01_latch_9_reset();
}

void gen_01_latch_9_reset() {
    this->gen_01_latch_9_value = 0;
}

number gen_01_plusequals_13_next(number x, number reset) {
    {
        {
            this->gen_01_plusequals_13_value = ((bool)(reset) ? 0 + x : this->gen_01_plusequals_13_value + x);
            return this->gen_01_plusequals_13_value;
        }
    }
}

void gen_01_plusequals_13_reset() {
    this->gen_01_plusequals_13_value = 0;
}

array<number, 3> gen_01_counter_20_next(number a, number reset, number limit) {
    number carry_flag = 0;

    if (reset != 0) {
        this->gen_01_counter_20_count = 0;
        this->gen_01_counter_20_carry = 0;
    } else {
        this->gen_01_counter_20_count += a;

        if (limit != 0) {
            if ((a > 0 && this->gen_01_counter_20_count >= limit) || (a < 0 && this->gen_01_counter_20_count <= limit)) {
                this->gen_01_counter_20_count = 0;
                this->gen_01_counter_20_carry += 1;
                carry_flag = 1;
            }
        }
    }

    return {this->gen_01_counter_20_count, carry_flag, this->gen_01_counter_20_carry};
}

void gen_01_counter_20_init() {
    this->gen_01_counter_20_count = 0;
}

void gen_01_counter_20_reset() {
    this->gen_01_counter_20_carry = 0;
    this->gen_01_counter_20_count = 0;
}

number gen_01_change_23_next(number x) {
    number temp = x - this->gen_01_change_23_prev;
    this->gen_01_change_23_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_01_change_23_init() {
    this->gen_01_change_23_prev = 0;
}

void gen_01_change_23_reset() {
    this->gen_01_change_23_prev = 0;
}

number gen_01_latch_25_next(number x, number control) {
    if (control != 0.)
        this->gen_01_latch_25_value = x;

    return this->gen_01_latch_25_value;
}

void gen_01_latch_25_dspsetup() {
    this->gen_01_latch_25_reset();
}

void gen_01_latch_25_reset() {
    this->gen_01_latch_25_value = 0;
}

number gen_01_latch_27_next(number x, number control) {
    if (control != 0.)
        this->gen_01_latch_27_value = x;

    return this->gen_01_latch_27_value;
}

void gen_01_latch_27_dspsetup() {
    this->gen_01_latch_27_reset();
}

void gen_01_latch_27_reset() {
    this->gen_01_latch_27_value = 0;
}

number gen_01_plusequals_31_next(number x, number reset) {
    {
        {
            this->gen_01_plusequals_31_value = ((bool)(reset) ? 0 + x : this->gen_01_plusequals_31_value + x);
            return this->gen_01_plusequals_31_value;
        }
    }
}

void gen_01_plusequals_31_reset() {
    this->gen_01_plusequals_31_value = 0;
}

array<number, 3> gen_01_counter_40_next(number a, number reset, number limit) {
    number carry_flag = 0;

    if (reset != 0) {
        this->gen_01_counter_40_count = 0;
        this->gen_01_counter_40_carry = 0;
    } else {
        this->gen_01_counter_40_count += a;

        if (limit != 0) {
            if ((a > 0 && this->gen_01_counter_40_count >= limit) || (a < 0 && this->gen_01_counter_40_count <= limit)) {
                this->gen_01_counter_40_count = 0;
                this->gen_01_counter_40_carry += 1;
                carry_flag = 1;
            }
        }
    }

    return {this->gen_01_counter_40_count, carry_flag, this->gen_01_counter_40_carry};
}

void gen_01_counter_40_init() {
    this->gen_01_counter_40_count = 0;
}

void gen_01_counter_40_reset() {
    this->gen_01_counter_40_carry = 0;
    this->gen_01_counter_40_count = 0;
}

number gen_01_sah_93_next(number x, number trig, number thresh) {
    RNBO_UNUSED(thresh);

    if (this->gen_01_sah_93_prev <= 0 && trig > 0)
        this->gen_01_sah_93_value = x;

    this->gen_01_sah_93_prev = trig;
    return this->gen_01_sah_93_value;
}

void gen_01_sah_93_reset() {
    this->gen_01_sah_93_prev = 0.;
    this->gen_01_sah_93_value = 0.;
}

void gen_01_dspsetup(bool force) {
    if ((bool)(this->gen_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gen_01_setupDone = true;
    this->gen_01_latch_5_dspsetup();
    this->gen_01_latch_9_dspsetup();
    this->gen_01_latch_25_dspsetup();
    this->gen_01_latch_27_dspsetup();
}

number xfade_tilde_05_func_next(number pos, int channel) {
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
                    {
                        return this->safesqrt(1.0 - rnbo_abs(pos));
                    }
                }
            } else {
                return 0;
            }
        }
    }
}

void xfade_tilde_05_func_reset() {}

void numberobj_03_init() {
    this->numberobj_03_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-80"), 1, this->_currentTime);
}

void numberobj_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_03_value;
}

void numberobj_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_03_value_set(preset["value"]);
}

void numberobj_04_init() {
    this->numberobj_04_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-82"), 1, this->_currentTime);
}

void numberobj_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_04_value;
}

void numberobj_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_04_value_set(preset["value"]);
}

void param_11_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_11_value;
}

void param_11_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_11_value_set(preset["value"]);
}

void param_12_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_12_value;
}

void param_12_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_12_value_set(preset["value"]);
}

void numberobj_05_init() {
    this->numberobj_05_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-119"), 1, this->_currentTime);
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
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-17"), 1, this->_currentTime);
}

void numberobj_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_06_value;
}

void numberobj_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_06_value_set(preset["value"]);
}

void param_13_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_13_value;
}

void param_13_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_13_value_set(preset["value"]);
}

void numberobj_07_init() {
    this->numberobj_07_currentFormat = 0;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-99"), 1, this->_currentTime);
}

void numberobj_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_07_value;
}

void numberobj_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_07_value_set(preset["value"]);
}

number xfade_tilde_06_func_next(number pos, int channel) {
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
                    {
                        return this->safesqrt(1.0 - rnbo_abs(pos));
                    }
                }
            } else {
                return 0;
            }
        }
    }
}

void xfade_tilde_06_func_reset() {}

number gen_02_history_2_getvalue() {
    return this->gen_02_history_2_value;
}

void gen_02_history_2_setvalue(number val) {
    this->gen_02_history_2_value = val;
}

void gen_02_history_2_reset() {
    this->gen_02_history_2_value = 0;
}

void gen_02_history_2_init() {
    this->gen_02_history_2_value = 0;
}

number gen_02_history_1_getvalue() {
    return this->gen_02_history_1_value;
}

void gen_02_history_1_setvalue(number val) {
    this->gen_02_history_1_value = val;
}

void gen_02_history_1_reset() {
    this->gen_02_history_1_value = 0;
}

void gen_02_history_1_init() {
    this->gen_02_history_1_value = 0;
}

number gen_02_change_2_next(number x) {
    number temp = x - this->gen_02_change_2_prev;
    this->gen_02_change_2_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_02_change_2_init() {
    this->gen_02_change_2_prev = 0;
}

void gen_02_change_2_reset() {
    this->gen_02_change_2_prev = 0;
}

number gen_02_latch_4_next(number x, number control) {
    if (control != 0.)
        this->gen_02_latch_4_value = x;

    return this->gen_02_latch_4_value;
}

void gen_02_latch_4_dspsetup() {
    this->gen_02_latch_4_reset();
}

void gen_02_latch_4_reset() {
    this->gen_02_latch_4_value = 0;
}

number gen_02_latch_8_next(number x, number control) {
    if (control != 0.)
        this->gen_02_latch_8_value = x;

    return this->gen_02_latch_8_value;
}

void gen_02_latch_8_dspsetup() {
    this->gen_02_latch_8_reset();
}

void gen_02_latch_8_reset() {
    this->gen_02_latch_8_value = 0;
}

number gen_02_plusequals_12_next(number x, number reset) {
    {
        {
            this->gen_02_plusequals_12_value = ((bool)(reset) ? 0 + x : this->gen_02_plusequals_12_value + x);
            return this->gen_02_plusequals_12_value;
        }
    }
}

void gen_02_plusequals_12_reset() {
    this->gen_02_plusequals_12_value = 0;
}

array<number, 3> gen_02_counter_20_next(number a, number reset, number limit) {
    number carry_flag = 0;

    if (reset != 0) {
        this->gen_02_counter_20_count = 0;
        this->gen_02_counter_20_carry = 0;
    } else {
        this->gen_02_counter_20_count += a;

        if (limit != 0) {
            if ((a > 0 && this->gen_02_counter_20_count >= limit) || (a < 0 && this->gen_02_counter_20_count <= limit)) {
                this->gen_02_counter_20_count = 0;
                this->gen_02_counter_20_carry += 1;
                carry_flag = 1;
            }
        }
    }

    return {this->gen_02_counter_20_count, carry_flag, this->gen_02_counter_20_carry};
}

void gen_02_counter_20_init() {
    this->gen_02_counter_20_count = 0;
}

void gen_02_counter_20_reset() {
    this->gen_02_counter_20_carry = 0;
    this->gen_02_counter_20_count = 0;
}

number gen_02_change_23_next(number x) {
    number temp = x - this->gen_02_change_23_prev;
    this->gen_02_change_23_prev = x;
    return (temp > 0. ? 1. : (temp < 0. ? -1. : 0));
}

void gen_02_change_23_init() {
    this->gen_02_change_23_prev = 0;
}

void gen_02_change_23_reset() {
    this->gen_02_change_23_prev = 0;
}

number gen_02_latch_25_next(number x, number control) {
    if (control != 0.)
        this->gen_02_latch_25_value = x;

    return this->gen_02_latch_25_value;
}

void gen_02_latch_25_dspsetup() {
    this->gen_02_latch_25_reset();
}

void gen_02_latch_25_reset() {
    this->gen_02_latch_25_value = 0;
}

number gen_02_latch_27_next(number x, number control) {
    if (control != 0.)
        this->gen_02_latch_27_value = x;

    return this->gen_02_latch_27_value;
}

void gen_02_latch_27_dspsetup() {
    this->gen_02_latch_27_reset();
}

void gen_02_latch_27_reset() {
    this->gen_02_latch_27_value = 0;
}

number gen_02_plusequals_31_next(number x, number reset) {
    {
        {
            this->gen_02_plusequals_31_value = ((bool)(reset) ? 0 + x : this->gen_02_plusequals_31_value + x);
            return this->gen_02_plusequals_31_value;
        }
    }
}

void gen_02_plusequals_31_reset() {
    this->gen_02_plusequals_31_value = 0;
}

array<number, 3> gen_02_counter_40_next(number a, number reset, number limit) {
    number carry_flag = 0;

    if (reset != 0) {
        this->gen_02_counter_40_count = 0;
        this->gen_02_counter_40_carry = 0;
    } else {
        this->gen_02_counter_40_count += a;

        if (limit != 0) {
            if ((a > 0 && this->gen_02_counter_40_count >= limit) || (a < 0 && this->gen_02_counter_40_count <= limit)) {
                this->gen_02_counter_40_count = 0;
                this->gen_02_counter_40_carry += 1;
                carry_flag = 1;
            }
        }
    }

    return {this->gen_02_counter_40_count, carry_flag, this->gen_02_counter_40_carry};
}

void gen_02_counter_40_init() {
    this->gen_02_counter_40_count = 0;
}

void gen_02_counter_40_reset() {
    this->gen_02_counter_40_carry = 0;
    this->gen_02_counter_40_count = 0;
}

number gen_02_sah_93_next(number x, number trig, number thresh) {
    RNBO_UNUSED(thresh);

    if (this->gen_02_sah_93_prev <= 0 && trig > 0)
        this->gen_02_sah_93_value = x;

    this->gen_02_sah_93_prev = trig;
    return this->gen_02_sah_93_value;
}

void gen_02_sah_93_reset() {
    this->gen_02_sah_93_prev = 0.;
    this->gen_02_sah_93_value = 0.;
}

void gen_02_dspsetup(bool force) {
    if ((bool)(this->gen_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gen_02_setupDone = true;
    this->gen_02_latch_4_dspsetup();
    this->gen_02_latch_8_dspsetup();
    this->gen_02_latch_25_dspsetup();
    this->gen_02_latch_27_dspsetup();
}

void numberobj_08_init() {
    this->numberobj_08_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-67"), 1, this->_currentTime);
}

void numberobj_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_08_value;
}

void numberobj_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_08_value_set(preset["value"]);
}

void numberobj_09_init() {
    this->numberobj_09_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-70"), 1, this->_currentTime);
}

void numberobj_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_09_value;
}

void numberobj_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_09_value_set(preset["value"]);
}

void scopetilde_02_updateEffectiveCount() {
    number effectiveCount = 256 * 1 + 256 * 0;
    this->scopetilde_02_effectiveCount = this->maximum(effectiveCount, 256);
}

void scopetilde_02_dspsetup(bool force) {
    if ((bool)(this->scopetilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    {
        this->scopetilde_02_mode = 1;
    }

    this->getEngine()->sendListMessage(
        TAG("setup"),
        TAG("scope~_obj-78"),
        {1, 1, this->samplerate(), 0, 1, 0, 0, 128, this->scopetilde_02_mode},
        this->_currentTime
    );;

    this->scopetilde_02_updateEffectiveCount();
    this->scopetilde_02_setupDone = true;
}

void numberobj_10_init() {
    this->numberobj_10_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-41"), 1, this->_currentTime);
}

void numberobj_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_10_value;
}

void numberobj_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_10_value_set(preset["value"]);
}

void numberobj_11_init() {
    this->numberobj_11_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-44"), 1, this->_currentTime);
}

void numberobj_11_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_11_value;
}

void numberobj_11_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_11_value_set(preset["value"]);
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

void data_02_init() {
    this->data_02_buffer->setWantsFill(true);
}

Index data_02_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    number size = 0;
    return (Index)(size);
}

void data_02_dspsetup(bool force) {
    if ((bool)(this->data_02_setupDone) && (bool)(!(bool)(force)))
        return;

    if (this->data_02_sizemode == 2) {
        this->data_02_buffer = this->data_02_buffer->setSize((Index)(this->mstosamps(this->data_02_sizems)));
        updateDataRef(this, this->data_02_buffer);
    } else if (this->data_02_sizemode == 3) {
        this->data_02_buffer = this->data_02_buffer->setSize(this->data_02_evaluateSizeExpr(this->samplerate(), this->vectorsize()));
        updateDataRef(this, this->data_02_buffer);
    }

    this->data_02_setupDone = true;
}

void data_02_bufferUpdated() {
    this->data_02_report();
}

void data_02_report() {
    this->data_02_srout_set(this->data_02_buffer->getSampleRate());
    this->data_02_chanout_set(this->data_02_buffer->getChannels());
    this->data_02_sizeout_set(this->data_02_buffer->getSize());
}

void scopetilde_03_updateEffectiveCount() {
    number effectiveCount = 256 * 0 + 256 * 0;
    this->scopetilde_03_effectiveCount = this->maximum(effectiveCount, 256);
}

void scopetilde_03_dspsetup(bool force) {
    if ((bool)(this->scopetilde_03_setupDone) && (bool)(!(bool)(force)))
        return;

    {
        this->scopetilde_03_mode = 1;
    }

    this->getEngine()->sendListMessage(
        TAG("setup"),
        TAG("scope~_obj-28"),
        {1, 1, this->samplerate(), 0, 0, 0, 0, 128, this->scopetilde_03_mode},
        this->_currentTime
    );;

    this->scopetilde_03_updateEffectiveCount();
    this->scopetilde_03_setupDone = true;
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
    param_01_value = 300;
    param_02_value = 300;
    param_03_value = 50;
    param_04_value = 0.5;
    param_05_value = 0;
    param_06_value = 0;
    param_07_value = 0;
    param_08_value = 0;
    numberobj_01_value = 0;
    numberobj_01_value_setter(numberobj_01_value);
    param_09_value = 0;
    toggle_01_value_number = 0;
    toggle_01_value_number_setter(toggle_01_value_number);
    param_10_value = 0;
    p_01_target = 0;
    numberobj_02_value = 0;
    numberobj_02_value_setter(numberobj_02_value);
    expr_04_in1 = 0;
    expr_04_in2 = 1;
    expr_04_out1 = 0;
    p_02_target = 0;
    gen_01_in1 = 0;
    gen_01_in2 = 0;
    gen_01_KnbWindowCoefficient = 0;
    gen_01_KnbDelayTimeLeft = 0;
    gen_01_KnbSmooth = 10;
    gen_01_KnbDuty = 0;
    gen_01_KnbSmoothWindow = 20;
    dspexpr_03_in1 = 0;
    dspexpr_04_in1 = 0;
    dspexpr_04_in2 = 0;
    xfade_tilde_05_pos = 0;
    dspexpr_05_in1 = 0;
    dspexpr_05_in2 = 0;
    numberobj_03_value = 0;
    numberobj_03_value_setter(numberobj_03_value);
    linetilde_01_time = 50;
    linetilde_01_keepramp = 1;
    numberobj_04_value = 0;
    numberobj_04_value_setter(numberobj_04_value);
    scale_01_inlow = 0;
    scale_01_inhigh = 100;
    scale_01_outlow = 0;
    scale_01_outhigh = 0.99;
    scale_01_power = 1;
    param_11_value = 50;
    param_12_value = 50;
    numberobj_05_value = 0;
    numberobj_05_value_setter(numberobj_05_value);
    expr_05_in1 = 0;
    expr_05_in2 = 100;
    expr_05_out1 = 0;
    linetilde_02_time = 10;
    linetilde_02_keepramp = 1;
    numberobj_06_value = 0;
    numberobj_06_value_setter(numberobj_06_value);
    param_13_value = 50;
    numberobj_07_value = 0;
    numberobj_07_value_setter(numberobj_07_value);
    expr_07_in1 = 0;
    expr_07_in2 = 1;
    expr_07_out1 = 0;
    dspexpr_06_in1 = 0;
    dspexpr_07_in1 = 0;
    dspexpr_07_in2 = 0;
    xfade_tilde_06_pos = 0;
    dspexpr_08_in1 = 0;
    dspexpr_08_in2 = 0;
    gen_02_in1 = 0;
    gen_02_in2 = 0;
    gen_02_KnbSmoothWindow = 20;
    gen_02_KnbSmooth = 10;
    gen_02_KnbDelayTimeRight = 0;
    gen_02_KnbDuty = 0;
    gen_02_KnbWindowCoefficient = 0;
    numberobj_08_value = 0;
    numberobj_08_value_setter(numberobj_08_value);
    expr_08_in1 = 0;
    expr_08_in2 = 100;
    expr_08_out1 = 0;
    linetilde_03_time = 10;
    linetilde_03_keepramp = 1;
    numberobj_09_value = 0;
    numberobj_09_value_setter(numberobj_09_value);
    numberobj_10_value = 0;
    numberobj_10_value_setter(numberobj_10_value);
    expr_09_in1 = 0;
    expr_09_in2 = 100;
    expr_09_out1 = 0;
    linetilde_04_time = 10;
    linetilde_04_keepramp = 1;
    numberobj_11_value = 0;
    numberobj_11_value_setter(numberobj_11_value);
    data_01_sizeout = 0;
    data_01_size = 0;
    data_01_sizems = 10000;
    data_01_normalize = 0.995;
    data_01_channels = 1;
    data_02_sizeout = 0;
    data_02_size = 0;
    data_02_sizems = 10000;
    data_02_normalize = 0.995;
    data_02_channels = 1;
    ctlin_01_input = 0;
    ctlin_01_controller = 5;
    ctlin_01_channel = -1;
    expr_01_in1 = 0;
    expr_01_in2 = 0.007874015748;
    expr_01_out1 = 0;
    ctlin_02_input = 0;
    ctlin_02_controller = 6;
    ctlin_02_channel = -1;
    expr_02_in1 = 0;
    expr_02_in2 = 0.007874015748;
    expr_02_out1 = 0;
    ctlin_03_input = 0;
    ctlin_03_controller = 1;
    ctlin_03_channel = -1;
    expr_03_in1 = 0;
    expr_03_in2 = 0.007874015748;
    expr_03_out1 = 0;
    ctlin_04_input = 0;
    ctlin_04_controller = 6;
    ctlin_04_channel = -1;
    expr_06_in1 = 0;
    expr_06_in2 = 0.007874015748;
    expr_06_out1 = 0;
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
    signals[7] = nullptr;
    signals[8] = nullptr;
    signals[9] = nullptr;
    signals[10] = nullptr;
    signals[11] = nullptr;
    signals[12] = nullptr;
    signals[13] = nullptr;
    signals[14] = nullptr;
    signals[15] = nullptr;
    signals[16] = nullptr;
    signals[17] = nullptr;
    signals[18] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    param_01_lastValue = 0;
    param_02_lastValue = 0;
    param_03_lastValue = 0;
    param_04_lastValue = 0;
    param_05_lastValue = 0;
    param_06_lastValue = 0;
    param_07_lastValue = 0;
    scopetilde_01_lastValue = 0;
    scopetilde_01_effectiveCount = 256;
    scopetilde_01_xsign = 1;
    scopetilde_01_ysign = 1;
    scopetilde_01_mode = 0;
    scopetilde_01_setupDone = false;
    param_08_lastValue = 0;
    numberobj_01_currentFormat = 6;
    numberobj_01_lastValue = 0;
    param_09_lastValue = 0;
    toggle_01_lastValue = 0;
    param_10_lastValue = 0;
    numberobj_02_currentFormat = 6;
    numberobj_02_lastValue = 0;
    gen_01_history_2_value = 0;
    gen_01_history_1_value = 0;
    gen_01_change_3_prev = 0;
    gen_01_latch_5_value = 0;
    gen_01_latch_9_value = 0;
    gen_01_plusequals_13_value = 0;
    gen_01_counter_20_carry = 0;
    gen_01_counter_20_count = 0;
    gen_01_change_23_prev = 0;
    gen_01_latch_25_value = 0;
    gen_01_latch_27_value = 0;
    gen_01_plusequals_31_value = 0;
    gen_01_counter_40_carry = 0;
    gen_01_counter_40_count = 0;
    gen_01_sah_93_prev = 0;
    gen_01_sah_93_value = 0;
    gen_01_setupDone = false;
    feedbacktilde_01_feedbackbuffer = nullptr;
    numberobj_03_currentFormat = 6;
    numberobj_03_lastValue = 0;
    linetilde_01_currentValue = 0;
    numberobj_04_currentFormat = 6;
    numberobj_04_lastValue = 0;
    param_11_lastValue = 0;
    param_12_lastValue = 0;
    numberobj_05_currentFormat = 6;
    numberobj_05_lastValue = 0;
    linetilde_02_currentValue = 0;
    numberobj_06_currentFormat = 6;
    numberobj_06_lastValue = 0;
    param_13_lastValue = 0;
    numberobj_07_currentFormat = 6;
    numberobj_07_lastValue = 0;
    feedbacktilde_02_feedbackbuffer = nullptr;
    gen_02_history_2_value = 0;
    gen_02_history_1_value = 0;
    gen_02_change_2_prev = 0;
    gen_02_latch_4_value = 0;
    gen_02_latch_8_value = 0;
    gen_02_plusequals_12_value = 0;
    gen_02_counter_20_carry = 0;
    gen_02_counter_20_count = 0;
    gen_02_change_23_prev = 0;
    gen_02_latch_25_value = 0;
    gen_02_latch_27_value = 0;
    gen_02_plusequals_31_value = 0;
    gen_02_counter_40_carry = 0;
    gen_02_counter_40_count = 0;
    gen_02_sah_93_prev = 0;
    gen_02_sah_93_value = 0;
    gen_02_setupDone = false;
    numberobj_08_currentFormat = 6;
    numberobj_08_lastValue = 0;
    linetilde_03_currentValue = 0;
    numberobj_09_currentFormat = 6;
    numberobj_09_lastValue = 0;
    scopetilde_02_lastValue = 0;
    scopetilde_02_effectiveCount = 256;
    scopetilde_02_xsign = 1;
    scopetilde_02_ysign = 1;
    scopetilde_02_mode = 0;
    scopetilde_02_setupDone = false;
    numberobj_10_currentFormat = 6;
    numberobj_10_lastValue = 0;
    linetilde_04_currentValue = 0;
    numberobj_11_currentFormat = 6;
    numberobj_11_lastValue = 0;
    data_01_sizemode = 2;
    data_01_setupDone = false;
    data_02_sizemode = 2;
    data_02_setupDone = false;
    scopetilde_03_lastValue = 0;
    scopetilde_03_effectiveCount = 256;
    scopetilde_03_xsign = 1;
    scopetilde_03_ysign = 1;
    scopetilde_03_mode = 0;
    scopetilde_03_setupDone = false;
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

    number param_01_value;
    number param_02_value;
    number param_03_value;
    number param_04_value;
    number param_05_value;
    number param_06_value;
    number param_07_value;
    number param_08_value;
    number numberobj_01_value;
    number param_09_value;
    number toggle_01_value_number;
    number param_10_value;
    number p_01_target;
    number numberobj_02_value;
    number expr_04_in1;
    number expr_04_in2;
    number expr_04_out1;
    number p_02_target;
    number gen_01_in1;
    number gen_01_in2;
    number gen_01_KnbWindowCoefficient;
    number gen_01_KnbDelayTimeLeft;
    number gen_01_KnbSmooth;
    number gen_01_KnbDuty;
    number gen_01_KnbSmoothWindow;
    number dspexpr_03_in1;
    number dspexpr_04_in1;
    number dspexpr_04_in2;
    number xfade_tilde_05_pos;
    number dspexpr_05_in1;
    number dspexpr_05_in2;
    number numberobj_03_value;
    list linetilde_01_segments;
    number linetilde_01_time;
    number linetilde_01_keepramp;
    number numberobj_04_value;
    list scale_01_input;
    number scale_01_inlow;
    number scale_01_inhigh;
    number scale_01_outlow;
    number scale_01_outhigh;
    number scale_01_power;
    list scale_01_out;
    number param_11_value;
    number param_12_value;
    number numberobj_05_value;
    number expr_05_in1;
    number expr_05_in2;
    number expr_05_out1;
    list linetilde_02_segments;
    number linetilde_02_time;
    number linetilde_02_keepramp;
    number numberobj_06_value;
    number param_13_value;
    number numberobj_07_value;
    number expr_07_in1;
    number expr_07_in2;
    number expr_07_out1;
    number dspexpr_06_in1;
    number dspexpr_07_in1;
    number dspexpr_07_in2;
    number xfade_tilde_06_pos;
    number dspexpr_08_in1;
    number dspexpr_08_in2;
    number gen_02_in1;
    number gen_02_in2;
    number gen_02_KnbSmoothWindow;
    number gen_02_KnbSmooth;
    number gen_02_KnbDelayTimeRight;
    number gen_02_KnbDuty;
    number gen_02_KnbWindowCoefficient;
    number numberobj_08_value;
    number expr_08_in1;
    number expr_08_in2;
    number expr_08_out1;
    list linetilde_03_segments;
    number linetilde_03_time;
    number linetilde_03_keepramp;
    number numberobj_09_value;
    number numberobj_10_value;
    number expr_09_in1;
    number expr_09_in2;
    number expr_09_out1;
    list linetilde_04_segments;
    number linetilde_04_time;
    number linetilde_04_keepramp;
    number numberobj_11_value;
    number data_01_sizeout;
    number data_01_size;
    number data_01_sizems;
    number data_01_normalize;
    number data_01_channels;
    number data_02_sizeout;
    number data_02_size;
    number data_02_sizems;
    number data_02_normalize;
    number data_02_channels;
    number ctlin_01_input;
    number ctlin_01_controller;
    number ctlin_01_channel;
    number expr_01_in1;
    number expr_01_in2;
    number expr_01_out1;
    number ctlin_02_input;
    number ctlin_02_controller;
    number ctlin_02_channel;
    number expr_02_in1;
    number expr_02_in2;
    number expr_02_out1;
    number ctlin_03_input;
    number ctlin_03_controller;
    number ctlin_03_channel;
    number expr_03_in1;
    number expr_03_in2;
    number expr_03_out1;
    number ctlin_04_input;
    number ctlin_04_controller;
    number ctlin_04_channel;
    number expr_06_in1;
    number expr_06_in2;
    number expr_06_out1;
    MillisecondTime _currentTime;
    SampleIndex audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[19];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number param_01_lastValue;
    number param_02_lastValue;
    number param_03_lastValue;
    number param_04_lastValue;
    number param_05_lastValue;
    number param_06_lastValue;
    number param_07_lastValue;
    number scopetilde_01_lastValue;
    number scopetilde_01_effectiveCount;
    number scopetilde_01_xmonitorvalue;
    number scopetilde_01_ymonitorvalue;
    list scopetilde_01_monitorbuffer;
    number scopetilde_01_xsign;
    number scopetilde_01_ysign;
    Int scopetilde_01_mode;
    bool scopetilde_01_setupDone;
    number param_08_lastValue;
    Int numberobj_01_currentFormat;
    number numberobj_01_lastValue;
    number param_09_lastValue;
    number toggle_01_lastValue;
    number param_10_lastValue;
    Int numberobj_02_currentFormat;
    number numberobj_02_lastValue;
    number gen_01_history_2_value;
    number gen_01_history_1_value;
    Float32BufferRef gen_01_revdel;
    number gen_01_change_3_prev;
    number gen_01_latch_5_value;
    number gen_01_latch_9_value;
    number gen_01_plusequals_13_value;
    int gen_01_counter_20_carry;
    number gen_01_counter_20_count;
    number gen_01_change_23_prev;
    number gen_01_latch_25_value;
    number gen_01_latch_27_value;
    number gen_01_plusequals_31_value;
    int gen_01_counter_40_carry;
    number gen_01_counter_40_count;
    number gen_01_sah_93_prev;
    number gen_01_sah_93_value;
    bool gen_01_setupDone;
    signal feedbacktilde_01_feedbackbuffer;
    Int numberobj_03_currentFormat;
    number numberobj_03_lastValue;
    list linetilde_01_activeRamps;
    number linetilde_01_currentValue;
    Int numberobj_04_currentFormat;
    number numberobj_04_lastValue;
    number param_11_lastValue;
    number param_12_lastValue;
    Int numberobj_05_currentFormat;
    number numberobj_05_lastValue;
    list linetilde_02_activeRamps;
    number linetilde_02_currentValue;
    Int numberobj_06_currentFormat;
    number numberobj_06_lastValue;
    number param_13_lastValue;
    Int numberobj_07_currentFormat;
    number numberobj_07_lastValue;
    signal feedbacktilde_02_feedbackbuffer;
    number gen_02_history_2_value;
    number gen_02_history_1_value;
    Float32BufferRef gen_02_revdelright;
    number gen_02_change_2_prev;
    number gen_02_latch_4_value;
    number gen_02_latch_8_value;
    number gen_02_plusequals_12_value;
    int gen_02_counter_20_carry;
    number gen_02_counter_20_count;
    number gen_02_change_23_prev;
    number gen_02_latch_25_value;
    number gen_02_latch_27_value;
    number gen_02_plusequals_31_value;
    int gen_02_counter_40_carry;
    number gen_02_counter_40_count;
    number gen_02_sah_93_prev;
    number gen_02_sah_93_value;
    bool gen_02_setupDone;
    Int numberobj_08_currentFormat;
    number numberobj_08_lastValue;
    list linetilde_03_activeRamps;
    number linetilde_03_currentValue;
    Int numberobj_09_currentFormat;
    number numberobj_09_lastValue;
    number scopetilde_02_lastValue;
    number scopetilde_02_effectiveCount;
    number scopetilde_02_xmonitorvalue;
    number scopetilde_02_ymonitorvalue;
    list scopetilde_02_monitorbuffer;
    number scopetilde_02_xsign;
    number scopetilde_02_ysign;
    Int scopetilde_02_mode;
    bool scopetilde_02_setupDone;
    Int numberobj_10_currentFormat;
    number numberobj_10_lastValue;
    list linetilde_04_activeRamps;
    number linetilde_04_currentValue;
    Int numberobj_11_currentFormat;
    number numberobj_11_lastValue;
    Float32BufferRef data_01_buffer;
    Int data_01_sizemode;
    bool data_01_setupDone;
    Float32BufferRef data_02_buffer;
    Int data_02_sizemode;
    bool data_02_setupDone;
    number scopetilde_03_lastValue;
    number scopetilde_03_effectiveCount;
    number scopetilde_03_xmonitorvalue;
    number scopetilde_03_ymonitorvalue;
    list scopetilde_03_monitorbuffer;
    number scopetilde_03_xsign;
    number scopetilde_03_ysign;
    Int scopetilde_03_mode;
    bool scopetilde_03_setupDone;
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
    DataRef revdel;
    DataRef revdelright;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_855* p_01;
    RNBOSubpatcher_856* p_02;

};

PatcherInterface* createRnboReverseDelay()
{
    return new RnboReverseDelay();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr RnboReverseDelayFactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return createRnboReverseDelay;
}

} // end RNBO namespace

