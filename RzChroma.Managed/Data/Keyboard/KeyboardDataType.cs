using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RzChroma.Data.Keyboard
{
    /// <summary>
    /// Represents the different types of keyboard data
    /// </summary>
    /// <remarks>
    /// Values from RzChromaSDKTypes.h from the Razer Chroma SDK
    /// </remarks>
    public enum KeyboardDataType
    {
        CHROMA_NONE = 0,            //!< No effect.
        CHROMA_BREATHING,           //!< Breathing effect.
        CHROMA_CUSTOM,              //!< Custom effect.
        CHROMA_REACTIVE,            //!< Reactive effect.
        CHROMA_STATIC,              //!< Static effect.
        CHROMA_SPECTRUMCYCLING,     //!< Spectrum cycling effect.
        CHROMA_WAVE,                //!< Wave effect.
        CHROMA_STARLIGHT,           //!< Starlight effect.
        CHROMA_CUSTOM_KEY,          //!< Custom effects with keys.
        CHROMA_INVALID              //!< Invalid effect.
    }
}
