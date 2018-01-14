
#ifndef TRAVAIL_COMMAND_BUFFER_HPP
#define TRAVAIL_COMMAND_BUFFER_HPP

#include <list>
#include <string>

#include "travail/ui/TextField.hpp"
#include "travail/graphics/Curses.hpp"
#include "travail/math/Point.hpp"
#include "travail/util/History.hpp"

namespace travail {
    class CommandBuffer : public TextField {
    public:
        static const std::string ClassName;
        
    public:
        CommandBuffer();
        CommandBuffer(const std::string & name);
        CommandBuffer(int width);
        CommandBuffer(const std::string & name, int width);
        CommandBuffer(const Point2i & origin, int width);
        CommandBuffer(const std::string & name, const Point2i & origin,
                      int width);
        virtual ~CommandBuffer();
        
        virtual int handle(int ch) override;
        
        virtual const std::string & classname() const override;
        
        History & getHistory();
        const History & getHistory() const;
    protected:
        int m_HistoryIndex;
        History m_History;
        History::Iterator m_HistoryPos;
        std::string m_Stash;
    };
}

#endif
