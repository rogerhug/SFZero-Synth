/*
  ==============================================================================

    customLook.h
    Created: 17 May 2021 1:56:01pm
    Author:  Roger Hug

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>

struct CustomLookAndFeel    : public juce::LookAndFeel_V1
{
    void drawRoundThumb (juce::Graphics& g, float x, float y, float diameter, juce::Colour colour, float outlineThickness)
    {
        auto halfThickness = outlineThickness * 0.5f;
        
        juce::Path p;
        p.addEllipse (x + halfThickness,
                      y + halfThickness,
                      diameter - outlineThickness,
                      diameter - outlineThickness);
        
        juce::DropShadow (juce::Colours::black, 1, {}).drawForPath (g, p);
        
        g.setColour (colour);
        g.fillPath (p);
        
        g.setColour (colour.brighter());
        g.strokePath (p, juce::PathStrokeType (outlineThickness));
    }
    
    void drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override
    {
        auto baseColour = backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
        .withMultipliedAlpha      (button.isEnabled() ? 0.9f : 0.5f);
        
        if (isButtonDown || isMouseOverButton)
            baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.1f);
        
        auto flatOnLeft   = button.isConnectedOnLeft();
        auto flatOnRight  = button.isConnectedOnRight();
        auto flatOnTop    = button.isConnectedOnTop();
        auto flatOnBottom = button.isConnectedOnBottom();
        
        auto width  = (float) button.getWidth()  - 1.0f;
        auto height = (float) button.getHeight() - 1.0f;
        
        if (width > 0 && height > 0)
        {
            auto cornerSize = fmin (2.0f, fmin (width, height) * 0.45f);
            auto lineThickness = cornerSize    * 0.1f;
            auto halfThickness = lineThickness * 0.5f;
            
            juce::Path outline;
            outline.addRoundedRectangle (0.5f + halfThickness, 0.5f + halfThickness, width - lineThickness, height - lineThickness,
                                         cornerSize, cornerSize,
                                         ! (flatOnLeft  || flatOnTop),
                                         ! (flatOnRight || flatOnTop),
                                         ! (flatOnLeft  || flatOnBottom),
                                         ! (flatOnRight || flatOnBottom));
            
            auto outlineColour = button.findColour (button.getToggleState() ? juce::TextButton::textColourOnId
                                                    : juce::TextButton::textColourOffId);
            
            g.setColour (baseColour);
            g.fillPath (outline);
            
            if (! button.getToggleState())
            {
                g.setColour (outlineColour);
                g.strokePath (outline, juce::PathStrokeType (lineThickness));
            }
        }
    }
    
    void drawTickBox (juce::Graphics& g, juce::Component& component,
                      float x, float y, float w, float h,
                      bool ticked,
                      bool isEnabled,
                      bool isMouseOverButton,
                      bool isButtonDown) override
    {
        auto boxSize = w * 0.7f;
        
        auto isDownOrDragging = component.isEnabled() && (component.isMouseOverOrDragging() || component.isMouseButtonDown());
        
        auto colour = component.findColour (juce::TextButton::buttonColourId)
        .withMultipliedSaturation ((component.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
        .withMultipliedAlpha (component.isEnabled() ? 1.0f : 0.7f);
        
        drawRoundThumb (g, x, y + (h - boxSize) * 0.5f, boxSize, colour,
                        isEnabled ? ((isButtonDown || isMouseOverButton) ? 1.1f : 0.5f) : 0.3f);
        
        if (ticked)
        {
            g.setColour (isEnabled ? findColour (juce::TextButton::buttonOnColourId) : juce::Colours::green);
            
            auto scale = 9.0f;
            auto trans = juce::AffineTransform::scale (w / scale, h / scale).translated (x - 2.5f, y + 1.0f);
            
            g.fillPath (LookAndFeel_V1::getTickShape (6.0f), trans);
        }
    }
    
    void drawLinearSliderThumb (juce::Graphics& g, int x, int y, int width, int height,
                                float sliderPos, float minSliderPos, float maxSliderPos,
                                const juce::Slider::SliderStyle style, juce::Slider& slider) override
    {
        auto sliderRadius = (float) (getSliderThumbRadius (slider) - 2);
        
        auto isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());
        
        auto knobColour = slider.findColour (juce::Slider::thumbColourId)
        .withMultipliedSaturation ((slider.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
        .withMultipliedAlpha (slider.isEnabled() ? 1.0f : 0.7f);
        
        if (style == juce::Slider::LinearHorizontal || style == juce::Slider::LinearVertical)
        {
            float kx, ky;
            
            if (style == juce::Slider::LinearVertical)
            {
                kx = (float) x + (float) width * 0.5f;
                ky = sliderPos;
            }
            else
            {
                kx = sliderPos;
                ky = (float) y + (float) height * 0.5f;
            }
            
            auto outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;
            /*
            drawRoundThumb (g,
                            kx - sliderRadius,
                            ky - sliderRadius,
                            sliderRadius * 0.0f,
                            knobColour, outlineThickness);*/
        }
        else
        {
            // Just call the base class for the demo
            LookAndFeel_V2::drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }
    
    void drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const juce::Slider::SliderStyle style, juce::Slider& slider) override
    {
        g.fillAll (slider.findColour (juce::Slider::backgroundColourId));
        
        if (style == juce::Slider::LinearBar || style == juce::Slider::LinearBarVertical)
        {
            juce::Path p;
            
            if (style == juce::Slider::LinearBarVertical)
                p.addRectangle ((float) x, sliderPos, (float) width, 1.0f + (float) height - sliderPos);
            else
                p.addRectangle ((float) x, (float) y, sliderPos - (float) x, (float) height);
            
            auto baseColour = slider.findColour (juce::Slider::rotarySliderFillColourId)
            .withMultipliedSaturation (slider.isEnabled() ? 1.0f : 0.5f)
            .withMultipliedAlpha (0.8f);
            
            g.setColour (baseColour);
            g.fillPath (p);
            int fillh = slider.getValue()*height;
            auto lineThickness = fmin (15.0f, (float) fmin (width, height) * 0.45f) * 0.1f;
            g.drawRect (slider.getLocalBounds().toFloat(), lineThickness);
 
            g.fillRect(x, y-5, fillh, height);
        }
        else
        {
            drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
            drawLinearSliderThumb      (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }
    
    void drawLinearSliderBackground (juce::Graphics& g, int x, int y, int width, int height,
                                     float /*sliderPos*/,
                                     float /*minSliderPos*/,
                                     float /*maxSliderPos*/,
                                     const juce::Slider::SliderStyle /*style*/, juce::Slider& slider) override
    {
        auto sliderRadius = (float) getSliderThumbRadius (slider) - 0.5f;
        juce::Path on, off;
        
        if (slider.isHorizontal())
        {
            auto iy = (float) y + (float) height * 0.5f - sliderRadius * 0.5f;
            juce::Rectangle<float> r ((float) x - sliderRadius * 0.5f, y+5, (float) width + sliderRadius, height-5);
            auto onW = r.getWidth() * ((float) slider.valueToProportionOfLength (slider.getValue()));
            
            on.addRectangle (r.removeFromLeft (onW));
            off.addRectangle (r);
        }
        else
        {
            auto ix = (float) x + (float) width * 0.5f - sliderRadius * 0.5f;
           // juce::Rectangle<float> r (ix, (float) y - sliderRadius * 0.5f, sliderRadius, (float) height + sliderRadius);
            juce::Rectangle<float> r(x, (float)y - sliderRadius * 0.5f, width-1, (float)height + sliderRadius);
            auto onH = r.getHeight() * ((float) slider.valueToProportionOfLength (slider.getValue()));
            
            on.addRectangle (r.removeFromBottom (onH));
            off.addRectangle (r);
        }
        
        g.setColour (slider.findColour (juce::Slider::rotarySliderFillColourId));
        g.fillPath (on);
        
        g.setColour (slider.findColour (juce::Slider::trackColourId));
        g.fillPath (off);
    }
    
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                           float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override
    {
        auto radius = (float) fmin (width / 2, height / 2) - 2.0f;
        auto centreX = (float) x + (float) width  * 0.5f;
        auto centreY = (float) y + (float) height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
        
        if (slider.isEnabled())
            g.setColour (slider.findColour (juce::Slider::rotarySliderFillColourId));
        else
            g.setColour (juce::Colour (0x80808080));
        
        {
            juce::Path filledArc;
            filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, 0.5);
            g.fillPath (filledArc);
        }
        
        {
            auto lineThickness = fmin (15.0f, (float) fmin (width, height) * 0.45f) * 0.1f;
            juce::Path outlineArc;
            outlineArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, 0.5);
            g.strokePath (outlineArc, juce::PathStrokeType (lineThickness));
            g.setColour (juce::Colours::white);
            juce::Path outlineArcA;
            outlineArcA.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, 0.5);
            
            g.strokePath (outlineArcA, juce::PathStrokeType (lineThickness));
            
        }
    }
   
};
