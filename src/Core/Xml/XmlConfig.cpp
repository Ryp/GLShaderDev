/*
 * This file is part of GLShaderDev.
 *
 * GLShaderDev is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GLShaderDev is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GLShaderDev.  If not, see <http://www.gnu.org/licenses/>
 */

#include "XmlConfig.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "exception/configexception.hpp"

using boost::property_tree::xml_parser::read_xml;
using boost::property_tree::xml_parser::write_xml;
using boost::property_tree::xml_writer_settings;
using boost::property_tree::ptree_error;
using boost::property_tree::xml_parser::no_concat_text;
using boost::property_tree::xml_parser::no_comments;
using boost::property_tree::xml_parser::trim_whitespace;

XmlConfig::XmlConfig(const std::string& file, IXmlSerializable& object)
:   _file(file),
    _object(object)
{}

void XmlConfig::serialize()
{
    std::ofstream               cfg(_file);
    ptree                       pt;
    xml_writer_settings<char>   settings(' ', WhiteSpaceIndent);

    if (!cfg.good())
        throw (ConfigException(_file, "Could not open file"));
    try
    {
        _object.serialize(pt);
        write_xml(cfg, pt, settings);
    }
    catch (const ptree_error& e)
    {
        throw (ConfigException(_file, e.what()));
    }
}

void XmlConfig::deserialize()
{
    std::ifstream   cfg(_file);
    ptree           pt;

    if (!cfg.good())
        throw (ConfigException(_file, "Could not open file"));
    try
    {
        read_xml(cfg, pt, trim_whitespace | no_comments);
        _object.deserialize(pt);
    }
    catch (ptree_error& e)
    {
        throw (ConfigException(_file, e.what()));
    }
}
