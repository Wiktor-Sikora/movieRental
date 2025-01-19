CREATE TABLE IF NOT EXISTS "users"(
  "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
  "login" TEXT UNIQUE NOT NULL,
  "password" TEXT NOT NULL,
  "is_admin" INTEGER NOT NULL DEFAULT '0',
  "is_blocked" INTEGER NOT NULL DEFAULT '0'
);
CREATE TABLE IF NOT EXISTS "movies"(
  "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
  "name" TEXT NOT NULL,
  "description" TEXT,
  "released" INTEGER NOT NULL,
  "price" REAL DEFAULT '10.00',
  "in_stock" INTEGER DEFAULT '10'
);
CREATE TABLE IF NOT EXISTS "rental"(
  "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
  "movie_id" INTEGER NOT NULL REFERENCES "movies"("id"),
  "user_id" INTEGER NOT NULL REFERENCES "users"("id"),
  "returned" INTEGER NOT NULL DEFAULT '0',
  "date" TEXT
);
CREATE TABLE IF NOT EXISTS "finances"(
  "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
  "amount" REAL NOT NULL,
  "user_id" INTEGER NOT NULL REFERENCES "users"("id"),
  "date" TEXT
);

INSERT INTO movies VALUES(1,'Skazani na Shawshank','Adaptacja opowiadania Stephena Kinga. Niesłusznie skazany na dożywocie bankier, stara się przetrwać w brutalnym, więziennym świecie.',1994,10.0,10);
INSERT INTO movies VALUES(2,'Zielona mila','Emerytowany strażnik więzienny opowiada przyjaciółce o niezwykłym mężczyźnie, którego skazano na śmierć za zabójstwo dwóch 9-letnich dziewczynek.',1999,10.0,10);
INSERT INTO movies VALUES(3,'Nietykalni','Sparaliżowany milioner zatrudnia do opieki młodego chłopaka z przedmieścia, który właśnie wyszedł z więzienia.',2011,10.0,10);
INSERT INTO movies VALUES(4,'Ojciec chrzestny','Opowieść o nowojorskiej rodzinie mafijnej. Starzejący się Don Corleone pragnie przekazać władzę swojemu synowi.',1972,10.0,10);
INSERT INTO movies VALUES(5,'Dwunastu gniewnych ludzi','Dwunastu przysięgłych ma wydać wyrok w procesie o morderstwo. Jeden z nich ma wątpliwości dotyczące winy oskarżonego.',1957,10.0,10);
INSERT INTO movies VALUES(6,'Forrest Gump','Historia życia Forresta, chłopca o niskim ilorazie inteligencji z niedowładem kończyn, który staje się miliarderem i bohaterem wojny w Wietnamie.',1994,10.0,10);
INSERT INTO movies VALUES(7,'Lot nad kukułczym gniazdem','Historia złodzieja, szulera i chuligana, który, by uniknąć więzienia, udaje niepoczytalność. Trafia do szpitala dla umysłowo chorych, gdzie twardą ręką rządzi siostra Ratched.',1975,10.0,10);
INSERT INTO movies VALUES(8,'Ojciec chrzestny II','Rok 1917. Młody Vito Corleone stawia pierwsze kroki w mafijnym świecie Nowego Jorku. Ponad 40 lat później jego syn Michael walczy o interesy i dobro rodziny.',1974,10.0,10);
INSERT INTO movies VALUES(9,'Władca Pierścieni: Powrót króla','Zwieńczenie filmowej trylogii wg powieści Tolkiena. Aragorn jednoczy siły Śródziemia, szykując się do bitwy, która ma odwrócić uwagę Saurona od podążających w kierunku Góry Przeznaczenia hobbitów.',2003,10.0,10);
INSERT INTO movies VALUES(10,'Lista Schindlera','Historia przedsiębiorcy Oskara Schindlera, który podczas II wojny światowej uratował przed pobytem w obozach koncentracyjnych 1100 Żydów.',1993,10.0,10);
INSERT INTO movies VALUES(11,'Pulp Fiction','Przemoc i odkupienie w opowieści o dwóch płatnych mordercach pracujących na zlecenie mafii, żonie gangstera, bokserze i parze okradającej ludzi w restauracji.',1994,10.0,10);
INSERT INTO movies VALUES(12,'Życie jest piękne','Zamknięty w obozie koncentracyjnym wraz z synem Guido próbuje przekonać chłopca, że okrutna rzeczywistość jest jedynie formą zabawy dla dorosłych.',1997,10.0,10);
INSERT INTO movies VALUES(13,'Władca Pierścieni: Dwie wieże','Drużyna Pierścienia zostaje rozbita, lecz zdesperowany Frodo za wszelką cenę chce wypełnić powierzone mu zadanie. Aragorn z towarzyszami przygotowuje się, by odeprzeć atak hord Sarumana.',2002,10.0,10);
INSERT INTO movies VALUES(14,'Pulp Fiction','Przemoc i odkupienie w opowieści o dwóch płatnych mordercach pracujących na zlecenie mafii, żonie gangstera, bokserze i parze okradającej ludzi w restauracji.',1994,10.0,10);
INSERT INTO movies VALUES(15,'Życie jest piękne','Zamknięty w obozie koncentracyjnym wraz z synem Guido próbuje przekonać chłopca, że okrutna rzeczywistość jest jedynie formą zabawy dla dorosłych.',1997,10.0,10);
INSERT INTO movies VALUES(16,'Władca Pierścieni: Dwie wieże','Drużyna Pierścienia zostaje rozbita, lecz zdesperowany Frodo za wszelką cenę chce wypełnić powierzone mu zadanie. Aragorn z towarzyszami przygotowuje się, by odeprzeć atak hord Sarumana.',2002,10.0,10);
INSERT INTO movies VALUES(17,'Siedem','Dwóch policjantów stara się złapać seryjnego mordercę wybierającego swoje ofiary według specjalnego klucza - siedmiu grzechów głównych.',1995,10.0,10);
INSERT INTO movies VALUES(18,'Podziemny krąg','Cierpiący na bezsenność mężczyzna poznaje gardzącego konsumpcyjnym stylem życia Tylera Durdena, który jest jego zupełnym przeciwieństwem.',1999,10.0,10);
INSERT INTO movies VALUES(19,'Chłopcy z ferajny','Kilkunastoletni Henry i Tommy DeVito trafiają pod opiekę potężnego gangstera. Obaj szybko uczą się panujących w mafii reguł.',1990,10.0,10);
INSERT INTO movies VALUES(20,'Pianista','Podczas drugiej wojny światowej Władysław Szpilman, znakomity polski pianista, stara się przeżyć w okupowanej Warszawie.',2002,10.0,10);
INSERT INTO movies VALUES(21,'Milczenie owiec','Seryjny morderca i inteligentna agentka łączą siły, by znaleźć przestępcę obdzierającego ze skóry swoje ofiary.',1991,10.0,10);
INSERT INTO movies VALUES(22,'Piękny umysł','Geniusz matematyczny John Nash za wszelką cenę pragnie opracować teorię, dzięki której zostanie cenionym naukowcem. Przeszkodą staje się jego stopniowo rozwijająca choroba.',2001,10.0,10);
INSERT INTO movies VALUES(23,'Django','Łowca nagród Schultz i czarnoskóry niewolnik Django wyruszają w podróż, aby odbić żonę tego drugiego z rąk bezlitosnego Calvina Candie''ego.',2012,10.0,10);
INSERT INTO movies VALUES(24,'Król Lew','Targany niesłusznymi wyrzutami sumienia po śmierci ojca mały lew Simba skazuje się na wygnanie, rezygnując z przynależnego mu miejsca na czele stada.',1994,10.0,10);
INSERT INTO movies VALUES(25,'Incepcja','Czasy, gdy technologia pozwala na wchodzenie w świat snów. Złodziej Cobb ma za zadanie wszczepić myśl do śpiącego umysłu.',2010,10.0,10);
INSERT INTO movies VALUES(26,'Joker','Strudzony życiem komik popada w obłęd i staje się psychopatycznym mordercą.',2019,10.0,10);
INSERT INTO movies VALUES(27,'Gran Torino','Walt Kowalski to emerytowany weteran żyjący we własnym poukładanym świecie. Jego spokój zostaje zburzony przez nowych sąsiadów z Azji, których syn spróbuje ukraść mu ulubione auto.',2008,10.0,10);
INSERT INTO movies VALUES(28,'Człowiek z blizną','Rok 1980. Pochodzący z Kuby przestępca, Tony Montana, tworzy w Miami narkotykowe imperium.',1983,10.0,10);
INSERT INTO movies VALUES(29,'Coco','Dwunastoletni meksykański chłopiec imieniem Miguel usiłuje zgłębić tajemnice rodzinnej legendy.',2017,10.0,10);
INSERT INTO movies VALUES(30,'Wyspa tajemnic','Szeryf federalny Daniels stara się dowiedzieć, jakim sposobem z zamkniętej celi w pilnie strzeżonym szpitalu dla chorych psychicznie przestępców zniknęła pacjentka.',2010,10.0,10);
INSERT INTO movies VALUES(31,'Leon zawodowiec','Płatny morderca ratuje dwunastoletnią dziewczynkę, której rodzina została zabita przez skorumpowanych policjantów.',1994,10.0,10);
INSERT INTO movies VALUES(32,'Green Book','Drobny cwaniaczek z Bronksu zostaje szoferem ekstrawaganckiego muzyka z wyższych sfer i razem wyruszają na wielotygodniowe tournée.',2018,10.0,10);
INSERT INTO movies VALUES(33,'Szeregowiec Ryan','W poszukiwaniu zaginionego szeregowca wysłany zostaje doborowy oddział żołnierzy.',1998,10.0,10);
INSERT INTO movies VALUES(34,'Whiplash','Młody i ambitny perkusista za wszelką cenę pragnie dołączyć do czołówki najwybitniejszych artystów muzyki jazzowej.',2014,10.0,10);
INSERT INTO movies VALUES(35,'Przełęcz ocalonych','Schyłek II wojny światowej. Podczas krwawej bitwy o Okinawę amerykański sanitariusz odmawia noszenia broni i zabijania z powodów moralnych.',2016,10.0,10);
INSERT INTO users (login, password, is_admin, is_blocked) VALUES('admin', 'password', 1, 0);