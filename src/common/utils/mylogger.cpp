/* Copyright (c) 2018 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#include <cctype>
#include <sstream>
#include <execinfo.h>
#include <dlfcn.h>     // for dladdr
#include <cxxabi.h>    // for __cxa_demangle


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

    VLOG(lglvl) << "vid_type:" << static_cast<int>(sd.get_vid_type().get_type());
    // DDlogfield(lglvl, sd, vid_type);

    DDlogfield(lglvl, sd, group_name);
    DDlogfield(lglvl, sd, isolation_level);
    DDlogfield(lglvl, sd, comment);
    VLOG(lglvl) << "--------";
}

void myLogger::doLogEncBuf(const std::string &pref, int lglvl, const std::string &buf) {
    std::stringstream s;
    for (const auto &i : buf) {
        if (::isprint(i)) {
            s << i;
        } else {
            s << "\\x" << int(i);
        }
    }
    VLOG(lglvl) << pref << s.str();
}


void myLogger::doLogBackTrace(const std::string &pref, int lglvl) {
    std::stringstream s;

    void *buffer[kBacktraceMaxDepth];
    char **strings;

    int nptrs = backtrace(buffer, kBacktraceMaxDepth);
    strings = backtrace_symbols(buffer, nptrs);
    s << "\n";
    if (strings != nullptr) {
        for (int i = 0; i < nptrs; i++) {
            Dl_info info;
            if (dladdr(buffer[i], &info)) {
                char *demangled = NULL;
                int status;
                demangled = abi::__cxa_demangle(info.dli_sname, NULL, 0, &status);
                s << "  f-" << (nptrs - i) << " : " << demangled << "\n";
                free(demangled);
            } else {
                s << strings[i] << "\n";
            }
        }
        VLOG(lglvl) << "---- " << pref << " ----";
        VLOG(lglvl) << s.str();
        VLOG(lglvl) << "------------";
    }
    free(strings);
}


#undef DDlogfield

}   // namespace utils
}   // namespace nebula
