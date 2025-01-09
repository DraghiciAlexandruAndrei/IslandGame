#include "Game.h"
int main() {
    Game game;
    game.start();
    return 0;
}
/*
TO DO :
fast forward

--add inventory management function coppy from chat gpt
-- make work again enemies 



--repair the chances of an enemy to apear randomly when exploring->done
--fix actions thing when visiting island 
--add new location to discover
--add new resources and random how many resorces you get
--add new enemies( adding enemies when visiting the island)

--add colection of specific resources in locations

--list of location-> done




--add items by index

-->adauga inamici la locatii specifice
--> creaaza meniu separat pentru Village 
--> Vulcanul zona pe care satul o venereaza
--> tip specifici de inamice la locatii specifice 
--> poate putem face o coordonare intre locatie si inamici

-->inamici mai grei in swamp volcano village

--> random event : Intalnim un nativ cu doua choice 
                                      interact -> Sacrifice bad end
                                      stay hidden -> continue your journey
    -->tipuri de random events : enemy encounter
                                 special event encounter with natives
                                 special event gasind resourse sau arme/ lasate de alti supravietuitori.
===== foloseste polimorfism si functii virtuale pentru adaugarea itemelor in game maybe enemies and locations more easily
===== foloseste pointeri 
*/