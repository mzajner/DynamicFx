Processor 
Type SynthChain ID 
Draft 01 Bypassed Gain 	      �?Balance 	        VoiceLimit 	      P@KillFadeTime 	      4@IconColour 0 packageName  BuildVersion �  EditorStates BodyShown 0 Visible 1 Solo 0 Folded 1  ChildProcessors  Processor Type MidiProcessorChain ID Midi Processor Bypassed EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor Type ScriptProcessor ID Interface Bypassed Script �Content.makeFrontInterface(1400, 1009);


// =============================================================== Page Handling

// Get these lines by selecting all controls and choose "Create Script Definition for selection"
const var MainPageButton = Content.getComponent("MainPageButton");
const var APageButton = Content.getComponent("APageButton");
const var BPageButton = Content.getComponent("BPageButton");
const var CPageButton = Content.getComponent("CPageButton");
const var FXPageButton = Content.getComponent("FXPageButton");
const var ArpPageButton = Content.getComponent("ArpPageButton");
const var SettingsPageButton = Content.getComponent("SettingsPageButton");







const var BPage = Content.getComponent("BPage");
const var CPage = Content.getComponent("CPage");
const var FXPage = Content.getComponent("FXPage");
const var ArpPage = Content.getComponent("ArpPage");
const var SettingsPage = Content.getComponent("SettingsPage");
const var MainPage = Content.getComponent("MainPage");
const var APage = Content.getComponent("APage");


// Put them all in an array for better iterating.
const var pages = [MainPage, APage, BPage, CPage, FXPage, ArpPage, SettingsPage];

/** This function iterates the array, hides all pages and only shows the given page.
*
*   pageToShow is a reference to the control. Check the onControl callback to see what's going on.
*/
inline function handlePages(pageToShow)
{
    for(p in pages)
        p.set("visible", pageToShow == p);
}

// This page will be shown as default
// If you're working on another page, just pass this is temporarily
// so it doesn't switch back when compiling.
handlePages(MainPage);




// =============================================================== LAF Knobs



//Engine.loadFontAs("{PROJECT_FOLDER}oxygen.regular.ttf", 'OxygenRegular');
//Engine.loadFontAs("{PROJECT_FOLDER}oxygen.bold.ttf", 'OxygenBold');

const STARTX = 0;
const STARTY = 1;
const WIDTH = 2;
const HEIGHT = 3;

const CONST_SurfaceGradientTop = 0xFF000000;
const CONST_SurfaceGradientBottom = 0xFF484B52;
const CONST_BorderColour = 0xFF939399;
const CONST_DisabledIndicatorColour = 0xff5a5b5c;
const CONST_DisabledSurfaceColour = 0xFF191a1d;
const CONST_DisabledButtonTextColour = 0xFF94949a;

const CONST_SmallButtonFontSize = 15;


////////////////// KNOB LOOK AND FEEL //////////////////

// Create a look and feel function.
const LAF_StandardKnob = Content.createLocalLookAndFeel();

// Register and define the drawing function for the knob.
LAF_StandardKnob.registerFunction("drawRotarySlider", function(Style,Widget)
{
	// Get the area of the widget (not just the knob).
	var Area = Widget.area;
	var KnobHeight = Area[HEIGHT];
	var KnobWidth = Area[HEIGHT];
	
	// Get the knob's circumference.
	var KnobSurfaceArea = [12, 12, Area [HEIGHT]-24, Area[HEIGHT]-24];

	// Draw the knob's surface.
	Style.setGradientFill([Widget.itemColour1, Area [HEIGHT]/2, 0, Widget.itemColour2, Area [HEIGHT]/2, Area[HEIGHT]]);
	Style.fillEllipse(KnobSurfaceArea);
 
	// Draw the knob's label.
	var LabelOffset = Area[HEIGHT];
	Style.setColour(Widget.textColour);
	Style.setFont("Oxygen Bold", 14); 
	Style.drawAlignedText(Widget.text, [Area[STARTX] + LabelOffset, Area[HEIGHT]-Area [HEIGHT] -8, Area [HEIGHT]+LabelOffset, Area[HEIGHT]], "left");    
	Style.setFont("Oxygen Regular", 14); 
	Style.setColour(0XFF838387);
	var KnobValue = Widget.value;
	var ConcatenatedValue = Engine.doubleToString(KnobValue,2) +  Widget.suffix;
	Style.drawAlignedText(ConcatenatedValue, [Area[STARTX] + LabelOffset, Area[HEIGHT]-Area [HEIGHT] +6, Area [HEIGHT]+LabelOffset, Area[HEIGHT]], "left");    
   
    // Draw the arc, which is the value indicator circle around the knob.
    var K = Content.createPath();
	var ValueRange = Widget.max - Widget.min;
    var startOffset = 2.4;
    var arcThickness = 0.02;
    var arcWidth = 1.0 - 2.0 * arcThickness;
	var endOffset = -startOffset + 2.0 * startOffset * Widget.valueNormalized;
    var val = "";
    var ArcOffset = 0.1;

	// Check if this is a centred knob.
	if ( (Widget.min < 0) && (Widget.max > 0) ) { startOffset = 0.08; }

	K.addArc([arcThickness / 2 + ArcOffset, arcThickness / 2 + ArcOffset, arcWidth + arcThickness - ArcOffset*2, arcWidth + arcThickness - ArcOffset*2], -startOffset - 0.08, endOffset + 0.08);   
    var pathArea = K.getBounds(Widget.area[HEIGHT]);  
	
	// Set the arc's standard colour.
	Style.setColour (Widget.bgColour);

	// Draw the arc.
    Style.drawPath(K, pathArea, Widget.area[WIDTH] * arcThickness);

	// Change the colour if there's a mouse-over or the knob is being turned.
    if (Widget.hover || Widget.clicked) {
	    Style.setColour(0xFFC1C1C2);	
	    Style.drawPath(K, pathArea, Widget.area[WIDTH] * arcThickness );
    }
    
    // Draw the value indicator.
    Style.rotate(endOffset, [Widget.area[HEIGHT] / 2, Widget.area[HEIGHT] / 2]);
    Style.setColour(Widget.textColour);
    Style.fillRoundedRectangle([Widget.area[HEIGHT] / 2 - Widget.area[HEIGHT] * -0.01, Widget.area[HEIGHT] / 2 - Widget.area[HEIGHT] * 0.295, Widget.area[HEIGHT]  * 0.03, Widget.area[HEIGHT] * 0.03], 3);
});

////////////////// KNOB DECLARATION //////////////////

// Define the callback function for when the knob is turned.
const var MasterVolKnob = Content.getComponent("MasterVolKnob");



// Assign the look and feel to the knob.
MasterVolKnob.setLocalLookAndFeel(LAF_StandardKnob);function onNoteOn()
{
	
}
 function onNoteOff()
{
	
}
 function onController()
{
	
}
 function onTimer()
{
	
}
 function onControl(number, value)
{
    /*  This callback just calls the page handling function with the respective page.
    *   The other custom callbacks are implemented in the onInit script.
    */
	switch(number)
    {
        case MainPageButton: handlePages(MainPage); break;
        case APageButton: handlePages(APage); break;
        case BPageButton: handlePages(BPage); break;
        case CPageButton: handlePages(CPage); break;
        case FXPageButton: handlePages(FXPage); break;
        case ArpPageButton: handlePages(ArpPage); break;
        case SettingsPageButton: handlePages(SettingsPage); break;

    }
} EditorStates BodyShown 1 Visible 1 Solo 0 contentShown 1 onInitOpen 1  ChildProcessors   Content  Control type ScriptButton id MainPageButton value 	         Control type ScriptButton id APageButton value 	         Control type ScriptButton id BPageButton value 	         Control type ScriptButton id CPageButton value 	         Control type ScriptButton id FXPageButton value 	         Control type ScriptButton id ArpPageButton value 	         Control type ScriptButton id SettingsPageButton value 	         Control type ScriptSlider id MasterVolKnob value 	   �=
�? UIData  ContentProperties DeviceType 	Desktop Component type ScriptImage id Image1 x 	        y 	        fileName +/Users/kameronclark/Desktop/Skin_Idea.png width 	     ��@height 	     ��@ Component type ScriptButton id MainPageButton x 	     ��@y 	      4@isMomentary 1  Component type ScriptButton id APageButton x 	     h�@y 	     �V@isMomentary 1 width 	      I@height 	      D@ Component type ScriptButton id BPageButton x 	     X�@y 	     �V@width 	      >@height 	      >@isMomentary 1  Component type ScriptButton id CPageButton x 	     ��@y 	     �V@width 	      >@height 	      D@isMomentary 1  Component type ScriptButton id FXPageButton x 	     ��@y 	     �V@width 	      >@height 	      D@isMomentary 1  Component type ScriptButton id ArpPageButton x 	     ��@y 	     �V@width 	      >@height 	      D@isMomentary 1  Component type ScriptButton id SettingsPageButton x 	     �@y 	     �V@isMomentary 1 width 	      >@height 	      D@ Component 
type ScriptPanel id 
MainPage x 	        y 	     @`@width 	     ��@height 	     �@bgColour 
16777215 itemColour 0 itemColour2 0 textColour 
16777215 Component type ScriptPanel id LayerAPanel x 	      >@y 	     �Z@width 	     �z@height 	     Ё@itemColour2 855309 itemColour 855309 bgColour 
16777215 textColour 
16777215 parentComponent 
MainPage  Component 
type ScriptPanel id LayerBPanel x 	     P~@y 	      [@width 	     �z@height 	     Ё@itemColour 0 itemColour2 0 textColour 
16777215 parentComponent 
MainPage  Component type ScriptPanel id LayerCPanel x 	     P�@y 	     @[@parentComponent 
MainPage width 	     �z@height 	     Ё@textColour 
16777215 itemColour2 0 itemColour 0 bgColour 
16777215  Component type ScriptPanel id APage x 	      �y 	     @`@width 	      �@height 	     �@textColour 
16777215 itemColour2 4278848010 itemColour 4278848010 bgColour 
16777215 visible  Component 
type ScriptPanel id BPage x 	      �y 	     @`@width 	      �@height 	     �@textColour 
16777215 itemColour2 4278848010 itemColour 4278848010 visible  Component type ScriptPanel id CPage x 	      $�y 	     @`@width 	     0�@height 	     �@itemColour 4278848010 textColour 
16777215 bgColour 
16777215 itemColour2 4278848010 visible  Component type ScriptPanel id FXPage x 	      >�y 	     @`@width 	     p�@height 	     �@itemColour 4278848010 itemColour2 4278848010 textColour 
16777215 bgColour 
16777215 visible  Component 
type ScriptPanel id 	ArpPage x 	      >�y 	     @`@width 	     �@height 	     �@itemColour 4278848010 textColour 
16777215 itemColour2 4278848010 visible  Component type ScriptPanel id SettingsPage x 	      >�y 	     @`@width 	     ��@height 	     �@itemColour 4278848010 itemColour2 4278848010 textColour 
16777215 bgColour 
16777215 visible  Component 	type ScriptSlider id MasterVolKnob x 	      I@y 	     ��@width 	      i@height 	      T@bgColour 	����    itemColour 	   �    itemColour2 	   �     Processor Type ModulatorChain ID GainModulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID PitchModulation Bypassed Intensity 	        EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type EffectChain ID FX Bypassed EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type StreamingSampler ID 
Sampler1 Bypassed Gain 	      �?Balance 	        VoiceLimit 	      p@KillFadeTime 	      4@IconColour 0 PreloadSize 	      �@BufferSize 	      �@VoiceAmount 	      p@SamplerRepeatMode 	      @RRGroupAmount 	      �?PitchTracking 	      �?OneShot 	        CrossfadeGroups 	        Purged 	        Reversed 	        NumChannels    UseStaticMatrix 	        Group0Table  Group1Table  Group2Table  Group3Table  Group4Table  Group5Table  Group6Table  Group7Table  SampleMapID Bass - Classic Retro EditorStates BodyShown 1 Visible 1 Solo 0 MapPanelShown 1 BigSampleMap 1 Folded 1  ChildProcessors  Processor Type MidiProcessorChain ID Midi Processor Bypassed EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors   Processor Type ModulatorChain ID GainModulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor Type AHDSR ID AHDSR Envelope1 Bypassed Monophonic 	        Retrigger 	      �?Intensity 	      �?AttackCurve 	        DecayCurve 	        Attack 	        AttackLevel 	        Hold 	     ��@Decay 	    �!�@Sustain 	        Release 	      _@EcoMode 	      �?EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type ModulatorChain ID Attack Time Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors   Processor Type ModulatorChain ID Attack Level Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors   Processor Type ModulatorChain ID Decay Time Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors   Processor Type ModulatorChain ID Sustain Level Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors   Processor Type ModulatorChain ID Release Time Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors   Processor Type ModulatorChain ID PitchModulation Bypassed Intensity 	        EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors   Processor Type EffectChain ID FX Bypassed EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors   Processor Type ModulatorChain ID Sample Start Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors   Processor Type ModulatorChain ID Group Fade Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors   RoutingMatrix NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ���� channels  channelData enabled level 	        suffix   RoutingMatrix NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ���� macro_controls  macro name 	Macro 1 value 0.0 midi_cc -1  macro name 	Macro 2 value 0.0 midi_cc -1  macro name 	Macro 3 value 0.0 midi_cc -1  macro name 	Macro 4 value 0.0 midi_cc -1  macro name 	Macro 5 value 0.0 midi_cc -1  macro name 	Macro 6 value 0.0 midi_cc -1  macro name 	Macro 7 value 0.0 midi_cc -1  macro name 	Macro 8 value 0.0 midi_cc -1  MidiAutomation   MPEData Enabled  