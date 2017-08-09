#ifndef __m3u8variant__h
#define __m3u8variant__h
#include <map>
#include <vector>
#include <string>
#include <sstream>

#include "wrappers.h"
#include "common.h"

struct M3U8AlternativeMedia
{
    std::string type;
    std::string uri;
    std::string groupid;
};

struct M3U8StreamInfo
{
    std::string url;
    HeaderMap headers;
    std::string codecs;
    std::string resolution;
    M3U8AlternativeMedia audio;
    M3U8AlternativeMedia subtitles;
    unsigned long int bitrate;

    bool operator<(const M3U8StreamInfo& m) const
    {
        return bitrate < m.bitrate;
    }
};

class M3U8VariantsExplorer
{
    std::string url;
    HeaderMap headers;
    std::vector<M3U8StreamInfo> streams;
    const unsigned int redirectLimit;
    int parseStreamInfoAttributes(const char *line, M3U8StreamInfo& info, std::vector<M3U8AlternativeMedia>& altstreams);
    int parseAlternativeMediaAttributes(const char *line, std::vector<M3U8AlternativeMedia>& altstreams, const std::string& url);
    int getVariantsFromMasterUrl(const std::string& url, HeaderMap& headers, unsigned int redirect);
public:
    M3U8VariantsExplorer(const std::string& url, const HeaderMap& headers):
        url(url),
        headers(headers),
        redirectLimit(5){};
    std::vector<M3U8StreamInfo> getStreams();

};

bool isM3U8Url(const std::string& url);
#endif

