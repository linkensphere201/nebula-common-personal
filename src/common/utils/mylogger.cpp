/* Copyright (c) 2018 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */


#include "common/utils/mylogger.h"

namespace nebula {
namespace utils {
#define DDlogfield(lglvl, v, fld)                                                                  \
    do {                                                                                           \
        VLOG(lglvl) << #fld << ":" << v.get_##fld();                                               \
    } while (0)

void myLogger::doLog(const std::string &pref, int lglvl, const meta::cpp2::SpaceDesc &sd) {
    VLOG(lglvl) << "---- " << pref << ",v=" << lglvl << " ----";
    DDlogfield(lglvl, sd, space_name);
    DDlogfield(lglvl, sd, partition_num);
    DDlogfield(lglvl, sd, replica_factor);
    DDlogfield(lglvl, sd, charset_name);
    DDlogfield(lglvl, sd, collate_name);

    VLOG(lglvl) << "vid_type:" <<
      static_cast<int>(sd.get_vid_type().get_type());
    // DDlogfield(lglvl, sd, vid_type);

    DDlogfield(lglvl, sd, group_name);
    DDlogfield(lglvl, sd, isolation_level);
    DDlogfield(lglvl, sd, comment);
    VLOG(lglvl) << "--------";
}

#undef DDlogfield

}   // namespace utils
}   // namespace nebula
