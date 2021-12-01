Pridani repozitare do slozky s projektem

git init
git config --global user.name "........"
git config --global user.email .............
git remote add origin https://git.fit.vutbr.cz/xnovak3i/IZP_projekt_2.git


Pridani souboru do repozitare

git add NAZEV_SOUBORU.txt
git commit -m "......."     Napr. "first commit", "prvni", "nahrani Honza 3"
git push -u origin master
Bude to po vas chtit prihlasovaci jmeno a heslo
Jsou stejna jako udaje do WISu tzn. xprijmeni0 a vase heslo


Nahrani obsahu repozitare - Prvni spusteni

git pull origin master


Aktualizace obsahu souborů - Nutné provádět pravidelně před začátkem programování a před nahráním do repozitáře

git add NAZEV_SOUBORU_K_AKTUALIZACI.txt
git commit -m "......."     Napr. "first commit", "prvni", "nahrani Honza 3"
git pull origin master

do souboru se vam nahraji nove casti, ktere pridali jini lide
Následně otevřete aktualizované soubory a upravíte si je
odstranite vse mezi "<<<<<<HEAD" a "======", takto je ozanacen stary kod ktery nekdo zmenil
Nasledne

git push -u origin master
