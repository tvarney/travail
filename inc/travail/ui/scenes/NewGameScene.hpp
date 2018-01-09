
#ifndef TRAVAIL_NEW_GAME_SCENE_HPP
#define TRAVAIL_NEW_GAME_SCENE_HPP

#include "travail/ui/Scene.hpp"

#include "travail/ui/Label.hpp"
#include "travail/ui/InputField.hpp"
#include "travail/ui/Option.hpp"
#include "travail/ui/Column.hpp"
#include "travail/ui/Row.hpp"

namespace travail {
    class NewGameScene : public Scene {
    public:
        NewGameScene();
        virtual ~NewGameScene();
        
        virtual void run();
        virtual void handle(int ch);
    protected:
        bool m_Running;
        Column m_Column;
        Row m_Row;
        
        Label m_LabelTitle, m_LabelHelp1, m_LabelHelp2;
        InputField m_Name, m_Age, m_Height, m_Weight;
        Option m_Gender;
        Label m_LabelStr, m_LabelStrVal;
        Label m_LabelDex, m_LabelDexVal;
        Label m_LabelAgl, m_LabelAglVal;
        Label m_LabelCon, m_LabelConVal;
        Label m_LabelInt, m_LabelIntVal;
        Label m_LabelWis, m_LabelWisVal;
        Label m_LabelCha, m_LabelChaVal;
        Label m_LabelNext;
    };
}

#endif
