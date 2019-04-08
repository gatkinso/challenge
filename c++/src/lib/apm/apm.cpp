// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "apm.h"
#include "transport.pb.h"
#include "google/protobuf/util/json_util.h"
#include "hasher.h"
#include <fstream>
#include <sstream>

#include <iostream>

namespace exagent
{

bool APM::process_request(const std::string req_json_str, const std::string id)
{
    if (req_json_str.length() == 0 || id.length() == 0)
    {
        //normally this would of course all be logged....
        return false;
    }

    {
        std::lock_guard<std::mutex> lock(mtx_);
        exmap_[id] = req_json_str;
    }

    return true;
}

void build_str(const std::string& key, challenge::transport::Transport& txp_proto, 
    std::stringstream& ss, bool end)
{
    auto iter = txp_proto.string_values().find(key);
    if (iter != txp_proto.string_values().end())
        ss << iter->second;
    else
        ss << " ";
    
    if (false == end)
        ss << ",";
}

bool APM::process_response(const std::string res_json_str, const std::string id)
{
    //std::cerr << id.c_str();
    std::lock_guard<std::mutex> lock(mtx_);

    auto req = exmap_.find(id);
    if (req == exmap_.end())
        return false;

    std::string md5_str;
    if (false == Hasher::md5(res_json_str, md5_str))
        return false;

    challenge::transport::Transport txp_proto;
    auto ret = google::protobuf::util::JsonStringToMessage(req->second, &txp_proto);

    if (ret != google::protobuf::util::Status::OK)
    {
        return false;
    }

    exmap_.erase(id);

    std::stringstream ss;
    build_str("timestamp", txp_proto, ss, false);
    build_str("uuid", txp_proto, ss, false);
    build_str("pid", txp_proto, ss, false);
    build_str("tid", txp_proto, ss, false);
    build_str("base_url", txp_proto, ss, false);
    build_str("method", txp_proto, ss, false);
    build_str("timestamp", txp_proto, ss, false);
    build_str("timestamp", txp_proto, ss, false);
    ss << md5_str << std::endl;

    if (false == this->write_file(ss.str()))
        return false;
    
    return true;
}

std::string APM::get_filename() 
{
    std::lock_guard<std::mutex> lock(mtx_);
    return filename_;
}

void APM::set_filename(const std::string filename) 
{
    std::lock_guard<std::mutex> lock(mtx_);
    filename_ = filename;
}

bool APM::write_file(const std::string str)
{
    try
    {
        std::ofstream out_file(filename_, std::ofstream::out | std::ofstream::app);
        out_file.write(str.c_str(), str.size());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}

}