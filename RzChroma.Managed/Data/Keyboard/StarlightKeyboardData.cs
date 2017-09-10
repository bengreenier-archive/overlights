using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RzChroma.Data.Keyboard
{
    /// <summary>
    /// Represents <see cref="DataType.Keyboard"/> of type <see cref="KeyboardDataType.CHROMA_STARLIGHT"/>
    /// </summary>
    public class StarlightKeyboardData : IKeyboardData
    {
        /// <summary>
        /// the type of starlight effect
        /// </summary>
        public enum StarlightEffect
        {
            TWO_COLORS = 1, //!< 2 colors.
            RANDOM_COLORS   //!< Random colors
        }

        /// <summary>
        /// The duration the lighting effect will last
        /// </summary>
        public enum DurationType
        {
            DURATION_SHORT = 1, //!< Short duration.
            DURATION_MEDIUM,    //!< Medium duration.
            DURATION_LONG       //!< Long duration.
        }

        /// <summary>
        /// The type of data
        /// </summary>
        public DataType Type => DataType.Keyboard;

        /// <summary>
        /// The type of event
        /// </summary>
        public KeyboardDataType EventType => KeyboardDataType.CHROMA_STARLIGHT;

        /// <summary>
        /// The type of starlight effect
        /// </summary>
        public StarlightEffect StarlightType
        {
            get;
            set;
        }

        /// <summary>
        /// The effect duration
        /// </summary>
        public DurationType Duration
        {
            get;
            set;
        }

        /// <summary>
        /// The first color associated with the effect
        /// </summary>
        /// <remarks>
        /// This can be <c>null</c>, depending on <see cref="StarlightType"/>
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
        /// this can be <c>null</c>, depending on <see cref="StarlightType"/>
        /// </remarks>
        public Color ColorTwo
        {
            get;
            set;
        }
    }
}
