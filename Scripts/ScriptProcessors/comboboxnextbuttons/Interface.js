Content.makeFrontInterface(600, 500);



//// COMBO BOX BROWSE BUTTONS
const var ComboBox3 = Content.getComponent("ComboBox3");


const var ComboBox1      = Content.getComponent("ComboBox1");
const var ComboBox2     = Content.getComponent("ComboBox2");
const var Left_Random_Value  = Content.getComponent("Left_Random_Value");
const var Right_Random_Value = Content.getComponent("Right_Random_Value");
const var C_Random_Value = Content.getComponent("C_Random_Value");
const var Prev_Cpanel = Content.getComponent("Prev_Cpanel");
const var Next_Cpanel = Content.getComponent("Next_Cpanel");






// ComboBoxes 
// ComboBox1
inline function onComboBox1Control(component, value)
{
    Left_Random_Value.setValue(myValues[value-1]);
};
ComboBox1.setControlCallback(onComboBox1Control);

// ComboBox2
inline function onComboBox2Control(component, value)
{
    Right_Random_Value.setValue(myValues[value-1]);
};
ComboBox2.setControlCallback(onComboBox2Control);

// ComboBox3


inline function onComboBox3Control(component, value)
{
	C_Random_Value.setValue(myValues[value-1]);
};
ComboBox3.setControlCallback(onComboBox3Control);





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
 