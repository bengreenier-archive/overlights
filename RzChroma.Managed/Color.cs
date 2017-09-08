using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RzChroma
{
    /// <summary>
    /// Represents an RGBA color
    /// </summary>
    /// <remarks>
    /// Each component is a single byte represented as an int value
    /// </remarks>
    public class Color
    {
        /// <summary>
        /// Red component
        /// </summary>
        public int R;

        /// <summary>
        /// Green component
        /// </summary>
        public int G;

        /// <summary>
        /// Blue component
        /// </summary>
        public int B;

        /// <summary>
        /// Alpha component
        /// </summary>
        public int A;
    }
}
