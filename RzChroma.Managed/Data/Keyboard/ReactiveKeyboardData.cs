using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RzChroma.Data.Keyboard
{
    /// <summary>
    /// Represents <see cref="DataType.Keyboard"/> of type <see cref="KeyboardDataType.CHROMA_REACTIVE"/>
    /// </summary>
    public class ReactiveKeyboardData : IKeyboardData
    {
        /// <summary>
        /// The duration the lighting effect will last
        /// </summary>
        public enum DurationType
        {
            DURATION_NONE = 0,    //!< No duration.
            DURATION_SHORT,     //!< Short duration.
            DURATION_MEDIUM,    //!< Medium duration.
            DURATION_LONG,      //!< Long duration.
            DURATION_INVALID    //!< Invalid duration.
        }

        /// <summary>
        /// The type of data
        /// </summary>
        public DataType Type => DataType.Keyboard;

        /// <summary>
        /// The type of event
        /// </summary>
        public KeyboardDataType EventType => KeyboardDataType.CHROMA_REACTIVE;

        /// <summary>
        /// The effect duration
        /// </summary>
        public DurationType Duration
        {
            get;
            set;
        }

        /// <summary>
        /// The effect color
        /// </summary>
        public Color Color
        {
            get;
            set;
        }
    }
}
