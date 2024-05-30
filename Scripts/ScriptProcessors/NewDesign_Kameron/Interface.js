Content.makeFrontInterface(939, 706);


include("Filters.js");
include("LookAndFeel.js");
include("PresetBrowser.js");
//include("CopyProtection.js");



//Release Trigger Edit Panel


const var TriggerEdit = Content.getComponent("TriggerEdit");




inline function onTriggerEditControl(component, value)
{
    if (value)
        TrigEditPanel.set("visible", true);

};

Content.getComponent("TriggerEdit").setControlCallback(onTriggerEditControl);

const var TrigEditPanel = Content.getComponent("TrigEditPanel");




const var TrigClose = Content.getComponent("TrigClose");




inline function onTrigCloseControl(component, value)
{
    if (value)
        TrigEditPanel.set("visible", false);
};

Content.getComponent("TrigClose").setControlCallback(onTrigCloseControl);



//Noise Edit Panel

const var NoiseEdit = Content.getComponent("NoiseEdit");


inline function onNoiseEditControl(component, value)
{
    if (value)
        NoiseEditPanel.set("visible", true);

};

Content.getComponent("NoiseEdit").setControlCallback(onNoiseEditControl);
const var NoiseEditPanel = Content.getComponent("NoiseEditPanel");



const var CloseEdit = Content.getComponent("CloseEdit");




inline function onCloseEditControl(component, value)
{
    if (value)
        NoiseEditPanel.set("visible", false);
};

Content.getComponent("CloseEdit").setControlCallback(onCloseEditControl);




// =============================================================== Page Handling

// Get these lines by selecting all controls and choose "Create Script Definition for selection"

const var APageButton = Content.getComponent("APageButton");
const var BPageButton = Content.getComponent("BPageButton");
const var CPageButton = Content.getComponent("CPageButton");
const var FXPageButton = Content.getComponent("FXPageButton");
const var SeqPageButton = Content.getComponent("SeqPageButton");
const var SettingsPageButton = Content.getComponent("SettingsPageButton");
const var MainPageButton = Content.getComponent("MainPageButton");







const var APage = Content.getComponent("APage");
const var BPage = Content.getComponent("BPage");
const var CPage = Content.getComponent("CPage");
const var FXPage = Content.getComponent("FXPage");
const var SeqPage = Content.getComponent("SeqPage");
const var StgPage = Content.getComponent("StgPage");
const var MainPage = Content.getComponent("MainPage");







// Put them all in an array for better iterating.
const var pages = [APage, BPage, CPage, FXPage, SeqPage, StgPage, MainPage];

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



//RESIZE CODE//

namespace ZoomHandler
{
	const var MIN_ZOOM = 0.85;
	const var MAX_ZOOM = 6.0;
	const var ZOOM_STEP = 0.1;
	const var INTERFACE_WIDTH = 390;
	const var INTERFACE_HEIGHT = 605;

	const var ZoomPanel = Content.getComponent("ZoomPanel");
	
	const var draggerData = [ 110,109,143,130,218,67,147,216,145,66,108,147,216,145,66,143,130,218,67,108,0,0,0,0,143,130,218,67,108,143,130,218,67,0,0,0,0,108,143,130,218,67,147,216,145,66,99,109,143,130,218,67,139,140,96,67,108,139,140,96,67,143,130,218,67,108,66,160,23,67,143,
	130,218,67,108,143,130,218,67,66,160,23,67,108,143,130,218,67,139,140,96,67,99,109,143,130,218,67,102,22,188,67,108,102,22,188,67,143,130,218,67,108,66,160,151,67,143,130,218,67,108,143,130,218,67,66,160,151,67,108,143,130,218,67,102,22,188,67,99,101,
	0,0 ];
	
	
	const var draggerPath = Content.createPath();
	
	
	draggerPath.loadFromData(draggerData);
	
	ZoomPanel.setPaintRoutine(function(g)
	{
		g.setColour(Colours.withAlpha(Colours.white, (this.data.hover && this.data.allowDrag) ? 0.8 : 0.2));
		g.fillPath(draggerPath, [8, 4, 14, 14]);
	});
	
	inline function allowZoom(panel, on)
	{
		panel.data.allowDrag = on;
		panel.setMouseCursor(on ?"BottomRightCornerResizeCursor" : "NormalCursor", Colours.white, [0, 0]);
		panel.repaint();
	}
	
	allowZoom(ZoomPanel, true);
	
	ZoomPanel.setMouseCallback(function(event)
	{
		this.data.hover = event.hover;
		
		if(event.clicked)
		{
			this.data.zoomStart = Settings.getZoomLevel();
		}
		if(event.mouseUp)
		{
			return;
		}
	
		if(event.drag)
		{
			if(!this.data.allowDrag)
				return;
	
			var diagonal = Math.sqrt(INTERFACE_WIDTH*INTERFACE_WIDTH + INTERFACE_HEIGHT*INTERFACE_HEIGHT);
			var currentZoom = Settings.getZoomLevel();
			var dragPixel = 0;
			
			if(event.dragX > event.dragY)
				dragPixel = (event.dragX * currentZoom) / INTERFACE_WIDTH;
			else
				dragPixel = (event.dragY * currentZoom) / INTERFACE_HEIGHT;
			
			
			var maxScaleFactor = Content.getScreenBounds(false)[3] / INTERFACE_HEIGHT;
			var diagonalDrag = this.data.zoomStart + dragPixel;
			
			diagonalDrag += (ZOOM_STEP / 2);
			
			diagonalDrag = Math.min(diagonalDrag, maxScaleFactor);
			
			diagonalDrag -= Math.fmod(diagonalDrag, ZOOM_STEP);
			diagonalDrag = Math.range(diagonalDrag, MIN_ZOOM, MAX_ZOOM);
			
			var zoomToUse = diagonalDrag;
	
			if(currentZoom != zoomToUse)
			{
				Settings.setZoomLevel(zoomToUse);
			}
		}
		
		this.repaint();
	});
}






////////////////// COMBO BOXES //////


//Sampler
const var Sampler1 = Synth.getChildSynth("Sampler1");
const var Sampler2 = Synth.getSampler("Sampler2");
const var Sampler3 = Synth.getSampler("Sampler3");
const var Sampler4 = Synth.getSampler("Sampler4");
const var Sampler5 = Synth.getSampler("Sampler5");
const var ReleaseTrig = Synth.getSampler("ReleaseTrig");


//Sample Maps Array
const var sampleMaps = Sampler.getSampleMapList(); 

//Combo Box - Textures - Noise

const var SelectNoise = Content.getComponent("SelectNoise");

//SelectNoise.set("items", sampleMaps.join("\n"));


inline function onSelectNoiseControl(component, value)
{
	Sampler5.loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("SelectNoise").setControlCallback(onSelectNoiseControl);

//Combo Box - Release Trigger 

const var ReleaseTrigSmpl = Content.getComponent("ReleaseTrigSmpl");


//ReleaseTrigSmpl.set("items", sampleMaps.join("\n"));


inline function onReleaseTrigSmplControl(component, value)
{
	ReleaseTrig.loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("ReleaseTrigSmpl").setControlCallback(onReleaseTrigSmplControl);


//// COMBO BOX LAYERS A,B,C

const var Left_Random_Value  = Content.getComponent("Left_Random_Value");
const var Right_Random_Value = Content.getComponent("Right_Random_Value");
const var C_Random_Value = Content.getComponent("C_Random_Value");
const var Prev_Cpanel = Content.getComponent("Prev_Cpanel");
const var Next_Cpanel = Content.getComponent("Next_Cpanel");


//// ComboBox1 - Layer A

const var ComboBox1 = Content.getComponent("ComboBox1");

//ComboBox1.set("items", sampleMaps.join("\n"));

inline function onComboBox1Control(component, value)
{
    Left_Random_Value.loadSampleMap(sampleMaps[value-1]);
    	Sampler1.asSampler().loadSampleMap(sampleMaps[value-1]);
};
ComboBox1.setControlCallback(onComboBox1Control);

Content.getComponent("ComboBox1").setControlCallback(onComboBox1Control);



// ComboBox2 - Layer B
const var ComboBox2 = Content.getComponent("ComboBox2");

//ComboBox2.set("items", sampleMaps.join("\n"));

inline function onComboBox2Control(component, value)
{
    Right_Random_Value.loadSampleMap(sampleMaps[value-1]);
    Sampler2.loadSampleMap(sampleMaps[value-1]);
};
ComboBox2.setControlCallback(onComboBox2Control);

Content.getComponent("ComboBox2").setControlCallback(onComboBox2Control);



// ComboBox3 - Layer C
const var ComboBox3 = Content.getComponent("ComboBox3");

//ComboBox3.set("items", sampleMaps.join("\n"));

inline function onComboBox3Control(component, value)
{
	C_Random_Value.sloadSampleMap(sampleMaps[value-1]);
	Sampler3.loadSampleMap(sampleMaps[value-1]);
};
ComboBox3.setControlCallback(onComboBox3Control);

Content.getComponent("ComboBox3").setControlCallback(onComboBox3Control);



// COMBO BOX PREV & NEXT BUTTONS

// Prev LEFT - ComboBox 1 Controls
inline function onPrev_LeftControl(component, value)
{
    if (value)
    {
	    ComboBox1.setValue(ComboBox1.getValue() == 1 ? ComboBox1.get("max") : ComboBox1.getValue() - 1);
	    ComboBox1.changed();
    }
};
Content.getComponent("Prev_Left").setControlCallback(onPrev_LeftControl);

// Next LEFT - ComboBox 1 Controls
inline function onNext_Left1Control(component, value)
{
    if (value)
    {
	    ComboBox1.setValue(ComboBox1.getValue() == ComboBox1.get("max") ? 1 : ComboBox1.getValue() + 1);
	    ComboBox1.changed();
    }
};
Content.getComponent("Next_Left1").setControlCallback(onNext_Left1Control);


// Prev RIGHT - ComboBox 2 Controls
inline function onPrev_RightControl(component, value)
{
    if (value)
    {
	    ComboBox2.setValue(ComboBox2.getValue() == 1 ? ComboBox2.get("max") : ComboBox2.getValue() - 1);
	    ComboBox2.changed();
    }
};
Content.getComponent("Prev_Right").setControlCallback(onPrev_RightControl);

// Next RIGHT - ComboBox 2 Controls
inline function onNext_RightControl(component, value)
{
    if (value)
    {
	    ComboBox2.setValue(ComboBox2.getValue() == ComboBox2.get("max") ? 1 : ComboBox2.getValue() + 1);
	    ComboBox2.changed();
    }
};
Content.getComponent("Next_Right").setControlCallback(onNext_RightControl);


// Prev C - ComboBox 3 Controls
inline function onPrev_CpanelControl(component, value)
{
    if (value)
    {
	    ComboBox3.setValue(ComboBox3.getValue() == 1 ? ComboBox3.get("max") : ComboBox3.getValue() - 1);
	    ComboBox3.changed();
    }
};
Content.getComponent("Prev_Cpanel").setControlCallback(onPrev_CpanelControl);




// Next C - ComboBox 3 Controls
inline function onNext_CpanelControl(component, value)
{
    if (value)
    {
	    ComboBox3.setValue(ComboBox3.getValue() == ComboBox3.get("max") ? 1 : ComboBox3.getValue() + 1);
	    ComboBox3.changed();
    }
};
Content.getComponent("Next_Cpanel").setControlCallback(onNext_CpanelControl);



///LAF COMBO BOX

Engine.loadFontAs("{PROJECT_FOLDER}Fonts/MontserratExtraBold.ttf", "MontserratExtraBold");

const laf = Content.createLocalLookAndFeel();

laf.registerFunction("drawComboBox", function(g, obj)
{	
	var a = obj.area;
	
	g.setColour(obj.itemColour1);
	g.drawRect(obj.area, 1.0);
	g.fillTriangle([a[2] - 20, 12, 13, 6], Math.PI);
	
	g.setColour(obj.textColour);
	g.setFont("MontserratExtraBold", 18);   
	g.drawAlignedText(obj.text, [7, a[1], a[2], a[3]], "left");  			
});



ComboBox1.setLocalLookAndFeel(laf);
ComboBox2.setLocalLookAndFeel(laf);
ComboBox3.setLocalLookAndFeel(laf);


/// LAF ON / OFF BUTTON


const LAF_SliderButton = Content.createLocalLookAndFeel();

LAF_SliderButton.registerFunction("drawToggleButton", function(g, obj) {
	// Create descriptive variables name for the widget's properties.
	var widgetStartX = widget.area[0];
	var widgetStartY = widget.area[1];
	var widgetWidth = obj.area[2];
	var widgetHeight = obj.area[3];

	// Set customisable LAF variables.
	var widgetCornerSize = 3;
	var widgetBorderWidth = 1;
	var handleWidth = widgetWidth/6;
	var handleLength = widgetHeight;
	
	// Calculate stuff.
	var scalingFactor = (widgetWidth - handleWidth) / widgetWidth;
	var widgetDisplayValue = obj.value * scalingFactor;
	
	var buttonStatesText = [];
	var textString = obj.text;

	if (obj.value) {
		
		var wellColour = obj.itemColour1;
		var buttonStartX = widgetWidth - handleLength;
		var textStartX = 0;
		var buttonValueText = (obj.text).split(".")[0];

	} else {
		
		var wellColour = obj.itemColour2;
		var buttonStartX = 0;
		var textStartX = handleLength;
		var buttonValueText = (obj.text).split(".")[1];
	}
	
	// Draw background
	g.setColour (wellColour);
	g.fillRoundedRectangle(obj.area, widgetHeight/2);
	
	// Draw button
	g.setColour (obj.bgColour);
	g.fillRoundedRectangle([buttonStartX, 0, handleLength, widgetHeight], widgetHeight/2);
	
	// Draw Text
	g.setColour(obj.textColour);
	
	// Set the font.
	g.setFont("Arial", widgetHeight-8); 
	
	g.drawAlignedText(buttonValueText, [ textStartX, 0, widgetWidth-handleLength, widgetHeight], "centred");
});



const var AHPPower = Content.getComponent("AHPPower");
const var LayerBLPButton = Content.getComponent("LayerBLPButton");
const var LayerCLPButton = Content.getComponent("LayerCLPButton");

const var LayerALPButton = Content.getComponent("LayerALPButton");
const var OnOffA = Content.getComponent("OnOffA");
const var OnOffB = Content.getComponent("OnOffB");
const var OnOffC = Content.getComponent("OnOffC");
const var TextureOnOff = Content.getComponent("TextureOnOff");
const var RelTriButton = Content.getComponent("RelTriButton");




RelTriButton.setLocalLookAndFeel(LAF_SliderButton);
LayerCLPButton.setLocalLookAndFeel(LAF_SliderButton);

LayerBLPButton.setLocalLookAndFeel(LAF_SliderButton);

LayerALPButton.setLocalLookAndFeel(LAF_SliderButton);
TextureOnOff.setLocalLookAndFeel(LAF_SliderButton);
OnOffA.setLocalLookAndFeel(LAF_SliderButton);
OnOffB.setLocalLookAndFeel(LAF_SliderButton);
OnOffC.setLocalLookAndFeel(LAF_SliderButton);
function onNoteOn()
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
        case APageButton: handlePages(APage); break;
        case BPageButton: handlePages(BPage); break;
        case CPageButton: handlePages(CPage); break;
        case FXPageButton: handlePages(FXPage); break;
case SeqPageButton: handlePages(SeqPage); break;
case SettingsPageButton: handlePages(StgPage); break;
case MainPageButton: handlePages(MainPage); break;


    }
}