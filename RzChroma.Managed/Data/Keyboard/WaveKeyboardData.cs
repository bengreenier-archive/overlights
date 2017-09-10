using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RzChroma.Data.Keyboard
{
    /// <summary>
    /// Represents <see cref="DataType.Keyboard"/> of type <see cref="KeyboardDataType.CHROMA_WAVE"/>
    /// </summary>
    public class WaveKeyboardData : IKeyboardData
    {
        /// <summary>
        /// Represents the direction of the wave
        /// </summary>
        public enum DirectionType
        {
            DIRECTION_NONE = 0,           //!< No direction.
            DIRECTION_LEFT_TO_RIGHT,    //!< Left to right.
            DIRECTION_RIGHT_TO_LEFT,    //!< Right to left.
            DIRECTION_INVALID           //!< Invalid direction.
        }

        /// <summary>
        /// The type of data
        /// </summary>
        public DataType Type => DataType.Keyboard;

        /// <summary>
        /// The type of event
        /// </summary>
        public KeyboardDataType EventType => KeyboardDataType.CHROMA_WAVE;

        /// <summary>
        /// The direction of the wave
        /// </summary>
        public DirectionType Direction
        {
            get;
            set;
        }
    }
}
