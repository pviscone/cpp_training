# Inheritance

E' un modo per creare classi a partire da altre già esistenti ereditandone attributi e metodi (modificandoli o sovrascrivendoli se necessario)

**Terminologia**: 

- Base class: La classe dal quale si eredit
- Child/Derived/sub class: La classe che eredita dalla base class
- "Is-A relashionship": Le child class sono sotto tipi più specifici della base class

Ci sono delle differenze tra ereditarietà e composizione (istanza di un'altra classe nella classe (anche definire una variabile come attributo è composizione))

| Inheritance                                                  | Composizione                                                 |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| "Is-a" relationship: Ovvero una sottoclasse che condivide gli attributi della parent class | "Has-a" relationship: Ovvero relazione di possesso. Una classe "Persona" può possedere una classe "Account" nonostante non condividano attributi |

Volendo si possono usare entrambi. Se facciamo composizione nella parent class la acquisiranno anche le child class

## Tipi di accesso

L'inheritance può essere private, public e protected. Di default è private ma conviene solitamente si usa la public.

> Nell'Header della child class bisogna includere l'header della Base class

```cpp
class Base{};
//Al posto di public ci può essere anche private o protected
class Child: public Base{};
```

- Public: Più comune, stabilisce relazione "is -a": Acquisice i membri pubblici della base class come public e i protected come protected
- Private: Acquisisce i membri pubblici e protected della base class come private nella child
- Protected: Acquisisce i membri pubblici e protected della base class come protected nella child

**I membri private della base class sono sempre inaccessibili dalla child**. 

Le non public inheritance seguono la logica di "Is implemented in term of" invece di "is a". Simile alla composizione ma non è la stessa cosa. In ogni caso conviene non abusare dell'inheritance 

### Protected members

I membri protected di una classe sono accessibili da tutti i metodi della classe ma non sono accessibili direttamente dagli oggetti della classe. Praticamente sono come dei private ma si possono ereditare

## Costruttori e distruttori

 La parte della base class della child class deve essere inizializzata prima della child class.

Quando viene creato un oggetto della child class viene eseguito prima il costruttore della parent class e poi quello della child class.

I **distruttori** invece vengono chiamati al contrario, viene eseguito prima il distruttore della child class poi quella della base class. Ogni distruttore si deve occupare di deallocare le risorse allocate dal costruttore della propria classe

La **child class NON eredita**:

- Costruttori e distruttore della base class **MA** i costruttori/distruttore della child class possono invocare quelli della base
- Operatore di assegnamento = overloadato della base class **MA** l'operatore di assegnamento della child può invocare quello della base
- Le friends function della base class

Nel corpo della child class è possibile usare il Base operator dove base è il nome della classe  (using Base::Base;) (introdotto in c++11) che permette inheritance esplicita dei costruttori ma segue uno sbotto di regole.

```cpp
//Student ha costruttore con 2 parametri name e age
class Student : public Person{
    private:
    	int grades;
    public:
    	Student(string name,int age,int grades_val){
            Person(name,age);
            grades=grades_val;
        }
};

//Oppure se vogliamo usare la class initialization list
Student::Student(string name, int age, int grades_val):
	Person{name,age},grades{grades_val}{
    }
```



## Copy constructor

Quando copiamo un oggetto della child class dobbiamo copiare anche la parte della base class. 
Basta invocare il copy constructor della base class in quello della child

```cpp
Student::Student(const Student &other):
	Person(other),grades{other.grades}{}
//Può confondere il fatto che si passa al costruttore di person (che si aspetta un oggetto person) la reference di un oggetto student ma il compilatore sa il fatto suo

```

Per il move constructor funziona allo stesso identico modo

### Overloaded copy assignment

Anche qui basta invocare prima quello della base class

```cpp
Person::Person &operator=(const Person &rhs){
    if (this !=rhs){
        name=rhs.name;
        age=rhs.age;
    }
    return *this
}

Student::Student &operator=(const Student &rhs){
    if (this != &rhs){
        Person::operator=(rhs);
        grades=rhs.grades;
    }
    return *this
}
```

Se non definisci un copy/move constructor per la child class il compilatore chiamerà automaticamente quello della base class.

**Attenzione a lavorare con i puntatori, devi implementare deep copy**

## Ridefinire i membri della base class

Oltre a chiamare i membri della base class la child class può anche sovrascriverli, ridefinirli o fare overloading

```cpp
//Esempio: Estensione della funzione. sia parent dotata di metodo func
class Child : public Parent{
    public:
    	void func(){
            Parent::func();
            //do something else
        }
}
```

### Static binding

Di default  il compilatore decide quale metodo è stato chiamato durante la fase di compilazione (static binding methods call).
E' un metodo molto efficiente ma può essere comodo avere un approccio diverso e farlo a runtime (dynamic binding)

```cpp
//Esempio
Base *ptr = new Child(); //Si può fare in quando un Child è anche un base

//Su ptr se chiamiamo un metodo sarà chiamato il metodo della classe Base ma in questo caso potrebbe essere utile usare il metodo della classe child
```



## Multiple Inheritance

Una classe può ereditare da più classi contemporaneamente

```cpp
class Child:
	public Parent1, public Parent2{
        
    };
```

Spesso può essere evitata, pensaci 2 volte prima di usarla
