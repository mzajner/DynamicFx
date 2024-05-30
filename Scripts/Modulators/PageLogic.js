namespace PageLogic
{
	const var ModMatrixPanel = Content.getComponent("ModMatrixPanel");
	
/*	ModMatrixPanel.setPaintRoutine(function(g)
	{
		var b = this.getLocalBounds(5);
		
		g.fillAll(0x75000000);
		
		g.fillRoundedRectangle(Rect.removeFromBottom(b, 530), 10);
		g.fillRoundedRectangle(Rect.removeFromTop(b, 530), 10);
		
		g.setColour(0x75000000);
		g.fillRect([42, 625, 713, 4]);
	
		//g.addNoise(0.05);
		
		g.setFont("Lato Bold", 18.0);
		g.setColour(0x23FFFFFF);
		g.drawAlignedText(Engine.getProjectInfo().ProjectName, b, "topRight");
	});*/
	
	const var menuButtonLaf = Content.createLocalLookAndFeel();
	
	menuButtonLaf.registerFunction("drawToggleButton", function(g, obj)
	{
		g.setColour(0x22000000);
		g.fillRect(obj.area);
		g.setColour(Colours.withAlpha(Colours.white, obj.over ? 0.8 : 0.6));
		g.setFont("Lato Bold", 13.0);
		g.drawAlignedText(obj.text, obj.area, "centred");
	});
	
	const var menuButtons = [Content.getComponent("Button1"), 
	                         Content.getComponent("Button2"), 
	                         Content.getComponent("Button3")];
	
	inline function onMenuButton(component, value)
	{
		if(!value)
			return;
		
		local idx = menuButtons.indexOf(component);
		Console.print("Button clicked: " + component.data.id + ", Index: " + idx);
		if(idx == 0)
			Engine.undo();
		else if(idx == 1)
			Engine.redo();
		else if(idx == 2)
			matrix.clearAllConnections();
	}
	
	for(c in menuButtons)
	{
		c.set("isMomentary", true);
		c.setLocalLookAndFeel(menuButtonLaf);
		c.set("saveInPreset", false);
		c.setControlCallback(onMenuButton);
	}
	    
	
	const var pageButton_laf = Content.createLocalLookAndFeel();
	
	pageButton_laf.registerFunction("drawToggleButton", function(g, obj)
	{
		
	
		g.setColour(0x22000000);
		if(obj.value)
			g.fillRect(obj.area);
		
		var alpha = 0.2;
		
		if(obj.over)
			alpha += 0.1;
			
		if(obj.value)
			alpha += 0.5;
		
		g.setColour(Colours.withAlpha(Colours.white, alpha));
		g.setFont("Lato Bold", 13.0);
		g.drawAlignedText(obj.text, obj.area, "centred");
	});
	
	const var pageButton_laf_targets = [Content.getComponent("Button4"), 
	                                    Content.getComponent("Button5"), 
	                                    Content.getComponent("Button6"),
	                                    Content.getComponent("LfoButton1"),
	                                    Content.getComponent("LfoButton2"),
	                                    Content.getComponent("LfoButton3")];
	
	const var pageBroadcaster = Engine.createBroadcaster({
		"id": "pageBroadcaster",
		"args": ["index"]
	});
	
	pageBroadcaster.attachToRadioGroup(9000, "page logic");
	
	pageBroadcaster.addComponentPropertyListener(["ModulatorPanel", "TableBG", "MatrixBG"], "visible", "show pages", function(index, i)
	{
		return index == i;
	});
	
	for(c in pageButton_laf_targets)
	    c.setLocalLookAndFeel(pageButton_laf);
	    
}
