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

#include "hasher.h"
#include <vector>
#include <openssl/md5.h>

namespace exagent {

bool Hasher::md5(const std::string& in, std::string& result)
{   
    if(in.size() == 0)
    {
        return false;
    }
    
    std::vector<unsigned char> digest(MD5_DIGEST_LEN);
 
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, in.data(), in.size());
    MD5_Final(digest.data(), &ctx);
 
    std::vector<char> mdString(MD5_STR_LEN);
    for (size_t i = 0; i < digest.size(); i++)
    {
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    }
    
    result.resize(MD5_STR_LEN);
    std::copy(mdString.begin(), mdString.end(), result.begin()); //Could just return the digest, eliminating this copy

    return true;
}

}