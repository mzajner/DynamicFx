Content.makeFrontInterface(939, 676);

include("LookAndFeel.js");
include("PresetBrowser.js");

// =============================================================== Page Handling

// Get these lines by selecting all controls and choose "Create Script Definition for selection"
const var MainPageButton = Content.getComponent("MainPageButton");
const var APageButton = Content.getComponent("APageButton");
const var BPageButton = Content.getComponent("BPageButton");
const var CPageButton = Content.getComponent("CPageButton");
const var FXPageButton = Content.getComponent("FXPageButton");
const var ArpPageButton = Content.getComponent("ArpPageButton");
const var SettingsPageButton = Content.getComponent("SettingsPageButton");






const var MainPage = Content.getComponent("MainPage");
const var APage = Content.getComponent("APage");
const var BPage = Content.getComponent("BPage");
const var CPage = Content.getComponent("CPage");
const var FXPage = Content.getComponent("FXPage");
const var ArpPage = Content.getComponent("ArpPage");
const var StgPage = Content.getComponent("StgPage");







// Put them all in an array for better iterating.
const var pages = [APage, BPage, CPage, FXPage, ArpPage, MainPage];

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






////////////////// COMBO BOX MAPS //////////////////



//Sampler
const var Sampler1 = Synth.getChildSynth("Sampler1");
const var Sampler2 = Synth.getSampler("Sampler2");
const var Sampler3 = Synth.getSampler("Sampler3");
const var Sampler4 = Synth.getSampler("Sampler4");
const var Sampler5 = Synth.getSampler("Sampler5");

//Sample Maps Array
const var sampleMaps = Sampler.getSampleMapList(); 

//Combo Box - Layer A

const var ComboBox1 = Content.getComponent("ComboBox1");

ComboBox1.set("items", sampleMaps.join("\n"));


inline function onComboBox1Control(component, value)
{
	Sampler1.asSampler().loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("ComboBox1").setControlCallback(onComboBox1Control);

//Combo Box - Layer B

const var ComboBox2 = Content.getComponent("ComboBox2");

//ComboBox2.set("items", sampleMaps.join("\n"));


inline function onComboBox2Control(component, value)
{
	Sampler2.loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("ComboBox2").setControlCallback(onComboBox2Control);

//Combo Box - Layer C

const var ComboBox3 = Content.getComponent("ComboBox3");

//ComboBox3.set("items", sampleMaps.join("\n"));


inline function onComboBox3Control(component, value)
{
	Sampler3.loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("ComboBox3").setControlCallback(onComboBox3Control);


//Combo Box - Textures

const var ComboBox4 = Content.getComponent("ComboBox4");

ComboBox4.set("items", sampleMaps.join("\n"));


inline function onComboBox4Control(component, value)
{
	Sampler5.loadSampleMap(sampleMaps[value-1]);
};


Content.getComponent("ComboBox4").setControlCallback(onComboBox4Control);




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
case ArpPageButton: handlePages(ArpPage); break;
case MainPageButton: handlePages(MainPage); break;


    }
}