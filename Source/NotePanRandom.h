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

    NotePanRandom.h
    Created: 22 Feb 2020 10:39:25pm
    Author:  Ryan Challinor

  ==============================================================================
*/

#pragma once
#include "NoteEffectBase.h"
#include "IDrawableModule.h"
#include "Checkbox.h"
#include "INoteSource.h"
#include "Slider.h"

class NotePanRandom : public NoteEffectBase, public IDrawableModule, public IFloatSliderListener
{
public:
   NotePanRandom();
   static IDrawableModule* Create() { return new NotePanRandom(); }
   
   
   void CreateUIControls() override;
   
   void SetEnabled(bool enabled) override { mEnabled = enabled; }
   
   //INoteReceiver
   void PlayNote(double time, int pitch, int velocity, int voiceIdx = -1, ModulationParameters modulation = ModulationParameters()) override;
   
   void FloatSliderUpdated(FloatSlider* slider, float oldVal) override {}
   
   virtual void LoadLayout(const ofxJSONElement& moduleInfo) override;
   virtual void SetUpFromSaveData() override;
   
private:
   //IDrawableModule
   void DrawModule() override;
   void GetModuleDimensions(float& width, float& height) override { width = mWidth; height = mHeight; }
   bool Enabled() const override { return mEnabled; }
   
   float mSpread;
   FloatSlider* mSpreadSlider;
   float mCenter;
   FloatSlider* mCenterSlider;
   
   static const int kPanHistoryDisplaySize = 10;
   struct PanHistoryDisplayItem
   {
      float time;
      float pan;
   };
   PanHistoryDisplayItem mPanHistoryDisplay[kPanHistoryDisplaySize];
   int mPanHistoryDisplayIndex;
   
   float mWidth;
   float mHeight;
};
