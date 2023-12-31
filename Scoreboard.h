#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <vector>

namespace Scoreboard{

    class Scoreboard{
        public:
            Box* getBox(int id_box); 
        protected:


            std::vector<Box> board;
    };
}

#endif