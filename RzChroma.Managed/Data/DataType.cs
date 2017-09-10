using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RzChroma.Data
{
    /// <summary>
    /// Represents the different types of RzChroma <see cref="IData"/>
    /// </summary>
    public enum DataType
    {
        None = 0,
        Keyboard = 1,
        Mouse = 2,
        Headset = 3,
        Adapter = 4
    }
}
