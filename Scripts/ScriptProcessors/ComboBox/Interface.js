Content.makeFrontInterface(1400, 1009);


//RESIZE CODE//

const var Knob1 = Content.getComponent("Knob1");

inline function onKnob1Control(component, value)
{
	Engine.setZoomLevel(value);
};

Content.getComponent("Knob1").setControlCallback(onKnob1Control);

const var Panel1 = Content.getComponent("Panel1");
Panel1.setControlCallback(onPanel1Control);

inline function onPanel1Control(component, value)
{
    Knob1.setValue(value);
    Knob1.changed();
}

Panel1.setPaintRoutine(function(g)
{
    g.fillAll(Colours.black);
    
    if (this.data.inTheZone)
    {
        g.setColour(Colours.white);
        g.fillTriangle([this.getWidth() - 30, this.getHeight() - 30, 30, 30], Math.PI / 10);
    }
});

Panel1.setMouseCallback(function(event) {
   
    if (event.x >= this.getWidth() - 30 && event.y >= this.getHeight() - 30)
    {        
        if (event.clicked)
        {
            this.data.resizing = true;
            this.data.width = this.getWidth();
            this.data.height = this.getHeight();
        }
        
        this.data.inTheZone = true;
    }
    else
    {
        this.data.inTheZone = false;
    }

    if (event.mouseUp)
        this.data.resizing = false;
    
    if (this.data.resizing)
    {
        var p1 = 1 + 1 / this.data.width * event.dragX;
        var p2 = 1 + 1 / this.data.height * event.dragY;
        this.setValue(Math.range(p1 * p2, 0, 1));
        this.changed();
    }
    
    this.repaint();
});


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



//Engine.loadFontAs("{PROJECT_FOLDER}BebasNeue", 'BebasNeue');
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

const CONST_SmallButtonFontSize = 12;


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
	Style.setFont("Oxygen Bold", 12); 
	Style.drawAlignedText(Widget.text, [Area[STARTX] + LabelOffset, Area[HEIGHT]-Area [HEIGHT] -8, Area [HEIGHT]+LabelOffset, Area[HEIGHT]], "left");    
	Style.setFont("Oxygen Regular", 10); 
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
MasterVolKnob.setLocalLookAndFeel(LAF_StandardKnob);





////////////////// COMBO BOX MAPS //////////////////



//Sampler
const var Sampler1 = Synth.getChildSynth("Sampler1");
const var Sampler2 = Synth.getSampler("Sampler2");
const var Sampler3 = Synth.getSampler("Sampler3");
const var Sampler4 = Synth.getSampler("Sampler4");

//Sample Maps Array
const var sampleMaps = Sampler.getSampleMapList(); 

//Combo Box - Layer A

const var ComboBox1 = Content.getComponent("ComboBox1");

//ComboBox1.set("items", sampleMaps.join("\n"));


inline function onComboBox1Control(component, value)
{
	Sampler1.asSampler().loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("ComboBox1").setControlCallback(onComboBox1Control);

//Combo Box - Layer B

const var ComboBox2 = Content.getComponent("ComboBox2");

ComboBox2.set("items", sampleMaps.join("\n"));


inline function onComboBox2Control(component, value)
{
	Sampler2.loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("ComboBox2").setControlCallback(onComboBox2Control);

//Combo Box - Layer C

const var ComboBox3 = Content.getComponent("ComboBox3");

ComboBox3.set("items", sampleMaps.join("\n"));


inline function onComboBox3Control(component, value)
{
	Sampler3.loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("ComboBox3").setControlCallback(onComboBox3Control);



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
	g.setFont("MontserratExtraBold", 30);   
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
        case MainPageButton: handlePages(MainPage); break;
        case APageButton: handlePages(APage); break;
        case BPageButton: handlePages(BPage); break;
        case CPageButton: handlePages(CPage); break;
        case FXPageButton: handlePages(FXPage); break;
        case ArpPageButton: handlePages(ArpPage); break;
        case SettingsPageButton: handlePages(SettingsPage); break;

    }
}