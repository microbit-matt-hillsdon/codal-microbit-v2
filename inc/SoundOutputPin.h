/*
The MIT License (MIT)

Copyright (c) 2017 Lancaster University.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef CODAL_SOUND_OUTPUT_PIN_H
#define CODAL_SOUND_OUTPUT_PIN_H

#include "Pin.h"
#include "CodalConfig.h"
#include "CodalComponent.h"
#include "MicroBitCompat.h"
#include "Mixer2.h"
#include "SoundEmojiSynthesizer.h"

#ifndef CONFIG_SOUND_OUTPUT_PIN_PERIOD
#define CONFIG_SOUND_OUTPUT_PIN_PERIOD  50
#endif

/**
  * Class definition for a SoundPin.
  *
  * Provides an abstraction between an analog output pin and an input to the audio mixer pipeline.
  */
namespace codal
{
    class SoundOutputPin : public codal::Pin
    {
    private:
        Mixer2                  &mix;
        MixerChannel            *channel;
        SoundEmojiSynthesizer   synth;
        int                     periodUs;
        int                     value;

    public:

        /**
         * Constructor.
         * Create a DevicePin instance, generally used to represent a pin on the edge connector.
         *
         * @param id the unique EventModel id of this component.
         * @param mixer the mixer to use
         */
        SoundOutputPin(Mixer2 &mixer, int id = MICROBIT_ID_VIRTUAL_SPEAKER_PIN);


        /**
         * Configures this IO pin as an analog/pwm output, and change the output value to the given level.
         *
         * @param value the level to set on the output pin, in the range 0 - 1024
         *
         * @return DEVICE_OK on success, DEVICE_INVALID_PARAMETER if value is out of range, or DEVICE_NOT_SUPPORTED
         *         if the given pin does not have analog capability.
         */
        int setAnalogValue(int value);

        /**
         * Configures this IO pin as an analogue input (if necessary), and samples the Pin for its analog value.
         *
         * @return the current analogue level on the pin, in the range 0 - 1024, or
         *         DEVICE_NOT_SUPPORTED if the given pin does not have analog capability.
         *
         * @code
         * Pin P0(DEVICE_ID_IO_P0, DEVICE_PIN_P0, PIN_CAPABILITY_BOTH);
         * P0.getAnalogValue(); // P0 is a value in the range of 0 - 1024
         * @endcode
         */
        int getAnalogValue();

        /**
         * Configures the PWM period of the analog output to the given value.
         *
         * @param period The new period for the analog output in milliseconds.
         *
         * @return DEVICE_OK on success, or DEVICE_NOT_SUPPORTED if the
         *         given pin is not configured as an analog output.
         */
        int setAnalogPeriod(int period);

        /**
         * Configures the PWM period of the analog output to the given value.
         *
         * @param period The new period for the analog output in microseconds.
         *
         * @return DEVICE_OK on success, or DEVICE_NOT_SUPPORTED if the
         *         given pin is not configured as an analog output.
         */
        int setAnalogPeriodUs(int period);

        /**
         * Obtains the PWM period of the analog output in microseconds.
         *
         * @return the period on success, or DEVICE_NOT_SUPPORTED if the
         *         given pin is not configured as an analog output.
         */
        uint32_t getAnalogPeriodUs();

        /**
         * Obtains the PWM period of the analog output in milliseconds.
         *
         * @return the period on success, or DEVICE_NOT_SUPPORTED if the
         *         given pin is not configured as an analog output.
         */
        int getAnalogPeriod();

        private:

        /**
         * Update the sound being played to match that requested.
         */
        void update();
    };
}


#endif