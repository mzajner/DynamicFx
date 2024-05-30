Content.makeFrontInterface(939, 706);

include("ModMatrixList.js"); //Keep ModMatrixList at Top of the script
include("Declarations.js");
include("Arpeggiator.js");
include("Comboboxes.js");
include("DraggableFilter.js");
include("EditPanels.js");
//include("Filters.js");
include("Legato.js");
include("LookAndFeel.js");
include("MuteSolo.js");
include("PresetBrowser.js");
//include("CopyProtection.js");
include("PageHandling.js");
include("Resize.js");


include("Modulators.js");
include("UI/RectHelpers.js");
include("TableLogic.js");
include("UI/TableLookAndFeel.js");
include("UI/KnobLookAndFeel.js");
include("UI/DragPanel.js");
include("UI/PageLogic.js");

/*
include("Combobox.js");
include("EffectsArchive.js");
*/


Synth.deferCallbacks(false);
Synth.setUseUniformVoiceHandler("MikeEditions_1.0", false); //Change this to the current XML project



const var Viewport1 = Content.getComponent("Viewport1");

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