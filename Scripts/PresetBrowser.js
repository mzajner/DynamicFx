//////////////// BEGINING OF THE PRESET BROWSER WINDOW //////////////////////////


const var PRESET_Bar = Content.addPanel("PRESET_Bar",315,30);

Content.setPropertiesFromJSON("PRESET_Bar", {
    "width": 330,
    "height": 35,
    "borderSize": 1,
    "visible": true,
    "borderRadius": 10,
});






const var PRESET_Opener = Content.addButton("PRESET_Opener", 0, 0);

Content.setPropertiesFromJSON("PRESET_Opener", {
    "height": 30,
    "width": 280,
    "text": "PRESET BROWSER",
    "parentComponent": "PRESET_Bar",
    "x": 0,
    "y": 2,
    "isMomentary": true,
    "bgColour": 00333333,
    "itemColour": 00333333,
    "itemColour2": 00333333
});

inline function onPRESET_OpenerControl(component, value)
{
    if (value)
        PRESET_Container.set("visible", true);

};

Content.getComponent("PRESET_Opener").setControlCallback(onPRESET_OpenerControl);







const var PRESET_Container = Content.addPanel("PRESET_Container");

Content.setPropertiesFromJSON("PRESET_Container", {

    "borderSize": 1,
    "visible": false,
    "borderRadius": 0,
    "x": 10,
    "y": 100,
});





const var PRESET_Closer = Content.addButton("PRESET_Closer", 850, 8);



inline function onPRESET_CloserControl(component, value)
{
    if (value)
        PRESET_Container.set("visible", false);
};

Content.getComponent("PRESET_Closer").setControlCallback(onPRESET_CloserControl);

















namespace UserPresetWidgets
{
	/** Creates a arrow button that cycles through the current category. */
	inline function createPresetButton(name, x, y, up)
	{
		local widget = Content.addPanel(name, x, y);
    
		Content.setPropertiesFromJSON(name, {
		"width": 15,
		"height": 20,
		"saveInPreset": false,
		"tooltip": up ? "Load next user preset" : "Load previous user preset",
        "parentComponent": "PRESET_Bar",
		"allowCallbacks": "Clicks & Hover"
		});
    
		widget.data.up = up;
    
		widget.setPaintRoutine(function(g)
		{
			g.setColour(this.data.hover ? 0x20FFFFFF : 0x28FFFFFF);
			g.fillTriangle([0, 0, this.getWidth(), this.getHeight()], this.data.up ? Math.PI/2 : 1.5 * Math.PI);
		});
    
		widget.setMouseCallback(function(event)
		{
			this.data.hover = event.hover;
    	
			if(event.clicked)
			{
				if(this.data.up)
					Engine.loadNextUserPreset(true);
				else
					Engine.loadPreviousUserPreset(true);		
			}
    	
			this.repaint();
		});
		return widget;
	};

	/** Creates a Label that shows the current User Preset.
	*
	*	You can click on it and it will open up a popup with the preset browser.
	*
	*	Customization: Use the itemColour property of the Panel to set the
	*	Preset Browser Colour.
	*/
	inline function createPresetDisplay(name, x, y)
	{
		local widget = Content.addPanel(name, x, y);
    
		Content.setPropertiesFromJSON(name, {
		"width": 250,
		"height": 30,
		"x": 26,
		"y": 2,
		"tooltip": "Your current preset",
        "parentComponent": "PRESET_Bar",
		});
    
    
		widget.setPaintRoutine(function(g)
		{

			g.setColour(0x00FFFFFF);
			g.drawRect([0, 0, this.getWidth(), this.getHeight()], 1);
			g.setFont("Arial", 17.0);
			g.setColour(0xFFFFFFFF);
    	
			g.drawAlignedText(Engine.getCurrentUserPresetName(), [5, 0, this.getWidth(), this.getHeight()], "left");
		});
    
		widget.setTimerCallback(function()
		{
			this.repaint();
		});
    
		widget.startTimer(300);
	
    
		widget.setMouseCallback(function(event)
		{
			this.data.hover = event.hover;
			this.repaint();
		});
		return widget;
	};

}


Engine.loadNextUserPreset(true);
const var UpButton = UserPresetWidgets.createPresetButton("UpButton", 300, 6, true);
const var DownButton = UserPresetWidgets.createPresetButton("DownButton", 279, 6, false);
const var PresetDisplay = UserPresetWidgets.createPresetDisplay("PresetDisplay", 129, 0);


/////////////////////// END OF THE PRESET BROSER WINDOW //////////////////////////