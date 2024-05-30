Content.makeFrontInterface(600, 600);

Content.addKnob("Knob1", 100, 0);
Content.addKnob("Knob2", 0, 50);
Content.addKnob("Knob3", 0, 100);
Content.addKnob("Knob4", 0, 150);



const var bc = Engine.createBroadcaster({
	"id": "FxBroadcaster",
	"colour": -1, 
	"args": ["component", "property", "value"]
})

bc.attachToComponentProperties("Knob1", "parameterId", "Parameter Id Watcher");

/** This function just syncs the `x` property by returning the value but you could calculate any custom value if you need to. */
inline function updateFunction(indexInList, component, property, EffectId)
{
	Console.print(trace({
		"indexInList": indexInList,
		"component": component.get("id"),
		"property": property,
		"value": value
	}));
	
	// something to play around with...
	//return value * (indexInList + 2);

	return value ;
};


/** You could also just pass in this instead of the updateFunction, then it will use the "default" behaviour. */
const var defaultUpdateFunction = 0;

/* Add a listener that changes properties when the broadcaster sends out a message. */
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
	
}
 