# Übung 1

## Autoren

Patrick Fischlhammer, Elias Leonhardsberger

## Fragen

### Was ist Anstoß bzw. Auslöser des Prozesses?

Anfrage des Kunden

### Womit endet der Prozess?

Rechnung an den Kunden

### Wer ist/sind Kunde(n)?

Anfragensteller

### Worin liegt der Nutzen des Prozesses für den Kunden?

Erhalten der Ware für Zahlung

### Woran kann man messen, wie gut dieser Prozess ist?

Durchlaufzeit, beteiligte Personen, Downtime mitten im Prozess(Kaffeezeit)

### Aus welchen Tätigkeiten besteht der Prozess?

1. Anfrage bearbeiten
1. Angebot erstellen
1. Kontrolle des Angebots
1. Freigabe des Angebots
1. Im Auftragverwaltungssystem erfassen
1. Freigabe des Auftrags
1. Auftragsbestädtigung verschicken
1. Logistik Entscheidung(Auf Lager, nachbestellen oder produzieren)
1. Bei Geschäftsführung nachfragen
1. Materialauftrag erstellen
1. Material und Auftrag weitergeben
1. Material ausliefern
1. Material nachbestellen
1. Materialentnahmeschein übermitteln
1. Beleg prüfen
1. Beleg an Rechnungswesen weiterleiten
1. Beleg an Buchhaltung weiterleiten
1. Beleg an Sachbearbeiter zuteilen
1. Ausgangsrechnung verschicken

### Was braucht man für diesen Prozess (Input)?

Anfrage, Material(Falls von Zulieferer)

### Was wird entlang dieses Prozesses an Output erzeugt?

Angebot, Lieferung, Nachbestellung, Ausgangsrechnung

## Ist Aufnahme

### Übersicht

```mermaid
flowchart LR
Kunde;
Vertieb;
Logistik;
Rechnungswesen;
Buchhaltung;
Geschäftsführung;

Kunde <--> Vertieb;
Vertieb --> Logistik;
Logistik <--> Geschäftsführung;
Logistik --> Rechnungswesen;
Logistik --> Kunde;
Rechnungswesen --> Buchhaltung;
Buchhaltung --> Kunde;
```

### Vertrieb

```mermaid
flowchart LR
KundeI((Input<br>Kunde));
KundeO((Output<br>Kunde));
Logistik((Output<br>Logistik));
subgraph Vertrieb
Leiter;
SachbearbeiterA;
SachbearbeiterC;
SachbearbeiterD;
end;

KundeI --fragt an--> Leiter;
Leiter --bearbeitet Anfrage und gibt weiter--> SachbearbeiterA;
SachbearbeiterA --erstellt Angebot und gibt zur Kontrolle weiter--> Leiter;
Leiter --kontrolliert und versendet Angebot--> KundeO;

KundeI --erteilt Auftrag--> SachbearbeiterC;
SachbearbeiterC --prüft Auftrag und gibt weiter--> SachbearbeiterD;
SachbearbeiterD --erfasst Auftrag im System und gibt zur Freigabe weiter--> Leiter;
Leiter --gibt frei verschickt Auftragsbestäditigung---> KundeO;
Leiter --gibt frei und informiert Logistik---> Logistik;
```

### Logistik

```mermaid
flowchart LR
KundeO((Output<br>Kunde));
GeschäftsführungO((Output<br>Geschäftsführung));
GeschäftsführungI((Input<br>Geschäftsführung));
Rechnungswesen((Output<br>Rechnungswesen));
LieferantO((Ouput<br>Lieferant));
Vertieb((Input<br>Vertrieb));
subgraph Logistik
Leiter;
Sachbearbeiter;
SachbearbeiterH;
end;

Vertieb --informiert über Auftrag---> Leiter;
Leiter --entscheidet über Logistik und fragt bei Geschäftsführung---> GeschäftsführungO;
GeschäftsführungI --erteilt Auslieferungsauftrag---> Leiter;
Leiter --gibt Auftrag weiter--> Sachbearbeiter;
Sachbearbeiter --sendet Material--> KundeO;
Sachbearbeiter --sendet Nachbestellung--> LieferantO;
SachbearbeiterH --gibt nach dem Versand den Materialentnahmeschen weiter--> Leiter;
Leiter --prüft Beleg und gibt weiter---> Rechnungswesen;
```

### Rechnungswesen

```mermaid
flowchart LR
Logistik((Input<br>Logistik));
Buchhaltung((Output<br>Buchhaltung));
subgraph Rechnungswesen
Leiter;
end;

Logistik --gibt Beleg weiter--> Leiter;
Leiter --gibt Beleg weiter--> Buchhaltung;
```

### Buchhaltung

```mermaid
flowchart LR
Rechnungswesen((Input<br>Rechnungswesen));
Kunde((Output<br>Kunde));
subgraph Buchhaltung
Leiter;
Sachbearbeiter;
end;

Rechnungswesen --gibt Beleg weiter--> Leiter;
Leiter --teilt Beleg zu--> Sachbearbeiter;
Sachbearbeiter --verschickt Ausgangsrechnung--> Kunde;
```

## Schwachstellenanalyse

- Leiter sind persönlich verantwortlich
- Keine Vertretung
- Daduch viele Liegezeiten
- Mehr Sachbearbeiter involviert als nötig
- Leiter der Logistik entscheidet nicht über Logistik
- Prozessschritte sind direkt an Personen gebunden
- Umleitung über Rechnungswesen um Rechnung zu erstellen
- Keine gesammelten Bestellungen beim Lieferanten

## Sollkonzeption

### Übersicht

```mermaid
flowchart LR
Kunde;
Vertieb;
Logistik;
Rechnungswesen;
Buchhaltung;

Kunde <--> Vertieb;
Vertieb --> Logistik;
Logistik --> Rechnungswesen;
Logistik --> Kunde;
Logistik --> Buchhaltung;
Buchhaltung --> Kunde;
```

### Vertrieb

```mermaid
flowchart LR
KundeI((Input<br>Kunde));
KundeO((Output<br>Kunde));
Logistik((Output<br>Logistik));

subgraph Vertrieb
AnfrageEingang[Anfrage eingegangen];
AngebotErstellung[Angebot erstellt];
AngebotKontrolle[Angebot kontrolliert];
AuftragErteilt[Auftrag erteilt];
AuftragEingetragen[Auftrag im System eingetragen];
end
KundeI --fragt an--> AnfrageEingang;
AnfrageEingang --Angebot durch einen der Sacharbeiter erstellen--> AngebotErstellung;
AngebotErstellung --Angebot durch Leiter / Vertretung kontrolliern und freigeben--> AngebotKontrolle;
AngebotKontrolle --Angebot durch Sachbearbeiter versenden--> KundeO;
KundeI --erteilt Auftrag--> AuftragErteilt;
AuftragErteilt --Auftrag durch Sachbearbeiter in System eingetragen--> AuftragEingetragen;
AuftragEingetragen --Auftragsbestätigung durch Sachbearbeiter versenden--> KundeO;
AuftragEingetragen --System benachrichtigt Logistik--> Logistik;
```

### Logistik

```mermaid
flowchart LR
KundeO((Output<br>Kunde));
Vertieb((Input<br>Vertrieb));
Rechnungswesen((Output<br>Rechnungswesen));
LieferantO((Ouput<br>Lieferant));
Buchhaltung((Output<br>Buchhaltung));

subgraph Logistik
AuftragEingegangen[Auftrag im System eingetragen];
Entscheidung[Entscheidung über Logistik getroffen];
Entnahme[Material entnommen]
Sammelbestellung[Sammelbestellung für den Lieferanten];
Lieferung[Lieferung erfolgt];
BelegInAuftragssystem[Beleg und Entnahmeschein ist im Auftragssystem];
end

Vertieb --System benachrichtigt über Auftrag---> AuftragEingegangen;
AuftragEingegangen --Entscheidung durch System getroffen--> Entscheidung;
Entscheidung --Material durch Sachbearbeiter entnommen--> Entnahme;
Entnahme --Material durch Sachbearbeiter versendet----> KundeO;
Entnahme --Materialentnahme wird durch System für Sammelbestellung markiert--> Sammelbestellung;
Sammelbestellung --Sammelbestellung durch Sachbearbeiter versendet---> LieferantO;
Entnahme -.- Lieferung;
Lieferung --Beleg und Entnahmeschein wird durch Sachbearbeiter im Auftragssystem eingetragen--> BelegInAuftragssystem;
BelegInAuftragssystem --System benachrichtigt Rechnungswesen--> Rechnungswesen;
BelegInAuftragssystem --System benachrichtigt Buchhaltung--> Buchhaltung;
```

### Buchhaltung

```mermaid
flowchart LR
Logistik((Input<br>Logistik));
Kunde((Output<br>Kunde));

subgraph Buchhaltung
BelegEingang[Beleg eingegangen];
Ausgangsrechnung[Ausgangsrechnung erstellt];
end

Logistik --System benachrichtigt über Beleg--> BelegEingang;
BelegEingang --Ausgangsrechnung wird vom System erstellt--> Ausgangsrechnung;
Ausgangsrechnung --Ausgangsrechnung wird durch Sachbearbeiter kontrolliert und versendet--> Kunde;
```
