#ifndef BrickType_hpp
#define BrickType_hpp

#include "SDL.h"
#include <string>
using namespace std;

class BrickType
{
private:
	char id;
	int hitPoints;		//koliko je puta potrebno pogoditi ciglu
	int breakScore;		//bodovi za razbijanje
	
	string texture;
	string hitSound;
	string breakSound;
	
public:
	BrickType();
	~BrickType();

	char getId() { return id; }
	int getHitPoints() { return hitPoints; }
	void addToHitPoints(int n) { hitPoints += n; }
	int getBreakScore() { return breakScore; }
	void setBrickType(char c);
};

#endif /* BrickType_hpp */