using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RzChroma.Data.Keyboard
{
    /// <summary>
    /// Represents native keyboard event data
    /// </summary>
    public interface IKeyboardData : IData
    {
        /// <summary>
        /// The type of event this data describes
        /// </summary>
        KeyboardDataType EventType
        {
            get;
        }
    }

    public static class IKeyboardDataExtensions
    {
        /// <summary>
        /// Casts keyboard data to specific keyboard data types
        /// </summary>
        /// <typeparam name="TCast">The specific IKeyboardData type</typeparam>
        /// <param name="data">data to convert</param>
        /// <returns>the converted data</returns>
        public static TCast As<TCast>(this IKeyboardData data) where TCast : IKeyboardData
        {
            return (TCast)data;
        }
    }
}
