# Project 2
## Autor: Jan Novák <xnovak3i@stud.fit.vutbr.cz>
## Popis projektu
Cílem projektu je vytvořit program, který bude implementovat základní matematické operace nad množinami a binárními relacemi. Vstupem programu budou textová data reprezentující množiny a relace a zadání operací. Výsledek zpracování bude program tisknout na standardní výstup.  

## Specifikace programu
Program implementujte ve zdrojovém souboru setcal.c (Set Calculator). Vstupní data budou čtena ze souboru, jehož jméno bude zadáno argumentem příkazové řádky. Program provádí operace zadané v souboru po řádcích jedním průchodem. Výsledek zpracování každého řádku program tiskne na standardní výstup (tedy počet řádků na výstupu odpovídá počtu řádků vstupního souboru). 

### Syntax spouštění
    ./setcal FILE

### Formát vstupního souboru

Textový soubor se skládá ze tří po sobě následujících částí:

- Definice univerza - jeden řádek začínající "U " a pokračující mezerou oddělenými prvky,
- Definice množin a relací - jeden nebo více řádků začínající "S " nebo "R " a pokračující mezerou oddělenými prvky (řádek začínající "S" indikuje definici množiny, "R" slouží pro definici relace),
- Příkazy nad množinami a relacemi - jeden nebo více řádků začínající "C " a pokračující identifikátorem příkazu

#### __Univerzum__

Prvky univerza mohou býtjsou řetězce obsahující malá a velká písmena anglické abecedy. Délka řetězce je maximálně 30 znaků. Prvky univerza nesmí obsahovat identifikátory příkazů (viz níže) a klíčová slova true a false. Všechny prvky v množinách a relacích musí patřit do univerza. Příklad: 

    U Apple Lemon Orange Banana Peach

#### __Množiny__

Každá množina je definovaná na jednom řádku mezerou oddělenými prvky z univerza. Identifikátorem množiny je číslo řádku, na kterém je množina definovaná (vzhledem k tomu, že na prvním řádku souboru je univerzum, identifikátory množin tedy začínají číslem 2). Identifikátory množin jsou použity v operacích (viz níže). Příklad definice množiny:

    S Apple Banana Peach

#### __Relace__

Každá relace je definována výčtem dvojic. Dvojice je ohraničená kulatými závorkami, první a druhý prvek dvojice jsou oddělené mezerou. Jednotlivé dvojice jsou oddělené mezerou. Příklad:

    R (Apple Banana) (Apple Peach) (Apple Apple)

#### __Příkazy__

Každý příkaz je definován na jednom řádku, začíná identifikátorem příkazu a argumenty příkazu jsou oddělené mezerou (od identifikátoru i mezi sebou). Argumenty příkazu jsou číselné identifikátory množin a relací (celá kladná čísla, číslo 1 identifikuje množinu univerza). Příklad:

    C minus 1 2

### Příkazy nad množinami

Příkaz pracuje nad množinami a jeho výsledkem je buď množina (v tom případě tiskne množinu ve stejném formátu jako se očekává ve vstupním souboru, tj. začíná "S " a pokračuje mezerou oddělenými prvky) nebo je výsledkem pravdivostní hodnota (v tom případě tiskne true nebo false na samostatný řádek) nebo je výsledkem přirozené číslo (které se tiskne na samostatný řádek).

- empty A - tiskne true nebo false podle toho, jestli je množina definovaná na řádku A prázdná nebo neprázdná.
- card A - tiskne počet prvků v množině A (definované na řádku A).
- complement A - tiskne doplněk množiny A.
- union A B - tiskne sjednocení množin A a B.
- intersect A B - tiskne průnik množin A a B.
- minus A B - tiskne rozdíl množin A \ B.
- subseteq A B - tiskne true nebo false podle toho, jestli je množina A podmnožinou množiny B.
- subset A B - tiskne true nebo false, jestli je množina A vlastní podmnožina množiny B.
- equals A B - tiskne true nebo false, jestli jsou množiny rovny.

Příkazy nad relacemi

Příkaz pracuje nad relacemi a jeho výsledkem je buď pravdivostní hodnota (tiskne true nebo false), nebo množina (tiskne množinu ve formátu jako ve vstupnímu souboru).

- reflexive R - tiskne true nebo false, jestli je relace reflexivní.
- symmetric R - tiskne true nebo false, jestli je relace symetrická.
- antisymmetric R - tiskne true nebo false, jestli je relace antisymetrická.
- transitive R - tiskne true nebo false, jestli je relace tranzitivní.
- function R - tiskne true nebo false, jestli je relace R funkcí.
- domain R - tiskne definiční obor funkce R (lze aplikovat i na relace - první prvky dvojic).
- codomain R - tiskne obor hodnot funkce R (lze aplikovat i na relace - druhé prvky dvojic).
- injective R A B - tiskne true nebo false, jestli je funkce R injektivní. A a B jsou množiny; a∈A, b∈B, (a,b)∈R.
- surjective R A B - tiskne true nebo false, jestli je funkce R surjektivní. A a B jsou množiny; a∈A, b∈B, (a,b)∈R.
- bijective R A B - tiskne true nebo false, jestli je funkce R bijektivní. A a B jsou množiny; a∈A, b∈B, (a,b)∈R.

### Implementační detaily

Maximální podporovaný počet řádků je 1000.

Na pořadí prvků v množině a v relaci na výstupu nezáleží.

Všechny prvky množin a v relacích musí patřit do univerza. Pokud se prvek v množině nebo dvojice v relaci opakuje, jedná se o chybu.

### Příklady použití

```
$ cat sets.txt
U a b c x y z
S a b c x
S x y z
C intersect 2 3
C minus 2 3

$ ./setcal sets.txt
U a b c x y z
S a b c x
S x y z
S x
S a b c
```

```

$ cat rel.txt
U dad mom girl boy man woman
R (dad boy) (dad girl) (mom boy) (mom girl)
R (dad man) (boy man) (mom woman) (girl woman)
C codomain 2
C function 3

$ ./setcal rel.txt
U dad mom girl boy man woman
R (dad boy) (dad girl) (mom boy) (mom girl)
R (dad man) (boy man) (mom woman) (girl woman)
S boy girl
true
```
