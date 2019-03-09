-- Adminer 4.7.0 MySQL dump

SET NAMES utf8;
SET time_zone = '+00:00';
SET foreign_key_checks = 0;
SET sql_mode = 'NO_AUTO_VALUE_ON_ZERO';

DROP TABLE IF EXISTS `books`;
CREATE TABLE `books` (
  `bookID` int(11) NOT NULL AUTO_INCREMENT,
  `moduleID` int(11) NOT NULL,
  `title` text NOT NULL,
  `author` text NOT NULL,
  `BookYear` year(4) NOT NULL,
  `Diathesima` int(11) NOT NULL,
  `EkdotikosOikos` text NOT NULL,
  `Address` text NOT NULL,
  PRIMARY KEY (`bookID`),
  KEY `moduleID` (`moduleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `books` (`bookID`, `moduleID`, `title`, `author`, `BookYear`, `Diathesima`, `EkdotikosOikos`, `Address`) VALUES
(25,	15100001,	'ΑΠΕΙΡΟΣΤΙΚΟΣ ΛΟΓΙΣΜΟΣ ΤΟΜΟΣ Ι',	'FINNEY R.L., WEIR M.D., GIORDANO F.R. ',	'2018',	8,	'HISTORICAL QUEST',	'Χρυσηίδος 66, 131 22 Ίλιον (ή Νέα Λιόσια) Αττικής'),
(204,	15100114,	'ΓΡΑΜΜΙΚΗ ΑΛΓΕΒΡΑ ΚΑΙ ΕΦΑΡΜΟΓΕΣ',	'STRANG GILBERT ',	'2019',	34,	'ΚΕΝΤΡΟ ΛΕΞΙΛΟΓΙΑΣ',	'Διάκου Αθανάσιου 26, 570 09 Καλοχώρι Θεσσαλονίκης\r\n'),
(251,	15100090,	'ΕΙΣΑΓΩΓΗ ΣΤΟΥΣ ΑΛΓΟΡΙΘΜΟΥΣ ΤΟΜΟΣ Ι',	'CORMEN T.H., LEISERSON C.E., RIVEST R.L., STEIN C. ',	'2017',	28,	'ΤΟΥΜΠΗΣ ΣΤ. & ΣΙΑ Ο.Ε',	'Κορίνης 3, Ομόνοια, 105 53 Αθήνα Αττικής'),
(260,	15100088,	'ΔΟΜΕΣ ΔΕΔΟΜΕΝΩΝ',	'ΓΕΩΡΓΑΚΟΠΟΥΛΟΣ Γ.Φ.',	'2016',	40,	'ΔΙΣΙΓΜΑ',	'Δοϊράνης 134, 176 73 Καλλιθέα Αττικής'),
(3046,	15100114,	'ΜΙΑ ΕΙΣΑΓΩΓΗ ΣΤΗ ΓΡΑΜΜΙΚΗ ΑΛΓΕΒΡΑ ΤΟΜΟΣ Ι',	'ΒΑΡΣΟΣ, ΔΕΡΙΖΙΩΤΗΣ, ΕΜΜΑΝΟΥΗΛ, ΜΑΛΙΑΚΑΣ, ΜΕΛΑΣ, ΤΑΛΕΛΛΗ ',	'2019',	4,	'ΕΚΔΟΣΕΙΣ ΠΑΡΑΣΚΕΥΑΔΑΚΗ',	'Τρικούπη Χαρίλαου 83, Εξάρχεια, 106 81 Αθήνα Αττικής'),
(3873,	15100091,	'Μεταγλωττιστές Γλωσσών Προγραμματισμού: Θεωρία & Πράξη',	'Κωνσταντίνος Λάζος, Παναγιώτης Κατσαρός, Ζαφείρης Καραϊσκος ',	'2018',	45,	'ΚΑΣΤΑΝΙΑ ΒΑΣΙΛ',	'Λεωφόρος Μεσογείων 419, 153 43 Αγία Παρασκευή Αττικής'),
(7982,	15100088,	'Δομές Δεδομένων με C',	'Νικόλαος Μισυρλής ',	'2017',	16,	'ΠΑΡΙΣΙΑΝΟΥ Α.Ε.',	'Ράλλη Ιωάννη 21, Άνω Μποφίλια, 144 52 Μεταμόρφωση Αττικής'),
(9691,	15100429,	'Προγραμματισμός με τη C++',	'Stroustrup Bjarne ',	'2017',	0,	'HISTORICAL QUEST',	'Χρυσηίδος 66, 131 22 Ίλιον (ή Νέα Λιόσια) Αττικής'),
(9719,	15100154,	'Συστήματα Κινητών Επικοινωνιών',	'Κανάτας Αθανάσιος,Κωνσταντίνου Φίλιππος,Πάντος Γεώργιος ',	'2015',	13,	'ΚΕΝΤΡΟ ΛΕΞΙΛΟΓΙΑΣ',	'Διάκου Αθανάσιου 26, 570 09 Καλοχώρι\r\n'),
(9771,	15100419,	'Σύγχρονη κρυπτογραφία',	'Γκρίτζαλης Στέφανος ',	'2017',	17,	'ΤΟΥΜΠΗΣ ΣΤ. & ΣΙΑ Ο.Ε',	'Κορίνης 3, Ομόνοια, 105 53 Αθήνα Αττικής'),
(12072,	15100429,	'Η ΓΛΩΣΣΑ ΠΡΟΓΡΑΜΜΑΤΙΣΜΟΥ C++',	'BJARNE STROUSTRUP ',	'2016',	14,	'ΔΙΣΙΓΜΑ',	'Δοϊράνης 134, 176 73 Καλλιθέα Αττικής'),
(12172,	15100301,	'Εισαγωγή στην επικοινωνία ανθρώπου - υπολογιστή',	'Αβούρης Νικόλαος ',	'2016',	33,	'ΕΚΔΟΣΕΙΣ ΠΑΡΑΣΚΕΥΑΔΑΚΗ',	'Τρικούπη Χαρίλαου 83, Εξάρχεια, 106 81 Αθήνα Αττικής'),
(12186,	15100406,	'Θεμελιώδεις αρχές συστημάτων βάσεων δεδομένων',	'Elmasri Ramez,Navathe Shamkant B. ',	'2017',	46,	'ΚΑΣΤΑΝΙΑ ΒΑΣΙΛ',	'Λεωφόρος Μεσογείων 419, 153 43 Αγία Παρασκευή Αττικής'),
(12204,	15100126,	'Σήματα, συστήματα και αλγόριθμοι',	'Καλουπτσίδης Νίκος ',	'2015',	8,	'ΠΑΡΙΣΙΑΝΟΥ Α.Ε.',	'Ράλλη Ιωάννη 21, Άνω Μποφίλια, 144 52 Μεταμόρφωση Αττικής'),
(12263,	15100204,	'Unix για προγραμματιστές και χρήστες',	'Glass Graham,Albes King ',	'2018',	3,	'HISTORICAL QUEST',	'Χρυσηίδος 66, 131 22 Ίλιον (ή Νέα Λιόσια) Αττικής'),
(12270,	15100154,	'Ασύρματες επικοινωνίες',	'Rappaport Theodore ',	'2017',	0,	'ΚΕΝΤΡΟ ΛΕΞΙΛΟΓΙΑΣ',	'Διάκου Αθανάσιου 26, 570 09 Καλοχώρι Θεσσαλονίκης\r\n'),
(12304,	15100301,	'Επικοινωνία ανθρώπου - υπολογιστή, 3ή Έκδοση',	'Dix Alan J., Finlay Janet E., Abowd Gregory D., Beale Russell ',	'2019',	17,	'ΤΟΥΜΠΗΣ ΣΤ. & ΣΙΑ Ο.Ε\r\n',	'Κορίνης 3, Ομόνοια, 105 53 Αθήνα Αττικής'),
(12398,	15100429,	'Τρόπος Σκέψης σε C++, 2η Έκδοση, B\' Tόμος',	'Eckel Bruce, Allison Chuck ',	'2018',	42,	'ΔΙΣΙΓΜΑ',	'Δοϊράνης 134, 176 73 Καλλιθέα Αττικής'),
(13583,	15100090,	'ΑΛΓΟΡΙΘΜΟΙ',	'SANJOY DASGUPTA, CHRISTOS PAPADIMITRIOU, UMESH VAZIRANI ',	'2016',	28,	'ΕΚΔΟΣΕΙΣ ΠΑΡΑΣΚΕΥΑΔΑΚΗ',	'Τρικούπη Χαρίλαου 83, Εξάρχεια, 106 81 Αθήνα Αττικής'),
(13618,	15100419,	'ΒΑΣΙΚΕΣ ΑΡΧΕΣ ΑΣΦΑΛΕΙΑΣ ΔΙΚΤΥΩΝ: ΕΦΑΡΜΟΓΕΣ ΚΑΙ ΠΡΟΤΥΠΑ',	'WILLIAM STALLINGS ',	'2018',	43,	'ΚΑΣΤΑΝΙΑ ΒΑΣΙΛ',	'Λεωφόρος Μεσογείων 419, 153 43 Αγία Παρασκευή Αττικής'),
(13863,	15100204,	'ΠΡΟΓΡΑΜΜΑΤΙΣΜΟΣ ΣΕ UNIX',	'MARC J. ROCHKIND ',	'2016',	47,	'ΠΑΡΙΣΙΑΝΟΥ Α.Ε.',	'Ράλλη Ιωάννη 21, Άνω Μποφίλια, 144 52 Μεταμόρφωση Αττικής'),
(13884,	15100408,	'ΣΥΓΧΡΟΝΑ ΛΕΙΤΟΥΡΓΙΚΑ ΣΥΣΤΗΜΑΤΑ',	'ANDREW S. TANENBAUM ',	'2013',	43,	'HISTORICAL QUEST',	'Χρυσηίδος 66, 131 22 Ίλιον (ή Νέα Λιόσια) Αττικής'),
(13898,	15100090,	'ΣΧΕΔΙΑΣΜΟΣ ΑΛΓΟΡΙΘΜΩΝ',	'JON KLEINBERG, EVA TARDOS ',	'2018',	3,	'ΚΕΝΤΡΟ ΛΕΞΙΛΟΓΙΑΣ',	'Διάκου Αθανάσιου 26, 570 09 Καλοχώρι\r\n'),
(13909,	15100065,	'ΤΕΧΝΗΤΗ ΝΟΗΜΟΣΥΝΗ: ΜΙΑ ΣΥΓΧΡΟΝΗ ΠΡΟΣΕΓΓΙΣΗ',	'STUART RUSSELL, PETER NORVIG ',	'2016',	45,	'ΤΟΥΜΠΗΣ ΣΤ. & ΣΙΑ Ο.Ε',	'Κορίνης 3, Ομόνοια, 105 53 Αθήνα Αττικής'),
(13955,	15100083,	'ΕΙΣΑΓΩΓΗ ΣΤΗΝ ΕΠΙΣΤΗΜΗ ΤΩΝ ΥΠΟΛΟΓΙΣΤΩΝ',	'BEHROUZ FOROUZAN, FIROUZ MOSHARRAF ',	'2015',	41,	'ΔΙΣΙΓΜΑ',	'Δοϊράνης 134, 176 73 Καλλιθέα Αττικής'),
(13957,	15100083,	'Η ΕΠΙΣΤΗΜΗ ΤΩΝ ΥΠΟΛΟΓΙΣΤΩΝ: ΜΙΑ ΟΛΟΚΛΗΡΩΜΕΝΗ ΠΑΡΟΥΣΙΑΣΗ',	'J. GLENN BROOKSHEAR ',	'2015',	50,	'ΕΚΔΟΣΕΙΣ ΠΑΡΑΣΚΕΥΑΔΑΚΗ',	'ΕΚΔΟΣΕΙΣ ΠΑΡΑΣΚΕΥΑΔΑΚΗ'),
(14841,	15100408,	'Λειτουργικά συστήματα',	'Silberschatz Abraham,Galvin Peter B. ,Gagne Greg ',	'2017',	6,	'ΚΑΣΤΑΝΙΑ ΒΑΣΙΛ',	'Λεωφόρος Μεσογείων 419, 153 43 Αγία Παρασκευή Αττικής'),
(18331,	15100126,	'ΣΗΜΑΤΑ ΚΑΙ ΣΥΣΤΗΜΑΤΑ',	'ΣΕΡΑΦΕΙΜ ΚΑΡΑΜΠΟΓΙΑΣ ',	'2019',	16,	'ΠΑΡΙΣΙΑΝΟΥ Α.Ε.',	'Ράλλη Ιωάννη 21, Άνω Μποφίλια, 144 52 Μεταμόρφωση Αττικής'),
(31326,	15100126,	'Εισαγωγή στη θεωρία σημάτων και συστημάτων',	'Θεοδωρίδης Σέργιος, Μπερμπερίδης Κώστας, Κοφίδης Λευτέρης ',	'2014',	7,	'HISTORICAL QUEST',	'Χρυσηίδος 66, 131 22 Ίλιον (ή Νέα Λιόσια) Αττικής'),
(45234,	15100001,	'Γενικά Μαθηματικά - Απειροστικος Λογισμός τόμος Ι',	'Αθανασιάδης Χ. Ε., Γιαννακούλιας Ε., Γιωτόπουλος Σ.Χ ',	'2015',	8,	'ΚΕΝΤΡΟ ΛΕΞΙΛΟΓΙΑΣ',	'Διάκου Αθανάσιου 26, 570 09 Καλοχώρι\r\n'),
(45346,	15100091,	'Μεταγλωττιστές',	'Παπασπύρου Νικόλαος Σ.,Σκορδαλάκης Εμμανουήλ Σ. ',	'2018',	14,	'ΤΟΥΜΠΗΣ ΣΤ. & ΣΙΑ Ο.Ε',	'Κορίνης 3, Ομόνοια, 105 53 Αθήνα Αττικής'),
(45390,	15100001,	'Εφαρμοσμένος Απειροστικός Λογισμός',	'Τσίτσας Λ. ',	'2016',	5,	'ΔΙΣΙΓΜΑ',	'Δοϊράνης 134, 176 73 Καλλιθέα Αττικής'),
(12713790,	15100091,	'Μεταγλωττιστές',	'Alfred V. Aho, Monica S. Lam, Ravi Sethi, Jeffrey D. Ullman ',	'2017',	40,	'ΕΚΔΟΣΕΙΣ ΠΑΡΑΣΚΕΥΑΔΑΚΗ',	'Τρικούπη Χαρίλαου 83, Εξάρχεια, 106 81 Αθήνα Αττικής'),
(12867416,	15100065,	'ΤΕΧΝΗΤΗ ΝΟΗΜΟΣΥΝΗ',	'ΒΛΑΧΑΒΑΣ Ι., ΚΕΦΑΛΑΣ Π.,ΒΑΣΙΛΕΙΑΔΗΣ Ν., ΚΟΚΚΟΡΑΣ Φ., ΣΑΚΕΛΛΑΡΙΟΥ Η.',	'2017',	22,	'ΚΑΣΤΑΝΙΑ ΒΑΣΙΛ',	'Λεωφόρος Μεσογείων 419, 153 43 Αγία Παρασκευή Αττικής'),
(13256964,	15100068,	'Ψηφιακή Επεξεργασία Φωνής: Θεωρία και Εφαρμογές',	'Rabiner L. ',	'2018',	32,	'ΠΑΡΙΣΙΑΝΟΥ Α.Ε.',	'Ράλλη Ιωάννη 21, Άνω Μποφίλια, 144 52 Μεταμόρφωση Αττικής'),
(18548901,	15100406,	'Συστήματα διαχείρισης βάσεων δεδομένων',	'Ramakrishnan Raghu, Gehrke Johannes ',	'2018',	0,	'HISTORICAL QUEST',	'Χρυσηίδος 66, 131 22 Ίλιον (ή Νέα Λιόσια) Αττικής');

DROP TABLE IF EXISTS `bookselection`;
CREATE TABLE `bookselection` (
  `selectionID` int(11) NOT NULL AUTO_INCREMENT,
  `userID` int(11) NOT NULL,
  `bookID` int(11) NOT NULL,
  PRIMARY KEY (`selectionID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `bookselection` (`selectionID`, `userID`, `bookID`) VALUES
(6,	1,	25),
(7,	1,	260),
(8,	1,	7982),
(9,	5,	12204),
(10,	5,	12072),
(11,	5,	12204),
(12,	5,	12072),
(13,	5,	12186),
(14,	5,	13256964);

DROP TABLE IF EXISTS `departments`;
CREATE TABLE `departments` (
  `departmentID` tinyint(4) NOT NULL AUTO_INCREMENT,
  `universityID` int(11) NOT NULL,
  `department` text NOT NULL,
  `books` int(11) NOT NULL,
  PRIMARY KEY (`departmentID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `departments` (`departmentID`, `universityID`, `department`, `books`) VALUES
(1,	1,	'ΠΛΗΡΟΦΟΡΙΚΗΣ ΚΑΙ ΤΗΛΕΠΙΚΟΙΝΩΝΙΩΝ',	40),
(2,	1,	'ΕΠΙΣΤΗΜΗΣ ΦΥΤΙΚΗΣ ΠΑΡΑΓΩΓΗΣ',	38);

DROP TABLE IF EXISTS `modules`;
CREATE TABLE `modules` (
  `moduleID` int(11) NOT NULL AUTO_INCREMENT,
  `title` text CHARACTER SET greek NOT NULL,
  `semester` int(11) NOT NULL,
  `departmentID` int(11) NOT NULL,
  PRIMARY KEY (`moduleID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `modules` (`moduleID`, `title`, `semester`, `departmentID`) VALUES
(15100001,	'ΑΝΑΛΥΣΗ Ι',	1,	1),
(15100065,	'ΤΕΧΝΗΤΗ ΝΟΗΜΟΣΥΝΗ',	5,	1),
(15100068,	'ΕΠΕΞΕΡΓΑΣΙΑ ΟΜΙΛΙΑΣ',	8,	1),
(15100083,	'ΕΙΣΑΓΩΓΗ ΣΤΗΝ ΕΠΙΣΤΗΜΗ ΤΗΣ ΠΛΗΡΟΦΟΡΙΚΗΣ & ΤΗΛΕΠΙΚΟΙΝΩΝΙΩΝ',	1,	1),
(15100088,	'ΔΟΜΕΣ ΔΕΔΟΜΕΝΩΝ',	2,	2),
(15100090,	'ΑΛΓΟΡΙΘΜΟΙ ΚΑΙ ΠΟΛΥΠΛΟΚΟΤΗΤΑ',	4,	2),
(15100091,	'ΜΕΤΑΓΛΩΤΙΣΤΕΣ',	6,	2),
(15100114,	'ΓΡΑΜΜΙΚΗ ΑΛΓΕΒΡΑ',	2,	2),
(15100126,	'ΣΗΜΑΤΑ ΚΑΙ ΣΥΣΤΗΜΑΤΑ',	3,	1),
(15100154,	'ΣΥΣΤΗΜΑΤΑ ΚΙΝΗΤΩΝ ΚΑΙ ΠΡΟΣΩΠΙΚΩΝ ΕΠΙΚΟΙΝΩΝΙΩΝ',	8,	2),
(15100204,	'ΠΡΟΓΡΑΜΜΑΤΙΣΜΟΣ ΣΥΣΤΗΜΑΤΟΣ',	6,	2),
(15100301,	'ΕΠΙΚΟΙΝΩΝΙΑ ΑΝΘΡΩΠΟΥ - ΜΗΧΑΝΗΣ',	7,	1),
(15100406,	'ΥΛΟΠΟΙΗΣΗ ΣΥΣΤΗΜΑΤΩΝ ΒΑΣΕΩΝ ΔΕΔΟΜΕΝΩΝ',	4,	1),
(15100408,	'ΛΕΙΤΟΥΡΓΙΚΑ ΣΥΣΤΗΜΑΤΑ',	5,	1),
(15100419,	'ΚΡΥΠΤΟΓΡΑΦΙΑ',	7,	1),
(15100429,	'ΑΝΤΙΚΕΙΜΕΝΟΣΤΡΑΦΗΣ ΠΡΟΓΡΑΜΜΑΤΙΣΜΟΣ',	3,	1);

DROP TABLE IF EXISTS `universities`;
CREATE TABLE `universities` (
  `universityID` tinyint(4) NOT NULL AUTO_INCREMENT,
  `university` text NOT NULL,
  `type` text NOT NULL,
  PRIMARY KEY (`universityID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `universities` (`universityID`, `university`, `type`) VALUES
(1,	'Εθνικό Καποδιστριακό Πανεπιστήμιο Αθηνών',	'Τεχνολογικών Επιστημών');

DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `userID` smallint(6) NOT NULL AUTO_INCREMENT,
  `username` varchar(16) NOT NULL,
  `password` varchar(32) NOT NULL,
  `email` varchar(50) NOT NULL,
  `surname` text NOT NULL,
  `name` text NOT NULL,
  `universityID` smallint(6) NOT NULL,
  `departmentID` smallint(6) NOT NULL,
  `registrationNum` varchar(40) NOT NULL,
  `phone` text NOT NULL,
  `semester` tinyint(4) NOT NULL,
  `BooksTaken` int(11) NOT NULL,
  `studentID` varchar(40) NOT NULL,
  `role` varchar(40) NOT NULL,
  PRIMARY KEY (`userID`),
  UNIQUE KEY `username` (`username`),
  KEY `universityID` (`universityID`,`departmentID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `users` (`userID`, `username`, `password`, `email`, `surname`, `name`, `universityID`, `departmentID`, `registrationNum`, `phone`, `semester`, `BooksTaken`, `studentID`, `role`) VALUES
(1,	'tester',	'81dc9bdb52d04dc20036dbd8313ed055',	'sdi140518@di.uoa.gr',	'Κώτσας',	'Αλκιβιάδης',	1,	1,	'2147483647',	'6900000000',	1,	0,	'0',	'0'),
(5,	'akotsas',	'81dc9bdb52d04dc20036dbd8313ed055',	'alkis_kotsas@gmail.com',	'Kotsas',	'Alkiviadis',	1,	1,	'53fd2feec16b1311062dbaee26a15bc9',	'6942573937',	2,	6,	'1115200900072',	'undergrad');

-- 2019-01-13 22:44:43