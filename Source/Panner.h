/**
    bespoke synth, a software modular synthesizer
    Copyright (C) 2021 Ryan Challinor (contact: awwbees@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
/*
  ==============================================================================

    Panner.h
    Created: 10 Oct 2017 9:49:16pm
    Author:  Ryan Challinor

  ==============================================================================
*/

#pragma once
#include <iostream>
#include "IAudioProcessor.h"
#include "IDrawableModule.h"
#include "Slider.h"
#include "ClickButton.h"
#include "RollingBuffer.h"
#include "Ramp.h"
#include "Checkbox.h"
#include "PatchCableSource.h"

class Panner : public IAudioProcessor, public IDrawableModule, public IFloatSliderListener, public IButtonListener, public IIntSliderListener
{
public:
   Panner();
   virtual ~Panner();
   static IDrawableModule* Create() { return new Panner(); }
   
   
   void CreateUIControls() override;
   
   void SetPan(float pan) { mPan = pan; }
   
   //IAudioSource
   void Process(double time) override;
   void SetEnabled(bool enabled) override { mEnabled = enabled; }
   
   void FloatSliderUpdated(FloatSlider* slider, float oldVal) override;
   void IntSliderUpdated(IntSlider* slider, int oldVal) override;
   void ButtonClicked(ClickButton* button) override;
   void CheckboxUpdated(Checkbox* checkbox) override;
   
   virtual void LoadLayout(const ofxJSONElement& moduleInfo) override;
   virtual void SetUpFromSaveData() override;
   
private:
   //IDrawableModule
   void DrawModule() override;
   void GetModuleDimensions(float& w, float& h) override { w=120; h=40; }
   bool Enabled() const override { return mEnabled; }
   
   float mPan;
   Ramp mPanRamp;
   FloatSlider* mPanSlider;
   float mWiden;
   FloatSlider* mWidenSlider;
   RollingBuffer mWidenerBuffer;
};

