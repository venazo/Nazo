#include "Logger.h"
#include "../resource/FileUtils.h"

namespace Zewada
{
    Logger::Logger()
    {
	    //m_old = std::cout.rdbuf(m_log.rdbuf());
    }

    Logger::~Logger()
    {
	    std::string log;
	    log = m_log.str();
	    FileUtils::SerializeData("Log.txt", log);
    }

    const std::string Logger::GetLog()
    {
	    //m_log.str() is only temprorary deletes itself instantly
	    static std::string log;
	    log = m_log.str();
	    return log;
    }
}