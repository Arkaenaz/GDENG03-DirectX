#include "ColorPickerScreen.h"

#include "imgui.h"

ColorPickerScreen::ColorPickerScreen() : UIScreen("ColorPickerScreen")
{
    isActive = false;
}

ColorPickerScreen::~ColorPickerScreen()
{
}

void ColorPickerScreen::draw()
{
    ImGui::Begin("Color Picker", &isActive);

    if (ImGui::ColorPicker4("Color", color, ImGuiColorEditFlags_PickerHueWheel))
    {
	    
    };

    ImGui::End();
}