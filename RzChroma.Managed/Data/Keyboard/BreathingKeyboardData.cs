using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RzChroma.Data.Keyboard
{
    /// <summary>
    /// Represents <see cref="DataType.Keyboard"/> of type <see cref="KeyboardDataType.CHROMA_BREATHING"/>
    /// </summary>
    public class BreathingKeyboardData : IKeyboardData
    {
        /// <summary>
        /// The type of the breathing effect
        /// </summary>
        public enum BreathingEffect
        {
            TWO_COLORS = 1,     //!< 2 colors
            RANDOM_COLORS,      //!< Random colors
            INVALID             //!< Invalid type
        }

        /// <summary>
        /// The type of data
        /// </summary>
        public DataType Type => DataType.Keyboard;

        /// <summary>
        /// The type of event
        /// </summary>
        public KeyboardDataType EventType => KeyboardDataType.CHROMA_BREATHING;

        /// <summary>
        /// The type of breathing effect
        /// </summary>
        public BreathingEffect BreathingType
        {
            get;
            set;
        }

        /// <summary>
        /// The first color associated with the effect
        /// </summary>
        /// <remarks>
        /// This can be <c>null</c>, depending on <see cref="BreathingType"/>
        /// </remarks>
        public Color ColorOne
        {
            get;
            set;
        }

        /// <summary>
        /// The second color associated with the effect
        /// </summary>
        /// <remarks>
        /// this can be <c>null</c>, depending on <see cref="BreathingType"/>
        /// </remarks>
        public Color ColorTwo
        {
            get;
            set;
        }
    }
}
