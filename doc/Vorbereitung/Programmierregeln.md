# Programmierregeln
## Über dieses Dokument
Programmieren in einem Team ist immer eine Herausforderung, und sie wächst
sehr stark mit der Anzahl teilnehmenden Entwickler. Entwickler legen sich
oft gegenseitig beim Programmieren Steine in den Weg. Und dies ganz
unabsichtlich, es passiert einfach:

* Der Programmierstil entspricht in etwa der Handschrift eines Menschen,
  jeder hat einen eigenen, und geht Probleme anders an.

* Wenn ein Programmierer sich im "Flow" befindet, ist alles sonnenklar.
  Weniger trifft dies auf die Leute zu, die dann versuchen den Code
  zu verstehen.

* Jeder verwendet eigene Commit/Branching-Models, was zu einem
  extremen Durcheinander führen kann.

Es braucht gewisse Regeln, die eingehalten werden sollten.

*Linus Torvalds*, "Schöpfer" des Linux Kernels, an dem
parallel mehr als aktive 4300 Entwickler beteiligt sind, schreibt
in einem eigens als Regelwerk vorgesehenem Dokument:

						Linux kernel coding style
						
	This is a short document describing the preferred coding style for the
	linux kernel. Coding style is very personal, and I won't _force_ my
	views on anybody, but this is what goes for anything that I have to be
	able to maintain, and I'd prefer it for most other things too. Please
	at least consider the points made here.


Auch wenn unser Projekt deutlich kleiner ausfällt, sollten wir
uns gewisse Sachen vornehmen.

## Programmierstil
### Leerzeilen
Von Leerzeilen soll gebraucht gemacht werden! Zusammengehörende Blöcke
wie Eingabe, oder eine ganze Auswertung sollen im Code als solche von
unten und oben etwas abgegrenzt ersichtlich sein.

### Tabulatoren
Code zwischen geschweiften Klammern `{ }` wird mit einem Tabulator eingerückt.

### Sonstige Leerzeichen
Man findet Leerzeichen vor Operatoren, nicht aber zum Beispiel nach `if`.
	if(this->hasVisited == 4)

### Variabeln
Variabeln sollten so benannt werden, das man sich darunter etwas vorstellen
kann, ohne das die Variable zu lange wird.

	int anzahlverbleibendeschuesse;

ist ein schlechtes Beispiel. Besser wären schlicht:

	int anzahlSchuesse;
	int schuesse;

### camelCase
Die Namen von Funktionen, Klassen und Variabeln werden in camelCase geschrieben.
Dies erhöht die Leserlichtkeit von Namen enorm. Dabei wird das Wort am Anfang
klein geschrieben, jedes dazugehörige Wort fängt aber wieder gross an.
Beispiele:

	int anzahlAbwesende;
	class personenKoordinaten;
	bool personVergleichen(person person1, person person2);


## Workflow
Der Workflow bezeichnet den Arbeitsablauf beim Programmieren. 

### Commits
Commits sollten für sich abschliessend sein. Das heisst es wird gecommitet,
wenn zum Beispiel Änderungen am Soundmodul durchgeführt wurden. Es macht keinen
Sinn zu warten, und dann Änderungen, die Verschiedenes bewirken in einen Commit
zu stecken. (Sammelcommit) Besonders darauf zu achten gilt, wenn nur
ein kleiner Fehler behoben wurde.

### Pushes
Es hat sich in meinen Erfahrungen gezeigt, dass es Sinn macht, wenn möglich
Commits nach dem Erstellen gleich zu pushen. Damit geht man anfälligen
Merge Conflicts aus dem Weg, sollte später gepusht werden, wenn ähnliche
Änderungen bereits durchgeführt werden. Ausserdem sind die anderen Entwickler
auf dem neusten Stand über Fortschritte in anderen Modulen.

### Branches
Der master Branch müsste immer funktionieren. Entwicklungen von Modulen,
und ganz besonders Experimente müssen ausgelagert werden, damit sie die
Stabilität nicht beeinflussen. Harmonieren die Änderungen in den anderen
Branches mit dem master Branch, so dürfen diese in den master Branch
gemergt werden.  


## Nichts ist perfekt
Die Entwicklung einer Software kann kurzzeitige Störungen im
Zentralnervensystem hervorrufen. Besonders dann, wenn zum x-ten Mal
etwas nicht funktioniert, oder Mitentwickler einem den Build verderben.
Wir sind Mitentwickler, nicht Gegenentwickler! Also ruhig bleiben,
Kopf in Geradlage zurückheben, Speichelproduktion einstellen und Finger
aus dem Mund nehmen! ;)


###### Diese Informationen basieren auf meinen Erfahrungen; Gerne können wir über einzelne Punkte diskutieren.
