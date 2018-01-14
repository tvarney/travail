
#ifndef TRAVAIL_TEXT_FIELD_HPP
#define TRAVAIL_TEXT_FIELD_HPP

#include <string>
#include "travail/ui/Widget.hpp"

namespace travail {
    class TextField : public Widget {
    public:
        static const std::string ClassName;
        
        typedef int (*TextPredicate)(int);
        
    public:
        TextField();
        explicit TextField(const std::string & name);
        explicit TextField(int width);
        TextField(const std::string & name, int width);
        TextField(int x, int y, int width);
        TextField(const std::string & name, int x, int y, int width);
        TextField(const Point2i & origin, int width);
        TextField(const std::string & name, const Point2i & origin, int width);
        virtual ~TextField();
        
        virtual const std::string & getContents() const;
        virtual void setContents(const std::string &string);
        
        virtual void setMaxLength(std::size_t max);
        virtual std::size_t getMaxLength() const;
        
        virtual void setPredicate(TextPredicate validch);
        
        virtual Point2i getCursor() const;
        
        /**
         * \brief Interpret input.
         * 
         * This method interprets the value in \c ch as if it was obtained by
         * the ncurses \c getch() method. It attempts to provide basic line
         * editing functionality in a style similar to emacs.
         * 
         * \arg \c ch The input character
         * \return The character if it isn't handled, 0 otherwise
         */
        virtual int handle(int ch) override;
        /**
         * \brief Draw entire TextField
         */
        virtual void draw() override;
        
        virtual const std::string & classname() const;
        
        /**
         * \brief Add character to content buffer.
         * 
         * This method assumes that std::isprint(ch) returns true. If window is
         * nullptr then there is no graphical update issued.
         * 
         * \arg \c ch The printable character to add
         */
        virtual void addch(char ch);
        /**
         * \brief Delete character at cursor.
         * 
         * This method removes the character after the insertion point into the
         * content buffer. This does nothing if the cursor points to the end of
         * the content buffer. The cursor does not move.
         */
        virtual void delch();
        /**
         * \brief Move cursor back and delete character.
         * 
         * This method implements the familiar backspace operation; delete the
         * character before the cursor and move backwards.
         */
        virtual void bspace();
        
        virtual void cmove(int amount);
        
        virtual void pword();
        virtual void nword();
        virtual void toeol();
        virtual void tosol();
        
        virtual void cleareol();
        
        virtual void clear();
        
        virtual void updateCurs() const;
    protected:
        TextPredicate m_ValidCh;
        
        std::size_t m_MaxStrSize; //< Maximum buffer length
        std::size_t m_StrIndex; ///< Index into the content buffer
        std::size_t m_DispIndex; ///< Index into content buffer where we start
        std::size_t m_Cursor; ///< Where we are on screen
        std::size_t m_Advance; ///< How much to advance the screen on updates
        std::string m_Buffer; ///< Content buffer
    };
}

#endif
