# Lernprotokoll

(Format: Datum - Name)
(Alle Commits: Eintrag Lernprotokoll)

### 15.10.14

Aktueller Stand: Jan und Gabriel haben sich mit C++ vertraut gemacht und verfügen einigermassen über Grundlagen. Patrick sich über SFML informiert und hat die beiden anderen beim lernen unterstützt.
Wir sind heute zum Schluss gekommmen, dass nach dem erlernen von C++ nun fürs erste die Gameidee im Zentrum unseres Projektes steht. Wir haben beschlossen, dass wir bis am Freitag alle konkrete Ideen zu den jeweiligen Ideen mitbringen und wir haben uns Mittwoch den 22. Oktober als Datum festgelegt an dem wir eine einigermassen konkrete Idee haben und an dem der Projektvertrag fertig ist. Aus unserer Sicht sind wir auf gutem Wege und haben ein gutes Gefühl.

### 22.10.14

Wir haben uns auf eine Spielidee geeinigt: Wir programmieren ein Einbrecherspiel. Dazu haben wir bereits erste Überlegungen zu Design, Realisierung und Dauer gemacht. Wir haben uns auf ein 2D-Spiel aus der Vogelperspektive geeinigt, bei dem man in ein Haus einbrechen muss. Es soll 3 Spielmodi haben:
  1. Einen bestimmten Gegenstand klauen
  2. In einer bestimmten Zeit so viel wie möglich stehlen
  3. Einen möglichst hohen Wert erreichen

### 29.10.14

Die Spielidee haben wir bereits verfeinert und haben uns erste Ziele gesetzt: Bis nächsten Montag soll ein Bild im Hintergrund des Spieles geladen werden und es sollte eine Figur haben die man über den Bildschirm bewegen kann. Ausserdem sollten auch Mauern und eine Kolliosionsüberprüfung vorhanden sein. Wir haben heute die main.cpp Datei erstellt und  somit offiziel mit dem Programmieren des Spiels angefangen. Dazu haben wir ein Demo-Hintergrundbild, Demo-Level und Demo-Spielertextur erstellt um das Spiel testen zu können.

### 04.11.14 - Gabriel Gavrilas

Wir haben den Projektvertag nun vollständig abgabebereit. Der Demo-Level funktioniert bereits, wobei wir jedoch probleme mit dem definieren der Mauern haben. Dadurch bleibt unser Spiel momentan noch eine Figur, die sich auf einem gezeichneten Hintergrund bewegt. Bei Jan funktioniert das Laden des Hintergrundes und der Spielerfigur nicht perfekt. Wir freuen uns, dass wir unsere Ziele grösstenteils erreicht haben. Als nächstes sollten wir weitere Elemente in die Demo-Version einfügen.

### 08.11.14 - Patrick Eigensatz

Heute sind uns einige Errungenschaften gelungen: Zum einen haben wir die `sf::View` Klasse, die SFML bereitstellt erfolgreich einsetzen können, d. h. das Spiel müsste jetzt,
unabhängig von der Auflösung oder der Bildschirmgrösse immer gleich aussehen. Schuld, dass es bis jetzt nicht funktionierte, war ein Missverständnis der SFML-Dokumentation,
das auch etwas durch eine Inkonsistenz der SFML-Funktionen entstand. Ausserdem wurden diverse Probleme mit der Kollisionsdetektion gelöst. Es gibt keine "Schlupflöcher" mehr
in den Mauern und man kann problemlos um die Mauer herumlaufen. (Es existieren also auch keine unsichtbaren Mauern mehr!). Bei Jan funktionieren die Skalierungen noch nicht wie gewünscht.


### 09.11.14 - Patrick Eigensatz

Gabriel hat durch langes Ausprobieren und tüfteln unsere Bildschirmauflösungsprobleme fast überall verbannt. Auch hat er es geschafft, die Benachrichtigungsklasse im Spiel richtig einzusetzen, bzw. zum Laufen zu bringen. Jan meldet
noch vereinzelt Probleme mit seinem Laptop, das Spiel scheint aber bei allen anderen Versuchspcs (mehr als 7!)
ohne Probleme zu funktionieren. Wir vermuten seine Probleme in der hohen Auflösungdes PCs. Wir arbeiten an einer Lösung, (lassen diese jetzt aber bewusst im Hintergrund) und
kümmern uns darum wichtige Teile des Spiels (GUI, Updater, Schätze, Spielfluss) zu implementieren.

### 12.11.14

Wir sind noch einmal zusammen gesessen und haben versucht das Game auf Jans PC auch ohne Probleme zum laufen zu bringen. Da haben wir auch entschieden, dass wir das Bild nach dem Spieler ausrichten, so dass der Spieler immer in der Mitte der Ansicht ist. Wir dachten, dass das Problem dadurch vielleicht einfacher zu beheben ist. Durch das Einführen einer Zoom-Funktion können wir nun manuel die Einstellung der Grösse und der Ansicht des Spielerfeldes einstellen. Damit ist das erste Problem der Ansicht schon einmal behoben. Jetzt bleiben nur noch die Mauern. Im zusammenhang mit diesen haben wir bemerkt, dass wir 2 Koordinatensysteme haben und Jans PC damit wohl mühe hat. Das haben wir jetzt auch behoben und jetzt werden die Mauern auch bei Jan richtig skaliert. Das einzige das noch nicht funktioniert ist zur Zeit die Konsole die nicht angezeigt wird bei Jan. Aber wir entscheiden uns, dass diese im Moment nicht weiternotwendig ist und sind sehr froh, dass wir es hinbekommen haben, dass das Game auf all unseren 3 PCs läuft. Nun fasst jeder von uns ein kleines neuses Ziel. Patrick verfeinert die Ansicht unseres Games und einer zusätzlichen demo Map und Gabriel will sich nun mal mit den Türen befassen, Jan übernimmt den Auftrag vom programmieren von Schätzen.
Wir haben auch noch den Projektvertrag zurückerhalten und werden nun die uns empfolenen Verbesserungen übernehmen. Wir haben eine sehr nützliche und gut aufgebaute Kritik erhalten, so dass wir jetzt auch konkret wissen was wir besser machen müssen und auf was wir achten müssen.

### 19.11.14

Durch gute zusammen Arbeit konnten wir heute den Projektvertrag verbessert wieder mitbringen und haben den Vertrag alle zusammen unterschrieben. 
Jan muss nach kurzer Absprache seine Zeilen nocheinmal überarbeiten, da wir uns entschieden die Schätze auch in die Animations-Klasse zu nehmen. Diese hat Patrick kurzerhand selber geschrieben und auch geich für die Mauern kompatibel gemacht und die Pfeile eingefügt hat. Patrick hat auch aus lauter freude einen kleinen Cheat geschrieben um durch die Mauern gehen zu können. Dafür muss man nur die Konsole öffnen mit der Shift Taste. Gabriel hat bereits die ersten Zeilencode geschrieben für die Türen, nach absprache haben wir ein leicht verbeserte Variante gewählt um die Türen zum laufen zu bringen. Wir bleiben am Ball. Die letsten factor funktionen wurden entfernt, da es diese nicht wirklich braucht.

### 26.11.14

Wir haben bis und mit heute einen weiteren Schritt gemacht. Gabriel hat die Türen gezeichnet und nun so weit, dass wir die Tür öffnen können. Und heute ist es sogar schon so weit, durch gemeinsame Denkarbeit, dass man die Türe öffnen und schliessen kann. Wenn man auf dem Feld der Türe landet. Jetzt braucht es nur noch dass man nicht mehr durch die Türen hindurch gehen kann. Jan hat die Schätze auch so weit, dass man sie auf Abfrage entfernen kann wenn man auf ihnen ist. Das Bild wird auch noch skaliert und so besser dem Spiel angepasst. Wir haben uns aufgeschrieben, was es alles noch braucht, bis wir von einem kompletten Game sprechen können. Das wäre sicher Möbel, Zeitlimite, Sound, das Aussenlevel(mit weniger Gewichtung), ein Startmenu. Bis nächste Woche sollen sich alle ein paar Gedanken machen zum Problem  mit den undurchlaufbaren Mauern.

### 03.12.14 - Gabriel Gavrilas

Wir arbeiten immernoch an den Türen. Diese lassen sich bereits öffnen und schliessen, doch sind geschlossene Türen noch passierbar. Wir haben auch gemerkt, dass das eine viel schwierigere Aufgabe ist, als zuvor agenommen. Wir suchen heute eine Lösung zu diesem Problem.
Wir müssen eine Mauer an der Position der Türe mit den Dimensionen und der Rotation der Türe erstellen.
Dazu wollte Ich noch, dass diese entsprechende Mauer erst entsteht, wenn die Türe auch wirklich geschlossen ist.
Wir haben nun eine Lösung gesucht, und haben schlussendlich, nach Patricks Empfehlung, auf Pointer auf Funktionen zurückgegriffen.
Da uns allen dieses Gebiet noch nicht so bekannt war, mussten wir uns noch einarbeiten und haben dies heute noch nicht vollendet.
Voraussichtlich werden wir in einigen Tagen auch dieses Problem behoben haben.
Unsere nächsten Ziele werden ein GUI(Patrick), Möbel(Jan?), Aussenbereich des Hauses(Ich?), Gegner und Laserschranken, sowie Ton und Lärmpegeleinbau im Spiel.
