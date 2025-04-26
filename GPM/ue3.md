# Übung 3

Elias Leonhardsberger - s2310307019

## Beispiel 1

### a) Ermitteln Sie den kritische Pfad

A -> D -> G -> H

### b) Wie hoch ist die Durchlaufzeit ?

14 Stunden

### c) Wie hoch ist die kumulierte Pufferzeit in diesem Geschäftsprozess?

4 Stunden

### d) Angenommen dieser Prozess beginnt Montag 8:00 Uhr. Ein Arbeitstag dauert von 8:00 bis 17:00 Uhr (in der Mittagspause von 12:00 bis 13:00 wird 1 Stunde nicht gearbeitet). Wann ist dieser Prozess frühestens fertig?

Dienstag 15 Uhr

### e) Wie wirken sich diese Optionen auf den Endzeitpunkt aus, angenommen Aktivität F beginnt

#### 1 Stunden später?

Gar nicht, da G und H länger dauern

#### 3 Stunden später?

Wird um eine Stunde nach hinten verschoben, da es dann eine Stunde länger als G und H dauert.

## Beispiel 2

### a) Berechnen Sie die Beanspruchung der Ressourcenklasse „Helpdesk-Mitarbeiter*in“ je Instanz

Beanspruchung = 120 + (300 + 180) \* 0.9 = 552s

### b) Wie hoch ist die theoretische Kapazität (μ) der Ressourcenklasse „Helpdesk-Mitarbeiter*in“ je Stunde

μ = (5 \* 3600) / 552 = 32,6 Anfragen pro Stunde

### c) Wie hoch ist die Ressourcenauslastung (ρ) dieser Ressourcenklasse

μ pro Tag = y = 260,8

ρ = 250 / 260,8 = 95,86%

## Beispiel 3

### a) Ermitteln Sie die durchschnittliche Durchlaufzeit in Tagen

Durchlaufzeit = 1,5 + 6 + (3 + 3) / 0.8 = 15 Tage

### b) Ermitteln Sie die gesamte durchschnittliche Bearbeitungszeit in Stunden

Bearbeitungszeit = 0,5 + 8 + (4 + 2) / 0.8 = 16 Stunden

### c) Ermitteln Sie die Durchlaufzeiteffizienz in %

Durchlaufzeiteffizienz = 16 / (15 * 24) = 4,44444%

### d) Ermitteln Sie die durchschnittlichen Kosten einer Instanz

Kosten = 0,5 \* 25 + 8 \* 50 + (4 \* 75 + 2 \* 100) / 0.8 = 1037,5€

## Bespiel 4

### a) Berechnen Sie die theoretische Kapazität (μ) jeder dieser beiden Ressourcenklassen pro Woche

BeanspruchungV = 2 + (3 + 2 + 1) * 0.9 = 7,4

BeanspruchungP = 2 * 0.9 = 1,8

µV = 64 / 7,4 = 8,6 pro Woche

µP = 8 / 1,8 = 4,4 pro Woche

### b) Welche der Klassen ist der Engpass?

Produktionsleiter

### c) Angenommen es treffen in einer Woche 4 Angebote ein (λ=4), wie gestaltet sich die Auslastung der beiden Ressourcenklassen (ρ) in dieser Woche

4 / 8,6 = 46,51% für Vertriebsingenieurinnen

4 / 4,4 = 90,9% für Produktionsleiter
