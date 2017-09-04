using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RzChroma.Managed
{
    public class RzChromaKeyboardCustomData : RzChromaKeyboardData
    {
        public RzChromaKeyboardCustomData()
        {
            this.Type = NativeLayouts.RZKEYBOARDTYPE.CHROMA_CUSTOM;
        }

        /// <summary>
        /// Max sizes: <see cref="NativeLayouts.RZKEYBOARD_MAX_ROWS"/> <see cref="NativeLayouts.RZKEYBOARD_MAX_COLUMNS"/>
        /// </summary>
        public NativeLayouts.Color[][] ColorMap
        {
            get;
            set;
        }
    }
}
