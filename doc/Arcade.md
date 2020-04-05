# Documenation Arcade

Cette documentation à pour but d'expliquer comment implémenter de nouvelles bibliotheques graphique ainsi que de nouveaux jeux.


## Comment implémenter les bibliotheques

Chaque bibliotheques graphiques utilisent des méthodes communes hérité d'une interface : **IGraphicLib**.
Cela permet de rendre le jeu indépendant de la bibliotheque graphique mais également de rendre le jeu compatible
avec d'autres bibliotheques graphiques.

Pour créer un nouveau jeu ou une nouvelle bibliotheque graphique, il faut le ou la compiler pour en faire une bibliotheque partagée et la mettre dans le dossier **lib** ou **games** à la racine du repository.

Le coreProgram se chargera de récupérer les .so se trouvant dans les dossiers **games/**, **lib/** et d'ainsi les charger.

## Comment créer un jeu

Pour créer un jeu, il vous faudra créer un fichier **[Nom_du_jeu].hpp** contenant une classe qui hérite des méthodes de l'interface **IGame.hpp**. Pour vos objets il vous faudra hériter de la classe **IGameObject.hpp**

### IGame.hpp

```cpp
typedef  struct  Rect_s {
    int left;
    int top;
    int width;
    int height;
} Rect;

class  IGame {
    public:
	virtual  ~IGame() = default;							// Destructor
	virtual  int  handleEvents(const  unsigned  char  &c) = 0;			// Reçois les events des touches, et return un status pour savoir si le jeu est fini (win ou loose) ou si il doit continuer.
	virtual  void  updateGame(void) = 0;						// Permet d'update les objets qui ne dépendent pas d'inputs, mais par exemple du temps
	virtual  std::list<std::shared_ptr<IGameObject>> getObjects(void) const = 0;	// Retourne votre liste d'objets
	virtual  Rect  getAppearanceRectIdx(int  idx) = 0;				// Retourne le rect de vos objets en fonction d'un index
	virtual  char  getAppearanceCharIdx(int  idx) = 0;				// Retourn un char (apparence pour lib textuel) en fonction d'un index
	virtual  int  getScore() const = 0;						// Retourn le score actuel de la partie
};
```
### IGameObject.hpp
```cpp
class  IGameObject {
    public:
	virtual  ~IGameObject() = default;
	virtual  std::pair<float, float> getPos() const = 0;
	virtual  char  getAppearance() const = 0;
};
```

Ces méthodes sont communes à tous les jeux, car elles sont appelés dans la boucle principale du Core.
Libre à vous de rajouter ensuite vos méthodes dans la classe de votre jeu qui modifieront ensuite votre liste d'objets.


## Comment créer une bibliotheque graphique

Pour créer une bibliotheque graphique, il vous faudra créer un fichier **[Nom_de_la_lib].hpp** contenant une classe qui hérite des méthodes de l'interface **IGraphicLib.hpp**.


### IGraphicLib.hpp
```cpp
class  IGraphicLib {
    public:
	virtual  ~IGraphicLib() = default;
	virtual  char  getEvent() = 0;							// Catch les inputs claviers
	virtual  void  draw(std::shared_ptr<IGame> game) = 0;				// Draw les Objets des jeux
	virtual  void  loadGame(const  std::string  &gamename) = 0;			// Initialise la lib en fonction des infos du jeu
	virtual  void  draw_score(int  score, std::pair<float, float> pos) = 0;		// Affiche le score
	virtual  void  gameOver(int  score) = 0;					// Affiche la fin du jeu
	virtual  void  init_score(int  score, std::pair<float, float> pos) = 0;		// Initialise l'objet score
};
```

Ces méthodes sont communes à toutes les bibliotheques graphiques car elles sont appelés dans la boucle principale du Core.

## Gestion d'erreur

Une classe pour gérer les erreurs a été mise en place **Exception.hpp**, pour l'utiliser il suffit d'utilise le code si dessous.
```cpp
if (...)
    throw(Exception ("Message d'erreur"));
```

### Exception.hpp
```cpp
class  Exception : public  std::exception {
    public:
	Exception(std::string  const  &str) {message = str;}
	std::string  what() {return (message);}
    private:
	std::string message;
};
```
