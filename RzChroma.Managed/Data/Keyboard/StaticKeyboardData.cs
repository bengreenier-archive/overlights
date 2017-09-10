using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RzChroma.Data.Keyboard
{
    /// <summary>
    /// Represents <see cref="DataType.Keyboard"/> of type <see cref="KeyboardDataType.CHROMA_STATIC"/>
    /// </summary>
    public class StaticKeyboardData : IKeyboardData
    {
        /// <summary>
        /// The type of data
        /// </summary>
        public DataType Type => DataType.Keyboard;

        /// <summary>
        /// The type of event
        /// </summary>
        public KeyboardDataType EventType => KeyboardDataType.CHROMA_STATIC;

        /// <summary>
        /// The color of the effect
        /// </summary>
        public Color Color
        {
            get;
            set;
        }
    }
}
