using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RzChroma.Data
{
    /// <summary>
    /// Representation of 
    /// </summary>
    public interface IData
    {
        /// <summary>
        /// The type of data
        /// </summary>
        DataType Type
        {
            get;
        }
    }

    public static class IDataExtensions
    {
        /// <summary>
        /// Casts data to specific data types
        /// </summary>
        /// <typeparam name="TCast">The specific IData type</typeparam>
        /// <param name="data">data to convert</param>
        /// <returns>the converted data</returns>
        public static TCast As<TCast>(this IData data) where TCast : IData
        {
            return (TCast)data;
        }
    }
}
