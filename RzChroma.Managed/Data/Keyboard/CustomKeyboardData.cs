using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RzChroma.Data.Keyboard
{
    /// <summary>
    /// Represents <see cref="DataType.Keyboard"/> of type <see cref="KeyboardDataType.CHROMA_CUSTOM"/>
    /// </summary>
    public class CustomKeyboardData : IKeyboardData
    {
        /// <summary>
        /// The maximum number of rows of data this object type can represent
        /// </summary>
        /// <remarks>
        /// As defined in RzChromaSDKTypes.h from the Razer Chroma SDK
        /// </remarks>
        public static readonly int MaxRows = 6;

        /// <summary>
        /// The maximum number of cols of data this object type can represent
        /// </summary>
        /// <remarks>
        /// As defined in RzChromaSDKTypes.h from the Razer Chroma SDK
        /// </remarks>
        public static readonly int MaxCols = 22;
        
        /// <summary>
        /// The type of data
        /// </summary>
        public DataType Type => DataType.Keyboard;

        /// <summary>
        /// The type of event
        /// </summary>
        public KeyboardDataType EventType => KeyboardDataType.CHROMA_CUSTOM;

        /// <summary>
        /// Keyboard color data
        /// </summary>
        /// <remarks>
        /// This 2d array represents a keyboard layout with color data for each key
        /// </remarks>
        public Color[][] ColorMap
        {
            get;
            set;
        }
    }
}
